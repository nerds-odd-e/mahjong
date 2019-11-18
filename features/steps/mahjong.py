from behave import *
import requests


def get_request(context, uri):
    r = requests.get(url = "http://localhost:8889/" + uri) 
    return r.json()

def game_get_request(context, cmd):
    return get_request(context, str(context.scenario.game_id)+ "/" + cmd) 


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


@then(u'I\'ve got one tile picked')
def step_impl(context):
    p = game_get_request(context, "current") 
    assert p[0]['new_pick'] != 0
    assert p[1]['new_pick'] == 0