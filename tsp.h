#include "reduced_matrix.h"
#include "ct_matrix.h"
#include <queue>


struct compare {
  bool operator()(const ReducedMatrix& l, const ReducedMatrix& r) {
    return(l.GetCost() > r.GetCost());
  }
};

struct compare2 {
  bool operator()(const CTMatrix& l, const CTMatrix& r) {
    return(l.GetCost() > r.GetCost());
  }
};

class TSP {
  public:
    // Mencari x di vector
    bool SearchPath(vector<int> children, int x);

    // Menghasilkan array berisi simpul yang belum ada di path
    // Prekondisi: path pasti belum lengkap
    vector<int> GetChildren(const ReducedMatrix& parent);

    // Menghasilkan array berisi simpul yang belum ada di path
    // Prekondisi: path pasti belum lengkap
    vector<int> GetChildren(const CTMatrix& parent);

    // Menambahkan anak-anak dari simpul yang barusan diproses
    void AddChildren(const ReducedMatrix& parent, vector<int> children);

    // Menambahkan anak-anak dari simpul yang barusan diproses
    void AddChildren(const CTMatrix& parent, vector<int> children, const Matriks& adj);
    
    // Mengecek apakah semua simpul sudah dicapai
    bool HasReturned(const ReducedMatrix& reducedMatrix);

    // Mengecek apakah semua simpul sudah dicapai
    bool HasReturned(const CTMatrix& ctMatrix);

    // Mengeksekusi algoritma utama Reduced Cost Matrix
		void ReducedCostMatrixAlgorithm();

    // Mengeksekusi algoritma utama Bobot Tur Lengkap
    void CompleteTourCostAlgorithm();

  private:
		priority_queue<ReducedMatrix, vector<ReducedMatrix>, compare> branch_rcm;
    priority_queue<CTMatrix, vector<CTMatrix>, compare2> branch_ctm;
};