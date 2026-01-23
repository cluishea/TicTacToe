#ifndef TTC
#define TTC

# include "Board.h"


class TicTacToe{

    public:

    Board::Board state;
    int turn;
    int result;
    std::vector<Board::Action> playableMoves;

    TicTacToe ();
    TicTacToe(Board::Board state);
    void CalculatePlayableMoves();
    void Display();
    int Move(Board::Action action);
    int Result();
    void Play();
    int Simulate();
    
};


#endif
