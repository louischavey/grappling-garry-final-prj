#pragma once
#include <ge211.hxx>

class Hook {
public:
    Hook(ge211::Posn<double> coordinates, int points, ge211::Dims<int> dims, int power_up);
    void attach_player(class Player* ptr) {
        _player = ptr;
    }
    void detach_player(class Player* ptr) {
        if(ptr == _player) {
            _player = nullptr;
        }
    }
    void set_visible(bool b) {
        _visible = b;
    }
    bool is_visible() {
        return _visible;
    }
    void set_multiplier_power_up() {
        _power_up = 1;
    }
    void set_extra_life_power_up()
    {
        _power_up = 2;
    }
    bool overlap(ge211::Posn<double> pos);
    int get_points()
    {
        return _points;
    }
    ge211::Posn<double> _coordinates;
    ge211::Dims<int> _dims;
    int _power_up;

private:
    int _points;
    bool _visible;
    class Player* _player;
};