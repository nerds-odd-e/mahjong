from behave import *
import requests


def get_request(context, uri):
    r = requests.get(url = "http://localhost:8889" + uri) 
    return r.json()
    
def get_game_request(context, uri):
    r = requests.get(url = "http://localhost:8889" + uri) 
    return r.json()

@given(u'I have joined a game')
def step_impl(context):
    context.scenario.game_id = get_request(context, '/join')['game_id']
    

@when(u'I start a game')
def step_impl(context):
    p = requests.get(url = "http://localhost:8889/" + str(context.scenario.game_id)+ "/start") 


@then(u'I should see that I\'ve got my hand of tiles')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then I should see that I\'ve got my hand of tiles')


@then(u'I\'ve got one tile picked')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then I\'ve got one tile picked')