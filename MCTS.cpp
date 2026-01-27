#include <iostream>
#include <cmath>
#include "Board.h"
#include "TTC.h"
#include "MCTS.h"



    MCTSNode::MCTSNode(Board::Board s, int p){
        state=s;
        untriedActions = TicTacToe(s).playableMoves;
        player = p;
    }

    MCTSNode::MCTSNode(Board::Board s, 
        MCTSNode* pN,
        Board::Action a, 
        int p
        ){

         state = s;
         parentNode = pN;
         action = a;
         player = p;
         untriedActions = TicTacToe(s).playableMoves;
    }


    bool MCTSNode::isTerminalNode(){
        if(TicTacToe(state).playableMoves.size()==0){
            return true;
        }else{
            return false;
        }
    }

    bool MCTSNode::isFullyExpanded(){
        if (untriedActions.size()==0){
            return true;
        }else{
            return false;
        }
    }

    MCTSNode* MCTSNode::Expand(){
        if (!untriedActions.empty()){
            Board::Action nextAction = untriedActions.back();
            untriedActions.pop_back();

            TicTacToe temp = TicTacToe(state);
            temp.Move(nextAction);
        
            MCTSNode* childNode = new MCTSNode(temp.state,this,nextAction,temp.turn);
            children.push_back(childNode);

            return childNode;
        }
        return nullptr;
    }

    MCTSNode* MCTSNode::BestChild(){

        std::vector<double> childrenUCB; 
        double max = 0;
        int max_index = 0;


        for (int i = 0; i<children.size();++i){
            if (children[i]->visits==0){
                return children[i];
            }
            double exploit = (double)children[i]->wins/children[i]->visits;
            double explore = 0.8*sqrt(log(visits)/children[i]->visits);

            if ((exploit+explore)>max){
                max = exploit+explore;
                max_index = i;
            }
        }
        return children[max_index];
    }

    int MCTSNode::Rollout(){
        int winner = TicTacToe(state).Simulate();
        return winner;
    }

    void MCTSNode::BackPropagate(int winner){
        ++visits;

        if(winner == 0){
            wins+=0.5;
        // I changed this so prob high chance of breaking
        }else if(winner != player){
            wins+=1;
        }else if(winner == player){
            wins-=2;
        }

        if(parentNode){
            parentNode->BackPropagate(winner);
        }

    }


Board::Action BestMove(Board::Board state, int numIter){


    MCTSNode rootNode = MCTSNode(state,TicTacToe(state).turn);

    

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
    for (int i = 0; i<rootNode.children.size();i++){
        std::cerr << rootNode.children[i]->visits << "     "<< rootNode.children[i]->wins << std::endl;
        if(rootNode.children[i]->wins > max){
            max = rootNode.children[i]->visits;
            max_index = i;
        }
    }
    std::cerr << max << "     "<< max_index;

    return rootNode.children[max_index]->action;

}

int main(){

    TicTacToe a = TicTacToe();
    a.PlayMCTS();


    return 0;
}
