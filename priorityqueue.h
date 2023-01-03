// priorityqueue.h
// Imran Khan
// 654046372
// using windows vscode
// 10/28/2022
#pragma once

#include <iostream>
#include <sstream>
#include <set>
// #include <queue>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)


// checks the node if they are the same in the same position or not
    bool _checker(NODE *cur, NODE *other) {

      if (cur == nullptr && other == nullptr) {
        return true;
      } 
      else if(cur != nullptr && other != nullptr){

        return cur->priority == other->priority &&_checker(cur->left, other->left)&&  _checker(cur->right, other->right); 
      

      }
      else {
        return false;
      }
    }
//traverses through the binary tree and then it prints out the value in which it is needed this is used in the tostring function.
    void _traverse(NODE* cur,ostream &output)
    {
      
      if(cur == nullptr){
          return;
        }
        else{
          NODE *temp = cur;
          _traverse(cur->left,output);//goes through the function again
          
          while(temp != nullptr){
            //prints out the value
            output<<temp-> priority;
            output<<" value: ";
            output<<temp-> value<<endl;
            
            
            temp = temp->link;
          }
          
          _traverse(cur->right,output);//goes through the function again
        }
    }//end of _traverse

//this is used to make a new tree that is the same as the other tree and then used to compare the values in it
    void _anotherTree(NODE* root2)
    {
        
      if(root2 != nullptr){
        NODE* tempvalue =root2;
        tempvalue ->value = root2->value;
        tempvalue -> priority = root2 ->priority;
        this->enqueue(tempvalue->value, tempvalue->priority);//inserts thre value in the new binary tree
        _anotherTree(tempvalue->left);
        //checks for a linked list
        if(tempvalue->link != nullptr){
          _anotherTree(tempvalue->link);
        }
         _anotherTree(tempvalue->right);
      }
        
    }//end of _anotherTree

//this fucntion is used to delete the tree and clears it all out and then it is now an empty tree
    void _deleteTree(NODE* node) 
    { 
      NODE *temp = nullptr;
        if (node == NULL) return; 
      
        /* first delete both subtrees */
      if(node->link == nullptr){
        _deleteTree(node->left); //deletes the left side
        _deleteTree(node->right);  //deletes the right side
 
        delete node;
  
        size--;
        
      }
      else{
        NODE* temp2= nullptr;
        temp = node->link;
        //checks for a linked list
        while(temp!= nullptr){
          temp2 = temp->link;
  
          delete temp;
          temp = temp2;
 
          size--;
        }
        _deleteTree(node->left); //deletes the left side
        _deleteTree(node->right);  //deletes the right side
     
        delete node;
     
        size--;
        
      }
      
    } 
    
