/*
Descricion: 
El programa toma valores y datos de una ciudad, con los cuales se armara un conjunto de nodos, sobre los que estara aplicando distintos alogritmos
tanto para saber las conexiones, caminos mas cortos para pasar por cada central, el camino que deberia tomar para llegar a todas las colonias
y como conectar posibles colonias nuevas a las centrales, procensando los datos y brindando esta informacion dentro de un archivo de texto generado.

Axel Ricardo Hernandez Montes de Oca    A01369965
Daniel Daniel Amaya Gutierrez           A01769048
Last Modified: 24/11/2021

****Runing considerations****
Tested on Linux and Replit.com

Command: {
  clang++-7 -pthread -std=c++17 -o main A01369965_ActInt2.cpp
  ./main
}
*/

#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
using namespace std;

//Se definen las estructuras que tendran los vectores y nodos
//Colonias
struct STCcolonias {
    string name;
    int x;
    int y;
    bool isCentral;
};
//Conexiones entre colonias
struct STCconexiones {
    string col1;
    string col2;
    int cost;
    bool alreadyPass = false;
};
//Nuevas colonias
struct STCnvColonias {
    string name;
    int x;
    int y;
};

//Variables del input inicial
int nColonias=0,nConexiones=0,nNuevasColonias=0;

//Vectores donde se almacenara la informacion
vector<STCcolonias> colonias;
vector<STCconexiones> conexiones;
vector<STCnvColonias> nvColonias;

//Vector donde se almacena lo que se escribira dentro del archivo txt
vector<vector<string>> output;

//Funcion para llamar los datos del input
void askData() {
    string name1, name2;
    int x,y,cost,tmp;
    bool isCentral;

    cin >> nColonias;
	cin >> nConexiones;
	cin >> nNuevasColonias;

    for(int i = 0; i<nColonias; i++) {
        cin>>name1;
        cin>>x;
        cin>>y;
        cin>>tmp;
        if(tmp == 1) {isCentral = true;}
        else {isCentral = false;}

        colonias.push_back({name1, x, y, isCentral});
    }

    for(int i = 0; i<nConexiones; i++) {
        cin>>name1;
        cin>>name2;
        cin>>cost;

        conexiones.push_back({name1, name2, cost, false});
    }

    for(int i = 0; i<nNuevasColonias; i++) {
        cin>>name1;
        cin>>x;
        cin>>y;

        nvColonias.push_back({name1, x, y});
    }
}

//Esta clase es auxiliar ya que contiene funciones en la cual transforma los datos a un grafo con forma [][] para poderlo trabajar en los algoritimos
//Tambien contiene una funcion que hace un join de vector a string
class AuxiliaryClass {
    private:
        int finder(string name1, string name2) {
            int tmp;
            for(int i = 0; i<conexiones.size(); i++) {
                if(name1 == conexiones[i].col1 && name2 == conexiones[i].col2) {
                    tmp = conexiones[i].cost;
                    break;
                }
                else if (name1 == conexiones[i].col2 && name2 == conexiones[i].col1) {
                    tmp = conexiones[i].cost;
                    break;
                }
            }
            return tmp;
        }

    public:
        template <typename T>
        string join(const T& v, const string& delim) {
            ostringstream s;
            for (const auto& i : v) {
                if (&i != &v[0]) {
                    s << delim;
                }
                s << i;
            }
            return s.str();
        }

        int** generateGraph(vector<string> names, int len) {
            int** MainNode = new int*[len];

            for(int i = 0; i<len; i++) {
                MainNode[i] = new int[len]; 
            }

            for(int y = 0; y<len; y++) {
                for(int x = 0; x<len; x++) {
                    MainNode[x][y] = finder(names[y],names[x]);
                }
            }

            return MainNode;
        }
};

// Clase para realizar la primera parte del output, siendo la conexion de colonias de forma optima
//El primer algoritmo tiene una complejidad de nivel O(nm) 
class E1 {
    private:
        //----------------------------------------------------------------------------------
        struct STCbindings {
            string name;
            vector<STCconexiones> conex = {};
        };

        vector<STCconexiones> cp;
        //----------------------------------------------------------------------------------
        
