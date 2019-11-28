from behave import *
import requests


def get_request(context, uri):
    r = requests.get(url = "http://localhost:8889/" + uri)
    return r.json()

def game_get_request(context, cmd):
    return get_request(context, str(context.scenario.game_id)+ "/" + cmd) 

def get_my_current_pick(context):
    p = game_get_request(context, "current") 
    return p['players'][0]['new_pick']

def to_tile_id(tile):
    map = {
        "🀙": 65,
        "🀚": 66,
        "🀛": 67,
        "🀡": 73,
        "🀆": 48,
        "🀏": 57,
        "🀐": 97,
        "🀑": 98,
        "🀔": 101,
        "🀗": 104,
        "🀘": 105
    }
    return map[tile]

def is_in_circles(tile):
    return tile in range(to_tile_id("🀙"), to_tile_id("🀡") + 1)

def is_in_characters(tile):
    return tile in range(to_tile_id("🀆"), to_tile_id("🀏") + 1)

def is_in_bamboo(tile):
    return tile in range(to_tile_id("🀐"), to_tile_id("🀘") + 1)


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

@given(u'I have joined a game')
def step_impl(context):
    context.scenario.game_id = get_request(context, 'join')['game_id']

@step(u'I start a game')
def step_impl(context):
    game_get_request(context, "start")

@step(u'I pick')
def step_impl(context):
    game_get_request(context, "pick")

@then(u'I should see that I have "{number_of_tiles}" tiles')
def step_impl(context, number_of_tiles):
    p = game_get_request(context, "current") 
    assert p['players'][0]['player_index'] == 0, f"Player Index is {p['players'][0]['player_index']}"
    assert str(len(p['players'][0]['hand'])) == number_of_tiles, f"number of tiles is {len(p['players'][0]['hand'])}"

@then(u'I should see that all players have "{number_of_tiles}" tiles')
def step_impl(context, number_of_tiles):
    players = game_get_request(context, "current")['players'] 
    for i, p in enumerate(players):
        assert len(p['hand']) == int(number_of_tiles), f"number of tiles for player {i} is {len(p['hand'])} not {number_of_tiles}"

@then(u'I\'ve got one tile picked')
def step_impl(context):
    p = game_get_request(context, "current") 
    assert p['players'][0]['new_pick'] != 0

@then(u'I have nothing picked')
def step_impl(context):
    p = game_get_request(context, "current")
    assert p['players'][0]['new_pick'] == 0

@step(u'the next tile to be picked is "{tile}"')
def step_impl(context, tile):
    game_get_request(context, "test_set_next_pick?" + str(to_tile_id(tile)))

@then(u'I should see my new pick is "{tile}"')
def step_impl(context, tile):
    expected = to_tile_id(tile)
    actual = get_my_current_pick(context)
    assert  actual == expected, f"expected '{expected}', but got '{actual}'"

@step(u'I discard my new pick')
def step_impl(context):
    tile = get_my_current_pick(context)
    game_get_request(context, f"throw?{tile}") 

@step(u'I should see my opponent picks up tile "{tile}"')
def step_impl(context, tile):
    event = game_get_request(context, "next_event")
    assert event["action"] == "pick"
    assert event["player"] == 1
    actual = event["tile"]
    expected = to_tile_id(tile)
    assert  actual == expected, f"expected '{expected}', but got '{actual}'"

@step(u'My number of wins is "{wins}"')
def step_impl(context, wins):
    raise NotImplementedError(u'STEP: When My number of wins is 2')

@when(u'Outcome of the game is "{result}"')
def step_impl(context, result):
    raise NotImplementedError(u'STEP: When Result of the game is win')
    
@given(u'I am level "{lvl}" player')
def step_impl(context, lvl):
    game_get_request(context, "set_level?" + str(lvl))

@then(u'I am level "{lvl}" player')
def step_impl(context, lvl):
    result = game_get_request(context, "get_level")
    assert str(result['current_level']) == lvl, f"Current level is {result['current_level']}"

@when(u'I win the game')
def step_impl(context):
    raise NotImplementedError(u'STEP: When I win the game')

@when(u'I start an immediately win game')
def step_impl(context):
    game_get_request(context, "start_immediately_win")

@when(u'I try to win')
def step_impl(context):
    result = game_get_request(context, "win")
    assert False, f"result_of_wins: {result}"

@step(u'My number of wins should be {expected_number_of_wins}')
def step_impl(context,expected_number_of_wins):
    result = game_get_request(context, "get_number_of_wins")
    assert str(expected_number_of_wins) == str(result["number_of_wins"]), f"expected_number_of_wins: {expected_number_of_wins} == number_of_wins {number_of_wins}"

@then(u'All of my tiles should be of the same type')
def step_impl(context):
    p = game_get_request(context, "current") 
    assert are_all_tiles_in_one_suit(p['players'][0]['hand']), f"Player's tiles are not of the same suit"
    assert are_all_tiles_in_one_suit(p['players'][1]['hand']), f"Opponent's tiles are not of the same suit"

@given(u'it\'s my opponent\'s turn and it picks "{tile}"')
def step_impl(context, tile):
    context.execute_steps(u'''
        When I pick
        And the next tile to be picked is "{tile}"
        And I discard my new pick
        '''.format(tile = tile))

@when(u'my opponent discards a tile')
def step_impl(context):
    pass

@then(u'the discarded tile is "{tile}"')
def step_impl(context, tile):
    result = game_get_request(context, "next_event")
    result = game_get_request(context, "next_event")

    assert str(result['action']) == 'discard'
    assert to_tile_id(tile) == result['tile'], f"expected: {to_tile_id(tile)} == actual tile {result['tile']}"