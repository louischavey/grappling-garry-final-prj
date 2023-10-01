#include "hook.hxx"

// note that power_up = 0 means a normal hook, power_up = 1 means a hook that
// causes a multiplier, and power_up = 2 means a hook that gives an extra life
Hook::Hook(ge211::Posn<double> coordinates, int points, ge211::Dims<int>
        dims, int power_up)
        : _coordinates(coordinates.x, coordinates.y)
        {
            _points = points;
            _visible = true;
            _dims = dims;
            _power_up = power_up;
        }

// takes into account hook dims
bool Hook::overlap(ge211::Posn<double> pos)
{
    if((pos.x >= _coordinates.x - _dims.width/2 &&
       pos.x <= _coordinates.x + _dims.width/2) &&
       (pos.y >= _coordinates.y - _dims.height/2 &&
       pos.y <= _coordinates.y + _dims.height/2)) {
        return true;
    }
    return false;
}