

#include "Graph.h"

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

Graph::Graph(int N)
{
	//Get numVertex. Create and initialize matrix
	numVertex = N;	
	matrix = new int *[N];
	for (int i = 0; i < N; i++){
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++){
			matrix[i][j] = 0;
		}		
	}


}
Graph::~Graph()
{
	delete matrix[numVertex];
}
Graph::Graph(const std::string& filepath, const char type){
	std::fstream fin;
	fin.open(filepath);
	if (fin.is_open())
	{
		int n;
		fin >> n;
		numVertex = n;

		matrix = new int *[n];
		for (int i = 0; i < n; i++){
			matrix[i] = new int[n];
			for (int j = 0; j < n; j++){
				matrix[i][j] = 0;
			}
		}	
		
		while (!fin.eof()){
			int v_from, v_to, weight=1;
			if (type == 'W')
				fin >> v_from >> v_to >> weight;
			else
				fin >> v_from >> v_to;

			this->setEdgeMatrix(v_from, v_to,weight);
			this->setEdgeList(v_from, v_to);
		}

	}

}


void Graph::setEdgeList(int v_from, int v_to){
	edgeList.push_back(
	std::pair<int,int> (v_from, v_to)
	);

}
void Graph::removeEdgeList(int v_from, int v_to){
	std::vector< std::pair<int, int> >::iterator it;

	for (it = edgeList.begin(); it != edgeList.end(); ++it){
		if ((it->first == v_from) && (it->second == v_to))
			edgeList.erase(it);
	}
}

void Graph::setEdgeMatrix(int v_from, int v_to, int weight){
	matrix[v_from][v_to] = weight;
	matrix[v_to][v_from] = weight;
}
void Graph::removeEdgeMatrix(int v_from, int v_to){
	matrix[v_from][v_to] = 0;
	matrix[v_to][v_from] = 0;
}


int Graph::ShortestPath(int from, int to){
	return 0;
}

static int counter = 1;
void Graph::FindPath(int from, std::vector<int> &checkedVert){
	
	for (int i = 0; i < numVertex; i++){
		if( (matrix[from][i] ==1)&&(checkedVert[i]==-1)){
			checkedVert[i] = counter;
			counter++;
			FindPath(i, checkedVert);
		}
	}
}


int * Graph::findBridges(){
	//1 connectivity component
	int topVert = 0;
	std::vector< std::pair<int, int> >::iterator curEdge;
	
		
	for (curEdge = edgeList.begin(); curEdge != edgeList.end(); ++curEdge){
		//delete i-th edge
		removeEdgeMatrix(curEdge->first, curEdge->second);
		

		std::vector<int> checkedVert;
		for (int i = 0; i < numVertex; i++){
			checkedVert.push_back(-1);
		}

		checkedVert[topVert] = 0;
		counter = 1;
		FindPath(topVert, checkedVert);
		bool f = false;
		for (auto i : checkedVert){
			if (i == -1)
				f = true;
		}
		if (f){
			std::cout << "(" << curEdge->first << "," << curEdge->second << ") is a bridge" << std::endl;
		}
		setEdgeMatrix(curEdge->first, curEdge->second,1);

	}
	return 0;
}

std::vector<int> Graph::salesman(const std::string& filepath){
	std::fstream fin;
	fin.open(filepath);
	if (fin.is_open())
	{
		fin >> startVert;
		std::vector<int> hamCyc;
		std::vector<int> _hamCyc;
		_hamCyc = computeSalesman(startVert);

		hamCyc.reserve(hamCyc.size() + _hamCyc.size());
		hamCyc.insert(hamCyc.end(), _hamCyc.begin(), _hamCyc.end());


	}		
	return{ 1 };
}

std::vector<int> Graph::computeSalesman(const int startV){
	std::vector<int> _hamCyc;
	for (int i = 0; i < numVertex; i++){
		if (matrix[startV][i] != 0){
			if (matrix[startV][i] == Graph::startVert)
				///..
			computeSalesman( matrix[startV][i] );
		}
		
			
	}
	return{ 1 };
}

class V{
public:
	V() = default;
	~V() = default;
	V(const V& newV) : vert(newV.vert), key(newV.key), par(newV.par)
	{}
	int vert;
	int key;
	int par;

	/*bool operator < (V & right) const {
	return this->key < right.key;
	}*/
};

bool operator < (V right, V left){
	return left.key < right.key;
}



const int inf = 100000;
std::vector<std::pair<int, int>>  Graph::minSpanningTree(int root){
	std::vector<std::pair<int, int>> A;
	std::priority_queue<V> queueV;
	bool * includedV = new bool[numVertex];
	int *keys = new int[numVertex];


	for (int i = 0; i < numVertex; i++){
		includedV[i] = 0;
		keys[i] = inf;

		V newV;
		newV.vert = i;
		newV.par = -1;
		if (i == root)
			newV.key = 0;
		else
			newV.key = inf;
		queueV.push(newV);
	}

	int cnt = 0;
	while (cnt<numVertex){

		V u{ queueV.top() };
		queueV.pop();
		if (!includedV[u.vert]){
			A.push_back({ u.par, u.vert });
			includedV[u.vert] = 1;
			cnt++;
		}

		for (int v = 0; v < numVertex;v++){
			if ((!includedV[v]) && (matrix[u.vert][v] != 0) && (keys[v]> matrix[u.vert][v])){
				V newV;
				newV.vert = v;
				newV.key = matrix[u.vert][v];
				keys[v] = newV.key;
				newV.par = u.vert;
				queueV.push(newV);
			}

		}

	}
	delete includedV;
	delete keys;

	return A;

}