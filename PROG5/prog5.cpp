//@file: prog5.cpp (submitted by mrumbaua)
//@author: Marvin Rumbaua (mrumbaua), Zhia Chong (zchong)
//@date: 03/27/13
//@description: Calculates the extreme points of a set of data points and displays the edges and associated points for the Quick Hull Problem

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

const char RED[] = "\033[22;31m"; //sets the output to red
const char RESET[] = "\033[0m"; //resets to white color
const char GREEN[] = "\033[22;32m"; //sets the output to green

//this is a C-struct called Point to represent x and y coordinates
struct Point {
    int x, y;
};
enum Direction {top, bottom};

//@MergeSort sorts an array
//@pre list exists, begin and end are assigned
//@post recursively sortes the list
//@param list
//@param begin
//@param end
//@usage MergeSort(list, begin, end);
void MergeSort(vector<Point>& list, int begin, int end);

//@merges two separate sublists together
//@pre list exists, first, mid and last are assigned
//@post merges two sublists together in order
//@param list
//@param first
//@param mid
//@param last
//@usage Merge(list, first, mid, last);
void Merge(vector<Point>& list, int first, int mid, int last);

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
vector<Point> GetInputFromFile(ifstream& infile);

//@this function closes the textfile
//@post textfile is closed
//@param infile
//@usage CloseInputFile(infile);
void CloseInputFile(ifstream& infile);

//@algorithm from http://stackoverflow.com/questions/1165647/how-to-determine-if-a-list-of-polygon-points-are-in-clockwise-order
//@the idea is we add all the 3 edges connecting the points together
//@if the sum is positive, it is a clockwise cycle
//@else, counterclockwise
//@pre beginPoint, endPoint, and third exist and are assigned values
//@post N/A
//@param beginPoint, the starting point of the line
//@param endPoint, the ending point of the line
//@param third, point being evaluated
//@return true if point is counter clockwise, else false//@usage:  vector<vector<Point>> topbottom = FindTopBottomSets(mList, mList.front(), mList.back(), top);
bool IsCounterClockWise(Point beginPoint, Point endPoint, Point third);

//@prints array
//@pre an array exists
//@post outputs elements in array
//@param array
//@return N/A
//@usage PrintArray(final);
void PrintArray(vector<Point> array);

//@finds the determinant squared value of a given point perpendicular to a given line
//@pre first, second and max are assigned values
//@post N/A
//@param first, beginning point of a line
//@param second, end point of a line
//@param max, point being evaluated
//@return determinant squared value
//@usage double temp = FindDeterminantSquared(first, last, array[i]);
double FindDeterminantSquared(Point first, Point second, Point max);

//@checks for a valid max distance
//@pre array and maxpoint exist
//@post maxPoint is assigned a value
//@param array, list of points
//@param maxPoint, the point that is the furthest from the line perpendicularly
//@return true if a valid max distance exists, else false
//@usage if (FindPointWithMaxDistance(s1, pMax))

bool FindPointWithMaxDistance(vector<Point> array, Point& maxPoint);

//@finds the top and bottom halves of the set
//@pre set, begin, end and half are assigned values
//@post N/A
//@param set, array of points
//@param begin, starting point of line
//@param end, ending point of line
//@param half, direction (top or bottom half)
//@returns a vector with ONLY 2 vectors inside. The first in the vector will be
//@        the left set, the second the right set.
//@usage:  vector<vector<Point>> topbottom = FindTopBottomSets(mList, mList.front(), mList.back(), top);
vector< vector<Point> > FindTopBottomSets(vector<Point> set, Point begin, Point end, Direction half);

//@combines two lists
//@pre v1 and v2 exist and are assigned elements
//@post N/A
//@param v1, list of points
//@param v2, list of points
//@return concatonated list
//@usage vector<Point> final = ConcatLists(leftHull, rightHull);
vector<Point> ConcatLists(vector<Point> v1, vector<Point> v2);

//@recursively finds the extreme points that make its convex hull
//@pre s1 contains points, half is assigned a direction
//@post N/A
//@param s1, array of points
//@param half, direction of hull
//@return an array of extreme points that connect to make the hull
//@usage vector<Point> leftHull = FindHull(left, tophalf);
vector<Point> FindHull(vector<Point> s1, Direction half);

