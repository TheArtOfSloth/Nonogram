#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;

string messedUp;
int selection;
int temp1;													//for holding row number for selection and changing
int temp2;													//for holding column number for selection and changing
string buf;													//holds a line of data from the file
string entries;												//holds user entries for the puzzle
ifstream dataFile;											//used to open the file(select a puzzle)

struct puzzle
{
	bool solution[4][4];									//the solution grid. This should only change when first created. Or if a new puzzle starts.
	bool gridState[4][4];									//the player grid. This should hold the data for the current game. A graphical depiction should be built.
	void setSol(int x, int y)								//for setting up the solution
	{
		solution[x-1][y-1] = true;
	};
	void setGrid(int x, int y)							//for changing values to true
	{
		gridState[x-1][y-1] = true;
	};
	void clearGrid(int x, int y)							//for changing values to false
	{
		gridState[x-1][y-1] = false;
	};
	void setItUp()											//sets up a clear starting grid. Needs to create a solution as well.
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				gridState[i][j] = false;					//the line that actually ensures that the player grid starts blank.
		};
	};
	bool isSolved()
	{
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				if(solution[i][j]!=gridState[i][j])
				return false;
			};	
		};
		return true;
	};
	void gameplay(string x)
	{
		//NOT DESIGNED YET. PLEASE FILL IN LATER.
	};

};



int main()
{
	puzzle game;
	cout << "Please select a number between 1 and 1: ";		//picking a puzzle. Only 1 exists so far.
	cin >> selection;										//the int selection of a puzzle
	cout << endl << "Okay! Here goes..." << endl;
	if (selection == 1)										//a placeholder for a better puzzle selection system.
		dataFile.open("samplePuzzle.txt");
	else													//for smart alecs who didn't select 1.
	{
		cout << "no. nonono. It failed. Sorry, eh?" << endl << "press something and then enter to leave. sorry again. ";
		cin >> messedUp;									//prompt so the user can read the above text before the program terminates
		return 0;
	};											
	dataFile.open("samplePuzzle.txt");						//open the file
	
	while(dataFile.good())									//loop to read file and create solution grid
	{
		getline(dataFile, buf);
		temp1=atoi(buf.c_str[0]);
		temp2=atoi(buf.c_str[1]);
		game.setSol(temp1, temp2);
	};
	dataFile.close();										//close the file

	return 0;
}