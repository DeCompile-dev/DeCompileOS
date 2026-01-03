# Offical Readme for DeCompileOS

Build: docker build buildenv -t decompileos

# Features

- 64 Bit Long mode support
- Simple Memory handler

# Commands
Listed by help
- help — prints the command list
- version — prints version info + build date
- test — runs the “test application” (calls the starting module)
- echo [text] — prints back whatever you type after echo 
- clear — clears the screen
- cmd_debug — triggers the main module’s debug entry (main_debug)

“Developer commands” (also shown in help)
- game_engine_test — initializes the (very simple) “game engine” flag
- game_2d — prints the ASCII box/line demo (only works after game_engine_test)
- panic_test — intentionally panics the kernel

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
