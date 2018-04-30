//
//  board.hpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include "Player.hpp"

class Board{
private:
    vector<vector<Piece*>> myBoard;
    Player Player1;
    Player Player2;
    
    string int_to_string(int, int);
    void printHelper1();
    void printHelper2();
    int* string_to_int(string loc);
    bool Validate_move(bool player, string to, string from);
    void Get_move(string& to, string& from, bool);
public:
    Board();
    void Set_Players();
    void Print();
    void Move(bool player);
}; 

#endif /* board_hpp */
