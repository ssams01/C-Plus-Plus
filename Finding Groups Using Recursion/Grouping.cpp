/*
 * Name: Stephen Sams
 * Date Submitted: 02/09/2021
 * Lab Section: 002
 * Assignment Name: Lab 3: Finding Groups Using Recursion
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
    private:
        int row, col;
    public:
        GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square
        GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square
        //Compare with == operator, used in test cases
        bool operator== (const GridSquare r) const
        {
            if ((row == r.row) && (col == r.col))
            {
                return true;
            }
            return false;
        }
        int getRow() { return row; } //return row value
        int getCol() { return col; } //return column value
        //Output using << operator, used in Grouping::printGroups()
        friend ostream& operator<< (ostream& os, const GridSquare obj);
};

//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

/*
Groups squares in 10x10 grid upon construction
Additional private helper functions may be added
Need to implement the constructor that takes a file name
as well as findGroup
The findGroup function's parameter list may be changed based
on how the function is implemented
*/
class Grouping
{
    private:
        int grid[10][10];
        vector<vector<GridSquare>> groups;
    public:
        Grouping() : grid{},groups() {} //Default constructor, no groups
        Grouping(string fileName); //Implement this function
        void findGroup(int r, int c); //Implement this function (recursive)
        void printGroups() //Displays grid's groups of squares
        {
            for(int g=0; g<groups.size(); g++)
            {
                cout << "Group " << g+1 << ": ";
                for(int s=0; s<groups[g].size(); s++)
                {
                    cout << " " << groups[g][s];
                }
                cout << endl;
            }
        }
        vector<vector<GridSquare>> getGroups() //Needed in unit tests
        {
            return groups;
        }
};

//Implement the (parameterized) constructor and findGroup functions below

//This is the parameterized constructor for the Grouping class, reads from the file into the grid[][] array (1 for X's and 0 for .'s'), and 
//then pushes the elements of the grid[][] array that contain a 1(X) to a vector to keep track where they are 
Grouping::Grouping(string fileName) {
    string inputFromFile = " ";
    ifstream fileInput(fileName);
    vector<GridSquare> xStorage; //used to indicate where an 1(X) was encountered
    int i = 0; //loop counter
    int j = 0; //loop counter
    int k = 0; //loop counter
    int l = 0; //loop couter
    const int MAX = 10; //the number of elements in grid array, used in loop conditions
    
    for(i = 0; i < MAX; i++) { //outer for loop get's input from the file
        getline(fileInput, inputFromFile); 
        for(j = 0; j < MAX; j++) { //checks to see if the current element in inputFromFile[] array is an 'X',and if so assigns the current 
                                   //element in the grid[][] array with 1, and if its a '.' assigns the current element in the grid[][] array
                                   //with a 0
            if(inputFromFile[j] == 'X') {
                grid[i][j] = 1;
            }
            else if(inputFromFile[j] == '.') {
                grid[i][j] = 0;
            }
        }
    }
    
    for(k = 0; k < MAX; k++) { //nested-for loop is designed to check if the curren element in the grid[][] array is a 1 and if so pushes 
                               //xStorage to the back of the groups vector and then calls the findGroup function
        for(l = 0; l < MAX; l++) {
            if(grid[k][l] == 1) {
                groups.push_back(xStorage);
                findGroup(k,l);
            }
        }
    }
}

//Function is designed to find groups within our grid[][] array through the use of recursive programming
void Grouping::findGroup(int r, int c) {
    const int UPPER_BOUND = 10; //highest valid number
    const int LOWER_BOUND = 0; //lowest valid number
    
    if(grid[r][c] == 0) { //if the passed in element of grid[][] array's value is 0, it exits the function
        return;
    }
    
    grid[r][c] = 0; //resets the current position so that, the base case will be triggered next time this GridSquare is encountered
    
    groups.back().push_back(GridSquare(r,c)); //accesses the most recent group using the .back() function and then pushes to the back of the
                                              //groups vector the result of a call to the GridSquare classe's parameterized constructor
    
    if((r + 1) < UPPER_BOUND) { //these 4 ifs statments are meant to check the "GridSquare" above,below, and beside the current "GridSquare"
                                //and if its within bounds then findGroup is called recursively in order to add new "GridSquare's" to the group
        findGroup(r + 1, c);
    }
    if((r - 1) >= LOWER_BOUND) {
        findGroup(r - 1, c);
    }
    if((c + 1) < UPPER_BOUND) {
        findGroup(r, c + 1);
    }
    if((c - 1) >= LOWER_BOUND) {
        findGroup(r, c - 1);
    }
}

//Simple main function to test Grouping
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}