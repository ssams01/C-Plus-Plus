/*
 * Name: Stephen Sams
 * Date Submitted: 04/19/2021
 * Lab Section: 002
 * Assignment Name: Lab 10 - Using Breadth-first Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

//Function is designed to build a graph of possible states that connects every valid state in the puzzle with its neighboring states according
//to the moves possile
void build_graph(void) {
    int i = 0; 
    int j = 0;
    
    for (i = 0; i < 16; i++) {
        vector<int> stateVector; //meant to store the 16 possible states
        
        for (j = 0; j < 16; j++) {
            string neighborString = neighbor_label(i,j); //initializes the value of "neighborString" with the "label" created from the call to
                                                         //the neighbor_label() function                                             
 
            if (neighborString != "") { //(for next 2 lines): checks to see if the string is empty and if so, then checks to see if we aren't
                                        //on iteration 3,6,7,8,9, or 12 of the inner for loop counter "j"
                if (j != 3 && j != 6 && j != 7 && j != 8 && j != 9 && j != 12) {
                    edge_label.insert(pair<pair<int, int>, string>(pair<int, int>(i,j), neighborString));
                  
                    stateVector.push_back(j); //pushes the element to the "back" of our vector "stateVector"
                }
            }
        }
        nbrs.insert(pair<int, vector<int> >(i,stateVector)); //inserts the pair "i" and the our vector "stateVector" into the "nbrs" map
    } 
}

int main(void)
{
  build_graph();

  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
 