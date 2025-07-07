#!/bin/bash
make

if [ $# -gt 0 ]; then
    echo "Running: \"$@\""
    exec "$@"
fi