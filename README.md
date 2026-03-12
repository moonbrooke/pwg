# PWG

Very simple password generator written in C.

### Compiling

- Linux: `gcc pwg.c -o pwg`
- Windows: `gcc pwg.c -o pwg -lbcrypt`

### Usage

Run `./pwg` to generate a 16-character password. For a custom length (up to 32), append the number to the command: `./pwg 20`.
