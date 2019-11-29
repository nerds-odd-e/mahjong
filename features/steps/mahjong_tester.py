from mahjong_driver import MJDriver, get_request, game_get_request, to_tile_id

def assert_eq(expected, actual):
    assert expected == actual, f"expected: {expected}, actual: {actual}"
    
class MJTester:
    def __init__(self, context):
        self.context_ = context
        self.driver_ = MJDriver(context)

    def player_0_immediately_win(self):
        result = self.driver_.get_current_status()
        hand_size = len(result['players'][0]['hand'])
        new_hand = ','.join("🀙" * hand_size)
        self.replace_player_0_hand_with(new_hand)
        self.player_0_force_pick_a("🀙")
        result = game_get_request(self.context_,"win")

    def player_0_force_pick_a(self, tile):
        self.driver_.testability_set_next_pick(tile)
        self.player_0_pick()
        result = self.driver_.get_current_pick_of_player(0)
        assert_eq(tile, result)

    def player_0_pick(self):
        assert_eq("your_turn", self.driver_.get_next_event()["action"])
        self.driver_.player_0_pick()

    def replace_player_0_hand_with(self, replace_tiles):
        self.driver_.replace_player_0_hand_with(replace_tiles)