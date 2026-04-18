import curses
from input_functions import *
from curses_funcs import *
from create_flashcards import *
from revise_flashcards import *
from show_helpme import *

# Define exit codes:
SUCCESS = 0
CONTINUE = -1
CODE_INTERRUPTED = -2


def main(stdscr):
    try:
        # Init curses env
        init_curses()
        stdscr.clear()
        choices = ["Create flashcards", "Revise flashcards", "Read HELPME.txt file", "Leave"]
        selected_option = multi_choice_input(stdscr, choices, q_str = "Welcome to Snekkie Flashcards!\nWhat would you like to do?")
        stdscr.clear()
        if selected_option == "Create flashcards":
            create_flashcards(stdscr)
        elif selected_option == "Revise flashcards":
            revise_flashcards(stdscr)
        elif selected_option == "Read HELPME.txt file":
            show_helpme(stdscr)
        elif selected_option == "Leave":
            return SUCCESS
        stdscr.refresh()
        stdscr.getch()  # Wait for user input before clearing the screen
    except KeyboardInterrupt:
        return CODE_INTERRUPTED
    else:
       return CONTINUE


while __name__ == "__main__":
    code: int = curses.wrapper(main)
    if code == SUCCESS:
        break
    elif code == CONTINUE:
        continue
    elif code == CODE_INTERRUPTED:
        break
    else:
        raise Exception("No exit code.")

