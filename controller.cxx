#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{ }

// where all the events (on_frame, draw, etc.) are coming into
void Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

// can do some work every frame if you want to
void Controller::on_frame(double last_frame_seconds)
{
    model_.on_frame();
}

void Controller::on_mouse_down(ge211::events::Mouse_button, ge211::Posn<int>
        curr)
{
    if(model_._player.is_moving()) {
        return;
    }
    for(Hook* h : model_.hooks) {
        if((curr.x >= h->_coordinates.x - model_.hook_dims .width/2 &&
            curr.x <= h->_coordinates.x + model_.hook_dims .width/2) &&
            (curr.y >= h->_coordinates.y - model_.hook_dims .height/2 &&
            curr.y <= h->_coordinates.y + model_.hook_dims.height/2))
        {
            model_._player.move_to_hook(*h);
        }
    }
}