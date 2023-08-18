program iterpath

use, intrinsic :: iso_c_binding

implicit none

interface
integer(C_SIZE_T) function path_parts(path, i, result, buffer_size) bind(C)
import
character(kind=C_CHAR), intent(in) :: path(*)
integer(C_INT), intent(in), value :: i
character(kind=C_CHAR), intent(out) :: result(*)
integer(C_SIZE_T), intent(in), value :: buffer_size
end function

end interface

character(2048, kind=C_CHAR) :: path, part, last_part
!! arbitrary buffer size

integer(C_INT) :: i
integer(C_SIZE_T) :: L

path = "/home/username/Downloads/"

!> 1000 is arbitrary max number of parts
do i = 0,1000
  L = path_parts(trim(path) // C_NULL_CHAR, i, part, len(part, kind=C_SIZE_T))
  if (L == 0) exit
  last_part = part(1:L)
  print *, trim(last_part)
end do

if (last_part /= "Downloads") error stop "path_parts() failed, last part " // trim(last_part) // " is not Downloads"

print *, "OK: file_parts"

end program
