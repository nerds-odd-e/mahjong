Feature: Mahjong Game - allowed actions

    Background:
        Given I have joined a game
        And I am level "1" player
        And I start a new round

    Scenario Outline: Melding prompt test
        Given my hand is "🀙,🀙,🀚,🀛"
        When my opponent picks a "<next tile>" after I pick and discard
        Then I should see that my opponent discarded the "<next tile>"
        And I should see that I can do only these "<actions>"

        Examples:
            | next tile | actions       |
            | 🀡        |               |
            | 🀙        | win pong chow |
            | 🀜        | win chow      |
            | 🀚        | chow          |