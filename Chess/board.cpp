//
//  board.cpp
//  Chess
//
//  Created by Brandon Bass on 4/28/18.
//  Copyright © 2018 Brandon Bass. All rights reserved.
//

#include "board.hpp"

// black pieces
// king \u2654, queen \u2655, rook \u2656, bishop \u2657, knight \u2658, pawn \u2659

// white pieces
// king \u265A, queen \u265B, rook \u265C, bishop \u265D, knight \u265E, pawn \u265F

// converts two ints, to a string of them, i.e. 1,1 -> b2
string Board::int_to_string(int x, int y){
    return (char)(x+97)+ to_string(y+1);
}

int* Board::string_to_int(string loc){
    int* newArray = new int[2];
    newArray[0] = int(loc[0])-97;
    newArray[1] = loc[1]-'0'-1;
    return newArray;
}

// creates board and players
Board::Board(){
    // make first col of board a1-a8
    Piece* b_rk_1 = new rook("\u2656", "a8");
    Piece* w_rk_1 = new rook("\u265C", "a1");
    vector<Piece*> a = {w_rk_1, b_rk_1};
    
    // make first col of board b1-b8
    Piece* b_kn_1 = new knight("\u2658", "b8");
    Piece* w_kn_1 = new knight("\u265E", "b1");
    vector<Piece*> b = {w_kn_1, b_kn_1};
    
    // make first col of board c1-c8
    Piece* b_bp_1 = new bishop("\u2657", "c8");
    Piece* w_bp_1 = new bishop("\u265D", "c1");
    vector<Piece*> c = {w_bp_1, b_bp_1};
    
    // make first col of board d1-d8
    Piece* b_qn = new queen("\u2655", "d8");
    Piece* w_qn = new queen("\u265B", "d1");
    vector<Piece*> d = {w_qn, b_qn};
    
    // make first col of board e1-e8
    Piece* b_kg = new king("\u2654", "e8");
    Piece* w_kg = new king("\u265A", "e1");
    vector<Piece*> e = {w_kg, b_kg};
    
    //make col f
    Piece* b_bp_2 = new bishop("\u2657", "f8");
    Piece* w_bp_2 = new bishop("\u265D", "f1");
    vector<Piece*> f = {w_bp_2, b_bp_2};
    
    // make col g
    Piece* b_kn_2 = new knight("\u2658", "g8");
    Piece* w_kn_2 = new knight("\u265E", "g1");
    vector<Piece*> g = {w_kn_2, b_kn_2};
    
    // make col h
    Piece* b_rk_2 = new rook("\u2656", "h8");
    Piece* w_rk_2 = new rook("\u265C", "h1");
    vector<Piece*> h = {w_rk_2, b_rk_2};
    
    
    // add base pieces to the board
    myBoard = {a,b,c,d,e,f,g,h};
    
    // finish creating board by adding blank spots and pawns to my board
    vector<Piece*> temp;
    for (int j = 0; j < myBoard.size(); j++){
        temp.clear();
        for (int i = 1; i < 7; i++){
            Piece* piece_holder = nullptr;
            if (i == 1){
                piece_holder = new pawn("\u265F", int_to_string(j, i), 0);
            }else if(i == 6){
                piece_holder = new pawn("\u2659", int_to_string(j, i), 1);
            }
            temp.push_back(piece_holder);
        }
        myBoard[j].insert(myBoard[j].begin()+1, temp.begin(), temp.end());
    }
                                
     // add all pieces to players maps
    for (int j = 0; j < myBoard.size(); j++){
        for (int i = 0, k = 7; i < 2 && k > 5; i++, k--){
            Player1.add_to_map(int_to_string(j, i), myBoard[j][i]);
            Player2.add_to_map(int_to_string(j, k), myBoard[j][k]);
        }
    }
}

// helps print the board
void Board::printHelper1(){
    for (int j = 0; j < myBoard.size(); j++)
        cout << " _ _";
    cout << endl;
}

// prints visual representatin of board
void Board::Print(){
    for (int i = 7; i >= 0; i--){
        printHelper1();
        cout << "| ";
        for (int j = 0; j < 8; j++){
            if (myBoard[j][i] != nullptr){
                cout << myBoard[j][i]->get_symbol()+ " | ";
            }else{
                cout << "  | ";
            }
        }
        cout << endl;
    }
    printHelper1();
}

// grabs the moves that the player is going to make
void Board::Get_move(string& to, string& from, bool player){
    cout << " enter your move in the form 'from to', i.e a3 b4" << endl;
    if (player) cout << Player2.get_name();
    else cout << Player1.get_name();
    cout << " enter your move: ";
    cin >> from >> to;
}

// sets the player names
void Board::Set_Players(){
    string p1_name;
    string p2_name;
    cout << "Enter player1's name: ";
    cin >> p1_name;
    Player1.set_name(p1_name);
    cout << "Enter player2's name: ";
    cin >> p2_name;
    Player2.set_name(p2_name);
}

// checks for outside board conditions and whether there is a piece there or not
bool Board::Validate_move(bool player, string to, string from){
    // bad string
    if (to.length() != 2 || from.length() != 2) return 0;
    // outside boundaries
    if (to[0] > 'h' || to[0] < 'a' || from[0] > 'h' || from[0] < 'a') return 0;
    if (to[1] > '8' || to[1] < '1' || from[1] > '8' || from[1] < '1') return 0;

    return true;
}

// moves piece, by switching around pointers and deleting piece if needed
void Board::Move(bool player){
    string to;
    string from;
    int* start;
    int* end;
    
    bool success;
    
    // loops until the move is valid
    do{
        // loops until the move is semi-valid
        do{
            Get_move(to, from, player);
        }while(!Validate_move(player, to, from));
        if (player){//player2
            success = Player2.move(from, to, &Player1);
        }else { // player1
            success = Player1.move(from, to, &Player2);
        }
    }while(!success);
    
    // move is valid so update board pointers
    start = string_to_int(from);
    end = string_to_int(to);
    Piece* temp = myBoard[end[0]][end[1]];
    myBoard[end[0]][end[1]] = myBoard[start[0]][start[1]];
    myBoard[start[0]][start[1]] = nullptr;
    myBoard[end[0]][end[1]]->set_loc(to); 
    if (temp != nullptr){
        delete temp;
    }
}


