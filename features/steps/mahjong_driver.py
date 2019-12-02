import requests

def get_request(uri):
    print("query:" + uri)
    r = requests.get(url = "http://localhost:8889/" + uri)
    print(r.json())
    return r.json()

def join_a_game_and_get_driver():
    return MJDriver(get_request('join')['game_id'])

tile_map = {
    None: (0, None),
    "🀙": (65, "circle"),
    "🀚": (66, "circle"),
    "🀛": (67, "circle"),
    "🀜": (68, "circle"),
	"🀝": (69, "circle"),
    "🀞": (70, "circle"),
    "🀟": (71, "circle"),
    "🀠": (72, "circle"),
    "🀡": (73, "circle"),
    "🀇": (49, "character"),
    "🀈": (50, "character"),
    "🀉": (51, "character"),
    "🀊": (52, "character"),
    "🀋": (53, "character"),
    "🀌": (54, "character"),
    "🀍": (55, "character"),
    "🀎": (56, "character"),
    "🀏": (57, "character"),
    "🀐": (97, "bamboo"),
    "🀑": (98, "bamboo"),
    "🀒": (99, "bamboo"),
    "🀓": (100, "bamboo"),
    "🀔": (101, "bamboo"),
    "🀕": (102, "bamboo"),
    "🀖": (103, "bamboo"),
    "🀗": (104, "bamboo"),
    "🀘": (105, "bamboo"),
    "🀀": (108, "dragon"),
    "🀁": (111, "dragon"),
    "🀂": (114, "dragon"),
    "🀃": (117, "dragon"),
    "🀄": (120, "dragon"),
    "🀅": (123, "dragon"),
    "🀆": (126, "dragon"),
}

tile_id_map = {v[0]: (k, v[1]) for k, v in tile_map.items()}

def to_tile_id(tile):
    return tile_map[tile][0]

def id_to_tile(tile_id):
    return tile_id_map[tile_id][0]

def tile_id_suit(tile_id):
    return tile_id_map[tile_id][1]

class MJDriver:
    def __init__(self, game_id):
        self._game_id = game_id

    def game_get_request(self, cmd):
        return get_request(str(self._game_id)+ "/" + cmd) 

    def start_a_round(self):
        self.game_get_request("start")

    def get_current_status(self):
        return self.game_get_request("current")

    def get_next_event(self):
        return self.game_get_request("next_event")

    def testability_set_next_pick(self, tile):
        self.game_get_request("testability_set_next_pick?"+str(to_tile_id(tile)))

    def player_0_pick(self):
        self.game_get_request("pick")

    def player_0_discard(self, tile):
        self.game_get_request(f"discard?{to_tile_id(tile)}") 

    def player_0_win(self):
        return self.game_get_request("win") 

    def get_current_pick_of_player(self, index):
        result = self.get_current_status()
        return id_to_tile(result['players'][index]['new_pick'])

    def replace_player_0_hand_with(self, replace_tiles):
        tiles = replace_tiles.split(",")
        request_tiles = ",".join(str(to_tile_id(tile)) for tile in tiles)
        self.game_get_request("testability_set_hand?" + request_tiles)

    def get_last_discard(self):
        last_discard = None
        while(True):
            event = self.get_next_event()
            if event["action"] == "your_turn":
                break
            if event["action"] == "discard":
                last_discard = event["tile"]
        if last_discard is None:
            return None
        return id_to_tile(last_discard)
        
    def pop_event_until_its_player_0_turn(self):
        self.get_last_discard()

    def set_level(self, level):
        self.game_get_request("set_level?" + str(level))

    def get_level(self):
        return self.game_get_request("get_level")['current_level']

    def get_suits_of_player_0_hand(self):
        tile_ids = self.get_current_status()["players"][0]["hand"]
        return set(tile_id_suit(tile_id) for tile_id in tile_ids)
