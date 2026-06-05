#include <iostream>
#include <string>
#include <vector>
#include "dp.h"
#include "../dataRead/read_data.h"


using namespace std;

int dpRecursive(State currentState, int lastMoveID,
    vector<MoveData>& databaseSol, MemoTable& memo) {

    string stateKey = to_string(lastMoveID) + "_" + to_string(currentState.enemy_hitstun_left) 
    + "_"+ to_string(currentState.current_proration) + "_" + to_string(currentState.combo_count);


    if (memo.memoDamage.count(stateKey)) {
        return memo.memoDamage[stateKey];
    }

    MoveData lastMove = searchMoveById(lastMoveID, databaseSol);

    int maxNextDamage = 0;
    vector<string> bestNextRoute = {};


    for (const auto& child : lastMove.validCancel) {
        MoveData childMove = searchMoveById(child, databaseSol);
        int currHitstun = currentState.enemy_hitstun_left - childMove.startupFrame;

        if (currHitstun >= 0) {
            int tempDamage = static_cast<int>(childMove.damage*currentState.current_proration);
            if (tempDamage <= 0) continue;
    
            int decayedHitstun = childMove.hitstun - (currentState.combo_count*DECAY_FACTOR);
            if (decayedHitstun < 2) decayedHitstun = 2;

            int nextHitstun = currHitstun + decayedHitstun;
            double nextProration = childMove.proration*currentState.current_proration;
            int nextComboCount = currentState.combo_count + 1;

            State nextState(
                childMove.moveNotation,
                nextHitstun,
                nextProration,
                0,
                nextComboCount
            );

            int nextDamage = dpRecursive(nextState,child,databaseSol,memo);
            int nextTotalDamage = tempDamage + nextDamage;

            if (maxNextDamage < nextTotalDamage) {
                maxNextDamage = nextTotalDamage;

                bestNextRoute = {childMove.moveNotation};
                string nextStateKey = to_string(child) + "_" + to_string(nextState.enemy_hitstun_left) 
                + "_"+ to_string(nextState.current_proration) + "_" + to_string(nextState.combo_count);

                if (memo.memoRoute.count(nextStateKey)) {
                    bestNextRoute.insert(bestNextRoute.end(), memo.memoRoute[nextStateKey].begin(), memo.memoRoute[nextStateKey].end());
                }

            }
            
        }  
    }
    memo.memoDamage[stateKey] = maxNextDamage;
    memo.memoRoute[stateKey] = bestNextRoute;

    return maxNextDamage;
    
      
}


void DPAlgorithm(int starterId,vector<MoveData>& databaseSol) {
    MoveData starterMove = searchMoveById(starterId, databaseSol);

    State initialState(
        starterMove.moveNotation,
        starterMove.hitstun,
        starterMove.proration,
        starterMove.damage,
        1
    );

    MemoTable memo;

    int maxFutureDamage = dpRecursive(initialState, starterId, databaseSol, memo);
    int finalMaxDamage = starterMove.damage + maxFutureDamage;

    vector<string> finalBestRoute = {starterMove.moveNotation};
    string initialKey = to_string(starterId) + "_" + to_string(starterMove.hitstun) + "_"
                + to_string(starterMove.proration) + "_1";
                
    if (memo.memoRoute.count(initialKey)) {
        finalBestRoute.insert(finalBestRoute.end(),memo.memoRoute[initialKey].begin()
        ,memo.memoRoute[initialKey].end());
    }

    cout << "\n====================================\n";
    cout << "         HASIL RUTE KOMBO DP        \n";
    cout << "====================================\n";
    cout << "Jalur Tombol Terbaik : ";
    for (size_t i = 0; i < finalBestRoute.size(); ++i) {
        cout << finalBestRoute[i];
        if (i < finalBestRoute.size() - 1) cout << " -> ";
    }
    cout << "\nMax Total Damage     : " << finalMaxDamage << " Damage PTS\n";
    cout << "====================================\n";

}