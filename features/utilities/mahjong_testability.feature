Feature: Mahjong Game Testability

    Background:
        Given I have joined a game
        And I am level "1" player
        And I start a new round

    Scenario: Starting a game hosted by player
        Then I should see that all players have 4 tiles
        And I have nothing picked
        When I pick
        Then I've got one tile picked

    Scenario: Testability for player
        Given the next tile to be picked is "🀡"
        When I pick
        Then I should see my new pick is "🀡"

    Scenario: Testability for opponent
        Given I pick
        And the next tile to be picked is "🀡"
        When I discard my new pick
