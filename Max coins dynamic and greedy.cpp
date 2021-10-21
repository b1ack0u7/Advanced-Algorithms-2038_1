/*
Axel Ricardo Hernandez Montes de Oca
A01369965
Last Modified: 21/09/2021
*/


/*
Runing considerations
Tested on Linux and Replit.com

Command: {
  clang++-7 -pthread -std=c++17 -o main A01369965_Act1.2.cpp
  ./main
}

*/


#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* Globals */
struct STCvalues {
  int coin;
  int cant;
};

int Nval, Pval, Qval;
vector<int> Coins;
vector<STCvalues> STCvaluesDYN;
vector<STCvalues> STCvaluesGRE;
/* Globals */


/* Helps */
void displayVJ(string tag, vector<int> data) {
  /* Display all the items on the vector */
  cout<<tag;
  for(int i = 0; i < data.size(); i++) {
    cout << " " << data[i];
  }
  cout<<endl;
}

void displayStruct(vector<STCvalues> data, bool debug) {
  /* Display all the items on the vector Struct */

  /*Debug*/
  if(debug == true) {
    for(int i = 0; i < data.size(); i++) {
      cout<< "Moneda: $" << data[i].coin << " | Cantidad: " << data[i].cant<<endl;
    }
  }
  /*Debug*/

  /*Oficial*/
  else {
    reverse(data.begin(), data.end());
    for(int i = 0; i < data.size(); i++) {
      if(data[i].cant != 0) {
        cout<< "Moneda: $" << data[i].coin << " | Cantidad: " << data[i].cant<<endl;
      }
    }
  }
  /*Oficial*/

}
/* Helps */


void askData() {
  /* 
  1: Ask the Nvalues to itinerate and ask for list of coins
  2: Then sort the list of coins and result in [min -> max]
  3: Creates the savers "STCvaluesDYN" & "STCvaluesGRE" with a struct of {coins, cant}
  4: Ask for the Q&P values 

  */

  int tmp;

  cout<<"Nvalores: ";
  cin>>Nval;

  for(int i=0; i<Nval; i++) {
    cout<<endl;
    cin>>tmp;
    Coins.push_back(tmp);
  }
  sort(Coins.begin(), Coins.end());

  for(int i = 0; i < Coins.size(); i++) {
    STCvaluesDYN.push_back({Coins[i],0});
  }
  STCvaluesGRE = STCvaluesDYN;

  printf("\n P & Q\n");
  cout<<endl;
  cin>>Pval;

  cout<<endl;
  cin>>Qval;
}


void translateData(vector<int> usedCoins, int change) {
  /*
  What does this function do is, read the vector of "usedCoins" the process is simple
  1: Uses "change" to point to the last index then uses their result save on itself ("change") therefore it goes again put it into the "usedCoins" index and so on.
  2: Determina wich type of coin it is and adds to the struct of coins to later display;
  [?]*: used goto to save resources after finding where to save the coin on the structure
  */
  int actualCoin;
  while (change > 0) {
    actualCoin = usedCoins[change];
    for(int i = 0; i<STCvaluesDYN.size(); i++) {
      if(STCvaluesDYN[i].coin == actualCoin) {
        STCvaluesDYN[i].cant += 1;
        goto cnt;
      }
    }

    cnt:;
    change = change - actualCoin;
  }
}

