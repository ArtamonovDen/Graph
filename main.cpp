#include "Graph.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class Graph;

//class V{
//public:
//	V() = default;
//	~V() = default;
//	V(const V& newV) : vert(newV.vert), key(newV.key), par(newV.par)
//	{}
//	int vert;
//	int key;
//	int par;
//
//	/*bool operator < (V & right) const {
//	return this->key < right.key;
//	}*/
//};
//
//bool operator < (V right, V left){
//	return left.key < right.key;
//}
//
//
//
//const int inf = 100000;
//void minSpanningTree(int root){
//	std::priority_queue<V> queueV;
//	for (int i = 0; i < 2; i++){
//		V newV;
//		newV.vert = i;
//		newV.key = inf;
//		if (i == root)
//			newV.par = 0;
//		else
//			newV.par = -1;
//		queueV.push(newV);
//	}
//
//	while (!queueV.empty()){
//		V u{ queueV.top() };
//	}
//
//}

//
int main(){

	std::string path = "edgeList1.txt";	
	//Graph *G = Graph::loadFromEdgeList(path);
	Graph G(path, 'W');
	//G.findBridges();
	std::vector<std::pair<int, int>> A = G.minSpanningTree(0);
	for (auto i : A){
		std::cout << i.first << " " << i.second << std::endl;
	}


	//V v1{ 2, 4, 1 };
	//V v2{ 4, 5, 2 };
	//V v3{ 5, 6, 6 };
	//std::queue<int> w;
	//std::priority_queue<V> myPrQueue;
	//myPrQueue.push(v3);
	//myPrQueue.push(v2);
	//myPrQueue.push(v1);
	//
	//

	//std::cout << myPrQueue.size() << std::endl;
	//std::cout << myPrQueue.top().vert<< std::endl;
	//myPrQueue.pop();
	//std::cout << myPrQueue.top().vert << std::endl;



	std::cin.get();
	return 0;
}
//g++ - O3 - Wall - std = c++11 main.cpp