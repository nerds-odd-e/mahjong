#pragma once

#include "BaseAIPerspective.h"

class DummyPlayerPerspective : public BaseAIPerspective
{
public:
DummyPlayerPerspective(Settings & settings) : BaseAIPerspective(settings) {}
protected:
    Tile whichToDiscard() override;
    bool isAbleToWin(Tile tile) const override
    {
        return false;
    }
};
