#include "piece.hxx"
#include <vector>


//INITIALIZER
Piece::Piece(Piece_type name_,
             ge211::Posn<int> piece_posn_,
             int color_,
             Position_set valid_moves_,
             bool active_)
        :
        name_(name_),
        piece_posn_(piece_posn_),
        color_(color_),
        valid_moves_(valid_moves_),
        active_(active_)
//0 is black, 1 is white
{}


//sets piece position
void
Piece::set_posn(ge211::Posn<int> pos) {
    piece_posn_ = pos;
}

//sets piece active
void
Piece::set_active(bool active){
    active_ = active;
}
//sets piece's name
void
Piece::set_name(Piece_type name){
    name_ = name;
}
//sets piece color
void
Piece::set_color(int color){
    color_ = color;
}
//overloading the == operator for Piece
bool
operator==(Piece piece1, Piece piece2){
    return piece1.get_active() == piece2.get_active() && piece1.get_name() ==
    piece2.get_name() && piece1.get_color() == piece2.get_color() && piece1
    .get_valid_moves() == piece2.get_valid_moves() && piece1.get_posn() ==
    piece2.get_posn();
}

//Rules for Each Piece
//puts a Position set into valid_moves_ which is the piece's valid move in
// the curr position
void
Piece::set_valid_moves(std::vector<std::vector<Piece>> squares){
    //add valid moves in
    valid_moves_ = {};
    if(name_ == Piece_type::rook) {
        //while loop
        //list of spot
        std::vector<ge211::Dims<int>> directions = {
                {1,0},{0,1},
                {-1,0},{0,-1}};
        for (auto m : directions){
            bool b = true;
            Position curr = piece_posn_ + m;
            while (b) {
                //int i = 0;
                //ge211::Posn<int> move_pos1 = piece_posn_.up_by(i)
                //set_valid _moves takes in arguement (whole board )->don't
                // take from model
                if (!is_valid_move(curr, squares)) {
                    break;
                }
                int curr_square_color = get_color_at_square(curr.x, curr.y,
                                                            squares);
                if (curr_square_color == other_player(color_)){
                    valid_moves_ |= {curr};
                    break;
                }
                //add the player to the list and then return
                if (curr_square_color == -1){
                    valid_moves_ |= {curr};
                }
                //if it's an empty square within bounds
                //add to list
                curr = curr + m;
            }
        }
        //valid_moves_ =
        //if coords ->all direction, one coord stays the same
    } else if(name_ == Piece_type::king){
        std::vector<ge211::Dims<int>> directions = {
                {1,0},{1,1},{0,1},
                {-1,1},{-1,0},{-1,-1},
                {0,-1},{1,-1}};
        for (auto m : directions){
            Position curr = piece_posn_ + m;
            if (is_valid_move(curr, squares)){
                valid_moves_ |= {curr};
            }
        }

    }
    else if(name_ == Piece_type::queen){
        std::vector<ge211::Dims<int>> directions = {
                {1,0},{1,1},{0,1},
                {-1,1},{-1,0},{-1,-1},
                {0,-1},{1,-1}};
        for (auto m : directions){
            bool b = true;
            Position curr = piece_posn_ + m;
            while (b) {
                //int i = 0;
                //ge211::Posn<int> move_pos1 = piece_posn_.up_by(i)
                //set_valid _moves takes in arguement (whole board )->don't
                // take from model
                if (!is_valid_move(curr, squares)) {
                    break;
                }
                int curr_square_color = get_color_at_square(
                        curr.x, curr.y, squares);
                if (curr_square_color == other_player(color_)){
                    valid_moves_ |= {curr};
                    break;
                }

                //add the player to the list and then return
                if (curr_square_color == -1){
                    valid_moves_ |= {curr};
                }
                //if it's an empty square within bounds
                //add to list
                curr = curr + m;
            }
        }
    }
        //knight direction
    else if(name_ == Piece_type::knight) {
        //return in model (see reversi)
        std::vector<ge211::Dims<int>> directions = {
                {1,-2},{-1,-2},{2,-1},
                {2,1},{1,2},{-1,2},
                {-2,1},{-2,-1}};
        for (auto m : directions) {
            Position curr = piece_posn_ + m;
            if (!is_valid_move(curr, squares)) {
                continue;
            }
            int curr_square_color = get_color_at_square(
                    curr.x, curr.y, squares);

            if (curr_square_color == other_player(color_) ||
                curr_square_color == -1) {
                valid_moves_ |= {curr};
            }
        }
    }
    else if(name_ == Piece_type::bishop){
        std::vector<ge211::Dims<int>> directions = {{1,1},
                                                    {-1,1},
                                                    {-1,-1},
                                                    {1,-1}};
        for (auto m : directions){
            bool b = true;
            Position curr = piece_posn_ + m;
            while (b) {
                //int i = 0;
                //ge211::Posn<int> move_pos1 = piece_posn_.up_by(i)
                //set_valid _moves takes in arguement (whole board )->don't
                // take from model

                if (!is_valid_move(curr, squares)) {//the square is out of
                    // bounds
                    break;
                }
                int curr_square_color = get_color_at_square(curr.x,curr.y,
                                                            squares);
                if (curr_square_color == other_player(color_)){
                    valid_moves_ |= {curr};
                    break;
                }
                //add the player to the list and then return
                if (get_color_at_square(curr.x, curr.y,squares) == -1){
                    valid_moves_ |= {curr};
                }
                //if it's an empty square within bounds
                //add to list
                curr = curr + m;
            }
        }
    }

        //dark is on the left, 0
        //light is on the right, 1

    else if(name_ == Piece_type::pawn){
        if(color_ == 0){
            ge211::Dims<int> direction = {0,1};
            Position curr = piece_posn_ + direction;
            if (is_valid_move(curr, squares)
                && get_color_at_square(curr.x,curr.y,squares)!=
                   other_player(color_)){
                valid_moves_ |= {curr};
            }
            ge211::Dims<int> dir_diag_bottom = {-1,1};
            ge211::Dims<int> dir_diag_up = {1,1};
            Position diag_bottom = piece_posn_ + dir_diag_bottom;

            if (good_position(diag_bottom) &&is_valid_move(diag_bottom,
                                                           squares)){
                if (get_color_at_square(diag_bottom.x,
                                        diag_bottom.y,squares)!=-1
                    && get_color_at_square
                               (diag_bottom.x,diag_bottom.y,squares)==
                       other_player(color_)){
                    valid_moves_ |= {diag_bottom};
                }
            }
            Position diag_up = piece_posn_ + dir_diag_up;
            if (good_position(diag_up) &&is_valid_move(
                    diag_up, squares)){
                if (get_color_at_square(diag_up.x,diag_up.y,squares)!=-1
                    && get_color_at_square(diag_up.x,diag_up.y,squares)==
                       other_player(color_)){
                    valid_moves_ |= {diag_up};
                }
            }
        }
        if (color_ == 1) {
            ge211::Dims<int> direction = {0,-1};
            Position curr = piece_posn_ + direction;
            if (is_valid_move(curr, squares)
                && get_color_at_square(curr.x,curr.y,squares)!=
                   other_player(color_)){
                valid_moves_ |= {curr};
            }
            ge211::Dims<int> dir_diag_bottom = {1,-1};
            ge211::Dims<int> dir_diag_up = {-1,-1};
            Position diag_bottom = piece_posn_ + dir_diag_bottom;

            if (good_position(diag_bottom) && is_valid_move(
                    diag_bottom, squares)){
                if (get_color_at_square(
                        diag_bottom.x,diag_bottom.y,squares)!=-1
                    && get_color_at_square(
                        diag_bottom.x,diag_bottom.y,squares)==
                       other_player(color_)){
                    valid_moves_ |= {diag_bottom};
                }
            }
            Position diag_up = piece_posn_ + dir_diag_up;
            if (good_position(diag_up) &&
                is_valid_move(diag_up, squares)){
                if (get_color_at_square(diag_up.x,diag_up.y,squares)!=-1
                    && get_color_at_square(diag_up.x,diag_up.y,squares)==
                       other_player(color_)){
                    valid_moves_ |= {diag_up};
                }
            }
        }
    }
}
//returns if pos in bounds
bool
Piece::good_position(ge211::Posn<int> pos)
{
    return 0 <= pos.x && pos.x < 8 && 0 <= pos.y && pos.y < 8;
}

//returns if pos is in bounds and if the color is dif than curr color
bool
Piece::is_valid_move(ge211::Posn<int> pos, std::vector<std::vector<Piece>>
squares){
    //checks if potential move is in bounds
    //returns true if is, false if not
    return good_position(pos) &&
           get_color_at_square(pos.x, pos.y, squares)
           != color_;

}
//return other player given curr player
int
Piece::other_player(int player)
{
    switch (player) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return -1;
    }
}
