//Zhia Chong and Marvin Rumbaua
//zchong, mrumbaua
//matrix.cpp
//Implementation file for Matrix

#include <iostream>
#include <iomanip>
#include "matrix.h"
#include <cmath>
#include <fstream>
using namespace std;

const char RED[] = "\033[22;31m"; //sets the output to red
const char RESET[] = "\033[0m"; //resets to white color
const char GREEN[] = "\033[22;32m"; //sets the output to green
const char BLUE[] = "\033[22;34m";
const char CYAN[] = "\033[22;36m";

//default constructor with size 4 as default matrix size
Matrix::Matrix()
{ 
	size = 4;
	matrixWithTwoDimensions = new bool[4*4];
}

//constructor that takes in a parameter for matrix size
//@pre		:matrix is not initialized 
//@post 	:matrix is initialized with size
//@param	:matrixSize size of matrix
//@return	:NA
//@usage	:Matrix mat(4);
Matrix::Matrix(int matrixSize)
{
    size = matrixSize;
    matrixWithTwoDimensions = new bool[size * size];
}

//copy constructor that takes in a matrix
//@pre		:matrix is not initialized 
//@post 	:matrix is initialized
//@param	:T The matrix to be copied
//@return	:NA
//@usage	:Matrix *mat = new Matrix(oldMat);
Matrix::Matrix(const Matrix &T)
{
	size = T.getMatrixSize();
	matrixWithTwoDimensions = new bool[size * size];
	for (int i = 0; i < T.getMatrixSize(); i++)
	{
		for (int j = 0; j < T.getMatrixSize(); j++)
		{
			bool val = (T.getMatrixValue(i, j) == 0) ? false:true;
			setMatrixVal(i, j, val);
		}
	}
}
	
//destructor 
//@pre		:matrix exists 
//@post 	:matrix destroyed
//@param	:NA
//@return	:NA
//@usage	:~mat();
Matrix::~Matrix()
{
	size = -1;
    delete [] matrixWithTwoDimensions;
}

//Depth First Search to find //
//@pre		:adjacency matrix is initialized
//@post 	:	
//@param	:
//@return	:
//@usage	:mat->DFS();
void Matrix::DFS(Matrix& T)
{
	for(int row = 0; row < size; row++)
	{
		for(int col = 0; col < size; col++)
		{
			if(getMatrixBoolVal(row, col))
			{
				DFSHelper(row, col, T);
			}
		}
	}
}

//a Warshall Step that finds the paths
//@pre		:adjacency matrix is defined, k is defined
//@post 	:fills in the matrix T
//@param	:T, the traversal matrix
//@return	:NA
//@usage	:mat -> WarshallStep(5);
  void Matrix::WarshallStep(const int k)
{
	cout << "\nFound 1 at the following indices of the matrix: " << endl;
	int color, col;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            bool one = getMatrixBoolVal(i, j);
            bool nexttwo = getMatrixBoolVal(i, k) && getMatrixBoolVal(k, j);
            setMatrixVal(i, j, one || nexttwo);
            if (one) {
				cout << "i: " << PickColor(2) << i << RESET << " j: ";
				cout << PickColor(2) << j << RESET << endl;
			}
			else if (nexttwo) {
				cout << "i: " << PickColor(1) << i << RESET << " k: ";
				cout << PickColor(1) << k << RESET << " and k: " <<  PickColor(1);
				cout << k << RESET << " and j: " << PickColor(1) << j << RESET << endl; 
			}
        }
    }
    PressEnter();
}

//fills up the matrix using input from an array
//@pre		:matrix is not filled
//@post 	:matrix is filled with input from an array
//@param	:input A bool array 
//@return	:NA
//@usage	:mat -> setMatrix(vector<bool> input);
void Matrix::setMatrix(vector<bool> input)
{
    int trace = 0;
	int inputSize = (int)sqrt(input.size());
	for (int i = 0; i < inputSize; i++)
	{
		for (int j = 0; j < inputSize; j++)
		{
			setMatrixVal(i, j, input[trace++]);
		}
	}
}

//gets the value of a matrix at a given row and column
//@pre		:row and column are specified
//@post 	:NA
//@param	:row The row of matrix
//@param	:column The column of matrix
//@return	:the value of matrix at given row and column
//@usage	:mat -> getMatrixValue(2, 3);
int Matrix::getMatrixValue(int row, int column) const{
	return getMatrixBoolVal(row, column) ? 1:0;
}

//gets the size ofvoid PrintMatrix(int row, int col, int color); matrix
//@pre		:NA
//@post 	:NA
//@param	:NA
//@return	:the size of matrix
//@usage	:mat -> getMatrixSize()
int Matrix::getMatrixSize() const{return size;}

//executes the Warshall Algorithm and finds ...
//@pre		:matrix is already initialized
//@post 	:computes the matrix
//@param	:NA
//@return	:NA
//@usage	:mat -> Warshall();
void Matrix::Warshall()
{
	int color = 1;
    for (int i = 0; i < size; i++)
    {
		WarshallStep(i);		
		PrintMatrix(i, i, color++);
        PressEnter();
        if (color > 4)
			color = 1;
	}
	cout << "The transitive closure is:" << endl;
	PrintMatrix(1, 1, 5); //5 is RESET, so back to black
	PressEnter();
}

