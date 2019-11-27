Feature: Mahjong Game - Dummy Player

Background:
    Given I have joined a game
    And I am level "0" player

Scenario: Dummy Player Discard Behaviour
  Given I start a game
  And it's my opponent's turn and it picks "🀛"
  When my opponent discards a tile
  Then the discarded tile is "🀛"
