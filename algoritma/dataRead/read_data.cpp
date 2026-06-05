#include <iostream>
#include "../json.hpp"
#include "read_data.h"
#include <fstream>

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
// void cetakPreviewGraf(const std::vector<moveData>& daftarGerakan) {
//     std::cout << "=======================================================\n";
//     std::cout << "  PREVIEW STRUKTUR ADJACENCY LIST (GRAF GERAKAN SOL)   \n";
//     std::cout << "=======================================================\n";
    
//     // Cetak 3 contoh gerakan pertama (Close Slash, 5H, 2S) beserta opsi cancelnya
//     for (size_t i = 0; i < 3 && i < daftarGerakan.size(); ++i) {
//         const auto& m = daftarGerakan[i];
//         std::cout << "Gerakan  : " << m.moveName << " (" << m.moveNotation << ")\n";
//         std::cout << "Damage   : " << m.damage << " | Startup: " << m.startupFrame << " Frame\n";
//         std::cout << "Edge Out : " << m.moveNotation << " -> CANCELLABLE KE ID [";
        
//         for (size_t j = 0; j < m.validCancel.size(); ++j) {
//             std::cout << m.validCancel[j];
//             if (j < m.validCancel.size() - 1) std::cout << ", ";
//         }
//         std::cout << "]\n";
//         std::cout << "-------------------------------------------------------\n";
//     }
// }
