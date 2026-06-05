#ifndef GA_H
#define GA_H
#include "./variables/variables.h"
#include <vector>

using namespace std;

const int UKURAN_POPULASI = 50;
const int MAKS_GENERASI = 100;
const int TOURNAMENT_SIZE = 3;
const double PROB_CROSSOVER = 0.8;
const double PROB_MUTASI = 0.1;

struct Individu {
    vector<int> kromosom;
    int fitness;
};

/**
 * @brief Fungsi untuk mengevaluasi kombo pada kromosom untuk mengembalikan total damage.
 * * @param kromosom berisi child kandidat
 * * @param databaseSol berisi semua gerakan sol dan sudah terbentuk graf
 */
int evaluasiKomboKromosom(const vector<int>& kromosom, const vector<MoveData>& databaseSol);

/**
 * @brief Fungsi untuk menentukan Individu yang terbaik secara acak seperti seleksi alam
 * * @param populasi kandidat solusi 
 * * @param tournamentSize banyaknya seleksi yang dilakukan 
 */
Individu tournamentSelection(const vector<Individu>& populasi, int tournamentSize);

/**
 * @brief Prosedur untuk menyelesaikan permasalaahan dengan algoritma Genetic.
 * * @param starterId id move yang digunakan sebagai initial point
 * * @param databaseSol berisi semua gerakan sol dan sudah berbentuk graf.
 * 
 */
void GeneticAlgorithm(int starterId,vector<MoveData>& databaseSol);


#endif