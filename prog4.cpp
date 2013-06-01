//@file: prog4.cpp
//@date: 03/03/13
//@description: Calculates and outputs the extreme points of a set of points(Convex Hull Problem)

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

//creates a struct called Point with x and y coordinates
struct Point {double x;
	      double y;};

//Generates a struct point containing an x and y coordinate
//pre   : x and y are assigned values
//post  : NA
//param : x, x coordinate
//param : y, y coordinate
//return: a struct Point containing an x and y coordinate
//usage : vectorPoints.push_back(CreatePoint(0, 5));
Point CreatePoint(double x, double y);

//Writes points used in graph to an output file
//pre   : output file is open
//post  : graph points are output to output file
//param : outfile
//param : arrayOfPoints This is a vector containing Points of the graph
//return: NA
//PrintPointsInOutput(outfile, vectorOfGraphPoints);
void PrintPointsInOutput(ofstream& outfile, vector<Point>arrayOfPoints);

//Finds the a, b and c of the equation ax + by - c = 0
//pre   : point1 and point2 are defined
//post  : NA
//param : point1 A struct Point 
//param : point2 A Struct Point
//return: a vector containing 3 points with a at index 0, b at 1 and c at 2
//usage : vector<double> abc = FindABC(point1, point2);
vector<double>FindABC(Point point1, Point point2);

//Generates a vector of struct Points
//pre   : vectorOfGraphPoints exists
//post  : NA
//param : infile The input channel to retrieve data from an input file
//return: a struct Point containing an x and y coordinate
//usage : vector<Point> vectorOfGraphPoints = CreateGraphPoints();
vector<Point> CreateGraphPoints(ifstream& infile);

//Find the extreme points of a set of graph coordinates
//pre   : vectorOfGraphPoints exists and contains Points with x and y coordinates
//post  : NA
//param : vectorOfGraphPoints, vector of struct Points that each contain an x and y coordinate 
//param : outfile An output channel to print to a file
//return: the extreme points calculated (P1 and P2)
//usage : FindExtremePoints(vectorOfGraphPoints);
void FindExtremePoints(vector<Point> vectorOfGraphPoints, ofstream& outfile);

//Opens output file
//pre   : 
//post  : output file is open
//param : outfile
//return: NA
//usage : OpenOutputFile(outfile);
void OpenOutputFile(ofstream& outfile);

//Opens input file
//pre   : infile is defined
//post  : input file is open
//param : infile
//return: NA
//usage : OpenInputFile(infile);
void OpenInputFile(ifstream& infile);

//Closes output file
//pre   : 
//post  : output file is closed
//param : outfile
//return: NA
//usage : CloseOutputFile(outfile);
void CloseOutputFile(ofstream& outfile);

//Writes data to open output file
//pre   : output file is open
//post  : data is output to output file
//param : outfile
//param : point1, struct Point that contains an x and y coordinate
//param : point2, struct Point that contains an x and y coordinate
//param : i, index of first extreme point
//param : j index of next extreme point
//return: NA
//usage : PrintToOutputFile(outfile, point1, point2, i, j);
void PrintToOutputFile(ofstream& outfile, Point point1, Point point2, int i, int j);

//Closes infile file
//pre   : infile file is open
//post  : infile file is closed
//param : infile
//return: NA
//usage : CloseInputFile(infile);
void CloseInputFile(ifstream& infile);

//Finds the signs of other points in the graph
//pre   : vectorOfGraphPoints exists, i and j (indices to the vector) and p1 and p2 all exist
//post  : NA
//param : vectorOfGraphPoints, vector of struct Points that each contain an x and y coordinate 
//param : i Index to the starting point in the vector
//param : j Index to the end point in the vector
//param : p1 Starting point used to calculate a,b and c
//param : p2 End point used to calculate a, b, and c
//return: true if all other points are either less than or more than the line connecting p1 and p2. false 
//        otherwise.
//usage : if(SignsOfOtherPointsAreTheSame(vectorOfGraphPoints, i, j, point1, point2))
bool SignsOfOtherPointsAreTheSame(vector<Point> vectorOfGraphPoints, int i, int j, Point& p1, Point& p2);

