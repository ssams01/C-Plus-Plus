/*
 * Name: Stephen Sams
 * Date Submitted: 04/02/2021
 * Lab Section: 002
 * Assignment Name: Lab 8 - Storing a Sequence into a Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = nullptr; }
};

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

/*
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}
*/

// insert value v at rank r
Node *insert(Node *T, int v, int r) {
	int rankOfRoot = 0;
	
	if (T != nullptr) { //checks to see first if the tree exists and if so then, checks to see if the left side of the Tree exists and if so 
	                    //assigns the "rankOfRoot" with the size of the left side of the Tree.  Though if it dosen't exists assigns it with 0.
		rankOfRoot = T->left ? T->left->size : 0;
	}
  
    if (T == nullptr) { //checks to see if the tree exists and if dosen't returns a new Node with the passed in value "v"
        return new Node(v);
    }
    
	if (r <= rankOfRoot) { //checks to see if the passed in rank "r" is less than or equal to the "rankOfRoot" then insert "v" on the left side
	                       //of the tree...
	    T->left = insert(T->left, v, r);
	}
	else { //...otherwise if the passed in rank "r" is greater than the "rankOfRoot", insert "v" on the right side of the tree
	    T->right = insert(T->right, v, r - rankOfRoot - 1);
	}
	
	fix_size(T); //calls fix_size to adjust the size of T after the insertion
	
	return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R) {
    int rankOfRoot = 0;
    
    if (T != nullptr) { //checks to see first if the tree exists and if so then, checks to see if the left side of the Tree exists and if so 
	                    //assigns the "rankOfRoot" with the size of the left side of the Tree.  Though if it dosen't exists assigns it with 0.
		rankOfRoot = T->left ? T->left->size : 0;
	}
    
    if (T == nullptr) { //checks to see if the tree exists and if not sets L and R to nullptr and then returns
	    *L = nullptr;
	    *R = nullptr;
	  
	    return;
    }
  
    if (r <= rankOfRoot) { //check's to see if the passed in rank "r"'s value is less than that of the "rankOfRoot" and if so recursively calls
                          //split on the left side and on the left subtree (which R can now be ignored)... 
  
  	    split(T->left, r, L, &T->left);
   	  
  	    *R = T; //points R to T
	  
	    fix_size(T); //calls fix_size to adjust the size of T after the split
    }
    else { //...or if the passed in rank "r"'s value is greater than that of the "rankOfRoot" recursively calls split() on the right side and  
          //on the right subtree (which L can now be ignored)
  	  
  	    split(T->right, r - rankOfRoot - 1, &T->right, R); 
  	  
  	    *L = T; //points L to T
	 
	    fix_size(T); //calls fix_size to adjust the size of T after the split
    }
}

// insert value v at rank r
Node *insert_random(Node *T, int v, int r) {
    int rankOfRoot = 0;
    
    if (T != nullptr) { //checks to see first if the tree exists and if so then, checks to see if the left side of the Tree exists and if so 
	                    //assigns the "rankOfRoot" with the size of the left side of the Tree.  Though if it dosen't exists assigns it with 0.
		rankOfRoot = T->left ? T->left->size : 0;
	}
    
    int randomValue = rand(); //generates a random value
    // BASECASE 
    if (T == nullptr) { //checks to see if the tree exists and if not initializes a random seed and returns a new node with the value of "v"
                        //passed in...
  
	    srand (time(NULL));
  	
  	    return new Node(v);
    }
    else if (T) { //...though if the tree exists, mod "randomValue" by the size of tree plus 1
  	    randomValue = randomValue % (T->size + 1);
    }
  
    if (randomValue == 0) { //checks to see if the value of "randomValue" and if so sets the new number being added as the root, though if not                     //...
  	  
  	    Node* newNode = new Node(v); //creates a new node, allocates memory for it and assigns it the value of "v"
  	  
  	    split(T, r, &newNode->left, &newNode->right); //calls the split function in order to split the tree and set the resulting left and 
  	                                                //right tree's as the children of a new node
  	  
  	    fix_size(newNode); //calls fix_size to adjust the size of newNode after the split
  	  
  	    return newNode;
    }
    else { //...recursively call insert_random() on the left or right side of the tree respectively
  
  	    if (r <= rankOfRoot) { //check's to see if the passed in key "k"'s value is less than that of T's key and if so recursively calls  
                              //insert_random() on T's left...
  	  	    T->left = insert_random(T->left, v, r);
  	  	
  	  	    fix_size(T); //calls fix_size to adjust the size of T after the insertion
  	  	
  	  	    return T;
  	    }
  	    else { //...or if the passed in rank "r"'s value is greater than that of the "rankOfRoot" recursively calls insert_random on T's right
  	  	    T->right = insert_random(T->right, v, r - rankOfRoot - 1);
  	  	
  	  	    fix_size(T); //calls fix_size to adjust the size of T after the insertion
  	  	
  	  	    return T;
  	    }
    }
}

// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n) {
  Node *T = nullptr;

  // start by inserting the first team
  T = insert_random(T, 0, 0);

  // now insert the other teams...
  for (int i=1; i<n; i++) {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key)) {// can we insert at beginning?
        T = insert_random(T, i, 0);
    }
    else if (did_x_beat_y(select(T,T->size-1)->key, i)) { // can we insert at end?
	    T = insert_random(T, i, T->size);
    }
    else {
	    // 7 5 4 2 0 3 1 6    (when inserting team i=8)
	    // W W W L L L W L
        int treeStart = 0; 
        int treeEnd = T->size - 1;

        while (treeStart + 1 != treeEnd) {
            int treeMidpoint = (treeEnd + treeStart)/2; //calculates the midpoint of the tree and stores it int the create variable
            
            if (did_x_beat_y(select(T,treeMidpoint)->key, i)) { //calls the did_x_beat_y() function passing in T and the midpoint 
                                                                //and the element "i" and if the midpoint "beats" element "i" the replace the
                                                                //start (treeStart) with the midpoint (treeMidpoint)...
                treeStart = treeMidpoint;
            }
            else { //...though if the midpoint "loses" to element "i" update the end (treeEnd) with the midpoint (treeMidpoint)
                treeEnd = treeMidpoint;
            }
        }
        T = insert_random(T, i, treeEnd); //whenever the while condition is met, insert "i" into the position in the tree represented by
                                          //"treeEnd"
    }
  }

  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

int main(void)
{
  vector<int> inorder;
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
    
  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
    //    inorder=inorder_traversal(S);
    //    printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}
