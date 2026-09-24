"""Read-only checks for the baseline review artifacts; run from any directory."""
from collections import Counter
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
BASELINE = "b30e83872c0006e8240c8b4f565da5351bf10080"
EXCLUDED = {"EnetTest", "BehaviourTests", "TestCases", "TestCommon", "UnitTests"}
ALIASES = {
    "BASE-SERVER-002": "BASE-NET-003",
    "BASE-API-010": "BASE-SERVER-005",
    "BASE-NET-008": "BASE-STORAGE-011",
    "BASE-STORAGE-012": "BASE-UTIL-002",
    "BASE-STORAGE-022": "BASE-UTIL-002",
    "ADD-NET-001": "BASE-SERVER-019",
    "ADD-NET-004": "BASE-SERVER-008",
    "ADD-UTIL-002": "BASE-SERVER-007",
}


def git(*args):
    return subprocess.check_output(["git", *args], cwd=ROOT, text=True, encoding="utf-8")


def in_scope(name):
    path = Path(name)
    if path.suffix.lower() not in {".cxx", ".hxx", ".cmake", ".txt"}:
        return False
    if name == "CMakeLists.txt":
        return True
    parts = path.parts
    if len(parts) < 2 or parts[0] != "Source" or parts[1] in EXCLUDED:
        return False
    if parts[1] == "Vendor":
        return len(parts) == 3 and path.suffix.lower() in {".cmake", ".txt"}
    if parts[1] == "DLLs" and len(parts) > 3 and parts[3] in {"galaxy", "gog"}:
        return False
    return True


errors = []
inputs = sorted(filter(in_scope, git("ls-tree", "-r", "--name-only", BASELINE).splitlines()))
expected = {name + ".review.MD" for name in inputs}
actual = {str(p.relative_to(ROOT)).replace("\\", "/") for p in (ROOT / "Source").rglob("*.review.MD")}
if (ROOT / "CMakeLists.txt.review.MD").exists():
    actual.add("CMakeLists.txt.review.MD")
for missing in sorted(expected - actual):
    errors.append("Missing report: " + missing)
for extra in sorted(actual - expected):
    errors.append("Out-of-scope report: " + extra)

records = {}
categories = {}
evidence_references = {}
heading = re.compile(r"^#{2,6}\s+[^\n]*", re.MULTILINE)
finding_heading = re.compile(r"^#{2,6}\s+\[?((?:BASE|ADD)-[A-Z]+-\d{3})\]?")
severity_re = re.compile(r"\*\*Severity:\*\*\s*(?:\*\*)?(Critical|High|Medium|Low|Informational)")
category_re = re.compile(r"\*\*Category:\*\*\s*([^\n]+)")
reports = []
for name in sorted(expected & actual):
    path = ROOT / name
    reports.append(path)
    text = path.read_text(encoding="utf-8")
    if BASELINE not in text:
        errors.append("Missing baseline SHA: " + name)
    matches = list(heading.finditer(text))
    for index, match in enumerate(matches):
        identity = finding_heading.match(match.group())
        if not identity:
            continue
        finding = identity.group(1)
        if finding.startswith("BASE-") and re.search(r"addendum|follow.up", match.group(), re.IGNORECASE):
            continue  # Evidence refinements are not new canonical records.
        section = text[match.end():matches[index + 1].start() if index + 1 < len(matches) else len(text)]
        severity_match = severity_re.search(section)
        if not severity_match:
            if finding.startswith("BASE-"):
                evidence_references.setdefault(finding, []).append(name)
                continue
            errors.append("Missing severity: " + name + " " + finding)
            continue
        severity = severity_match.group(1)
        if finding in records and records[finding] != severity:
            errors.append("Inconsistent severity: " + finding)
        records[finding] = severity
        cat = category_re.search(section)
        if cat:
            categories.setdefault(finding, cat.group(1).strip().strip("*"))
        if "**Confidence:**" not in section:
            errors.append("Missing Confidence: " + name + " " + finding)
        if not re.search(r"\*\*(?:Exact location|Locations?|Location\(s\)):\*\*", section):
            errors.append("Missing Location: " + name + " " + finding)

for finding, paths in evidence_references.items():
    if finding not in records:
        errors.append("Evidence addendum has no canonical finding: " + finding + " " + str(paths))