        //Esta funcion obtiene el minimo peso de todas las opciones de las conexiones disponibles
        STCconexiones getMin(string name) {
            STCconexiones tmp = {"","",INT_MAX};
            int idx = 0;

            for(int i = 0; i<cp.size(); i++) {
                if(cp[i].col1 == name || cp[i].col2 == name) {
                    if(cp[i].cost < tmp.cost) {
                        tmp = cp[i];
                        idx = i;
                    }
                }
            }
            cp.erase(cp.begin() + idx);

            return tmp;
        }

        //Esta funcion traza un camino para ver si es factible en cuyo caso de que encuentre items dobles se utilizara el del menor costo
        //Esto asegura de que se pase por todos los nodos con el menor coste
        vector<STCconexiones> tracePath(vector<STCconexiones> data) {
            vector<STCconexiones> result,tmp;
            STCconexiones item;
            vector<int> toBeDeleted;

            result.push_back(data[0]);
            string target = data[0].col2;
            data.erase(data.begin());

            while(data.size() != 1) {
                cout<<endl;
                toBeDeleted.clear();
                for(int i = 0; i<data.size(); i++) {
                    if(data[i].col1 == target || data[i].col2 == target) {
                        tmp.push_back(data[i]);
                        toBeDeleted.push_back(i);
                    }
                }

                //Delet passed data
                for(int i = 0; i<toBeDeleted.size(); i++) {
                    data.erase(data.begin() + toBeDeleted[i]);
                }

                //Checks if its only one item
                if(tmp.size() == 1) {
                    item = tmp[0];
                }
                else {
                    item = {"","",INT_MAX};
                    for(int i = 0; i<tmp.size(); i++) {
                        if(tmp[i].cost < item.cost) {
                            item = tmp[i];
                        }
                    }
                }

                //Add the min value
                result.push_back(item);
                if(item.col1 == target) {
                    target = item.col2;
                }
                else {
                    target = item.col1;
                }
            }

            result.push_back(data[0]);
            return result;
        }

        //Pasa por todos los candidatos y suma sus costos para obtener el coste final
        int getCost(vector<STCconexiones> data) {
            int cost = 0;
            for(int i = 0; i<data.size(); i++) {
                cost += data[i].cost;
            }
            return cost;
        }

        //Obtiene los nombres de los nodos
        vector<string> initializer() {
            vector<string> names;

            for(int i = 0; i<colonias.size(); i++) {
                names.push_back(colonias[i].name);
            }
            return names;
        }
        
    public:
        //Ejecuta las funciones
        void Do() {
            int finalCost = 0;
            vector<string> names = initializer();
            vector<STCconexiones> result;
            vector<string> out;
            cp = conexiones;
            
            for(int i = 0; i<names.size(); i++) {
                result.push_back(getMin(names[i]));
            }

            result = tracePath(result);
            finalCost = getCost(result);

            //Print
            cout<<"1 – Cableado óptimo de nueva conexión "<<endl;
            out.push_back("1 – Cableado óptimo de nueva conexión ");
            for(int i = 0; i<result.size(); i++) {
                cout<<result[i].col1<<" - "<<result[i].col2<<" "<<result[i].cost<<endl;
                out.push_back(result[i].col1 + " - " + result[i].col2 + " " + to_string(result[i].cost));
            }
            cout<<"Costo Total = "<<finalCost<<endl<<endl;
            out.push_back("Costo Total = " + to_string(finalCost));

            output.push_back(out);
        }
};

