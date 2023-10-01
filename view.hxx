#pragma once
#include <ge211.hxx>

struct Model;

struct View
{
public:
    explicit View(Model const&);
    void draw(ge211::Sprite_set& set);

private:
    Model const& model;
    ge211::Rectangle_sprite const hook_sprite;
    ge211::Rectangle_sprite const hook_sprite_extra_life;
    ge211::Rectangle_sprite const hook_sprite_multiplier;
    ge211::Circle_sprite const player_sprite;
    ge211::Font sans30_{"sans.ttf", 30};  // from view.hxx in random_text example
    ge211::Text_sprite score_sprite;
    ge211::Text_sprite word_sprite;
    ge211::Transform text_transform;
    ge211::Circle_sprite const mine_sprite;
};
