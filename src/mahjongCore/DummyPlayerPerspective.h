#pragma once

#include "AIPerspective.h"

class DummyPlayerPerspective : public AIPerspective
{
public:
DummyPlayerPerspective(Settings & settings) : AIPerspective(settings) {}
protected:
    Tile whichToDiscard() override;
};
