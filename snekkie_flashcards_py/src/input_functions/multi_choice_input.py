import curses
from curses_funcs.clear_screen import clear_screen
from curses_funcs.centre_text import centre_text

def multi_choice_input(stdscr, choices: list = [], q_str: str = "Pick an option: ") -> str:
    curses.curs_set(0)  # Hide cursor
    clear_screen(stdscr)  # Clear the screen

    # Center the question string
    centre_text(stdscr, q_str)

    # Calculate starting position for the choices
    max_y, max_x = stdscr.getmaxyx()
    start_y_choices = max_y // 2 + 1

    # Find the maximum length of the choice lines
    max_length = max(len(choice) for choice in choices)

    # Set the starting position for the choices
    start_x_choices = max_x // 2 - max_length // 2

    # Set initial selected index
    selected_index = 0

    # Input loop
    while True:
        # Print the choices
        for i, c in enumerate(choices):
            choice_line = f"{c}"
            stdscr.addstr(start_y_choices + i, start_x_choices, choice_line)

        # Print the cursor at the selected choice
        stdscr.move(start_y_choices + selected_index, start_x_choices - 4)  # Adjusted for spacing
        stdscr.addstr("~> ")

        # Get user input
        key = stdscr.getch()

        # Clear the area where the cursor was previously located
        stdscr.move(start_y_choices + selected_index, start_x_choices - 4)
        stdscr.addstr("    ")  # Clear the previous indicator

        # Handle arrow key input
        if key == curses.KEY_UP:
            selected_index = max(0, selected_index - 1)
        elif key == curses.KEY_DOWN:
            selected_index = min(len(choices) - 1, selected_index + 1)
        elif key == ord('\n'):
            return choices[selected_index]  # Return the selected choice

# Example usage:
# def main(stdscr):
#     curses.curs_set(0)  # Hide cursor
#     options = ["Option 1", "Option 2", "Option 3"]
#     selected_option = multi_choice_input(stdscr, options, q_str="Choose an option:")
#     stdscr.addstr(f"You selected: {selected_option}")
#     stdscr.refresh()
#     stdscr.getch()  # Wait for a key press
#
# curses.wrapper(main)

