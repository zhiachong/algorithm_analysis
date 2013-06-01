//@file name:prog2.cpp
//@author(s): Marvin Jake Rumbaua(mrumbaua) & Zhia Chong (zchong)
//@date        : 02/15/13
//
//@description: This program calculates the Fibonacci Number Sequence by means of:
//
//    1. the iterative, non recursive, linear time algorithm up to a value of n that the user inputs
//    2. the phi formula using a number k, the largest index of the sequence from part 1, F(k) (logarithmic time)
//    3. the matrix power algorithm, using k as in part 2 (logarithmic time)

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const char RED[] = "\033[22;31m"; //sets the output to red
const char RESET[] = "\033[0m"; //resets to white color
const double PHI = (1 + sqrt(5))/2;

//@Displays welcome prompt
//@pre   : none
//@post  : Greeting is output
//@param : none
//@return: none
//@usage : DisplayGreeting();
void DisplayGreeting();

//@Displays Banner for Iterative Method
//@pre   : none
//@post  : Iterative banner is output
//@param : none
//@return: none
//@usage : DisplayIterativeMethodBanner();
void DisplayIterativeMethodBanner();

//@Displays Banner for Phi Method
//@pre   : sizeOfTable is assigned
//@post  : Phi Method Banner is output
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : DisplayPhiMethodBanner(sizeOfTable);
void DisplayPhiMethodBanner(int sizeOfTable);

//@Displays calculations for Phi Method
//@pre   : sizeOfTable is assigned
//@post  : Phi Method calculations are displayed
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : DisplayPhiMethodOutput(sizeOfTable);
void DisplayPhiMethodOutput(int sizeOfTable);

//@Displays Banner and output for Matrix Algorithm Method
//@pre   : sizeOfTable is assigned
//@post  : Matrix Algorithm Banner is output
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : MatrixAlgorithmBannerAndOutput();
void MatrixAlgorithmBannerAndOutput(int sizeOfTable);

//@Determines if number is base 2 number
//@pre   : checkNum is assigned a value
//@post  : none
//@param : checkNum A positive integer
//@return: true if checkNum is a base 2 number, else false
//@usage : if (IsBase2(sizeOfTable));
bool IsBase2(int checkNum);

//@Gets input value from the user
//@pre   : none
//@post  : none
//@param : none
//@return: the value input by the user
//@usage : unsigned int inputSize = GetInput();
int GetInput();

//@Asks user if they want to run the program again
//@pre   : program is run at least once
//@post  : none
//@param : none
//@return: if yes, 1; else -1
//@usage : sizeOfTable = PromptForRepeat();
int PromptForRepeat();

//@Calculates the Fibonacci sequence up to the number of the user input
//@pre   : ArrayOfFibSequence exists, inputSize is assigned a value
//@post  : none
//@param : ArrayOfFibSequence A pointer to the Fibonacci array
//@param : inputSize The largest index of Fibonacci sequence
//@return: the size of the sequence that is calculated
//@usage : int sizeOfTable = CalcFibSeqIteratively(ArrayOfFibSequence, inputSize);
int CalcFibSeqIteratively(unsigned int* f, int inputSize);

//@Checks for unsigned int overflow
//@pre   : there exists a calculated value in current and prev
//@post  : none
//@param : current The current number in the Fibonacci sequence
//@param : prev The previous number in the Fibonacci sequence
//@return: true if current value is less than prev value
//@usage : while(!IsOverflow(next, f[i-1]) && i <= inputSize){
bool IsOverflow(unsigned int current, unsigned int prev);

//@Displays the calculated Fibonacci sequence in an organized table
//@pre   : An array F exists and is assigned with values of the Fibonacci sequence
//@post  : An organized table of the Fibonacci sequence is output to screen
//@param : fibArray A pointer to the Fibonacci sequence array
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : PrintPrettyTable(array, n);
void PrintPrettyTable(unsigned int* fibArray, int sizeOfTable);

