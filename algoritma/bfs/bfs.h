#ifndef BFS_H
#define BFS_H
#include "./variables/variables.h"
#include <vector>

using namespace std;

/**
 * @brief Prosedur untuk menyelesaikan permasalaahan dengan algoritma BFS.
 * * @param starterId id move yang digunakan sebagai initial point
 * * @param databaseSol berisi semua gerakan sol dan sudah berbentuk graf.
 * 
 */
void BFSAlgorithm(int starterId,vector<MoveData>& databaseSol);

#endif