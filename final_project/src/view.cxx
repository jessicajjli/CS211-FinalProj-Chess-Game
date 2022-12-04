#include "view.hxx"

static int const grid_size = 50;
//initializes all the sprites
View::View(Model const& model)
        : model_(model),
          tile_({grid_size-1, grid_size-1},
                {0, 151, 0}),
          dark_pawn_sprite_("dark_pawn.png"),
          light_pawn_sprite_("white_pawn.png"),
          dark_bishop_sprite_("dark_bishop.png"),
          light_bishop_sprite_("white_bishop.png"),
          dark_king_sprite_("dark_king.png"),
          light_king_sprite_("white_king.png"),
          dark_queen_sprite_("dark_queen.png"),
          light_queen_sprite_("white_queen.png"),
          dark_knight_sprite_("dark_knight.png"),
          light_knight_sprite_("white_knight.png"),
          dark_rook_sprite_("dark_rook.png"),
          light_rook_sprite_("white_rook.png"),
          winner_tile_({grid_size-1, grid_size-1},
                      {180, 180, 180}),
          poss_move_({grid_size-1, grid_size-1},
                           {200, 0, 0}),
          wsmall_circle_(10, {200, 200, 200}),
          bsmall_circle_(10, {0, 0, 0})
{ }

//sets initial window dimensions
View::Dimensions
View::initial_window_dimensions() const
{
    return {cell_size * model_.grid_size,
            cell_size * model_.grid_size};
}

//draws sprite to board
void
View::draw(ge211::Sprite_set& set, ge211::Posn<int> mouse_pos)
{
    // add sprites for pieces here
    for (std::vector<Piece> vec: model_.squares()){
        for (Piece curr_piece: vec) {// is column
            if(curr_piece.get_active()){
                // Draw pawn sprite
                if (curr_piece.get_name() == Piece_type::pawn) {
                    draw_pawn(curr_piece.get_posn(),
                              curr_piece.get_color(), set);
                }
                if (curr_piece.get_name() == Piece_type::bishop) {
                    draw_bishop(curr_piece.get_posn(),
                                curr_piece.get_color(), set);
                }
                if (curr_piece.get_name() == Piece_type::king) {
                    draw_king(curr_piece.get_posn(),
                              curr_piece.get_color(), set);
                }
                if (curr_piece.get_name() == Piece_type::queen) {
                    draw_queen(curr_piece.get_posn(),
                               curr_piece.get_color(), set);
                }
                if (curr_piece.get_name() == Piece_type::knight) {
                    draw_knight(curr_piece.get_posn(),
                                curr_piece.get_color(), set);
                }
                if (curr_piece.get_name() == Piece_type::rook) {
                    draw_rook(curr_piece.get_posn(),
                              curr_piece.get_color(), set);
                }
            }
         }
    }

    // add squares for grid here
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            set.add_sprite(tile_,board_to_screen({i,j}), 0);
            Position_set move_set = model_.get_piece_pressed().get_valid_moves();
            Position curr = {i,j};
            if (move_set[curr]){
                set.add_sprite(poss_move_,board_to_screen({i,j}), 1);
            }
        }
    }



    //turn sprites
    if(model_.get_turn() == 0){
        set.add_sprite(bsmall_circle_,
                       mouse_pos, 4);
    }
    if(model_.get_turn() == 1){
        set.add_sprite(wsmall_circle_,
                       mouse_pos, 4);
    }

    add_winner_tile_(set, 2);

}

//helpers for settings positions on board
View::Position
View::board_to_screen(Position pos) const
{
    return {grid_size * pos.x, grid_size * pos.y};
}
View::Position
View::screen_to_board(Position pos) const
{
    Position p = {pos.x/(grid_size), pos.y/(grid_size)};
    return p;
}

//
//helper functions for drawing pieces
//
void
View::draw_pawn(Position pos, int color, ge211::Sprite_set& set) const {
    if(color==0) {
        set.add_sprite(dark_pawn_sprite_,
                       board_to_screen(pos), 3);
    }else{
        set.add_sprite(light_pawn_sprite_,
                       board_to_screen(pos), 3);
    }
}

void
View::draw_bishop(Position pos, int color, ge211::Sprite_set& set) const {
    if(color==0) {
        set.add_sprite(dark_bishop_sprite_,
                       board_to_screen(pos), 3);
    }else{
        set.add_sprite(light_bishop_sprite_,
                       board_to_screen(pos), 3);
    }
}

void
View::draw_king(Position pos, int color, ge211::Sprite_set& set) const {
    if(color==0) {
        set.add_sprite(dark_king_sprite_,
                       board_to_screen(pos), 3);
    }else{
        set.add_sprite(light_king_sprite_,
                       board_to_screen(pos), 3);
    }
}

void
View::draw_queen(Position pos, int color, ge211::Sprite_set& set) const {
    if(color==0) {
        set.add_sprite(dark_queen_sprite_,
                       board_to_screen(pos), 3);
    }else{
        set.add_sprite(light_queen_sprite_,
                       board_to_screen(pos), 3);
    }
}

void
View::draw_knight(Position pos, int color, ge211::Sprite_set& set) const {
    if(color==0) {
        set.add_sprite(dark_knight_sprite_,
                       board_to_screen(pos), 3);
    }else{
        set.add_sprite(light_knight_sprite_,
                       board_to_screen(pos), 3);
    }
}

void
View::draw_rook(Position pos, int color, ge211::Sprite_set& set) const {
    if(color==0) {
        set.add_sprite(dark_rook_sprite_,
                       board_to_screen(pos), 3);
    }else{
        set.add_sprite(light_rook_sprite_,
                       board_to_screen(pos), 3);
    }
 }


 //adds winner tile
void
View::add_winner_tile_(ge211::Sprite_set& set,
        int z) const
{
    if(model_.get_winner() != -1) {
        for (int row = 0; row < 8; row++) {
            for (int i = 0; i < 8; i++) {//i is column
                if(model_.get_color_at_square(row, i) == model_.get_winner()){
                    set.add_sprite(winner_tile_, board_to_screen({row, i}), 2);
                }
            }
        }
    }

}



