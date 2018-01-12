// Header file to hold Puzzle class.
#ifndef PUZZLE_H
#define PUZZLE_H 1

#include<fstream>
#include<string>
using namespace std;

class Puzzle 
{
public:
	Puzzle() { delete this; }
	Puzzle(string);
	bool** getSolution() { return solution; }
	bool getSolutionByPoint(int, int);
	int** getRowKey() { return rowKey; }
	int** getColumnKey() { return columnKey; }
	int getRows() { return numRows; }
	int getColumns() { return numColumns; }
	int getHalfRows() { return halfRows; }
	int getHalfColumns() { return halfColumns; }
	~Puzzle();
private:
	bool** solution; // To store solution
	int** rowKey;    // To store row clues
	int** columnKey; // To store column clues
	int numRows, numColumns, halfRows, halfColumns;
};

Puzzle::Puzzle(string filename)
{
	ifstream file(filename);
	if (!file.good()) Puzzle();
	else
	{
		file >> numRows;
		file >> numColumns;

		// Initialize arrays
		bool** solution = new bool*[numRows];
		for (int row = 0; row < numRows; row++)
		{
			solution[row] = new bool[numColumns];
			for (int column = 0; column < numColumns; column++)
			{
				solution[row][column] = false;
			}
		}

		int row, col;
		while (!file.eof())
		{
			file >> row;
			file >> col;
			solution[row][col] = true;
		}
		file.close();

		int** rowKey = new int*[numRows];
		for (int i = 0; i < numRows; i++)
		{
			rowKey[i] = new int[halfRows = (numRows % 2 == 1) ? ((numRows + 1) / 2) : (numRows / 2)];
			for (int j = 0; j < halfRows; j++)
			{
				rowKey[i][j] = 0;
			}
		}

		int** columnKey = new int*[halfColumns = (numColumns % 2 == 1) ? ((numColumns + 1) / 2) : (numColumns / 2)];
		for (int i = 0; i < halfColumns; i++)
		{
			columnKey[i] = new int[numColumns];
			for (int j = 0; j < numColumns; j++)
			{
				columnKey[i][j] = 0;
			}
		}

		// Set keys
		for (int i = numRows - 1; i >= 0; i--)
		{
			int digit = halfRows;
			for (int j = numColumns - 1; j >= 0; j--)
			{
				if (!solution[i][j] && rowKey[digit][i] > 0) digit--;
				else if (!solution[i][j]); // skip
				else rowKey[digit][i]++;
			}
		}

		for (int i = numColumns - 1; i >= 0; i--)
		{
			int digit = halfColumns;
			for (int j = numRows - 1; j >= 0; j--)
			{
				if (!solution[i][j] && columnKey[i][digit] > 0) digit--;
				else if (!solution[i][j]); // skip
				else columnKey[i][digit]++;
			}
		}
	}
}

bool Puzzle::getSolutionByPoint(int row, int column)
{
    if (row >= numRows || column >= numColumns) return;
    else return solution[row][column];
}

Puzzle::~Puzzle()
{
	for (int i = 0; i < numRows; i++)
	{
		delete[] solution[i];
		delete[] rowKey[i];
	}
	delete[] solution;
	delete[] rowKey;

	for (int i = 0; i < halfColumns; i++) delete[] columnKey[i];
	delete[] columnKey;
	delete this;
}

#endif