//***************************************************************************************************************
int main(){
    ofstream outfile;
    ifstream infile;

    OpenInputFile(infile);
    vector<Point> vectorOfGraphPoints = CreateGraphPoints(infile);

    OpenOutputFile(outfile);
    PrintPointsInOutput(outfile, vectorOfGraphPoints);
    FindExtremePoints(vectorOfGraphPoints, outfile);	

    CloseOutputFile(outfile);
    CloseInputFile(infile);
    return 0;
}
//***************************************************************************************************************
//Generates a struct point containing an x and y coordinate
//pre   : x and y are assigned values
//post  : NA
//param : x, x coordinate
//param : y, y coordinate
//return: a struct Point containing an x and y coordinate
//usage : vectorPoints.push_back(CreatePoint(0, 5));
Point CreatePoint(double x, double y){
    Point point = {x,y};
    return point;
}

//Generates a vector of struct Points
//pre   : vectorOfGraphPoints exists
//post  : NA
//param : infile The input channel to retrieve data from an input file
//return: a struct Point containing an x and y coordinate
//usage : vector<Point> vectorOfGraphPoints = CreateGraphPoints();
vector<Point> CreateGraphPoints(ifstream& infile){
    vector<Point> vectorPoints;
    while (!infile.eof())
    {
        int x,y;
        infile >> x;
        infile >> y;
        vectorPoints.push_back(CreatePoint(x, y));
    }
    return vectorPoints;
}

//Find the extreme points of a set of graph coordinates
//pre   : vectorOfGraphPoints exists and contains Points with x and y coordinates
//post  : NA
//param : vectorOfGraphPoints, vector of struct Points that each contain an x and y coordinate 
//param : outfile An output channel to print to a file
//return: the extreme points calculated (P1 and P2)
//usage : FindExtremePoints(vectorOfGraphPoints);
void FindExtremePoints(vector<Point> vectorOfGraphPoints, ofstream& outfile){
    for(int i = 0; i < vectorOfGraphPoints.size() - 1; i++){
    	for(int j = i + 1; j < vectorOfGraphPoints.size(); j++){
           
	    Point point1, point2;
            //find the signs of all other points
            if(SignsOfOtherPointsAreTheSame(vectorOfGraphPoints, i, j, point1, point2))
                PrintToOutputFile(outfile, point1, point2, i, j);
        }
    }
}

//Finds the signs of other points in the graph
//pre   : vectorOfGraphPoints exists, i and j (indices to the vector) and p1 and p2 all exist
//post  : NA
//param : vectorOfGraphPoints, vector of struct Points that each contain an x and y coordinate 
//param : i Index to the starting point in the vector
//param : j Index to the end point in the vector
//param : p1 Starting point used to calculate a,b and c
//param : p2 End point used to calculate a, b, and c
//return: true if all other points are either less than or more than the line connecting p1 and p2. false 
//        otherwise.
//usage : if(SignsOfOtherPointsAreTheSame(vectorOfGraphPoints, i, j, point1, point2))
bool SignsOfOtherPointsAreTheSame(vector<Point> vectorOfGraphPoints, int i, int j, Point& p1, Point& p2)
{
    Point point1 = vectorOfGraphPoints[i];
    Point point2 = vectorOfGraphPoints[j]; 

    p1 = point1;
    p2 = point2;
    
    vector<double> abc = FindABC(point1, point2);
    double a = abc.at(0);
    double b = abc.at(1);
    double c = abc.at(2);

    bool extremePointExists = true;
    bool signOfPoint = false; 
    bool assignedSign = false;

    for(int k = 0; k < vectorOfGraphPoints.size() && extremePointExists; k++){
        if(k != i && k != j){
            Point point3 = vectorOfGraphPoints[k];
            double sign = a*(point3.x) + b*(point3.y) - c;
            if (!assignedSign){
                assignedSign = true;
            	if(sign > 0)
            	    signOfPoint = true;		
                else
            	    signOfPoint = false;
            }
            else{
                if(signOfPoint && sign > 0)
                    extremePointExists = true;
                else if(!signOfPoint && sign < 0)
            	    extremePointExists = true;
           	else
           	    extremePointExists = false;
          
            }
        }
    } 
    return extremePointExists;
}

