#include "reduced_matrix.h"
#include <queue>


struct compare {
  bool operator()(const ReducedMatrix& l, const ReducedMatrix& r) {
    return(l.GetCost() > r.GetCost());
  }
};


class TSP {
  public:

    // Mencari x di vector
    bool SearchPath(vector<int> children, int x);

    // Menghasilkan array berisi simpul yang belum ada di path
    // Prekondisi: path pasti belum lengkap
    vector<int> GetChildren(ReducedMatrix parent);

    // Menambahkan anak-anak dari simpul yang barusan diproses
    void AddChildren(ReducedMatrix parent, vector<int> children);
    
    // Mengecek apakah semua simpul sudah dicapai
    bool HasReturned(ReducedMatrix reducedMatrix);

    // Mengeksekusi algoritma utama Reduced Cost Matrix
		void ReducedCostMatrixAlgorithm();

		priority_queue<ReducedMatrix, vector<ReducedMatrix>, compare> branch;
};