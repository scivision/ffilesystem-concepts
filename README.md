# Filesystem concepts

A testbed for the
[Ffilesystem library](https://github.com/scivision/fortran-filesystem),
to test across platforms without breaking the widely-used library.

## Canonical

Creating "Lname" as entirely the lower case version of "Uname" deliberately forces the drive/root to be lower case.
In general full paths on Windows and macOS have some uppercase character elements:

* Windows: upper case drive letter
* macOS: /Users/ etc. has some upper case letters

## lib_dir

A working example of how to determine an executable's full path no matter what the current working directory is.
This can be useful when a data file is known to exist relative to an executable.
This is relevant to say CMake installed project that has an executable and associated data files installed.
Assuming the user knows the path to the MAIN executable in the installed directory, the program can determine its own full path and
then a priori know the relative path to the data file(s).
