# zconvert

`zconvert` is a small C++ CLI that takes one or more folders/files, creates a ZIP archive for each input, and then renames the result to the requested extension.

> This is currently a ZIP-first workflow. It does not perform true conversion to a different archive format; it simply changes the filename suffix after creating the ZIP file.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Usage

```bash
./build/zconvert -f folder1 folder2 folder3 .epub
```

The command above will produce:

```text
folder1.epub
folder2.epub
folder3.epub
```

Each output is written next to the original input path.

## Notes

- The `-f` flag means “use this target extension for each output”.
- The extension must start with a dot, for example `.epub` or `.zip`.
- The tool creates a temporary `.zip` file for each input before renaming it to the requested extension.
