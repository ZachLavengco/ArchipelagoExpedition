#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class Node{
    private:
        int island;
        Node * next;

    public:
        //Constructor
        Node(int val){ 
            island = val;
            next = NULL;
        }

        Node(int val, Node* nxt){   
            island = val;
            next = nxt;
        }

  
        int getIsland(){
            return island;
        }

    
        Node * getNext(){
            return next;
        }

        void setIsland(int val){
            island = val;
        }

        void setNext(Node* nxt){
            next = nxt;
        }

};

class MyList{
    private:
        Node* head;

    public:

        MyList(){
            head = NULL;
        }

        void insert(int val){
           
            Node* temp = new Node(val, NULL);
            Node* curr = head;
            Node* prev = NULL; 

            while(curr!= NULL){
                if(curr->getIsland() == val){
                    printf("Ferry ride already added!\n");
                    return;
                }
                prev = curr; 
                curr = curr->getNext();
            }
            if(prev == NULL){
                head = temp; 
            }
            else{
                prev->setNext(temp) ; 
            }
        }

        void remove(int v1){
  
            Node * curr = head;
            Node * prev = NULL;
            while(curr != NULL && curr->getIsland() != v1){
                prev = curr;
                curr = curr->getNext();
            }
            if(curr == NULL){
                printf("Ferry ride does not exist\n");
                return;
            }
            //if node to delete is at head of list
            if(prev == NULL){
                prev = curr->getNext();
                delete curr;
                head = prev;
            }
       
            else{
                prev->setNext(curr->getNext());
                delete curr;
            }
        }

        int getListLength(){
            int total = 0;
            Node* tmp = head;

            while(tmp != NULL){
                total++;
                tmp = tmp->getNext();
            }

            return total;
        }

        int getNthElem(int n){
            int curr = 0;
            Node * temp = head;
            while(temp != NULL && curr != n){
                curr++;
                temp = temp->getNext();
            }

            if(temp == NULL)
                return -1;

            else{
                return temp->getIsland();
            }
        }

        void printList(){
            Node* temp = head;
						int ind = 0;
            while(temp != NULL){
								if (ind == 0) {
									printf("  ");
									ind++;
								}
                printf("%d  ", temp->getIsland());
                temp = temp->getNext();
            }
        }


        // deletes entire list
        void removeAll( )
        {
          Node* curr = head;
          Node* next;
          // iterates through list until end is reached
          while (curr != NULL) {
              next = curr->getNext(); // gets next node
              delete curr;  // deletes current node
              curr = next;  // sets current to next node
          }
          head = NULL;  // sets first to null
        }

        Node* getHead() {
          return head;
        }

        void setHead(Node** newHead) {
          head = (*newHead);
        }
};

class IslandQueue : public MyList {
    public:
        //
        // pushes to back of queue
        //
        void push(int val) {
            Node* newNode = new Node(val);
            Node* temp = getHead();
            //
            // base case if queue is empty
            //
            if (temp == NULL) {
              setHead(&newNode);
              return;
            }
            //
            // iterates to the end of the list and inputs node
            //
            while (temp->getNext() != NULL) {
              temp = temp->getNext();
            }
            temp->setNext(newNode);
        }
        //
        // returns the front node
        //
        int front() {
            Node* temp = getHead();
            //
            // returns if list is empty
            //
            if (temp == NULL) {
              return -1;
            }
            return temp->getIsland();
        }
        //
        // deletes the front node
        //
        void pop() {
            Node* remove = getHead();
            //
            // returns if list is empty
            //
            if (remove == NULL) {
              return;
            }
            Node* next = remove->getNext();
            setHead(&next);
            delete remove;
        }
        //
        // clears queue
        //
        void clear() {
            removeAll();
        }
};

class IslandStack : public MyList {
    public:
        int num = 0;
        //
        // pushes to front of queue
        //
        void push(int val) {
            num++;
            Node* newNode = new Node(val);
            Node* temp = getHead();
            //
            // base case if stack is empty
            //
            if (temp == NULL) {
              setHead(&newNode);
              return;
            }
            newNode->setNext(temp);
            setHead(&newNode);
        }
        //
        // returns the front node
        //
        int top() {
            Node* temp = getHead();
            //
            // returns if list is empty
            //
            if (temp == NULL) {
              return -1;
            }
            return temp->getIsland();
        }
        //
        // deletes the front node
        //
        void pop() {
            Node* remove = getHead();
            //
            // returns if list is empty
            //
            if (remove == NULL) {
              return;
            }
            Node* next = remove->getNext();
            setHead(&next);
            delete remove;
            num--;
        }
        //
        // gets size of stack
        //
        int size() {
          return num;
        }
};

class Island{
    private:
        MyList *adjacent;
        bool visited;
        int prevLocation;

    public:
        Island(){
            adjacent = new MyList;
            visited = false;
						prevLocation = -1;
        }

        MyList* getAdjacent(){
            return adjacent;
        }

        void clear(){
            adjacent->removeAll();
        }

        bool getVisited(){
            return visited;
        }

        void setVisited(bool status){
            visited = status;
        }

        void setPrevLocation(int l) {
            prevLocation = l;
        }

        int getPrevLocation() {
            return prevLocation;
        }
};


//
// File class for creating nodes of file names
//
class FileNode {
  private:
    char* fname;
    FileNode* next;
  public:
    FileNode() {
      // allows a file name of 50 characters long
      fname = new char[50];
      next = nullptr;
    }
    // gets filenode's file name
    char* getFile() {
      return fname;
    }
    // sets filenode's file name
    void setFile(char* f) {
      fname = f;
    }
    void deleteFileName() {
      delete fname;
    }
    // gets filenode's next node
    FileNode* getNext() {
      return next;
    }
    // sets filenode's next node
    void setNext(FileNode* n) {
      next = n;
    }
};


// FileList class creating a list of files
class FileList {
private:
  FileNode* first;
public:
  FileList() {
    first = NULL;
  }

  void insert(char* name) {
    // Create a new node to put into end of the list
    FileNode* tmp = new FileNode;
    FileNode* curr = first;
    FileNode* prev = NULL;
    tmp->setFile(name);
    
    // iterates through list until end is reached
    while (curr != NULL)
    {
      prev = curr;
      curr = curr->getNext();
    }

    // if it's the beginning of the list set new node to beginning
    if (prev == NULL)
    {
      first = tmp;
    }
    // links previous pointer to new node
    else
    { 
      prev->setNext(tmp);
    }
  }

  // checks whether the file is currently open
  bool checkIfOpen(char* name) {
    FileNode* curr = first;
    while (curr != NULL) {
      if (strcmp(curr->getFile(), name) == 0) {
        return true;
      }
      curr = curr->getNext();
    }
    return false;
  }

  // removes specific data from list
  void remove(char* name)
  {
    FileNode* curr = first;
    FileNode* prev = NULL;

    // iterates until wanted node is found
    while ((curr != NULL) && (curr->getFile() != name))
    {
      prev = curr;
      curr = curr->getNext();
    }
    // returns if there was no node with data found
    if (curr == NULL) {
      return;
    }
    // if there's only one element in the list
    else if (prev == NULL)
    {
      first = curr->getNext();
      //curr->deleteFileName();
      delete curr;
    }
    // if at the end of the list
    else if (curr->getNext() == NULL) {
      prev->setNext(NULL);
      //curr->deleteFileName();
      delete curr;
    }
    // if in the middle of the list
    else
    { 
      prev->setNext(curr->getNext());
      //curr->deleteFileName();
      delete curr;
    }
  }
};