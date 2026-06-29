$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$releaseDir = Join-Path $projectRoot 'release-package'
$exePath = Join-Path $projectRoot 'build-release\Release\zconvert.exe'
$readmePath = Join-Path $projectRoot 'README.md'

if (-not (Test-Path $exePath)) {
    throw "Executable not found at $exePath. Run build-release.ps1 first."
}

Remove-Item -Recurse -Force $releaseDir -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Force -Path $releaseDir | Out-Null

Copy-Item $exePath -Destination $releaseDir
Copy-Item $readmePath -Destination $releaseDir

Write-Host "Release package created at:" (Resolve-Path $releaseDir).Path
