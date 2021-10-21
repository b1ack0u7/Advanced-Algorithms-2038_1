/*
Axel Ricardo Hernandez Montes de Oca
A01369965
20/10/2021

RUN Command: {
  clang++-7 -pthread -std=c++17 -o main A01369965_Act3.3.cpp
  ./main
}
*/
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
 
struct datas {
  int n;
  vector<int> v;
  vector<int> w;
  int maxw;
};

datas askData() {
  int n,tmps,w;
  vector<int> tmp;
  vector<int> tmp2;

  cout<<endl;
  cin>>n;

  for(int i = 0; i<n; i++) {
    cout<<endl;
    cin>>tmps;
    tmp.push_back(tmps);
  }

  for(int i = 0; i<n; i++) {
    cout<<endl;
    cin>>tmps;
    tmp2.push_back(tmps);
  }

  cout<<endl;
  cin>>w;
  return datas({n,tmp,tmp2,w});
} 

int max(int a, int b)
{
    return (a > b) ? a : b;
}
 
void knapsack(int maxcap, vector<int> w, vector<int> v, int n)
{
  //Loads the variables to be used
  //Create a vector inside a vector to be like -> [][]
  int i, j;
  vector<vector<int>> k(n + 1, vector<int>(maxcap + 1));

  for(i = 0; i <= n; i++) {
    for(j = 0; j <= maxcap; j++) {
      //If its 0 the asigns 0
      if (i == 0 || j == 0) {
        k[i][j] = 0;
      }   
      //Check the previous data from k vector or the previous data plus de previous value of $
      else if (w[i - 1] <= j) {
        k[i][j] = max(v[i - 1] + k[i - 1][j - w[i - 1]], k[i - 1][j]);
      }  
      //Assign normal value
      else {
        k[i][j] = k[i - 1][j];
      }
    }
  }

  cout<<endl;
  cout<<k[n][maxcap];
}

int main() {
  datas dat = askData(); 
  knapsack(dat.maxw, dat.w, dat.v, dat.n);
}