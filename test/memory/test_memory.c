// functions:
//  fs_total_sys_memory() - returns total system memory in bytes
//  GetFreeMemory()       - returns free system memory in bytes

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(__APPLE__)
#include <mach/mach.h>
#include <sys/sysctl.h>
#elif defined(__linux__)
#include <sys/sysinfo.h>
#endif

#if !defined(_WIN32)
#include <unistd.h>
#endif

#include <limits.h>

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


long fs_get_free_memory() {
  // https://github.com/ninja-build/ninja/pull/2605
#if defined(_WIN32) || defined(__CYGWIN__)
  static long committed_idle = LONG_MAX;
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  GlobalMemoryStatusEx(&status);
  const long committed = (status.ullTotalPageFile - status.ullAvailPageFile);
  // since system use committed memory normaly, we store the smallest amount we have seen to guess how much
  // paging is non-ninja related
  committed_idle = (committed_idle < committed) ? committed_idle : committed;

  return status.ullAvailPhys - (committed - committed_idle);
#elif defined(__APPLE__)
  static uint64_t swapped_idle = LONG_MAX;
  vm_size_t page_size;
  vm_statistics64_data_t vm_stats;

  mach_port_t port = mach_host_self();
  mach_msg_type_number_t count = sizeof(vm_stats) / sizeof(natural_t);

  size_t swap_stats_size = sizeof(struct xsw_usage);
  struct xsw_usage swap_stats;

  int ctl[] = {CTL_VM, VM_SWAPUSAGE};

  int result = host_page_size(port, &page_size);
  result += host_statistics64(port, HOST_VM_INFO,
    (host_info64_t)(&vm_stats), &count);
  result -= sysctl(ctl, 2, &swap_stats, &swap_stats_size, NULL, 0);

  if (KERN_SUCCESS != result)
    // information not available
    return LONG_MAX;

  // inactive is memory is marked to be moved to swap or is fs cache and should be considered as free
  int64_t free_memory = (vm_stats.free_count + vm_stats.inactive_count ) * page_size;
  // since inactive memory can be moved to the swap this value will be inexact, and i don't belive that there is a clean solution for that.
  uint64_t used_swap = swap_stats.xsu_used;
  swapped_idle = (used_swap < swapped_idle) ? used_swap : swapped_idle;
  return free_memory - (used_swap - swapped_idle);
#elif defined(__linux__)
  static long swapped_idle = LONG_MAX;
  struct sysinfo infos;
  sysinfo(&infos);
  const long swapped = (infos.totalswap - infos.freeswap);
  // since system use committed memory normally, store the smallest amount we have seen
  swapped_idle = (swapped_idle < swapped) ? swapped_idle : swapped;
  return infos.freeram - (swapped - swapped_idle);
#else
  return LONG_MAX;
#endif
}


int main(void)
{
  unsigned long long t = fs_total_sys_memory();
  if(t <= 0)
    return EXIT_FAILURE;

  printf("Total system memory: %llu bytes\n", t);

  long f = fs_get_free_memory();
  if(f <= 0)
    return EXIT_FAILURE;

  printf("Free system memory:  %ld bytes\n", f);

  return EXIT_SUCCESS;
}
