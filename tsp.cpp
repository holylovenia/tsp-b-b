#include "tsp.h"
#include <ctime>

static int numberOfGeneratedNodeRCM = 0;
static int numberOfGeneratedNodeCTM = 0;

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
}