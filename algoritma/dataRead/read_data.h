#ifndef READ_DATA_H
#define READ_DATA_H

#include <string>
#include <vector>
#include "./variables/variables.h"

using namespace std;

/**
 * @brief Fungsi mencari move dengan ID.
 * * @param id id move yang ingin dicari
 * * @param databaseSol berisi semua gerakan sol dan sudah berbentuk graf.
 * 
 */
MoveData searchMoveById(int id, const vector<MoveData>& databaseSol);


/**
 * @brief Prosedur untuk membaca berkas JSON dan memasukkan datanya ke dalam vector struct MoveData.
 * * @param sourceFile Nama atau jalur (path) dari file JSON data gerakan (e.g., "solData.json").
 * @param listMoves Referensi ke vector penampung data simpul graf di memori utama.
 */
void readMoveData(const string& sourceFile, vector<MoveData>& listMoves);


#endif 