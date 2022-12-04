#include "model.hxx"

using namespace ge211;


//initializes board as 2D 8x8 vector
Model::Model()
    :piece_pressed_(Piece(Piece_type::none,
                          {0,0},-1,
                          {},false))
{
    for (int i = 0; i < 8; i++) {
        squares_.push_back(std::vector<Piece>());
    }
    //vector of 8 vectors, each as a row on chessboard
    int counter = 0;
    for (std::vector<Piece>& vec: squares_) {
        for (int i = 0; i < 8; i++) {//i is column
            vec.push_back(Piece( Piece_type::none,
                                {i, counter},
                                -1,{}, false));
            //-1 is empty
            //adding 8 empty pieces into each row/column
        }
        counter += 1; //y coord
    }
    //SETS BEGINNING POSITIONS
    squares_[0][0] = Piece(Piece_type::rook,
                           {0, 0}, 0,
                           {}, true);
    squares_[1][0] = Piece(Piece_type::knight,
                           {1, 0}, 0,
                           {}, true);
    squares_[2][0] = Piece( Piece_type::bishop,
                           {2, 0}, 0,
                           {}, true);
    squares_[3][0] = Piece(Piece_type::queen,
                           {3, 0}, 0,
                           {}, true);
    squares_[4][0] = Piece(Piece_type::king,
                           {4, 0}, 0,
                           {}, true);
    squares_[5][0] = Piece(Piece_type::bishop,
                           {5, 0}, 0,
                           {}, true);
    squares_[6][0] = Piece(Piece_type::knight,
                           {6, 0}, 0,
                           {}, true);
    squares_[7][0] = Piece(Piece_type::rook,
                           {7, 0}, 0,
                           {},true);


    squares_[0][7] = Piece(Piece_type::rook,
                           {0, 7}, 1,
                           {},true);
    squares_[1][7] = Piece(Piece_type::knight,
                           {1, 7}, 1,
                           {}, true);
    squares_[2][7] = Piece(Piece_type::bishop,
                           {2, 7}, 1,
                           {}, true);
    squares_[3][7] = Piece(Piece_type::queen,
                           {3, 7}, 1,
                           {}, true);
    squares_[4][7] = Piece(Piece_type::king,
                           {4, 7}, 1,
                           {}, true);
    squares_[5][7] = Piece(Piece_type::bishop,
                           {5, 7}, 1,
                           {}, true);
    squares_[6][7] = Piece(Piece_type::knight,
                           {6, 7}, 1,
                           {}, true);
    squares_[7][7] = Piece(Piece_type::rook,
                           {7, 7}, 1,
                           {}, true);
//Sets Pawns
    for (int p = 0; p < 8; p++) {
        squares_[p][1] = Piece(
                Piece_type::pawn,{p, 1},
                0,{}, true);
        squares_[p][6] = Piece(
                Piece_type::pawn,{p, 6},
                1,{}, true);
    }
}

//Operator
Piece
Model::operator[](Position pos) const
{
    return squares_[pos.x][pos.y];
}


//CHANGES TURNS
void
Model::change_turn()
{
    if (turn_ == 1) {
        turn_ = 0;
    }else{
        turn_ = 1;
    }
}


//resets piece pressed
void
Model::reset_piece_pressed() {
    piece_pressed_ = Piece(Piece_type::none, {0, 0}, -1, {}, false);
}



//plays move
//move_to is where the piece wants to go to
//move_from is where the piece came from

void
Model::play_move(Position move_to, Position move_from, Piece piece)
{

    if(squares_[move_to.x][move_to.y].get_color() != get_turn()){
        if(squares_[move_to.x][move_to.y].get_name() == Piece_type::king){
            winner_ = get_turn();
        }
    }

    Piece move_piece = Piece(piece); // making copy of piece that is moving
    move_piece.set_posn({move_to.x, move_to.y});
    squares_[move_to.x][move_to.y] = move_piece;

    squares_[move_from.x][move_from.y].set_active(false);
    squares_[move_from.x][move_from.y].set_name(Piece_type::none);
    squares_[move_from.x][move_from.y].set_color(-1);

    reset_piece_pressed();
    change_turn();
}





