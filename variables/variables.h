#ifndef VARIABLES_H
#define VARIABLES_H
#include <string>
#include <vector>   

using namespace std;

const int DECAY_FACTOR = 1;

struct MoveData {
    int moveID;
    string moveName;
    string moveNotation;
    int damage;
    int startupFrame;
    int activeFrame;
    int recoveryFrame;
    int attackLevel;
    int hitstun;
    double proration;
    vector<int> validCancel;
};

struct State {
    std::string current_move;
    int enemy_hitstun_left;
    double current_proration;
    int total_damage;
    int combo_count; // <-- Tambahkan ini untuk melacak hit keberapa

    State(std::string m, int h, double p, int d, int c) 
        : current_move(m), enemy_hitstun_left(h), current_proration(p), total_damage(d), combo_count(c) {}
};

struct BfsNode {
    State state;
    vector<string> rute;
    int lastMoveId;

    BfsNode(State s, vector<string> r, int id) : state(s), rute(r), lastMoveId(id) {}
};




#endif