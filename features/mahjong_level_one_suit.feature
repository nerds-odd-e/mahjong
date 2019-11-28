Feature: Mahjong Game level one suit

Background: Joining a game as a level 1 player
    Given I have joined a game
    And I am level "1" player
    

Scenario: Starting a game hosted by player
    When I start a game
    Then All of my tiles should be of the same type

@wip
Scenario Outline: In multiple games suits should be cycled
    When I am in round <round>
    Then I must see all my tiles are <suit>

    Examples:
        | round | suit   |
        | 1     | circle |
        | 2     | bamboo |
        | 3     | character |
        | 4     | circle |


    