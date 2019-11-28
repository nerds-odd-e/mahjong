Feature: Mahjong Game Level Two

    Background:
        Given I have joined a game
        And I am level "2" player
        And I start a game

    Scenario: Beginning of level two
        Then My number of wins should be 0
        When I play an immediately win game
        Then My number of wins should be 1

# Scenario Outline: Checking the progress of level two
#     Given My number of wins is "<current wins>"
#     When Outcome of the game is "<result>"
#     Then My number of wins is "<new wins>"
#     Examples:
#         | current wins | result | new wins |
#         | 2            | win    | 3        |
#         | 2            | lose   | 2        |
