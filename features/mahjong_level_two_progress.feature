@wip
Feature: Mahjong Game Level Two

    Background:
        Given I have joined a game
        And I'm in level 2
        And I start a game

    Scenario Outline: Checking the progress of level two
        Given My number of wins is "<current wins>"
        When Outcome of the game is "<result>"
        Then My number of wins is "<new wins>"
        Examples:
            | current wins | result | new wins |
            | 2            | win    | 3        |
            | 2            | lose   | 2        |
