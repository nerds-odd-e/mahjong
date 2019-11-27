#ifndef AI_PERSPECTIVE_H_
#define AI_PERSPECTIVE_H_

#include "Perspective.h"
class Hand;
class EvaluatorAdaptor;
class AIPerspective: public Player{
public:
	AIPerspective(Settings & settings);
	virtual ~AIPerspective();

	void deal(const Tile tiles[], int n, int distance);
	virtual void pick(Tile tile, int distance);
	virtual void pong(Tile tile, int distance);
	virtual int chow(Tile tile, Tile with, int distance);
	virtual void win(int score, int distance);
	virtual void discard(Tile tile, int distance);

	virtual void pushActionRequest(PlayerActionRequest * actionRequest);
	void setEvaluator(EvaluatorAdaptor * evaluator);

protected:
	virtual Tile whichToDiscard();
	Hand * player;

private:
	EvaluatorAdaptor * evaluator;

};

#endif /* AI_PERSPECTIVE_H_ */
