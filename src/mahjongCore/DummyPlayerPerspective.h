#pragma once

#include "AIPerspective.h"

class DummyPlayerPerspective : public AIPerspective
{

public:
	DummyPlayerPerspective(unsigned int max_holding_count) : AIPerspective(max_holding_count) {};

protected:
    Tile whichToDiscard() override;
};
