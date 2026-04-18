import curses

def get_key_index(key_name, color_dict):
    """
    Get the index of a color key from a dictionary.
    
    Parameters:
        key_name (str): The name of the color key.
        color_dict (dict): The dictionary containing color keys and their indexes.
    
    Returns:
        int: The index of the color key, or -1 if not found.
    """
    for index, name in color_dict.items():
        if name == key_name:
            return index
    return -1  # Return -1 if key not found


def init_curses():
    # Define color pairs based on Alacritty color configuration
    # You may need to adjust these colors to match your preferences

    # Define custom colors with alpha transparency
    TRANSPARENT_COLOR = -1  # Use default background color with alpha

    # Alacritty color configuration
    alacritty_colors = {
        "foreground": "#CDD6F4",
        "background": "#1E1E2E",
        "cursor": "#F5E0DC",
        "selection_bg": "#F5E0DC",
        # Add more colors as needed...
    }

    # Initialize curses colors
    curses.start_color()
    curses.use_default_colors()

    # Define custom colors
    for key, color_name in alacritty_colors.items():
        r, g, b = int(color_name[1:3], 16), int(color_name[3:5], 16), int(color_name[5:], 16)
        key_index = get_key_index(key, alacritty_colors)  # Get the index for the color key
        if key_index != -1:
            curses.init_color(key_index, r, g, b)  # Initialize the color with the retrieved index

    # Define color pairs
    # Define more color pairs as needed...
    
    # Initialize color pairs
    curses.start_color()
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
    # Define more color pairs as needed

