#include "view.hxx"
#include "model.hxx"

static ge211::Color const hook_color {255, 0, 0};
static ge211::Color const player_color {255, 234, 0};
static ge211::Color const extra_life_color {255, 255, 255};
static ge211::Color const multiplier_color{0, 255, 0};
static ge211::Color const mine_color {0, 0, 255};

View::View(Model const& model)
        : model(model),
          hook_sprite(model.hook_dims, hook_color),
          hook_sprite_extra_life(model.hook_dims, extra_life_color),
          hook_sprite_multiplier(model.hook_dims, multiplier_color),
          player_sprite(model.player_radius, player_color),
          mine_sprite(model.player_radius/2, mine_color)
{}

// draws our hooks, mines, and score
void
View::draw(ge211::Sprite_set& set)
{
    ge211::geometry::Posn<int> temp_coords = {int(model._player._coordinates.x),
                                    int(model._player._coordinates.y)};
    set.add_sprite(player_sprite, temp_coords);
    for(Hook* h : model.hooks) {
        if(h->is_visible()) {
            temp_coords = {int(h->_coordinates.x),
                           int(h->_coordinates.y)};

            if(h->_power_up == 1) {
                set.add_sprite(hook_sprite_multiplier, temp_coords);
            }

            else if(h->_power_up == 2) {
                set.add_sprite(hook_sprite_extra_life, temp_coords);
            }

            else {
                set.add_sprite(hook_sprite, temp_coords);
            }

            Mine* m = model.get_mine(h);
            if(m && m->is_visible()) {
                temp_coords = {int(m->_coordinates.x),
                               int(m->_coordinates.y)};
                set.add_sprite(mine_sprite,temp_coords);
            }
        }
    }
    ge211::Text_sprite::Builder score_builder(sans30_);
    score_builder << "Score: " << model.score;
    score_sprite.reconfigure(score_builder);
    set.add_sprite(score_sprite, {0, 0});
}