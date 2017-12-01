//----------------------------------------------------------------------
// Created by Nate  Braukhoff  on 3/31/17.
//This is a circular Queue, it follow first in first out princable.
//----------------------------------------------------------------------
#include <iostream>
#include <cassert>

using namespace std;

#ifndef CQUEUE_CQUEUE_H
#define CQUEUE_CQUEUE_H
#define TEST

template <typename QInfo, int MAX = 100>
class Queue
{
private:
   int front, rear, count;
   QInfo items[MAX];

public:
   void Test();

   Queue(){front = rear = count = 0;}           //constructor
   ~Queue(){};                                  //destructor
   bool IsFull(){return count == MAX;}          //return true if count = size of the queue
   bool IsEmpty() {return count == 0;}          //return true if count = 0
   bool Enqueue(const QInfo &x);                //add a val to the queue
   bool Dequeue(QInfo &x);                      //removes a val to the queue
   Queue Grow(const Queue &q);                  //this method grows queue

   int getFront() const {return front;}         //return the address of the front in the array
   int getRear() const {return rear;}           //return the address of the rear in the array
   int getSize() const {return count;}
   //return the value of size
};

//----------------------------------------------------------------------
//Enqueue: This method takes in a reference x and adds it to the back
// of the Queue. Returns true if x was added to the back of the queue
// other wise it will return false because the queue is full and
// can't add x
//----------------------------------------------------------------------
template<typename QInfo, int MAX>
bool Queue<QInfo, MAX>::Enqueue(const QInfo &x)
{
   if(!IsFull())
   {
      items[rear] = x;
      rear = (rear + 1) % MAX;
      count++;
      return true;
   }
   return false;

}

//----------------------------------------------------------------------
//Dequeue: This method takes in a reference x and sets it equal to
// the front of the stack. It will return true if the prossess
// happened, otherwise it will return false because there is nothing
// in the queue to return
//----------------------------------------------------------------------
template<typename QInfo, int MAX>
bool Queue<QInfo, MAX>::Dequeue(QInfo &x)
{
   if(!IsEmpty())
   {
      x = items[front];
      front = (front + 1) % MAX;
      count--;
      return true;
   }
   return false;
}

template<typename QInfo, int MAX>
Queue Queue<QInfo, MAX>::Grow(const Queue &q)
{
   if(IsFull())
   {
      QInfo temp[MAX * 2];
      for(int i = 0; i < count; i++)
      {
         temp[i] = items[rear];
         rear = (rear + 1) % MAX;
      }
      items = temp;
      rear = count;
      front = 0;

   }
}

#ifdef TEST
//----------------------------------------------------------------------
//Test: This is were all the test are located for the methods.
//----------------------------------------------------------------------
template<typename QInfo, int MAX>
void Queue<QInfo, MAX>::Test()
{
  //test IsEmpty
   Queue<int, 5> q1;
   assert(q1.IsEmpty());            //nothing in the queue

   //test Enqueue
   q1.Enqueue(1);                  //add something to the queue
   assert(!q1.IsEmpty());          //check to see if there is something in the queue

   //test Dequeue
   int x;
   q1.Dequeue(x);
   assert(q1.IsEmpty());          //check to see if the only thing
                                  // that was in the queue was removed

   assert(1 == x);                //check to see if the value
                                  // that it got is =

   //test if the queue is circling around
   Queue<int, 3> q2;
   q2.Enqueue(1);                       //add to the queue
   q2.Enqueue(2);                       //add to the queue
   q2.Dequeue(x);                       //removes form the queue
   q2.Enqueue(3);                       //add to the queue
   q2.Enqueue(4);                       //add to the queue
   assert(q2.IsFull());                 //q2 should be full
   assert((q2.getRear() - q2.getFront()) == 0);

   //the queue looks like [4,2,3]
}

#endif

#endif //CQUEUE_CQUEUE_H
