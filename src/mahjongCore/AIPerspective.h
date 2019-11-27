#ifndef AI_PERSPECTIVE_H_
#define AI_PERSPECTIVE_H_

#include "BaseAIPerspective.h"

class Hand;
class EvaluatorAdaptor;
class AIPerspective: public BaseAIPerspective {
public:
	AIPerspective(Settings & settings);
	virtual ~AIPerspective();

protected:
	virtual Tile whichToDiscard();
	virtual bool isAbleToWin(Tile tile) const;
};

#endif /* AI_PERSPECTIVE_H_ */
