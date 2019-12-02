Feature: Mahjong Lvl 0 pair wins

    Background:
        Given I have joined a game
        And I am level "0" player
        And I start a game

    Scenario: Win with only pair
        When I play an immediately win game
        Then I must be level "1" player
