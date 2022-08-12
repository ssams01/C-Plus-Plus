/*
 * Name: Stephen Sams
 * Date Submitted: 03/28/2021
 * Lab Section: 002
 * Assignment Name: Lab 7 - Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert> //was assert.h

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

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
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

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k) {
  if (T == nullptr) { //checks to see if the tree is empty, and if so returns nullptr
      return nullptr;
  }
  if (k == T->key) { //if the value at "k" matches the value of the current key, then return T
      return T; 
  }
  if (k < T->key) { //if node was not found, using recursion check the left side of the tree...
      return find(T->left, k);
  }
  else { //...or the right side of the tree
      return find(T->right, k);
  }
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r) {
  assert(T != nullptr && r >= 0 && r < T->size); //"asserts" that the tree isn't empty as well as to see if the rank is higher or equal to 0
  
  int rankOfRoot;
  
  if (T->left != nullptr) { //checks to see T's left exists and if so, assigns "rankOfRoot" with the rank of T's left...
  	rankOfRoot = T->left->size;
  }
  else { //...though if it dosen't exist, assigns rankOfRoot with a value of 0.
  	rankOfRoot = 0;
  }
 
  if (r == rankOfRoot) { //checks to see if the current value of "rankOfRoot" is equal to the passed in rank and if so returns T (BASE CASE)
  	return T;
  }
  
  if (r < rankOfRoot) { //if the current value of "rankOfRoot" dosen't equal to the passed in rank, using recursion checks the left side if the
                        //passed in ranks value is less than that of "rankOfRoot"...
  	return select(T->left, r);
  }
  else { //...or the right side if its value is greater than that of "rankOfRoot"
  	return select(T->right, r - rankOfRoot - 1);
  }
}

// Join trees L and R (with L containing keys all <= the keys in R) and Returns a pointer to the joined tree.  
Node *join(Node *L, Node *R) {
  if (L == nullptr) { //(for if and else-if): Acts as the base case for join(); returns R if Node L is equal to nullptr and vice-versa
      return R;
  }
  else if (R == nullptr) {
      return L;
  }
  else { //exectures if neither condition in the base case is true
	  double chooseLeftTree = (double) L->size / (L->size + R->size); //probability of choosing left tree (L)
	  double randomNumber = (double) rand() / RAND_MAX; //generates a random number
	  
	  if (randomNumber <= chooseLeftTree) { //checks to see if randomNumber's value is less than or equal to that of "chooseLeftTree" and if
	                                        //so, makes the root of the tree the left tree (L)'s root... 
	  	
		L->right = join(L->right, R); //assigns R's left with the result of a recursive call to join
	  	
	  	fix_size(L); //calls fix_size() to adjust the size of L after the join
	  	
	  	return L;
	  }
	  else { //...or if randomNumber's value is greater than that of "chooseLeftTree", makes the root of the tree the right tree (R)'s root
  	   
  	    R->left = join(L, R->left); //assigns R's left with the result of a recursive call to join
	  	
	  	fix_size(R); //calls fix_size() to adjust the size of R after the join
	  	
	  	return R;
	  }
  }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k) {
  assert(T != nullptr); //checks to see if the tree exists
  
  if (k == T->key) { //checks to see if the current key's value matches the passed in key "k", and if so replaces the node by joining its 
                     //children
	  if (T->left == nullptr && T->right == nullptr && T->key == k) { //checks to see if T's left and right exist and if not, deletes T and 
	                                                                  //returns nullptr
	  	delete(T); 
	  	
	  	return nullptr; 
	  }
	  else {
	  	  Node *temporaryNode = T; //temporary Node that points to T
	  	  
		  T = join(T->left, T->right); //reassigns T using recursion (which joins T's children)
		  
		  delete(temporaryNode); //deallocates T
		  
		  return T;
	  }
  }
  else if (k < T->key) { //if the passed in key "k"'s value is less than that of T's key recursively call remove() on the left side of 
                         //the tree...
      T->left = remove(T->left, k);
  }
  else { //...and if the passed in key "k"'s value is greater than that of T's key recurssively call remove() on the right side of the tree
      T->right = remove(T->right, k);
  }
  
  fix_size(T); //calls fix_size to adjust the size after the remove
  
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R) {
  if (T == nullptr) { //checks to see if the tree exists and if not sets L and R to nullptr and then returns
	  *L = nullptr;
	  *R = nullptr;
	  
	  return;
  }
  
  if (k < T->key) { //check's to see if the passed in key "k"'s value is less than that of T's key and if so recursively calls split() on the
                    //left side and on the left subtree (which R can now be ignored)... 
  
  	  split(T->left, k, L, &T->left);
   	  
  	  *R = T; //points R to T
	  
	  fix_size(T); //calls fix_size to adjust the size of T after the split
  }
  else { //...or if the passed in key "k"'s value is greater than that of T's key recursively calls split() on the right side and on the right 
         //subtree (which L can now be ignored)
  	  
  	  split(T->right, k, &T->right, R); 
  	  
  	  *L = T; //points L to T
	 
	  fix_size(T); //calls fix_size to adjust the size of T after the split
  }
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k) {
  int randomValue = rand(); //generates a random value
  // BASECASE 
  if (T == nullptr) { //checks to see if the tree exists and if not initializes a random seed and returns a new node with the value of "k"
                      //passed in...
  	
	srand (time(NULL));
  	
  	return new Node(k);
  }
  else if (T) { //...though if the tree exists, mod "randomValue" by the size of tree plus 1
  	  randomValue = randomValue % (T->size + 1);
  }
  
  if (randomValue == 0) { //checks to see if the value of "randomValue" and if so sets the new number being added as the root, though if not...
  	  
  	  Node* newNode = new Node(k); //creates a new node, allocates memory for it and assigns it the value of "k"
  	  
  	  split(T, k, &newNode->left, &newNode->right); //calls the split function in order to split the tree and set the resulting left and right 
  	                                                //tree's as the children of a new node
  	  
  	  fix_size(newNode); //calls fix_size to adjust the size of newNode after the split
  	  
  	  return newNode;
  }
  else { //...recursively call insert_random() on the left or right side of the tree respectively
  
  	  if (k < T->key) { //check's to see if the passed in key "k"'s value is less than that of T's key and if so recursively calls  
                       //insert_random() on T's left...
  	  	T->left = insert_random(T->left, k);
  	  	
  	  	fix_size(T); //calls fix_size to adjust the size of T after the insertion
  	  	
  	  	return T;
  	  }
  	  else { //...or if the passed in key "k"'s value is greater than that of T's key recursively calls insert_random on T's right
  	  	T->right = insert_random(T->right, k);
  	  	
  	  	fix_size(T); //calls fix_size to adjust the size of T after the insertion
  	  	
  	  	return T;
  	  }
  }
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
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}
