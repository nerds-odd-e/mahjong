Feature: Mahjong Lvl 0 pair wins

Background:
    Given I am level "0" player
    And I have joined a game
    Given I start a game

@wip
Scenario:
    Then I have "1" tile in hand

@wip
Scenario:
    Given I won
    Then I am level "1" player
