module finder

use, intrinsic :: iso_fortran_env, only : stderr=>error_unit

implicit none

contains

function get_filename(path, name)
!! given a path, stem and vector of suffixes, find the full filename
!! assumes:
!! * if present, "name" is the file name we wish to find (without suffix or directories)
!! * if name not present, "path" is the directory + filename without suffix
!!
!! suffixes to check: [character(4) :: '.h5', '.nc', '.dat']
!! if file not found, empty character is returned

character(*), intent(in) :: path
character(*), intent(in), optional :: name
character(:), allocatable :: get_filename

character(:), allocatable :: path1
character(4), parameter :: suff(3) = [character(4) :: '.h5', '.nc', '.dat']
integer :: i

integer, parameter :: MAX_PATH = 8191

get_filename = path
!! avoid undefined return

if(len(path) == 0) return

if(present(name)) then
  if(index(path, name, back=.true.) == 0) then
    !> assume we wish to append stem to path
    get_filename = path // '/' // name
  elseif(index(get_filename, '.', back=.true.) > 4) then
    !> it's a stem-matching full path with a suffix
    if(.not. is_file(get_filename)) get_filename = ''
    return
  endif
endif

if(is_file(get_filename)) return

path1 = get_filename

do i = 1, size(suff)
  get_filename = path1 // trim(suff(i))
  if (is_file(get_filename)) return
enddo

get_filename = ''
if(present(name)) then
  write(stderr,*) 'filesystem:get_filename: ',name,' not found in ', path
else
  write(stderr,*) 'filesystem:get_filename: file not found: ',path
endif

end function get_filename

end module finder
