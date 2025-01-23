#!/bin/bash

# Wrapper for gcc to enforce safe compilation practices
# Usage: ./gcc_safe.sh [gcc options]

# Mandatory flags
MANDATORY_FLAGS="-Wall -Wextra -Werror -fstack-protector-strong -D_FORTIFY_SOURCE=2 -O2"

# Disallowed flags
DISALLOWED_FLAGS=(
    "-fno-stack-protector"
    "-O0"
)

# Function to check for disallowed flags
check_disallowed_flags() {
    for flag in "$@"; do
        for disallowed in "${DISALLOWED_FLAGS[@]}"; do
            if [[ "$flag" == "$disallowed" ]]; then
                echo "Error: Disallowed flag detected: $flag"
                exit 1
            fi
        done
    done
}

# Check for disallowed flags
check_disallowed_flags "$@"

# Combine mandatory flags with user-provided flags
gcc $MANDATORY_FLAGS "$@"

