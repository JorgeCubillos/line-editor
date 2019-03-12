
	//Jorge Cubillos and Scott Farrow
	//Lauren Antt / Johnnhy Vang
	//Programming Concepts
	//This is an attempt to create a line editor
	//using a giant switch function menu. 

	//It will have the following functions
	//START MENU
	//Open File
	//Move Line
	//Insert Line
	//Type Line
	//Copy Line
	//Delete Line
	//Replace Line
	//Create New File
	//Move Line
	//Insert Line
	//Type Line
	//Copy Line
	//Delete Line
	//Replace Line


	////////////// SOURCE CODE ////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <stdio.h>

	using namespace std;

//Prototype to Open File
vector<string> readFile(string);
void startMenu();
void editMenuLong();
int moveLine(vector<string>, int, int &);
void insertLine(vector<string>&, int, int &, vector<string>);
int typeLine(vector<string>, int, int &);
int replaceLine(vector<string> &, int, int &, vector<string>);
int deleteLine(vector<string> &lines, int selectedLine, int&currentLine);
int locateLine(vector<string> lines, int selectedLIne, int&currentLine);
void substituteLine(vector<string>&lines, int selectedLine, int &currentLine);
void saveLines(string file_name, vector<string> lines);
int copyLine(vector<string> lines, int selectedLine, int &currentLine, vector<string>&temporary);

void help();
void error();
int pasteLine(vector<string> &lines, int selectedLine, int &currentLine, vector<string>&temporary);
//void openFile();

int main()
{
	/////////// DEFINITIONS /////////////////

	///////// OPENING THE FUNCTIONN
	//File Location Defintion

	string fileLocation = "C:\\Users\\jorge.cubillos\\Desktop\\Test.txt";
	//User Document will be stored in vector "userDocument"
	vector<string> userDocument;

	//Line Placeholders 
	int currentLine = 0;			//current line num
	int selectedLine = 0;			//desired line num
	int displayRows = 0;			//displayed row 
	vector<string> temporary;		//temporary values


									//Choice Placeholder (for menu)
	int option;
	cout << "would you like to:" << endl; //Figures out initial opening of document
	cout << "1. Open File\n" << "2. Create New File\n";
	cin >> option;


	switch (option)
	{
	case(1): {
		cout << "File location: ";
		cin >> fileLocation;
		userDocument = readFile(fileLocation);
		break;
	}
	case(2): {
		cout << "Please create a document (.txt) and then type the file location here: ";
		cin >> fileLocation;
		userDocument = readFile(fileLocation);
		break;
	}
	}
	
	//readFile(fileLocation);
	char cmd = 'H';
	cout << "\n\n\nIf you need help at any time press H to see a list of functions.\n"; //just a reminder (only happens when document is first opened)


	while (cmd != 'Q') { //THIS IS FOR RUNNING A LOOP TO TAKE IN COMMANDS FOR EDITING DOCUMENT
		char cmd;
		cout << "\nCMD: ";
		cin >> cmd;
		cmd = toupper(cmd);
		switch (cmd)   //x is for the letter input the user chooses
		{
		case 'O':		//Open file function
		{
			readFile(fileLocation);//openFile();
		}
		break;
		case 'M':		//Move
		{
			moveLine(userDocument, selectedLine, currentLine);
		}
		break;
		case 'I':		//Insert
		{
			insertLine(userDocument, selectedLine, currentLine, temporary); //GETLINE
		}
		break;
		case 'T':		//Type
		{
			typeLine(userDocument, selectedLine, currentLine); //GETLINE
		}
		break;
		case 'C':		//Copy
		{
			copyLine(userDocument, selectedLine, currentLine, temporary);
		}
		break;
		case 'D':		//Delete
		{
			deleteLine(userDocument, selectedLine, currentLine); //ALLOW USER TO CHANGE CURRENT LINE BEFORE DELETING
		}
		break;
		case 'R':		//Replace
		{
			replaceLine(userDocument, selectedLine, currentLine, temporary);
		}
		break;
		case 'X':
		{
			substituteLine(userDocument, selectedLine, currentLine);
		}
		break;
		case 'S':		//SAVE
		{
			saveLines(fileLocation, userDocument);
		}
		break;
		case 'Q':		//Quit
		{
			char x;
			cout << "Would you like to save? (Y or N): ";
			cin >> x;

			switch (x)
			{
			case('Y'):
			{
				saveLines(fileLocation, userDocument);
			}
			case('y'):
			{
				saveLines(fileLocation, userDocument);
			}
			default:
			{
				cout << "Thank you, Goodbye.";
			}
			}
		}
		break;
		case 'H':		//Help
		{
			help();
		}
		break;
		case 'L': //LOCATE
		{
			locateLine(userDocument, selectedLine, currentLine);
		}
		break;
		case 'P':		//paste
		{
			pasteLine(userDocument, selectedLine, currentLine, temporary);
		}
		default:
		{
			error();

		}
		}
	};

	return 0;
}




