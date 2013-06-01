//Zhia Chong and Marvin Rumbaua
//zchong, mrumbaua
//matrix.h
//Header file for Matrix

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

class Matrix {
	//friend operator overload to output a matrix
	//@pre		:matrix is already initialized and output stream is open
	//@post 	:prints out the matrix
	//@param	:output The output stream
	//@param	:A Matrix to be printed
	//@return	:NA
	//@usage	:operator <<(cout, *A);
    friend ostream& operator<< (ostream& output, const Matrix& A);
    
    //friend operator overload to get input into a matrix
	//@pre		:matrix is not initialized and input stream is open
	//@post 	:matrix is filled with info from input stream
	//@param	:input The input stream
	//@param	:A Matrix to be filled
	//@return	:NA
	//@usage	:operator>>(input, *mat);
    friend istream& operator>> (istream& input, Matrix& A);
  public:
	//default constructor with size 4 as default matrix size
    Matrix();
    
    //constructor that takes in a parameter for matrix size
	//@pre		:matrix is not initialized 
	//@post 	:matrix is initialized with size
	//@param	:matrixSize size of matrix
	//@return	:NA
	//@usage	:Matrix mat(4);
    Matrix(int matrixSize);
    
    //copy constructor that takes in a matrix
	//@pre		:matrix is not initialized 
	//@post 	:matrix is initialized
	//@param	:T The matrix to be copied
	//@return	:NA
	//@usage	:Matrix *mat = new Matrix(oldMat);
    Matrix(const Matrix &T);
		
	//destructor 
	//@pre		:matrix exists 
	//@post 	:matrix destroyed
	//@param	:NA
	//@return	:NA
	//@usage	:~mat();	
    ~Matrix();
    
    
    void DFS(Matrix& T);
    
    //a Warshall Step that finds the paths
	//@pre		:adjacency matrix is defined, k is defined
	//@post 	:fills in the matrix T
	//@param	:T, the traversal matrix
	//@return	:NA
	//@usage	:mat -> WarshallStep(5);
    void WarshallStep(const int k);
    
	//executes the Warshall Algorithm and finds ...
	//@pre		:matrix is already initialized
	//@post 	:computes the matrix
	//@param	:NA
	//@return	:NA
	//@usage	:mat -> Warshall();
    void Warshall();
    
    //fills up the matrix using input from an array
	//@pre		:matrix is not filled
	//@post 	:matrix is filled with input from an array
	//@param	:input A bool array 
	//@return	:NA
	//@usage	:mat -> setMatrix(vector<bool> input);
    void setMatrix(vector<bool> input);
    
    //gets the value of a matrix at a given row and column
	//@pre		:row and column are specified
	//@post 	:NA
	//@param	:row The row of matrix
	//@param	:column The column of matrix
	//@return	:the value of matrix at given row and column
	//@usage	:mat -> getMatrixValue(2, 3);
    int getMatrixValue(int row, int column) const;
    
	//gets the size ofvoid PrintMatrix(int row, int col, int color); matrix
	//@pre		:NA
	//@post 	:NA
	//@param	:NA
	//@return	:the size of matrix
	//@usage	:mat -> getMatrixSize()
    int getMatrixSize() const;
    
  private:  
    bool *matrixWithTwoDimensions;
    int size;
    vector <int> stack;
    
    //helper to print the entire matrix with a specific color 
	//@pre		:row, column and color are initialized
	//@post 	:prints out a Matrix
	//@param	:row The row of matrix 
	//@param	:column The column of matrix
	//@param 	:color The color to use for cout
	//@return	:NA
	//@usage	:PrintMatrix(i, i, color++);
    void PrintMatrix(int row, int col, int color);
    
    //pushes row and col onto explicit stack (attatches row and col to end of vector
	//@pre		:stack exists
	//@post		:row and col were attatched to the end of the vector
	//@param	:row, index of row
	//@param	:col, index of col
	//@usage	:pushMatrix(row, col);
    void pushMatrix(int row, int col);
    
    //pops row and col from explicit stack and assigns values to row and col
    //@pre		:the stack is not empty, row and col exist
    //@post		:row and col are assigned values from the stack
    //@param	:row, index of row
	//@param	:col, index of col
	//@usage	:popMatrix(row, col);
	void popMatrix(int& row, int& col);
	
	//helper to set a value at specific row and column of matrix
	//@pre		:row, column and value are initialized
	//@post 	:matrix at row and column is inserted with value
	//@param	:row The row of matrix 
	//@param	:column The column of matrix
	//@param 	:value The bool value to insert into matrix
	//@return	:NA
	//@usage	:mat -> setMatrixVal(0, 1, true);
    void setMatrixVal(int row, int column, bool value);
    
    //helper to get a bool value at specific row and column of matrix
	//@pre		:row, column and value are initialized
	//@post 	:NA
	//@param	:row The row of matrix 
	//@param	:column The column of matrix
	//@return	:returns the boolean value at a specific row and column
	//@usage	:mat -> getMatrixBoolVal(0, 1);
    bool getMatrixBoolVal(int row, int column) const;
    
    void DFSHelper(int row, int col, Matrix& T);
    
    //picks a color to use for std::cout
	//@pre		:n is initialized
	//@post 	:NA
	//@param	:n The color index
	//@return	:returns color 
	//@usage	:mat -> PickColor(0, 1);
    const char* PickColor(int in);
    
	//waits for input from user
	//@pre		:NA
	//@post		:next set of output is printed on screen
	//@param	:NA
	//@return	:NA
	//@usage	:PressEnter();
    void PressEnter();
};
#endif
