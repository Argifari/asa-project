
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "ga.h"
#include "../dataRead/read_data.h"

using namespace std;


int evaluasiKomboKromosom(const vector<int>& kromosom, const vector<MoveData>& databaseSol) {
    if (kromosom.empty()) return 0;

    MoveData starterMove = searchMoveById(kromosom[0], databaseSol);
    State currentState(
        starterMove.moveNotation,
        starterMove.hitstun,
        starterMove.proration,
        starterMove.damage,
        1
    );

    MoveData prevMove = starterMove;
    for (long long i = 1; i < kromosom.size(); ++i) {
        int childId = kromosom[i];
        MoveData childMove = searchMoveById(childId, databaseSol);

        auto it = find(prevMove.validCancel.begin(), prevMove.validCancel.end(), childId);

        if (it == prevMove.validCancel.end()) {
            return 0; 
        }

        int currHitstun = currentState.enemy_hitstun_left - childMove.startupFrame;

        if (currHitstun >= 0) {
            int tempDamage = static_cast<int>(childMove.damage * currentState.current_proration);
            if (tempDamage <= 0) continue;
        
            int decayedHitstun = childMove.hitstun - (currentState.combo_count*DECAY_FACTOR);
            if (decayedHitstun < 2) decayedHitstun = 2;

            currentState.enemy_hitstun_left = currHitstun + decayedHitstun;
            currentState.current_proration = childMove.proration*currentState.current_proration;
            currentState.total_damage = currentState.total_damage + tempDamage;
            currentState.combo_count = currentState.combo_count + 1;
        }
        
        prevMove = childMove;
    }

    return currentState.total_damage;

}



Individu tournamentSelection(const vector<Individu>& populasi, int tournamentSize) {
    Individu bestKandidat = populasi[rand() % populasi.size()];

    for (int i = 1; i < tournamentSize; i++) {
        Individu kandidat = populasi[rand() % populasi.size()];

        if (kandidat.fitness > bestKandidat.fitness) {
            bestKandidat = kandidat;
        }
    }
    return bestKandidat;

}


void GeneticAlgorithm(int starterId,vector<MoveData>& databaseSol) {
    srand(time(0));
    vector<Individu> populasi(UKURAN_POPULASI);

    for (int i = 0; i < UKURAN_POPULASI; i++) {
        populasi[i].kromosom.push_back(starterId);

        int currentId = starterId;
        bool lanjut = true;

        while (lanjut) {
            MoveData currentMove = searchMoveById(currentId, databaseSol);

            if (currentMove.validCancel.empty()) break;
            int nextId = currentMove.validCancel[rand() % currentMove.validCancel.size()];
            populasi[i].kromosom.push_back(nextId);

            currentId = nextId;

            if (populasi[i].kromosom.size() >= 12 || rand() % 100 < 20) lanjut = false;
        }

        populasi[i].fitness = evaluasiKomboKromosom(populasi[i].kromosom, databaseSol);

    }

    for (int gen = 0; gen < MAKS_GENERASI; gen++) {

        sort(populasi.begin(), populasi.end(), [](const Individu& a, const Individu& b) {
            return a.fitness > b.fitness;
        });

        vector<Individu> populasiBaru;

        populasiBaru.push_back(populasi[0]);
        populasiBaru.push_back(populasi[1]);

        while (populasiBaru.size() < UKURAN_POPULASI) {
            Individu p1 = tournamentSelection(populasi, TOURNAMENT_SIZE);
            Individu p2 = tournamentSelection(populasi, TOURNAMENT_SIZE);

            Individu anak = p1;

            double randCross = static_cast<double>(rand()) / RAND_MAX;
            if (randCross < PROB_CROSSOVER) {
                if (p1.kromosom.size() > 2 && p2.kromosom.size() > 2) {
                    long long cut = 1 + (rand() % (p1.kromosom.size() - 1));

                    anak.kromosom.resize(cut);

                    for (long long k = cut; k < p2.kromosom.size(); k++) {
                        anak.kromosom.push_back(p2.kromosom[k]);
                    }
                }
            }

            double randMut = static_cast<double>(rand()) / RAND_MAX;

            if (randMut < PROB_MUTASI) {
                if (anak.kromosom.size() > 1) {
                    long long mutIdx = 1 + (rand() % (anak.kromosom.size() - 1));
                    MoveData prevMove = searchMoveById(anak.kromosom[mutIdx - 1], databaseSol);

                    if (!prevMove.validCancel.empty()) {
                        anak.kromosom[mutIdx] = prevMove.validCancel[rand() % prevMove.validCancel.size()];
                    }
                }
            }

            anak.fitness = evaluasiKomboKromosom(anak.kromosom, databaseSol);
            populasiBaru.push_back(anak);

        }

        populasi = populasiBaru;

    }

    sort(populasi.begin(), populasi.end(), [](const Individu& a, const Individu& b) {
        return a.fitness > b.fitness;
    });

    Individu solusiTerbaik = populasi[0];

    // Cetak Hasil Akhir Kombo Teroptimal via GA
    cout << "\n====================================\n";
    cout << "         HASIL RUTE KOMBO GA        \n";
    cout << "====================================\n";
    cout << "Jalur Tombol Terbaik : ";
    for (size_t i = 0; i < solusiTerbaik.kromosom.size(); ++i) {
        MoveData m = searchMoveById(solusiTerbaik.kromosom[i], databaseSol);
        cout << m.moveNotation;
        if (i < solusiTerbaik.kromosom.size() - 1) cout << " -> ";
    }
    cout << "\nMax Total Damage     : " << solusiTerbaik.fitness << " Damage PTS\n";
    cout << "====================================\n";
}

