from behave import *
from mahjong_tester import join_a_game_to_test, assert_eq


global tester

@given(u'I have joined a game')
def step_impl(context):
    global tester
    tester = join_a_game_to_test()

@step(u'I start a new round')
def step_impl(context):
    tester.driver_.start_a_round()

@step(u'I pick')
def step_impl(context):
    tester.driver_.player_0_pick()

@then(u'I should see that all players have {number_of_tiles} tiles')
def step_impl(context, number_of_tiles):
    players = tester.driver_.get_current_status()["players"]
    assert_eq(int(number_of_tiles), len(players[0]['hand']))
    assert_eq(int(number_of_tiles), len(players[1]['hand']))

@then(u'I\'ve got one tile picked')
def step_impl(context):
    actual = tester.driver_.get_current_pick_of_player(0)
    assert actual != None

@then(u'I have nothing picked')
def step_impl(context):
    actual = tester.driver_.get_current_pick_of_player(0)
    assert_eq(None, actual)

@when(u'I won {win_count} times')
def step_impl(context, win_count):
    for _ in range(int(win_count)):
        tester.driver_.start_a_round()
        tester.player_0_immediately_win()

@step(u'the next tile to be picked is "{tile}"')
def step_impl(context, tile):
    tester.driver_.testability_set_next_pick(tile)

@then(u'I should see my new pick is "{tile}"')
def step_impl(context, tile):
    actual = tester.driver_.get_current_pick_of_player(0)
    assert_eq(tile, actual)

@step(u'I discard my new pick')
def step_impl(context):
    tester.player_0_discard_new_pick()

@given(u'I am level "{lvl}" player')
def step_impl(context, lvl):
    tester.driver_.set_level(lvl)

@then(u'I must be level "{lvl}" player')
def step_impl(context, lvl):
    result = tester.driver_.get_level()
    assert_eq(lvl, str(result))

@when(u'I play an immediately win game')
def step_impl(context):
    tester.player_0_immediately_win()

@step(u'my opponent picks a "{tile}" after I pick and discard')
def step_impl(context, tile):
    tester.force_player_1_to_pick_after_player_0_pick_and_discard(tile)

@step(u'I am in round "{round}"')    
def step_impl(context, round):
    for _ in range(int(round) - 1):
        tester.driver_.start_a_round()
        tester.player_0_immediately_win()
    tester.driver_.start_a_round()

@then(u'I must see all my tiles are "{suit}"')
def step_impl(context, suit):    
    suits = tester.driver_.get_suits_of_player_0_hand()
    assert_eq(set([suit]), suits)

@given(u'my hand is "{replace_tiles}"')
def step_impl(context, replace_tiles):
    tester.replace_player_0_hand_with(replace_tiles)

@then(u'I should see that my opponent discarded the "{tile}"')
def step_impl(context, tile):
    assert_eq(tile, tester.driver_.get_last_discard())

@then(u'I should see that I can do only these "{possible_actions}"')
def step_impl(context, possible_actions):
    allowed_actions = tester.get_allowed_actions()
    expected_actions = possible_actions.split(" ")
    assert_eq(expected_actions, allowed_actions)

@then(u'I should see that I can do only these ""')
def step_impl(context):
    allowed_actions = tester.get_allowed_actions()
    assert_eq([], allowed_actions)

@then(u'my opponent must be at dummy player level')
def step_impl(context):
    for tile in "🀝🀋🀔🀀":
        tester.force_player_1_to_pick_after_player_0_pick_and_discard(tile)
        assert_eq(tile, tester.driver_.get_last_discard())

@then(u'my opponent must be at smart player level')
def step_impl(context):
    for tile in "🀝🀋🀔🀀":
        tester.force_player_1_to_pick_after_player_0_pick_and_discard(tile)
        if tile != tester.driver_.get_last_discard():
            return
    assert False, "The opponent always discard what it picked. It's not a smart player"