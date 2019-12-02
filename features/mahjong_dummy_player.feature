Feature: Mahjong Game - Dummy Player

Background:
    Given I have joined a game
    And I am level "0" player

Scenario: Dummy Player Discard Behaviour
  Given I start a game
  When my opponent picks a "🀛" after I pick and discard
  Then I should see that my opponent discarded the "🀛"
