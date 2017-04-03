// File: ct_matrix.h

#ifndef CT_MATRIX_H
#define CT_MATRIX_H

#include "matriks.h"
#include <vector>

class CTMatrix: public Matriks {
	public:
    // Constructor
    // Jumlah baris = n dan jumlah kolom = 2
    CTMatrix(const Matriks& adj);

    // Copy constructor
    CTMatrix(const CTMatrix& c);

    // Menghitung cost
    double CalculateCost();

    // Mengembalikan cost
    double GetCost() const;

    // Memproses simpul
    void ProcessNode(int dest, const Matriks& adj);

    // Mengembalikan path
    vector<int> GetPath() const;

    // Menulis isi path
    void PrintPath() const;

	protected:
    vector<int> path;
    double cost;
};


#endif