//Function Defintion to Open File
vector<string> readFile(string file)
{

	char input[1000]; //sizing

	vector<string> lines; //vector that holds text in openFile

	ifstream document(file); //reads in file to lines

	if (document.fail()) //if file does not open, try again option
	{
		cout << "File opening failed.";
		string fileLocation;
		int option;
		cout << "would you like to:" << endl; //Figures out initial opening of document
		cout << "1. Open File\n" << "2. Create New File\n";
		cin >> option;
		switch (option)
		{
		case(1): {
			cout << "File location: ";
			cin >> file;
			break;
		}
		case(2): {
			cout << "Desired file name or location: ";
			cin >> file;
			break;
		}
		}
		ifstream document(file);

		while (!document.eof())
		{
			document.getline(input, sizeof(input));
			lines.push_back(input);
		}

		for (int count = 0; count < lines.size(); count++) //prints out document with line numbers
		{
			int n = count + 1;
			cout << n << " " << lines[count] << endl;
		}

		return lines;
	}

	while (!document.eof())
	{
		document.getline(input, sizeof(input));
		lines.push_back(input);
	}

	for (int count = 0; count < lines.size(); count++) //prints out document with line numbers
	{
		int n = count + 1;
		cout << n << " " << lines[count] << endl;
	}

	return lines; //returns content
}


void startMenu() //store the text for the menue text
{
	char ch;
	cout << "Welcome. This program allows you to create or edit a text file. Press enter to continue." << endl;
	cin.get(ch);
	cout << "Please enter a number to select." << endl;
	cout << "1. Open File" << endl;
	cout << "2. Create New File" << endl;
	cout << "3. Quit" << endl;
}

//This is the edit menu. It will display the different editing options. It is the long version.
/*void editMenuLong()
{
	char ch;
	cout << endl;
	cout << "This is the edit menu. Press enter to view the options and select the desired function." << endl;
	cin.get(ch);
	cout << "Please enter a letter to select." << endl;
	cout << "1. Insert Function." << endl;
	cout << "2. Type Function." << endl;
	cout << "3. Move Funciton." << endl;
	cout << "4. Replace Function." << endl;
	cout << "5. Delete Function." << endl;
	cout << "6. Locate funciton." << endl;
	cout << "7. Substitute Funciton." << endl;
	cout << "8. Copy Function." << endl;
	cout << "9. Paste Function." << endl;
	cout << "10. Quit" << endl;
	cout << "99. SHOW MENU/HELP" << endl;
}*/

//Thi is the edit menu. This is for quick acess in every menu. 
/*void editMenuShort()
{
	cout << "A. Insert Function." << endl;
	cout << "B. Type Function." << endl;
	cout << "C. Move Funciton." << endl;
	cout << "D. Replace Function." << endl;
	cout << "E. Delete Function." << endl;
	cout << "F. Locate funciton." << endl;
	cout << "G. Substitute Funciton." << endl;
	cout << "I. Copy Function." << endl;
	cout << "J. Paste Function." << endl;
	cout << "K. Quit" << endl;
	cout << "H. SHOW MENU/HELP" << endl;
}*/

//This is the move line function. Enter a line number and it takes you there and diplays the rest
int moveLine(vector<string> lines, int selectedLine, int &currentLine)
{
	cout << "Move Function Selected" << endl;
	cout << "Enter a line number ";
	cin >> selectedLine;

	currentLine = selectedLine;

	for (int i = selectedLine; i < lines.size(); i++)
	{
		int n = i;
		cout << n << " " << lines[i] << " \n";
	}

	return 0;
}

