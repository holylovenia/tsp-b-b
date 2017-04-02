#ifndef REDUCED_MATRIX_H
#define REDUCED_MATRIX_H

#include "matriks.h"
#include <vector>

using namespace std;

class ReducedMatrix: public Matriks {
	public:
    // Constructor
    ReducedMatrix();

    // Copy Constructor
    ReducedMatrix(const ReducedMatrix& r);

    // Mereduksi baris i
    int ReduceRow(int i);

    // Mereduksi kolom j
    int ReduceColumn(int j);

    // Mereduksi setiap baris matriks
    int ReduceAllRow();

    // Mereduksi setiap kolom matriks
    int ReduceAllColumn();

    // Mereduksi matriks
    int ReduceAll();

    // Mereduksi matriks (final)
    // Prekondisi: objek sudah jadi matriks tereduksi
    void ReduceMatrix(int dest);

    // Mengecek apakah matriks merupakan matriks tereduksi
    bool IsReducedMatrix();

    // Menjadikan baris i, kolom j, dan simpul(j, i) menjadi infinity
    // i adalah parent dari matriks
    void SetToInfinity(int j);

    // Mengembalikan path
    vector<int> GetPath() const;

    // Mengembalikan nilai cost
    int GetCost() const;

    // Menulis isi path
    void PrintPath();

    protected:
    vector<int> path;
    int cost;
};


#endif