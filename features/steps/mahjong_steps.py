from behave import *
from mahjong_tester import join_a_game_to_test, assert_eq


def tile_types():
    map = {
        "circle": circles(),
        "character": characters(),
        "bamboo": bamboos()
    }
    return map

def circles():
    return range(to_tile_id("🀙"), to_tile_id("🀡") + 1)

def characters():
    return range(to_tile_id("🀇"), to_tile_id("🀏") + 1)

def bamboos():
    return range(to_tile_id("🀐"), to_tile_id("🀘") + 1)

def is_in_circles(tile):
    return tile in circles()

def is_in_characters(tile):
    return tile in characters()

def is_in_bamboo(tile):
    return tile in bamboos()

def are_all_tiles_in_one_suit(tiles):
    if is_in_circles(tiles[0]):
        for tile in tiles:
            if not is_in_circles(tile):
                return False        
    elif is_in_characters(tiles[0]):
        for tile in tiles:
            if not is_in_characters(tile):
                return False
    elif is_in_bamboo(tiles[0]):
        for tile in tiles:
            if not is_in_bamboo(tile):
                return False            
    return True

def try_win(context):
    game_get_request(context, "win")

def giving_the_same_tiles_to_users_hand(context,replace_tile):
    p = game_get_request(context, "current")
    tiles_in_hand = p['players'][0]['hand']

    for tile in tiles_in_hand:
        game_get_request(context, "testability_set_next_pick?" + str(to_tile_id(replace_tile)))
        game_get_request(context, "pick")
        game_get_request(context, f"throw?{tile}")

    p = game_get_request(context, "current")
    new_hand = p['players'][0]['hand']

    for tile in new_hand:
        assert  tile == to_tile_id(replace_tile), f"expected '{to_tile_id(replace_tile)}', but got '{tile}'"

global tester

@given(u'I have joined a game')
def step_impl(context):
    global tester
    tester = join_a_game_to_test()

@step(u'I start a game')
def step_impl(context):
    tester.driver_.start_a_game()

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
        game_get_request(context, "force_win")

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

@step(u'My number of wins is "{wins}"')
def step_impl(context, wins):
    raise NotImplementedError(u'STEP: When My number of wins is 2')

@when(u'Outcome of the game is "{result}"')
def step_impl(context, result):
    raise NotImplementedError(u'STEP: When Result of the game is win')
    
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

@step(u'My number of wins should be {expected_number_of_wins}')
def step_impl(context,expected_number_of_wins):
    number_of_wins = tester.driver_.get_number_of_wins()
    assert_eq(str(expected_number_of_wins),str(number_of_wins))

@then(u'All of my tiles should be of the same type')
def step_impl(context):
    p = game_get_request(context, "current") 
    assert are_all_tiles_in_one_suit(p['players'][0]['hand']), f"Player's tiles are not of the same suit"

@step(u'my opponent picks a "{tile}" after I pick and discard')
def step_impl(context, tile):
    tester.force_player_1_to_pick_after_player_0_pick_and_discard(tile)

@step(u'I am in round "{round}"')    
def step_impl(context, round):
    for _ in range(int(round)):
        game_get_request(context, "start")

@then(u'I must see all my tiles are "{suit}"')
def step_impl(context, suit):    
    p = game_get_request(context, "current") 
    for tile in  p['players'][0]['hand']:
        if tile not in tile_types()[suit]:
            assert False, "Not all tiles are " + suit

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