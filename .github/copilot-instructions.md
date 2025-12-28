# Copilot Instructions — Playfair (C++)

Quick, actionable notes to help an AI coding agent be immediately productive in this repository.

## Project overview

- Single-file C++ implementation of the Playfair cipher: `playfair.cpp`.
- Minimal project: no build scripts, no tests, no CI configuration. See `README.md` for a short summary.

## Big-picture behavior (what the program does)

- Interactive command-line program: prompts for Encode/Decode, key, whether to map I↔J, and the text to process.
- Main entrypoint: `main()` constructs a `playfair` object and calls `doIt(key, text, ij, e)`.
- Core features to understand in `playfair.cpp`:
  - `createGrid(string k, bool ij)` — builds a 5×5 key matrix (row-major) from the key + alphabet; if `ij` is true, `J` is treated as `I`, otherwise `Q` is omitted.
  - `getTextReady(string t, bool ij, bool e)` — uppercase & filter non-alpha, optionally replace `J`→`I`, remove `Q` if required, prepares digraphs and inserts `'X'` between identical letters when encoding (`e == true`), and appends `'X'` if length is odd.
  - `doIt(int dir)` — performs encryption/decryption on digraphs using Playfair rules (same row/column wrap with modular indexing, otherwise swap columns).
  - `display()` — prints `OUTPUT:` and the resulting digraphs (space-separated pairs, line-wrapped).
- Note: the grid is filled via `copy(nk.begin(), nk.end(), &_m[0][0]);` so the matrix layout is sequential in memory (row-major order).

## Build & run (examples you can use now)

- There are no build files; compile directly with a C++ compiler:
  - Linux / macOS / WSL / MSYS2 (recommended):
    g++ -std=c++17 -O2 -o playfair playfair.cpp
    ./playfair
  - Windows (MSVC cl):
    cl /EHsc /O2 playfair.cpp
    playfair.exe
  - Note: the program uses `system("pause")` at the end of `main()` (Windows-specific) — when running on non-Windows shells you may see different behavior.

## Typical interactive session (example inputs)

- When prompted:
  - `(E)ncode or (D)ecode?` → `E`
  - `Enter a en/decryption key:` → `PLAYFAIR`
  - `I <-> J (Y/N):` → `Y` (makes J treated as I)
  - `Enter the text:` → `Hide the gold in the tree stump`
- Output is printed after those prompts with `OUTPUT:` header and space-separated digraphs.

## Project-specific conventions & patterns

- Single-file implementation; no header separation; all logic inside `playfair` class.
- ASCII-only, uppercase-only processing — non A–Z characters are ignored when building the plaintext used for encryption/decryption.
-
