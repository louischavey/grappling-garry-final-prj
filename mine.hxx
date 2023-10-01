#pragma once
#include <ge211.hxx>
#include "hook.hxx"

class Mine : public Hook {
public:
    Mine(Hook* h);
    void initialize_coordinates(ge211::geometry::Posn<double> p);
    Hook* get_hook() {
        return _hookptr;
    };
    ge211::geometry::Posn<double> get_coords() {
        return _coordinates;
    };

private:
    Hook* _hookptr;
};