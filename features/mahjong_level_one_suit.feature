Feature: Mahjong Game level one suit

Scenario: Starting a game hosted by player
    Given I have joined a game
    And I am level "1" player
    When I start a game
    Then All of my tiles should be of the same type

@wip
Scenario: Starting a game hosted by player with 4 tiles
    Given I have joined a game
    And I am level "1" player
    When I start a game
    Then my hand should be of size 4
