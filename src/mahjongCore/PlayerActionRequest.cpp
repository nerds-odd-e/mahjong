#include "tile.h"
#include "PlayerActionRequest.h"
#include "GameState.h"


void PlayerActionRequest::doPlayerAction(GameState *currentState_) {

	if (ACTION_RESTART == action_)
		currentState_->restart();
	else if (ACTION_DISCARD == action_)
		currentState_->discard(tile_);
	else if (ACTION_WIN == action_)
		currentState_->doWin();
	else if (ACTION_PICK == action_)
		currentState_->doPick();
	else if (ACTION_WIN == action_)
		currentState_->doWin();
	else if (ACTION_PONG == action_)
		currentState_->doPong();
	else if (ACTION_CHOW == action_)
		currentState_->doChow(tile_);
}
