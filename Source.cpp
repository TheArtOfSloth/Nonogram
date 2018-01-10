#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;

string messedUp;
string selection;
string entries;									//holds user entries for the puzzle

int menuFlag = 0;								//used to specify the user is ready or not to load a file
int gameRunning = 1;

int parseString(string selection){
	if (selection.compare("Exit") || selection.compare("exit")){		//user wishes to leave
		parseExit();
	}
	else if(selection.compare("Help") || selection.compare("help")){	//user wishes to learn how to play
		parseHelp();
	}
	
	else{									//user has specified a filename
		menuFlag++;
	}
	return 0;		
	}
}

void parseHelp()
{
	cout << "Nonograms are picture logic puzzles, where you are given a list of numbers and within the rules of interpreting those numbers, carve out a picture inside a grid." << endl;
	//this is where I would have an example grid
	cout << "Along the topside and along the leftside of the grid are lists of numbers. The lists are the number of filled-in squares (aka black blocks) that reside within that row or column." << endl;
	cout << "Your job is to fill in squares on the grid, such that the number of squares satisfy the number of needed blocks in each row and column simultaneously" << endl;
	//would love to have sample pictures
	cout << "If a row or column is given two or more numbers, the number of blocks will be in groups. A group of blocks specifies the number of adjacent blocks. There will be at least one empty block between each group." << endl;
	cout << "For example, if row three shows that there are '3 2 1' blocks, then somewhere in that row there will be three adjacent black blocks. Then there will be at least one empty white spaces, followed by two more adjacent black blocks, followed by some number of white spaces, then a single black block" << endl;
	//sample picture goes here
	cout << "The puzzle will automatically detect when your puzzle is completed. Have fun!" << endl;
	
	//whew
	cout << "Please specify the file you wish to play, or Exit to exit." << endl;
}

int parseExit()
{
	cout << "Goodbye!" << endl;
	exit();
	return 0;
}

int main()
{
	while(gameRunning == 1){
		cout << "Welcome to our nonogram project!" << endl;
		cout << "If you would like to read the instructions on how to play a nonogram, please type Help." << endl;
		//Tarin here, I'm starting work on our main menu that our user uses to either ask for instructions or load a puzzle
		cout << "If you would like to start a puzzle, please specify the filename of the puzzle you would like to play." << endl;
		//picking a puzzle. Only 1 exists so far.
		cout << "At any time you may type Exit to exit." << endl;
		//allows the user to leave
	
		while (menuFlag == 0){			//we stay in this loop to check what the user's input is
			cin >> selection;		//the user gives us a string and we parse that string for Exit, Help, or a filename
			parseString();
		}
	
		cout << endl << "Okay! Here goes..." << endl;		//we are now ready to attempt to load files
		
		//if(puzzle is solved){
			//cout << "Congratulations! You have completed the puzzle!" << endl;
			//cout << "Would you like to try another?" << endl;
			//here we would ask if the user wants to load another puzzle. For this submission the answer will be no
			//since we're not loading another puzzle yet, exit the loop and program
		gameRunning = 0;
		//}
		
	}
	return 0;
}
