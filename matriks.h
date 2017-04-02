#ifndef MATRIKS_H
#define MATRIKS_H

#include <iostream>

using namespace std;

static const int INFINITY = -1;

class Matriks {
  public:
    // Constructor (dari file)
    // Seluruh elemen matriks diinisialisasi dengan nilai 0
    Matriks();

    // Constructor dengan parameter banyak baris dan banyak kolom
    // Insialisasi dengan 0
    Matriks(int row, int col);

    // cctor
    Matriks(const Matriks& m);

    // dtor
    ~Matriks();

    // operator= menjamin tidak bitwise copy.
    // dan dapat melakukan assignment m1=m2; prekondisi: ukuran m1=ukuran m2
    Matriks& operator= (Matriks& m);

    // menulis ukuran dan isi Matriks (lihat contoh
    void PrintMatriks();

    // isikan nilai v di posisi data[i,j], i dan j terdefinisi
    void SetData (int i, int j, int v);

    // ambil elemen v di posisi data[i,j], i dan j terdefinisi
    int GetData (int i, int j) const;

    // Mengembalikan n_brs
    int GetBrs() const;

    // Mengembalikan n_kol
    int GetKol() const;

    // Mengakumulasi setiap sel dalam matriks
    double Accumulate() const;

    // Mencari nilai minimum dalam baris i
    int GetMinValueInRow(int i) const;

    // Mencari nilai minimum kedua dalam baris i
    int GetSecondMinValueInRow(int i) const;

    // Mencari nilai maksimum dalam kolom j
    int GetMinValueInCol(int j) const;

  protected:
    int n_brs; // Banyaknya baris, n_brs > 0
    int n_kol; // Banyaknya kolom, n_kol > 0
    int ** b; // Elemen matriks
};

#endif