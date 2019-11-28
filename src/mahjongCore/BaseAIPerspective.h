#ifndef BASE_AI_PERSPECTIVE_H_
#define BASE_AI_PERSPECTIVE_H_

#include "Perspective.h"
class Hand;
class EvaluatorAdaptor;
class BaseAIPerspective: public Player{
public:
	BaseAIPerspective(Settings & settings);
	virtual ~BaseAIPerspective();

	void deal(const Tile tiles[], int n, int distance);
	virtual void pick(Tile tile, int distance);
	virtual void pong(Tile tile, int distance);
	virtual int chow(Tile tile, Tile with, int distance);
	virtual void win(int score, int distance);
	virtual void discard(Tile tile, int distance);

	virtual void pushActionRequest(PlayerActionRequest * actionRequest);
	void setEvaluator(EvaluatorAdaptor * evaluator);

protected:
	Hand * player;
	EvaluatorAdaptor * evaluator;

	virtual Tile whichToDiscard() = 0;
  	virtual bool isAbleToWin(Tile tile) const;
};

#endif /* BASE_AI_PERSPECTIVE_H_ */
