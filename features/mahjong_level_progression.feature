Feature: Mahjong Game - level progression

    Background:
        Given I have joined a game
    @wip
    Scenario Outline: level progression
        And I am level "<level>" player
        When I won <win_count> times 
        Then I must be level "<next_level>" player
        Examples:
            | level | win_count | next_level |
            | 0     | 1         | 1          |
            | 1     | 5         | 2          |
