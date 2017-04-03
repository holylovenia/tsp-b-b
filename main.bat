cls
g++ main.cpp tsp.cpp reduced_matrix.cpp ct_matrix.cpp matriks.cpp -o main
main
dot -Tsvg graph_rcm.dot -o graph_rcm.svg
dot -Tsvg graph_ctm.dot -o graph_ctm.svg
graph_rcm.svg
graph_ctm.svg