#ifdef __cplusplus
#include <string>
int execute_process(const std::string);
#else
int execute_process(const char*);
#endif

int create_process(const char*);
