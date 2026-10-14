# File I/O

These examples explore reading, writing, and processing files, from small command-line utilities to file-backed data projects.

## Standalone programs

| Program | Overview |
| --- | --- |
| [`my-cat.c`](my-cat.c) | Reads bytes from a file and writes them to standard output. |
| [`my-wc.c`](my-wc.c) | Experiments with tokenizing file contents and counting lines, words, and bytes. |
| [`my-grep.c`](my-grep.c) | Searches a file for a text pattern and prints matching lines. |
| [`hex-viewer.c`](hex-viewer.c) | Displays file bytes in hexadecimal alongside printable ASCII characters. |
| [`Simple-user-database.c`](Simple-user-database.c) | Stores and lists user records in a binary file. |

## Multi-file projects

- [`memory-noteboke/`](memory-noteboke/) — a menu-driven note manager with options to add, edit, delete, and view notes.
- [`pass-database/`](pass-database/) — a binary-file record manager with options to add, delete, search, filter, and list records.

## Concepts

- C file streams: `fopen`, `fclose`, `fread`, `fwrite`, `fseek`, and `rewind`
- Text input and binary records
- Reading files by byte and by line
- Dynamic allocation while processing input
