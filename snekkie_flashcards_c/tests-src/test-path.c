#include "../src/headers/shared_typedefs.h"
#include "../src/headers/path.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>  // I just really want this to be pretty
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

#define BOLD "\e[1m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BOLD_YELLOW "\e[1;93m"
#define RESET "\e[0m"


void print_sep(void) {
	struct winsize ws;
	printf(BOLD);
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
		for (int i=0; i<ws.ws_col; i++) {
			putchar('=');
		}
		printf("\n");
	} else {
		// Fallback branch
		for (int i=0; i<80; i++) {
			putchar('=');
		}
		printf("\n");
	}
	printf(RESET);
}


/*
 * wrap - Word wrap text to a fixed column width
 *
 * Original author:  Ryan Uber <ryan@blankbmx.com>
 * Link:             http://www.ryanuber.com/word-wrapping-in-ansi-c.html
 *
 * (Modified by yours truly, Dylan Boughey <snekkieboi@pm.me>, for this test suite.)
 * (As far as I know, this code has no license and seems freely available.)
 *
 * This function will wrap large amounts of a text into a manageable and human-readable width
 * word by word. Just specify the number of columns you are working with and feed it a string,
 * and it will return a new string (including added line breaks) to accommodate the area you
 * are working with.
 *
 */
void wrap(char *str) {
	char *out;
	struct winsize ws;
	int columns;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
		columns = ws.ws_col;
	} else {
		columns = 80;
	}
	out = malloc(columns*2+1);  // Arbitrary but should be more than enough
	int len, n, w, wordlen=0, linepos=0, outlen=0;
	/*
	 *Find length of string 'str' without using string.h
	 */
	for (len=0; str[len]; ++len);
	/* 
	 * Allocate the full space of 'str' to 'word', so there is no possible way that the string
	 * could contain a word that does not fit into the 'word' variable.
	 */
	char word[len];
	/*
	 * Loop through each individual character in the passed array (str) and detect white space
	 * and word length to determine how to handle line wrapping.
	 */
	for (n=0; n<=len; n++) {
		/*
		 * Detect spaces and newlines. We cannot gurantee that the passed string is null-
		 * terminated, so we also need to handle cases where we reach the end of the string
		 * without encountering wite space characters.
		 */
		if (str[n] == ' ' || str[n] == '\n' || n == len) {
			/*
			 * If the current word will not fit on the current line, add a newline.
			 */
			if (linepos > columns ) {
				out[outlen++] = '\n';
				linepos = wordlen;
			}
			/*
			 * Append the found word to the output and reset the word character array in
			 * preparation for accepting characters for the next word.
			 */
			for (w=0; w<wordlen; w++ ) {
				out[outlen++] = word[w];
				word[w] = '\0';
			}
			/*
			 * If we reach the end of the string, add the null-terminator character.
			 */
			if (n == len) {
				out[outlen] = '\0';
			}
			/*
			 * If we encounter a newline character, append it to the string as usual, but
			 * set the line position counter back to 0 (new line = start count from 0 again).
			 */
			else if (str[n] == '\n') {
				out[outlen] = str[n];
				linepos=0;
			}
			/*
			 * If the word fits in the current line without trouble, just add the space.
			 */
			else {
				out[outlen] = ' ';
				linepos++;
			}
			/*
			 * Increment the final output length for the next loop, and set the word length
			 * counter back to 0 (newline or space = new word).
			 */
			outlen++;
			wordlen=0;
		}
		/*
		 * If the current character is in the middle of a word somewhere, just append it and
		 * move on, incrementing counters.
		 */
		else {
			word[wordlen++] = str[n];
			linepos++;
		}
	}
	printf("%s", out);
}