//@Prints table column
//@pre   : fibArray exists, counter, nCounter, fnCounter are assigned
//@post  : nCounter and fnCounter are both incremented
//@param : fibArray A pointer to the array that contains Fibonacci sequence
//@param : counter Counter to keep count of how many lines printed
//@param : nCounter Counter to keep track of how many 'n' rows printed
//@param : fnCounter Counter to keep track of how many 'F(n)' rows printed
//@param : rowLabel Label on the current row being printed (either 'f', or 'n')
//@return: none
//@usage : PrintColumn(fibArray, inputSize, nCounter, fnCounter, 'f');
void PrintColumn(unsigned int* fibArray, unsigned int counter, long& nCounter, long& fnCounter, const char& rowLabel);

//@Prints a number of new lines
//@pre   : num is nonnegative
//@post  : num new lines are output
//@param : num Number of lines to be printed
//@return: none
//@usage : PrintLines(1);
void PrintLines(int num);

//@Calculates Phi to a power (sizeOfTable)
//@pre   : sizeOfTable is assigned
//@post  : none
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: value of phi raised to the power of a number (sizeOfTable)
//@usage : round((1/sqrt(5))*CalcPhiPowered(k, phi));
double CalcPhiPowered(unsigned int sizeOfTable);

//@Calculates the Fibonacci sequence in logarithmic time
//@pre   : input size not equal to 0
//@post  : none
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: calulates the Fibonacci sequence in logarithmic time
//@usage : CalcFibLogTime(sizeOfTable)
double CalcFibLogTime(unsigned int sizeOfTable);

//@Creates matrix
//@pre     : first, second, secondRowFirst, and secondRowSecond are intialized and assigned
//@post     : none
//@param : first
//@param : second
//@param : secondRowFirst
//@param : secondRowSecond
//@return: a 2D matrix with values
//@usage : unsigned int** fibMatrix = CreateMatrix(0, 1, 1, 1);
//@matrix representation
//            |first        ,         second        |
//            |secondRowSecond, secondRowFirst|
unsigned int** CreateMatrix(unsigned int first, unsigned int second, unsigned int secondRowFirst, unsigned int secondRowSecond);

//@Displays the Fibonacci sequence calculated using a matrix
//@pre     : inputSize is assigned
//@post     : Displays the calculated Fibonacci sequence
//@param : inputSize The largest index of Fibonacci sequence
//@return: none
//@usage : PrintFibonacciUsingMatrix(sizeOfTable);
void PrintFibonacciUsingMatrix(unsigned int inputSize);

//@Multiplies matrices to a variable "power" recursively
//@pre     : power is assigned a value and fibArray is initialized
//@post     : none
//@param : fibArray A pointer to the Fibonacci sequence array
//@param : power An integer for the power function
//@return: a 2D matrix that is raised to a variable "power"
//@usage : matrixContainer.push_back(recursiveCalcMatrix(matrixContainer, sizeOfTable));
unsigned int** recursiveCalcMatrix(vector<unsigned int**>fibArray, int power);

//@Calculates phi to the power of n recursively
//@pre   : power is assigned a value
//@post  : none
//@param : power An integer for the power function
//@return: phi to the power of n
//@usage : return recursiveCalcPhi(sizeOfTable);
double recursiveCalcPhi(int power);

//@Calculates the Fibonacci sequence using matricies
//@pre   : sizeOfTable is assigned
//@post  : outputs Fibonacci number at F(sizeOfTable);
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : MatrixForm(sizeOfTable);
vector<unsigned int**> MatrixForm(unsigned int sizeOfTable);

//@Multiplies 2 2D matrices
//@pre     : firstMatrix and secondMatrix are initialized
//@post     : none
//@param : firstMatrix A 2D matrix
//@param : secondMatrix A 2D matrix
//@return: the product of 2 2D matrices
//@usage : return MultMatrices(recursiveCalcMatrix(fibArray, power - 1), fibArray.at(0));
unsigned int** MultMatrices(unsigned int **firstMatrix, unsigned int **secondMatrix);

//@checks for valid input
//@pre     : inputSize is assigned a value
//@post     : none
//@param : inputSize The largest index of Fibonacci sequence
//@return: if inputSize >= 0 true, else false
//@usage : return MultMatrices(recursiveCalcMatrix(fibArray, power - 1), fibArray.at(0));
bool IsValidInput(int inputSize);

//**************************************************************************************************

