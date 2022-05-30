# brainfucker
A header-only brainfuck (BF) interpreter written in C++.

Singleton class for interpreting brainfuck code. Currently does not accept files but I'm planning on adding features in the near future. How does it work? `#include` the lib and call `Brainfucker::run(const char *)`, pointing to you brainfuck code. If you encounter anny bugs, feel free to report or suggest a fix. The code is simple enought to understand honestly, brainfuck is a simple language. :)
