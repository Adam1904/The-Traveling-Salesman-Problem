#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <string>
#include <bits/stdc++.h> 

using namespace std;

/* --------- Declaration of new list item type --------- */       
struct TlistElement{
  TlistElement * next, * prev;
  char identifier;
  float latitude;
  float magnitude;
};

float calculateRoute(TlistElement * p1, TlistElement * p2){
  // reading the coordinates and switching to correct units
  float cz1 = (p1->latitude-p2->latitude)*(p1->latitude-p2->latitude)*71*71;
  float cz2 = (p1->magnitude-p2->magnitude)*(p1->magnitude-p2->magnitude)*111*111;
  return sqrt(cz1+cz2); // using the Pythagorean theorem
}

/* --------- Declaration of the type of a bidirectional list class --------- */   
struct TdoubleList{

  private:
    TlistElement * front, * back;
    unsigned counter;

  public:  
    /* --------- Constructor --------- */       
    TdoubleList(){
      front = NULL;
      back = NULL;
      counter  = 0;
    }

    /* --------- Destructor --------- */    
    ~TdoubleList(){

      TlistElement * p;
      
      while(front){
        p = front->next; // iterating through all the items in the list
        delete front; // removing element from top of list as long as front is not NULL
        front = p;
      }              
    }

    unsigned size(){ 
      return counter; // returns the length of the list
    }

    TlistElement * push_front(TlistElement * p){
      p->next = front; 
      p->prev = NULL;

      if(front) 
        front->prev = p; // adds an item (pointed out by p) to the top of the list

      front = p;
      if(!back) // if back is not null
        back = front;

      counter++;
      return front; // returns an address
    }

    TlistElement * push_back(TlistElement * p){ // Dodaje element na końcu listy i zwraca jego adres

      if(back) 
        back->next = p; // adds an item (pointed out by p) to the end of the list

      p->next = NULL; 
      p->prev = back;
      back = p;

      if(!front) // if front is not nullptr
        front = back;

      counter++;
      return back; // returns an address
    }

    TlistElement * insert(TlistElement * p1, TlistElement * p2){

      p1->next = p2->next; 
      p1->prev = p2;
      p2->next = p1;

      if(p1->next) 
        p1->next->prev = p1; // adds a p1 element after a p2 element
      else
        back = p1; // if p1->next is nullptr

      counter++;
      return p1; // returns p1 address
    }

    TlistElement * pop_front(){

      TlistElement * p;
      
      if(front){

        p = front;
        front = front->next; // removes an item from the top of the list

        if(!front) 
          back = NULL;
        else
          front->prev = NULL; // if front is NULL
        
        counter--;
        return p; // returns the address of the deleted item
      }
      else 
        return NULL; // if the front is NULL it returns NULL
    }

    TlistElement * pop_back(){

      TlistElement * p;
      
      if(back){

        p = back;

        if(p == front) 
          front = back = NULL; // removes an item from the end of the list
        else{
          back = back->prev;
          back->next = NULL; // removes an item from the end of the list
        };

        counter--;
        return p; // returns the address of the deleted item
      }
      else 
        return NULL; // if the back is NULL it returns NULL
    }

    TlistElement * erase(TlistElement * p){

      TlistElement * p1;
      
      // deleting from the list the element pointed by p
      if(p->prev) 
        p->prev->next = p->next; 
      else 
        front = p->next;
      
      if(p->next) 
        p->next->prev = p->prev;
      else 
        back = p->prev;
      
      counter--; // counter decrementation

      return p; // returns the address of the deleted item
    } 

    TlistElement * index(unsigned n){ 

      TlistElement * p;
      
      if((!n) || (n > counter)) 
        return NULL; // if the list has fewer than n elements, it returns NULL (elements are numbered from 1)
      else if(n == counter) 
        return back; // if it's the last item in the list, return it
      else if(n < counter / 2){
        p = front;
        while(--n) p = p->next;
        return p; // returns the nth element
      }
      else{
        p = back;
        while(counter > n++) p = p->prev;
        return p; // returns the nth element
      }  
    }

