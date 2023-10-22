program iterpath

use, intrinsic :: iso_c_binding

implicit none

interface
integer(C_SIZE_T) function fs_make_tempdir(result, buffer_size) bind(C)
import
character(kind=C_CHAR), intent(out) :: result(*)
integer(C_SIZE_T), intent(in), value :: buffer_size
end function

end interface

integer, parameter :: MAX_PATH = 8191

block
character(:), allocatable :: temp_dir

temp_dir = make_tempdir()

print '(a)', "OK: Fortran mkdtemp: " // temp_dir
end block !< valgrind tweak

contains

function make_tempdir() result (r)
character(:), allocatable :: r
character(kind=c_char, len=:), allocatable :: cbuf
integer(C_SIZE_T) :: N
allocate(character(MAX_PATH) :: cbuf)
N = fs_make_tempdir(cbuf, len(cbuf, kind=C_SIZE_T))
allocate(character(N) :: r)
r = cbuf(:N)
end function

end program
