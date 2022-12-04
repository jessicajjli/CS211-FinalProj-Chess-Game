#pragma once

#include "model.hxx"
static const int cell_size = 50;
class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;
    explicit View(Model const& model);

    Dimensions initial_window_dimensions() const;

    void draw(ge211::Sprite_set& set, Position mouse_pos);

    Position screen_to_board(Position screen_pos) const;
    // Converts an abstract board position to a concrete screen
    // position.
    Position board_to_screen(Position board_pos) const;

    void draw_pawn(Position pos, int color, ge211::Sprite_set& set) const;
    void draw_bishop(Position pos, int color, ge211::Sprite_set& set) const;
    void draw_king(Position pos, int color, ge211::Sprite_set& set) const;
    void draw_queen(Position pos, int color, ge211::Sprite_set& set) const;
    void draw_knight(Position pos, int color, ge211::Sprite_set& set) const;
    void draw_rook(Position pos, int color, ge211::Sprite_set& set) const;
    void add_winner_tile_( ge211::Sprite_set& set, int z) const;

private:
    Model const& model_;
    //pieces
    ge211::Rectangle_sprite const tile_;
    ge211::Image_sprite dark_pawn_sprite_;
    ge211::Image_sprite light_pawn_sprite_;
    ge211::Image_sprite dark_bishop_sprite_;
    ge211::Image_sprite light_bishop_sprite_;
    ge211::Image_sprite dark_king_sprite_;
    ge211::Image_sprite light_king_sprite_;
    ge211::Image_sprite dark_queen_sprite_;
    ge211::Image_sprite light_queen_sprite_;
    ge211::Image_sprite dark_knight_sprite_;
    ge211::Image_sprite light_knight_sprite_;
    ge211::Image_sprite dark_rook_sprite_;
    ge211::Image_sprite light_rook_sprite_;
    //tiles
    ge211::Rectangle_sprite const winner_tile_;
    ge211::Rectangle_sprite const poss_move_;
    //turn helpers
    ge211::Circle_sprite const wsmall_circle_;
    ge211::Circle_sprite const bsmall_circle_;
};
