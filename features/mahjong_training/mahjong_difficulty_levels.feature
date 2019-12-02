Feature: Mahjong Game - difficulty levels

    Background:
        Given I have joined a game

    Scenario Outline: difficulty levels
        Given I am level "<level>" player
        When I start a new round
        Then I should see that all players have <hand_size> tiles
        And I must be level "<level>" player
        And my opponent must be at <opponent_level> level
        Examples:
            | level | hand_size | opponent_level |
            | 0     | 1         | dummy player   |
            | 1     | 4         | dummy player   |
            | 2     | 4         | dummy player   |
            | 3     | 7         | dummy player   |
            | 4     | 13        | smart player   |
            | 5     | 13        | smart player   |
            | 6     | 13        | smart player   |


