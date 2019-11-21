/***********************************************************
 *  mj script for html mahjiong game.
 * 
 *
 */
var converter = new Array();

converter[0] = 0;
converter[49] = 1;
converter[50] = 2;
converter[51] = 3;
converter[52] = 4;
converter[53] = 5;
converter[54] = 6;
converter[55] = 7;
converter[56] = 8;
converter[57] = 9;
converter[65] = 21;
converter[66] = 22;
converter[67] = 23;
converter[68] = 24;
converter[69] = 25;
converter[70] = 26;
converter[71] = 27;
converter[72] = 28;
converter[73] = 29;
converter[97] = 41;
converter[98] = 42;
converter[99] = 43;
converter[100] = 44;
converter[101] = 45;
converter[102] = 46;
converter[103] = 47;
converter[104] = 48;
converter[105] = 49;
converter[108] = 61;
converter[111] = 64;
converter[114] = 67;
converter[117] = 70;
converter[120] = 73;
converter[123] = 76;
converter[126] = 79;
var player_count = 2;
var App = {
    max_holding_count: 13,
    max_meld_count: 4,
    players: Array(player_count),
    player_count: player_count,
    current_player: 0,
    board_index: 1,
    chowing: false,
    game_id: undefined,
    setup: function() {
        document.onclick = App.onclick;

        this._AddNotification();
        this.StartGame();
        this._getRequest("join", null, function(http) {
            App.game_id = JSON.parse(http.responseText).game_id;
            App._ExecuteCmd("start", 0);
        });
    },
    StartGame: function() {
        this._SetupPage();
    },
    updateAll: function() {
        this._getCmdRequest("current", null, function(text) {
            var data = JSON.parse(text)
            App.players = data.players;
            App.allowed_actions = data.allowed_actions;
            App._UpdateAllCells();
        });
    },
    Pick: function(player, new_tile) {
        if (new_tile == 0) {
            alert("Nobody wins.");
            this._SetupBoard();
            this._UpdateAllCells();
            this._ExecuteCmd("start", 0);
        } else {
            this.players[player].new_pick = new_tile;
            this._UpdateAllCells();
        }
    },
    _resetChowing: function() {
        this._showStatus("action", "");
        this.chowing = false;
    },
    Chow: function() {
        if (this.chowing)
            this._resetChowing();
        else if (App._isPicking()) {
            this._showStatus("action", "Please click on the smallest tile you want to chow with.");
            this.chowing = true;
        }
    },
    Chow_with_tile: function(tile) {
        this._ExecuteCmd('chow', tile);
    },
    Pong: function() {
        this._ExecuteCmd('pong', 0);
    },
    Kong: function() {
        this._ExecuteCmd('kong', 0);
    },
    Win: function() {
        this._ExecuteCmd('win', 0);
    },
    WinAck: function(distance, score) {
        this._ResetAllButtons();
        if (score == 0) {
            alert("Nobody wins.");
        } else {
            if (distance == 0)
                alert("You win (" + score + ")!");
            else
                alert("You lose (" + score + ")!");
        }
        this._SetupBoard();
        this._UpdateAllCells();
        this._ExecuteCmd("start", 0);

    },
    onclick: function(e) {
        var target;
        try {
            target = App._findClickableTarget(e.target);
        } catch (ex) {
            target = App._findClickableTarget(window.event.srcElement);
        }

        if (target) {
            if (App._isPicking() && !App.chowing) {
                App._Pick();
            } else {
                var discard = -1
                var id = target.id.substr(5);
                if (id == 'current') {
                    discard = App.players[0].new_pick;
                } else {
                    var index = parseInt(id);
                    index = App._CellIndexToHoldingIndex(0, index);
                    if (index >= 0) {
                        discard = App.players[0].hand[index];
                    }
                }
                if (discard != -1)
                    if (App.chowing)
                        App.Chow_with_tile(discard);
                    else
                        App._Throw(discard);
            }
        }
    },
    _isPicking: function() {
        if (this.players[0].new_pick == 0) {
            if ((this.players[0].hand.length % 3) == 1)
                return true;
        }
        return false;
    },
    _Throw: function(tile) {
        this._ResetAllButtons();
        App._ExecuteCmd('throw', tile);
    },
    _Pick: function() {
        this._ResetAllButtons();
        App._ExecuteCmd('pick', 0);
    },
    Throw: function(player, tile) {
        if (tile != 0) {
            if (this.players[player].new_pick != tile) {
                for (var i = 0; i < this.players[player].hand.length; i++)
                    if (this.players[player].hand[i] == tile) {
                        this.players[player].hand[i] = this.players[player].new_pick;
                        break;
                    }
                this.players[player].hand.sort(function(a, b) { return a - b });
            }
            this.players[player].new_pick = 0;

            this._UpdateAllCells();
            var cell = document.getElementById("sh_" + App.board_index);
            App.board_index++;
            cell.innerHTML = "<img src='images/" + converter[tile] + ".png' height=64 width=41 style='-webkit-transform: rotate(180deg);-moz-transform: rotate(180deg);filter: progid:DXImageTransform.Microsoft.BasicImage(rotation=2);'>"
        }
        this._Picking(player);
    },
    RemoveLast: function() {
        var cell = document.getElementById("sh_" + (App.board_index - 1));
        cell.className = "meld";
    },
    LightButton: function(button) {
        var cell = document.getElementById(button + "_button");
        cell.style.cssText = "background: #FF0000;"
    },
    _ResetAllButtons: function() {
        this._ResetButton("win")
        this._ResetButton("chow")
        this._ResetButton("kong")
        this._ResetButton("pong")
    },
    _ResetButton: function(button) {
        var cell = document.getElementById(button + "_button");
        cell.style.cssText = ""
    },

    _StopUpdate: function() {
        if (this.ti1 != -1) {
            clearInterval(this.ti1);
            this.ti1 = -1;
        }
    },
    _Update: function() {
        App._ExecuteCmd('update', 0)
    },
    _Picking: function(player) {
        this.current_player = player;
    },
    _findClickableTarget: function(target) {
        // If a table cell, we assume that's editable
        try {
            if (target.id.substr(0, 4) == "ph_0")
                return target;

            if (target.parentNode)
                return this._findClickableTarget(target.parentNode);
        } catch (e) {}
        return null;
    },

    _getRequest: function(cmd, raw_param, callback) {
        var http;
        try {
            http = new XMLHttpRequest();
        } catch (e) {
            http = new ActiveXObject("Microsoft.XMLHTTP");
        }
        http.open("GET", cmd + '?' + raw_param, true);
        http.send(null);
        http.onreadystatechange = function() {
            if (http.readyState == 4) {
                callback(http);
            }
        };
    },

    _getCmdRequest: function(cmd, param, callback) {
        this._getRequest('/' + this.game_id + '/' + cmd, param, function(http) {
            var textout = http.responseText;
            callback(textout);
        });
    },

    _ExecuteCmd: function(cmd, param) {
        this.allowed_actions = []
        this._resetChowing();
        this._getCmdRequest(cmd, param, function(textout) {
            var data = JSON.parse(textout)
            if (data.action != "your turn") {
                App._DisplayAction(data);
                setTimeout(function() {
                    App._ExecuteCmd("next_action", 0);
                }, 500);
            } else {
                App.updateAll();
            }
        });
    },

    _DisplayAction: function(data) {
        if (data.action === 'update_all') { App.updateAll(); return; }
        if (data.action === 'pick') { App.Pick(data.player, data.tile); return; }
        if (data.action === 'discard') { App.Throw(data.player, data.tile); return; }
        if (data.action === 'win') { App.WinAck(data.player, data.score); return; }
        alert("unknown action: " + data.action)
    },

    _showStatus: function(desc, result) {
        var tstat = document.getElementById("tabel_status")
        if (tstat.innerText)
            tstat.innerText = desc + ":" + result
        else
            tstat.textContent = desc + ":" + result

    },
    _AddNotification: function() {
        var newNode = document.createElement("span")
        newNode.setAttribute("id", "tabel_status");
        newNode.style.cssText = "position: absolute;" +
            "margin: 0px;" +
            "padding: 0px;" +
            "font-family: verdana;" +
            "font-size: 12px;" +
            "background: #FFAA88;" +
            "left:0px;top:0px;"
        newNode.innerHTML = "Mahjiong game is working!"
        document.body.appendChild(newNode);
    },
    _SetupPage: function() {
        var newNode = document.createElement("span")
        newNode.setAttribute("id", "game_board");
        newNode.innerHTML = "<table>\n" +
            "<tr><td id=player_1> put me here" +
            "<tr><td id=board0>\n" +
            "<tr><td id=player_0>\n" +
            "<tr><td id=panel0></table><div id='log'>log...</div>"
        document.body.appendChild(newNode);
        this._SetupPlayers();
        this._SetupBoard();
        this._SetupPannel();
    },
    _SetupPlayers: function() {
        for (var i = 0; i < this.player_count; i++) {
            this._SetupPlayer(i);
        }
    },
    _SetupPlayer: function(player) {
        var html = "<table class=player><tr><td width=50><table class='meld_plate'><tr>"
        for (var i = 0; i < this.max_meld_count; i++)
            html += ("<td id=meld_" + player + "_" + i + ">");
        html = html + "</table><td><table><tr>"
        var cnt = 1;
        for (var i = 0; i < this.max_holding_count; i++) {
            html += ("<td id=ph_" + player + "_" + i + ">");
        }
        html += ("<td>-<td id=ph_" + player + "_current></table></table>");
        var player_html = document.getElementById("player_" + player);
        player_html.innerHTML = html;
    },

    _SetupBoard: function() {
        this.board_index = 1;
        var html = "<table><tr><td width=800 height=150><table>"
        var cnt = 1;
        for (var i = 0; i < 4; i++) {
            html += "<tr>"
            for (var j = 0; j < 15; j++) {
                html += ("<td id=sh_" + cnt + ">");
                cnt++;
            }
        }
        var board = document.getElementById("board0");

        board.innerHTML = html;
    },
    _SetupPannel: function() {

        var panel = document.getElementById("panel0");
        panel.innerHTML = "<table><tr>" +
            "<td> <a class='button' id=chow_button onclick='return App.Chow()'>Chow</a>" +
            "<td> <a class='button' id=pong_button onclick='return App.Pong()'>Pong</a>" +
            "<td> <a class='button' id=kong_button onclick='return App.Kong()'>Kong</a>" +
            "<td> <a class='button' id=win_button onclick='return App.Win()'>Win!!</a>" +
            "</table>";

    },
    _UpdateAllCells: function() {
        for (var j = 0; j < this.player_count; j++) {
            for (var i = 0; i < this.max_meld_count; i++) {
                this._Updatemeld(j, i)
            }
            for (var i = 0; i <= this.max_holding_count; i++)
                this._UpdateCell(j, i);
        }
        this._ResetAllButtons();
        this.allowed_actions.forEach(element => this.LightButton(element));
    },
    _Updatemeld: function(player, index) {
        var cell = document.getElementById("meld_" + player + "_" + index);
        if (index < this.players[player].melds.length) {
            var inc = 0
            var e = this.players[player].melds[index];
            if (e > 0x100) {
                e -= 0x100;
                inc = 1;
            } else
                e -= 0x80;
            e = converter[e];
            var html = "<table class=meld_w><tr>"
            html += ("<td class=meld_w>" + "<img class=meld_plate src='images/" + e + ".png' height=64 width=41>");
            e += inc;
            html += ("<td class=meld_w>" + "<img class=meld_plate src='images/" + e + ".png' height=64 width=41>");
            e += inc;
            html += ("<td class=meld_w>" + "<img class=meld_plate src='images/" + e + ".png' height=64 width=41>");
            html += "</table>"
            cell.innerHTML = html;
        } else {
            cell.innerHTML = "";
        }

    },
    _CellIndexToHoldingIndex: function(player, cell_index) {
        var diff = this.max_holding_count - this.players[player].hand.length;
        return cell_index >= diff ? cell_index - diff : -1;
    },
    _UpdateCell: function(player, index) {
        var cell;
        var tile;
        if (index != this.max_holding_count) {
            cell = document.getElementById("ph_" + player + "_" + index);
            var holding_index = this._CellIndexToHoldingIndex(player, index);
            tile;
            if (holding_index >= 0)
                tile = this.players[player].hand[holding_index];
            else
                tile = 0;
        } else {
            cell = document.getElementById("ph_" + player + "_current");
            tile = this.players[player].new_pick;
        }
        if (tile == 0 && index != this.max_holding_count)
            cell.innerHTML = "";
        else
            cell.innerHTML = "<img class='active_tile' src='images/" + converter[tile] + ".png' height=64 width=41>"
    },

    the_end: 1
}

function setup() {
    App.setup();
}
window.App = App;
window.onload = setup;