public:
    //
    // default constructor:
    //
    //establishes a blank priority queue.
    //O(1)
    priorityqueue() {
      size =0;
   
      root = nullptr;
      curr = nullptr;
      
        
        
    }
 

    //
    // operator=
    //
    // builds a clone of the "other" tree after clearing "this" tree.
    //adjusts the member variables for each one.
    //O(n), where n is the total number of missing nodes in the custom BST
    priorityqueue& operator=(const priorityqueue& other) {
        
       
      
        this->clear();
        
        _anotherTree(other.root);//makes the other tree
        this->size = other.size;//makes it the same size
        
        
        return *this;

        
        
    }

    //
    // clear:
    //
   // releases the priority queue's related memory, but it is public. where n is the total number of nodes in the modified BST

    void clear() {
 
      _deleteTree(root);//deletes the whole tree
   //resets the pointers of the tree
      root = nullptr;
      curr = nullptr;
      
        
  
        
        
    }
    
    //
    // destructor:
    //
    // releases the priority queue's related memory.
    // where n is the total number of nodes in the modified BST
    ~priorityqueue() {
      if(root != nullptr){
        clear();//clears the memory
      }
        
    }
    
    //
    // enqueue:
    //
    // based on priority, inserts the value into the custom BST in the appropriate place.
    // O(logn + m), where m is the number of duplicate priorities and n is the number of unique nodes in the tree
    void enqueue(T value, int priority) {
      
      if( this-> root == nullptr){

        //makes new nodes on the tree accordingly
        NODE * temp = new NODE;
        temp->value = value;
        temp->left =NULL;
        temp->right =NULL;
        temp->parent = NULL;
        temp->link = NULL;
        temp->dup = false;
        temp->priority=priority;

        size++;
        root = temp;
      }
      else{

        //makes another node and makes it a default value
        NODE *temp = root;
        NODE *prev = nullptr;
        NODE *add = new NODE;
        add->value = value;
        add->left =NULL;
        add->right =NULL;
        add->parent = NULL;
        add->link = NULL;
        add->dup = false;
        add->priority = priority;
        

        while(temp != nullptr){

          if(priority == temp->priority){
            //checks for the linked list is the values are the same
            while(temp != nullptr){
              prev = temp;
              temp = temp->link;
            }
            add->dup = true;
            prev->link = add;
            add->parent = prev;
            
            size++;
            return;
          }

          if(priority < temp->priority){
            //moves to the left because the value is lower that the parent in the binary tree
            prev = temp;
            temp = temp->left;
          }
          else{
            //moves to the right is not then
            prev = temp;
            temp = temp->right;
          }

        }

        if(priority < prev->priority){
          //moves to the left because the value is lower that the parent in the binary tree
          //adds the value to the left side
          prev->left = add; 
          add->parent = prev;
          size++;
        }

        if(priority > prev->priority){
          //moves to the right because the value is lower that the parent in the binary tree
          //adds the value to the right side
          prev->right = add; 
          add->parent = prev;
          size++;
        }
        

      }
    }
    //
    // dequeue:
    //
    //    removes the element from the priority queue and returns the value of the subsequent element in the priority queue.
    // O(logn + m), where m is the number of duplicate priorities and n is the number of unique nodes in the tree
    T dequeue() {

        T valueOut;

        if (root == nullptr){
            return valueOut;
        }

      //makes a new node and equals it to the root
        NODE* curr = root;
        NODE* previous = curr->parent;

        while(curr->left != nullptr){
            previous = curr;
            curr = curr->left;
        }

      //checks for the linked list in the binary tree and moves it accordingly
        if (previous == nullptr){
            if (root->link == nullptr && root->dup != true){
                root = curr->right;
            } 
            else {
                NODE *temp = root->link;
                temp->right = root->right;
                root = temp;
            }

            if (root != nullptr){
                root->parent = nullptr;
            } 
        } 
          //checks the next value if it is in the right hand side
        else if (curr->right != nullptr) {
            NODE *temp2 =curr ->right;
            previous->left = temp2;
            temp2->parent = previous;
        } 
          //checks for the linked list in the binary tree and moves it accordingly
        else if (curr->link != nullptr && curr->dup == true ){
            NODE* temp3 = curr->link;
            previous->left = temp3;
            temp3->parent = previous;
        } 
           //checks the next value if it is in the left hand side
        else {
            previous->left = nullptr;
        }

        //returns the value
        valueOut = curr->value;
        delete curr;
        size--;
        return valueOut;

    }

    
    //
    // Size:
    //
    //   returns 0 if the priority queue is empty and the number of elements in it.
    // O(1)
    int Size() {
        
        
        return size; 
        
        
    }
    
    //
    // begin
    //
    // Internal state is reset to allow for an inorder traversal. The internal state after the call to begin() indicates the first inorder node, ensuring that the initial call to the next() function returns the first inorder node value.
    // where n is the number of distinct nodes in the tree, O(logn)

    void begin() {
        //checks the last value in the binary tree
        curr = root;
        while(curr->left != nullptr ){
            curr = curr->left;
        }
        
    }
    
    //
    // next
    //
    // advances the internal state in advance of future calls after using the internal state to return the next inorder priority. True is also returned if a value or priority were really returned (through the reference parameter).
    
    // When the internal state reaches null, which indicates that no more values or priorities are available, False is returned. The traversal of the order ends here.
    bool next(T& value, int &priority) {
      //checks if the tree is empty
      if (curr == nullptr){
          return false;
        } 

      NODE* temp = nullptr;
      value = curr->value;
      priority = curr->priority;
      
      
      //checks is it is a linked list or not
      if(curr->link!= nullptr){
        curr = curr->link;
        return true;
      }

      //if linked list is present
      if (curr->dup == true){
          
        if (curr->link == nullptr){
          NODE* curr2 = curr;
          int p =curr->priority;
          while(curr2->priority == p ){
            curr = curr2;
            curr2 = curr2->parent;
            if(curr2 == nullptr){
                break;
              }
            }
          } 
        }

      //checks the right hand side
        
      if (curr->right != nullptr) {

        curr = curr->right;

        while (curr->left != nullptr) {
            curr = curr->left;
        }
        return true;
        } 
        //checks the left hand side
      else {
        NODE *curr2 =curr;
            
        while (curr2->parent != nullptr) {
          temp = curr->parent;
          if(curr2->priority < temp->priority){
            curr = temp;
            return true;
          }
          else{
            curr2 = curr2->parent;
          }
        }
        return false;
      }
    }


    //
    // toString:
    //
    // returns an ordered string containing the whole priority queue.

    string toString() {
      stringstream output;
      string display = "";
   
      _traverse(root, output);//in order trasverse
      display = output.str();
      
      return display;

        
    }
    
    //
    // peek:
    //   without removing it from the priority queue, returns the value of the subsequent element in the priority queue.
    // O(logn + m), where m is the number of duplicate priorities and n is the number of unique nodes in the tree
    T peek() {
      T valueOut;
      int priority;
   
      if(next(valueOut,priority)){
        valueOut= valueOut;
      }
        // the binary tree is empty
      else{
        cout<<"The queue is empty"<<endl;
      }
      return valueOut; 
        
        
    }
    


    //
    // ==operator
    //
    //     returns true if the priority queue entered as other is the priority queue that is currently in use. If not, returns false.
    // where n is the total number of nodes in the modified BST
    bool operator==(const priorityqueue& other) const {
      if(root != other.root){
        return false;
      }
      bool check;
      check = _checker(root,other.root);
      return check; 
        
        
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
