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

#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

#ifdef _MSC_VER
#include <io.h>  // _mktemp_s
#else
#include <unistd.h> // mkstemp (macOS)
#endif

#include "mkdtemp.h"

char* mkdtemp(char* tn) noexcept(false)
{
  size_t len = strlen(tn);
  int ret = 0;
  do {
    std::strcpy(tn + len - 6, "XXXXXX");
#ifdef _MSC_VER
    // if(_mktemp_s(tn, 7) != 0)
    if (!_mktemp(tn)
#else
    if (mkstemp(tn) == -1
#endif
     || tn == nullptr || *tn == '\0')
       throw std::runtime_error("ERROR:mkdtemp:mkstemp: could not create temporary name");


    std::error_code ec;
    if (!fs::create_directory(tn, ec) && ec != std::errc::file_exists)
      throw std::runtime_error("ERROR:mkdtemp: could not create temporary directory " + ec.message());

  } while (ret != 0);
  return tn;
}
