#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;

string messedUp;
string selection;
int temp1;									//for holding row number for selection and changing
int temp2;									//for holding column number for selection and changing
string buf;									//holds a line of data from the file
string entries;									//holds user entries for the puzzle
ifstream dataFile;								//used to open the file(select a puzzle)
int menuFlag = 0;								//used to specify the user is ready or not to load a file


class puzzle
{
	ifstream dataFil;							//for opening a file
	string buff;								//for reading the file
	int temp3;								//for input into setSol
	int temp4;								//for input into setSol
	bool solution[4][4];							//solution grid
	void clearSol()								//for clearing the solution before setting it up
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				solution[i][j]=false;
			};
		};
	};
	void setSol(int x, int y)						//for setting up the solution
	{
		solution[x-1][y-1] = true;
	};
	puzzle(string w)
	{
		clearSol();
		dataFil.open(w);						//open the file
		while(dataFil.good())						//loop to read file and create solution grid
		{
			getline(dataFil, buff);
			temp3=atoi(buff.c_str[0]);
			temp4=atoi(buff.c_str[1]);
			setSol(temp3, temp4);
		};
		dataFil.close();						//close the file
	};

};

class game
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
	bool solution[4][4];								//the solution grid. This should only change when first created. Or if a new puzzle starts.
	bool gridState[4][4];								//the player grid. This should hold the data for the current game. A graphical depiction should be built.
	void setSol(int x, int y)							//for setting up the solution
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
	void setItUp()									//sets up a clear starting grid. Needs to create a solution as well.
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				gridState[i][j] = false;				//the line that actually ensures that the player grid starts blank.
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
	puzzl gam;
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
	
	dataFile.open("samplePuzzle.txt");		//this line will be our junit test. Open the file
	//dataFile.open(selection);			//we will be using this line later
	
	if (!dataFile.isOpen())				//file failed to open
	{
		cout << "no. nonono. It failed. Sorry, eh?" << endl << "press something and then enter to leave. sorry again. ";
		cin >> messedUp;						//prompt so the user can read the above text before the program terminates
		return 0;
	};											
	
	while(dataFile.good())							//loop to read file and create solution grid
	{
		getline(dataFile, buf);
		temp1=atoi(buf.c_str[0]);
		temp2=atoi(buf.c_str[1]);
		gam.setSol(temp1, temp2);
	};
	
	//if(puzzle is solved){
		//cout << "Congratulations! You have completed the puzzle!" << endl;
	//}
	dataFile.close();							//close the file

	return 0;
}
