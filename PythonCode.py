import re
import string

def CountItems(): # This is a python function designed to read each line of input and create a dictionary showing how many of each line was listed.
    
    # First, we create the dictionary.
    groceryList = {}

    # Here, the input file is opened.
    file = open("CS210_Project_Three_Input_File.txt", "r")

    # This for loop processes each line in the file, using a nested if statement to check if it is already in the dictionary, either adding it or updating its amount.
    for line in file:
        output = line.removesuffix('\n')

        if output in groceryList.keys():
            groceryList[output] += 1
        else:
            groceryList[output] = 1
    
    # Here, the file is closed properly.
    file.close()

    # Here, it cycles through each item in the dictionary, printing them in a formatted manner.
    for i in groceryList:
        print(i + ": " + str(groceryList[i]))


def SearchItem(item): # This function is designed to have a string passed to it for it to search the text file for and return a number for how many times it was found.
    
    # The following variable is declared to hold the counted number.
    count = 0;
    
    # Here, the file is opened to be read.
    file = open("CS210_Project_Three_Input_File.txt", "r")

    # This for loop processes each line looking for the entered string. The nested if statement increases the count each time the string is found, regardless of case-sensitivity.
    for line in file:
        trimmedLine = line.removesuffix('\n')

        if trimmedLine.lower() == item.lower():
            count += 1

    # Here, the file is properly closed.
    file.close()

    # The total value of count is then returned.
    return count

def DataGenerate(): # This function reads the text file and creates a .dat text file with each item listed only once alongside a number for how many times it was listed.
    
    # First we create a dictionary to store the values, and string variable for output.
    groceryList = {}
    Output = ""

    # Here, the text file being read is opened.
    inputFile = open("CS210_Project_Three_Input_File.txt", "r")

    # This for loop processes each line in the text file, creating the dictionary the same way as in CountItems()
    for line in inputFile:
        output = line
        output = output.removesuffix('\n')

        if output in groceryList.keys():
            groceryList[output] += 1
        else:
            groceryList[output] = 1
    
    # Here, the file is properly closed.
    inputFile.close()

    # Here, the file being written is opened.
    outputFile = open("frequency.dat", "w")

    # Here, a simple for loop prints the content of the created dictionary into the .dat text file in a clean formatted way.
    for i in groceryList:
        outputFile.write(i + " " + str(groceryList[i]) + "\n")

    # Finally, the .dat output text file is closed properly.
    outputFile.close()

    

    
