#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;

string messedUp;
string selection;
int temp1;														//for holding row number for selection and changing
int temp2;														//for holding column number for selection and changing
string buf;														//holds a line of data from the file
string entries;													//holds user entries for the puzzle
ifstream dataFile;												//used to open the file(select a puzzle)


class puzzle()
{
	ifstream dataFil;											//for opening a file
	string buff;												//for reading the file
	int temp3;													//for input into setSol
	int temp4;													//for input into setSol
	bool solution[4][4];										//solution grid
	void clearSol()												//for clearing the solution before setting it up
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				solution[i][j]=false;
			};
		};
	};
	void setSol(int x, int y)									//for setting up the solution
	{
		solution[x-1][y-1] = true;
	};
	puzzle(string w)
	{
		clearSol();
		dataFil.open(w);										//open the file
		while(dataFil.good())									//loop to read file and create solution grid
		{
			getline(dataFil, buff);
			temp3=atoi(buff.c_str[0]);
			temp4=atoi(buff.c_str[1]);
			setSol(temp3, temp4);
		};
		dataFil.close();										//close the file
	};

};

class game()
{
private:
	bool gridStat[4][4];
public:
	game()
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				gridStat[i][j]=false;
			};
		};
	};
	void changeSpace(int x, int y)
	{
		if(gridStat[x-1][y-1]==true)
			gridStat[x-1][y-1]=false;
		else
			gridStat[x-1][y-1]=true;
	};
};

struct puzzl
{
	bool solution[4][4];									//the solution grid. This should only change when first created. Or if a new puzzle starts.
	bool gridState[4][4];									//the player grid. This should hold the data for the current game. A graphical depiction should be built.
	void setSol(int x, int y)								//for setting up the solution
	{
		solution[x-1][y-1] = true;
	};
	void setGrid(int x, int y)								//for changing values to true
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

bool isSolve(puzzle x, game y)
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			if (x.solution[i][j] != y.gridStat[i][j])
				return false;
		};
	};
	return true;
};

int parseExit(string selection)
{
	if (selection.compare("Exit") || selection.compare("exit")){	//user wishes to leave
		cout << "Goodbye!" << endl;
		exit();
	}
	return 0;
}

int main()
{
	puzzl gam;
	cout << "Welcome to our nonogram project!" << endl;
	cout << "If you would like to read the instructions on how to play a nonogram, please type Help." << endl;
	//Tarin here, I'm starting work on our main menu that our user uses to either ask for instructions or load a puzzle
	cout << "If you would like to start a puzzle, please specify the filename of the puzzle you would like to play." << endl;
	//picking a puzzle. Only 1 exists so far.
	cout << "At any time you may type Exit to exit." << endl;
	//allows the user to leave
	
	cin >> selection;	//the user gives us a string and we parse that string for Exit or a filename
	parseExit(selection);
	
	if (selection.compare("Help") || selection.compare("help")){	//user wishes to learn how to play
		//this needs to go in its own function later
		cout << "Extensive instructions on how to play a nonogram go here" << endl;
		
		cout << "Please specify the file you wish to play." << endl;
		cin >> selection;
	}
	parseExit(selection);
	
	cout << endl << "Okay! Here goes..." << endl;
	
	//if (selection == 1)	//a placeholder for a better puzzle selection system.
	dataFile.open("samplePuzzle.txt");		//this line will be our junit test
	//dataFile.open(selection);			//we will be using this line later
	
	if (!dataFile.isOpen())				//file failed to open
	{
		cout << "no. nonono. It failed. Sorry, eh?" << endl << "press something and then enter to leave. sorry again. ";
		cin >> messedUp;						//prompt so the user can read the above text before the program terminates
		return 0;
	};											
	//dataFile.open("samplePuzzle.txt");					//open the file
	
	while(dataFile.good())							//loop to read file and create solution grid
	{
		getline(dataFile, buf);
		temp1=atoi(buf.c_str[0]);
		temp2=atoi(buf.c_str[1]);
		gam.setSol(temp1, temp2);
	};
	dataFile.close();							//close the file

	return 0;
}
