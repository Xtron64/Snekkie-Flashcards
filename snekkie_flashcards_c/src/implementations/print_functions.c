#include <stdio.h>
void print_usage(char* program_name) {
	/* 
	 * Very basic helper to show the user the correct usage of the program and 
	 * appropriately exit the program with a failure.
	 */
	fprintf(stderr, "Usage: %s <command> <deck> [flags...]\n", program_name);
	fprintf(stderr, "   or: %s <command> [--help | -h]\n\n", program_name);
	fprintf(stderr, "Commands: \tDescription:\n");
	fprintf(stderr, "     help \t   Show help\n");
	fprintf(stderr, "   create \t Create deck\n");
	fprintf(stderr, "   revise \t Revise deck\n");
}


void print_no_data_dir(void) {
	fprintf(stderr, "ERROR: no suitable data directory path available to store "
			"flashcards.\n");
}


void print_help(void) {
	/*
	 * Another basic helper, that prints all flags and options to the user. Doesn't
	 * exit.
	 */
	fprintf(stdout, "Not made yet soz\n");
	printf("print_help\n");
}


void print_create_help(void) {
	fprintf(stdout, "Not made yet soz\n");
	printf("print_create_helpn\n");
}


void print_revise_help(void) {
	fprintf(stdout, "Not made yet soz\n");
	printf("print_revise_help\n");
}


void print_invalid_deck_name(char* deck) {
	fprintf(stderr, "ERROR: Invalid deck name: %s\n", deck);
	fprintf(stderr, "Please only use letters, numbers, '_', and '-' in your "
			"deck's name.\n");
}
