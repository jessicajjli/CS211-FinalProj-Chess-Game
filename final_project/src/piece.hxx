#pragma once
#include <ge211.hxx>
#include <iostream>
#include "position_set.hxx"


//enum for each type of piece used
enum class Piece_type
{
    knight,
    queen,
    king,
    rook,
    bishop,
    pawn,
    none,
};

class Piece{

private:
    Piece_type name_;
    ge211::Posn<int> piece_posn_; //(x,y) -> represents indices in vectors
    int color_; //0 is black, 1 is white, -1 is empty color
    Position_set valid_moves_;
    bool active_; //true if alive/active, false if dead/captured
    bool is_valid_move(ge211::Posn<int>, std::vector<std::vector<Piece>>);

public:
    Piece(Piece_type name_,
          ge211::Posn<int> piece_posn_,
          int color_,
          Position_set valid_moves_,
          bool active_);
    //gets name
    using Position = ge211::Posn<int>;
    Piece_type get_name(){
        return name_;
    }
    //gets valid moves
    Position_set get_valid_moves(){
        return valid_moves_;
    }
    //gets color
    int get_color() const{
        return color_;
    }
    //gets if active or not
    bool get_active(){
        return active_;
    }
    //sets name
    void set_name(Piece_type);

    //sets color
    void set_color(int color);

    //sets active status
    void set_active(bool);

    //sets other player
    int other_player(int);

    friend bool operator==(Piece, Piece);

    //get posn
    ge211::Posn<int> get_posn(){
        return piece_posn_;
    }
    //set posn
    void set_posn(ge211::Posn<int> pos);

    //constructor, create a piece
    void set_valid_moves(std::vector<std::vector<Piece>>);

    bool good_position(ge211::Posn<int>);

    //gets color at square
    int get_color_at_square(int x, int y, std::vector<std::vector<Piece>>
    squares){
        return squares[x][y].get_color();
    }

};