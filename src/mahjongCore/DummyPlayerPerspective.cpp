#include "DummyPlayerPerspective.h"
#include "Hand.h"

Tile DummyPlayerPerspective::whichToDiscard()
{
    return player->getCurrentTileAtHand();
}
