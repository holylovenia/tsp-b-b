#include "tsp.h"
#include <algorithm>

static int numberOfGeneratedNode = 0;

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

vector<int> TSP::GetChildren(ReducedMatrix parent) {
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

void TSP::AddChildren(ReducedMatrix parent, vector<int> children) {
  int numberOfChildren = children.size();
  for(int i = 0; i < numberOfChildren; i++) {
    ReducedMatrix addedChildren(parent);
    addedChildren.ReduceMatrix(children[i]);
    branch.push(addedChildren);
    numberOfGeneratedNode++;
  }
}

bool TSP::HasReturned(ReducedMatrix reducedMatrix) {
  return(SearchPath(reducedMatrix.GetPath(), 0));
}

void TSP::ReducedCostMatrixAlgorithm() {
  ReducedMatrix reducedMatrix, solution;
  branch.push(reducedMatrix);
  int bound = reducedMatrix.GetBrs() + 1;
  ReducedMatrix processed;
  bool foundSolution;
  while((!branch.empty()) && (!foundSolution)) {
    ReducedMatrix processed = branch.top();
    branch.pop();
    if(HasReturned(processed)) {
      solution = processed;
      foundSolution = true;
    } else {
      AddChildren(processed, GetChildren(processed));
    }
  }
  if(foundSolution) {
    cout << "Solusi: ";
    solution.PrintPath();
    cout << endl;
    cout << "Cost: " << solution.GetCost() << endl;
    cout << "Jumlah simpul yang dibangkitkan: " << numberOfGeneratedNode << endl;
  } else {
    cout << "Tidak ada solusi" << endl;
  }
}