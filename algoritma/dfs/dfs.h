#ifndef DFS_H
#define DFS_H
#include "./variables/variables.h"
#include <vector>

using namespace std;

/**
 * @brief Prosedur untuk menyelesaikan permasalaahan dengan algoritma DFS.
 * * @param starterId id move yang digunakan sebagai initial point
 * * @param databaseSol berisi semua gerakan sol dan sudah berbentuk graf.
 * 
 */
void DFSAlgorithm(int starterId,vector<MoveData>& databaseSol);

/**
 * @brief Prosedur untuk melakukan rekursif secara mendalam.
 * * @param currentState state saat ini 
 * * @param currentRoute rute saat ini
 * * @param lastMoveId move terakhir yang telah digunakan
 * * @param databaseSol berisi semua gerakan sol dan sudah terbentuk graf
 * * @param maxTotalDamage total damage 
 * * @param bestRoute rute paling bagus 
 */
void dfsRecursive(State currentState, vector<string>& currentRoute, int lastMoveID,
                    vector<MoveData>& databaseSol, int& maxTotalDamage, 
                    vector<string>& bestRoute);

#endif