#include <vector>
#include <random>
#include <iostream>
#include "Board.h"


class TicTacToe{

    public:

    std::mt19937 mt{};

    Board::Board state;
    int turn;
    std::vector<Board::Action> playableMoves;

    std::vector<std::vector<Board::Action>> winningCombinations = {{{0,0},{0,1},{0,2}},{{0,0},{1,1},{2,2}},{{0,0},{1,0},{2,0}},{{2,0},{1,1},{0,2}},{{2,0},{2,1},{2,2}},{{0,2},{1,2},{2,2}},{{0,1},{1,1},{2,1}},{{0,2},{1,2},{2,2}}};
    int result=2;

    // Constructor for starting game state
   TicTacToe (){
        state = {{0,0,0},{0,0,0},{0,0,0}};
        turn = 1;
        CalculatePlayableMoves();
        Result();
   }

   // Constructor for any game state
   TicTacToe(Board::Board s){
        state = s;
        CalculatePlayableMoves();
        if (playableMoves.size()%2){
            turn = 1;
        }else{
            turn = -1;
        }
        Result();
   }

   // Calculateshe Playable moves in the current position and assigns it to playableMoves
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

   // Displays the current game state and playable moves
   void Display(){

        std::cout << "Current State: "<<std::endl;
        std::cout << "Turn: "<<turn<<std::endl;

        for (int i = 0; i<state.size();i++){
            for (int j = 0; j<state.at(0).size();j++){
                std::cout << state.at(i).at(j)<<'\t';
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


   // Changes the gamestate by playing an action
   int Move(Board::Action action){ 
        for(int i = 0; i< playableMoves.size();i++){
            if (playableMoves.at(i).at(1)==action.at(1) && playableMoves.at(i).at(0)==action.at(0)){
                state.at(action.at(0)).at(action.at(1)) = turn;
                turn = -turn;
                CalculatePlayableMoves();
            }
        }
        result = Result();
        return result;
   }


    //Checks if game ended (1,-1,0,2)
    int Result(){
        
        if(playableMoves.size()>=5){
            return 2;
        }else{
            for(int i = 0; i<winningCombinations.size();++i){
                if(state[winningCombinations.at(i).at(0).at(0)][winningCombinations.at(i).at(0).at(1)]==1 && 
                    state[winningCombinations.at(i).at(1).at(0)][winningCombinations.at(i).at(1).at(1)]==1 && 
                    state[winningCombinations.at(i).at(2).at(0)][winningCombinations.at(i).at(2).at(1)]==1){
                    return 1;
                } else if(state[winningCombinations.at(i).at(0).at(0)][winningCombinations.at(i).at(0).at(1)]==-1 && 
                    state[winningCombinations.at(i).at(1).at(0)][winningCombinations.at(i).at(1).at(1)]==-1 && 
                    state[winningCombinations.at(i).at(2).at(0)][winningCombinations.at(i).at(2).at(1)]==-1){
                    return -1;
                }
            }
            if (playableMoves.size()==0){
                return 0;
            }
        }
        return 2;
    }

    void Play(){
        std::cout<<"Starting game:"<<std::endl;

        int index;

        while(result == 2){
            Display();
            do{
                std::cout<<"Enter the index of the move you want to play:";
                std::cin>>index;
            }while(!(index>0 && index<=playableMoves.size()));

            Move(playableMoves[index-1]);

        }
        if (result == 1){
            std::cout<<"Player 1 won.";
        }else if (result == -1){
            std::cout<<"Player -1 won.";
        }else {
            std::cout << "Draw";
        }

        std::cout<<std::endl<<"Game ended."<<std::endl;

        Display();

    }

    int Simulate(){

        int index;

        while(result == 2){
        
            std::uniform_int_distribution<> randomMove{0,playableMoves.size()};
            index = randomMove(mt);

            Move(playableMoves[index]);

        }
        return result;
    }


};

