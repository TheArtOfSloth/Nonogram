#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
#include"puzzle.h"
#include"game.h"
using namespace std;

string messedUp;
string selection;
string entries;									//holds user entries for the puzzle

int menuFlag = 0;								//used to specify the user is ready or not to load a file
int gameRunning = 1;

int newCoordX = 0; int newCoordY = 0;						//used to store user input for 'entries'

puzzle playPuzzle;
game playGame;

void printPuzzle(puzzle playPuzzle, game playGame){
	//this function will print out the nonogram in ASCII to cout
	
	int numRows = playPuzzle.getRows();
	int numColumns = playPuzzle.getColumns();
	int biggestRow = 1; int biggestColumn = 1;
	int** thisRowKey = playPuzzle.getRowKey();
	int** thisColumnKey = playPuzzle.getColumnKey();
	bool** printBoard = playGame.getBoard();
	
	for(int itorX = 0; itorX < playPuzzle.getColumns(); itorX++){
		//i need to find out which column has the most number of hints. Variable initialized to 1 for one hint
		int tempBiggest = 1;
		while(thisColumnKey[itorX].hasNext()){
			tempBiggest++;
		}
		if(tempBiggest > biggestColumn) biggestColumn = tempBiggest;
	}
	for(int itorY = 0; itorY < playPuzzle.getRows(); itorY++){
		int tempBiggest = 1;
		while(thisRowKey[itorY].hasNext()){
			tempBiggest++;
		}
		if(tempBiggest > biggestRow) biggestRow = tempBiggest;
	}
	
	for (i < playPuzzle.getColumns() + biggestColumn){
  		for (j < playPuzzle.getRows() + biggestRow){
			//I am now goign to determine what we print based on where we are
    			if (i < biggestColumn && j < biggestRow) cout << " ";				//we're still in the corner
    			if (i < biggestColumn && j > biggestRow){					//we're in in the column hints
				if (thisColumnKey[j-biggestRow][i] != NULL) cout << thisColumnKey[j-biggestRow][i];
				else cout << " ";
			}
    			if (i > biggestColumn && j < biggestRow){					//we're in the row hints
				if(thisRowKey[i-biggestColumn][j] != NULL) cout << thisRowKey[i-biggestColumn][j];
				else cout << " ";
			}
    			if (i > biggestColumn && j > biggestRow){					//we're in the grid playfield
      				if (printBoard[j-biggestRow][i-biggestColumn] == TRUE) cout << "X";
      				else cout << " ";
    			}
			cout << endl;
		}
  	}
	cout << "Please type the co-ordinates of the box you would like to fill (or erase)" << endl;
}

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

int* parseCoOrds(game playGame, int newX, newY){
	playGame.move(newX, newY);
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
		
		menuFlag = 0;
		while (menuFlag == 0){			//we stay in this loop to check what the user's input is
			cin >> selection;		//the user gives us a string and we parse that string for Exit, Help, or a filename
			parseString();
		}
	
		cout << endl << "Okay! Here goes..." << endl;		//we are now ready to attempt to load files
		
		//here goes code for actually looping and running the game
		//load up the puzzle file here
		//if and only if the puzzle loads properly, run this statement:
		Puzzle* playPuzzle = new Puzzle(selection);
		Game* playGame = new Game(playPuzzle);
		//assert the puzzle loaded and playPuzzle and playGame were initialized
		
		//then set this variable
		puzzleLoaded = 1;
		
		//load a game class here, to actually start running the game
		
		while(puzzleLoaded == 1){	//this loop will be something that checks after every move
			//print the puzzle
			printPuzzle(playPuzzle, playGame);
			
			//add a call to a function that polls the user for their input. Return here
			cout << "Please enter a row." << endl;
			cin >> newCoordX;
			cout << "Please enter a column." << endl;
			cin >> newCoordY;
			newCoOrds = parseCoOrds(playGame, newCoordX, newCoordY);
			
			//check if the puzzle is solved
			if(playGame.isWin()) isSolved == TRUE;
			if(isSolved == TRUE){
				cout << "Congratulations! You have completed the puzzle!" << endl;
				//cout << "Would you like to try another?" << endl;
				//here we would ask if the user wants to load another puzzle. For this submission the answer will be no
				//since we're not loading another puzzle yet, exit the loop and program
				gameRunning = 0;
				//regardless, we now end the puzzleLoaded loop
				puzzleLoaded = 0;
			}
		}
	}
	return 0;
} 