//La segunda clase del programa, contiene el algoritmo para el problema del agente viajero, utilizando B&B, tiene una complejidad O(n^2)
//puesto que se recorre la matriz de adyacencia n veces y en cada iteracion volvemos a recorrer todo el arreglo n veces
class E2 {
    private:
        //----------------------------------------------------------------------------------
        int *finalPath;
        bool *visited;
        int cost = INT_MAX;
        //----------------------------------------------------------------------------------
		//Esta funcion copia la ruta actual por la final y es la que nos ayuda al final con la impresion de la ruta optima
        void copyToFinal(int currentPath[], int len){
            for (int i=0; i<len; i++) {
                finalPath[i] = currentPath[i];
            }
            finalPath[len] = currentPath[0];
        }
		//Se encuentra el primer minimo dentro d ela orilla de la matriz y hasta el vertice del indice
        int firstMin(int **graph, int i, int len){
            int min = INT_MAX;
            for (int k=0; k<len; k++) {
                if (graph[i][k]<min && i != k) {
                    min = graph[i][k];
                }
            }
            return min;
        }
		//Encuentra el segundo minimo dentro de la orilla del vertice hasta llegar al indice i
        int secondMin(int **graph, int i, int len) {
            int first = INT_MAX, second = INT_MAX;
            for (int j=0; j<len; j++) {
                if (i == j) {
                    continue;
                }
                if (graph[i][j] <= first){
                    second = first;
                    first = graph[i][j];
                }
                else if (graph[i][j] <= second && graph[i][j] != first) {
                    second = graph[i][j];
                }
            }
            return second;
        }
		//Iremos visitando los niveles para todos los vertices y llamandose recursivamente
        void TSPpeso(int **graph, int currentBound, int currentWeight, int level, int currentPath[], int len) {
        	//Si ya llego al ultimo nivel, armamos el costo final y retornamos lo que en este caso ya recaudo como el minimo costo
            if (level==len){
                if (graph[currentPath[level-1]][currentPath[0]] != 0){
                    int currentCost = currentWeight + graph[currentPath[level-1]][currentPath[0]];
                    if (currentCost < cost){ // Si el ultimo nivel resulta tener un costo menor, actualizamos el valor del costo final, en otro caso se queda igual
                        copyToFinal(currentPath, len);
                        cost = currentCost;
                    }
                }
                return;
            }
            // En caso de aun no llegar al final, iremos calculando los costos y rutas 
            for (int i=0; i<len; i++){
            	//Si aun no se visita el nivel y adem�s no es el mismo en donde estabamos
                if (graph[currentPath[level-1]][i] != 0 && visited[i] == false){
                	//Se actualizan los pesos actuales y la poda actual
                    int temp = currentBound;
                    currentWeight += graph[currentPath[level-1]][i];
        			//Verificamos si estamos en el nivel 2, y actualizamos la poda
                    if (level==1){
                        currentBound -= ((firstMin(graph, currentPath[level-1], len) + firstMin(graph, i, len))/2);
                    }
                    else{
                        currentBound -= ((secondMin(graph, currentPath[level-1], len) + firstMin(graph, i, len))/2);
                    }
					//Si los datos son menores al costo que tenemos, podemos tomar la ruta como la optima, de otro modo podamos el nivel y se llama recursivamente
                    if (currentBound + currentWeight < cost){
                    	//Actualizamos el nivel
                        currentPath[level] = i;
                        //Actualizamos que ya visitamos el nodo en este nivel
                        visited[i] = true;
                        //Se repite todo pero ya con el nodo ponderado
                        TSPpeso(graph, currentBound, currentWeight, level+1, currentPath, len);
                    }
        			//De otro modo actualizamos los datos de peso y poda
                    currentWeight -= graph[currentPath[level-1]][i];
                    currentBound = temp;
        			//Volvemos a hacer el arreglo de visitar con false
                    memset(visited, false, len);
                    //Actualizamos la ruta que esta actualmente
                    for (int j=0; j<=level-1; j++) {
                        visited[currentPath[j]] = true;
                    }
                }
            }
        }
		// La funcion principal para el STP
        void TSP(int **adj, int len) {
        	// Hcemos la variable del camino actual
            int currentPath[len+1];
            // poda actual
            int currentBound = 0;
            // llenamos la ruta actual con -1
            memset(currentPath, -1, len+1);
            // Llenamos los visitados como 0
            memset(visited, 0, len);
        	//Armamos la poda con el primer minimo y el segundo minimo para todas las esquinas
            for (int i=0; i<len; i++) {
                currentBound += (firstMin(adj, i, len) + secondMin(adj, i, len));
            }
            //Redondeamos
            currentBound = (currentBound&1)? currentBound/2 + 1 : currentBound/2;
        	//Hacemos el primer visitado como verdadero
            visited[0] = true;
            //Hacemos nuestro primera ruta iniciando en 0
            currentPath[0] = 0;
        	// Llamos otra funcion para el peso
            TSPpeso(adj, currentBound, 0, 1, currentPath, len);
        }