//Finds the a, b and c of the equation ax + by - c = 0
//pre   : point1 and point2 are defined
//post  : NA
//param : point1 A struct Point 
//param : point2 A Struct Point
//return: a vector containing 3 points with a at index 0, b at 1 and c at 2
//usage : vector<double> abc = FindABC(point1, point2);
vector<double>FindABC(Point point1, Point point2)
{
    double a = point2.y - point1.y;
    double b = point1.x - point2.x;
    double c = point1.x*point2.y - point1.y*point2.x;
    vector<double> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    return v;
}

//Opens input file
//pre   : infile is defined
//post  : input file is open
//param : infile
//return: NA
//usage : OpenInputFile(infile);
void OpenInputFile(ifstream& infile){
    infile.open("in4.dat");
}

//Opens output file
//pre   : outfile is defined
//post  : output file is open
//param : outfile
//return: NA
//usage : OpenOutputFile(outfile);
void OpenOutputFile(ofstream& outfile){
    outfile.open("out4.dat");
}

//Closes infile file
//pre   : infile file is open
//post  : infile file is closed
//param : infile
//return: NA
//usage : CloseInputFile(infile);
void CloseInputFile(ifstream& infile){
    infile.close();
}

//Closes output file
//pre   : output file is open
//post  : output file is closed
//param : outfile
//return: NA
//usage : CloseOutputFile(outfile);
void CloseOutputFile(ofstream& outfile){
    outfile.close();
}

//Writes points used in graph to an output file
//pre   : output file is open
//post  : graph points are output to output file
//param : outfile
//param : arrayOfPoints This is a vector containing Points of the graph
//return: NA
//PrintPointsInOutput(outfile, vectorOfGraphPoints);
void PrintPointsInOutput(ofstream& outfile, vector<Point>arrayOfPoints)
{
    cout << "The output has also been printed in a file named \"out4.dat\"\n";
    outfile << "These are the points on the graph:" << endl;
    for (int i = 0; i < arrayOfPoints.size(); i++)
    {
        Point tempPoint = arrayOfPoints[i];
        outfile << "P" << i << ": (" << setw(2) << tempPoint.x;
        outfile << ", " << setw(2) << tempPoint.y;
        outfile << ")" << endl; 
    }
    outfile << "\n\nThe extreme points are: \n"; 
}

//Writes data to open output file
//pre   : output file is open
//post  : data is output to output file
//param : outfile
//param : point1, struct Point that contains an x and y coordinate
//param : point2, struct Point that contains an x and y coordinate
//param : i, index of first extreme point
//param : j index of next extreme point
//return: NA
//usage : PrintToOutputFile(outfile, point1, point2, i, j);
void PrintToOutputFile(ofstream& outfile, Point point1, Point point2, int i, int j){
    cout << "P" << i << ": (" << setw(2);
    cout << point1.x << ", " << setw(2) << point1.y;
    cout << ") and P" << j << ": (" << setw(2);
    cout << point2.x << ", " << setw(2) << point2.y << ") " << endl;
    
    outfile << "P" << i << ": (" << setw(2) << point1.x << ", ";
    outfile << setw(2) << point1.y;
    outfile << ") and P" << j << ": (" << setw(2) << point2.x;
    outfile << ", " << setw(2) << point2.y << ") " << endl; 
}
