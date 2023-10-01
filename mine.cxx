#include "mine.hxx"

Mine::Mine(Hook* h)
    : Hook(h->_coordinates, 0, h->_dims, 0) {
        _hookptr = h;
        set_visible(false);
    };

// applies a "budge" that's randomized in quadrant to mines
void Mine::initialize_coordinates(ge211::geometry::Posn<double> p) {
    int sign = 1;
    if(p.x < 0) {
        sign = -1;
    }
    _coordinates.x = p.x + _hookptr->_coordinates.x + (sign * _dims.width);
    if(p.y < 0) {
        sign = -1;
    }
    _coordinates.y = p.y + _hookptr->_coordinates.y + (sign * _dims.height);
};
