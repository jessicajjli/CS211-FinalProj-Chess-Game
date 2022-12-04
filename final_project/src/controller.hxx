#pragma once

#include "model.hxx"
#include "view.hxx"
#include "piece.hxx"

#include <ge211.hxx>
#include <utility>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    void on_mouse_up (ge211::Mouse_button, ge211::Posn<int>) override;
    //void on_mouse_down(ge211::Mouse_button, View::Position) override;
    void on_mouse_move (ge211::Posn<int>) override;
    void on_key(ge211::Key) override;

private:
    Model model_;
    View view_;
    ge211::Posn<int> mouse_pos = {0,0};
};
