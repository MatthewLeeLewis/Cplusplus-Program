#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
void DisplayMenu() { //This Function displays a formatted menu of clearly labelled options.

	cout << "------------------------ ENTER A NUMBER FOR ONE OF THE FOLLOWING OPTIONS ---------------------------" << endl; 
	cout << "****************************************************************************************************" << endl; 
	cout << "1. Produce a list of all items purchased in a given day along with the number of times each item was" << endl << "   purchased." << endl << endl;  
	cout << "2. Produce a number representing how many times a specific item was purchased in a given day." << endl << endl; 
	cout << "3. Produce a text-based histogram listing all items purchased in a given day, along with a " << endl << "   representation of the number of times each item was purchased." << endl << endl;  
	cout << "4. Exit application" << endl; 
	cout << "****************************************************************************************************" << endl << endl; 

}
void AnyKey() { //This Function simply outputs "Press Any Key to Continue..." and then runs the necessary code.

	cout << "Press Any Key to Continue..." << endl;
	cin.ignore(); 
	cin.get(); 

}

void Histogram() { //This function is used to generate a histogram from a previously generated ".dat" text file.

	ifstream file; //Creates the input stream for the dat text file.

	//initializes variables to track the currently read item name and amount.
	string itemName; 
	int itemAmount;

	//opens the ".dat" text file into the input stream. 
	file.open("frequency.dat"); 

	//This if statement verifies that it opened correctly and outputs an error if it did not. 
	if (!file.is_open()) {
		cout << "ERROR: Could not open input file." << endl; 
	}

	cout << endl; //This line simply creates more space for readability.

	//Here, the first item name and amount are read into the previously declared variables.
	file >> itemName;
	file >> itemAmount; 

	//Here, it loops until reaching the end of the file, reading each line and outputting data.
	while (!file.fail()) {
		cout << itemName << ": ";
		for (int i = 0; i < itemAmount; i++) { //This nested for loop reads the amount to print a correct amount of asterisks.
			cout << "*";
		}
		cout << endl; 
		file >> itemName;
		file >> itemAmount;
	}

	//Another line for adding blank space to improve formatting and readability.
	cout << endl; 
	file.close(); //Here, the file is properly closed.
}
void ProgramLoop() { //This method controls the main program loop.

	//a user input string variable is declared and calls for the user's input.
	string userInput;
	cin >> userInput;

	//So long as 4 is not entered, this loop will continuously repeat.
	while (userInput != "4") {

		if (userInput == "1") { //Here it checks if the input is 1 and then runs appropriate methods.
			CallProcedure("CountItems");
			cout << endl;
			AnyKey();
			DisplayMenu();
		}

		else if (userInput == "2") { //Here it checks if the input is 2 and then runs appropriate methods.
			cout << "What item do you wish to search for?" << endl;
			cin >> userInput;
			cout << endl << "The total number of " << userInput << " items is " << callIntFunc("SearchItem", userInput) << endl << endl;
			AnyKey();
			DisplayMenu();
		}

		else if (userInput == "3") { //Here it checks if the input is 3 and then runs appropriate methods.
			CallProcedure("DataGenerate");
			Histogram();
			AnyKey();
			DisplayMenu();
		}

		else { //Here it lets the user know that the input is invalid, then runs the appropriate methods to continue the loop.
			cout << "Invalid Input: Please enter 1-4" << endl << endl;
			AnyKey();
			DisplayMenu();
		}

		cin >> userInput; //At the end of all those checks, it calls for input again to properly continue the loop.
	}
}

void main()
{
	//Initializes the Display of the menu.
	DisplayMenu(); 

	//Begins the Core Program Loop
	ProgramLoop();
	
	cout << "**** PROGRAM ENDED ****" << endl; //Lets the user know the program execution has ended.
}