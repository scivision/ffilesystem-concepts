// https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes

#include <stdexcept>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void create_process(std::string_view cmd){

  STARTUPINFO si = { 0 };
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );

  // don't directly specify "cmd.exe" in exec() for security reasons
  char* comspec = std::getenv("COMSPEC");
  if(!comspec)
    throw std::runtime_error("ERROR: environment variable COMSPEC not defined");

  // https://learn.microsoft.com/en-us/troubleshoot/windows-client/shell-experience/command-line-string-limitation
  // 8191 max command line length
  std::string c = std::string(comspec) + " /c " + std::string(cmd);
  std::vector<char> buf(c.begin(), c.end());

  if (!CreateProcessA(comspec, //  COMSPEC
    buf.data(),    // Command line
    nullptr,   // Process handle not inheritable
    nullptr,   // Thread handle not inheritable
    FALSE,  // Set handle inheritance to FALSE
    0,      // No creation flags
    nullptr,   // Use parent's environment block
    nullptr,   // Use parent's starting directory
    &si,    // Pointer to STARTUPINFO structure
    &pi )   // Pointer to PROCESS_INFORMATION structure
    )
    throw std::runtime_error("CreateProcess failed: " + c);

 // Wait until child process exits.
  WaitForSingleObject( pi.hProcess, 5000 );

  if (!CloseHandle(pi.hThread) || !CloseHandle(pi.hProcess))
    throw std::runtime_error("CreateProcess:CloseHandle failed");

}
