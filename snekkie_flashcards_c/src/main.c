#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "headers/main_typedefs.h"	// For main.c specific typedefs
#include "headers/shared_typedefs.h"	// For typedefs shared across modules
#include "headers/getopt_parsing.h"	// yeah dw
#include "headers/print_functions.h"	// For main.c specific printf helper functions
#include "headers/commands.h"		// For the actual flashcards commands
#include "headers/path.h"		// For getting `find_data_dir_path`
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>


bool is_help_flag(const char* arg) {
	if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
		return true;
	} else return false;
}


command_t get_command(const int argc, char *argv[]) {
	if (strcmp(argv[1], "help") == 0) return HELP;
	if (is_help_flag(argv[1])) return HELP;
	if (strcmp(argv[1], "create") == 0) return CREATE;
	if (strcmp(argv[1], "revise") == 0) return REVISE;
	return INVALID;
}


argument_pattern_t validate_pattern 
(const int argc, char *argv[], command_t command) {
	/*
	 * This helper function finds if the given arguments match a certain pattern,
	 * and either prints the appropriate 'help' information for that pattern,
	 * or it will print the usage if there is something extra that is considered
	 * invalid within that pattern.
	 *
	 * Patterns:
	 * snekkie_flashcards help | --help | -h
	 * snekkie_flashcards create --help | -h
	 * snekkie_flashcards revise --help | -h
	 *
	 * If there are any trailing arguments that follow any of those patterns,
	 * we return indicating a usage error.
	 *
	 * RETURNS:
	 * - NONE_MATCHED: 
	 * when the arguments don't match any pattern.
	 * - MATCHED_AND_CORRECT_USAGE:
	 * when the arguments simply match a pattern with no trailing arguments.
	 * - WRONG_USAGE:
	 * when there are trailing arguments that break what is otherwise a matched
	 * pattern.
	 */
	if (command == HELP) {
		if (argc > 2) {
			return HELPER_WRONG_USAGE;
		} else {
			print_help();
			return HELPER_MATCHED_AND_CORRECT_USAGE;
		}
	}
	if (argc < 3) {
		return WRONG_USAGE;
	}
	if (command == CREATE && is_help_flag(argv[2])) {
		if (argc>3) {
			return HELPER_WRONG_USAGE;
		} else {
			print_create_help();
			return HELPER_MATCHED_AND_CORRECT_USAGE;
		}
	}
	if (command == REVISE && is_help_flag(argv[2])) {
		if (argc>3) {
			return HELPER_WRONG_USAGE;
		} else {
			print_revise_help();
			return HELPER_MATCHED_AND_CORRECT_USAGE;
		}
	}
	return HELPER_NONE_MATCHED;
}


wrapper_error_t check_deck_name(const char *deck) {
	for (int i = 0; deck[i] != '\0'; i++) {
		if (!(isalnum(deck[i]) || deck[i] == '_' || deck[i] == '-')) {
			return FAILURE;
		}
	}
	return SUCCESSFUL;
}


int main(const int argc, char *argv[]) {
	snekkie_flashcards_exit_t exit_code = SUCCESS;
	char *data_dir_path = NULL;
	if (argc == 2 && !(is_help_flag(argv[1]) || (strcmp(argv[1], "help") == 0))) { 
		print_usage(argv[0]);
		exit_code = WRONG_USAGE;
		goto exit;
	} else if (argc <= 1) {	
		print_usage(argv[0]);
		exit_code = WRONG_USAGE;
		goto exit;
	}
	command_t command = get_command(argc, argv);
	if (command == INVALID) {
		print_usage(argv[0]);
		exit_code = WRONG_USAGE;
		goto exit;
	}

	switch (validate_pattern(argc, argv, command)) {
	case HELPER_NONE_MATCHED:
		break;
	case HELPER_MATCHED_AND_CORRECT_USAGE:
		goto exit;
	case HELPER_WRONG_USAGE:
		print_usage(argv[0]);
		exit_code = WRONG_USAGE;
		goto exit;
	}

	switch(check_deck_name(argv[2])) {
	case SUCCESSFUL:
		break;
	case FAILURE:
		print_invalid_deck_name(argv[2]);
		exit_code = INVALID_DECK_NAME;
		goto exit;
	}

	if (find_data_dir(&data_dir_path) == FAILURE) {
		print_no_data_dir();
		exit_code = NO_DATA_DIR;
		goto exit;
	}

	if (command == CREATE && exit_code == SUCCESS) {
		create(argv[2], data_dir_path);
	} else if (command == REVISE && exit_code == SUCCESS) {
		revise(argv[2], data_dir_path);
	}
	exit:
		free(data_dir_path);
		return exit_code;
}
