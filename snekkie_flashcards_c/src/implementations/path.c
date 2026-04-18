#include "../headers/shared_typedefs.h"
#include "../headers/path.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>


wrapper_error_t create_dir(const char *dir) {
	/*
	 * Basically a defensive programming wrapper for mkdir to create the directory
	 * 'const char *dir' and checks the return value of mkdir to ensure it didn't
	 * fail.
	 * Returns SUCCESSFUL if mkdir was successful, returns FAILURE if mkdir was 
	 * unsuccessful.
	 */
	errno = 0;
	if (mkdir(dir, 0700) == -1 && errno != EEXIST) {
		return FAILURE;
	} else {
		return SUCCESSFUL;
	}
};


dir_status_t check_dir(const char *dir) {
	/*
	 * Does 3 checks on the parameter 'dir' and returns stateful information.
	 * The 3 checks are (in plain English):
	 * (1) Does 'dir' exist?
	 * (2) Is 'dir' a directory?
	 * (3) Does 'dir' have the right permissions for reading/writing?
	 * Returns DIR_VALID if all 3 checks passed. If an individual check is failed,
	 * it returns:
	 * If (1) failed -> returns DIR_MISSING
	 * If (2) failed -> returns DIR_NOT_A_DIRECTORY
	 * If (3) failed -> returns DIR_NO_READ_WRITE_ACCESS
	 */
	struct stat sb;
	if (stat(dir, &sb) == -1) return DIR_MISSING;
	if (!S_ISDIR(sb.st_mode)) return DIR_NOT_A_DIRECTORY;
	if (access(dir, R_OK | W_OK) != 0) return DIR_NO_READ_WRITE_ACCESS;
	return DIR_VALID;
}


env_var_status_t check_env_var(char **path_var, const char *env_var) {
	/*
	 * Uses getenv to find the value of the given environment variable 'char
	 * *env_var', validates the path it points to, and returns an appropriate
	 * 'env_var_status_t' value to report 1 of 3 options:
	 * (1) -> EV_FOUND_AND_VALID:
	 * The environment variable was found and is 'valid'
	 * (2) -> EV_FOUND_BUT_INVALID:
	 * The environment variable was found but is 'invalid'
	 * (3) -> EV_NOT_FOUND:
	 * The environment variable was not found
	 *
	 * This function mutates 'char **path_var' to store the getenv'd value in the
	 * passed-in variable.
	 */
	char *env_path = getenv(env_var);
	if (env_path != NULL) {
		if (asprintf(path_var, "%s", env_path) == -1) {
			return EV_FOUND_BUT_INVALID;
		} 
		if (check_dir(*path_var) == DIR_VALID) {
			return EV_FOUND_AND_VALID;
		} else {
			return EV_FOUND_BUT_INVALID;
		}
	} else {
		return EV_NOT_FOUND;
	}
};


