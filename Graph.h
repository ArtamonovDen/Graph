
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Graph
{
public:
	Graph(int);
	Graph();
	Graph(const std::string& filepath, const char);
	
	~Graph();

	int getSize() const{
		return numVertex;
	}
	int ** getMatrix(){
		return matrix;
	}


	/*static Graph* loadFromEdgeList(const std::string filepath){
		 std::fstream fin;
		 fin.open(filepath);
		 if (!fin.is_open())
		 return nullptr;
		 int n;
		 fin >> n;
		 Graph*newGraph = new Graph(n);
		 while (!fin.eof()){
		 int v_from, v_to;
		 fin >> v_from >> v_to;
		 newGraph->setEdgeMatrix(v_from, v_to);
		 newGraph->setEdgeList(v_from, v_to);
		 }
		 return newGraph;
	 }*/
	 
	void setEdgeMatrix(int, int,int);
	void removeEdgeMatrix(int, int);

	void setEdgeList(int, int);
	void removeEdgeList(int, int);

	int * findBridges();
	int ShortestPath(int from, int to);
	std::vector<int> salesman(const std::string& filepath);

	std::vector<std::pair<int, int>>   minSpanningTree(int root);
	
	
private:
	std::vector<int> computeSalesman(const int startVert);
	void FindPath(int from, std::vector<int> &checkedVert);
	int ** matrix;
	int numVertex;
	int startVert{ -1 };
	std::vector< std::pair<int, int> > edgeList;
};



#endif