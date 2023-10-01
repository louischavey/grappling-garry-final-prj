#include <ge211.hxx>
#include "model.hxx"
#include "player.cxx"

Model::Model()
    :
      screen_dims(768, 576),
      hook_timer(),
      random_x_coord_(0, screen_dims.width),
      random_y_coord_lower(0, screen_dims.height/2),
      random_y_coord_higher(screen_dims.height/2, screen_dims.height),
      y_lower_higher(0, 1),
      power_up_prob(0, 100),
      mine_random(0, 5),
      mine_random_sign(0, 2),
      mine_appear(0, 10),
      hook_dims(20, 40),
      _player({double(screen_dims.width/2)-100,0}, 60.0)
{
    game_done = false;
    score = _player.get_score();

}

// Called every frame: Updates the player's attributes (including the death
// cases) and draws hooks every 2 seconds
void Model::on_frame() {
    score = _player.get_score();
    _player.on_frame();
    is_dead(_player._coordinates);
    hook_seconds = hook_timer.elapsed_time().seconds();
    if(hook_seconds > 2) {
        hook_timer.reset();
        while(!create_hook());
    }
}

// Puts down a hook of normal or different power up types at a random
// position and a mine that is budged and made visible at random
bool Model::create_hook()
{
    ge211::Posn<double> p1 {0.0, 0.0};

    //randomly determine the position of our hook
    if (y_lower_higher.next()) {
        p1 = {(double) random_x_coord_.next(),
              (double) random_y_coord_higher.next()};
    }
    else {
        p1 = {(double) random_x_coord_.next(),
              (double) random_y_coord_lower.next()};
    }

    //make sure we're not creating hooks on top of each other
    for (Hook *h: hooks) {
        if (h->overlap(p1)) {
            return false;
        }
    }

    //if number is within a range, call multiplier power-up hook creator
    //if other random # is w/in a range, call extra life power-up hook creator
    Hook *h = new Hook(p1, 1, hook_dims, 0);
    Mine *m = new Mine(h);

    if(power_up_prob.next() % 5 == 0) {
        h->set_multiplier_power_up();
    }
    else if(power_up_prob.next() % 10 == 0) {
        h->set_extra_life_power_up();
    }

    hooks.push_back(h);
    mines.push_back(m);

    double x = mine_random.next();
    double y = mine_random.next();

    if (mine_random_sign.next()) {
        x *= -1;
    }
    if (mine_random_sign.next()) {
        y *= -1;
    }
    m->initialize_coordinates({x, y});

    if (mine_appear.next_between(0, get_proportion_to_score()) == 0) {
        m->set_visible(true);
    }
    return true;
}

// checks the two player dead cases
void Model::is_dead(ge211::geometry::Posn<double> c) {
    if(is_killed_by_screen(c) || is_killed_by_mine(c)) {
        _player.lose_life();
        _player.reset_hook();
        if(_player.get_lives() == 0) {
            exit(0);
        }
        _player._coordinates = {double(screen_dims.width / 2), 0};
        _player._velocity_unit_vector = {0, 0};
    }
}

// one of two player death cases where it touches screen
bool Model::is_killed_by_screen(ge211::Posn<double> player_coordinates) {
        if(player_coordinates.y + player_radius > screen_dims.height ||
           player_coordinates.y < 0 ||
           player_coordinates.x + player_radius > screen_dims.width ||
           player_coordinates.x < 0) {
                return true;
        }
        return false;
};

//other player death case where it touches a mine
bool Model::is_killed_by_mine(ge211::Posn<double> player_coordinates) {
    for(Mine* m : mines) {
        if(m->is_visible() && m->overlap(player_coordinates)) {
            return true;
        }
    }
    return false;
}

// upper limit of the random number generator for the mines appearing;
// as score increases, the probability of mines appearing will increase
int Model::get_proportion_to_score()
{
    if(score <= 20) {
        return 11 - score/2;
    }
    return 1;
}






