import requests

def get_request(uri):
    r = requests.get(url = "http://localhost:8889/" + uri)
    return r.json()

def join_a_game_and_get_driver():
    return MJDriver(get_request('join')['game_id'])

tile_map = {
    None: 0,
    "🀙": 65,
    "🀚": 66,
    "🀛": 67,
    "🀜": 68,
	"🀝": 69,
    "🀞": 70,
    "🀟": 71,
    "🀠": 72,
    "🀡": 73,
    "🀇": 49,
    "🀈": 50,
    "🀉": 51,
    "🀊": 52,
    "🀋": 53,
    "🀌": 54,
    "🀍": 55,
    "🀎": 56,
    "🀏": 57,
    "🀐": 97,
    "🀑": 98,
    "🀒": 99,
    "🀓": 100,
    "🀔": 101,
    "🀕": 102,
    "🀖": 103,
    "🀗": 104,
    "🀘": 105,
    "🀀": 108,
    "🀁": 111,
    "🀂": 114,
    "🀃": 117,
    "🀄": 120,
    "🀅": 123,
    "🀆": 126,
}

tile_id_map = {v: k for k, v in tile_map.items()}

def to_tile_id(tile):
    return tile_map[tile]

def id_to_tile(tile_id):
    return tile_id_map[tile_id]

class MJDriver:
    def __init__(self, game_id):
        self._game_id = game_id

    def game_get_request(self, cmd):
        p = get_request(str(self._game_id)+ "/" + cmd) 
        print(cmd)
        print(p)
        return p

    def start_a_game(self):
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
        self.game_get_request(f"throw?{to_tile_id(tile)}") 

    def player_0_win(self):
        self.game_get_request("win") 

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
        return id_to_tile(last_discard)
        
    def set_level(self, level):
        self.game_get_request("set_level?" + str(level))

    def get_level(self):
        return self.game_get_request("get_level")['current_level']

    def get_number_of_wins(self):
        result = self.game_get_request("get_number_of_wins")
        return result["number_of_wins"]