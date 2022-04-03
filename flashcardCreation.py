import json

yes = \
    (
            "yes" or "Y"
    )

no = \
    (
            "no" or "n"
    )

yes_no = \
    (
            yes or no
    )
accepted_fonts = ("Georgia" or "Times New Roman" or "Calibri")


# Front-text


def flashcardCreation():
    # Front-Text
    while True:
        print("What would you like the front to say?")
        front_text = input("You: ")
        print("Are you sure?")
        front_text_confirmation = input("You: ")
        if front_text_confirmation.lower() != yes.lower():
            continue
        else:
            break
    # Back-text
    while True:
        print("What would you like the back to say?")
        back_text = input("You: ")
        print("Are you sure?")
        back_text_confirmation = input("You: ")
        if back_text_confirmation.lower() != yes.lower():
            continue
        else:
            break
    return front_text, back_text


out = {}
while True:
    front_text, back_text = flashcardCreation()
    with open('flashcard.json', 'w') as f:
        json.dump(out, f, indent=2)
