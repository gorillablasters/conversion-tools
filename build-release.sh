#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd "$(dirname "$0")" && pwd)"
build_dir="$project_root/build-release"

mkdir -p "$build_dir"

cmake -S "$project_root" -B "$build_dir" -DCMAKE_BUILD_TYPE=Release
cmake --build "$build_dir" --config Release

if [ -f "$build_dir/Release/zconvert.exe" ]; then
  echo "Release build created: $build_dir/Release/zconvert.exe"
else
  echo "Release build did not produce zconvert.exe" >&2
  exit 1
fi
