mahjong
===========

The C plus plus version of the mahjong game. Mahjong is a Chinese game.

#How to build

First, get the unit testing frame work https://github.com/cpputest/cpputest installed.

Then, make sure you have make and cmake. Run

<pre>
    mkdir build
    cd build
    cmake ..
make
</pre>

# How to run
<pre>
src/game
</pre>
and then it will start a http service on port 8889. Visit http://localhost:8889 to play the game.

# Acceptance Test

Acceptance Test is using Behave with Python.

# JSON API

## `GET /join`

Join a new game. Returns:

```
{"game_id":2}
```

## `GET /<game ID>/start`

Start a new round. Right now always return:

```
{"action":"update_all"}
```

## `GET /<game ID>/current``

Get the latest status of the game. Returns:

```
{
    "players":[
        {
            "player_index":0, # player 0 is the human player
            "hand":[49,50,50,53,66,99,101,103,103,105,108,108,117],
            "new_pick":97,
            "melds":[]
        },{
            "player_index":1,
            "hand":[50,55,56,56,57,57,65,66,69,97,105,105,120],
            "new_pick":0,
            "melds":[]
        }
    ],
    "allowed_actions":["chow"]
}
```

## `GET /<game ID>/next_action`

After the human player moves, there could be multiple actions taken by other player(s). This api returns one action at a time. When playing with a fast AI player, the UI can use this to display the opponent's move in slow motion. Returns:
```
{"action":"pick", "player":0,"tile":97}
{"action":"discard", "player":1,"tile":117}
{"action":"your turn"}
{"action":"message", "content":"Are you kidding?"}
{"action":"win", "player":1,"score":1}
```

## `GET /<game ID>/pick`

Tell the server you want to pick a new tile. Returns:
```
{"action":"pick", "player":0,"tile":98}
```

## `GET /<game ID>/pong`

Tell the server you want to pong the last discarded tile from your opponent.

## `GET /<game ID>/chow?<tile id>`

Tell the server you want to chow the last discarded tile from your opponent. The <tile id> indicate the smallest tile you want chow with. For example, if you have 🀚🀛🀜🀝🀞 at hand, and your opponent just discarded 🀜:

| *command* | *new meld*  | *tiles remain at hand* |
| --------- | ----------- | ---------------------- |
|chow?🀚     | 🀚🀛🀜         | 🀜🀝🀞                    |
|chow?🀛     | 🀛🀜🀝         | 🀚🀜🀞                    |
|chow?🀜     | illegal     |                        |
|chow?🀝     | 🀜🀝🀞         | 🀚🀛🀜                    |
|chow?🀞     | illegal     |                        |

## `GET /<game ID>/throw?<tile id>`

Tell the server that you want to discard the tile with tile id. Returns:

```
{"action":"discard", "player":0,"tile":117}
```

## `GET /<game ID>/win`

Tell the server you think you win. Returns
```
{"action":"win", "player":0,"score":1}
```

