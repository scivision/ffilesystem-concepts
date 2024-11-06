# Filesystem concepts

A testbed for the
[Ffilesystem library](https://github.com/scivision/fortran-filesystem),
to test across platforms without breaking the widely-used library.
As in Ffilesystem, we use some optional C++20 features.
The main focus is on the C++17
[filesystem](https://en.cppreference.com/w/cpp/filesystem)
standard library.
We also demonstrate techniques in C to reproduce some C++ filesystem functionality at lower fidelity--otherwise, we'd be reinventing the wheel.

## platform-independent mkdtemp()

Platform-independent
[mkdtemp()](./test/mkdtemp/)
is a C++17 example of creating a temporary directory that works on Windows, Linux, macOS, MinGW, Cygwin, WSL, etc. across compilers and operating systems.

## Canonical

Creating [canonical](./test/canonical/) "lower_name" as entirely the lower case version of "cased_name" deliberately forces the drive/root to be lower case.
In general full paths on Windows and macOS have some uppercase character elements:

* Windows: upper case drive letter
* macOS: /Users/ etc. has some upper case letters

## Copy file tree

Recursively [copy a file tree](./test/copytree/).

## Iterate over directory

[Example](./test/iterdir/) of iterating over directory contents.

## Is executable

[Is executable](./test/is_exe/) tests if a file is executable. On Windows filesystems such as NTFS, all files are always seen as executable.
On most other filesystems, executable permissions can be detected.

## file types

Show what [type a file](./test/file_types/) is, such as regular file, directory, symlink, etc.

## lib_dir

A working example of how to determine an executable's full path no matter what the current working directory is.
This can be useful when a data file is known to exist relative to an executable.
This is relevant to say CMake installed project that has an executable and associated data files installed.
Assuming the user knows the path to the MAIN executable in the installed directory, the program can determine its own full path and
then a priori know the relative path to the data file(s).

## Drive space available

Determine the [free space available on a drive](./test/space_avail/).

## Filesystem type

Determine the
[filesystem type](./test/filesystem_type/)
of a drive or partition.
Note that WSL uses
[v9fs](https://devblogs.microsoft.com/commandline/whats-new-for-wsl-in-windows-10-version-1903/).

## Windows short path

For Windows only, find the short path (8.3) from a long filename and [vice versa](./test/short_path/).

## Symbolic links

[Symbolic links](./test/symlink/) are demonstrated across platforms, including Linux, macOS, Windows, MinGW, WSL, and Cygwin.
Windows symlinks may require setting group policy (Windows Pro) or enabling Windows Developer Mode (non-Pro Windows).

## Syscall

[Example system calls](./test/syscall/) with mild effort towards security and cross-platform compatibility.