//friend operator overload to output a matrix
//@pre		:matrix is already initialized and output stream is open
//@post 	:prints out the matrix
//@param	:output The output stream
//@param	:A Matrix to be printed
//@return	:NA
//@usage	:operator <<(cout, *A);
ostream& operator<< (ostream& output, const Matrix& A)
{
	int size = A.getMatrixSize();
    if (size == 0)
        output << "Matrix is empty!";
    for (int i = 0; i < size; i++)
    {
		output << "|";
        for (int j = 0; j < size; j++)
        {
            output << setw(2) << A.getMatrixValue(i, j) << " "; 
        }
        output << "|\n";
    }
}

//friend operator overload to get input into a matrix
//@pre		:matrix is not initialized and input stream is open
//@post 	:matrix is filled with info from input stream
//@param	:input The input stream
//@param	:A Matrix to be filled
//@return	:NA
//@usage	:operator>>(input, *mat);
istream& operator>> (istream& input, Matrix& A) {
	bool in;
	string instring;
	vector <bool> inputMatrix;
	while (!input.eof() && instring != "E")
	{	
		getline(input, instring);
		for (string::iterator i = instring.begin(); i < instring.end(); i++)
		{
			if (*i == '1')
			{
				in = true;
				inputMatrix.push_back(in);
				
			} else if (*i == '0')
			{
				in = false;
				inputMatrix.push_back(in);
			}
			
		}
	}
	A.setMatrix(inputMatrix);
}

							/*PRIVATE HELPER*/
							
//helper to set a value at specific row and column of matrix
//@pre		:row, column and value are initialized
//@post 	:matrix at row and column is inserted with value
//@param	:row The row of matrix 
//@param	:column The column of matrix
//@param 	:value The bool value to insert into matrix
//@return	:NA
//@usage	:mat -> setMatrixVal(0, 1, true);						
void Matrix::setMatrixVal(int row, int column, bool value)
{
    matrixWithTwoDimensions[row * size + column] = value;
}

//helper to print the entire matrix with a specific color 
//@pre		:row, column and color are initialized
//@post 	:prints out a Matrix
//@param	:row The row of matrix 
//@param	:column The column of matrix
//@param 	:color The color to use for cout
//@return	:NA
//@usage	:PrintMatrix(i, i, color++);
void Matrix::PrintMatrix(int row, int col, int color)
{
    if (size == 0)
        cout << "Matrix is empty!";
    for (int i = 0; i < size; i++)
    {
		cout << "|";
        for (int j = 0; j < size; j++)
        {
			if (j == col || i == row)
				cout << PickColor(color) << setw(2) << getMatrixValue(i, j) << RESET << " ";
			else 
				cout << setw(2) << getMatrixValue(i, j) << " "; 
        }  
        cout << "|\n";
    }
    cout << endl;
}

//helper to get a bool value at specific row and column of matrix
//@pre		:row, column and value are initialized
//@post 	:NA
//@param	:row The row of matrix 
//@param	:column The column of matrix
//@return	:returns the boolean value at a specific row and column
//@usage	:mat -> getMatrixBoolVal(0, 1);
bool Matrix::getMatrixBoolVal(int row, int column) const
{
    return matrixWithTwoDimensions[row * size + column];
}

//pushes row and col onto explicit stack (attatches row and col to end of vector
//@pre		:stack exists
//@post		:row and col were attatched to the end of the vector
//@param	:row, index of row
//@param	:col, index of col
//@usage	:pushMatrix(row, col);
void Matrix::pushMatrix(int row, int col)
{
	stack.push_back(row);
	stack.push_back(col);
}

//pops row and col from explicit stack and assigns values to row and col
//@pre		:the stack is not empty, row and col exist
//@post		:row and col are assigned values from the stack
//@param	:row, index of row
//@param	:col, index of col
//@usage	:popMatrix(row, col);
void Matrix::popMatrix(int& row, int& col)
{
	col = stack.back();
	stack.pop_back();
	row = stack.back();
	stack.pop_back();
}

//picks a color to use for std::cout
//@pre		:n is initialized
//@post 	:NA
//@param	:n The color index
//@return	:returns color 
//@usage	:mat -> PickColor(0, 1);
const char* Matrix::PickColor(int in)
{
	switch (in) {
		case 1:
			return RED;
		case 2:
			return GREEN;
		case 3: 
			return BLUE;
		case 4: 
			return CYAN;
		default:
			return RESET;
	}
}
	
//waits for input from user
//@pre		:NA
//@post		:next set of output is printed on screen
//@param	:NA
//@return	:NA
//@usage	:PressEnter();
void Matrix::PressEnter()
{
	cout << "			Press <ENTER> to move to next page";
	cin.get();
}

// Not completed
void Matrix::DFSHelper(int row, int col, Matrix& T)
{	
	int matrixRow, matrixCol;
	int matrixSize = size*size;
	
	vector<bool> visitedNode;
	visitedNode.reserve(matrixSize);
	
	for(int index = 0; index < matrixSize; index++)
		visitedNode[index] = false;
		
	pushMatrix(row, col);

	while(!stack.empty())
	{
		popMatrix(matrixRow, matrixCol);
		if(!visitedNode[matrixRow*size + matrixCol])
		{
			visitedNode[matrixCol*size + matrixRow] = true;
			for(int i = 0; i < size; i++)
			{
				if(getMatrixBoolVal(matrixCol, i))
				{
					visitedNode[matrixCol*size + i] = true;
					pushMatrix(i, 0);
				}
				T.setMatrixVal(matrixRow, i, true);
			}	
		}
	}
}
