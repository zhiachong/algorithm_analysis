//@author: Zhia Chong
//@file prog1.cpp
//@description: This program converts a non-negative decimal integer into its binary equivalent
//				and pretty prints it on the console
//@date: 1/30/2013

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//builds the binary sequence but in reverse order. eg. 6 would be 011 instead of 110 
//@pre: stack and input are defined
//@post: builds the binary sequence and puts it into a stack
//@param: stack This is a vector (a dynamic array) that can grow to a huge size
//@param: input This is the input from user
//@usage buildBinarySequenceInReverse(stack, 20);
void buildBinarySequenceInReverse(vector<int>& stack, int input)
{
	int temp = input;
	int remainder = 0;
	while (temp > 0)
	{
		remainder = temp % 2;
		temp /= 2;
		//adds the remainder to the top of the stack
		stack.push_back(remainder);
	}
}

//pretty prints the binary sequence of input stored in a stack
//@pre: stack is defined
//@post: pretty prints the binary sequence in right order on console
//@param: stack Contains the binary sequence in reversed order
//@usage printBinarySequence(stack);
void printBinarySequence(vector<int> stack)
{
	//goes to the top of the stack and starts printing
	for (int k = stack.size() - 1; k >= 0; k--)
	{
		cout << stack.at(k);
	}
	cout << endl;
}

//finds the binary sequence of input
//@pre: input is defined
//@post: builds the binary sequence of input and prints it on console
//@param: input This is the input from user
//@usage findBinary(20);
void findBinary(int input)
{
	//creates a dynamic array using <vector> class
	vector <int> stack;
	//builds the binary sequence and puts it in the stack
	buildBinarySequenceInReverse(stack, input);
	//prints out the binary in correct sequence from stack
	printBinarySequence(stack);
}

//main entry point of the program
int main()
{
	int decimal;
	while (decimal != -1)
	{
		cout << endl << endl;
		cout << "******************************" << endl;
		cout << "WELCOME TO MY BINARY CONVERTOR" << endl;
		cout << "******************************" << endl;
		cout << "Enter a non-negative base 10 " << endl;
		cout << "integer to convert to binary or" << endl;
		cout << "enter -1 to exit. " << endl;
		cout << "Input: ";
		cin >> decimal;
		if (decimal > 0)
		{
			cout << "Your input: " << decimal << endl;
			cout << "Your output: ";
			findBinary(decimal);
		}
	}
	cout << endl << "Thanks for trying!" << endl;
}
