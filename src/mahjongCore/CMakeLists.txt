set(Main_SRCS
      aiGame.cpp
      aiGame.h
      AIPerspective.cpp
      AIPerspective.h
      CMakeLists.txt
      EvaluatorAdaptor.cpp
      EvaluatorAdaptor.h
      game.cpp
      game.h
      GameIDMap.cpp
      GameIDMap.h
      GameState.cpp
      GameState.h
      Hand.cpp
      Hand.h
      mahjong_game.h
      MahjongCommand.cpp
      MahjongCommand.h
      MahjongGameFactory.h
      MahjongGameResponse.h
      mj_table.cpp
      mj_table.h
      Perspective.h
      PlayerActionRequest.cpp
      PlayerActionRequest.h
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
      HTMLUIEvent.h HTMLUIEvent.cpp
      )

add_library(mahjongCore ${Main_SRCS})

