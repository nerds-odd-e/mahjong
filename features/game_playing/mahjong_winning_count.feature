Feature: Mahjong Game - level 4 progress

    Background:
        Given I have joined a game
        And I am level "4" player
        And I start a game

    Scenario: Beginning of level four
        Then My number of wins should be 0
        When I play an immediately win game
        Then My number of wins should be 1