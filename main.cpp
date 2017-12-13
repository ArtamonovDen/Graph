#include "Graph.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class Graph;


int main(){

	std::string path = "edgeList1.txt";	
	std::string path2 = "matrixList1.txt";
	Graph G(path, 'W');
	//Graph G(path2, true);


	
	//G.findBridges();
	/*std::vector<std::pair<int, int>> A = G.minSpanningTree(0);
	for (auto i : A){
		std::cout << i.first << " " << i.second << std::endl;
	}*/
	G.salesman();




	std::cin.get();
	std::cin.get();
	return 0;
}
//g++ - O3 - Wall - std = c++11 main.cpp