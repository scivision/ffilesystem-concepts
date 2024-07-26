program test_chdir

use, intrinsic :: iso_c_binding

implicit none

interface
logical(C_BOOL) function fs_chdir(path) bind(C)
import
character(kind=C_CHAR), intent(in) :: path(*)
end function

integer(C_SIZE_T) function fs_get_cwd(path, buffer_size) bind(C)
import
character(kind=C_CHAR), intent(out) :: path(*)
integer(C_SIZE_T), intent(in), value :: buffer_size
end function
end interface

integer, parameter :: MAX_PATH = 8191

character(MAX_PATH) :: buf
logical :: ok

if(command_argument_count() < 1) error stop "please specify path to chdir"

call get_command_argument(1, buf)

print '(a)', 'current working directory: ', get_cwd()

ok = fs_chdir(trim(buf) // C_NULL_CHAR)

if (.not. ok) error stop "chdir failed"

print '(a)', 'New working directory: ', get_cwd()

contains

function get_cwd()
character(:), allocatable :: get_cwd
character(kind=c_char, len=:), allocatable :: cbuf
integer(C_SIZE_T) :: N
allocate(character(MAX_PATH) :: cbuf)
N = fs_get_cwd(cbuf, len(cbuf, kind=C_SIZE_T))
get_cwd = cbuf(:N)
end function

end program
