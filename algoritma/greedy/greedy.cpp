
#include <iostream>
#include <string>
#include <vector>
#include "greedy.h"
#include "../model/model.h"

using namespace std;




void greedyAlgorithm(int starterId,vector<MoveData>& databaseSol) {
    MoveData starterMove = searchMoveById(starterId, databaseSol);
    State currentState(
        starterMove.moveNotation,
        starterMove.hitstun,
        starterMove.proration,
        starterMove.damage,
        1
    );

    vector<string> ruteKombo;
    ruteKombo.push_back(starterMove.moveNotation);

    bool isKomboBerjalan = true;

    while (isKomboBerjalan) {
        MoveData currentMove = searchMoveById(starterId, databaseSol);

        int idPickMove = -1;
        int damageLocal = -1;

        State hasilState("",0,0,0,1);

        for (const auto& child : currentMove.validCancel) {
            MoveData childMove = searchMoveById(child, databaseSol);
            int currHitstun = currentState.enemy_hitstun_left - childMove.startupFrame;

            if (currHitstun >= 0) {
                int tempDamage = static_cast<int>(childMove.damage * currentState.current_proration);
                if (tempDamage <= 0) continue;
                string nextMove = childMove.moveNotation;
                int decayedHitstun = childMove.hitstun - (currentState.combo_count*DECAY_FACTOR);
                if (decayedHitstun < 2) decayedHitstun = 2;

                int nextHitstun = currHitstun + decayedHitstun;
                double nextProration = childMove.proration*currentState.current_proration;
                int nextTotalDamage = currentState.total_damage + tempDamage;
                int nextComboCount = currentState.combo_count + 1;

                if (tempDamage > damageLocal) {
                    damageLocal = tempDamage;
                    idPickMove = child;
                    hasilState = State(
                        nextMove,
                        nextHitstun,
                        nextProration,
                        nextTotalDamage,
                        nextComboCount
                    );
                }

            }
        }
        if (idPickMove == -1) {
            isKomboBerjalan = false;
        }
        else {
            currentState = hasilState;
            ruteKombo.push_back(hasilState.current_move);
            starterId = idPickMove;
        }

    }
    
    cout << "\n====================================\n";
    cout << "        HASIL RUTE KOMBO GREEDY     \n";
    cout << "====================================\n";
    cout << "Jalur Tombol : ";
    for (size_t i = 0; i < ruteKombo.size(); ++i) {
        cout << ruteKombo[i];
        if (i < ruteKombo.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Damage : " << currentState.total_damage << " Damage PTS\n";
    cout << "====================================\n";
}


