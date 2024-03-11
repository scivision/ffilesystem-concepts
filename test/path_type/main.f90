module filesystem

implicit none

private

public :: path_t

integer, parameter :: max_path = 1024

type :: path_t
  private
  character(:), allocatable :: path_str
contains
  procedure, public :: path=>get_path
  final :: destructor
end type

interface path_t
  !! constructor
  module procedure set_path
end interface


contains

subroutine destructor(self)
  type(path_t), intent(inout) :: self
  if(allocated(self%path_str)) deallocate(self%path_str)
end subroutine destructor


type(path_t) function set_path(path)
  character(*), intent(in) :: path

  allocate(character(max_path) :: set_path%path_str)

  set_path%path_str = path

end function set_path

pure function get_path(self, istart, iend)
  character(:), allocatable :: get_path
  class(path_t), intent(in) :: self
  integer, intent(in), optional :: istart, iend
  integer :: i1, i2

  i1 = 1
  i2 = len_trim(self%path_str)
  if(present(istart)) i1 = istart
  if(present(iend))   i2 = iend

  get_path = self%path_str(i1:i2)
end function get_path

end module filesystem


program obj

use filesystem

implicit none

valgrind : block

type(path_t) :: p

p = path_t("hello")
print '(a)', p%path()

end block valgrind


end program
