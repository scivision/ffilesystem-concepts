program iterpath

use, intrinsic :: iso_c_binding

implicit none

interface
integer(C_SIZE_T) function mkdtemp_f(result, buffer_size) bind(C)
import
character(kind=C_CHAR), intent(out) :: result(*)
integer(C_SIZE_T), intent(in), value :: buffer_size
end function

end interface

character(2048, kind=C_CHAR) :: path
character(:), allocatable :: temp_dir
!! arbitrary buffer size

integer(C_SIZE_T) :: L

L = mkdtemp_f(path, len(path, kind=C_SIZE_T))
if(L == 0) error stop "ERROR: Fortran mkdtemp got empty string"

allocate(character(L) :: temp_dir)
temp_dir = path(:L)

print '(a)', "OK: Fortran mkdtemp: " // temp_dir

deallocate(temp_dir)
!! for valgrind, not always detected/needed in Fortran main programs.

end program
