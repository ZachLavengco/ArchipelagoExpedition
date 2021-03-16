#include "Island.h"

class ArchipelagoExpedition
{
 private:
   // Create the Data Members for the Archipelago Network here
   Island *expedition;
   IslandQueue islandQ;
   FileList list;
   int numIslands;

   // Add file data member here
   // you can either use a linked list of strings
   // or a dynamic array of strings
  
 public:
  
 // Use a constructor to initialize the Data Members for your expedition
 ArchipelagoExpedition()
 {
   numIslands = 10;
   expedition = new Island[numIslands]();

 }

 IslandStack breadthFirstSearch(int x, int y) {
		//
		// set all previous locations to -1
		//
		for(int i = 0; i < numIslands; i++){
			expedition[i].setVisited(false);
			expedition[i].setPrevLocation(-1);
		}
		IslandStack pathList;  // initialize stack
		islandQ.clear();  // clears out the queue
		islandQ.push(x);  // pushes x into the queue
		int currentIsland = 1;
    if (bfs(y) == false) {
      printf("You can NOT get from island %d to island %d in one or more ferry rides\n", x, y);
       return pathList;
    } else {
      printf("You can get from island %d to island %d\n", x, y);
      currentIsland = y;
      pathList.push(currentIsland);
    }
	  do {
	    currentIsland = expedition[currentIsland - 1].getPrevLocation();
	    pathList.push(currentIsland);
	  } while (currentIsland != x);
    return pathList;
 }

 bool bfs (int b) {
    // while islandQ is not empty
    while (islandQ.front() != -1) {
      int a = islandQ.front();
      islandQ.pop();
      int itr = 0;  // iterates through the adjacency list
      int c = expedition[a-1].getAdjacent()->getNthElem(itr);
      //
      // iterates until nth element is equal to -1 meaning that list is empty
      //
      while (c != -1) {
        if (expedition[c-1].getPrevLocation() == -1) {
          expedition[c-1].setPrevLocation(a);
        }
        //
        // checks if we have found the island
        //
        if (c == b) {
          return true;
        }
        //
        // if island isn't found we just push the island into the queue and
        // go to the next island
        //
        islandQ.push(c);
        itr++;
        c = expedition[a-1].getAdjacent()->getNthElem(itr);
			}
		}
		return false;
 }
  
 void depthFirstSearchHelper(int x, int y){
   for(int i = 0; i < numIslands; i++){
     expedition[i].setVisited(false);
   }

   if(dfs(x,y) == true)
    printf("You can get from island %d to island %d in one or more ferry rides\n", x, y);
  else
    printf("You can NOT get from island %d to island %d in one or more ferry rides\n", x, y);
 }

 bool dfs(int x, int y){
   for(int i = 0; i < expedition[x-1].getAdjacent()->getListLength(); i++){
     int island = expedition[x-1].getAdjacent()->getNthElem(i);
     if(island == y)
      return true;

     if(expedition[island-1].getVisited() == false){
       expedition[x-1].setVisited(true);

       if ( dfs(island,y) == true )
        return true;
     }
   }
   return false;
 }
  
 void processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \r\n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0) 
      exit(1);
     
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();

    else if ( strcmp (command, "s") == 0) 
      doShortestPath();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) 
      doInsert();

    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 
 void showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q \n");
   printf ("  ? \n");
   printf ("  # \n");
   printf ("  s <int1> <int2> \n");
   printf ("  t <int1> <int2> \n");
   printf ("  r <int> \n");
   printf ("  i <int1> <int2> \n");
   printf ("  d <int1> <int2> \n");
   printf ("  l \n");
   printf ("  f <filename> \n");
 }

 void doShortestPath(){
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \r\n\t");


   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   
   printf ("Performing the shortest path Command from %d to %d\n", val1, val2);
   IslandStack s = breadthFirstSearch(val1, val2);
   //
   // base case if there is no path
   //
   if (s.top() == -1) {
     return;
   }
   //
   // prints out the stack of islands we went through to get to island val2 from island val1
   //
   printf("shortest path from %d to %d:", val1, val2);
   while (s.top() != -1) {
     printf(" %d", s.top());
     s.pop();
     //
     // will print out a dash for the next island if
     // there are still more islands to be printed out
     //
     if (s.size() != 0) {
       printf(" -");
     }
   }
   printf("\n");
 }
 
 void doTravel()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \r\n\t");


   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   // checks if island number is out of range
   if (val1 > numIslands || val1 < 0) {
     printf ("Invalid value for island\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   // checks if island number is out of range
   if (val2 > numIslands || val2 < 0) {
     printf ("Invalid value for island\n");
     return;
   }
   
   
   printf ("Performing the Travel Command from %d to %d\n", 
            val1, val2);
   depthFirstSearchHelper(val1, val2);
 }
 
 void doResize()
 {
   int val1 = 0;
   // get an integer value from the input
   char* next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi(next);
   
   printf ("Performing the Resize Command with %d\n", val1 );

   // deletes adjacency lists in each array
   for (int i = 1; i <= numIslands; i++) {
     expedition[i - 1].clear();
   }
   // deletes islands array
   delete [] expedition;
   // resizes the array of nodes
   expedition = new Island[val1];
   numIslands = val1;
 }
 
 void doInsert()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   // checks if island number is out of range
   if (val1 > numIslands || val1 < 0) {
     printf ("Invalid value for island\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   // checks if island number is out of range
   if (val2 > numIslands || val2 < 0) {
     printf ("Invalid value for island\n");
     return;
   }
   
   if(val1 <= numIslands && val2 <= numIslands){
    printf ("Performing the Insert Command for %d\n", val1 );
    expedition[val1-1].getAdjacent()->insert(val2);}
   else
    printf("Invalid value for island\n");
 }
 
 void doDelete()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   // checks if island number is out of range
   if (val1 > numIslands || val1 < 0) {
     printf ("Invalid value for island\n");
     return;
   }

   // get another integer value from the input
   next = strtok (NULL, " \r\n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   // checks if island number is out of range
   if (val2 > numIslands || val2 < 0) {
     printf ("Invalid value for island\n");
     return;
   }

   printf ("Performing the Delete Command for %d\n", val1 );
   expedition[val1-1].getAdjacent()->remove(val2);
 }
 
 void doList()
 {
   printf ("Displaying the adjacency list:\n" );
   for(int i = 0; i < numIslands; i++){
     printf("%d -->", i+1);
     expedition[i].getAdjacent()->printList();
     printf("\n");
   }
 }
 
 // used with command 'f <>'
 void doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \r\n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   printf ("Performing the File command with file: %s\n", fname);

   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use
   if (list.checkIfOpen(fname) == true) {
     printf("File is already in use\n");
     return;
   }
   //  2. open the file using fopen creating a new instance of FILE*
   FILE* f = fopen(fname, "r");
   list.insert(fname);
   if (f == NULL) {
     printf("Cannot open the file\n");
     return;
   }
   //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
   this->processCommandLoop(f);
   //  4. close the file when processCommandLoop() returns
   list.remove(fname);  // removes file from list
   fclose(f);
 }
};

int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the island adjcency list
  ArchipelagoExpedition islandData;
   
  // call the method that reads and parses the input
  islandData.showCommands();
  printf ("\nEnter commands at blank line\n");
  printf ("    (No prompts are given because of f command)\n");
  islandData.processCommandLoop (inFile);
   
  printf ("Goodbye\n");
 
  return 1;
 }