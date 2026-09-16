#!/usr/bin/env python3
"""Collapse consecutive identical nested scopes in UniverseLAN trace files."""

import argparse
import json
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class Scope:
    opener: str
    indent: str
    children: list = field(default_factory=list)
    closer: str | None = None
    complete: bool = False
    uid: int = 0


def delimiter(line: str, marker: str):
    stripped = line.lstrip(" \t")
    if not stripped.startswith(marker):
        return None
    return line[: len(line) - len(stripped)], stripped[1:]


def parse(lines):
    root = Scope("", "")
    stack = [root]
    problems = []
    next_uid = 1

    for number, line in enumerate(lines, 1):
        opened = delimiter(line, "+")
        closed = delimiter(line, "-")
        if opened is not None:
            indent, _ = opened
            scope = Scope(line, indent, uid=next_uid)
            next_uid += 1
            stack[-1].children.append(scope)
            stack.append(scope)
        elif closed is not None:
            if len(stack) == 1:
                problems.append({"line": number, "kind": "unmatched-close"})
                stack[-1].children.append(line)
            else:
                stack[-1].closer = line
                stack[-1].complete = True
                stack.pop()
        else:
            stack[-1].children.append(line)

    for scope in stack[1:]:
        problems.append({"line": None, "kind": "unclosed-scope", "opener": scope.opener})
    return root, problems


def normalize(scope):
    normalized = []
    for child in scope.children:
        if isinstance(child, Scope):
            normalize(child)
            key = (child.opener, tuple(child.normalized), child.closer) if child.complete else ("incomplete", child.uid)
            if child.complete and normalized and normalized[-1][0] == "scope" and normalized[-1][1] == key:
                normalized[-1][3] += 1
            else:
                normalized.append(["scope", key, child, 1])
        else:
            normalized.append(["line", child, None, 1])
    scope.normalized = normalized


def render(scope, output):
    if scope.opener:
        output.append(scope.opener)
    for kind, value, child, count in scope.normalized:
        if kind == "line":
            output.append(value)
            continue
        render(child, output)
        if count > 1:
            output.append(f"{child.indent}# repeat previous complete scope block x{count}")
    if scope.complete:
        output.append(scope.closer)


def render_expanded(scope, output):
    if scope.opener:
        output.append(scope.opener)
    for kind, value, child, count in scope.normalized:
        if kind == "line":
            output.append(value)
            continue
        for _ in range(count):
            render_expanded(child, output)
    if scope.complete:
        output.append(scope.closer)


def minimize(source: Path, destination: Path):
    raw = source.read_bytes()
    text = raw.decode("utf-8", errors="surrogateescape")
    lines = text.splitlines()
    root, problems = parse(lines)
    normalize(root)

    expanded_lines = []
    render_expanded(root, expanded_lines)
    if expanded_lines != lines:
        raise RuntimeError(f"Minimization changed trace content: {source}")

    output_lines = []
    render(root, output_lines)
    destination.write_bytes(
        ("\n".join(output_lines) + ("\n" if text.endswith(("\n", "\r")) and output_lines else "")).encode(
            "utf-8", errors="surrogateescape"
        )
    )
    return {
        "source": str(source),
        "output": str(destination),
        "original_bytes": len(raw),
        "minimized_bytes": destination.stat().st_size,
        "original_lines": len(lines),
        "minimized_lines": len(output_lines),
        "structural_round_trip_verified": True,
        "malformed": problems,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source_root", type=Path)
    parser.add_argument("output_root", type=Path)
    args = parser.parse_args()

    args.output_root.mkdir(parents=True, exist_ok=True)
    report = []
    for source in sorted(args.source_root.rglob("*.trace")):
        destination = args.output_root / f"{source.parent.name}-{source.stem}.min.trace"
        report.append(minimize(source, destination))

    report_path = args.output_root / "minimization-report.json"
    report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(report_path)


if __name__ == "__main__":
    main()
