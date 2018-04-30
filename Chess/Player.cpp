//
//  Player.cpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#include "Player.hpp"

// returns a players unordered map of pieces
unordered_map<string, Piece*> Player::getMap(){
    return this->Pieces;
}
//gets name
string Player::get_name(){
    return name;
}
//sets name
void Player::set_name(string n){
    name = n;
}

// adds piece to map
void Player::add_to_map(string key, Piece* value){
    Pieces.insert(make_pair(key, value));
}
// deletes piece from map
void Player::erase_from_map(string key){
    Pieces.erase(key);
}

// deletes all moves that have their own team in the way
void Player::narrow_moves(vector<vector<string>>& moves){
    for (int i = 0; i < moves.size(); i++){
        for (int j = 0; j < moves[i].size(); j++){
            if (j == 0 && Pieces.find(moves[i][j]) != Pieces.end()){
                moves.erase(moves.begin()+i);
                i--;
                break;
            }else if (Pieces.find(moves[i][j]) != Pieces.end()){
                for (unsigned long k = moves[i].size()-1; k >= j; k--){
                    moves[i].pop_back();
                }
            }
        }
    }
}

// deletes all moves that have the other team in the way
void Player::narrow_moves(vector<vector<string>>& moves, Player* otherPlayer){
    unordered_map<string, Piece*> Other_Pieces = otherPlayer->getMap();
    for (int i = 0; i < moves.size(); i++){
        for (int j = 0; j < moves[i].size(); j++){
            if (Other_Pieces.find(moves[i][j]) != Other_Pieces.end()){
                for (unsigned long k = moves[i].size()-1; k > j; k--){
                    moves[i].pop_back();
                }
            }
        }
    }
}

// returns only the valid moves
unordered_set<string> Player::valid_moves(Player* Other_Player, Piece* my_piece){
    // Generate all valid moves
    vector<vector<string>> my_moves = my_piece->Generate_all_moves();
    narrow_moves(my_moves);
    narrow_moves(my_moves, Other_Player);
    
    // convert vector into set
    unordered_set<string> my_set;
    for (vector<string> i: my_moves){
        for (string j: i){
            my_set.insert(j);
        }
    }
    return my_set;
}

// returns true if a move was made or false if a move wasn't made
bool Player::move(string loc1, string loc2, Player* Other_Player){
    
    // no piece to move, return false
    if (Pieces.find(loc1) == Pieces.end()) return false;
    
    unordered_set<string> Valid_moves = valid_moves(Other_Player, Pieces.at(loc1));
    // piece can't move to loc2, return false
    if (Valid_moves.find(loc2) == Valid_moves.end()) return false;
    
    // if we got here, all is well let's move the piece then return true
    // save pointer to piece we want to move
    Piece* holder = Pieces.at(loc1);
    
    // delete old mapping to this piece since we're changing its key
    erase_from_map(loc1);
    
    // if the the opponent has a piece at loc2, erase from map
    unordered_map<string, Piece*> temp_map = Other_Player->getMap();
    if (temp_map.find(loc2) != temp_map.end()){
        Other_Player->erase_from_map(loc2);
        cout << "Player Lost Piece at " << loc2 << endl;
    }
    
    // add piece with new location to map
    add_to_map(loc2, holder);
    
    return true;
}

// returns true if there is still a king, false otherwise 
bool Player::check_for_king(){
    for (pair<string, Piece*> i: Pieces){
        if (i.second->get_worth() == 100) return true;
    }
    return false;
}
