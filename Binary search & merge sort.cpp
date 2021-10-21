#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

/*
If it doesnt run normaly try this instead [tested on linux];
Run with: clang++-7 -pthread -std=c++17 -o Actividad1_1 Actividad1_1.cpp

./Actividad1_1
*/

int *finded, Ndata, Mdata;
vector<int> arrs;
vector<int> toFind, toFindCP;

/* Helps */
void display(vector<int> data) {
  /* Display all the items on the vector */
  for(int i = 0; i < data.size(); i++) {
    cout << data[i] << endl;
  }
}

int atIndex(vector<int> data, int value) {
  /* Help to determine de index at the M values vector */

  for(int i = 0; i < data.size(); i++) {
    if(value == data[i]) {
      return i;
    }
  }

  return -1;
}
/* Helps */

bool askData() {
  /* It ask the N and M values then proceede to convert to array to "toFind" and makes a copy "toFindCP" for later use */

  int tmp;
  vector<int> arr;

  cout<<endl;
  cin>>Ndata;
  cin>>Mdata;

  if(Ndata > 0) {
    for(int i=0; i<Ndata; i++) {
      cout<<endl;
      cin>>tmp;
      arr.push_back(tmp);
    }

    for(int i=0; i<Mdata; i++) {
      cout<<endl;
      cin>>tmp;
      toFind.push_back(tmp);
    }

    toFindCP = toFind;

    finded = new int[Mdata];

    arrs = arr;

    return 0;
  }
  else {
    return -1;
  }
}

vector<int> sort(vector<int> data) {
  /*Checks who´s the smallest then adds to the vector and the numbers gets removed from the original with the help of their index, then the vector gets reversed and return the value to continue working
  
  Finally return the vector sorted*/

  vector<int> arrOut;
  int current, currentPTR;

 while(data.size() != 0) {
    current = data[0];
    currentPTR = 0;

    for(int i = 0; i < data.size(); i++)
      if(data[i] < current){
        current = data[i];
        currentPTR = i;
      }

    arrOut.push_back(current);
    data.erase(data.begin() + currentPTR);
  }

  reverse(arrOut.begin(), arrOut.end());

  return arrOut;
}

void scanner1(vector<int> arr) {
  /* This scanner begin with the first and end with the last*/

  /* while the vector with M values are above 0 continues:
  First; Get the first value with their index using the function (atIndex) the removes from the vector the value
  Second; Run a "for" for all values to determine if it exists therefore if its true then add the value (atIndex) to the array "finded" at their corresponding index
  Third: If it´s not founded then the flag activates and add -1 to the number that isn´t */

  int srch, srchIndex;
  bool isFound;

  while(toFind.size() != 0) {
    isFound = false;
    srch = toFind[0];
    srchIndex = atIndex(toFindCP, srch);
    toFind.erase(toFind.begin());

    for(int i = 0; i < arr.size(); i++) {
      if(srch == arr[i]) {
        finded[srchIndex] = i;
        isFound = true;
        break;  
      }
    }

    if(isFound == false) {
      finded[srchIndex] = -1;
    }
  }
}

void scanner2(vector<int> arr) {
  /* This scanner begin with the last and end with the begin thus is used the "reverse" function*/

  /*There the same*/
  
  /* while the vector with M values are above 0 continues:
  First; Get the first value with their index using the function (atIndex) the removes from the vector the value
  Second; Run a "for" for all values to determine if it exists therefore if its true then add the value (atIndex) to the array "finded" at their corresponding index
  Third: If it´s not founded then the flag activates and add -1 to the number that isn´t */

  reverse(arr.begin(), arr.end());
  int srch, srchIndex;
  bool isFound;

  while(toFind.size() != 0) {
    isFound = false;
    srch = toFind[0];
    srchIndex = atIndex(toFindCP, srch);
    toFind.erase(toFind.begin());

    for(int i = 0; i < arr.size(); i++) {
      if(srch == arr[i]) {
        finded[srchIndex] = i;
        isFound = true;
        break;  
      }
    }

    if(isFound == false) {
      finded[srchIndex] = -1;
    }
  }
}


int main() {
  /* First; Calls the "askData" function to ask the initia values if it return 0 then the values of the vector are greater than 0 in the case that´s -1 then the program exits because we can´t work
  Second; If the M values are greater than 0 it means that there are values that need to check if it exists
  Then if the M values are greater than 2 then it uses multiple threads to maximize the speed of problem solving
  If the M values are 1 then it has no sense to use multiple threads because there´s no other value to process than himself
  Thread; The join, waits to the current thread to finish the process
  Third; Display the sorted vector with the N values then display the M values and their index values
  */

  bool ret;
  ret = askData();

  if(ret == 0) {
    arrs = sort(arrs);

    if(Mdata > 0) {
      if(Mdata >= 2) {
        thread th1(scanner1, arrs);
        thread th2(scanner2, arrs);

        th1.join();
        th2.join();
      }
      else {
        thread th1(scanner1, arrs);
        th1.join();
      }
      
      cout<<endl;
      display(arrs);

      for(int i = 0; i < Mdata; i++) {
        cout<<toFindCP[i]<<" "<<finded[i]<<endl;
      }
    }

  }

  else {
    return ret;
  }
}