int dynamicAlgorithm(vector<int> listCoins, int change) {
  /*
  1: Initialize; all de required data "countCoins" and "usedCoins" start with the resultant of Q & P "(change)" and all in zeros, the creates the "listALTCoins" to determine if an item of "listCoins" has passed
  2: Main "for"; used to itinerate in all the possible solutions for "change"
  2.1: Sub 1 "for"; used to filter the "listCoins" only to the change that had appeared as "cntCoins" then adds to the "listALTCoins" to avoid over processing
  2.2: Sub 2 "for"; itinerate throught the filtered "listALTCoins" check if "countCoins" [change-listALTCoins[j]] exist if, case true then to add "cntCoins" to itself and adds to "newCoin" amd this is when it stored all the good coins 
  2: Adds the results to the corresponding vector
  3: Then use "translateData" function to convert the noise into the coins that are needed
  4: Finally return the minimum used coins "countCoins" at the final index "change" - 1
  */ 
  change = change + 1;

  vector<int> countCoins(change, 0);
  vector<int> usedCoins(change, 0);

  vector<int> listALTCoins;

  for(int cns = 0; cns < change; cns++) {
    int cntCoins = cns;
    int newCoin = 1;

    /* Filter */
    for(int m = 0; m < listCoins.size(); m++) {
      if(cntCoins == listCoins[m]) {
        listALTCoins.push_back(cntCoins);
      }
    }
    /* Filter */

    /* DEBUG
    cout<<"Min ";
    for(int i=0; i<change; i++) {
      cout<<" "<<countCoins[i];
    }
    cout<<endl;
    
    cout<<"CENT: "<<cns<<endl;
    displayVJ("TR:",listALTCoins);
    cout<<endl;
    */

    for(int j = 0; j < listALTCoins.size(); j++) {
      if(countCoins[cns-listALTCoins[j]] + 1 < cntCoins) {
        cntCoins = countCoins[cns-listALTCoins[j]] + 1;
        newCoin = listALTCoins[j];
      }
    }

    countCoins[cns] = cntCoins;
    usedCoins[cns] =  newCoin;
  }
  
  /*cout<<"Minimo: "<<countCoins[change-1]<<endl;*/
  translateData(usedCoins, change-1);

  return countCoins[change-1];
}

int greedyAlgorithm(vector<int> listCoins, int change) {
  /*
  1: Initialize the variables "coin": used to store the "change", "conCount": used to store how many coins where they used
  2: Reverse the "listCoins" and "STCvaluesGRE" because the greedy algorithm requires that consume the biggest number and because the dara passed is [min -> max] needs to convert to [max -> min]
  3: Use a for to itinerate throught the "listCoins" the use the "coin" to determine how many times it need to be used
  4: Then Adds to the "coinCount" and save it to "STCvaluesGRE" and multiply the "coin" with the actualCoin and rest the result from "coin"
  5: Reverse the saved data "STCvaluesGRE"
  6: Return the minimum coin used "coinCount"
  */
  int coin;
  int coinCount = 0;
  reverse(listCoins.begin(), listCoins.end());
  reverse(STCvaluesGRE.begin(), STCvaluesGRE.end());

  for(int i = 0; i<listCoins.size(); i++) {
    coin = floor(float (change) / float (listCoins[i]));
    coinCount += coin;
    STCvaluesGRE[i].cant = coin;
    change -= (coin * listCoins[i]);
  }

  reverse(STCvaluesGRE.begin(), STCvaluesGRE.end());
  return coinCount;
}


int main() {
  /*
  **: "Coins" vector are structured as [min -> max] and so the Savers {"STCvaluesDYN", "STCvaluesGRE"} are the same but with this struct {coin, cant}
  1: Ask the data
  2: Uses the "dynamicAlgorithm" function args ["Coins": the vector list of all the available coins, "change": the result between PQ]
  2.1: Uses the "translateData" function
  3: Uses the "greedyAlgorithm" function args ["Coins": the vector list of all the available coins, "change": the result between PQ]
  4: Display the save struct args ["STCvaluesDYN": the vector that stores the resultant coins, "false": show on release build]
  5: Display the save struct args ["STCvaluesGRE": the vector that stores the resultant coins, "false": show on release build]
  */
  int change, dynMin, greedMin;

  askData();
  change = Qval - Pval;

  dynMin = dynamicAlgorithm(Coins, change);
  greedMin = greedyAlgorithm(Coins, change);

  cout<<"Dynamic algorithm & Min: "<<dynMin<<endl;
  displayStruct(STCvaluesDYN, false);

  cout<<endl;

  cout<<"Greedy algorithm & Min: "<<greedMin<<endl;
  displayStruct(STCvaluesGRE, false);
}