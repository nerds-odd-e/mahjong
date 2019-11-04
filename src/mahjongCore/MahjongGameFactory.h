#ifndef MAHJONGGAMEFACTORY_H_
#define MAHJONGGAMEFACTORY_H_

class MahjongGameResponse;
struct MahjongGameFactory {
	virtual ~MahjongGameFactory(){}
	virtual MahjongGameResponse * createMahjongGameRespond() = 0;

};


#endif /* MAHJONGGAMEFACTORY_H_ */
