Feature: Mahjong Game - undo discard

Background:
    Given I have joined a game
    Given I am in level 3
@wip
Scenario Outline: Melding prompt
    Given I am playing level 3 game
    and I discard a "<tile>"
    When UNDO button is selected
    Then discarded "<tile>" is restored

    Examples:
    | Initial Hand | Restored Hand  |
    | 🀡🀙🀙🀙🀜🀜🀜🀚   | 🀡🀙🀙🀙🀜🀜🀜🀚  |