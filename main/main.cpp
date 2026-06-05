#include <iostream>
#include <string>
#include <vector>
#include "./algoritma/json.hpp"
#include "./variables/variables.h"
#include "./algoritma/greedy/greedy.h"
#include "./algoritma/bfs/bfs.h"
#include "./algoritma/dfs/dfs.h"
#include "./algoritma/dp/dp.h"
#include "./algoritma/ga/ga.h"

#include "./algoritma/dataRead/read_data.h"

using namespace std;

vector <MoveData> databaseSol;


int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    readMoveData("../data/solData.json", databaseSol);

    greedyAlgorithm(1,databaseSol);

    BFSAlgorithm(1,databaseSol);

    DFSAlgorithm(1,databaseSol);

    DPAlgorithm(1,databaseSol);

    GeneticAlgorithm(1,databaseSol);

    return 0;
}