//This is the insert line function. Enter amount of lines, starting point, and new text and it will add it to the total file. 
void insertLine(vector<string> &lines, int selectedLine, int &currentLine, vector<string> temporary)
{

	int size = 1;

	cout << "Insert Function Selected" << endl;
	cout << "How many lines of text would you like to insert?" << endl;
	cin >> size;
	cout << endl;
	cout << "Which line would you like to insert new text?" << endl;
	cin >> selectedLine;
	cout << endl;


	
	//Get new lines and store in temporary


	for (int i = 0; i < 1; i++) {
		cin.ignore();
		cout << "Enter line:";
		//C:\\Users\\jorge.cubillos\\Desktop\\Test.txt
		string text;
		//cin.ignore();
		getline(cin, text);
		temporary.push_back(text);
	};
	for (int count = 1; count < size; count++)
	{
		cout << "Enter line:";

		string text;
		getline(cin, text);
		temporary.push_back(text);
	}

	//Combine 

	std::vector<string>::iterator it;
	it = lines.begin();

	lines.insert(it + selectedLine, temporary.begin(), temporary.end());


	//This then will display the NEW FILE AYYYY FAM

	for (int count = 0; count < lines.size(); count++)
	{
		int n = count;
		cout << n << " " << lines[count] << endl;
	}

	currentLine = selectedLine + size;

}

//This is the type line function. Print the contents of the next # lines, including the current one. 
int typeLine(vector<string> lines, int selectedLine, int &currentLine)
{
	int size = 0;

	cout << "Type Function Selected" << endl;
	cout << "Enter a line number ";
	cin >> selectedLine;
	cout << endl;
	cout << "Enter how many lines you want to diplay." << endl;
	cin >> size;
	currentLine = selectedLine;

	for (int i = selectedLine; i < selectedLine + size; i++)
	{
		int n = i;
		cout << n << " " << lines[i] << " \n";
	}

	return 0;
}

//This is the replace line function. It replaces a selected amount of lines, starting with a selected line. 
//After, it replaces it with a new set of lines. Sounds like a mix of MOVE, TYPE, AND INSERT, AND DELETE.
int replaceLine(vector<string> &lines, int selectedLine, int &currentLine, vector<string>temporary)
{

	int size = 0;
	//Get parameters
	cout << "Replace Function Selected" << endl;
	cout << "Enter a line number ";
	cin >> selectedLine;
	cout << endl;
	cout << "Enter how many lines you want to replace." << endl;
	cin >> size;

	//Get new replacement text
	for (int i = 0; i < 1; i++) {
		cin.ignore();
		cout << "Enter line:";
		//C:\\Users\\jorge.cubillos\\Desktop\\Test.txt
		string text;
		//cin.ignore();
		getline(cin, text);
		temporary.push_back(text);
	};
	for (int count = 1; count < size; count++)
	{
		cout << "Enter line:";

		string text;
		getline(cin, text);
		temporary.push_back(text);
	}


	cout << endl;
	//Insert replacement text

	std::vector<string>::iterator it;
	it = lines.begin();

	lines.insert(it + selectedLine, temporary.begin(), temporary.end());

	//Erase Old text

	lines.erase(lines.begin() + (selectedLine + size), lines.begin() + ((selectedLine + size) + size));

	//Display everything after modifications C:\\users\\jorge.cubillos\\desktop\\test.txt
	for (int count = 0; count <lines.size(); count++)
	{
		int n = count;
		cout << n << " " << lines[count] << endl;
	}


	currentLine = selectedLine + size;


	return 0;
}

//This is the delete line funciton. I would use it in conjunction with the move function and THEN use the delete function to delete the newly found line. 
int deleteLine(vector<string> &lines, int selectedLine, int&currentLine)
{
	int size = 0;
	cout << "Delete Function selected." << endl;
	cout << "You are about to delete a number of lines, including the line number you are currently on.\nPlease enter the number of lines you would like to delete.\n";
	cin >> size;
	cout << endl;

	//Delete Lines
	lines.erase(lines.begin() + (currentLine), lines.begin() + (currentLine + size));

	//Show Entire file
	for (int count = 0; count < lines.size(); count++)
	{
		int n = count + 1;
		cout << n << " " << lines[count] << endl;
	}

	//New current line after number of lines deleted
	currentLine = currentLine + size;

	return 0;
}

//This is the locate line function. It will locate the file for a specific string, and then search and state line number, else, nothing. 
int locateLine(vector<string> lines, int selectedLIne, int&currentLine)
{
	//Directions
	cout << "Locate function selected." << endl;
	cout << "The function will search for a desired string of text." << endl;

	//Get text sample
	string text;
	cout << "Enter line of text." << endl;
	cin >> text;

	//Search file for text

	int count = 0;
	do {
		std::vector<string>::iterator it;
		it = std::find(lines.begin(), lines.begin() + count, text);
		if (it != (lines.begin() + count))
		{
			cout << "Match found at line number " << count << endl;
			count++;
			it = lines.begin();
		}
		else
			count++;
	} while (count != lines.size());

	return 0;
}

