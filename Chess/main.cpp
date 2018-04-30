//
//  main.cpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#include "board.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    Board NewBoard;
    NewBoard.Print();
    NewBoard.Set_Players();
    
    while(1){
        NewBoard.Move(0);
        NewBoard.Print();
        NewBoard.Move(1);
        NewBoard.Print(); 
    }
    
}
