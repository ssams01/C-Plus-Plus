#pragma once

#include <iostream>

using namespace std;

//This class defines a queue of integers implemented
//using a circular array
//The array is dynamically allocated, but remains
//a fixed size for the lifespan of the object
//Do not modify anything in the class definition

class IntegerArrayQueue
{
    private:
        int* array; //pointer to array of integers
        int front; //index of item to dequeue
        int back; //index of item to enqueue
        int size;
    public:
        IntegerArrayQueue() :
            array(new int[10]), front(0), back(9), size(10)
            {
                for (int i = 0; i<10; i++) array[i]=0;
            }
        IntegerArrayQueue(int size) :
            array(new int[size]), front(0), back(size-1), size(size)
            {
                for (int i = 0; i<size; i++) array[i]=0;
            }
        ~IntegerArrayQueue() { delete [] array;}
        void printArrayQueue()
        {
            for (int i = 0; i<size; i++) cout << array[i] << " ";
            cout << endl;
            cout << "front: " << front << endl;
            cout << "back: " << back << endl;
            cout << "size: " << size << endl;
        }
        //Implement the enqueue and dequeue functions
        //enqueue: if there is space available enqueue value and
        //return true, otherwise return false
        bool enqueue(int value);
            
        
        //dequeue: if there is a value at the front of the queue
        //return the value and remove from the queue,
        //otherwise return 0
        int dequeue();
};
