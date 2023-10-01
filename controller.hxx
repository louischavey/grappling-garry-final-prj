#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_frame(double last_frame_seconds) override;
    void on_mouse_down(ge211::events::Mouse_button, ge211::Posn<int>) override;

private:
    Model model_;
    View view_;
};

//test