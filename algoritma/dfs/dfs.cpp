
#include <iostream>
#include <string>
#include <vector>
#include "dfs.h"
#include "../model/model.h"


using namespace std;

void dfsRecursive(State currentState, vector<string>& currentRoute, int lastMoveID,
    vector<MoveData>& databaseSol, int& maxTotalDamage, 
    vector<string>& bestRoute) {

    MoveData lastMove = searchMoveById(lastMoveID, databaseSol);

    bool hasNextMove = false;

    for (const auto& child : lastMove.validCancel) {
        MoveData childMove = searchMoveById(child, databaseSol);
        int currHitstun = currentState.enemy_hitstun_left - childMove.startupFrame;

        if (currHitstun >= 0) {
            int tempDamage = static_cast<int>(childMove.damage*currentState.current_proration);
            if (tempDamage <= 0) continue;
            hasNextMove = true;
            int nextTotalDamage = tempDamage + currentState.total_damage;
            int decayedHitstun = childMove.hitstun - (currentState.combo_count*DECAY_FACTOR);
            if (decayedHitstun < 2) decayedHitstun = 2;

            int nextHitstun = currHitstun + decayedHitstun;
            double nextProration = childMove.proration*currentState.current_proration;
            int nextComboCount = currentState.combo_count + 1;
            
            State nextState(
                childMove.moveNotation,
                nextHitstun,
                nextProration,
                nextTotalDamage,
                nextComboCount
            );

            currentRoute.push_back(childMove.moveNotation);

            dfsRecursive(nextState, currentRoute, child, databaseSol, maxTotalDamage, bestRoute);
            currentRoute.pop_back();
        }
    }
    
    if (!hasNextMove) {
        if (maxTotalDamage < currentState.total_damage) {
            maxTotalDamage = currentState.total_damage;
            bestRoute = currentRoute;
        }
    }
}

void DFSAlgorithm(int starterId,vector<MoveData>& databaseSol) {
    MoveData starterMove = searchMoveById(starterId, databaseSol);

    State initialState(
        starterMove.moveNotation,
        starterMove.hitstun,
        starterMove.proration,
        starterMove.damage,
        1
    );

    vector<string> bestRoute;
    vector<string> currentRoute = {starterMove.moveNotation};


    int maxTotalDamage = 0;

    dfsRecursive(initialState,currentRoute,starterId,databaseSol,maxTotalDamage,bestRoute);

    cout << "\n====================================\n";
    cout << "         HASIL RUTE KOMBO DFS       \n";
    cout << "====================================\n";
    cout << "Jalur Tombol Terbaik : ";
    for (size_t i = 0; i < bestRoute.size(); ++i) {
        cout << bestRoute[i];
        if (i < bestRoute.size() - 1) cout << " -> ";
    }
    cout << "\nMax Total Damage     : " << maxTotalDamage << " Damage PTS\n";
    cout << "====================================\n";





}
