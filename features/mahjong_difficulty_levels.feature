Feature: Mahjong Game - difficulty levels
    To train a beginer Mahjong player, the game need to
    have some difficulty levels and user can go up the levels
    as they improve.

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

    Scenario Outline: level progression
        And I am level "<level>" player
        When I won <win_count> times 
        Then I must be level "<next_level>" player
        Examples:
            | level | win_count | next_level |
            | 0     | 1         | 1          |
            | 1     | 3         | 2          |
            | 2     | 5         | 3          |
            | 3     | 5         | 4          |
            | 4     | 4         | 5          |

    Scenario Outline: In multiple games suits should be cycled
        Given I am level "1" player
        When I am in round "<round>"
        Then I must be level "1" player
        And I must see all my tiles are "<suit>"

        Examples:
            | round | suit      |
            | 1     | circle    |
            | 2     | bamboo    |
            | 3     | character |


    