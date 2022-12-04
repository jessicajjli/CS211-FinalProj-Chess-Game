#pragma once

#include <ge211.hxx>
#include "piece.hxx"
#include <list>

using Position = ge211::Posn<int>;


class Model
{

private:
    std::vector<std::vector<Piece>> squares_; // 8 rows, 8 columns
    int turn_ = 1; // 0 -> 'dark' or 1 -> 'light', starts with light
    int winner_ = -1; // 0 -> 'dark' or 1 -> 'light', -1-> tie
    std::list<Position> next_moves_;
    Piece piece_pressed_;



public:
    Model();
    Piece operator[](Position) const;

    const int grid_size = 8;

    //plays move
    void play_move(Position, Position, Piece);

    //changes turn
    void change_turn();

    //gets color at square
    int get_color_at_square(int x, int y) const{
        return squares_[x][y].get_color();
    }

    //gets piece
    Piece get_piece(Position pos){
        return squares_[pos.x][pos.y];
    }

    //gets piece pressed
    Piece get_piece_pressed() const{
        return piece_pressed_;
    }

    //sets piece pressed
    void set_piece_pressed(Piece piece) {
        piece_pressed_ = piece;
        piece_pressed_.set_valid_moves(squares_);
    }

    //resets piece pressed
    void reset_piece_pressed();

    //checks if pos is in set
    bool is_pos_in_set(Piece curr_piece, Position pos){
        Position_set valid_moves = curr_piece.get_valid_moves();
        if (valid_moves[pos]){
            return true;
        }
        return false;
    }
    //get current turn
    int get_turn() const{
        return turn_;
    }
    //get winner
    int get_winner() const{
        return winner_;
    }

    std::vector<std::vector<Piece>> squares() const
    { return squares_;}
    //getter function for squares


};