//@This program calculates and displays the Fibonacci Sequence based on user input
//@pre   : none
//@post  : Fibonacci Sequence is calculated and displayed
//@param : none
//@return: none
int main(){

    int inputSize = 1;

    while(inputSize != -1){

        DisplayGreeting();

        inputSize = GetInput();
       
        while(!IsValidInput(inputSize)){
            PrintLines(1);
            cout << "Invalid Number! Please enter a number >= 0" << endl << endl;
            inputSize = GetInput();
        }
        unsigned int* FibonacciArray = new unsigned int[inputSize];

        int sizeOfTable = CalcFibSeqIteratively(FibonacciArray, inputSize);

        PrintPrettyTable(FibonacciArray, sizeOfTable);

        DisplayPhiMethodBanner(sizeOfTable);

        DisplayPhiMethodOutput(sizeOfTable);

        MatrixAlgorithmBannerAndOutput(sizeOfTable);

        delete FibonacciArray;
        FibonacciArray = NULL;
       
        inputSize = PromptForRepeat();
    }
}

//**************************************************************************************************
//@Displays welcome prompt
//@pre   : none
//@post  : Greeting is output
//@param : none
//@return: none
//@usage : DisplayGreeting();
void DisplayGreeting(){

    system("clear");
   
    cout << "*******************************************************************" << endl;
    cout << "********** Welcome to the Fabulous World of Fibonacci!!! **********" << endl;
    cout << "*******************************************************************" << endl << endl;
}

//@Displays Banner for Iterative Method
//@pre   : none
//@post  : Iterative banner is output
//@param : none
//@return: none
//@usage : DisplayIterativeMethodBanner();
void DisplayIterativeMethodBanner(){
   
    cout << "*******************************************************************" << endl;
    cout << "************************ Iterative Method *************************" << endl;
    cout << "*******************************************************************" << endl << endl;
}

//@Displays Banner for Phi Method
//@pre   : sizeOfTable is assigned
//@post  : Phi Method Banner is output
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : DisplayPhiMethodBanner(sizeOfTable);
void DisplayPhiMethodBanner(int sizeOfTable){
   
    cout << "*******************************************************************" << endl;
    cout << "********************** Phi Algorithm Method ***********************" << endl;
    cout << "*******************************************************************" << endl << endl;

}

//@Displays calculations for Phi Method
//@pre   : sizeOfTable is assigned
//@post  : Phi Method calculations are displayed
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : DisplayPhiMethodOutput(sizeOfTable);
void DisplayPhiMethodOutput(int sizeOfTable){

    cout << "Largest Fibonacci sequence index that can be displayed: K = " << sizeOfTable << endl << endl;

    cout << "F(K/2) = " << "F(" << sizeOfTable << "/2) = F(" << (sizeOfTable/2) << ") = " << CalcFibLogTime(sizeOfTable / 2) << endl << endl;
   
    cout << "F(K) = F("  << sizeOfTable << ") = " << fixed << setprecision(0) << CalcFibLogTime(sizeOfTable) << endl << endl;

}

//@Displays Banner and output for Matrix Algorithm Method
//@pre   : sizeOfTable is assigned
//@post  : Matrix Algorithm Banner is output
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : MatrixAlgorithmBannerAndOutput();
void MatrixAlgorithmBannerAndOutput(int sizeOfTable){
   
    cout << "*******************************************************************" << endl;
    cout << "********************* Matrix Algorithm Method *********************" << endl;
    cout << "*******************************************************************" << endl << endl;

    cout << "Largest Fibonacci sequence index that can be displayed: K = " << sizeOfTable << endl << endl;

    PrintFibonacciUsingMatrix(sizeOfTable);
}

//@Determines if number is base 2 number
//@pre   : checkNum is assigned a value
//@post  : none
//@param : checkNum A positive integer
//@return: true if checkNum is a base 2 number, else false
//@usage : if (IsBase2(sizeOfTable));
bool IsBase2(int checkNum)
{
    //number of one bits in the integer
    unsigned int numberOfOneBits = 0;
    //while the total number of one bits is less than or equal to 1
    while (checkNum && numberOfOneBits <= 1)
    {
        if ((checkNum & 1) == 1)
            numberOfOneBits++;
        checkNum >>= 1;
    }
    //if there is only one 1 in the binary representation of checkNum
    return (numberOfOneBits == 1);
}

