# OpenQCD++
Testing grounds for a standard-parallelized OpenQCD port in modern C++.


## Quick overview for OpenQCD users

The code is organized in a similar fashion to how OpenQCD is organized, with the main differences being:
- The `devel` directory becomes `tests` and releases happen only with proper accompanying tests for the most part.
- There is no longer a `doc` folder with the same spirit as before, this info is instead stored as markdown files under `theoretical_framework`.
- There are now `docs` with automatically generated documentation from the code comments itself.
- The main programs are now scripted within `app` and not `main`.
- The program Makefiles are now generated with CMake, a `build` directory is also created for a CMake-oriented workflow.

E.g., while previously the workflow was:

```bash
cd OpenQCDxx/main
make PROGRAM
./PROGRAM
```

and a bunch of object files were created along the source code,

now it is:

```bash
cd OpenQCDxx/build
cmake ..
make PROGRAM
./app/PROGRAM
```

which consolidates all the compiled objects in a single directory.

