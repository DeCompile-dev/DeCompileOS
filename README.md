# Offical Readme for DeCompileOS

Build: docker build buildenv -t decompileos

# Features

- 64 Bit Long mode support
- Simple Memory handler

# Commands
- help (lists commands)
- version (prints ver and build date)
- echo [string]
- test (Runs a small test app)
- game_engine_test (simple ascii game demo)
- panic_test
and a easter egg! (find it yourself lol!)

# Running Docker - Running System

     Linux or MacOS: docker run --rm -it -v "$(pwd)":/root/env decompileos
     Windows (CMD): docker run --rm -it -v "%cd%":/root/env decompileos
     Windows (PowerShell): docker run --rm -it -v "${pwd}:/root/env" decompileos
     Docker Build command: make build-x86_64

# Architecture
     ================================================
     |             Shell Interface                  |
     |          Keyboard | IDT | GDT                |
     |             x86_64 Long Mode                 |
     |     Stage1 (MBR) → Stage2 (Protected → Long) |
     ================================================

# License
     MIT License Copyright (c) 2025 DeCompile-dev