//@finds subset of array of points given beginning and end extreme points
//@pre originalArray contains elements, begin and end are assigned values
//@post N/A
//@param originalArray, array of points
//@param begin, beginning point
//@param end, end point
//@return subset of points
//@usage vector<Point> s1Left = FindSubset(s1, begin, pMax);
vector<Point> FindSubset(vector<Point> originalArray, Point begin, Point end);

//@Displays sorting banner
//@pre none
//@post banner is output
//@param N/A
//@return N/A
//@usage DisplaySortingBanner();
void DisplaySortingBanner();

int main()
{
    ifstream infile;
    bool fileOK;
    OpenInputFile(infile, fileOK);
    vector<Point> mList = GetInputFromFile(infile);
    CloseInputFile(infile);

    if(fileOK)
    {
        DisplaySortingBanner();
	MergeSort(mList, 0, mList.size() - 1);

	Direction tophalf = top;
	Direction bottomhalf = bottom;

	vector< vector<Point> > topBottom = FindTopBottomSets(mList, mList[0], mList[mList.size() - 1], tophalf);
	vector<Point> left = topBottom[0];
	vector<Point> right = topBottom[1];

	vector<Point> leftHull = FindHull(left, tophalf);
	vector<Point> rightHull = FindHull(right, bottomhalf);

	vector<Point> final = ConcatLists(leftHull, rightHull);
	PrintArray(final);
    } else {
        cout << "File not found!" << endl;
    }

    return 0;

}

//@Displays sorting banner
//@pre none
//@post banner is output
//@param N/A
//@return N/A
//@usage DisplaySortingBanner();
void DisplaySortingBanner(){

    system ( "clear" );

    cout << GREEN << "****************************************" << RESET << endl;
	cout << GREEN <<   "** " << RED << "Sorting Input Data with Merge Sort " << GREEN << "**" << RESET << endl;
	cout << GREEN << "****************************************" << RESET << endl;
}

//@recursively finds the extreme points that make its convex hull
//@pre s1 contains points, half is assigned a direction
//@post N/A
//@param s1, array of points
//@param half, direction of hull
//@return an array of extreme points that connect to make the hull
//@usage vector<Point> leftHull = FindHull(left, tophalf);
vector<Point> FindHull(vector<Point> s1, Direction half)
{
    Point pMax;
    vector<Point> result;//@post maxPoint is assigned a value
    if (FindPointWithMaxDistance(s1, pMax))
    {
	Point begin = s1.front();
	Point end = s1.back();
	if (half == top)
	{
	    vector<Point> s1Left = FindSubset(s1, begin, pMax);
	    vector< vector<Point> > p1_To_pMax = FindTopBottomSets(s1Left, begin, pMax, half);	
	    vector<Point> s1Right = FindSubset(s1, pMax, end);		
	    vector< vector<Point> > pMax_To_pEnd = FindTopBottomSets(s1Right, pMax, end, half);
	    vector<Point> left = p1_To_pMax.front();
	    vector<Point> right = pMax_To_pEnd.front();
	    vector<Point> leftHull, rightHull;
	    leftHull = FindHull(left, half);
	    rightHull = FindHull(right, half);
	    result = ConcatLists(leftHull, rightHull);
	} else if (half == bottom) {
    	    vector<Point> s1Left = FindSubset(s1, pMax, end);
	    vector< vector<Point> > pMax_To_pEnd = FindTopBottomSets(s1Left, pMax, end, half);
	    vector<Point> s1Right = FindSubset(s1, begin, pMax);		
	    vector< vector<Point> > p1_To_pMax = FindTopBottomSets(s1Right, begin, pMax, half);
	    vector<Point> left = pMax_To_pEnd[0];
	    vector<Point> right = p1_To_pMax[0];
	    vector<Point> leftHull, rightHull;
	    leftHull = FindHull(left, half);
	    rightHull = FindHull(right, half);
	    result = ConcatLists(rightHull, leftHull);
	}
        return result;
	} else {
	    return s1;
	}
}

