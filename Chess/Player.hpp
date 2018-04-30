//
//  Player.hpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "pieces.hpp"

class Player{
private:
    unordered_map<string, Piece*> Pieces;
    void narrow_moves(vector<vector<string>>& moves);
    void narrow_moves(vector<vector<string>>& moves, Player*);
    unordered_set<string> valid_moves(Player*, Piece*);
    string name;
public:
    string get_name();
    void set_name(string); 
    unordered_map<string, Piece*> getMap();
    void add_to_map(string, Piece*);
    void erase_from_map(string);
    bool check_for_king();
    bool move(string loc1, string loc2, Player*);
};

#endif /* Player_hpp */
