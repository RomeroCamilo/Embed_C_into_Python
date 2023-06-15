from cgetSum import cSum

# Create a list of numbers #
numbers = []

while True:
        try: # Attempting to add value into numbers list. #
            user_input = input("Enter a float number (or 'q' to quit): ")
            if user_input.lower() == 'q':
                break
            number = float(user_input) # convert user input value into a float. if user input a letter, expect ValueError will be raised. #
            numbers.append(number)
        except ValueError: # If the user input an invalid value such as a letter. #
            print("Invalid input. Please enter a valid float number or 'q' to quit.")


# Calling cSum function #
result = cSum(numbers)

print('Sum:',result)

