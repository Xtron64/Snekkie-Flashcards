#ifndef PATH_H
#define PATH_H
#include "shared_typedefs.h"


// Information about a given environment variable
typedef enum {
	EV_FOUND_AND_VALID = 0,         // env var exists and passed check_dir
	EV_FOUND_BUT_INVALID = -1,      // env var exists but failed check_dir
	EV_NOT_FOUND = -2,              // env var does not exist
} env_var_status_t;


// Information about a given directory
typedef enum {
	DIR_VALID = 0,                  // Dir passed all 3 checks
	DIR_MISSING = -1,               // Dir doesn't exist
	DIR_NOT_A_DIRECTORY = -2,       // Dir isn't a directory, it's a file
	DIR_NO_READ_WRITE_ACCESS = -3,  // Dir has the wrong permissions (for RW)
} dir_status_t;


wrapper_error_t find_data_dir(char **env_var);
dir_status_t check_dir(const char *dir);
env_var_status_t check_env_var(char **path_var, const char *env_var);
wrapper_error_t create_dir(const char *dir);
#endif
