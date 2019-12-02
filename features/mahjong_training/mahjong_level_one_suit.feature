Feature: Mahjong Game level one suit

Background: Joining a game as a level 1 player
    Given I have joined a game
    And I am level "1" player
    

Scenario Outline: In multiple games suits should be cycled
    When I am in round "<round>"
    Then I must be level "1" player
    And I must see all my tiles are "<suit>"

    Examples:
        | round | suit      |
        | 1     | circle    |
        | 2     | bamboo    |
        | 3     | character |


    