

#include "Graph.h"

#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <iostream>

const int inf = 100000;

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
	//delete matrix[numVertex];
	delete[] matrix;
}
Graph::Graph(const std::string& filepath, const char type){
	//from list
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

Graph::Graph(const std::string& filepath, bool a){
	//from matrix
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
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				int weight;
				fin >> weight;
				matrix[i][j] = weight;
			}
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


int finalPathCast = inf;
std::vector<int> finalPath;



//void Graph::computeSalesman(int from, int curPathCast, std::set<int> curPath, int root){
//
//
//
//	for (int i = 0; i < numVertex; i++){
//		if (matrix[from][i] != 0) {
//			if ((curPath.size() == numVertex) && (i == root)){
//				if (curPathCast + matrix[from][i] < finalPathCast){
//					//finalPath.swap(curPath);
//					if(!finalPath.empty())
//						finalPath.erase(finalPath.begin(), finalPath.end());
//					for (std::set<int>::iterator it = curPath.begin(); it != curPath.end(); ++it){
//						finalPath.push_back(*it);
//					}
//					finalPathCast = curPathCast + matrix[from][i];
//				}
//			}
//			else{
//				if (curPath.count(i) == 0){
//					std::set<int> newPath = curPath;
//					newPath.insert(i);
//					computeSalesman(i, curPathCast + matrix[from][i], newPath, root);
//				}
//
//			}
//		
//		}
//	}
//	
//}
//
//void Graph::salesman(){
//	
//	int root;
//
//		std::cin >> root;
//		std::set<int> startPath;
//		startPath.insert(root);
//		computeSalesman(root, 0, startPath, root);
//
//
//		std::cout <<"Final Cost: "<< finalPathCast << std::endl;
//		std::cout << "Path: ";
//		
//		for (auto &i : finalPath)
//			std::cout << ' ' << i;
//
//
//}
template <typename T>
bool is_inVector(std::vector<T> vec, T val){
	for (auto &it : vec){
		if (it == val)
			return 1;
	}
	return 0;
}

void Graph::computeSalesman(int from, int curPathCast, std::vector<int> curPath, int root){

	for (int i = 0; i < numVertex; i++){
		if (matrix[from][i] != 0) {
			if ((curPath.size() == numVertex) && (i == root)){
				if (curPathCast + matrix[from][i] < finalPathCast){
					finalPath.swap(curPath);
					finalPathCast = curPathCast + matrix[from][i];
				}
			}
			else{
				if (! is_inVector(curPath,i) ){
					std::vector<int> newPath = curPath;
					newPath.push_back(i);
					computeSalesman(i, curPathCast + matrix[from][i], newPath, root);
				}

			}

		}
	}

}

void Graph::salesman(){

	int root;

	
	std::vector<int> startPath;
	std::cout << "Input the start Vertex: " << std::endl;
	std::cin >> root;
	startPath.push_back(root);
	computeSalesman(root, 0, startPath, root);


	std::cout << "Final Cost: " << finalPathCast << std::endl;
	std::cout << "Path: ";

	for (auto &i : finalPath)
		std::cout << ' ' << i;


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

};

bool operator < (V right, V left){
	return left.key < right.key;
}




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