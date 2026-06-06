#ifndef DP_H
#define DP_H
#include "./variables/variables.h"
#include <vector>
#include <map>

using namespace std;


/**
 * @brief Tipe bentukan untuk memoisasi.*/
// Atribut : 
// memoDamage untuk menyimpam damage
// memoRoute untuk menyimpan rute 
struct MemoTable {
    map<string, int> memoDamage;
    map<string, vector<string>> memoRoute;
};

/**
 * @brief Prosedur untuk melakukan rekursif.
 * * @param currentState state saat ini 
 * * @param lastMoveId move terakhir yang telah digunakan
 * * @param databaseSol berisi semua gerakan sol dan sudah terbentuk graf
 * * @param memo memoisasi dp
 */
int dpRecursive(State currentState, int lastMoveID,
                    vector<MoveData>& databaseSol, MemoTable& memo);

/**
 * @brief Prosedur untuk menyelesaikan permasalaahan dengan algoritma DP.
 * * @param starterId id move yang digunakan sebagai initial point
 * * @param databaseSol berisi semua gerakan sol dan sudah berbentuk graf.
 * 
 */
void DPAlgorithm(int starterId,vector<MoveData>& databaseSol);

#endif