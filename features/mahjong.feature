Feature: Mahjong Game

Scenario: Starting a game hosted by player
    Given I have joined a game
    When I start a game
    Then I should see that I've got my hand of tiles
    And I've got one tile picked
