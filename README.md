# AVL Tree

A self-balancing AVL tree in C++, driven by a small command interpreter on
stdin. Built for a data structures course.

Supported commands: `insert`, `remove`, `search`, `printInorder`,
`printPreorder`, `printPostorder`, `printLevelCount`, and `removeInorder`.
The program reads a command count on the first line, then that many commands,
one per line.

## Installation

Requires CMake 3.26 or newer and a C++14 compiler. CMake fetches Catch2 v3.0.1
for the test target, so the first configure needs network access.

```bash
git clone https://github.com/BryanZaneee/AVL_Tree_structure.git
cd AVL_Tree_structure
cmake -S . -B build
cmake --build build
```

That produces two binaries in `build/`: `AVLTree_complete` and `Tests`.

## Usage

```bash
./build/AVLTree_complete < testing/test-io/input-files/1.txt
```

Compare against the matching file in `testing/test-io/expected-output-files/`.

Run the unit tests:

```bash
./build/Tests
```

## Contributing

This is archived coursework and is not taking contributions.

## License

No license file is included, so this is "all rights reserved" by default.
