#!/usr/bin/env python3
"""
https://stackoverflow.com/questions/46113181/how-to-know-from-python-if-windows-path-limit-has-been-removed
"""

import ctypes
import ctypes.wintypes

def long_path_enabled() -> bool:
    ntdll = ctypes.WinDLL('ntdll')

    if hasattr(ntdll, 'RtlAreLongPathsEnabled'):
        ntdll.RtlAreLongPathsEnabled.restype = ctypes.c_ubyte
        ntdll.RtlAreLongPathsEnabled.argtypes = ()
        return bool(ntdll.RtlAreLongPathsEnabled())

    return False


if __name__ == '__main__':
    print("Windows long paths enabled: ", long_path_enabled())
