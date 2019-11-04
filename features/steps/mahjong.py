from behave import *
import requests


@given(u'I have joined a game')
def step_impl(context):
    p = requests.get(url = "http://localhost:8889/join") 
    context.scenario.game_id = p.json()['game_id']
    

@when(u'I start a game')
def step_impl(context):
    print(context.scenario.game_id)


@then(u'I should see that I\'ve got my hand of tiles')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then I should see that I\'ve got my hand of tiles')


@then(u'I\'ve got one tile picked')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then I\'ve got one tile picked')