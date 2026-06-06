#include <iostream>
#include "../json.hpp"
#include "model.h"
#include <fstream>
#include "./variables/variables.h"

using namespace std;

using json = nlohmann::json;


MoveData searchMoveById(int id, const vector<MoveData>& databaseSol) {
    for (const auto& m : databaseSol) {
        if (m.moveID == id) return m;
    }
    return MoveData();
}


void readMoveData(const string& sourceFile, vector<MoveData>& listMoves) {
    ifstream file(sourceFile);

    // Membuka file
    if (!file.is_open()) {
        cout<<"[ERROR] Gagal membuka file: "<<sourceFile<< endl;
        return;
    }

    // parsing setiap data di JSON
    json jData;
    try {
        file >> jData;
    }catch (json::parse_error& e) {
        cout<< "[ERROR] Gagal parsing JSON: "<< e.what() << endl;
        file.close();
        return;
    }

    file.close();

    // Memasukkan data yang telah diparsing ke dalam vector 
    for (const auto& item : jData) {
        MoveData move;

        move.moveID = item.at("moveId").get<int>();
        move.moveName = item.at("moveName").get<string>();
        move.moveNotation = item.at("moveNotation").get<string>();
        move.damage = item.at("damage").get<int>();
        move.startupFrame = item.at("startupFrame").get<int>();
        move.activeFrame = item.at("activeFrame").get<int>();
        move.recoveryFrame = item.at("recoveryFrame").get<int>();
        move.attackLevel = item.at("attackLevel").get<int>();
        move.hitstun = item.at("hitstun").get<int>();
        move.proration = item.at("proration").get<double>();
        move.validCancel = item.at("validCancel").get<vector<int>>();

        listMoves.push_back(move);
    }

    cout<< "[SUKSES] Prosedur berhasil memuat " << listMoves.size() << 
    " simpul gerakan ke memori.\n";

}