void substituteLine(vector<string>&lines, int selectedLine, int &currentLine)
{
	//These are the new substittue variables
	int pos = 0;
	string oldstr = "";
	string newstr = "";
	cout << "Substitute Function Selected";
	cin.ignore(100, '\n');
	cout << "Type the word or phrase you would like to substitute in the current line: ";
	getline(cin, oldstr);

	//Checks
	int flag = lines[currentLine].find(oldstr, 0);
	cin.ignore(100, '\n');
	if (flag == -1)
		cout << "ERROR STRING DOES NOT EXIST. ";
	else
	{
		cout << endl;
		cout << "Type the new word or phrase you would like to substitute in the line: ";
		getline(cin, newstr);
		while (pos != -1)
		{
			pos = lines[currentLine].find(oldstr, 0);
			if (pos != -1)
				lines[currentLine].replace(pos, oldstr.size(), newstr);
		}
		cout << (currentLine + 1) << ". " << lines[currentLine];
	}
}


//This is the Copy Function.
int copyLine(vector<string> lines, int selectedLine, int &currentLine, vector<string>&temporary)
{

	//Get parameters
	cout << "Copy Function Selected" << endl;
	cout << "Enter a line number to copy.";
	cin >> selectedLine;
	cout << endl;


	//Copy to temporary location
	temporary.push_back(lines[selectedLine - 1]);
	cout << endl;

	cout << "Copy created." << endl;

	//Display everything after modifications
	/*for (int count = 0; count <temporary.size(); count++)
	{
	cout << temporary[count] << endl;
	}
	*/
	currentLine = lines.size();

	return 0;
}

//This is the Paste Function. Use after Copy Function
int pasteLine(vector<string> &lines, int selectedLine, int &currentLine, vector<string>&temporary)
{
	cout << "Paste Function Selected:" << endl;



	//Insert Temporary
	std::vector<string>::iterator it;
	it = lines.begin();

	lines.insert(it + currentLine, temporary.begin(), temporary.end());

	//This then will display the NEW FILE AYYYY FAM

	for (int count = 0; count < lines.size(); count++)
	{
		int n = count + 1;
		cout << n << " " << lines[count] << endl;
	}

	//Selected Line is now temprary
	currentLine = currentLine + 1;

	return 0;
}

void saveLines(string file_name, vector<string> lines)
{
	string docName;
	cout << "Where would you like to save this document: ";
	cin >> docName;

	ofstream outDoc(docName);
	for (int count = 0; count != lines.size(); count++)
	{
		outDoc << lines[count] << endl;
	}
	outDoc.close();
}
void help()
{
	cout << "This is the help menu. Please enter the letter for a function below to begin.\n";
	cout << "Function:" << setw(10) << "Use this letter to call:" << setw(10) << "Description: \n";
	cout << "Open file" << setw(15) << "O" << setw(5) << "Open a file or create a new one.\n";
	cout << "Move" << setw(15) << "M" << setw(5) << "Locate and print a number of lines past the current.\n";
	cout << "Insert" << setw(15) << "I" << setw(5) << "Insert a number of lines into the file following the current line.\n";
	cout << "Type" << setw(15) << "T" << setw(5) << "Print contents of a number of lines, including the last typed.\n";
	cout << "Copy" << setw(15) << "C" << setw(5) << "Copy a number of lines, including the current.\n";
	cout << "Delete" << setw(15) << "D" << setw(5) << "Deletes a number of lines, including the current.\n";
	cout << "Replace" << setw(15) << "R" << setw(5) << "Replaces a number of lines, beginning at the current line, with a different number of lines.\n";
	cout << "Paste" << setw(15) << "P" << setw(5) << "Pastes copied content to a position between current line and the next.\n";
	cout << "Substitute" << setw(15) << "S" << setw(5) << "Substitutes a new string of words for an old string of words at\n" << setw(25) << "every occurence of the old string.\n";
	cout << "Quit" << setw(15) << "Q" << setw(5) << "Saves the file and quits the editor.\n";
	cout << "Help" << setw(15) << "H" << setw(5) << "Displays the help menu.\n";

	char x;
	cin >> x;
}
void error()
{
	cout << "There was an error, please try again\n";
}