//@checks for a valid max distance
//@pre array and maxpoint exist
//@post maxPoint is assigned a value
//@param array, list of points
//@param maxPoint, the point that is the furthest from the line perpendicularly
//@return true if a valid max distance exists, else false
//@usage if (FindPointWithMaxDistance(s1, pMax))
bool FindPointWithMaxDistance(vector<Point> array, Point& maxPoint)
{
    bool validPoint = true;
    if (array.size() <= 2)
	validPoint = false;
    if (validPoint) {
	Point first = array.front();
	Point last = array.back();
	double maxDistance = 0.0;
	for (int i = 1; i < array.size() - 1; i++)
	{
	    double temp = FindDeterminantSquared(first, last, array[i]);
	    if (temp >= maxDistance)
	    {
	        maxPoint = array[i];
	        maxDistance = temp;
	    }	
	}
    }
	
    return validPoint;
}

//@combines two lists
//@pre v1 and v2 exist and are assigned elements
//@post N/A
//@param v1, list of points
//@param v2, list of points
//@return concatonated list
//@usage vector<Point> final = ConcatLists(leftHull, rightHull);
vector<Point> ConcatLists(vector<Point> v1, vector<Point> v2)
{
    vector<Point> newList;
    newList.reserve(v1.size() + v2.size()); //reserve space that is big enough for two vectors
    newList.insert(newList.end(), v1.begin(), v1.end()); //puts v1 into the newList
    newList.insert(newList.end(), v2.begin(), v2.end()); //puts v2 into the newList
    return newList;
}

//@finds the determinant squared value of a given point perpendicular to a given line
//@pre first, second and max are assigned values
//@post N/A
//@param first, beginning point of a line
//@param second, end point of a line//@usage:  vector<vector<Point>> topbottom = FindTopBottom(mList);
//@param max, point being evaluated
//@return determinant squared value
//@usage double temp = FindDeterminantSquared(first, last, array[i]);
double FindDeterminantSquared(Point first, Point second, Point max)
{
    double firstD = first.x * (second.y - max.y);
    double secondD = first.y * (second.x - max.x);
    double thirdD = second.x * max.y - max.x * second.y;
    double result = (firstD - secondD + thirdD);
	
    return result * result;
}

//@prints array
//@pre an array exists
//@post outputs elements in array
//@param array
//@return N/A
//@usage PrintArray(final);
void PrintArray(vector<Point> array)
{
    int j = 1;//@usage:  vector<vector<Point>> topbottom = FindTopBottomSets(mList, mList.front(), mList.back(), top);
    for (int i = 0; i < array.size(); i+=2)
    {
	cout << " Edge:" << GREEN << setw(3) << j++ << RESET << " -> ";
        Point temp = array.at(i);
        cout << RED << setw(4) << "P(" << setw(2) << temp.x << ", " << setw(2) << temp.y << ")";
        Point temp2 = array.at(i+1);
        cout << RESET << "  &  " << RED << "P(" << setw(2) << temp2.x << ", " << setw(2) << temp2.y << ")" << RESET << endl;
    } 
}

//@finds the top and bottom halves of the set
//@pre set, begin, end and half are assigned values
//@post N/A
//@param set, array of points
//@param begin, starting point of line
//@param end, ending point of line
//@param half, direction (top or bottom half)
//@returns a vector with ONLY 2 vectors inside. The first in the vector will be
//@        the left set, the second the right set.
//@usage:  vector<vector<Point>> topbottom = FindTopBottomSets(mList, mList.front(), mList.back(), top);
vector< vector<Point> > FindTopBottomSets(vector<Point> set, Point begin, Point end, Direction half)
{
    Point extremePoint1 = begin;
    Point extremePoint2 = end;
    vector<Point> rightSet;
    vector<Point> leftSet;
    rightSet.push_back(extremePoint1);
    leftSet.push_back(extremePoint1);

    vector< vector<Point> > finalSet;

    for (int i = 1; i < set.size() - 1; i++)
    {
        Point temp = set[i];

        if (half == top && IsCounterClockWise(extremePoint1, extremePoint2, temp))
        {
            leftSet.push_back(temp);
        } else if (half == bottom && IsCounterClockWise(extremePoint2, extremePoint1, temp)) {
            leftSet.push_back(temp);
        } else {
	    rightSet.push_back(temp);
	}
    }
    rightSet.push_back(extremePoint2);
    leftSet.push_back(extremePoint2);
	
    finalSet.push_back(leftSet);
    finalSet.push_back(rightSet);
    return finalSet;
}

