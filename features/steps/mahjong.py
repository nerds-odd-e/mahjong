from behave import *
import requests


def get_request(context, uri):
    r = requests.get(url = "http://localhost:8889/" + uri) 
    return r.json()

def game_get_request(context, cmd):
    return get_request(context, str(context.scenario.game_id)+ "/" + cmd) 

def read_tiles(tiles):
    map = {
        "🀙": 65,
        "🀚": 66,
        "🀛": 67,
        "🀡": 73,
        "🀑": 98,
        "🀔": 101,
        "🀗": 104,
        "🀘": 105
    }
    return [map[t] for t in tiles]

@given(u'I have joined a game')
def step_impl(context):
    context.scenario.game_id = get_request(context, 'join')['game_id']
    

@when(u'I start a game')
def step_impl(context):
    game_get_request(context, "start") 


@then(u'I should see that I\'ve got my hand of tiles')
def step_impl(context):
    p = game_get_request(context, "current") 
    assert p[0]['player_index'] == 0
    assert len(p[0]['hand']) == 13