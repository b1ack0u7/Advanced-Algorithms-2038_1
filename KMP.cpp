/*
Axel Ricardo Hernandez Montes de Oca
A01369965
Last Modified: 05/10/2021


Runing considerations
Tested on Linux and Replit.com

Command: {
  clang++-7 -pthread -std=c++17 -o main KMP_Act2.1.cpp
  ./main
}

*/

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/* Data declaration */
struct dataSTC {
  vector<char>Finder;
  vector<char>Sample;
  vector<int>Idx;
};

vector<dataSTC> dataItin;
vector<string> htmlCode;
/* Data declaration */

/* Display */
void displayV(vector<int> data) {
  for(int i = 0; i<data.size(); i++) {
    cout<<data[i]<<" ";
  }
  cout<<endl;
}
/* Display */

/* Data initialization */
void askData() {
  int N;
  string tmp;

  vector<char>Finder;
  vector<char>Sample;

  cout<<endl;
  cin>>N;


  for(int j = 0; j<N; j++) {
    Finder.clear();
    Sample.clear();

    cout<<endl;
    cin>>tmp;
    for(int i = 0; i<tmp.length(); i++) {
      Finder.push_back(tmp[i]);
    }
    
    cout<<endl;
    cin>>tmp;
    for(int i = 0; i<tmp.length(); i++) {
      Sample.push_back(tmp[i]);
    }

    dataItin.push_back({Finder, Sample});
  }
}

void containerFinder(vector<char> finder, int M, int* cont) {
  // Create a container to save the previous suffixes
  int len = 0;
  cont[0] = 0;
  int i = 1;

  while (i < M) {
    if (finder[i] == finder[len]) {
      len++;
      cont[i] = len;
      i++;
    } 
    else {
      if (len != 0) {
        len = cont[len - 1];
      }
      else {
        cont[i] = 0;
        i++;
      }
    }
  }
}
/* Data initialization */

/* Algorithm */
vector<int> KMP(vector<char> finder, vector<char> sample) {
  vector<int>idx;
  int M = finder.size();
  int N = sample.size();
  int cont[M];

  containerFinder(finder, M, cont);

  int i = 0;
  int j = 0;

  while (i < N) {
    if (finder[j] == sample[i]) {
      j++;
      i++;
    }

    if (j == M) {
      idx.push_back(i-j);
      j = cont[j - 1];
    }

    else if (i < N && finder[j] != sample[i]) {
      if (j != 0)
        j = cont[j - 1];
      else
        i = i + 1;
    }
  }

  return idx;
}
/* Algorithm */

/* HTML */
void htmlCast(dataSTC data) {
  string tmp = "";
  int z = 0;
  bool flag = true;

  string redTag = "<span style=\"color: red\">";
  for(int i = 0; i<data.Finder.size(); i++) {
    redTag += data.Finder[i];
  }
  redTag += "</span>";


  for(int i = 0; i<data.Sample.size(); i++) {
    if(flag == true && i == data.Idx[z]) {
      tmp += redTag;
      i = data.Idx[z]+data.Finder.size();

      if(z != data.Idx.size()) {
        z += 1;
      }
      else {
        flag = false;
      }
    }
    else {
      tmp += data.Sample[i];
    }
  }
  
  htmlCode.push_back(tmp);
}

void saveFile() {
  ofstream myfile;
  myfile.open("KMP.html");
  for(int i = 0; i < htmlCode.size(); i++) {
    myfile << htmlCode[i];
    myfile <<"<br>";
  }
  myfile.close();

  cout<<endl;
  cout<<"File saved"<<endl;
}
/* HTML */

int main()
{
  askData();
  cout<<endl;

  for(int i = 0; i < dataItin.size(); i++) {
    dataItin[i].Idx = KMP(dataItin[i].Finder, dataItin[i].Sample);
    displayV(dataItin[i].Idx);
  }
  
  for(int i = 0; i < dataItin.size(); i++) {
    htmlCast(dataItin[i]);
  }
  
  saveFile();
}