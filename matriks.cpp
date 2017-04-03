// File: matriks.cpp

#include "matriks.h"
#include <iostream>
#include <fstream>

#define FILE_NAME "input4.txt"

using namespace std;

// ctor dengan param n (banyaknya baris) dan m (banyaknya kolom)
// Seluruh elemen matriks diinisialisasi dengan nilai 0
Matriks::Matriks() {
  ifstream fname;
  fname.open(FILE_NAME);
  fname >> n_brs;
  n_kol = n_brs;
	b = new int* [n_brs];
	for (int i = 0; i < n_brs; i++)
	{
		b[i] = new int [n_kol];
		for (int j = 0; j < n_kol; j++)
		{
			fname >> b[i][j];
		}
	}
  fname.close();
}

Matriks::Matriks(int row, int col) {
  n_brs = row;
  n_kol = col;
  b = new int* [n_brs];
  for (int i = 0; i < n_brs; i++)
  {
    b[i] = new int [n_kol];
    for (int j = 0; j < n_kol; j++)
    {
      b[i][j] = 0;
    }
  }
}

// cctor
Matriks::Matriks(const Matriks& m) {
  n_brs = m.n_brs;
  n_kol = m.n_kol;
	b = new int* [n_brs];
	for (int i = 0; i < n_brs; i++)
	{
		b[i] = new int [n_kol];
		for (int j = 0; j < n_kol; j++)
		{
			b[i][j] = m.b[i][j];
		}
	}
}

// dtor
Matriks::~Matriks() {
	for (int i = 0; i < n_brs; i++)
	{
		delete [] b[i];
	}
	delete [] b;
}

// operator= menjamin tidak bitwise copy.
// dan dapat melakukan assignment m1=m2{} prekondisi: ukuran m1=ukuran m2
Matriks& Matriks::operator= (Matriks& m) {
	b = new int* [m.GetBrs()];
	for (int i = 0; i < m.GetBrs(); i++)
	{
		b[i] = new int [m.GetKol()];
		for (int j = 0; j < m.GetKol(); j++)
		{
			b[i][j] = m.b[i][j];
		}
	}
	
	return (*this);
}

// menulis ukuran dan isi Matriks (lihat contoh
void Matriks::PrintMatriks() {
	cout << "N = " << n_brs << endl;
	cout << "M = " << n_kol << endl;
	for (int i = 0; i < n_brs; i++)
	{
		for (int j = 0; j < n_kol - 1; j++)
		{
			cout << b[i][j] << " ";
		}
		cout << b[i][n_kol - 1] << endl;
	}
}

// isikan nilai v di posisi data[i,j], i dan j terdefinisi
void Matriks :: SetData (int i, int j, int v) {
	b[i][j] = v;
}

// ambil elemen v di posisi data[i,j], i dan j terdefinisi
int Matriks :: GetData (int i, int j) const {
	return (b[i][j]);
}

// Mengembalikan n_brs
int Matriks :: GetBrs() const {
	return (n_brs);
}

// Mengembalikan n_kol
int Matriks :: GetKol() const {
	return (n_kol);
}

double Matriks::Accumulate() const {
  int sum = 0;
  for(int i = 0; i < n_brs; i++) {
    for(int j = 0; j < n_kol; j++) {
      if(b[i][j] != INFINITY)
        sum += b[i][j];
    }
  }
  return(sum);
}

int Matriks::GetMinValueInRow(int i) const {
  int min = b[i][0];
  for(int j = 1; j < n_kol; j++) {
    if ((b[i][j] != INFINITY) && ((min == INFINITY)|| (b[i][j] < min))) {
      min = b[i][j];
    }
  }
  if (min != INFINITY) {
    return(min);
  } else { // min == infinity
    return 0;
  }
}

int Matriks::GetSecondMinValueInRow(int i) const {
  int first = b[i][0];
  int second = b[i][0];
  for(int j = 1; j < n_kol; j++) {
    if (b[i][j] != INFINITY) {
      if((first == INFINITY) || (b[i][j] <= first)) {
        second = first;
        first = b[i][j];
      } else if(((b[i][j] < second) || (second == INFINITY)) && (b[i][j] > first)) {
        second = b[i][j];
      }
    }
  }
  return(second);
}

int Matriks::GetMinValueInCol(int j) const {
  int min = b[0][j];
  for(int i = 1; i < n_brs; i++) {
    if ((b[i][j] != INFINITY) && ((min == INFINITY)|| (b[i][j] < min))) {
      min = b[i][j];
    }
  }
  if (min != INFINITY) {
    return(min);
  } else { // min == infinity
    return 0;
  }
}