#include <iostream>
#include <cmath>
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
    double wins;
    // List of untried actions from this state
    std::vector<Board::Action> untriedActions;

    MCTSNode(Board::Board s){
        state=s;
    }

    MCTSNode(Board::Board s, 
        MCTSNode* pN,
        Board::Action a, 
        int p
        ){

         state = s;
         parentNode = pN;
         action = a;
         player = p;
    }

    MCTSNode(Board::Board s, Board::Action a, int p){
        state = s;
        action = a;
        player = p;
    }

    bool isTerminalNode(){
        if(TicTacToe(state).result==2){
            return 0;
        }else{
            return 1;
        }
    }

    bool isFullyExpanded(){
        if (untriedActions.size()==0){
            return true;
        }else{
            return false;
        }
    }

    MCTSNode* Expand(){
        if (!untriedActions.empty()){
            Board::Action nextAction = untriedActions.back();

            TicTacToe temp = TicTacToe(state);
            temp.Move(nextAction);
        
            MCTSNode childNode = MCTSNode(temp.state,nextAction,temp.turn);
            children.push_back(&childNode);

            return &childNode;
        }
    }

    MCTSNode* BestChild(){

        std::vector<double> childrenUCB; 
        double max = 0;
        int max_index = 0;

        for (int i = 0; i<=children.size();++i){
            if (children[i]->visits==0){
                return children[i];
            }
            double exploit = (double)children[i]->wins/children[i]->visits;
            double explore = 1.4*sqrt(log(visits)/children[i]->visits);

            if ((exploit+explore)>max){
                max = exploit+explore;
                max_index = i;
            }
        }
        return children[max_index];
    }

    int Rollout(){
        int winner = TicTacToe(state).Simulate();
        return winner;
    }

    void BackPropagate(int winner){
        ++visits;

        if(winner == 2){
            wins+=0.5;
        }else if(winner == player){
            wins+=1;
        }

        if(parentNode){
            parentNode->BackPropagate(winner);
        }

    }

};

Board::Action BestMove(Board::Board state, int numIter){
    MCTSNode rootNode = MCTSNode(state);

    for(int i = 0; i<numIter;++i){
        MCTSNode* node = &rootNode;

        while(!node->isTerminalNode() && node->isFullyExpanded()){
            node = node->BestChild();
        }
        if (!node->isFullyExpanded() && !node->isTerminalNode()){
            node = node->Expand();
        }

        int winner = node->Rollout();
        node->BackPropagate(winner);
    }

    int max = 0;
    int max_index = 0;
    for (int i = 0; i<rootNode.children.size();++i){
        if(rootNode.children[i]->visits>max){
            max = rootNode.children[i]->visits;
            max_index = i;
        }
    }

    return rootNode.children[max_index]->action;

}

int main(){

    

    return 0;
}
