#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long fs_total_sys_memory()
{
// https://stackoverflow.com/a/2513561
#ifdef _WIN32
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if(!GlobalMemoryStatusEx(&status))
    {
        perror("ERROR: GlobalMemoryStatusEx\n");
        return 0;
    }
    return status.ullTotalPhys;
#else
    const long pages = sysconf(_SC_PHYS_PAGES);
    if(pages < 0) {
        fprintf(stderr, "ERROR: sysconf: get total number of pages  %s\n", strerror(errno));
        return 0;
    }
    const long page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size < 0) {
        fprintf(stderr, "ERROR: sysconf: get page size  %s\n", strerror(errno));
        return 0;
    }
    return pages * page_size;
#endif
}

int main(void)
{
  unsigned long long t = fs_total_sys_memory();
  if(t <= 0)
    return EXIT_FAILURE;

  printf("Total system memory: %llu bytes\n", t);
  return EXIT_SUCCESS;
}
