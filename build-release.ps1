$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $projectRoot 'build-release'

New-Item -ItemType Directory -Force -Path $buildDir | Out-Null

cmake -S $projectRoot -B $buildDir -DCMAKE_BUILD_TYPE=Release
cmake --build $buildDir --config Release

$exePath = Join-Path $buildDir 'Release\zconvert.exe'
if (Test-Path $exePath) {
    Write-Host 'Release build created:' (Resolve-Path $exePath).Path
} else {
    throw 'Release build did not produce zconvert.exe'
}
