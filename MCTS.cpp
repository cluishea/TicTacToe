#include <iostream>
#include "Board.h"
#include "TTC.h"

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
    int visits;
    // Number of wins from this state
    int wins;
    // List of untried actions from this state
    std::vector<Board::Action> untriedActions;

    MCTSNode(Board::Board state, 
        MCTSNode* parentNode,
        Board::Action action, 
        int player
        ){

         state = state;
         parentNode = parentNode;
         action = action;
         player = player;
    }

    MCTSNode(Board::Board state, Board::Action action, int player){
        state = state;
        action = action;
        player = player;
    }

    

};