//@Gets input value from the user
//@pre   : none
//@post  : none
//@param : none
//@return: the value input by the user
//@usage : unsigned int inputSize = GetInput();
int GetInput(){
    int userInput;
    cout << "Please enter a value for n to calculate F(n): ";
    cin >> userInput;
    cout << endl;
    return userInput;
}

//@Asks user if they want to run the program again
//@pre   : program is run at least once
//@post  : none
//@param : none
//@return: if yes, 1; else -1
//@usage : sizeOfTable = PromptForRepeat();
int PromptForRepeat(){
   
    char answer;
   
    cout << "Would you like to continue? Type y/n then <ENTER>: ";
    cin >> answer;

    if(answer == 'y')
        return 1;
    else
        return -1;
}

//@Calculates the Fibonacci sequence up to the number of the user input
//@pre   : ArrayOfFibSequence exists, inputSize is assigned a value
//@post  : none
//@param : ArrayOfFibSequence
//@param : inputSize
//@return: the size of the sequence that is calculated
//@usage : int sizeOfTable = CalcFibSeqIteratively(ArrayOfFibSequence, inputSize);
int CalcFibSeqIteratively(unsigned int* f, int inputSize){

    if(inputSize == 0)
    {
        f[0] = 0;
        return 0;
    }

    f[0] = 0;
    f[1] = 1;

    int i = 2;
    unsigned int next = f[i - 1] + f[i - 2];
    while(!IsOverflow(next, f[i-1]) && i <= inputSize){
        f[i] = next;
        i++;
        next = f[i - 1] + f[i - 2];
    }
    return i - 1;
}

//@Checks for unsigned int overflow
//@pre   : there exists a calculated value in current and prev
//@post  : none
//@param : current
//@param : prev
//@return: true if current value is less than prev value
//@usage : while(!IsOverflow(next, f[i-1]) && i <= inputSize){
bool IsOverflow(unsigned int current, unsigned int prev){
    return (current < prev);
}

//@Displays the calculated Fibonacci sequence in an organized table
//@pre   : An array F exists and is assigned with values of the Fibonacci sequence
//@post  : An organized table of the Fibonacci sequence is output to screen
//@param : fibArray A pointer to the Fibonacci sequence
//@param : sizeOfTable The largest index of Fibonacci sequence
//@return: none
//@usage : PrintPrettyTable(F, n);
void PrintPrettyTable(unsigned int* fibArray, int sizeOfTable){
    long nCounter = 0, fnCounter = 0, timesRan = 0;
    enum Lines {N, FN};
    Lines lineToPrint = N;

    DisplayIterativeMethodBanner();
   
    for (int i = 0; i <= sizeOfTable && nCounter <= sizeOfTable; i++){
        if (lineToPrint == N){
            cout << right << setw(6) << "n: ";
            lineToPrint = FN;
            PrintColumn(fibArray, sizeOfTable, nCounter, fnCounter, 'n');
            PrintLines(1);
        }

        if (lineToPrint == FN){
            cout << RESET;
            cout << right << setw(6) << "F(n): ";
            lineToPrint = N;
            PrintColumn(fibArray, sizeOfTable, nCounter, fnCounter, 'f');
            PrintLines(2);
        }
    }
}

//@Prints table column
//@pre   : fibArray exists, counter, nCounter, fnCounter are assigned
//@post  : nCounter and fnCounter are CalcFibSeqIterativelyboth incremented
//@param : fibArray
//@param : counter
//@param : nCounter
//@param : fnCounter
//@param : rowLabel
//@return: none
//@usage : PrintColumn(fibArray, inputSize, nCounter, fnCounter, 'f');
void PrintColumn(unsigned int* fibArray, unsigned int counter, long& nCounter, long& fnCounter, const char& rowLabel){
    if (rowLabel == 'n'){
        for (int j = 0;j <= 4 && nCounter <= counter; j++){
            cout << RED;
            cout << right << setw(12) << nCounter;
            nCounter++;
        }
    } else {
        for (int j = 0;j <= 4 && fnCounter <= counter; j++){
                cout << right << setw(12) << fibArray[fnCounter];
                fnCounter++;
        }
    }
}

//@Prints a number of new lines
//@pre   : num is nonnegative
//@post  : num new lines are output
//@param : num number of lines to be printed
//@return: none
//@usage : PrintLines(1);CalcFibSeqIteratively
void PrintLines(int num) {
    for (int i = 0; i < num; i++)
        cout << endl;
}

