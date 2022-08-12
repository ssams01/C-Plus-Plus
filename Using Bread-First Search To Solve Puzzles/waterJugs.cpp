/*
 * Name: Stephen Sams
 * Date Submitted: 04/19/2021
 * Lab Section: 002
 * Assignment Name: Lab 10 - Using Breadth-First Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
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

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

//Function is designed to build a graph of possible states that connects every valid state in the puzzle with its neighboring states according
//to the moves possile
void build_graph(void) {
    int firstJug = 3; //(for next 2 lines): initializes the "firstJug" with its size of 3 and the "secondJug" with its size of 4
    int secondJug = 4; 
    
    state currentState = make_pair(0,0); //intializes the "currentState" with two 0s
    
    state finalState = make_pair(firstJug, firstJug); //creates a "finalState" using the size limits of our two water jugs
    
    while(currentState != finalState) { //loop designed to run as long as our "currentState" doesn't equal our "finalState"
        state nextState;
		
        nextState = make_pair(firstJug,currentState.second); //(for next 5 lines [including this one]): performs action 1: which is to fill 
                                                             //jug A (firstJug)
		
		if(currentState != nextState) { //checks to see if the "currentState" equals the "nextState" and if not preforms the action 
			
			pair<state,state> graphEdge = make_pair(currentState,nextState); //creates an "graphEdge" containing the "currentState" and the
			                                                                 //"nextstate"
			
			nbrs[currentState].push_back(nextState); //adds the "nextState" to the "currentState" of neighboring vectors
			
			edge_label[graphEdge] = actions[0]; //labels the "graphEdge" with the phrase "Fill A" by assigning the first element of the 
			                                    //"actions" array
		}
		
		nextState = make_pair(currentState.first,secondJug); //(for next 5 lines [including this one]): performs action 2: which is to fill 
                                                             //jug B (secondJug)
	
		if(currentState != nextState) { //checks to see if the "currentState" equals the "nextState" and if not preforms the action
			
		    pair<state,state> graphEdge = make_pair(currentState,nextState); //creates an "graphEdge" containing the "currentState" and the
			                                                                 //"nextstate"
		    
		    nbrs[currentState].push_back(nextState); //adds the "nextState" to the "currentState" of neighboring vectors
		    
		    edge_label[graphEdge] = actions[1]; //labels the "graphEdge" with the phrase "Fill B" by assigning the second element of the
			                                    //"actions" array
		}
		
		nextState = make_pair(0,currentState.second); //(for next 5 lines [including this one]): performs action 3: which is to empty
                                                      //jug A (firstJug)
		
		if(currentState != nextState) { //checks to see if the "currentState" equals the "nextState" and if not preforms the action
		    
			pair<state,state> graphEdge = make_pair(currentState,nextState); //creates an "graphEdge" containing the "currentState" and the
			                                                                 //"nextstate"
			
			nbrs[currentState].push_back(nextState); //adds the "nextState" to the "currentState" of neighboring vectors
			
		    edge_label[graphEdge] = actions[2]; //labels the "graphEdge" with the phrase "Empty A" by assigning the third element of the 
			                                    //"actions" array
		}
		
		nextState = make_pair(currentState.first,0); //(for next 5 lines [including this one]): performs action 4: which is to empty
                                                     //jug B (secondJug)
		
		if(currentState != nextState) { //checks to see if the "currentState" equals the "nextState" and if not preforms the action
		    
			pair<state,state> graphEdge = make_pair(currentState,nextState); //creates an "graphEdge" containing the "currentState" and the
			                                                                 //"nextstate"
			
			nbrs[currentState].push_back(nextState); //adds the "nextState" to the "currentState" of neighboring vectors
			
		    edge_label[graphEdge] = actions[3]; //labels the "graphEdge" with the phrase "Empty B" by assigning the fourth element of the 
			                                    //"actions" array
		}
		int adjustFirstJug = currentState.first; //(for the next 11 lines [including this one]): performs action 5: which is to pour 
		                                         //jug A (firstJug) into jug B (secondJug)
		                                         
		int adjustSecondJug = currentState.second; //(for this line and the previous line): initializes "adjustFirstJug" and "adjustSecondJug"
		                                           //with the first and second element of the "currentState" respectivley
		
		if(currentState.second < secondJug) { //checks to see if the second element in the "currenState" is less than the size of the 
		                                      //"secondJug" and if so performs the action
		                                      
			while(adjustFirstJug > 0 && adjustSecondJug < secondJug) { //loop is designed to continuouslly "add water" to the "secondJug" and
			                            //"remove water" from the "firstJug" until the "firstJug" is empty or until the "secondJug" is full
			    adjustSecondJug++;
			    adjustFirstJug--;
			}
	        nextState = make_pair(adjustFirstJug,adjustSecondJug); //assigns the "nextState" with result of pouring the "firstJug" into the 
	                                                               //"secondJug"
                                                     
			if(currentState != nextState) { //checks to see if the "currentState" equals the "nextState" and if not preforms the action
			    
				pair<state,state> graphEdge = make_pair(currentState,nextState); //creates an "graphEdge" containing the "currentState" and the
			                                                                     //"nextstate"
				 
				nbrs[currentState].push_back(nextState); //adds the "nextState" to the "currentState" of neighboring vectors
				
				edge_label[graphEdge] = actions[4]; //labels the "graphEdge" with the phrase "Pour A->B" by assigning the fifth element of the
			                                        //"actions" array
			}
		}
	    adjustFirstJug = currentState.first; //(for the next 11 lines [including this one]): performs action 6: which is to pour 
		                                    //jug B (secondJug) into jug A (firstJug)
		                                    
	    adjustSecondJug = currentState.second; //(for this line and the previous line): initializes "adjustFirstJug" and "adjustSecondJug"
		                                      //with the first and second element of the "currentState" respectivley
	   
	    if(currentState.first < firstJug) { //checks to see if the first element in the "currenState" is less than the size of the 
		                                   //"firstJug" and if so performs the action
		                                      
			while(adjustFirstJug < firstJug && adjustSecondJug > 0) { //loop is designed to continuouslly "add water" to the "firstJug" and
			                            //"remove water" from the "secondJug" until the "secondJug" is empty or until the "firstJug" is full
			    adjustFirstJug++;
			    adjustSecondJug--;
			}
			nextState = make_pair(adjustFirstJug,adjustSecondJug); //assigns the "nextState" with result of pouring the "secondJug" into the 
	                                                               //"firstJug"
		
			if(currentState != nextState) { //checks to see if the "currentState" equals the "nextState" and if not preforms the action
			    
				pair<state,state> graphEdge = make_pair(currentState,nextState); //creates an "graphEdge" containing the "currentState" and the
			                                                                     //"nextstate"
				
				nbrs[currentState].push_back(nextState); //adds the "nextState" to the "currentState" of neighboring vectors
				
			    edge_label[graphEdge] = actions[5]; //labels the "graphEdge" with the phrase "Pour B->A" by assigning the sixth element of the
			                                        //"actions" array
			}
	    }
		if(currentState.second == secondJug) { //checks to see if the second element of the "currentState" is equal to the size of the 
		                                       //"secondJug" and if so...
			
			currentState = make_pair(currentState.first + 1, 0); //...adds 1 to the "currenState"'s first element and resets its second element
			                                                     //to 0...
		}
		else { //...though if not, adds 1 to the "currentState"'s second element
			currentState = make_pair(currentState.first, currentState.second + 1);
		}
	}
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
