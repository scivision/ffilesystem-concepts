program test_chdir

use, intrinsic :: iso_c_binding

implicit none

interface
logical(C_BOOL) function fs_chdir(path) bind(C)
import
character(kind=C_CHAR), intent(in) :: path(*)
end function fs_chdir
end interface

character(1024) :: buf
logical :: ok

if(command_argument_count() < 1) error stop "please specify path to chdir"

call get_command_argument(1, buf)

ok = fs_chdir(trim(buf) // C_NULL_CHAR)

if (.not. ok) error stop "chdir failed"

end program
