foreach(d IN ITEMS canonical file_types iterdir lib_dir space syscall)
  add_subdirectory(${d})
endforeacH()
