import curses
from curses_funcs import *


def show_helpme(stdscr=None) -> None:
    if not stdscr:
        init_curses()

    with open("show_helpme/helpme.txt", "r") as h:
        help_me = h.readlines()

    max_y, max_x = stdscr.getmaxyx()

    # Determine the total number of lines and the number of visible lines
    total_lines = len(help_me)
    visible_lines = min(max_y, total_lines)

    # Display the first portion of the text
    for i in range(visible_lines):
        stdscr.addstr(i, 0, help_me[i].rstrip('\n'))

    # Refresh the screen
    stdscr.refresh()

    # Scroll functionality
    top_line = 0
    while True:
        key = stdscr.getch()

        if key == curses.KEY_ENTER or key in [10, 13]:
            break
        elif key == curses.KEY_DOWN and top_line < total_lines - visible_lines:
            # Scroll down
            top_line += 1
            stdscr.clear()
            for i in range(visible_lines):
                stdscr.addstr(i, 0, help_me[top_line + i].rstrip('\n'))
            stdscr.refresh()
        elif key == curses.KEY_UP and top_line > 0:
            # Scroll up
            top_line -= 1
            stdscr.clear()
            for i in range(visible_lines):
                stdscr.addstr(i, 0, help_me[top_line + i].rstrip('\n'))
            stdscr.refresh()

    # End curses mode
    curses.endwin()


# Example usage:
# curses.wrapper(show_helpme)

