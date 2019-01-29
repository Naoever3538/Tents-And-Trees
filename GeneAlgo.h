#ifndef GeneAlgo_H
#define GeneAlgo_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Treecomm.h"
#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"

//염색체 
struct Chrom{
	public:
	//유전자 위치들 
	char* locus;
	
	//접근
	char &operator[](const int i);

	//접근
	const char operator[](const int i) const;

	//생성자
	Chrom();

	//소멸자 
	~Chrom();
};

// 문제를 푸는 클래스
class GeneAlgo {
	public:
	Chrom* Best; //최적해
	int Fbest;
	
	private:
	//세대들 
	int Generation; //현 세대 번호. 첫 세대는 0 갈수록 1 증가 
	int NumberGen; //현 세대의 인구수 
	Chrom* Gen; //현 세대
	int NumberPar; //부모 세대의 인구수 
	Chrom* Par; //부모 세대
	
	//적합도들 
	int Fmax; //
	int Fmin; //
	int *Fitness; //세대의 적합도
	
	//룰렛 
	int NumberRou; // 아래 배열의 길이 
	int *Rou; //룰렛 배열 

	
	public:
	//실질적으로 문제를 푸는 함수 
	void toSolve(const TentMap *const tentMap);

	//염색체를 부모 없이 생성하는 함수 
	void toChromFromNothing(Chrom *const chrom, const TentMap *const tentMap);

	//염색체를 단친으로부터 물려받아 생성하는 함수 
	void toChromFromMother(Chrom *const chrom, const Chrom *const mother, const TentMap *const tentMap);

	//염색체를 양친으로부터 물려받아 생성하는 함수. 즉, 교차를 수행함 
	void toChromFromParent(Chrom *const chrom, const Chrom *const mother, const Chrom *const father, const TentMap *const tentMap);

	//염색체를 돌연변이하는함수. 지점별 일정한 확률로 
	void toMutate(Chrom *const chrom, const float mutaRate, const TentMap *const tentMap);
	
	//돌연변이 1점
	void toMutateSingle(Chrom *const chrom, const TentMap *const tentMap);
	
	//돌연변이 2점 
	void toMutateDouble(Chrom *const chrom, const TentMap *const tentMap);
	
	//돌연변이 3점 
	void toMutateTriple(Chrom *const chrom, const TentMap *const tentMap);
	
	//적합도
	const int toFit(Chrom *const chrom, const TentMap *const tentMap);
	
	//첫 세대 만들기
	void toFirstGen(const TentMap *const tentMap);

	//세대 평가하기 
	void toFitGen(const TentMap *const tentMap);
	
	//룰렛 만들기. 룰렛휠 선택  
	void toMakeRou();

	//룰렛 만들기. 순위기반 선택 
	void toMakeRouByOrder();
	
	//룰렛 돌려서 숫자 찾기 
	const int toRou();

	//세대 교체. 자식 세대는 부모세대가 된다. 
	void toReplace();
	
	//번식. 부모 세대를 바탕으로 새로운 자식 세대를 만든다.
	void toReproduce(const TentMap *const tentMap);

	//염색체를 맞교대(정렬을 위해서) 
	void toSwapGen(int g, int h);

	//퀵정렬
	void toQuickSort(int zeroth, int llast);
	
	//결과 출력
	void toPrintOut(const TentMap *const tentMap);

	//생성자
	GeneAlgo();

	//소멸자 
	~GeneAlgo();
};
#endif
