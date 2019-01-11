## How to compile CppUMochGen on Ubuntu 18.04
First off, you need my "ugly-hacks" branch (called `compile-on-ubuntu-18.04`).

Then the following packages are needed (more or less):
* `libclang-dev`, 6.0 works
* `llvm-dev`, 6.0 works
* See original on cmake et al.

## Building
* `mkdir build`
* `cd build`
* `cmake ..`
* `make`
* `sudo make install`

## Caveats on my version
* Unit tests are disabled. Complained about a missing file `direct.h`.
  That file is part of `mingw-w64-i686-dev` in Ubuntu. Not interested in
  installing that. Maybe more Windoisms?
* Paths to clang etc are hardcoded just because I'm stupid and ignorant on
  how cmake works.
* Paths to where CppUTest is installed were missing. But since testing
  over all is disabled this doesn't matter.
  