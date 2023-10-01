#pragma once

#include <ge211.hxx>
#include "hook.hxx"
#include "mine.hxx"
#include "player.hxx"

class Model
{
private:
    void addHook(ge211::Posn<int> coordinate, int points) {};
    void addMine(ge211::Posn<int> coordinate) {};

    ge211::Dims<int> screen_dims;
    ge211::Timer hook_timer;  // timer for hook creation
    double hook_seconds;  // stores the elapsed time between creating hooks

    ge211::Random_source<int> random_x_coord_;
    ge211::Random_source<int> random_y_coord_lower;
    ge211::Random_source<int> random_y_coord_higher;
    ge211::Random_source<int> y_lower_higher;
    ge211::Random_source<int> power_up_prob;
    ge211::Random_source<int> mine_random;
    ge211::Random_source<int> mine_random_sign;
    ge211::Random_source<int> mine_appear;

public:
    //START OF CONFIG
    static int const player_radius = 25;
    static int const mine_radius = 40;
    const ge211::Dims<int> hook_dims;
    //END OF CONFIG

    Model();
    void on_frame();
    bool create_hook();
    Mine* get_mine(Hook* h) const {
        for(Mine* m : mines) {
            if(m->get_hook() == h) {
                return m;
            }
        }
        return nullptr;
    };
    void is_dead(ge211::geometry::Posn<double> c);
    bool is_killed_by_screen(ge211::Posn<double> player_coordinates);
    bool is_killed_by_mine(ge211::Posn<double> player_coordinates);
    int get_proportion_to_score();
    void set_score(int n) {
        score = n;
    }
    std::vector<Hook*> hooks;
    std::vector<Mine*> mines;
    bool game_done;
    Player _player;
    int score;
};