    void showKeys(){

      TlistElement * p;
      
      if(!front) 
        cerr << "List is empty..." << endl;
      else{
        p = front;

        cout << "Displaying the contents of the list..." << endl;
        int numOfElement = 1;
        while(p){
          cout << numOfElement << ") " << p->identifier << " " << p->latitude << " " << p->magnitude << "\n"; // displaying all keys of elements in the list
          numOfElement++;
          p = p->next;
        }

        cout << endl;
      }
    }

    double calculateTotalRoute()
    {
        TlistElement * p1;
        TlistElement * p2;
        if(!front){
          cerr << "List is empty..." << endl;
          return 0.0;
        }
        else{
          double length = 0;
          p1 = front;
          p2 = p1->next;

          while(p2){
            // count the road 
            length = length + sqrt((p1->latitude-p2->latitude)*(p1->latitude-p2->latitude)*71*71+(p1->magnitude-p2->magnitude)*(p1->magnitude-p2->magnitude)*111*111);
            p1 = p2;
            p2 = p2->next;
          }

          cout << endl;
          return length;
        }
    
    }

    void neighborAlgorithm(){

      TlistElement * pStart; // starting from Warsaw
      TlistElement * pDesired;
      TlistElement * pFound;
      
      float distance;
      pStart = front; // putting Warsaw at the top of the list
      
      while(pStart){

        pDesired = pStart ->next; // iterate over the loop

        if(pDesired) // if we come across the desired value
          distance = calculateRoute(pStart, pDesired);
        if(pDesired->identifier=='X') // if the list comes to the end
          break;

        while(pDesired && pDesired->identifier!='X'){
        
          if (calculateRoute(pStart, pDesired) <= distance){
            distance = calculateRoute(pStart, pDesired);
            pFound = pDesired;
          }

          pDesired = pDesired ->next;
        }

        shift(pStart, pFound);                                                 
        pStart = pStart -> next;
        
      }
    }

    void shift(TlistElement * p1, TlistElement * p2){
      TlistElement * temp;
      TlistElement * temp1;
      TlistElement * temp2;
      TlistElement * temp3;
      TlistElement * temp4;
      
      int i = 0; // auxiliary variable
      while(p2->prev != p1){
        temp = p2->prev; // pointer from p2 to earlier                               
        temp1 = p2->next; // pointer from p2 to the next                                 
        temp2 = p2->prev->next; // pointer from previous to p2                           
        temp3 = p2->prev->prev; // pointer from previous to earlier
        temp4 = p2;

        p2->prev = temp3;                                       
        //S -prev := M              
        p2->next = temp;         
        //S -next := P


        // this is what p2 prev is supposed to point to
        //next
        p2->next->next = temp1;
        //P -next := Z
        //prev
        p2->next->prev = temp4;    
        //P -prev := S

        temp1->prev = temp;
        //Z - prev := P
        temp3->next = p2;         
        //M - next := S
      }
      p1->next = p2;
    }

