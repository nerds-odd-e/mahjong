Feature: Mahjong Game Level Two

    Background:
        Given I have joined a game
        And I am level "2" player
        And I start a game

    Scenario: Beginning of level two
        Then My number of wins should be 0
        When I play an immediately win game
        Then My number of wins should be 1