wrapper_error_t find_data_dir(char **final_path) {
	/*
	 * *final_path is allocated on success and must be freed by the caller. On 
	 * failure, *final_path is already freed but then set to NULL. This actually
	 * makes it safe to free again, as free(NULL) is always safe.
	 * Therefore, always free *final_path (or at least on success).
	 *
	 * Complex orchestrator function for helper functions found in this module.
	 * This function tries to find a 'valid' path in this order of priority:
	 * (1) Try the environment variable 'SNEKKIE_FLASHCARDS_DATA',
	 * (2) Try the environment variable 'XDG_DATA_HOME' and assign path as
	 * '$XDG_DATA_HOME/snekkie-flashcards-data',
	 * (3) Try the environment variable 'HOME' and assign path as
	 * '$HOME/.local/share/snekkie-flashcards-data'.
	 *
	 * All 3 potential ways of finding a path get 'validated'. See 'check_dir'
	 * to understand what 'valid' means and how paths get 'validated'.
	 */
	*final_path = NULL;
	char *xdg = NULL;
	char *home = NULL;
	/*
	 * TRY ENV VAR
	 * If the user wants to control this path, they can modify this env var.
	 * Not a big deal if they don't have it set.
	 */
	switch (check_env_var(final_path, "SNEKKIE_FLASHCARDS_DATA")) {
	case EV_FOUND_AND_VALID:
		// We just have the path the user wants (valid)
		goto returnSuccess;
	case EV_FOUND_BUT_INVALID:
		// If the user wants a custom path, we should respect that.
		// But we literally can't use it.
		// So fail and tell them that.
		goto returnFailure;
	case EV_NOT_FOUND:
		// Not having the env var set is reasonable and doesn't break the code
		break;
	}
	/*
	 * GET XDG (via $XDG_DATA_HOME -> or $HOME/.local/share fallback)
	 * Would be weird for $XDG_DATA_HOME to be unset, but it may be.
	 * If even $HOME is unset, we're screwed.
	 */
	switch (check_env_var(&xdg, "XDG_DATA_HOME")) {
	case EV_FOUND_AND_VALID:
		// Means we just have $XDG_DATA_HOME
		break;
	case EV_FOUND_BUT_INVALID:
		// If the xdg env var is broken, we should respect that the user wants
		// to use something broken. But we literally cannot use it.
		// So, exit with failure.
		goto returnFailure;
	case EV_NOT_FOUND:
		/*
		 * USE $HOME/.local/share AS FALLBACK
		 * In this case, the 'xdg' becomes more like "the path's parent dir".
		 */
		switch (check_env_var(&home, "HOME")) {
		case EV_FOUND_AND_VALID:
			// We have $HOME, so we can use it for the fallback for xdg
			if (asprintf(&xdg, "%s/.local/share", home) == -1) {
				fprintf(stderr,
					"ERROR: asprintf failed to assign "
					"`char *xdg`\n");
				goto returnFailure;
			}
			break;
		default:
			// Not even having $HOME set means we need to fail immediately
			fprintf(stderr, 
				"ERROR: $XDG_DATA_HOME and $HOME both not set.\n");
			goto returnFailure;
		}
	}
	/*
	 * TRY PATH VIA XDG
	 * Since we should have something for $XDG_DATA_HOME or $HOME/.local/share
	 * here, we can let the path be 'xdg'/snekkie-flashcards, then check if it
	 * exists.
	 */
	if (asprintf(final_path, "%s/snekkie-flashcards-data", xdg) == -1) {
		fprintf(stderr,
			"ERROR: asprintf failed to assign `char **final_path`\n");
		goto returnFailure;
	}
	switch (check_dir(*final_path)) {
	case DIR_VALID:
		goto returnSuccess;
	case DIR_NOT_A_DIRECTORY:
		fprintf(stderr, "ERROR: %s is not a directory.\n", *final_path);
		goto returnFailure;
	case DIR_NO_READ_WRITE_ACCESS:
		fprintf(stderr, "ERROR: %s has the wrong permissions.\n", *final_path);
		goto returnFailure;
	case DIR_MISSING:
		break;
	}
	/*
	 * CHECK XDG AND TRY TO WRITE PATH THERE
	 * If we're here, it means we need to create the path. So we should check the
	 * parent dir, xdg.
	 */
	switch (check_dir(xdg)) {
	case DIR_VALID:
		break;
	default:
		goto returnFailure;
	}
	switch (create_dir(*final_path)) {
	case SUCCESSFUL:
		goto returnSuccess;
	case FAILURE:
		fprintf(stderr, "ERROR: Failed to create %s\n", *final_path);
		goto returnFailure;
	}
	// Goto labels
	returnSuccess:
		free(xdg);
		free(home);
		return SUCCESSFUL;
	returnFailure:
		free(xdg);
		free(home);
		free(*final_path);
		*final_path = NULL;
		return FAILURE;
};
