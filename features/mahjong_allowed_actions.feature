Feature: Mahjong Game - allowed actions

    Background:
        Given I have joined a game
        And I am level "1" player
        And I start a game

    Scenario Outline: Melding prompt test
        Given my hand is "🀙,🀙,🀚,🀛"
        When My opponent discards the "<next tile>"
        Then I should see that I can do only these "<actions>"

        Examples:
            | next tile | actions       |
            | 🀡      |               |
            | 🀙      | win pong chow |
            | 🀜      | win chow      |
            | 🀚      | chow          |