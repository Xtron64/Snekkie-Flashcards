# Constants
yes = "yes"
no = "no"
yes_no = ("yes" or "no")
revise = "revise"
# 'revise' is meant to be the command to revise a flashcard bundle, it should ask the user which one to revise,
# which the user should reply with the name of the flashcard bundle
about = "about"
# 'About' is the command that shows you the README.md
create_flashcard = ("create" or "create flashcard" or "flashcard creation")
# 'create' is meant to redirect you 'flashcardCreation.py', which lets you create flashcards
show_bundle_names = ("bundles" or "show bundles" or "show bundle names")
# 'show_names' is meant to print the names of all flashcards bundles from a repository of flashcards bundles
commands_doc = ("list" or "commands")
# 'list' is meant to redirect you to 'commands.txt', which shows the user what each command does
leave = ("exit" or "app exit" or "leave" or "leave app" or "exit app" or "application exit" or "exit application" or "leave application" or "leave software" or "exit software" or "close software")
commands_list = (create_flashcard or show_bundle_names or commands_doc or about or leave or revise)


# Commands_list is a list of commands


def main():
    print(
        """What would you like to do? enter "commands" for a full list of commands,
         and make sure to enter all your commands in lowercase""")
    var = choice = input("You: ")
    if choice.lower() == commands_doc.lower():
        f = open('commands.md', 'r')
        f.read()
    if choice.lower() == create_flashcard.lower():
        import flashcardCreation
    if choice.lower() == revise.lower():
        import flashcardRevision
    if choice.lower() == about.lower():
        f = open('README.md', 'r')
        f.read()
    if choice.lower() == leave.lower():
        exit()
    if choice.lower() != commands_list.lower():
        print(
            "Please enter your desired command again, and make sure it's the correct command,"
            " also make sure it's lowercase."
        )
    main()


if __name__ == '__main__':
    main()
