Feature: Mahjong Game

Scenario: Starting a game hosted by player
    When I start a game
    Then I should see that I've got my hand of tiles
    And I've got one tile picked
    