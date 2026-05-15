#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
rm -rf "$ROOT/extras/tests/bin" \
       "$ROOT/extras/tests/obj" \
       "$ROOT/extras/tests/example_build" \
       "$ROOT/extras/tests/header_build"
