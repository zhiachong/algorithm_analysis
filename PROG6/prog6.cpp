//Zhia Chong and Marvin Rumbaua
//zchong, mrumbaua
//prog6.cpp
//Implementation file for Warshalls Algorithm and 
//Depth First Search

#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.h"
using namespace std;

//@prints a number of new lines
//@pre num is assigned a positive number
//@post outputs num new lines
//@param num is the number of new lines to output
//@param outfile
//@usage PrintLines(2, outfile);
void PrintLines(int num);

//@opens an external file for reading
//@post if the external file fileName exists, then
//@        it is associated with infile, its
//@     pointer is at the beginning else an exception
//@     is thrown
//@param infile
//@usage OpenInputFile(infile);
void OpenInputFile(ifstream& infile, bool& fileOk) ;

//@this function reads items from a file and inserts it
//@into a tree 
//@pre infile is open, and tree are assigned
//@post inputs data from file into tree
//@param infile
//@param item
//@usage GetInputFromFile(infile, item);
void GetInputFromFile(ifstream& infile, Matrix& T);

//@this function closes the textfile
//@post textfile is closed
//@param infile
//@usage CloseInputFile(infile);
void CloseInputFile(ifstream& infile);

//waits for input from user
//@pre		:NA
//@post		:next set of output is printed on screen
//@param	:NA
//@return	:NA
//@usage	:PressEnter();
void PressEnter();

//prints a menu for user
//@pre		:NA
//@post		:NA
//@param	:NA
//@return	:int
//@usage	:PrintMenu() == 1;
int PrintMenu();

//describes incremental steps for Warshall Algorithm
//@pre		:Matrix T exists
//@post		:the steps are output to screen
//@param	:T, the traversed matrix
//@return	:NA
//@usage	:WarshallPath(*mat);
void WarshallPath(Matrix &T);

//describes incremental steps for DFS
//describes incremental steps for DFS
//@pre		:Matrix T exists
//@post		:the steps are output to screen
//@param	:T, the traversed matrix
//@return	:NA
//@usage	:DFSPath(*mat);
void DFSPath(Matrix &T);

int main()
{	
	ifstream infile;
	bool inputOK;
	OpenInputFile(infile, inputOK);
	if (inputOK)
	{
		int choice = 0;
		int size;
		
		infile >> size;
		Matrix *mat = new Matrix(size);
		GetInputFromFile(infile, *mat);
		Matrix *DFSmat = new Matrix(*mat);
			
		infile >> size;
		Matrix *newMat = new Matrix(size);
		GetInputFromFile(infile, *newMat);
		Matrix *DFSnewMat = new Matrix(*newMat);
		
		CloseInputFile(infile);
		
		while (choice != 5)
		{	
			choice = PrintMenu();
			if (choice == 1)
				WarshallPath(*mat);
			else if (choice == 2) 
				DFSPath(*DFSmat);	
			else if (choice == 3)
				WarshallPath(*newMat);
			else if (choice == 4)
				DFSPath(*DFSnewMat);
		}
	}
	
	return 0;
}

//waits for input from user
//@pre		:NA
//@post		:next set of output is printed on screen
//@param	:NA
//@return	:NA
//@usage	:PressEnter();
void PressEnter()
{
	cout << "			Press <ENTER> to move to next page";
	cin.get();
}

//prints a menu for user
//@pre		:NA
//@post		:NA
//@param	:NA
//@return	:int
//@usage	:PrintMenu() == 1;
int PrintMenu()
{
	int choice;
	PrintLines(2);
	cout << "************************************************************************\n";
	cout << "		WELCOME TO THE WORLD OF INCREDIBLE GRAPHS        \n";
	cout << "************************************************************************";
	PrintLines(1);
	cout << "  Press 1 for Warshall's Algorithm Explanation of textbook's digraph";
	PrintLines(1);
	cout << "  Press 2 for Depth-First-Search Explanation of textbook's digraph ";
	PrintLines(1);
	cout << "  Press 3 for Warshall's Algorithm Explanation of our own digraph ";
	PrintLines(1);
	cout << "  Press 4 for Depth-First-Search Explanation of our own digraph ";
	PrintLines(1);
	cout << "  Press 5 to exit ";
	PrintLines(1);
	cout << "************************************************************************\n";
	cout << "Please hit <ENTER> after your choice: ";
	cin >> choice;
	return choice;
}

//describes incremental steps for Warshall Algorithm
//@pre		:Matrix T exists
//@post		:the steps are output to screen
//@param	:T, the traversed matrix
//@return	:NA
//@usage	:WarshallPath(*mat);
void WarshallPath(Matrix &T)
{
    cout << "You've made a brilliant choice!";
    PrintLines(2);
    cin.get();
		
    cout << "		Brief intro: Warshall's Algorithm is used to\n";
    cout << " 	find the transitive closure of a directed graph (digraph) ";
    PrintLines(2);
		
    cout << "This is the adjacency matrix obtained from an input file named ";
    cout << "in6.dat.";
    PrintLines(1);
    operator<<(cout, T);
		
    PressEnter();
    PrintLines(2);
    T.Warshall();
}

//describes incremental steps for DFS
//@pre		:Matrix T exists
//@post		:the steps are output to screen
//@param	:T, the traversed matrix
//@return	:NA
//@usage	:DFSPath(*mat);
void DFSPath(Matrix &T)
{
	cout << "Depth-First-Search it is!" << endl;
}
	
//@prints a number of new lines
//@pre num is assigned a positive number
//@post outputs num new lines
//@param num is the number of new lines to output
//@param outfile
//@usage PrintLines(2, outfile);
void PrintLines(int num)
{
    for (int i = 0; i < num; i++)
    {
       cout << endl;
    }
}

//@opens an external file for reading
//@post if the external file fileName exists, then
//@        it is associated with infile, its
//@     pointer is at the beginning else an exception
//@     is thrown
//@param infile
//@usage OpenInputFile(infile);
void OpenInputFile(ifstream& infile, bool& fileOk) 
{
    infile.open("in6.dat");
    if (infile.fail())
    {
        fileOk = false;
        cout << "ERROR opening input file" << endl;
    } else {
        fileOk = true;
    }
}

//@this function reads items from a file and inserts it
//@into a tree 
//@pre infile is open, and tree are assigned
//@post inputs data from file into tree
//@param infile
//@param item
//@usage GetInputFromFile(infile, item);
void GetInputFromFile(ifstream& infile, Matrix& T)
{
    operator>>(infile, T);
}

//@this function closes the textfile
//@post textfile is closed
//@param infile
//@usage CloseInputFile(infile);
void CloseInputFile(ifstream& infile)
{
    infile.close();
}


