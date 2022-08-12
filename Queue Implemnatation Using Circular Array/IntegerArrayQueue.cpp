#include <iostream>
#include "IntegerArrayQueue.h"

using namespace std;


//Function is designed to check if the queue is full and if it isn't, it enqueues the past in value to the queue
 bool IntegerArrayQueue::enqueue(int value) {
    int returnValue = true; //meant to check if the queue is full and if it is holds the value of FALSE
    
    if(((back + 2) % size == front) || (back == (front - 1) % (size - 1))) { //if the queue is full or if front and back are right next to
                                                                             //each other in the queue, returnValue is false
        returnValue = false; 
    }
    else if((back + 1) & size == front) { //checks to see if the list empty and if so it enqueues the first index in the array
        front = 0;
        back = 0;
        array[0] = value; //sets the value at the first index in the array to the value of "value"
    }
    else if((back == size - 1) && ((back + 2) % size != front )) {
        back = 0; //meant to repostion the back of the array to the front of the array
        array[back] = value;
    }
    else {
        back++;
        array[back] = value;
    }
    return returnValue;
     
 }
 
 //Function is designed to check if there's a value at the front of the queue and if so returns the value and removes it from the queue
 int IntegerArrayQueue::dequeue() {
     int returnValue = 0; //meant to hold the value at the front index of the array and the value is returned at the end of the function
     
     if((back + 1) % size == front) { //checks to see if the queue is empty and if so prints an error message letting the user know
         cout << "There is no value at the front of the queue, the queue is empty." << endl;
     }
     else {
         returnValue = array[front]; //sets the value of returnValue to the the value of the element at the "front" index of the array
         
         array[front] = 0; //resets the value of the element of the "front" index back to 0
         
         if(front == back) {//checks to see if there is only one node in the queue and if so resets both to the first index (0)
             front = 0;
             back = 0;
         }
         else if(front == size - 1) { //checks to see if "front" is pointed to the end of the array and if so set "front" back to the first
                                        //element in the array
             front = 0;                              
         }
         else { //front is dequeued and incremented to the next element in the array
             front++;
         }
     }
     return returnValue;
     
 }