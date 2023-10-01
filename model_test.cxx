#include "model.hxx"
#include <catch.hxx>

TEST_CASE("Player move to hook test - +x, +y")
{
    Player test_player = Player({100, 100}, 1);
    Hook test_hook = Hook({110, 120}, 1, {20, 40}, 0);

    test_player.move_to_hook(test_hook);
    for(int i = 0; i < 40; i++) {
        test_player.on_frame();
    }

    CHECK(!test_hook.is_visible());
    CHECK(test_player.get_score() == 1);


}

TEST_CASE("Player move to hook test - +x, -y")
{
    Player test_player = Player({100, 100}, 1);
    Hook test_hook = Hook({110, 90}, 1,  {20, 40}, 0);

    test_player.move_to_hook(test_hook);
    for(int i = 0; i < 20; i++) {
        test_player.on_frame();
    }

    CHECK(test_player._coordinates == test_hook._coordinates);
}

TEST_CASE("Player move to hook test - -x, -y")
{
    Player test_player = Player({100, 100}, 1);
    Hook test_hook = Hook({90, 90}, 1,  {20, 40}, 0);

    test_player.move_to_hook(test_hook);
    for(int i = 0; i < 20; i++) {
        test_player.on_frame();
    }

    CHECK(test_player._coordinates == test_hook._coordinates);}

TEST_CASE("Player move to hook test - -x, +y")
{
    Player test_player = Player({100, 100}, 1);
    Hook test_hook = Hook({90, 110}, 1,  {20, 40}, 0);

    test_player.move_to_hook(test_hook);
    for(int i = 0; i < 20; i++) {
        test_player.on_frame();
    }

    CHECK(test_player._coordinates == test_hook._coordinates);
}

//START OF "FAVORITE" MODEL TESTS

TEST_CASE("1 - Moving to hook behavior") {
    Player test_player = Player({100, 100}, 1);
    Hook test_hook = Hook({90, 110}, 1,  {20, 40}, 0);

    test_player.move_to_hook(test_hook);
    for(int i = 0; i < 10; i++) {
        test_player.on_frame();
    }

    CHECK(test_player._coordinates == test_hook._coordinates);  // coords match
    CHECK(!test_hook.is_visible());  // hook disappears
    CHECK(!(test_player._velocity_unit_vector.width == 0));
    CHECK(!(test_player._velocity_unit_vector.height == 0));
    CHECK(test_player.get_score() == 1);
    CHECK(test_player.get_hook() == nullptr);  // player doesn't own a hook
}

TEST_CASE("2 - Check a corner death case") {
    Model model;
    Player test_player = Player({768, 576}, 1);
    model._player = test_player;

    CHECK(model.is_killed_by_screen(test_player._coordinates));

    model._player.increment_lives();
    model.is_dead(model._player._coordinates);
    CHECK(model._player.get_lives() == 1);
}

TEST_CASE("3 - Check a mine death case") {
    Model model;

    Player test_player = Player({100, 100}, 1);
    Hook* test_hook = new Hook({90, 110}, 1,  {20, 40}, 0);
    Mine* test_mine = new Mine(test_hook);
    test_mine->set_visible(true);

    model.hooks.push_back(test_hook);
    model.mines.push_back(test_mine);

    CHECK(model.is_killed_by_mine(test_player._coordinates));

    model._player.increment_lives();
    model.is_dead(model._player._coordinates);
    CHECK(model._player.get_lives() == 1);
}

TEST_CASE("4 - Check power-ups") {
    Player test_player = Player({100, 100}, 1);
    Hook test_hook_multiplier = Hook({90, 110}, 1,  {20, 40}, 1);
    Hook test_hook_extra_life = Hook({100, 100}, 1,  {20, 40}, 2);

    test_player.move_to_hook(test_hook_multiplier);
    for(int i = 0; i < 10; i++) {
        test_player.on_frame();
    }

    CHECK(test_player.get_score() == 2);

    test_player.move_to_hook(test_hook_extra_life);
    for(int i = 0; i < 10; i++) {
        test_player.on_frame();
    }

    CHECK(test_player.get_lives() == 2);
}

TEST_CASE("5- Mines increase proportionally to score") {
    Model model;

    CHECK(model.get_proportion_to_score() == 11);

    model.set_score(2);
    CHECK(model.get_proportion_to_score() == 10); // lower proportion to score makes mine appearing more likely


}
