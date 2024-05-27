option(cppcheck "Run cppcheck on the code")
option(fortran "use Fortran" on)

# Necessary for shared library with Visual Studio / Windows oneAPI -- creates .lib file to acommpany .dll -- must be BEFORE targets are declared.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
