set(Main_SRCS
      aiGame.cpp
      aiGame.h
      AIPerspective.cpp
      AIPerspective.h
      BaseAIPerspective.cpp
      BaseAIPerspective.h
      DummyPlayerPerspective.cpp
      DummyPlayerPerspective.h
      EvaluatorAdaptor.cpp
      EvaluatorAdaptor.h
      game.cpp
      game.h
      GameIDMap.cpp
      GameIDMap.h
      GameLevel.h
      GameLevel.cpp
      GameState.cpp
      GameState.h
      Hand.cpp
      Hand.h
      mahjong_game.h
      MahjongCommand.cpp
      MahjongCommand.h
      mj_table.cpp
      mj_table.h
      Perspective.h
      PlayerActionRequest.cpp
      PlayerActionRequest.h
      Settings.cpp
      Settings.h
      tile.cpp
      tile.h
      TileArray.cpp
      TileArray.h
      UIEvent.cpp
      UIEvent.h
      UserPerspective.cpp
      UserPerspective.h
      Wall.cpp
      Wall.h
      GameJsonResponse.cpp GameJsonResponse.h
      MahjongGameServer.cpp MahjongGameServer.h
      )

add_library(mahjongCore ${Main_SRCS})

