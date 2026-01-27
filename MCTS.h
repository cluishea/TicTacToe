#ifndef MCTS_H
#define MCTS_H

#include "Board.h"

class MCTSNode{


    public:

    // State of the game
    Board::Board state;
    // Parent note (MCTSNode object)
    MCTSNode* parentNode = nullptr;
    // Actions that can be taken from this state
    Board::Action action;
    // Turn
    int player;
    // List of children of the current MCTSNode
    std::vector <MCTSNode*> children;
    // Number of visits
    int visits = 0;
    // Number of wins from this state
    double wins = 0.0;
    // List of untried actions from this state
    std::vector<Board::Action> untriedActions;

    MCTSNode(Board::Board s, int p);
    MCTSNode(Board::Board s, 
        MCTSNode* pN,
        Board::Action a, 
        int p
        );
    bool isTerminalNode();
    bool isFullyExpanded();
    MCTSNode* Expand();
    MCTSNode* BestChild();
    int Rollout();
    void BackPropagate(int winner);

};

Board::Action BestMove(Board::Board state, int numIter);


#endif
