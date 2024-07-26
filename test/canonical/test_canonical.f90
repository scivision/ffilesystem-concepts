!! Reference discussion (excellent) https://stackoverflow.com/a/34271901/7703794

program my_dir
!! get executable's directory, regardless of PWD or CWD

use, intrinsic :: iso_c_binding

implicit none

interface
integer(C_SIZE_T) function fs_realpath(path, rpath, buffer_size) bind(C)
import
character(kind=C_CHAR), intent(in) :: path(*)
character(kind=C_CHAR), intent(out) :: rpath(*)
integer(C_SIZE_T), intent(in), value :: buffer_size
end function
end interface

character(:), allocatable :: resolved
character(:, kind=C_CHAR), allocatable :: buf

integer :: L, ierr

valgrind : block

valgrind : block

call get_command_argument(0, length=L, status=ierr)
if(ierr /= 0) error stop "ERROR: get_command_argument(0) failed"
allocate(character(L) :: buf)
call get_command_argument(0, buf)

!! gfortran (Windows): full path
!! gfortran (Linux): relative path
!! ifort/ifx (Windows or Linux), nvfortran, flang: relative path

resolved = canonical(trim(buf) // C_NULL_CHAR)
print '(A)', "canonical(argv[0]) = " // trim(resolved)

end block valgrind

contains

function canonical(path)

character(*), intent(in) :: path
character(:), allocatable :: canonical

character(kind=C_CHAR, len=:), allocatable :: cbuf
integer(C_SIZE_T) :: N

integer, parameter :: MAX = 4096
!! arbitrary PATH_MAX, see Ffilesystem for robust implementation

allocate(character(MAX) :: cbuf)
N = fs_realpath(trim(path) // C_NULL_CHAR, cbuf, len(cbuf, kind=C_SIZE_T))
if (N < 1) error stop "ERROR: fs_realpath failed"

canonical = cbuf(:N)

print '(a)', "OK: Fortran canonical " // canonical

end function canonical

end program
