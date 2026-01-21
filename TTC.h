#ifndef TTC
#define TTC

# include "Board.h"


class TicTacToe{

    public:

    Board::Board state;
    int turn;

    TicTacToe ();
    TicTacToe(Board::Board state, int turn);
    std::vector<Board::Action> PlayableMoves();
    void Display();
    
};


#endif
