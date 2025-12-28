@echo off
REM Build script for Playfair Cipher (Windows)
REM Usage: build.bat

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Compile with g++
echo Compiling Playfair Cipher...
g++ -o build\playfair.exe src\playfair.cpp -std=c++11 -O2

if %ERRORLEVEL% EQU 0 (
    echo Build successful! Executable: build\playfair.exe
) else (
    echo Build failed!
    exit /b 1
)

