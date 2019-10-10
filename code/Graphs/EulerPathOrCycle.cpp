/*
Euler Path or Cycle O(n + m)

Grafo no dirigido:
-todos nodos con grado par (hay euler cycle)
-exactamente dos nodos con grado impar (hay euler path, empezando y terminando en estos nodos)

Grafo dirigido:
-todos los nodos tienen in_degree == out_degree (hay euler cycle)

-camino:
	todos los nodos excepto dos tienen in_degree == out_degree y estos dos cumplen que
	out_degree == in_degree + 1 (este es el inicio)
	in_degree == out_degree + 1 (este es el fin)

Si al hacer el algoritmo hay alguna arista q no fue recorrida no existe
euler path or cycle (esto puede pasar si el grafo no es conexo, por ejemplo)
*/

int mk[MAX]; //OJO este arreglo es para marcar aristas, el tamanno tiene q ser la cantidad de aristas
int pt[MAX]; //puntero para cada nodo, esto es para no recorrer aristas ya vistas varias veces
vector <pair <int, int> > g[MAX]; //nodo, id de arista
vector <int> v; //aqui se guarda el camino o ciclo en orden reverso

void dfs(int u) {
	for(; pt[u] < (int) g[u].size(); pt[u]++) {
		auto o = g[u][pt[u]];
		int v = o.first;
		int id = o.second;

		if(!mk[id]) {
			mk[id] = 1;
			dfs(v);
		}
	}

	v.push_back(u);
}