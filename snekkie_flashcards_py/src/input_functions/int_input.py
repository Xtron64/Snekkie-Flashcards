import curses
from curses_funcs import clear_screen

def int_input(stdscr, prompt: str = "Enter an integer: ") -> int:
    curses.curs_set(0)  # Hide cursor
    clear_screen(stdscr)
    while True:
        stdscr.clear()  # Clear the screen

        # Center the prompt
        max_y, max_x = stdscr.getmaxyx()
        start_x = max_x // 2 - len(prompt) // 2
        start_y = max_y // 2
        stdscr.addstr(start_y, start_x, prompt)

        # Initialize input string
        input_str = ""

        while True:
            # Display input string
            stdscr.addstr(start_y + 1, start_x, input_str.encode('utf-8'))

            # Display '>' symbol
            stdscr.addstr(start_y + 1, start_x - 2, "> ", curses.A_BOLD)

            # Get user input
            key = stdscr.getch()

            if key == curses.KEY_ENTER or key in [10, 13]:
                try:
                    return int(input_str)
                except ValueError:
                    # Invalid input, display error message
                    error_message = "Invalid input. Please enter an integer."
                    error_start_x = max_x // 2 - len(error_message) // 2
                    stdscr.addstr(start_y + 2, error_start_x, error_message, curses.A_BOLD)
                    stdscr.refresh()
                    input_str = ""  # Reset input string
            elif key == curses.KEY_BACKSPACE or key == 127:
                # Handle backspace
                if input_str:
                    input_str = input_str[:-1]  # Delete the last character
            elif chr(key).isdigit():
                # Handle digit input
                input_str += chr(key)  # Add digit to input string
    clear_screen()

