#include "reduced_matrix.h"

ReducedMatrix::ReducedMatrix(): Matriks() {
  path.push_back(0);
  if (!IsReducedMatrix())
    cost = ReduceAll();
}

ReducedMatrix::ReducedMatrix(const ReducedMatrix& r): Matriks(r) {
  path = r.path;
  cost = r.cost;
}

int ReducedMatrix::ReduceRow(int i) {
	int row_min = GetMinValueInRow(i);
	if (row_min > 0) {
		for(int j = 0; j < n_kol; j++) {
      if (b[i][j] != INFINITY)
        b[i][j] -= row_min;
		}
	}
  return(row_min);
}

int ReducedMatrix::ReduceColumn(int j) {
  int col_min = GetMinValueInCol(j);
  if (col_min > 0) {
    for(int i = 0; i < n_brs; i++) {
      if (b[i][j] != INFINITY)
        b[i][j] -= col_min;
    }
  }
  return(col_min);
}

int ReducedMatrix::ReduceAllRow() {
  int total_reduction = 0;
  for(int i = 0; i < n_brs; i++) {
    total_reduction += ReduceRow(i);
  }
  return(total_reduction);
}

int ReducedMatrix::ReduceAllColumn() {
  int total_reduction = 0;
  for(int j = 0; j < n_kol; j++) {
    total_reduction += ReduceColumn(j);
  }
  return(total_reduction);
}

int ReducedMatrix::ReduceAll() {
  return(ReduceAllRow() + ReduceAllColumn());
}

void ReducedMatrix::ReduceMatrix(int dest) {
  int origin = path.back();
  int edge_cost = b[origin][dest];
  int total_reduction;
  SetToInfinity(dest);
  if(IsReducedMatrix())
    total_reduction = 0;
  else
    total_reduction = ReduceAll();
  cost += edge_cost + total_reduction;
  path.push_back(dest);
}

bool ReducedMatrix::IsReducedMatrix() {
  int i = 0;
  int j = 0;
  bool isReduced = true;
  while((i < n_brs) && (isReduced)) {
    if(GetMinValueInRow(i) > 0) {
      isReduced = false;
    }
    i++;
  }
  while((j < n_kol) && (isReduced)) {
    if(GetMinValueInCol(j) > 0) {
      isReduced = false;
    }
    j++;
  }
  return(isReduced);
}

void ReducedMatrix::SetToInfinity(int j) {
  int i = path.back();
  for(int n = 0; n < n_kol; n++) {
    b[i][n] = INFINITY;
  }
  for(int n = 0; n < n_brs; n++) {
    b[n][j] = INFINITY;
  }
  b[j][i] = INFINITY;
}

vector<int> ReducedMatrix::GetPath() const {
  return(path);
}

int ReducedMatrix::GetCost() const {
  return(cost);
}

void ReducedMatrix::PrintPath() {
  int numberOfCitiesPassed = path.size();
  int i;
  for(i = 0; i < numberOfCitiesPassed-1; i++) {
    cout << path[i] + 1 << " -> ";
  }
  cout << path[i] + 1;
}