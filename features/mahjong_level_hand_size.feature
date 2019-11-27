Feature: Mahjong Game - hand size level dependent 

Background:
    Given I have joined a game

@wip
Scenario Outline: Given I have joined a game
    And I am level "<level>" player
    When I start a game
    Then my hand should be of size <hand_size>
    Examples:
    | level | hand_size |
    | 0     | 1         |
    | 1     | 4         |
    | 2     | 4         |
    | 3     | 7         |
    | 4     | 13        |
    | 5     | 13        |
    | 6     | 13        |