//@Calculates Phi to a power (sizeOfTable)
//@pre   : sizeOfTable is assigned
//@post  : none
//@param : sizeOfTable
//@return: value of phi raised to the power of a number (sizeOfTable)
//@usage : round((1/sqrt(5))*CalcPhiPowered(k, phi));
double CalcPhiPowered(unsigned int sizeOfTable){
    int log2SizeOfTable = int(log2(sizeOfTable));
    if (log2SizeOfTable == 0)
        return PHI * PHI;

    if (IsBase2(sizeOfTable))
    {
        double *powerOfPhi;
        powerOfPhi = new double[log2SizeOfTable];
        powerOfPhi[0] = PHI * PHI;
        for (int i = 1; i < log2SizeOfTable; i++)
        {
            powerOfPhi[i] = powerOfPhi[i-1] * powerOfPhi[i-1];
        }
        return powerOfPhi[log2SizeOfTable - 1];
    } else { //if non base2
        return recursiveCalcPhi(sizeOfTable);
    }
}

//@Calculates phi to the power of n recursively
//@pre   : power is assigned a value
//@post  : none
//@param : power
//@return: phi to the power of n
//@usage : return recursiveCalcPhi(sizeOfTable);
double recursiveCalcPhi(int power)
{
    if (power == 0)
        return 1.0;

    else if (power == 1)
    {
        return PHI;

    }
    else if (power == 2)
    {
        return PHI * PHI;

    }
    else if (power % 2 == 0)
    {
        double tempNum = recursiveCalcPhi(power / 2);
        return tempNum * tempNum;
    } else {
        return recursiveCalcPhi(power - 1) * PHI;
    }
}

//@Calculates the Fibonacci sequence in logarithmic time
//@pre   : input size not equal to 0
//@post  : none
//@param : sizeOfTable
//@return: calulates the Fibonacci sequence in logarithmic time
//@usage : CalcFibLogTime(sizeOfTable)
double CalcFibLogTime(unsigned int sizeOfTable){
    return round((1/sqrt(5))*CalcPhiPowered(sizeOfTable));
}

//@Creates matrix
//@pre     : first, second, secondRowFirst, and secondRowSecond are intialized and assigned
//@post     : none
//@param : first
//@param : second
//@param : secondRowFirst
//@param : secondRowSecond
//@return: a 2D matrix with values
//@usage : unsigned int** fibMatrix = CreateMatrix(0, 1, 1, 1);

unsigned int** CreateMatrix(unsigned int first, unsigned int second, unsigned int secondRowFirst, unsigned int secondRowSecond)
{
    //creates a 2D matrix
    unsigned int** fibMatrix = new unsigned int*[2];
    for(unsigned int i = 0; i < 2; ++i)
        fibMatrix[i] = new unsigned int[2];

    //initializes the matrix with 0, 1, 1, 1
    fibMatrix[0][0] = first;
    fibMatrix[0][1] = second;
    fibMatrix[1][0] = secondRowFirst;
    fibMatrix[1][1] = secondRowSecond;
    return fibMatrix;
}

//@Calculates the Fibonacci sequence using matricies
//@pre   : sizeOfTable is assigned
//@post  : outputs Fibonacci number at F(sizeOfTable);
//@param : sizeOfTable
//@return: none
//@usage : MatrixForm(sizeOfTable);

vector<unsigned int**> MatrixForm(unsigned int sizeOfTable)
{
    //this contains pointers to matrices
    vector<unsigned int**> matrixContainer;
   
    if(sizeOfTable == 0){
        matrixContainer.push_back(CreateMatrix(0, 0, 0, 0));
        return matrixContainer;

    }

    //creates a 2D matrix
    unsigned int** fibMatrix = CreateMatrix(0, 1, 1, 1);

    //adds the matrix to the matrix container
    matrixContainer.push_back(fibMatrix);
    //adds the square of first matrix to the matrix container
    matrixContainer.push_back(MultMatrices(fibMatrix, fibMatrix));

    //finds out if the size of table is a base 2
    int log2SizeOfTable = int(log2(sizeOfTable));


    //edge case: if the size is 1, or only 1 number in the sequence
    if (log2SizeOfTable == 0)
            cout << "F(n) = 1" << endl;

    if (IsBase2(sizeOfTable))
    {
        for (int i = 2; i < log2SizeOfTable + 1; i++)
        {
            //multiples two matrices together and adds them to the matrix container
            matrixContainer.push_back(MultMatrices(matrixContainer.at(i-1), matrixContainer.at(i-1)));
        }
    } else {
        matrixContainer.push_back(recursiveCalcMatrix(matrixContainer, sizeOfTable));
    }
    return matrixContainer;
}