int main() {
	print_sep();
	printf(BOLD_YELLOW "TEST 1: " YELLOW "RUNNING\n" RESET);
	wrap("'create_dir()' cannot create directory with missing parent.\n");
	if (create_dir("/path/to/bs/directory") == FAILURE) {
		printf(BOLD_YELLOW "TEST 1: " GREEN "SUCCESSFUL\n" RESET);
	} else {
		printf(BOLD_YELLOW "TEST 1: " RED "FAILED\n" RESET);
	}
	print_sep();
	printf(BOLD_YELLOW "TEST 2: " YELLOW "RUNNING\n" RESET);
	wrap("'create_dir()' can create a directory when given the right permissions.\n");
	struct passwd *pw = getpwuid(geteuid());
	// I sincerely apologise to whoever is reading this for how I wrote this test
	if (pw != NULL && pw->pw_dir != NULL) {
		// Very large and could overflow but unlikely given that this 
		// is a test and the edge case for it to happen is basically 
		// the test user's fault. (Not documented, but they'd lack 
		// common sense if they hit it.)
		char *dir = malloc(strlen(pw->pw_dir)+1024);
		strcpy(dir, pw->pw_dir);
		while (true) {
			/*
			 * We do this in a loop because they may already 
			 * have the directory we decided to hard-codedly
			 * test 'create_dir()'. If the directory already 
			 * existed, errno will equal EEXIST (so retry 
			 * recursively as to eventually satisfy uniqueness 
			 * so that the directory doesn't exist).
			 * We do this in the user's home directory because 
			 * we assume they have the right permissions.
			 * (I'm not over-engineering this test further to 
			 * guarantee that.)
			 */
			strcat(dir, "/.test");
			int tmp = create_dir(dir);
			if (errno == EEXIST) {
				continue;
			} else if (tmp == SUCCESSFUL) {
				rmdir(dir);
				printf(BOLD_YELLOW "TEST 2: " GREEN "SUCCESSFUL\n" RESET);
				free(dir);
				dir = NULL;
				break;
			} else {
				rmdir(dir);
				printf(BOLD_YELLOW "TEST 2: " RED "FAILED\n" RESET);
				free(dir);
				dir = NULL;
				break;
			}
		}
	} else {
		printf(BOLD_YELLOW "TEST 4: " YELLOW "INCONCLUSIVE\n" RESET);
	}
	print_sep();
	printf(BOLD_YELLOW "TEST 3: " YELLOW "RUNNING\n" RESET);
	wrap("'create_dir()' cannot create a directory with the wrong permissions.\n");
	/*
	 * The below test is similar in structure and design to test 2. 
	 * Look at test 2 to understand this test's code.
	 */
	char *dir = malloc(1024);
	strcpy(dir, "");
	if (strcmp(pw->pw_name, "root") != 0) {
		while (true) {
			strcat(dir, "/.test");
			int tmp = create_dir(dir);
			if (errno == EEXIST) {
				continue;
			} else if (tmp == FAILURE) {
				rmdir(dir);
				printf(BOLD_YELLOW "TEST 3: " GREEN "SUCCESSFUL\n" RESET);
				free(dir);
				dir = NULL;
				break;
			} else {
				rmdir(dir);
				printf(BOLD_YELLOW "TEST 3: " RED "FAILED\n" RESET);
				free(dir);
				dir = NULL;
				break;
			}
		}
	} else {
		printf(BOLD_YELLOW "TEST 3: " YELLOW "INCONCLUSIVE\n" RESET);
	}
	print_sep();
	printf(BOLD_YELLOW "TEST 4: " YELLOW "RUNNING\n" RESET);
	wrap("'check_dir()' can report that a missing directory is missing.\n");
	if (check_dir("/path/to/bs/directory") == DIR_MISSING) {
		printf(BOLD_YELLOW "TEST 4: " GREEN "SUCCESSFUL\n" RESET);
	} else {
		printf(BOLD_YELLOW "TEST 4: " RED "FAILED\n" RESET);
	}
	print_sep();
	printf(BOLD_YELLOW "TEST 5: " YELLOW "RUNNING\n" RESET);
	wrap("'check_env_var()' can report that an environment variable doesn't exist.\n");
	int i=0;
	bool j=false;
	do {
		char dummy_var[100];
		char* dummy_ptr;
		sprintf(dummy_var, "DUMMY_VAR_%d", i);
		if (getenv(dummy_var)==NULL) {
			if (check_env_var(&dummy_ptr, dummy_var) == EV_NOT_FOUND) {
				printf(BOLD_YELLOW "TEST 5: " GREEN "SUCCESSFUL\n" RESET);
				j=true;
				break;
			} else {
				printf(BOLD_YELLOW "TEST 5: " RED "FAILED\n" RESET);	
			}
		}
	} while (i<99);
	if (!j) {
		printf(BOLD_YELLOW "TEST 5: " YELLOW "INCONCLUSIVE\n" RESET);
		wrap("(Why are there env vars in the form 'ENV_VAR_NUM', where NUM "
		       "is any number ranging from 0 to 99, defined in your "
		       "environment?)\n");
	}
	print_sep();
	if (check_dir("/this/directory/should/not/sensibly/exist") != DIR_MISSING) {
		wrap("Why does the directory '/this/directory/should/not/sensibly/exist' exist?\n");
	} else {
		printf(BOLD_YELLOW "TEST 6: " YELLOW "RUNNING\n" RESET);
		wrap("'find_data_dir()' should fail if no 'valid' paths are available.\n");
		if (
			setenv("SNEKKIE_FLASHCARDS_DATA",
				"/this/directory/should/not/sensibly/exist", 1)==0 
			&& setenv("XDG_DATA_HOME", 
				"/this/directory/should/not/sensibly/exist", 1)==0
			&& setenv("HOME",
				"/this/directory/should/not/sensibly/exist", 1)==0) {
			char* dummy_path_ptr;
			if (find_data_dir(&dummy_path_ptr) == FAILURE) {
				printf(BOLD_YELLOW "TEST 6: " GREEN "SUCCESSFUL\n" RESET);
			} else {
				printf(BOLD_YELLOW "TEST 6: " RED "FAILED\n" RESET);
			}
		} else {
			printf(BOLD_YELLOW "TEST 6: " RED "INCONCLUSIVE\n" RESET);
			wrap("('setenv()' failed.)\n");
		}
	}
	print_sep();
	return 0;
}
