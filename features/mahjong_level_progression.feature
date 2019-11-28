Feature: Mahjong Game - level progression

    Background:
        Given I have joined a game

    Scenario Outline: level progression
        And I am level "<level>" player
        When I won <win_count> times 
        Then I must be level "<next_level>" player
        Examples:
            | level | win_count | next_level |
            | 1     | 3         | 2          |
            | 2     | 5         | 3          |
            | 3     | 5         | 4          |
            | 4     | 4         | 5          |
#            | 0     | 1         | 1          |


