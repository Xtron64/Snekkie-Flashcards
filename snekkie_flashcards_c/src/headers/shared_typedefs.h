#ifndef SHARED_TYPEDEFS_H
#define SHARED_TYPEDEFS_H
typedef enum {
	SUCCESSFUL = 0,                 // The wrapper had no errors
	FAILURE = -1,                    // The wrapper had an error
} wrapper_error_t;
#endif