//@finds subset of array of points given beginning and end extreme points
//@pre originalArray contains elements, begin and end are assigned values
//@post N/A
//@param originalArray, array of points
//@param begin, beginning point
//@param end, end point
//@return subset of points
//@usage vector<Point> s1Left = FindSubset(s1, begin, pMax);
vector<Point> FindSubset(vector<Point> originalArray, Point begin, Point end)
{	
    if (originalArray.size() == 2)
    {
	vector<Point> subset;
	subset.push_back(begin);
	subset.push_back(end);
	return subset;
    }
    bool endNotFound = true, beginNotFound = true;
    vector<Point> subset;
    int start = 0;
    Point beginningPoint = originalArray[start];
	
    while (!(beginningPoint.x == begin.x && beginningPoint.y == begin.y))
    {
	start++;
	beginningPoint = originalArray[start];
    }
	
    subset.push_back(beginningPoint);

    for (int i = start + 1; i < originalArray.size() && endNotFound; i++)
    {
	Point temp = originalArray[i];
	subset.push_back(temp);
	if (temp.x == end.x && temp.y == end.y)
	{
	    endNotFound = false;
	} 
    }
    return subset;
}

//@algorithm from http://stackoverflow.com/questions/1165647/how-to-determine-if-a-list-of-polygon-points-are-in-clockwise-order
//@the idea is we add all the 3 edges connecting the points together
//@if the sum is positive, it is a clockwise cycle
//@else, counterclockwise
//@pre beginPoint, endPoint, and third exist and are assigned values
//@post N/A
//@param beginPoint, the starting point of the line
//@param endPoint, the ending point of the line
//@param third, point being evaluated
//@return true if point is counter clockwise, else false
bool IsCounterClockWise(Point beginPoint, Point endPoint, Point third)
{
    int edge1 = (third.x - endPoint.x) * (third.y + endPoint.y);
    int edge2 = (beginPoint.x - third.x) * (beginPoint.y + third.y);
    int edge3 = (endPoint.x - beginPoint.x) * (endPoint.y + beginPoint.y);
    int sum   = edge1 + edge2 + edge3;
    return (sum <= 0);
}

//@MergeSort sorts an array
//@pre list exists, begin and end are assigned
//@post recursively sortes the list
//@param list
//@param begin
//@param end
//@usage MergeSort(list, begin, end);
void MergeSort(vector<Point>& list, int begin, int end)
{
    if (begin < end)
    {
       int middle = (begin + end) / 2;
       MergeSort(list, begin, middle);
       MergeSort(list, middle+1, end);
       Merge(list, begin, middle, end);
    } 
}

//@merges two separate sublists together
//@pre list exists, first, mid and last are assigned
//@post merges two sublists together in order
//@param list
//@param first
//@param mid
//@param last
//@usage Merge(list, first, mid, last);
void Merge(vector<Point>& list, int first, int mid, int last)
{
    vector<Point> tempArray;
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = first1;
  
    //determine which of the 2 arrays is smallest
    for(; (first1 <= last1) && (first2 <= last2); ++index)
    {
        Point fpoint = list[first1];
        Point spoint = list[first2];
        if (fpoint.x < spoint.x)
        {
            tempArray.push_back(fpoint);
            ++first1;
        } else if (fpoint.x == spoint.x)
        {
            if (fpoint.y < spoint.y)
            {
                tempArray.push_back(fpoint);
                first1++;
            }
            else 
            {
                tempArray.push_back(spoint);
                first2++;
            }
        } else {
            tempArray.push_back(spoint);
            first2++;
        }
    }
    
    //if any remains, place into the temp aray
    for (; first1 <= last1; ++ first1)
    {
        tempArray.push_back(list[first1]);
    }

    //if any remains, place into the temp array
    for(; first2 <= last2; ++first2)
    {
        tempArray.push_back(list[first2]);
    }

    int i = 0;
    //copy from temp array into original array   
    for (index = first; index <= last; index++)
    {
        Point x = tempArray.at(i);
        list[index] = x;
        i++;
    }
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
    infile.open("in5.dat");
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
vector<Point> GetInputFromFile(ifstream& infile)
{
    vector<Point> item;
    Point temp;
    while (!infile.eof())
    {
        infile >> temp.x;
        infile >> temp.y;
        item.push_back(temp);
    }
    return item;
}

//@this function closes the textfile
//@post textfile is closed
//@param infile
//@usage CloseInputFile(infile);
void CloseInputFile(ifstream& infile)
{
    infile.close();
}

