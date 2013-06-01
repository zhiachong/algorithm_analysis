#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

const char RED[] = "\033[22;31m"; //sets the output to red
const char RESET[] = "\033[0m"; //resets to white color

//this is a C-struct called Point to represent x and y coordinates
struct Point {
    int x, y;
};

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
void OpenInputFile(ifstream& infile) throw (exception);

//@this function reads items from a file and inserts it
//@into a tree 
//@pre infile is open, and tree are assigned
//@post inputs data from file into tree
//@param infile
//@param item
//@usage GetInputFromFile(infile, item);
void GetInputFromFile(ifstream& infile, vector<Point>& item);

//@this function closes the textfile
//@post textfile is closed
//@param infile
//@usage CloseInputFile(infile);
void CloseInputFile(ifstream& infile);

bool IsCounterClockWise(Point beginPoint, Point endPoint, Point third);

void PrintArray(vector<Point> array);

double FindDeterminantSquared(Point first, Point second, Point max);

bool FindPointWithMaxDistance(vector<Point> array, Point& maxPoint);

//finds the top and bottom halves of the set
//returns a vector with ONLY 2 vectors inside. The first in the vector will be
//        the left set, the second the right set.
//usage:  vector<vector<Point>> topbottom = FindTopBottom(mList);
vector< vector<Point> > FindTopBottomSets(vector<Point> set, Point begin, Point end);

vector<Point> ConcatLists(vector<Point> v1, vector<Point> v2);

vector<Point> FindHull(vector<Point> s1);

vector<Point> FindSubset(vector<Point> originalArray, Point begin, Point end);

int main()
{
    ifstream infile;
    OpenInputFile(infile);
    vector<Point> mList;

    GetInputFromFile(infile, mList);
    CloseInputFile(infile);
    PrintLines(2);
    cout << "***Sorting Data Input***" << endl;
    MergeSort(mList, 0, mList.size() - 1);
    cout << "       DONE" << endl;
	
    PrintArray (mList);
    cout << "Size: " << mList.size() << endl;
	
   
}

vector<Point> FindHull(vector<Point> s1)
{
	Point pMax;
	vector<Point> result;
	if (FindPointWithMaxDistance(s1, pMax))
	{
		Point begin = s1.front();
		vector<Point> s1Left = FindSubset(s1, begin, pMax);
		vector< vector<Point> > p1_To_pMax = FindTopBottomSets(s1Left, begin, pMax);
	
		Point end = s1.back();
		vector<Point> s1Right = FindSubset(s1, pMax, end);		
		vector< vector<Point> > pMax_To_pEnd = FindTopBottomSets(s1Right, pMax, end);
	
		vector<Point> left = p1_To_pMax.front();
		vector<Point> right = pMax_To_pEnd.front();
		vector<Point> leftHull, rightHull;
		
		
		leftHull = FindHull(left);
		rightHull = FindHull(right);
		
		result = ConcatLists(leftHull, rightHull);
		return result;
	} else {
		return s1;
	}
}

//usage: Point temp = FindPointWithMaxDistance(s2);
bool FindPointWithMaxDistance(vector<Point> array, Point& maxPoint)
{
	if (array.size() <= 2)
		return false;
	Point first = array.front();
	Point last = array.back();
	double maxDistance = 0;
	for (int i = 1; i < array.size() - 1; i++)
	{
		double temp = FindDeterminantSquared(first, last, array[i]);
		if (temp >= maxDistance)
		{
			maxPoint = array[i];
			maxDistance = temp;
		}	
	}
	return true;
}

//usage: vector<Point> concat = ConcatLists(leftSet, rightSet);
vector<Point> ConcatLists(vector<Point> v1, vector<Point> v2)
{
	vector<Point> newList;
	newList.reserve(v1.size() + v2.size()); //reserve space that is big enough for two vectors
	newList.insert(newList.end(), v1.begin(), v1.end()); //puts v1 into the newList
	newList.insert(newList.end(), v2.begin(), v2.end()); //puts v2 into the newList
	return newList;
}


double FindDeterminantSquared(Point first, Point second, Point max)
{
	double firstD = first.x * (second.y - max.y);
	double secondD = first.y * (second.x - max.x);
	double thirdD = second.x * max.y - max.x * second.y;
	double result = (firstD - secondD + thirdD);
	
    return result * result;
}

void PrintArray(vector<Point> array)
{
	for (int i = 0; i < array.size(); i++)
    {
        Point temp = array.at(i);
        cout << "x: " << temp.x << " y: " << temp.y << endl;
    } 
}

//finds the top and bottom halves of the set
//returns a vector with ONLY 2 vectors inside. The first in the vector will be
//        the left set, the second the right set.
//usage:  vector<vector<Point>> topbottom = FindTopBottom(mList);
vector< vector<Point> > FindTopBottomSets(vector<Point> set, Point begin, Point end)
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

      if (IsCounterClockWise(extremePoint1, extremePoint2, temp))
      {
        leftSet.push_back(temp);
      } else
      {
        rightSet.push_back(temp);
      }
    }
    rightSet.push_back(extremePoint2);
    leftSet.push_back(extremePoint2);

    finalSet.push_back(leftSet);
    finalSet.push_back(rightSet);
    return finalSet;
}

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

//algorithm from http://stackoverflow.com/questions/1165647/how-to-determine-if-a-list-of-polygon-points-are-in-clockwise-order
//the idea is we add all the 3 edges connecting the points together
//if the sum is positive, it is a clockwise cycle
//else, counterclockwise
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
    for(; (first1 <= last1) && (first2 <= last2); index++)
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
void OpenInputFile(ifstream& infile) throw (exception)
{
    try {
        infile.open("in5.dat");
    } 
    catch (exception de)
    {
      cout << de.what() << endl;
    }
}

//@this function reads items from a file and inserts it
//@into a tree 
//@pre infile is open, and tree are assigned
//@post inputs data from file into tree
//@param infile
//@param item
//@usage GetInputFromFile(infile, item);
void GetInputFromFile(ifstream& infile, vector<Point>& item)
{
    Point temp;
    while (!infile.eof())
    {
        infile >> temp.x;
        infile >> temp.y;
        item.push_back(temp);
    }
}

//@this function closes the textfile
//@post textfile is closed
//@param infile
//@usage CloseInputFile(infile);
void CloseInputFile(ifstream& infile)
{
    infile.close();
}
