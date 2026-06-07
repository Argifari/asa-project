#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "./algoritma/json.hpp"
#include "./variables/variables.h"
#include "./algoritma/greedy/greedy.h"
#include "./algoritma/bfs/bfs.h"
#include "./algoritma/dfs/dfs.h"
#include "./algoritma/dp/dp.h"
#include "./algoritma/ga/ga.h"

#include "./algoritma/model/model.h"

using namespace std;

#include <vector>

void flushCache() {
    const size_t cacheSize = 32 * 1024 * 1024; // 32 Megabytes
    std::vector<char> dummy(cacheSize, 1);

    volatile char sink = 0;
    for (size_t i = 0; i < cacheSize; i += 64) { // Loncat 64 byte (ukuran standar baris cache / cache line)
        sink = dummy[i];
    }
}

vector <MoveData> databaseSol;


int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    readMoveData("../data/solData.json", databaseSol);
    int starterId = 1;

    cout<<"=== MEMULAI PENGUJIAN PERFORMA ALGORITMA ===\n\n";

    // PENGUJIAN GREEDY
    auto startGreedy = chrono::high_resolution_clock::now();
    greedyAlgorithm(starterId,databaseSol);
    auto endGreedy = chrono::high_resolution_clock::now();

    auto durationGreedy = chrono::duration_cast<chrono::microseconds>(endGreedy - startGreedy).count();
    cout << "Waktu Eksekusi GREEDY : " << durationGreedy << " mikrodetik\n\n";

    flushCache();

    // PENGUJIAN DFS
    auto startDFS = chrono::high_resolution_clock::now();
    DFSAlgorithm(starterId,databaseSol);
    auto endDFS = chrono::high_resolution_clock::now();
    
    auto durationDFS = chrono::duration_cast<chrono::microseconds>(endDFS - startDFS).count();
    cout << "Waktu Eksekusi DFS : " << durationDFS << " mikrodetik\n\n";

    flushCache();

    // PENGUJIAN BFS
    auto startBFS = chrono::high_resolution_clock::now();
    BFSAlgorithm(starterId,databaseSol);
    auto endBFS = chrono::high_resolution_clock::now();
    
    auto durationBFS = chrono::duration_cast<chrono::microseconds>(endBFS - startBFS).count();
    cout << "Waktu Eksekusi BFS : " << durationBFS << " mikrodetik\n\n";

    flushCache();


    // PENGUJIAN DP
    auto startDP = chrono::high_resolution_clock::now();
    DPAlgorithm(starterId,databaseSol);
    auto endDP = chrono::high_resolution_clock::now();
    
    auto durationDP = chrono::duration_cast<chrono::microseconds>(endDP - startDP).count();
    cout << "Waktu Eksekusi DP : " << durationDP << " mikrodetik\n\n";
    
    
    flushCache();
    
    
    auto startGA = chrono::high_resolution_clock::now();
    GeneticAlgorithm(starterId,databaseSol);
    auto endGA = chrono::high_resolution_clock::now();
    
    auto durationGA = chrono::duration_cast<chrono::microseconds>(endGA - startGA).count();
    cout << "Waktu Eksekusi GA : " << durationGA << " mikrodetik\n\n";
    return 0;
}