    void displayGraph(){ // TODO fix displaying graph

      TlistElement * p1;
      TlistElement * p2;
      p1 = front;
      p2 = p1->next;

      if(!front){
          cerr << "List is empty..." << endl;
      }
      else{
        
        double maxY, maxX, minY, minX;
        
        maxY = minY = p1->magnitude;
        maxX = minX = p1->latitude;
          while(p2){
            if(p2->latitude > maxX)
              maxX = p2->latitude;
            if(p2->latitude < minX)
              minX = p2->latitude;  
            if(p2->magnitude > maxY)
              maxY = p2->magnitude;  
            if(p2->magnitude < minY)
              minY = p2->magnitude;  
            p1 = p2;
            p2 = p2->next;
          }
        
        int listSize = size();
        cout << string(5, ' ')<< "^" << endl;
        cout << fixed << setprecision(2) << maxY << "|";
        p1 = front;
        p2 = p1->next;
        for(int j = 0; j<listSize-1 ;j++){
            int counter2 = 0;
            int array[listSize];
            if(maxY == p1->magnitude){
              array[counter2] = p1->magnitude;
              counter2++;
            }
            if(counter2==1)
              cout << string((int)(50*p1->latitude/maxX), ' ') << (j+1);
            else{
              sort(array, array+listSize);
              cout << string((int)(50*array[0]/maxX), ' ') << (j+1);
              for(int c = 1; c<counter2; c++){
                cout << string(5, ' ') << (j+1+c);
              }
            }
            p1 = p2;
            p2 = p1->next;
          }
        cout << endl;
        for(int i = 0; i<18 ;i++){
          cout << string(5, ' ') << "|";
          p1 = front;
          p2 = p1->next;
          for(int j = 0; j<listSize-1 ;j++){
            int counter2 = 0;
            int array[listSize];
            if(i == (int)(20*p1->magnitude/maxY)){
              array[counter2] = p1->magnitude;
              counter2++;
            }
            if(counter2==1)
              cout << string((int)(50*p1->latitude/maxX), ' ') << (j+1);
            else{
              sort(array, array+listSize);
              for(int c = 0; c<counter2; c++){
                cout << string((int)(50*array[c]/maxX), ' ') << (j+1+c);
              }
            }
            p1 = p2;
            p2 = p1->next;
          }
          cout << endl;
        }
        cout << fixed << setprecision(2) << minY << "|";
        p1 = front;
        p2 = p1->next;
        for(int i = 0; i<listSize-1 ;i++){
          if (minY == p1->magnitude){
            cout << string((int)(50*p1->latitude/maxX), ' ') << (i+1);
          }
          p1 = p2;
          p2 = p1->next;
        }
        cout << endl;
        cout << string(5, ' ') << string(50, '-') << ">" << endl;
        cout << string(5, ' ') << fixed << setprecision(2) << minX << string(43, ' ') << fixed << setprecision(2) << maxX << "\n\n";

      }
    }
};

/* --------- Main function --------- */     
int main(){

  TdoubleList dl;
  TlistElement * p;
  int i;

  ifstream in("cities.txt"); // input file stream 

  if(!in){ 
    cerr << "Cannot open input file!" << endl; // handling bad file reading
    return 1;
  }

  char str[255]; // array of chars
  char * pch; // auxiliary pointer (points to the present char)
  char * pEnd; // auxiliary pointer (points to the end char)

  while(in){
    in.getline(str, 255); // the delimiter is set to by default ('\n')
    if(in) 
    {
        pch = strtok(str," "); // split string into tokens, which are sequences of contiguous characters separated by " "
        while (pch != NULL) // adding new element in the loop
        {
            p = new TlistElement;
            p->identifier = *pch;
            pch = strtok(NULL, " ");
            p->latitude = strtof(pch, &pEnd);
            pch = strtok(NULL, " ");
            p->magnitude = strtof(pch, &pEnd);
            pch = strtok(NULL, " ");
            dl.push_back(p);
        }
    }
  }
  
  cout << string(70, '*') << endl; // text separation for better visualization
  dl.displayGraph(); // displaying the graph
  dl.showKeys(); // displaying list
  cout << "Total length of the road is: " << dl.calculateTotalRoute() << " km" << "\n\n";
  cout << string(70, '*') << endl; // text separation for better visualization
  cout << "*** After calculations ***" << endl;

  p = new TlistElement; // setting pointer at the top of the list
  p->identifier = 'X'; // setting identifier 'X'
  p->latitude = 0; // setting zero values
  p->magnitude = 0; // setting zero values

  dl.push_back(p); // inserts the pointer to the end of the list
  dl.neighborAlgorithm(); // execution of the neighbor algorithm
  
  dl.pop_back(); // deleting the last element
  dl.displayGraph(); // displaying the graph
  dl.showKeys(); // displaying sorted list
  cout << "Total length of the road is: " << dl.calculateTotalRoute() << " km" << "\n\n";
  
  return 0;
}