addendum_dir = ROOT / ".ai/review-addendum"
coverage_counts = Counter()
if addendum_dir.exists():
    api_names = {"Chat", "Friends", "Matchmaking", "Networking", "CustomNetworking"}
    storage_names = {"Apps", "CloudStorage", "Stats", "Storage", "Telemetry", "User", "Utils"}
    def owner(name):
        parts = Path(name).parts
        if name == "CMakeLists.txt" or (len(parts) == 2 and parts[0] == "Source"):
            return "BUILD"
        component = parts[1]
        if component in {"DLLs", "Vendor"}:
            return "BUILD"
        if component in {"Server", "SystemTests", "Tracer", "Version"}:
            return "SERVER"
        if component == "Client":
            if len(parts) > 3 and parts[2] == "Impl":
                if Path(name).stem in api_names:
                    return "API"
                if Path(name).stem in storage_names:
                    return "STORAGE"
            return "CORE"
        return {"Client_NoVer": "CORE", "Shared": "NET", "Shared_NoVer": "UTIL",
                "InterceptionLogger": "INTERCEPT"}[component]
    notebooks_by_owner = {}
    for group in ("CORE", "API", "STORAGE", "NET", "UTIL", "SERVER", "INTERCEPT", "BUILD"):
        path = addendum_dir / (group + ".MD")
        if not path.exists():
            errors.append("Missing follow-up notebook: " + group)
            notebooks_by_owner[group] = ""
        else:
            notebooks_by_owner[group] = path.read_text(encoding="utf-8")
    # BUILD explicitly incorporates the exact wrapper list after re-verifying its blobs.
    notebooks_by_owner["BUILD"] += (ROOT / ".ai/review-baseline/WRAPPER-COVERAGE.MD").read_text(encoding="utf-8")
    for name in inputs:
        group = owner(name)
        coverage_counts[group] += 1
        if name not in notebooks_by_owner[group]:
            errors.append("Path absent from follow-up coverage ledger: " + group + " " + name)

notebooks = sorted((ROOT / ".ai/review-baseline").glob("*.MD"))
notebooks += sorted((ROOT / ".ai/review-addendum").glob("*.MD"))
summary = ROOT / ".ai/UniverseLAN-review-summary.MD"
if summary.exists():
    notebooks.append(summary)
for path in reports + notebooks:
    text = path.read_text(encoding="utf-8")
    for target in re.findall(r"\[[^\]\n]+\]\(([^)\n]+)\)", text):
        if re.match(r"(?:https?://|mailto:|#)", target):
            continue
        target = target.split("#", 1)[0]
        if target and not (path.parent / target).exists():
            errors.append("Broken link: " + str(path.relative_to(ROOT)) + " -> " + target)
    if any(line.rstrip(" \t") != line for line in text.splitlines()):
        errors.append("Trailing whitespace: " + str(path.relative_to(ROOT)))

source_diff = git("diff", "--name-only", BASELINE, "--", "Source", "CMakeLists.txt", ":!*.review.MD")
if source_diff.strip():
    errors.append("Production input differs from baseline: " + source_diff)

canonical = {key: value for key, value in records.items() if key not in ALIASES}
if "BASE-NET-003" in canonical:
    canonical["BASE-NET-003"] = "High"  # Combined server slot-reuse consequence.
for alias, parent in ALIASES.items():
    if alias not in records or parent not in records:
        errors.append("Unresolved alias: " + alias + " -> " + parent)

print("Baseline input files:", len(inputs))
print("Expected / actual per-file reports:", len(expected), "/", len(actual))
print("Distinct finding/investigation IDs:", len(records))
print("Finding-record severities:", dict(sorted(Counter(records.values()).items())))
print("Canonical groups (including investigations):", len(canonical))
print("Canonical severities:", dict(sorted(Counter(canonical.values()).items())))
print("Canonical High IDs:", ", ".join(sorted(k for k,v in canonical.items() if v == "High")))
def primary_category(finding):
    value = categories.get(finding, "Unspecified").rstrip(".")
    return "API/ABI" if value.startswith("API/ABI") else value.split(" / ", 1)[0]


print("Canonical primary categories:", dict(sorted(Counter(primary_category(k) for k,v in canonical.items() if v != "Informational").items())))
print("Checked notebook files:", len(notebooks))
if coverage_counts:
    print("Follow-up coverage by owner:", dict(sorted(coverage_counts.items())))
print("Errors:", len(errors))
for error in errors:
    print(error)
sys.exit(1 if errors else 0)
