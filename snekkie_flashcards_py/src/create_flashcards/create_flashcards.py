from input_functions import *

def create_flashcards(stdscr) -> None:
    # Get info about amount of flashcards and bundles
    ind_or_mul = multi_choice_input(stdscr, ["Individual", "Multiple"], "Would you like to create an individual flashcard or multiple?")

    if ind_or_mul == "Individual":
        own_or_bun = multi_choice_input(stdscr, ["On its own", "In a bundle"], "Would you like to have the flashcard on its own or add to bundle?")
        if own_or_bun == "In a bundle":
            new_or_existing = multi_choice_input(stdscr, ["New bundle", "Existing bundle"], "Would you like to add it to a new bundle or an existing bundle?")

    if ind_or_mul == "Multiple":
        amount = int_input(stdscr, "How many flashcards?")
        own_or_bun = multi_choice_input(stdscr, ["On their own", "In a bundle"], "Would you like to have the flashcards on their owjn or add them to a bundle?")
        if own_or_bun == "In a bundle":
            new_or_existing = multi_choice_input(stdscr, ["New bundle", "Existing bundle"], "Would you like to add them to anew bundle or an existing bundle?")
    # Get info about the flashcard(s)
