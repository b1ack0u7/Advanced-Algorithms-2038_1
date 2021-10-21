//Jonhatan A01769156
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


string leerArchivo(string file_name) {
    int n;
    string pat, txt;
    stringstream content;
    ifstream file;
    file.open(file_name);
    if(!file) {
        cout<<"No se puede abrir el archivo\n";
        exit(1);
    } else {
        content << file.rdbuf();
        txt = content.str();
        return txt;
    }
}

void manacher(string S) {
		vector<int> res(2,0); // resultado (inicio, longitud)
	  	int N, maxLong, maxCentro, C, Li, Ri;
	  	bool expansion;
	  	string T;
	  	if (S.length() == 0){   // S es nulo
            cout << "String de tamaño 0" << "\n";
		}
	    // Se procesa S
		T = "";
		for (char c:S){
			T = T+"|"+c;
		}
		T = T+"|";
	  	N = T.length();
	  	int L[N];
	  	// longitud y centro del maximo palindromo encontrado
	  	maxLong = 1;
	  	maxCentro = 1;		// Hasta ahora posicion 1
	  	
	  	C = 1;
	  	Li = 0;
	  	Ri = 0;
	 	
	  	expansion = false; // true si requiera expansion
	
	  	L[0]=0; 
		L[1]=1;
	  	
	  	for (Ri=2; Ri<N; Ri++){
	  		
	    	expansion = false;
	    	Li = C - (Ri-C);

	    	if ((C+L[C])-Ri >= 0){
	      		if (L[Li] < (C+L[C])-Ri){   // Caso 1
	      			L[Ri] = L[Li];
				}
				
				else if (L[Li] == (C+L[C])-Ri && (C+L[C]) == N-1){ // Caso 2
					L[Ri] = L[Li];
				}
				
				else if(L[Li] == (C+L[C])-Ri && (C+L[C]) < N-1){  // Caso 3
					L[Ri] = L[Li];
					expansion = true; // requiere expansion
				}
				
				else if(L[Li] > (C+L[C])-Ri){ // Caso 4
					L[Ri] = (C+L[C])-Ri;
					expansion = true; // requiere expansion
				}
			
			}
			
		    else{
		    	L[Ri] = 0;
		    	expansion = true;  // requiere expansion
		    }
			    
			    
		    // hacer la expansion hasta donde se pueda
		    if (expansion) {
		    	while ((Ri+L[Ri]) < N && (Ri-L[Ri]) > 0 && T[Ri+L[Ri]+1] == T[Ri-L[Ri]-1]){
		    		L[Ri]++;
				}
			}
		    	
		    // si el nuevo pal?ndromo se expande mas alla de C    	
		    if (Ri+L[Ri] > (C+L[C])){
		    	C = Ri;
			}
				
			// Guardar longitud y centro del palindromo mas grande hasta ahora	
		    if(L[Ri] > maxLong){ 
				maxLong = L[Ri];
				maxCentro = Ri;
			}
		
	    }
		// obtener inicio y longitud del maximo palindromo encontrado recordando que la longitud de T es el doble de la de S
		// Regresa los resultados en base 1
        res[0] = ((maxCentro-maxLong)/2)+1; // inicio en S
        res[1] = res[0]+maxLong-1; // final en S
        cout << "Palindromo entre: " << res[0] << " y " << res[1] << "\n"; 	
}

void proceso(string txt, vector<int>&vec) {
    //virusxtreme
    vec[0] = 0;
    int len = 0;
    int i=1;
    while (i<txt.length()){
        if(txt[i]==txt[len]){
            len++;
            vec[i] = len;
            i++;
            continue;
        }
        else{
            if(len==0){
                vec[i] = 0;
                i++;
                continue;
            }
            else{
                len = vec[len-1];
                continue;
            }
        }
    }
}

void KMP(string pat,string txt) {
    //virusxtreme
    //wevirusxtremevqw
    //len of the strings
    int t = txt.length();//16
    int p = pat.length();//11
    vector<int>vec(p);
    vector<int>aux;
    bool entro = false;
    int inicio,termina;
    proceso(pat,vec);
    int i=0;//1,ya2,3,4,5,6,7,8,9,10,11
    int j=0;//ya,1,2,3,4,5,6,,7,8,9
    while(i<t){
        if(pat[j]==txt[i]){
            
            i++;
            j++;
            if (j == p) { 
                //cout<<i+1 - p <<' ';
                //inicio = i+1 - p;
                //termina = inicio - p;
                entro = true;
                aux.push_back(i-p);
                j = vec[j - 1]; 
            }
        }else {
            if (j == 0)
                i++;
            else
                j = vec[j - 1];
        }

    }
    
    if(entro){
        cout << "True" << " " ;
        for(int i=0; i< aux.size();i++){
            cout << aux[i]+1 <<" ";
        }

        cout<<"\n";
        
    }else{
        cout << "False" << "\n";
    }

    //cout << i << " " << j <<" "<< p <<"\n";
}

struct dataResulted {
    int initial;
    int end;
};

dataResulted LCSubStr(string X, string Y, int m, int n) {
	// Create a table to store
	// lengths of longest
	// common suffixes of substrings.
	// Note that LCSuff[i][j] contains
	// length of longest common suffix
	// of X[0..i-1] and Y[0..j-1].

	int LCSuff[m + 1][n + 1];
	int result = 0, position=0; // To store length of the
					// longest common substring

	/* Following steps build LCSuff[m+1][n+1] in
		bottom up fashion. */
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			// The first row and first column
			// entries have no logical meaning,
			// they are used only for simplicity
			// of program
			if (i == 0 || j == 0)
				LCSuff[i][j] = 0;

			else if (X[i - 1] == Y[j - 1]) {
				LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
				if (result<LCSuff[i][j]){
					result=LCSuff[i][j];
					position=max(i,j);
				}
				else{
					result=result;
				}
			}
			else
				LCSuff[i][j] = 0;
		}
	}
	position=position-(result-1);
	result=(position+result)-1;

	return dataResulted({position, result});
}

string reCasterFile(string f) {
    ifstream file(f);
    vector<string> tmp;
    string input;
    string tmpString = "";

    while(file >> input) {
        tmp.push_back(input);
        tmp.push_back(" ");
    }
    tmp.pop_back(); 
    
    for(int i = 0; i<tmp.size(); i++) {
        tmpString += tmp[i];
    }
    file.close();

    return tmpString;
}

int main(){
    //declaración de strings para poder leerlas del txt
    string trans1, trans2, mcode1, mcode2, mcode3;
    trans1 = leerArchivo("transmission1.txt");
    trans2 = leerArchivo("transmission2.txt");
    mcode1 = leerArchivo("mcode1.txt");
    mcode2 = leerArchivo("mcode2.txt");
    mcode3 = leerArchivo("mcode3.txt");
    
    //Llamado a la primer parte
    cout << "Parte 1 \n";
    KMP(mcode1,trans1);
    KMP(mcode2,trans1);
    KMP(mcode3,trans1);
    KMP(mcode1,trans2);
    KMP(mcode2,trans2);
    KMP(mcode3,trans2);
        cout<<endl;

    //Llamado a la segunda parte
    cout << "Parte 2 \n";
    manacher(trans1);
	manacher(trans2);
    cout<<endl;

    string t1, t2;
    t1 = reCasterFile("transmission1.txt");
    t2 = reCasterFile("transmission2.txt");
    dataResulted returned = LCSubStr(t1, t2, t1.length(), t2.length());

    cout << returned.initial << " " << returned.end;
}
