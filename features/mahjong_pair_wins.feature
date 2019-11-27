Feature: Mahjong Lvl 0 pair wins

    Background:
        Given I have joined a game
        And I start a game
        And I am level "0" player

    @wip
    Scenario:
        Then I have "1" tile in hand

    @wip
    Scenario:
        Given I won
        Then I am level "1" player