    public:
        void Do() {
        	// Obtenemos la longitud de las colonias
            int len = colonias.size();
            //Hacemos la variable que guarda la ruta por la que es optima
            finalPath = new int[len+1];
            // Hacemos otra para verificar si esta guardado o no
            visited = new bool[len];
            //Vector para al final poder desplegar los nombres
            vector<string> names, traceNames;
			//Guardamos los nombres de las colonias
            for(int i = 0; i<len; i++) {
                names.push_back(colonias[i].name);
            }
			//Creamos la matriz de adyacencia
            int **graph = AuxiliaryClass().generateGraph(names, len);
			// Mandamos la matriz junto con la longitud
            TSP(graph, len);

            //Con el patron obtenido, armamos la lista con los nombres
            for(int i=0; i<=len; i++) {
                traceNames.push_back(colonias[finalPath[i]].name);
            }
            // Lo juntamos en unn string para el output en el txt
            string finalTrace = AuxiliaryClass().join(traceNames, " - ");

            //Lo imprimimos
            cout<<"2 – La ruta óptima es "<<endl;
            cout<<finalTrace<<endl;
            cout<<"Costo Total = "<<cost<<endl<<endl;
            // A�adimos a la variable del output del txt
            output.push_back({"2 – La ruta óptima es ", finalTrace, "Costo Total = " + to_string(cost)});
        }
};

//La tercera clase del programam contiene el algoritmo para pasar por las centrales con el menor coste haciendo uso del algoritmo de dijkstra
//Con una compleijad de O((N + M log M)*MN)
class E3 {
    private:
        //----------------------------------------------------------------------------------
        struct STCresult {
            string name = "";
            int cost = INT_MAX;
            vector<string> trace = {};
        };

        vector<string> spliter(string data) {
            vector<string> tmp;
            string word = "";
            for(auto x : data) {
                if(x == ',') {
                    tmp.push_back(word);
                    word = "";
                }
                else {
                    word = word + x;
                }
            }
            return tmp;
        }
        //----------------------------------------------------------------------------------

        //Esta funcion reordena para que el string introducido quede hasta arriba del stack
        vector<string> reorderFirst(string first) {
            vector<string> names;
            names.push_back(first);
            for(int i = 0; i<colonias.size(); i++) {
                if(first != colonias[i].name) {
                    names.push_back({colonias[i].name});
                }
            }
            return names;
        }

        //Obtiene el valor minimo de los puntos no visitados
        int minimumDist(int *dist, bool *visited, int len) {
            int min = INT_MAX, idx;
            for(int i=0;i<len;i++) {
                if(visited[i] == false && dist[i]<=min) {
                    min=dist[i];
                    idx=i;
                }
            }
            return idx;
        }

        //El clasico algoritmo de Dijkstra para obtener el camino mas rapido
        vector<STCresult> Dijkstra(int** node, int len, vector<string> names) {
            int *dist = new int[len];                          
            bool *visited = new bool[len];
            string *trace = new string[len];
            vector<STCresult> res;

            for(int i = 0; i<len; i++) {
                dist[i] = INT_MAX;
                visited[i] = false;	
            }
            
            dist[0] = 0;         
            
            for(int i = 0; i<len; i++) {
                int m = minimumDist(dist, visited, len); 
                visited[m] = true;

                for(int i = 0; i<len; i++) {
                    if(!visited[i] && node[m][i] && dist[m] != INT_MAX && dist[m] + node[m][i] < dist[i]) {
                        dist[i] = dist[m] + node[m][i];
                        trace[i] = trace[m]+names[i]+",";
                    }
                }
            }

            for(int i = 0; i<len; i++) {
                trace[i] = names[0]+","+trace[i];
                res.push_back({names[i], dist[i], spliter(trace[i])});
            }

            return res;
        }

