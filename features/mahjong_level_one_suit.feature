Feature: Mahjong Game level one suit

Scenario: Starting a game hosted by player
    Given I have joined a game
    And I am level "1" player
    When I start a game
    Then All of my tiles should be of the same type

@wip
Scenario: Playing multiple games
    Given I have joined game
    And I am level "1" player
    When I start a game "3" times, keeping count of suits 
    Then I must see "3" different suits