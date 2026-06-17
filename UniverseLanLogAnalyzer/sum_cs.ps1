$out = "all_cs.txt"
$base = (Get-Location).Path

Remove-Item $out -ErrorAction Ignore

Get-ChildItem -Recurse -Filter *.cs |
    Sort-Object FullName |
    ForEach-Object {
        $rel = $_.FullName.Substring($base.Length).TrimStart('\')
        Add-Content $out "==== $rel ====`r`n"
        Add-Content $out (Get-Content $_.FullName -Raw)
        Add-Content $out "`r`n"
    }