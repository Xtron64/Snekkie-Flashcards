import curses

def clear_screen(stdscr):
    max_y, max_x = stdscr.getmaxyx()
    for y in range(max_y):
        stdscr.move(y, 0)
        stdscr.clrtoeol()  # Clear current line
        if max_x > 0:  # Check if the width is valid
            try:
                stdscr.addstr(y, 0, ' ' * max_x)  # Rewrite blank spaces
            except curses.error:
                pass  # Ignore errors for lines with invalid width
