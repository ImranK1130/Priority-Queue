#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <sstream>
#include<string>
#include<cstdlib>
#include <map>
#include <vector>
#include <queue>

/*In this test case we are seeing if the size is equal to what is needed and also the to string is being checked to see 
if the correct output is in the binary tree*/
TEST(priorityqueuetesting1, one) {
    map<int, vector<int> > checker;
    priorityqueue<int> numbers;
    int p = 12;
    int values[] = {12,14,15,8,9,13,24,6,7,55,22,89};
    int priorities[] ={1,2,3,4,5,1,2,3,4,7,9,80};
    for(int i = 0; i<p; i++){
     numbers.enqueue(values[i],priorities[i]);
    }
    EXPECT_EQ(p,numbers.Size());
    for(int i = 0; i<p; i++){
     checker[priorities[i]].push_back(values[i]);
    }

    stringstream ss;
    for(auto i: checker){
      int priority = i.first;
      vector<int>value = i.second;
      for (size_t p = 0; p < value.size(); p++){
        ss << priority << " value: " << value[p] << endl;
      }

    }

  EXPECT_EQ(numbers.toString(), ss.str());

}
/*IN this function we are testing out random numbers and inputting them in a variable and then checking
 the to string if they match and then looking if the size is also correct */
TEST(priorityqueuetesting2, two){
  priorityqueue<int> checker;
  priorityqueue<int> checker2;
  int x = 0;
  int values[100];
  int priorities[100];
  for(int i = 0 ; i<100 ; i++){
    int y = rand() % 100; 
    values[i] = y;
  }
  for(int i = 0 ; i<100; i++){
   x = rand() % 100;
   priorities[i] = x;
  }
  for(int i = 0 ; i<100; i++){
    checker.enqueue(values[i],priorities[i]);
  }

  EXPECT_EQ(100,checker.Size());
  for(int i = 0 ; i<100; i++){
    checker2.enqueue(values[i],priorities[i]);
  }

  EXPECT_EQ(100,checker.Size()); 
  EXPECT_EQ(checker2.Size(),checker.Size());

  EXPECT_EQ(checker.toString(), checker2.toString());

}

/*in this test we check if the inputs addd to the binary tree are random in number and then we use 2 trees to compare 
them then we use the '=' operator to copy the tree to the other and check if the toString match*/
TEST(priorityqueuetesting3, three){
 priorityqueue<int> first;
 priorityqueue<int> copy;
 int values[100];
 int priorities[100];
 int x =0;
 int y =0;
 for(int i = 0 ; i<100; i++){
  x = rand() % 100;
  y = rand() % 100; 
  priorities[i] = x;
  values[i] = y;
 }
 for(int i = 0 ; i<100; i++){
  first.enqueue(values[i],priorities[i]);
 }

 stringstream ss;
 string firstval="";
 firstval = first.toString();

 copy = first;

 string copy2 = "";
 copy2 = copy.toString();


 EXPECT_EQ(firstval,copy2);
 EXPECT_EQ(100,copy.Size());



}
/*general test of the size implementation*/
TEST(size, PositiveNos) { 
  priorityqueue<string> pq;
  int x = 0;
  ASSERT_EQ(0,pq.Size());
}
 /*general test of the size implementation*/
TEST(addingsize, PositiveNos) { 
  priorityqueue<string> pq;
  int x = 0;
  // priorityqueue b;
  pq.enqueue("Dolores",5);
  pq.enqueue("Imran",9);
  pq.enqueue("fanny",3);
  pq.enqueue("common",3);
  pq.enqueue("dorleus",2);

  x = pq.Size();
  ASSERT_EQ(5,pq.Size());
}
/*general test of the size implementation*/
TEST(wrongaddingsize, PositiveNos) { 
  priorityqueue<string> pq;
  int x = 0;
  // priorityqueue b;
  pq.enqueue("Dolores",5);
  pq.enqueue("Imran",9);
  pq.enqueue("common",3);
  pq.enqueue("fanny",3);
  pq.enqueue("dorleus",2);

  x = 5;
  ASSERT_EQ(x,pq.Size());
}
/*general test of the size implementation and adding more than 100 inputs to see if they are inputted correctly*/
TEST(testing100Inputs, one){
  priorityqueue<string> pq;
  for(int i = 0; i<100 ; i++){
    pq.enqueue("test",i);
  }
  for(int i = 0; i<100 ; i++){
    pq.enqueue("test",i);
  }
  int x = 200;
  ASSERT_EQ(x,pq.Size());
  EXPECT_EQ(x,pq.Size());
}

