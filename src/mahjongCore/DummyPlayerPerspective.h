#pragma once

#include "AIPerspective.h"

class DummyPlayerPerspective : public AIPerspective
{

protected:
    Tile whichToDiscard() override;
};
