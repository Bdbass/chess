//
//  pieces.hpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#ifndef pieces_hpp
#define pieces_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Piece{
protected:
    int worth;
    string symbol;
    string location;
    
    int* string_to_int(string);
    string int_to_string(int*);
public:
    Piece();
    Piece(int wrth, string sym, string loc);
    int get_worth();
    string get_symbol();
    void set_loc(string new_loc);
    string get_loc();
    virtual vector<vector<string>> Generate_all_moves();
};

class rook: virtual public Piece{
public:
    rook(string symbol, string loc);
    vector<vector<string>> Generate_all_moves();
};

class pawn: public Piece{
private:
    bool first_move;
    bool color;
public:
    void set_move();
    bool get_move();
    pawn(string symbol, string loc, bool c);
    vector<vector<string>> Generate_all_moves();
};

class knight: public Piece{
public:
    knight(string symbol, string loc);
    vector<vector<string>> Generate_all_moves();
};

class bishop: virtual public Piece{
public:
    bishop(string symbol, string loc);
    vector<vector<string>> Generate_all_moves();
};

class king: public Piece{
private:
    bool first_move;
public:
    king(string symbol, string loc);
    vector<vector<string>> Generate_all_moves();
};

class queen:virtual public Piece, public rook, public bishop{
public:
    queen(string symbol, string loc);
    vector<vector<string>> Generate_all_moves();
};

#endif /* pieces_hpp */