/*in this we use the build in queue system to add in values of vector and then compare them with the pq queue that was made 
by the class that we made and then we tested them out if they were the same*/
TEST(priorityqueuetesting4, four){

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> first;
    priorityqueue<int> pq;
    vector<int> vec = {4,5,6,3,6,7,5,3,1,6,11,44,5,6,7,8,2,9,18,90};
    int value;
    int priorities;

    for (int i = 0; i < vec.size(); i++){
        pair<int, int> PAIR1;
        PAIR1.first = vec[i];
        PAIR1.second = i;
        first.push(PAIR1);
        pq.enqueue(i,vec[i]);
    }

    ASSERT_EQ(pq.Size(), first.size());
}
/*in this test case we are looking into the dequeue function and seeing if the sixe actually decreases or not accordingly*/

TEST(priorityqueuetesting5, five){
  map<int, vector<string> > checker;
  priorityqueue<string> numbers;
  int p = 9;
  int counter = 0;
  
  vector<string>namesvalues = {"Dolores","dave","patrick","bob","alexa","alex","imran","john","pen"};
  
  int priorities[] ={5,4,8,2,6,11,8,8,8};
  for(int i = 0; i<p; i++){
    numbers.enqueue(namesvalues[i],priorities[i]);
  }
  EXPECT_EQ(p,numbers.Size());
  for(int i = 0; i<p; i++){
    checker[priorities[i]].push_back(namesvalues[i]);
  }
  numbers.dequeue();
  counter++;
  numbers.dequeue();
  counter++;
  numbers.dequeue();
  counter++;
  numbers.dequeue();
  counter++;
  

  EXPECT_EQ(numbers.Size(), p - counter);


}

/*in this we are checking the next fuction and using stringstream to store in the values and them we ocmpare it with the 
to string in which theyboth have to be equal to pass the test case*/
TEST(priorityqueuetesting6, six){
  priorityqueue<string> numbers;
  int p = 9;
  
  vector<string>namesvalues = {"Dolores","dave","patrick","bob","alexa","alex","imran","john","pen"};
  
  int priorities[] ={5,4,8,2,6,11,8,8,8};
  for(int i = 0; i<p; i++){
    numbers.enqueue(namesvalues[i],priorities[i]);
  }

  stringstream ss;

  numbers.begin();
  string value = "";
  int priority = 0;

    while (numbers.next(value, priority)) {
       ss << priority << " value: " << value << endl;
    }
       ss << priority << " value: " << value << endl;

  EXPECT_EQ(numbers.toString(), ss.str());
}

/*in this test we are testing the dqueue function and seeing if the value is actually removed from the queue and then 
we are looking into them we another queue to see if they are the same even after dequeue*/

TEST(priorityqueuetesting7, seven){
  priorityqueue<string> checker;
  priorityqueue<string> checker2;
  int p = 9;
  int counter = 0;
  
  vector<string>namesvalues = {"Dolores","dave","patrick","bob","alexa","alex","imran","john","pen"};
  
  int priorities[] ={5,4,8,2,6,11,8,8,8};
  for(int i = 0; i<p; i++){
    checker.enqueue(namesvalues[i],priorities[i]);
  }

  stringstream ss;
  string firstval="";
  firstval = checker.toString();

  checker2 = checker;

  string copy2 = "";
  copy2 = checker2.toString();
  
  EXPECT_EQ(checker2.Size(),checker.Size());
  EXPECT_EQ(checker.toString(), checker2.toString());

  checker.dequeue();
  counter++;
  checker.dequeue();
  counter++;
  checker.dequeue();
  counter++;
  checker.dequeue();
  counter++;


  checker2.dequeue();
  counter++;
  checker2.dequeue();
  counter++;
  checker2.dequeue();
  counter++;
  checker2.dequeue();
  counter++;

  EXPECT_EQ(checker.toString(), checker2.toString());




}

int main(int argc, char **argv) 
    {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }