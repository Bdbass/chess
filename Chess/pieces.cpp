//
//  pieces.cpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#include "pieces.hpp"

// PIECE methods
// default constructor
Piece:: Piece(){
    worth = 0;
    symbol = "";
    location = "";
}
// overloaded constructuor
Piece:: Piece(int wrth, string sym, string loc){
    worth = wrth;
    symbol = sym;
    location = loc;
}
// set location of piece
void Piece::set_loc(string new_loc){
    location = new_loc;
}
//get location of piece
string Piece::get_loc(){
    return location;
}
//get worth
int Piece::get_worth(){
    return worth;
}
//get symbol
string Piece::get_symbol(){
    return symbol; 
}

int* Piece::string_to_int(string loc){
    int* newArray = new int[2];
    newArray[0] = int(loc[0])-97;
    newArray[1] = loc[1]-'0'-1;
    return newArray;
}
string Piece::int_to_string(int* myArray){
    return (char)(myArray[0]+97)+ to_string(myArray[1]+1);
}
vector<vector<string>> Piece::Generate_all_moves(){
    vector<vector<string>> emptyVec;
    return emptyVec;
}

//ROOK methods

// constructor
rook:: rook(string sym, string loc): Piece(10, sym, loc){};

// generates all moves for knight
vector<vector<string>> rook::Generate_all_moves(){
    vector<vector<string>> moves;
    int* myarray = string_to_int(this->location);
    int temp[2];
    vector<string> tempV;
    bool newVec = 0;
    
    temp[0] = myarray[0];
    // generate top moves
    for (int i = myarray[1]+1; i < 8; i++){
        temp[1] = i;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    
    // generate bottom moves
    for (int i = myarray[1]-1; i >= 0; i--){
        temp[1] = i;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    temp[1] = myarray[1];
    // generate left moves
    for (int i = myarray[0]-1; i >= 0; i--){
        temp[0] = i;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    // generate right moves
    for (int i = myarray[0]+1; i < 8; i++){
        temp[0] = i;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
    }
    
    return moves;
}

// PAWN METHODS

// constructor
pawn:: pawn(string sym, string loc, bool c): Piece(1, sym, loc){
    first_move = 1;
    color = c;
}
// generate all moves for pawn
vector<vector<string>> pawn::Generate_all_moves(){
    vector<vector<string>> moves;
    int* myarray = string_to_int(this->location);
    int temp[2];
    vector<string> tempV;
    bool newVec = 0;
    
    // means black, starts at top
    if (color){
        // forward
        if (myarray[1] > 0){
            temp[0] = myarray[0];
            temp[1] = myarray[1]-1;
            tempV.push_back(int_to_string(temp));
            newVec = 1;
            if (first_move && myarray[1]-1 > 0){
                temp[0] = myarray[0];
                temp[1] = myarray[1]-2;
                tempV.push_back(int_to_string(temp));
            }
        }
    }else { // white starts at bottom
        // forward
        if (myarray[1] < 7){
            temp[0] = myarray[0];
            temp[1] = myarray[1]+1;
            tempV.push_back(int_to_string(temp));
            newVec = 1;
            if (first_move && myarray[1]+1 < 7){
                temp[0] = myarray[0];
                temp[1] = myarray[1]+2;
                tempV.push_back(int_to_string(temp));
            }
        }
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //right
    if (myarray[0] < 7){
        temp[1] = myarray[1];
        temp[0] = myarray[0]+1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //left
    if (myarray[0] > 0){
        temp[1] = myarray[1];
        temp[0] = myarray[0]-1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
    }
    return moves; 
}
// KNIGHT METHODS

// constructor
knight:: knight(string sym, string loc): Piece(15, sym, loc){};

//generate all moves for knight
vector<vector<string>>knight:: Generate_all_moves(){
    vector<vector<string>> moves;
    int* myarray = string_to_int(this->location);
    int temp[2];
    vector<string> tempV;
    
    //top right
    if (myarray[0]+1 <8 && myarray[1]+2 <8){
        temp[0] = myarray[0]+1;
        temp[1] = myarray[1]+2;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //upper right
    if (myarray[0]+2 <8 && myarray[1]+1 <8){
        temp[0] = myarray[0]+2;
        temp[1] = myarray[1]+1;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //lower right
    if (myarray[0]+2 <8 && myarray[1]-1 >=0){
        temp[0] = myarray[0]+2;
        temp[1] = myarray[1]-1;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //bottom right
    if (myarray[0]+1 <8 && myarray[1]-2 >=0){
        temp[0] = myarray[0]+1;
        temp[1] = myarray[1]-2;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //bottom left
    if (myarray[0]-1 >= 0 && myarray[1]-2 >=0){
        temp[0] = myarray[0]-1;
        temp[1] = myarray[1]-2;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //lower left
    if (myarray[0]-2 >= 0 && myarray[1]-1 >=0){
        temp[0] = myarray[0]-2;
        temp[1] = myarray[1]-1;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //upper left
    if (myarray[0]-2 >= 0 && myarray[1]+1 <8){
        temp[0] = myarray[0]-2;
        temp[1] = myarray[1]+1;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
        tempV.clear();
    }
    //top left
    if (myarray[0]-1 >= 0 && myarray[1]+2 <8){
        temp[0] = myarray[0]-1;
        temp[1] = myarray[1]+2;
        tempV.push_back(int_to_string(temp));
        moves.push_back(tempV);
    }
    return moves;
}

//BISHOP METHODS

// constructor
bishop:: bishop(string sym, string loc): Piece(15, sym, loc){};

//generate all moves for knight
vector<vector<string>>bishop:: Generate_all_moves(){
    vector<vector<string>> moves;
    int* myarray = string_to_int(this->location);
    int temp[2];
    vector<string> tempV;
    bool newVec = 0;
    
    //top right
    for (int i = myarray[0]+1, j = myarray[1]+1; i < 8 && j <8; i++, j++){
        temp[0] = i;
        temp[1] = j;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //top left
    for (int i = myarray[0]-1, j = myarray[1]+1; i >= 0 && j <8; i--, j++){
        temp[0] = i;
        temp[1] = j;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //bottom right
    for (int i = myarray[0]+1, j = myarray[1]-1; i < 8 && j >= 0; i++, j--){
        temp[0] = i;
        temp[1] = j;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    
    //bottom left
    for (int i = myarray[0]-1, j = myarray[1]-1; i >= 0 && j >= 0; i--, j--){
        temp[0] = i;
        temp[1] = j;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
    }
    
    return moves;
    
}

// KING METHODS

//constructor
king::king(string symbol, string loc): Piece(100, symbol, loc){
    first_move = 1;
}
// generate all moves for the king
vector<vector<string>> king::Generate_all_moves(){
    vector<vector<string>> moves;
    int* myarray = string_to_int(this->location);
    int temp[2];
    vector<string> tempV;
    bool newVec = 0;
    
    //top
    if (myarray[1] < 7){
        temp[0] = myarray[0];
        temp[1] = myarray[1]+1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
    moves.push_back(tempV);
    tempV.clear();
    newVec = 0;
    }
    //bottom
    if (myarray[1] > 0){
        temp[0] = myarray[0];
        temp[1] = myarray[1]-1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //right
    if (myarray[0] < 7){
        temp[1] = myarray[1];
        temp[0] = myarray[0]+1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //left
    if (myarray[0] > 0){
        temp[1] = myarray[1];
        temp[0] = myarray[0]-1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //top right
    if (myarray[1] < 7 && myarray[0] < 7){
        temp[0] = myarray[0]+1;
        temp[1] = myarray[1]+1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //bottom right
    if (myarray[1] > 0 && myarray[0] < 7){
        temp[0] = myarray[0]+1;
        temp[1] = myarray[1]-1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //top left
    if (myarray[1] < 7 && myarray[0] > 0){
        temp[1] = myarray[1]+1;
        temp[0] = myarray[0]-1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    //bottom left
    if (myarray[0] > 0 && myarray[1] > 0){
        temp[1] = myarray[1]-1;
        temp[0] = myarray[0]-1;
        tempV.push_back(int_to_string(temp));
        newVec = 1;
    }
    if (newVec){
        moves.push_back(tempV);
        tempV.clear();
        newVec = 0;
    }
    return moves;
}

// QUEEN METHODS

// constructor
queen::queen(string symbol, string loc):Piece(50, symbol, loc), rook(symbol, loc), bishop(symbol, loc){};

// generate all moves for queen
vector<vector<string>> queen::Generate_all_moves(){
    vector<vector<string>> moves;
    moves = rook::Generate_all_moves();
    vector<vector<string>> temp = bishop::Generate_all_moves();
    moves.insert(moves.end(), temp.begin(), temp.end());
    return moves;
}

