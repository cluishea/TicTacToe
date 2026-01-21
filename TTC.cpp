#include <vector>
#include <iostream>
#include "Board.h"


class TicTacToe{

    public:

    Board::Board state;
    int turn;
    std::vector<Board::Action> playableMoves;

   TicTacToe (){
        state = {{0,0,0},{0,0,0},{0,0,0}};
        turn = 1;
        CalculatePlayableMoves();
   }

   TicTacToe(Board::Board s, int t){
        state = s;
        turn = t;
        CalculatePlayableMoves();
   }
   
   void CalculatePlayableMoves(){
        std::vector<Board::Action> temp;
        for (int i = 0; i<state.size();i++){
            for (int j = 0; j<state.at(0).size();j++){
                if (state.at(i).at(j)==0){
                    temp.push_back({i,j});
                }
            }
        }
        playableMoves = temp;
   }

   void Display(){

        std::cout << "Current State: "<<std::endl;

        for (int i = 0; i<state.size();i++){
            for (int j = 0; j<state.at(0).size();j++){
                std::cout << state.at(i).at(j);
            }
            std::cout<<std::endl;
        }

        std::cout << "Playable Moves: "<<std::endl;


        std::cout << "[";
        for (int i = 0; i<playableMoves.size();i++){ 
            std::cout << "(";
                std::cout << playableMoves.at(i).at(0) << "," << playableMoves.at(i).at(1);  
            std::cout<< ")";
        }
        std::cout << "]"<<std::endl;
   } 

   void Move(Board::Action action){ 
        for(int i = 0; i< playableMoves.size();i++){
            if (playableMoves.at(i).at(1)==action.at(1) && playableMoves.at(i).at(0)==action.at(0)){
                state.at(action.at(0)).at(action.at(1)) = turn;
                turn -= turn;
                CalculatePlayableMoves();
            }
        }



   }
   
   


};



int main(){


    std::cout << "Program Started.\n";

    TicTacToe a = TicTacToe({{1,0,-1},{0,0,0},{0,0,0}},1);
    a.Display();
    a.Move({1,1});
    a.Display();


    return 0;
}
