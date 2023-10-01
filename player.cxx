#include <ge211.hxx>
#include "player.hxx"

Player::Player(ge211::Posn<double> coordinates, double frameRate)
    : _coordinates(coordinates.x, coordinates.y),
      _velocity_unit_vector(),
      multiplier_timer()
    {

    _lives = 1;
    _hook = nullptr;
    _frameRate = frameRate;
    _move_frame_count = 0;
    _move_frame_rate = 2;
    score = 0;
    _multiplier = 1;

}

// initiates the move to hook
void Player::move_to_hook(Hook& hook)
{
    double max;
    _velocity_unit_vector = {(double)hook._coordinates.x - (double)
                             _coordinates.x,
                             (double)hook._coordinates.y - (double)
                             _coordinates.y};

    //helps us find a "slope" to add to play position
    max = std::max(std::fabs(_velocity_unit_vector.width),
                     std::fabs(_velocity_unit_vector.height));

    _velocity_unit_vector.width /= max;
    _velocity_unit_vector.height /= max;
    _hook = &hook;
    _hook->attach_player(this);
    _move_frame_count = 0;

}

//updates position and handles any hook hitting behavior
void Player::on_frame() {
    if(_hook != nullptr) {
        if(_hook->overlap(_coordinates)) {
            //call hook function that sets it to not visible and removes it
            // from hook list
            multiplier_power_up();
            if(_hook->_power_up == 2) {
                increment_lives();
            }
            increment_score();
            _hook->set_visible(false);
            _hook->detach_player(this);
            _hook = nullptr;
        }
    }
    //move the player towards the hook (move the position of the player
    //towards the hook) every __ frames
    if(_move_frame_count++ % _move_frame_rate == 0) {
        _coordinates.y += 2 *_velocity_unit_vector.height;
        _coordinates.x += 2 * _velocity_unit_vector.width;
    }
}

// getter for if player is attached to a hook
bool Player::is_moving() {
    if(_hook != nullptr) {
        return true;
    }
    return false;
}

// get rid of hook attachment
void Player::reset_hook()
{
    if(_hook != nullptr) {
        _hook->detach_player(this);
        _hook = nullptr;
    }
}

// checks to see if the attached hook creates a multiplier or gives an extra
// life
void Player::multiplier_power_up() {
    if(_hook->_power_up == 1) {
        _multiplier = 2;
        multiplier_timer.reset();
    }
    if(multiplier_timer.elapsed_time().seconds() > 5) {
        _multiplier = 1;
    }
};
