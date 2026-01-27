#ifndef TTC_H
#define TTC_H

#include <random>
# include "Board.h"


class TicTacToe{

    public:

    std::mt19937 mt{};

    Board::Board state;
    int turn;
    int result=2;
    std::vector<Board::Action> playableMoves;
    std::vector<std::vector<Board::Action>> winningCombinations = {{{0,0},{0,1},{0,2}},{{0,0},{1,1},{2,2}},{{0,0},{1,0},{2,0}},{{2,0},{1,1},{0,2}},{{2,0},{2,1},{2,2}},{{0,2},{1,2},{2,2}},{{0,1},{1,1},{2,1}},{{1,0},{1,1},{1,2}}};


    TicTacToe ();
    TicTacToe(Board::Board state);
    void CalculatePlayableMoves();
    void Display();
    int Move(Board::Action action);
    int Result();
    void Play();
    int Simulate();
    void PlayMCTS();
};


#endif
