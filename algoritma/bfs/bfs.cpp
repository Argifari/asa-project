
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "bfs.h"
#include "../model/model.h"


using namespace std;

void BFSAlgorithm(int starterId,vector<MoveData>& databaseSol) {
    queue<BfsNode> q;

    MoveData starterMove = searchMoveById(starterId, databaseSol);

    State initialState(
        starterMove.moveNotation,
        starterMove.hitstun,
        starterMove.proration,
        starterMove.damage,
        1
    );

    vector<string> bestRoute;
    bestRoute.push_back(starterMove.moveNotation);

    q.push(BfsNode(initialState, bestRoute, starterId));

    int maxTotalDamage = 0;

    while(!q.empty()) {
        BfsNode currNode = q.front();
        q.pop();

        State currentState = currNode.state;
        vector<string> currRute = currNode.rute;
        int lastMoveId = currNode.lastMoveId;
        bool hasNextMove = false;

        MoveData lastMove = searchMoveById(lastMoveId, databaseSol);

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

                vector<string> nextRoute = currRute;
                nextRoute.push_back(childMove.moveNotation);

                q.push(BfsNode(nextState,nextRoute,child));
            }
        }

        if (!hasNextMove) {
            if (maxTotalDamage < currentState.total_damage) {
                maxTotalDamage = currentState.total_damage;
                bestRoute = currRute;
            }
        }


    }
    cout << "\n====================================\n";
    cout << "         HASIL RUTE KOMBO BFS       \n";
    cout << "====================================\n";
    cout << "Jalur Tombol Terbaik : ";
    for (size_t i = 0; i < bestRoute.size(); ++i) {
        cout << bestRoute[i];
        if (i < bestRoute.size() - 1) cout << " -> ";
    }
    cout << "\nMax Total Damage     : " << maxTotalDamage << " Damage PTS\n";
    cout << "====================================\n";



}