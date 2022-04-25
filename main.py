# Constants.
# We need these.

yes = "yes"
no = "no"
revise = "revise"
about = "about"
create_flashcard = "create"
show_bundle_names = "bundles"
commands_doc = ("list" or "commands")
leave = ("exit" or "leave")
commands_list = (create_flashcard or show_bundle_names or commands_doc or about or leave or revise)


# This function gets the users input.
def userInput():
    _ = input("You: ")
    return _


# This is where all the real code is.
def main():
    global yes, no, revise, about, create_flashcard, show_bundle_names, commands_doc, leave, commands_list
    while True:
        print(
            """What would you like to do? enter "commands" for a full list of commands,
             and make sure to enter all your commands in lowercase""")
        usersChoice = userInput()
        choice = usersChoice.lower()
        for commands_doc in choice:
            f = open('commands.md', 'r')
            f.read()
        for create_flashcard in choice:
            import flashcardCreation
        for revise in choice:
            import flashcardRevision
        for about in choice:
            with open('README.md', 'r') as f:
                f.read()
                f.close()
        for leave in choice:
            exit()
        if choice != commands_list:
            print(
                "Please enter your desired command again, and make sure it's the correct command,"
                " also make sure it's lowercase."
            )


if __name__ == '__main__':
    main()
