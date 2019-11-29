import requests

def get_request(context, uri):
    return MJDriver(context).get_request(uri)

def game_get_request(context, cmd):
    return MJDriver(context).game_get_request(cmd)

tile_map = {
    "🀙": 65,
    "🀚": 66,
    "🀛": 67,
    "🀜": 68,
    "🀡": 73,
    "🀆": 48,
    "🀇": 49,
    "🀏": 57,
    "🀐": 97,
    "🀑": 98,
    "🀔": 101,
    "🀗": 104,
    "🀘": 105
}

tile_id_map = {v: k for k, v in tile_map.items()}

def to_tile_id(tile):
    return tile_map[tile]

def id_to_tile(tile_id):
    return tile_id_map[tile_id]

class MJDriver:
    def __init__(self, context):
        self.context_ = context

    def get_request(self, uri):
        r = requests.get(url = "http://localhost:8889/" + uri)
        return r.json()

    def game_get_request(self, cmd):
        return self.get_request(str(self._game_id())+ "/" + cmd) 

    def get_current_status(self):
        return self.game_get_request("current")

    def get_next_event(self):
        return self.game_get_request("next_event")

    def testability_set_next_pick(self, tile):
        self.game_get_request("testability_set_next_pick?"+str(to_tile_id(tile)))

    def player_0_pick(self):
        self.game_get_request("pick")

    def get_current_pick_of_player(self, index):
        result = self.get_current_status()
        return id_to_tile(result['players'][index]['new_pick'])

    def replace_player_0_hand_with(self, replace_tiles):
        tiles = replace_tiles.split(",")
        request_tiles = ",".join(str(to_tile_id(tile)) for tile in tiles)
        game_get_request(self.context_, "testability_set_hand?" + request_tiles)

    def _game_id(self):
        return self.context_.scenario.game_id
