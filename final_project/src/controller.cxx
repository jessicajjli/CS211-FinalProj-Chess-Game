#include "controller.hxx"


Controller::Controller()
        : model_(),
        view_(model_)
{}


//calls the draw function in view
void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse_pos);
}

//if user presses a key
void
Controller::on_key(ge211::Key k){
    if (ge211::Key::code('q') == k){
        quit();
    }
}
//for the screen game dimensions
View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}
//when user moves mouse
void Controller::on_mouse_move(ge211::Posn<int> pos)
{
    mouse_pos = pos;
}

//->trigger possible moves
//->selects one piece's possible moves at a time (all possible moves)
//selected space ->moves to space
void Controller::on_mouse_up(ge211::Mouse_button m, ge211::Posn<int>
        pos)
{

    if (model_.get_winner() == -1){
        ge211::Posn<int> board_p = view_.screen_to_board(pos);
        Position board_pos = {board_p.x, board_p.y};
        if (model_.get_piece(board_pos).get_color() == model_.get_turn()){
            model_.set_piece_pressed(model_.get_piece(board_pos));
        }
        if (model_.get_piece_pressed().get_name()
            != Piece_type::none && model_.is_pos_in_set(
                    model_.get_piece_pressed(), board_pos)){
            model_.play_move(board_pos, model_.get_piece_pressed().get_posn(),
                             model_.get_piece_pressed());
        }
    }
}


