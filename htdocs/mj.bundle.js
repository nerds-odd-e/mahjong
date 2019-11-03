/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./htdocs/app.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./htdocs/app.js":
/*!***********************!*\
  !*** ./htdocs/app.js ***!
  \***********************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\n\n/***********************************************************\n *  mj script for html mahjiong game.\n * \n *\n */\nvar converter = new Array();\nconverter[0] = 0;\nconverter[49] = 1;\nconverter[50] = 2;\nconverter[51] = 3;\nconverter[52] = 4;\nconverter[53] = 5;\nconverter[54] = 6;\nconverter[55] = 7;\nconverter[56] = 8;\nconverter[57] = 9;\nconverter[65] = 21;\nconverter[66] = 22;\nconverter[67] = 23;\nconverter[68] = 24;\nconverter[69] = 25;\nconverter[70] = 26;\nconverter[71] = 27;\nconverter[72] = 28;\nconverter[73] = 29;\nconverter[97] = 41;\nconverter[98] = 42;\nconverter[99] = 43;\nconverter[100] = 44;\nconverter[101] = 45;\nconverter[102] = 46;\nconverter[103] = 47;\nconverter[104] = 48;\nconverter[105] = 49;\nconverter[108] = 61;\nconverter[111] = 64;\nconverter[114] = 67;\nconverter[117] = 70;\nconverter[120] = 73;\nconverter[123] = 76;\nconverter[126] = 79;\nvar player_count = 2;\nvar App = {\n  max_holding_count: 13,\n  max_meld_count: 4,\n  player_count: player_count,\n  current_player: 0,\n  holdings: Array(player_count),\n  current: Array(player_count),\n  meld: Array(player_count),\n  board_index: 1,\n  chowing: false,\n  game_id: undefined,\n  setup: function setup() {\n    var j;\n\n    for (var j = 0; j < this.player_count; j++) {\n      this.holdings[j] = Array(0);\n      this.meld[j] = Array(0);\n    }\n\n    document.onclick = App.onclick;\n\n    this._AddNotification();\n\n    this.StartGame();\n\n    this._getRequest(\"game\", null, function (http) {\n      App.game_id = JSON.parse(http.responseText).player_id;\n\n      App._ExecuteCmd(\"start\", 0);\n    });\n  },\n  StartGame: function StartGame() {\n    this._SetupPage();\n  },\n  UpdateHolding: function UpdateHolding(new_holdings) {\n    for (var j = 0; j < this.player_count; j++) {\n      var cnt = 0;\n\n      for (var i in new_holdings[j]) {\n        if (new_holdings[j][i] < 0x80) cnt++;else break;\n      }\n\n      this.holdings[j] = Array(cnt - 1);\n\n      for (var i = 0; i < cnt - 1; i++) {\n        this.holdings[j][i] = new_holdings[j][i];\n      }\n\n      this.current[j] = new_holdings[j][i];\n      this.meld[j] = Array(new_holdings[j].length - cnt);\n      var cnt;\n\n      for (cnt = 0, i++; i < new_holdings[j].length; i++) {\n        this.meld[j][cnt++] = new_holdings[j][i];\n      }\n    }\n\n    this._UpdateAllCells();\n  },\n  Pick: function Pick(player, new_tile) {\n    if (new_tile == 0) {\n      alert(\"Nobody wins.\");\n\n      this._SetupBoard();\n\n      this._UpdateAllCells();\n\n      this._ExecuteCmd(\"start\", 0);\n\n      this._ExecuteCmd(\"all\", 0);\n    } else {\n      this.current[player] = new_tile;\n\n      this._UpdateAllCells();\n    }\n  },\n  _resetChowing: function _resetChowing() {\n    this._showStatus(\"action\", \"\");\n\n    this.chowing = false;\n  },\n  Chow: function Chow() {\n    if (this.chowing) this._resetChowing();else if (App._isPicking()) {\n      this._showStatus(\"action\", \"Please click on the smallest tile you want to chow with.\");\n\n      this.chowing = true;\n    }\n  },\n  Chow_with_tile: function Chow_with_tile(tile) {\n    this._ExecuteCmd('chow', tile);\n  },\n  Pong: function Pong() {\n    this._ExecuteCmd('pong', 0);\n  },\n  Kong: function Kong() {\n    this._ExecuteCmd('kong', 0);\n  },\n  Win: function Win() {\n    this._ExecuteCmd('win', 0);\n  },\n  WinAck: function WinAck(distance, score) {\n    this._ResetAllButtons();\n\n    this.StopUpdate();\n\n    if (score == 0) {\n      alert(\"Nobody wins.\");\n    } else {\n      if (distance == 0) alert(\"You win (\" + score + \")!\");else alert(\"You lose (\" + score + \")!\");\n    }\n\n    this._SetupBoard();\n\n    this._UpdateAllCells();\n\n    this._ExecuteCmd(\"start\", 0);\n  },\n  onclick: function onclick(e) {\n    var target;\n\n    try {\n      target = App._findClickableTarget(e.target);\n    } catch (ex) {\n      target = App._findClickableTarget(window.event.srcElement);\n    }\n\n    if (target) {\n      if (App._isPicking() && !App.chowing) {\n        App._Pick();\n      } else {\n        var discard = -1;\n        var id = target.id.substr(5);\n\n        if (id == 'current') {\n          discard = App.current[0];\n        } else {\n          var index = parseInt(id);\n          index = App._CellIndexToHoldingIndex(0, index);\n\n          if (index >= 0) {\n            discard = App.holdings[0][index];\n          }\n        }\n\n        if (discard != -1) if (App.chowing) App.Chow_with_tile(discard);else App._Throw(discard);\n      }\n    }\n  },\n  _isPicking: function _isPicking() {\n    if (this.current[0] == 0) {\n      if (this.holdings[0].length % 3 == 1) return true;\n    }\n\n    return false;\n  },\n  _Throw: function _Throw(tile) {\n    this._ResetAllButtons();\n\n    App._ExecuteCmd('throw', tile);\n  },\n  _Pick: function _Pick() {\n    this._ResetAllButtons();\n\n    App._ExecuteCmd('pick', 0);\n  },\n  Throw: function Throw(tile, player) {\n    if (tile != 0) {\n      if (this.current[player] != tile) {\n        for (var i = 0; i < this.holdings[player].length; i++) {\n          if (this.holdings[player][i] == tile) {\n            this.holdings[player][i] = this.current[player];\n            break;\n          }\n        }\n\n        this.holdings[player].sort(function (a, b) {\n          return a - b;\n        });\n      }\n\n      this.current[player] = 0;\n\n      this._UpdateAllCells();\n\n      var cell = document.getElementById(\"sh_\" + App.board_index);\n      App.board_index++;\n      cell.innerHTML = \"<img src='images/\" + converter[tile] + \".png' height=64 width=41 style='-webkit-transform: rotate(180deg);-moz-transform: rotate(180deg);filter: progid:DXImageTransform.Microsoft.BasicImage(rotation=2);'>\";\n    }\n\n    this._Picking(player);\n  },\n  RemoveLast: function RemoveLast() {\n    var cell = document.getElementById(\"sh_\" + (App.board_index - 1));\n    cell.className = \"meld\";\n  },\n  LightButton: function LightButton(button) {\n    var cell = document.getElementById(button + \"_button\");\n    cell.style.cssText = \"background: #FF0000;\";\n  },\n  _ResetAllButtons: function _ResetAllButtons() {\n    this._ResetButton(\"win\");\n\n    this._ResetButton(\"chow\");\n\n    this._ResetButton(\"kong\");\n\n    this._ResetButton(\"pong\");\n  },\n  _ResetButton: function _ResetButton(button) {\n    var cell = document.getElementById(button + \"_button\");\n    cell.style.cssText = \"\";\n  },\n  t: -1,\n  ResumeUpdate: function ResumeUpdate() {\n    if (this.t == -1) {//\t\t\t\tthis.t = setInterval(\"App._Update()\", 250);\n    }\n  },\n  StopUpdate: function StopUpdate() {\n    if (this.t != -1) {\n      clearInterval(this.t);\n      this.t = -1;\n    }\n  },\n  _Update: function _Update() {\n    App._ExecuteCmd('update', 0);\n  },\n  _Picking: function _Picking(player) {\n    this.current_player = player;\n  },\n  _findClickableTarget: function _findClickableTarget(target) {\n    // If a table cell, we assume that's editable\n    try {\n      if (target.id.substr(0, 4) == \"ph_0\") return target;\n      if (target.parentNode) return this._findClickableTarget(target.parentNode);\n    } catch (e) {}\n\n    return null;\n  },\n  _getRequest: function _getRequest(cmd, raw_param, callback) {\n    var http;\n\n    try {\n      http = new XMLHttpRequest();\n    } catch (e) {\n      http = new ActiveXObject(\"Microsoft.XMLHTTP\");\n    }\n\n    http.open(\"GET\", cmd + '?' + raw_param, true);\n    http.send(null);\n\n    http.onreadystatechange = function () {\n      if (http.readyState == 4) {\n        callback(http);\n      }\n    };\n  },\n  _ExecuteCmd: function _ExecuteCmd(cmd, param) {\n    this._resetChowing();\n\n    param = this.game_id * 1000 + param;\n\n    this._getRequest(cmd, param, function (http) {\n      var textout = http.responseText;\n\n      App._Display(textout);\n    });\n  },\n  _DisplayAnimation: function _DisplayAnimation(animations) {\n    if (this.ti != -1) clearInterval(this.ti);\n    eval(animations.shift());\n    if (animations.length > 0) this.ti = setInterval(function () {\n      App._DisplayAnimation(animations);\n    }, 500);\n  },\n  _Display: function _Display(text) {\n    this.ti = -1;\n    var animations = text.split(\"|\");\n    if (animations.length > 0) App._DisplayAnimation(animations);\n  },\n  _showStatus: function _showStatus(desc, result) {\n    var tstat = document.getElementById(\"tabel_status\");\n    if (tstat.innerText) tstat.innerText = desc + \":\" + result;else tstat.textContent = desc + \":\" + result;\n  },\n  _AddNotification: function _AddNotification() {\n    var newNode = document.createElement(\"span\");\n    newNode.setAttribute(\"id\", \"tabel_status\");\n    newNode.style.cssText = \"position: absolute;\" + \"margin: 0px;\" + \"padding: 0px;\" + \"font-family: verdana;\" + \"font-size: 12px;\" + \"background: #FFAA88;\" + \"left:0px;top:0px;\";\n    newNode.innerHTML = \"Mahjiong game is working!\";\n    document.body.appendChild(newNode);\n  },\n  _SetupPage: function _SetupPage() {\n    var newNode = document.createElement(\"span\");\n    newNode.setAttribute(\"id\", \"game_board\");\n    newNode.innerHTML = \"<table>\\n\" + \"<tr><td id=player_1> put me here\" + \"<tr><td id=board0>\\n\" + \"<tr><td id=player_0>\\n\" + \"<tr><td id=panel0></table><div id='log'>log...</div>\";\n    document.body.appendChild(newNode);\n\n    this._SetupPlayers();\n\n    this._SetupBoard();\n\n    this._SetupPannel();\n  },\n  _SetupPlayers: function _SetupPlayers() {\n    for (var i = 0; i < this.player_count; i++) {\n      this._SetupPlayer(i);\n    }\n  },\n  _SetupPlayer: function _SetupPlayer(player) {\n    var html = \"<table class=player><tr><td width=50><table class='meld_plate'><tr>\";\n\n    for (var i = 0; i < this.max_meld_count; i++) {\n      html += \"<td id=meld_\" + player + \"_\" + i + \">\";\n    }\n\n    html = html + \"</table><td><table><tr>\";\n    var cnt = 1;\n\n    for (var i = 0; i < this.max_holding_count; i++) {\n      html += \"<td id=ph_\" + player + \"_\" + i + \">\";\n    }\n\n    html += \"<td>-<td id=ph_\" + player + \"_current></table></table>\";\n    var player_html = document.getElementById(\"player_\" + player);\n    player_html.innerHTML = html;\n  },\n  _SetupBoard: function _SetupBoard() {\n    this.board_index = 1;\n    var html = \"<table><tr><td width=800 height=150><table>\";\n    var cnt = 1;\n\n    for (var i = 0; i < 4; i++) {\n      html += \"<tr>\";\n\n      for (var j = 0; j < 15; j++) {\n        html += \"<td id=sh_\" + cnt + \">\";\n        cnt++;\n      }\n    }\n\n    var board = document.getElementById(\"board0\");\n    board.innerHTML = html;\n  },\n  _SetupPannel: function _SetupPannel() {\n    var panel = document.getElementById(\"panel0\");\n    panel.innerHTML = \"<table><tr>\" + \"<td> <a class='button' id=chow_button onclick='return App.Chow()'>Chow</a>\" + \"<td> <a class='button' id=pong_button onclick='return App.Pong()'>Pong</a>\" + \"<td> <a class='button' id=kong_button onclick='return App.Kong()'>Kong</a>\" + \"<td> <a class='button' id=win_button onclick='return App.Win()'>Win!!</a>\" + \"</table>\";\n  },\n  _UpdateAllCells: function _UpdateAllCells() {\n    for (var j = 0; j < this.player_count; j++) {\n      for (var i = 0; i < this.max_meld_count; i++) {\n        this._Updatemeld(j, i);\n      }\n\n      for (var i = 0; i <= this.max_holding_count; i++) {\n        this._UpdateCell(j, i);\n      }\n    }\n  },\n  _Updatemeld: function _Updatemeld(player, index) {\n    var cell = document.getElementById(\"meld_\" + player + \"_\" + index);\n\n    if (index < this.meld[player].length) {\n      var inc = 0;\n      var e = this.meld[player][index];\n\n      if (e > 0x100) {\n        e -= 0x100;\n        inc = 1;\n      } else e -= 0x80;\n\n      e = converter[e];\n      var html = \"<table class=meld_w><tr>\";\n      html += \"<td class=meld_w>\" + \"<img class=meld_plate src='images/\" + e + \".png' height=64 width=41>\";\n      e += inc;\n      html += \"<td class=meld_w>\" + \"<img class=meld_plate src='images/\" + e + \".png' height=64 width=41>\";\n      e += inc;\n      html += \"<td class=meld_w>\" + \"<img class=meld_plate src='images/\" + e + \".png' height=64 width=41>\";\n      html += \"</table>\";\n      cell.innerHTML = html;\n    } else {\n      cell.innerHTML = \"\";\n    }\n  },\n  _CellIndexToHoldingIndex: function _CellIndexToHoldingIndex(player, cell_index) {\n    var diff = this.max_holding_count - this.holdings[player].length;\n    return cell_index >= diff ? cell_index - diff : -1;\n  },\n  _UpdateCell: function _UpdateCell(player, index) {\n    var cell;\n    var tile;\n\n    if (index != this.max_holding_count) {\n      cell = document.getElementById(\"ph_\" + player + \"_\" + index);\n\n      var holding_index = this._CellIndexToHoldingIndex(player, index);\n\n      tile;\n      if (holding_index >= 0) tile = this.holdings[player][holding_index];else tile = 0;\n    } else {\n      cell = document.getElementById(\"ph_\" + player + \"_current\");\n      tile = this.current[player];\n    }\n\n    if (tile == 0 && index != this.max_holding_count) cell.innerHTML = \"\";else cell.innerHTML = \"<img class='active_tile' src='images/\" + converter[tile] + \".png' height=64 width=41>\";\n  },\n  the_end: 1\n};\n\nfunction setup() {\n  App.setup();\n}\n\nwindow.App = App;\nwindow.onload = setup;\n\n//# sourceURL=webpack:///./htdocs/app.js?");

/***/ })

/******/ });