#ifndef AI_PERSPECTIVE_H_
#define AI_PERSPECTIVE_H_

#include "BaseAIPerspective.h"

class AIPerspective: public BaseAIPerspective {
public:
	AIPerspective(Settings & settings);
	virtual ~AIPerspective();
protected:
	virtual Tile whichToDiscard(); 
};

#endif /* AI_PERSPECTIVE_H_ */