//@Displays the Fibonacci sequence calculated using a matrix
//@pre     : inputSize is assigned
//@post     : Displays the calculated Fibonacci sequence
//@param : inputSize
//@return: none
//@usage : PrintFibonacciUsingMatrix(sizeOfTable);

void PrintFibonacciUsingMatrix(unsigned int inputSize)
{
    vector<unsigned int**> matrixContainer = MatrixForm(inputSize);
    vector<unsigned int**> matrixContainer2 = MatrixForm(inputSize/2);

    //get the last matrix from the matrix container
    unsigned int **matrix1 = matrixContainer.at(matrixContainer.size() - 1);
    unsigned int **matrix2 = matrixContainer2.at(matrixContainer2.size() - 1);

    //display the matrix container's information
   
    cout << "F(K/2) = " << "F(" << inputSize << "/2) = F(" << inputSize/2 << ") = " << matrix2[0][1] << endl << endl;
   
    cout << "F(K) = F(" << inputSize << ") = " << matrix1[0][1] << endl << endl;
}

//@Multiplies matrices to a variable "power" recursively
//@pre     : power is assigned a value and fibArray is initialized
//@post     : none
//@param : fibArray
//@param : power
//@return: a 2D matrix that is raised to a variable "power"
//@usage : matrixContainer.push_back(recursiveCalcMatrix(matrixContainer, sizeOfTable));

unsigned int** recursiveCalcMatrix(vector<unsigned int**>fibArray, int power)
{
    if (power == 0)
    {
        return CreateMatrix(0, 1, 1, 1);
    }
    else if (power == 1)
    {
        return fibArray.at(0);
    }
    else if (power == 2)
    {
        return MultMatrices(fibArray.at(0), fibArray.at(0));
    }
    else if (power % 2 == 0)
    {
        unsigned int** tempMatrix = recursiveCalcMatrix(fibArray, power / 2);
        return MultMatrices(tempMatrix, tempMatrix);
    } else {
        return MultMatrices(recursiveCalcMatrix(fibArray, power - 1), fibArray.at(0));
    }
}

//@Multiplies 2 2D matrices
//@pre     : firstMatrix and secondMatrix are initialized
//@post     : none
//@param : firstMatrix
//@param : secondMatrix
//@return: the product of 2 2D matrices
//@usage : return MultMatrices(recursiveCalcMatrix(fibArray, power - 1), fibArray.at(0));
unsigned int** MultMatrices(unsigned int **firstMatrix, unsigned int **secondMatrix)

{
    unsigned int first = firstMatrix[0][0];
    unsigned int second = firstMatrix[0][1];
    unsigned int secondRowFirst = firstMatrix[1][0];
    unsigned int secondRowSecond = firstMatrix[1][1];

    unsigned int s_first = secondMatrix[0][0];
    unsigned int s_second = secondMatrix[0][1];
    unsigned int s_secondRowFirst = secondMatrix[1][0];
    unsigned int s_secondRowSecond = secondMatrix[1][1];

    //multiples two 2x2 matrices together
    unsigned int **fibMatrix = CreateMatrix(first * s_first + second * s_secondRowFirst, first * s_second + second * s_secondRowSecond, secondRowFirst * s_first + secondRowSecond * s_secondRowFirst, secondRowFirst * s_second + secondRowSecond * s_secondRowSecond);

    return fibMatrix;
}

//@checks for valid input
//@pre     : inputSize is assigned a value
//@post     : none
//@param : inputSize
//@return: if inputSize >= 0 true, else false
//@usage : return MultMatrices(recursiveCalcMatrix(fibArray, power - 1), fibArray.at(0));
bool IsValidInput(int inputSize){
    return(inputSize >= 0);
}
