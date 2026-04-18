#ifndef MAIN_TYPEDEFS_H
#define MAIN_TYPEDEFS_H
typedef enum {
	SUCCESS = 0,
	WRONG_USAGE = 1,
	INVALID_DECK_NAME = 2,
	NO_DATA_DIR = 3,
	MALLOC_FAILED = 4,
} snekkie_flashcards_exit_t;


typedef enum {
	HELPER_NONE_MATCHED = 0,
	HELPER_WRONG_USAGE = -1,
	HELPER_MATCHED_AND_CORRECT_USAGE = -2,
} argument_pattern_t;


typedef enum {
	HELP = 0,
	CREATE = 1,
	REVISE = 2,
	INVALID = -1,
} command_t;
#endif
