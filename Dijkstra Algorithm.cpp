/*
Axel Ricardo Hernandez Montes de Oca
A01369965
Last Modified: 05/11/2021
*/


/*
Runing considerations
Tested on Linux and Replit.com

Command: {
  clang++-7 -pthread -std=c++17 -o main A01369965_Act3.2.cpp
  ./main
}

*/

#include <iostream>
#include <vector>

using namespace std;

struct STCdata {
    int cost;
    int node;
};

int n;
vector<vector<int>> w;

void askData() {
    int ntmp;
    vector<int> tmp;
    cout<<endl;
    cin>>n;

    for(int i = 0; i<n; i++) {
        tmp.clear();
        for(int j = 0; j<n; j++) {
            cout<<endl;
            cin>>ntmp;
            tmp.push_back(ntmp);
        }
        w.push_back(tmp);
    }
}

STCdata MIN(vector<int> dat) {
    int tmp = -2;
    int val;
    STCdata ret;

    for(int i = 0; i<dat.size(); i++) {
        val = dat[i];
        if(val != 0 && val != -1) {
            if(tmp == -2) {
                tmp = val;
                ret = {val, i};
            }
            else {
                if(val<tmp) {
                    tmp = val;
                    ret = {val, i};
                }
            }

        }
    }

    return ret;
}

vector<string> reCreate() {
    vector<string> tmp;
    for(int i = 0; i<n; i++) {
        tmp.push_back("nil");
    }
    return tmp;
}

void operation(vector<vector<int>> dat) {
    int tmp, count;
    bool flag;
    STCdata mn, mnAlt;
    vector<string> cont = reCreate();

    for(int x = 0; x<n; x++){
        for(int y = 0; y<n; y++) {
            if(x == y) {
                //cout<<"Sign: "<<x<<endl;
            }
            else {
                tmp = dat[x][y];
                mn = MIN(dat[x]);

                if(mn.cost == tmp) {
                    cont[y] = tmp;
                    cout<<"Node1: "<<x+1<<" to Node2: "<<y+1<<" : "<<tmp<<endl;
                }
                else {
                    count = 0;
                    flag = true;
                    //cout<<"Min: "<<mn.node<<" | "<<mn.cost<<endl;

                    while (flag) {
                        count += mn.cost;
                        mnAlt = MIN(dat[mn.node]);
                        if(mnAlt.cost == dat[mn.node][y]) {
                            count += mnAlt.cost;
                            //cout<<"if ";
                        }
                        else {
                            if(dat[x][y] == -1) {
                                count += dat[mn.node][y];
                            }
                            else {
                                count = dat[x][y];      
                            }
                            
                            //cout<<"else ["<<x<<"]  ";
                        }
                        cout<<"Node1: "<<x+1<<" to Node2: "<<y+1<<" : "<<count<<endl;
                        flag = false;
                    }
                }
            }
        }
        cout<<endl;
    }
}

int main() {
    askData();
    operation(w);   
}
