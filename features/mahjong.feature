Feature: Mahjong Game

Background:
    Given I have joined a game

Scenario: Starting a game hosted by player
    When I start a game
    Then I should see that I've got my hand of tiles
    Then I have nothing picked
    When I pick
    Then I've got one tile picked

#@wip
#Scenario: Testability for player
#    Given I start a game
#    And the next tile to be picked is "🀡"
#    When I pick
#    Then I should see my new pick is "🀡"
#
#@wip
#Scenario: Testability for opponent
#    Given I start a game
#    And I pick
#    And the next tile to be picked is "🀡"
#    When I discard my new pick
#    Then I should see my opponent picks up tile "🀡"

#@wip
#Scenario Outline: Melding prompt
#    Given my hand is "🀙🀙🀚🀛"
#    And my opponent's hand is "🀑🀔🀗🀘"
#    And it's my opponent's turn
#    And the next tile in the queue is "<next tile>"
#    When I start the game
#    Then I should see my opponent discard the "<next tile>"
#    And I should see that I can do only these "<actions>"

#    Examples:
#    | next tile | actions         |
#    | 🀡         |                 |
#    | 🀙         | Peng Chow Win   |
#    | 🀜         | Chow Win        |
#    | 🀚         | Chow            |