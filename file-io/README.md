# Hex Viewer

A simple hex viewer written in C.

## Description

This project reads a file in binary mode and displays its contents in hexadecimal and ASCII format, similar to the `hexdump -C` utility.

## Concepts Practiced

* File I/O
* Binary data processing
* Arrays
* Functions
* Pointers
* Output formatting

## Build

```bash
gcc hex-viewer.c -o hex-viewer
```

## Usage

```bash
./hex-viewer filename
```

## Example

```text
00000000  23 69 6e 63 6c 75 64 65 20 3c 73 74 64 69 6f 2e |#include <stdio.|
00000010  68 3e 0a 0a 76 6f 69 64 20 63 68 61 72 5f 72 65 |h>..void char_re|
```

## Future Improvements

* Configurable bytes per line
* Colored output
* Offset selection
* Better compatibility with hexdump output

