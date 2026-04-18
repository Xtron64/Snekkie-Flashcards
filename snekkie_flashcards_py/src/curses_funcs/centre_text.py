import curses

def centre_text(stdscr, text: str, color_pair=None):
    max_y, max_x = stdscr.getmaxyx()
    lines = text.split('\n')
    num_lines = len(lines)
    start_y = max_y // 2 - num_lines // 2
    max_length = max(len(line) for line in lines)

    for i, line in enumerate(lines):
        y = start_y + i
        x = max_x // 2 - max_length // 2
        if color_pair:
            stdscr.addstr(y, x, line.center(max_length), curses.color_pair(color_pair) | curses.A_BOLD)
        else:
            stdscr.addstr(y, x, line.center(max_length))
