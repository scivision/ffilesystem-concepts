/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include <cerrno>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <io.h>  // _mktemp_s
#else
#include <unistd.h> // mkstemp (macOS)
#endif

#include "mkdtemp.h"

char* mkdtemp(char* tn) {
  size_t len = strlen(tn);
  int ret = 0;
  do {
    std::strcpy(tn + len - 6, "XXXXXX");
#ifdef _WIN32
    // if(_mktemp_s(tn, 7) != 0)
    if (!_mktemp(tn)
#else
    if (mkstemp(tn) == -1
#endif
     || tn == nullptr || *tn == '\0')
    {
      std::cerr << "ERROR:mkdtemp:mkstemp: could not create temporary name " << strerror(errno) << "\n";
      return nullptr;
    }


    std::error_code ec;
    if (!fs::create_directory(tn, ec) && ec != std::errc::file_exists) {
      std::cerr << "ERROR:mkdtemp: could not create temporary directory " << ec.message() << "\n";
      return nullptr;
    }
  } while (ret != 0);
  return tn;
}
