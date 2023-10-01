#pragma once
#include <ge211.hxx>
#include "hook.hxx"

class Player {
public:
    Player(ge211::Posn<double> coordinates, double frameRate);
    void move_to_hook(Hook& hook);
    void on_frame();
    bool is_moving();
    int get_lives() {
        return _lives;
    }
    void lose_life() {
        _lives--;
    };
    int get_score()
    {
        return score;
    }
    void increment_score()
    {
        if(_hook != nullptr) {
            score += _hook->get_points() * _multiplier;
        }
    }
    void reset_hook();
    void multiplier_power_up();
    Hook* get_hook() {
        return _hook;
    }
    void increment_lives() {
        _lives++;
    }
    ge211::Posn<double> _coordinates;
    ge211::Dims<double> _velocity_unit_vector;

private:
    int _lives;
    Hook* _hook; //keep track of which hook player is moving to
    double _frameRate;
    long _move_frame_count;
    long _move_frame_rate;
    int score;
    int _multiplier;
    ge211::Timer multiplier_timer;
    double multiplier_seconds;
};
