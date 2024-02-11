#ifdef __cplusplus

#include <string>
void execute_process(std::string_view);
#ifdef _WIN32
void create_process(std::string_view);
#endif

#else
int execute_process(const char*);
#endif
