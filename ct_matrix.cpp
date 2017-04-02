#include "ct_matrix.h"


CTMatrix::CTMatrix(const Matriks& adj): Matriks(adj.GetBrs(), 2) {
  path.push_back(0);
  for(int i = 0; i < adj.GetBrs(); i++) {
    b[i][0] = adj.GetMinValueInRow(i);
    b[i][1] = adj.GetSecondMinValueInRow(i);
  }
  cost = adj.Accumulate() / 2.0;
}

CTMatrix::CTMatrix(const CTMatrix& c): Matriks(c) {
  path = c.path;
  cost = c.cost;
}

double CTMatrix::CalculateCost() {
  return(Accumulate() / 2.0);
}

double CTMatrix::GetCost() const {
  return(cost);
}

void CTMatrix::ProcessNode(int dest, const Matriks& adj) {
  int origin = path.back();
  path.push_back(dest);
  int value = adj.GetData(origin, dest);
  b[origin][1] = value;
  b[dest][0] = value;
  if(value == adj.GetMinValueInRow(dest))
    b[dest][1] = adj.GetSecondMinValueInRow(dest);
  else
    b[dest][1] = adj.GetMinValueInRow(dest);
  cost = CalculateCost();
}

vector<int> CTMatrix::GetPath() const {
  return(path);
}

void CTMatrix::PrintPath() const {
  int numberOfCitiesPassed = path.size();
  int i;
  for(i = 0; i < numberOfCitiesPassed-1; i++) {
    cout << path[i] + 1 << " -> ";
  }
  cout << path[i] + 1;
}