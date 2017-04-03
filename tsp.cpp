// File: tsp.cpp

#include "tsp.h"
#include <ctime>
#include <fstream>

static int numberOfGeneratedNodeRCM = 0;
static int numberOfGeneratedNodeCTM = 0;

using namespace std;

bool TSP::SearchPath(vector<int> children, int x) {
  bool found = false;
  int i = 1;
  while((!found) && (i < children.size())) {
    if(children[i] == x) {
      found = true;
    }
    i++;
  }
  return(found);
}

vector<int> TSP::GetChildren(const ReducedMatrix& parent) {
  bool found = false;
  vector<int> children;
  vector<int> temp_path = parent.GetPath();
  if(temp_path.size() < parent.GetBrs()) {
    for(int i = 1; i < parent.GetBrs(); i++) {
      if(!SearchPath(temp_path, i)) {
        children.push_back(i);
      }
    }
  } else {
    children.push_back(0);
  }
  return(children);
}

vector<int> TSP::GetChildren(const CTMatrix& parent) {
  bool found = false;
  vector<int> children;
  vector<int> temp_path = parent.GetPath();
  if(temp_path.size() < parent.GetBrs()) {
    for(int i = 1; i < parent.GetBrs(); i++) {
      if(!SearchPath(temp_path, i)) {
        children.push_back(i);
      }
    }
  } else {
    children.push_back(0);
  }
  return(children);
}

void TSP::AddChildren(const ReducedMatrix& parent, vector<int> children) {
  int numberOfChildren = children.size();
  for(int i = 0; i < numberOfChildren; i++) {
    ReducedMatrix addedChildren(parent);
    addedChildren.ReduceMatrix(children[i]);
    branch_rcm.push(addedChildren);
    numberOfGeneratedNodeRCM++;
  }
}

void TSP::AddChildren(const CTMatrix& parent, vector<int> children, const Matriks& adj) {
  int numberOfChildren = children.size();
  for(int i = 0; i < numberOfChildren; i++) {
    CTMatrix addedChildren(parent);
    addedChildren.ProcessNode(children[i], adj);
    branch_ctm.push(addedChildren);
    numberOfGeneratedNodeCTM++;
  }
}

bool TSP::HasReturned(const ReducedMatrix& reducedMatrix) {
  return(SearchPath(reducedMatrix.GetPath(), 0));
}

bool TSP::HasReturned(const CTMatrix& ctMatrix) {
  return(SearchPath(ctMatrix.GetPath(), 0));
}

bool TSP::IsNextCity(vector<int> path, int curr_city, int next_city) {
  int curr_city_index = 0;
  while(path[curr_city_index] != curr_city) {
    curr_city_index++;
  }
  int next_city_index = curr_city_index + 1;
  while((next_city_index < path.size()) && (path[next_city_index] != next_city)) {
    next_city_index++;
  }
  return(curr_city_index + 1 == next_city_index);
}

void TSP::DrawDirectedGraph(const Matriks& adj, const vector<int>& path) {
  ofstream fname;
  fname.open("graph_rcm.dot");
  fname << "digraph {" << endl;
  fname << "  rankdir = \"BT\"" << endl;
  fname << "  splines = \"line\"" << endl;
  for(int i = 0; i < adj.GetBrs(); i++) {
    for(int j = 0; j < adj.GetKol(); j++) {
      if(i != j) {
        if(IsNextCity(path, i, j))
          fname << "  " << i + 1 << " -> " << j + 1 << "[label=\"" << adj.GetData(i, j) << "\" , color=magenta, penwidth=4.0];" << endl;
        else  
          fname << "  " << i + 1 << " -> " << j + 1 << "[label=\"" << adj.GetData(i, j) << "\"];" << endl;
      }
    }
  }
  fname << "}";
  fname.close();
}

void TSP::DrawUndirectedGraph(const Matriks& adj, const vector<int>& path) {
  ofstream fname;
  fname.open("graph_ctm.dot");
  fname << "graph {" << endl;
  fname << "  rankdir = \"LR\"" << endl;
  fname << "  splines = \"line\"" << endl;
  for(int i = 0; i < adj.GetBrs(); i++) {
    for(int j = i + 1; j < adj.GetKol(); j++) {
      if((IsNextCity(path, i, j)) || (IsNextCity(path, j, i)))
        fname << "  " << i + 1 << " -- " << j + 1 << "[label=\"" << adj.GetData(i, j) << "\" , color=magenta, penwidth=4.0];" << endl;
      else  
        fname << "  " << i + 1 << " -- " << j + 1 << "[label=\"" << adj.GetData(i, j) << "\"];" << endl;
    }
  }
  fname << "}";
  fname.close();
}

void TSP::ReducedCostMatrixAlgorithm() {
  cout << "--- REDUCED COST MATRIX ALGORITHM ---" << endl;
  ReducedMatrix reducedMatrix, solution;
  clock_t begin = clock();
  branch_rcm.push(reducedMatrix);
  bool foundSolution;
  while((!branch_rcm.empty()) && (!foundSolution)) {
    ReducedMatrix processed = branch_rcm.top();
    branch_rcm.pop();
    if(HasReturned(processed)) {
      solution = processed;
      foundSolution = true;
    } else {
      AddChildren(processed, GetChildren(processed));
    }
  }
  clock_t duration = clock() - begin;
  if(foundSolution) {
    cout << "Solusi: ";
    solution.PrintPath();
    cout << endl;
    cout << "Cost: " << solution.GetCost() << endl;
    cout << "Jumlah simpul yang dibangkitkan: " << numberOfGeneratedNodeRCM << endl;
  } else {
    cout << "Tidak ada solusi" << endl;
  }
  cout << "Waktu eksekusi: " << (float) duration * 1000 / CLOCKS_PER_SEC << " ms" << endl;
  Matriks adj;
  DrawDirectedGraph(adj, solution.GetPath());
}

void TSP::CompleteTourCostAlgorithm() {
  cout << "--- COMPLETE TOUR COST ALGORITHM ---" << endl;
  Matriks adj;
  clock_t begin = clock();
  CTMatrix ctMatrix(adj);
  CTMatrix solution(adj);
  branch_ctm.push(ctMatrix);
  bool foundSolution;
  while((!branch_ctm.empty()) && (!foundSolution)) {
    CTMatrix processed = branch_ctm.top();
    branch_ctm.pop();
    if(HasReturned(processed)) {
      solution = processed;
      foundSolution = true;
    } else {
      AddChildren(processed, GetChildren(processed), adj);
    }
  }
  clock_t duration = clock() - begin;
  if(foundSolution) {
    cout << "Solusi: ";
    solution.PrintPath();
    cout << endl;
    cout << "Cost: " << solution.GetCost() << endl;
    cout << "Jumlah simpul yang dibangkitkan: " << numberOfGeneratedNodeCTM << endl;
  } else {
    cout << "Tidak ada solusi" << endl;
  }
  cout << "Waktu eksekusi: " << (float) duration * 1000 / CLOCKS_PER_SEC << " ms" << endl;
  DrawUndirectedGraph(adj, solution.GetPath());
}