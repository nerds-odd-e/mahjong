Feature: Mahjong Lvl 0 pair wins

    Background:
        Given I have joined a game
        And I am level "0" player
        And I start a game

    Scenario:
        Then I should see that I have "1" tiles

    @wip
    Scenario:
        Given I won
        Then I am level "1" player
