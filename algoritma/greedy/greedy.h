#ifndef GREEDY_H
#define GREEDY_H
#include "./variables/variables.h"
#include <vector>

using namespace std;



/**
 * @brief Prosedur untuk menyelesaikan permasalaahan dengan algoritma Greedy.
 * * @param starterId id move yang digunakan sebagai initial point
 * * @param databaseSol berisi semua gerakan sol dan sudah berbentuk graf.
 * 
 */
void greedyAlgorithm(int starterId,vector<MoveData>& databaseSol);

#endif