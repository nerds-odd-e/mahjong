from behave import *
import requests

@when(u'I start a game')
def step_impl(context):
    requests.get(url = "http://localhost:8889/game") 


@then(u'I should see that I\'ve got my hand of tiles')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then I should see that I\'ve got my hand of tiles')


@then(u'I\'ve got one tile picked')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then I\'ve got one tile picked')