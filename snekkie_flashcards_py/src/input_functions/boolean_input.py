'''
--- 'boolean_input()' documentation: ---
'''

def boolean_input(string: str = "You: ") -> bool:
    yes_inputs: list = ["yes", "y", "1", "true"]
    no_inputs: list = ["no", "n", "0", "false"]
    while True:
        user_input: str = input(string).lower()
        if user_input in yes_inputs:
            return True
        elif user_input in no_inputs:
            return False
        else:
            Print("Invalid input. Please try again.")
            continue