    public:  
        //Esta funcion ejecuta el algoritmo
        void Do() {
            //Inicializa las variables
            int **graph;
            vector<string> nameCentrals;
            vector<string> names;
            vector<STCresult> result, ffinal;
            STCresult tmp;
            int len = colonias.size();

            for(int i = 0; i<colonias.size(); i++) {
                if(colonias[i].isCentral) {
                    nameCentrals.push_back(colonias[i].name);
                }
            }

            if(nameCentrals.size() > 1) {
                while(nameCentrals.size() != 0) {
                    //Obtiene los nombres de los nodos con sus conexiones con otros
                    names = reorderFirst(nameCentrals[0]);
                    //Crea el grafo
                    graph = AuxiliaryClass().generateGraph(names, len);
                    //Hace el algoritmo para checar el menor valor
                    result = Dijkstra(graph, len, names);
                    //Borra el primer item de las centrales
                    nameCentrals.erase(nameCentrals.begin());

                    if(nameCentrals.size() == 0) {
                        //Si no hay mas centrales se acabo
                        break;
                    }
                    else{
                        //Obtiene los valores mas bajos de las centrales ya con el peso del algoritmo de dijkstra y lo agrega 
                        for(int i = 0; i<result.size(); i++) {
                            for(int j = 0; j<nameCentrals.size(); j++) {
                                if(result[i].name == nameCentrals[j] && result[i].cost < tmp.cost) {
                                    tmp = result[i];
                                }
                            }
                        }
                        ffinal.push_back(tmp);
                    }
                }

                //Translate Data
                //Traduce los datos y elimina los valores repetidos
                STCresult translated;
                translated.cost = 0;
                for(int i = 0; i<ffinal.size(); i++) {
                    translated.cost += ffinal[i].cost;
                    translated.trace.insert(translated.trace.end(), ffinal[i].trace.begin(), ffinal[i].trace.end());
                }
                unique(translated.trace.begin(), translated.trace.end());
                
                //Print
                string trace = AuxiliaryClass().join(translated.trace, " - ");
                cout<<"3 – Caminos más cortos entre centrales"<<endl;
                cout<<trace<<" = "<<translated.cost<<endl<<endl;
                output.push_back({"3 – Caminos más cortos entre centrales", trace + " = " + to_string(translated.cost)});
            }
            else {
                cout<<"3 – Caminos más cortos entre centrales"<<endl;
                cout<<nameCentrals[0]<<" = 0"<<endl<<endl;
                output.push_back({"3 – Caminos más cortos entre centrales", nameCentrals[0] + " = 0"});
            }
        }
};

//La cuarta clase usaremos geometria computacional para las distancias entre las nuevas colonias y las centrales
//Tiene una complejidad de O(nm) donde n es el numero de nuevas colonias y m el numero de las colonias
class E4 {
    private:
    	// Calcularemos la distancia entre las coordenadas de la nueva colonia con la central en este momento
    	//La formula es la distancia euclidiana
        float distanciaEuclidiana(float x2,float y2,float x1,float y1){
            double dx = x2 - x1;
            double dy = y2-y1;
            double distancia = dx * dx + dy * dy; 
            distancia = sqrt(distancia);
            return distancia;
        }

    public:
    	//Dentro del do se hara lo siguiente
        void Do(){
        	//Creamos las variables que nos ayudaran
            int min,minAct=0,indice;
            //Vector que usaremos en el txt
            vector<string> out;
            cout<<"4 – Conexión de nuevas colonias"<<endl;
            out.push_back("4 – Conexión de nuevas colonias");
            //Recorreremos todas las nuevas colonias
            for (int j=0;j<nvColonias.size();j++){
            	min=INT_MAX;
            	//Recorreremos dentro de cada nueva colonia, las colonias
                for (int i=0;i<colonias.size();i++){
                	//Si la colonia es central, llamaremos la funcion de las distancias
                    if (colonias[i].isCentral==true){
                    	//El minimo actual sera comparada con el minimo almacenado y si es menor se actualiza
                        minAct=distanciaEuclidiana(colonias[i].x,colonias[i].y,nvColonias[j].x,nvColonias[j].y);
                        if (minAct<min){
                            min=minAct;
                            //El indice nos indica cual colonia central fue la mas cercana
                            indice=i;
                        }
                        else{
                            min=min;
                        }
                    }
                }
                //Imprimimos la colonia nueva junto con la posicion de la colonia en el indice hecho
                cout<<nvColonias[j].name<<" debe conectarse con "<<colonias[indice].name<<endl;
                out.push_back(nvColonias[j].name + " debe conectarse con " + colonias[indice].name);
            }
            output.push_back(out);
        }
};

int main(){
	//Llamamos la funcion de askData para la captura de los datos
    askData();

	//Llamamos cada clase para cada algoritmo
    E1().Do();
    E2().Do();
    E3().Do();
    E4().Do();

    //Output txt
    ofstream myfile;
    myfile.open ("checkingA01369965.txt");
    for(int i = 0; i<output.size(); i++) {
        for(int j = 0; j<output[i].size(); j++) {
            myfile << output[i][j] + "\n";
        }
        myfile << "\n";
    }
    myfile.close();
}
