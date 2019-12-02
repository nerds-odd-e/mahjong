from mahjong_driver import join_a_game_and_get_driver

def assert_eq(expected, actual):
    assert expected == actual, f"expected: {expected}, actual: {actual}"
    
def join_a_game_to_test():
    return MJTester(join_a_game_and_get_driver())

class MJTester:
    def __init__(self, game_driver):
        self.driver_ = game_driver

    def player_0_immediately_win(self):
        result = self.driver_.get_current_status()
        hand_size = len(result['players'][0]['hand'])
        new_hand = ','.join("🀙" * hand_size)
        self.replace_player_0_hand_with(new_hand)
        self.force_player_0_to_pick_a("🀙")
        result = self.driver_.player_0_win()

    def force_player_0_to_pick_a(self, tile):
        self.driver_.testability_set_next_pick(tile)
        self.player_0_pick()
        result = self.driver_.get_current_pick_of_player(0)
        assert_eq(tile, result)

    def force_player_1_to_pick_after_player_0_pick_and_discard(self, tile):
        self.driver_.player_0_pick()
        self.driver_.testability_set_next_pick(tile)
        self.player_0_discard_new_pick()

    def player_0_pick(self):
        assert_eq("your_turn", self.driver_.get_next_event()["action"])
        self.driver_.player_0_pick()

    def player_0_discard_new_pick(self):
        tile = self.driver_.get_current_pick_of_player(0)
        self.driver_.player_0_discard(tile)

    def replace_player_0_hand_with(self, replace_tiles):
        self.driver_.replace_player_0_hand_with(replace_tiles)

    def get_allowed_actions(self):
        return self.driver_.get_current_status()["allowed_actions"]
