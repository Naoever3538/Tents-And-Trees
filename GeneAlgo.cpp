#ifndef GeneAlgo_Cpp 
#define GeneAlgo_Cpp

#include <stdio.h>

#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"
#include "GeneAlgo.h"

//class chrom
//접근
char &Chrom::operator[](const int i){
	return this->locus[i];
}

const char Chrom::operator[](const int i) const{
	return this->locus[i];
}

//생성자
Chrom::Chrom() : locus(nullptr){
}

//소멸자
Chrom::~Chrom(){
	if (locus != nullptr)
		delete[] locus;	
}

//class GeneAlgo
//실질적으로 문제를 푸는 함수
void GeneAlgo::toSolve(const TentMap *const tentMap){
	//난수 초기화 
	srand(time(nullptr));
			
	do {
		//2천세대마다 현 세대를 모두 지우고 새로운 세대가 시작된다
		if( Generation == 0 || (Generation > 2000 && Generation%2000 == 1))  
			toFirstGen(tentMap);

		//평가
		toFitGen(tentMap);

		if (Fbest==0)
			break;
			
		//정렬
		toQuickSort(0, NumberGen);
		
		if(Generation%2000 == 0) //2천세대마다 현재 상황을 프린트
			toPrintOut(tentMap);
		
		//룰렛 만들기
		toMakeRou();
		
		//세대 교체. 자식 세대는 부모세대가 된다.
		toReplace();
		Generation++;
		
		//번식. 부모 세대를 바탕으로 새로운 자식 세대를 만든다.
		toReproduce(tentMap);
	} while (1);
	
	toPrintOut(tentMap);
}

//염색체를 부모 없이 생성하는 함수 
void GeneAlgo::toChromFromNothing(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int)(tentMap -> NumberTrees);
	
	//유전자에 담을 공간 확보
	if(chrom -> locus == nullptr){
			chrom -> locus = new char[numberTrees];
	}
	
	//각 나무가 놓을 수 있는 방향을 고려하여 유전자 초기화 
	for(int k=0; k < numberTrees; k++){
		chrom->locus[k] = Direc::Action[treeDirection[k]]();
	}
}

//염색체를 단친으로부터 물려받아 생성하는 함수 
void GeneAlgo::toChromFromMother(Chrom *const chrom, const Chrom *const mother, const TentMap *const tentMap){
	const int numberTrees = (int) (tentMap -> NumberTrees);
	
	//염색체에 담을 공간 확보 
	if(chrom -> locus == nullptr){
			chrom -> locus = new char[numberTrees];
	}

	//모친으로부터 복사 
	for(int k=0; k < numberTrees; k++){
		chrom->locus[k] = mother->locus[k];
	}
}

//염색체를 양친으로부터 물려받아 생성하는 함수 
void GeneAlgo::toChromFromParent(Chrom *const chrom, const Chrom *const mother, const Chrom *const father, const TentMap *const tentMap){
	const int numberTrees = (int) (tentMap -> NumberTrees);
	
	//염색체에 담을 공간 확보 
	if(chrom -> locus == nullptr){
			chrom -> locus = new char[numberTrees];
	}
	
	//교차지점 선택
	int cross = rand() % (numberTrees - 1) + 1; //1부터 (numberTrees - 1)까지의 균등 분포 

	//모친으로부터 복사
	for(int k=0; k < cross; k++){
		chrom->locus[k] = mother->locus[k] ;
	}

	//부친으로부터 복사 
	for(int k=cross; k < numberTrees; k++){
		chrom->locus[k] = father->locus[k] ;
	}
}

//염색체를 돌연변이하는함수. 지점별 일정한 확률로
void GeneAlgo::toMutate(Chrom *const chrom, const float mutaRate, const TentMap *const tentMap){
	if(mutaRate <= 0) //돌연변이율이 0보다 작거나 같으면 할 일이 없다.
		return;

	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int) (tentMap -> NumberTrees);
		
	for(int k=0; k < numberTrees; k++){
		if( 1.0f / (RAND_MAX+1) * rand() < mutaRate){ //확률 난수 생성: 0부터 1까지의 균등 분포 
			switch(chrom->locus[k]){
				case (char) EnumGene::North:
					chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotNorth]();
					break;
				case (char) EnumGene::East:
					chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotEast]();
					break;
				case (char) EnumGene::South:
					chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotSouth]();
					break;
				case (char) EnumGene::West:
					chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotWest]();
					break;
			}
		}			
	}	
}

//돌연변이 1점
void GeneAlgo::toMutateSingle(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int) (tentMap -> NumberTrees);
	int k = rand() % (int) (tentMap -> NumberTrees);
	{
		switch(chrom->locus[k]){
			case (char) EnumGene::North:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotNorth]();
				break;
			case (char) EnumGene::East:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotEast]();
				break;
			case (char) EnumGene::South:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotSouth]();
				break;
			case (char) EnumGene::West:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotWest]();
				break;
		}
	}
}

//돌연변이 2점
void GeneAlgo::toMutateDouble(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int) (tentMap -> NumberTrees);
	int k = rand() % (int) (tentMap -> NumberTrees);
	int l = rand() % (int) (tentMap -> NumberTrees);
	while(k==l){
		l = rand() % (int) (tentMap -> NumberTrees);
	}
	
	{
		switch(chrom->locus[k]){
			case (char) EnumGene::North:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotNorth]();
				break;
			case (char) EnumGene::East:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotEast]();
				break;
			case (char) EnumGene::South:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotSouth]();
				break;
			case (char) EnumGene::West:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotWest]();
				break;
		}
	}
	
	{
		switch(chrom->locus[l]){
			case (char) EnumGene::North:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotNorth]();
				break;
			case (char) EnumGene::East:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotEast]();
				break;
			case (char) EnumGene::South:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotSouth]();
				break;
			case (char) EnumGene::West:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotWest]();
				break;
		}
	}
}

//돌연변이 3점
void GeneAlgo::toMutateTriple(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int) (tentMap -> NumberTrees);
	int k = rand() % (int) (tentMap -> NumberTrees);
	int l = rand() % (int) (tentMap -> NumberTrees);
	while(k==l){
		l = rand() % (int) (tentMap -> NumberTrees);
	}
	int m = rand() % (int) (tentMap -> NumberTrees);
	while(k==m || l==m){
		m = rand() % (int) (tentMap -> NumberTrees);
	}
	
	{
		switch(chrom->locus[k]){
			case (char) EnumGene::North:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotNorth]();
				break;
			case (char) EnumGene::East:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotEast]();
				break;
			case (char) EnumGene::South:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotSouth]();
				break;
			case (char) EnumGene::West:
				chrom->locus[k] = Direc::Action[treeDirection[k] & (char) EnumDirec::NotWest]();
				break;
		}
	}

	{
		switch(chrom->locus[l]){
			case (char) EnumGene::North:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotNorth]();
				break;
			case (char) EnumGene::East:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotEast]();
				break;
			case (char) EnumGene::South:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotSouth]();
				break;
			case (char) EnumGene::West:
				chrom->locus[l] = Direc::Action[treeDirection[l] & (char) EnumDirec::NotWest]();
				break;
		}
	}

	{
		switch(chrom->locus[m]){
			case (char) EnumGene::North:
				chrom->locus[m] = Direc::Action[treeDirection[m] & (char) EnumDirec::NotNorth]();
				break;
			case (char) EnumGene::East:
				chrom->locus[m] = Direc::Action[treeDirection[m] & (char) EnumDirec::NotEast]();
				break;
			case (char) EnumGene::South:
				chrom->locus[m] = Direc::Action[treeDirection[m] & (char) EnumDirec::NotSouth]();
				break;
			case (char) EnumGene::West:
				chrom->locus[m] = Direc::Action[treeDirection[m] & (char) EnumDirec::NotWest]();
				break;
		}
	}
}

//적합도
const int GeneAlgo::toFit(Chrom *const chrom, const TentMap *const tentMap){
	int fitness = 0; //적합도는 최초는 0으로 하고 깎아 나간다
	
	//충돌 처리 
	for(int c=0; c < tentMap->NumberTreeCheck; c++){
		int k = (int)(tentMap->TreeChecker[c].K);
		int l = (int)(tentMap->TreeChecker[c].L);
		auto collisMap = tentMap->TreeChecker[c].CollisMap;
		
		switch(collisMap[(int)(chrom->locus[k])][(int)(chrom->locus[l])]){
			case (char) EnumCollis::A:
				fitness -= 2; //대각선 
				break;
			case (char) EnumCollis::B:
				fitness -= 4; //직선 
				break;
			case (char) EnumCollis::C:
				fitness -= 8; //동일위치 
				break;
			case (char) EnumCollis::D:
				fitness -= 16; //텐트-나무 
		}
	}
	
	//행열당 나무개수 
	char *rowTent = new char[tentMap->Size];
	char *colTent = new char[tentMap->Size];

	for(int i=0; i < tentMap->Size; i++){
		rowTent[i]=0;
		colTent[i]=0;
	}
	
	
	for(int k=0; k < tentMap->NumberTrees; k++){
		char tentX;
		char tentY;
		tentMap->toGetTentXY(k, chrom->locus[k], &tentX, &tentY);
		rowTent[tentX] += 1;
		colTent[tentY] += 1;
	}

	for(int i=0; i < tentMap->Size; i++){
		fitness -= (rowTent[i]-tentMap->Row[i] > 0) ? 3*(rowTent[i]-tentMap->Row[i]) : -3*(rowTent[i]-tentMap->Row[i]);
		fitness -= (colTent[i]-tentMap->Col[i] > 0) ? 3*(colTent[i]-tentMap->Col[i]) : -3*(colTent[i]-tentMap->Col[i]);
	}		
	return fitness;
}

//첫 세대 만들기
void GeneAlgo::toFirstGen(const TentMap *const tentMap){
	if(Gen != NULL)
		delete[] Gen;
		
	NumberGen = 40;
	Gen = new Chrom[NumberGen];
	
	for(int g=0; g<NumberGen; g++){
		toChromFromNothing(Gen+g, tentMap);
	}
}

//세대 평가하기 
void GeneAlgo::toFitGen(const TentMap *const tentMap){
	Fmax = -0x4000000;
	Fmin = +0x4000000;
	
	if(Fitness != nullptr)
		delete[] Fitness; //이전의 적합도 배열은 지워버린다 
	Fitness = new int[NumberGen];
	
	for(int g=0; g<NumberGen;g++){
		Fitness[g] = toFit(Gen+g, tentMap);
		
		if (Fbest<Fitness[g]){
			if (Best != nullptr)
				delete Best;
			Best = new Chrom;
			toChromFromMother(Best, Gen+g, tentMap);
			Fbest = Fitness[g]; //최선의 적합도 갱신 
		}
		
		//Fbest는 전체 해의 최선이며 
		Fmax = (Fmax>Fitness[g]) ? Fmax : Fitness[g]; //Fmax는 현 세대의 전체 해의 최선이다 
		Fmin = (Fmin<Fitness[g]) ? Fmin : Fitness[g];	
	}
}

//룰렛 만들기. 룰렛휠 선택  
void GeneAlgo::toMakeRou(){
	if(Rou != nullptr)
		delete[] Rou; //이전의 룰렛 배열은 지워버린다
	NumberRou = NumberGen;
	Rou = new int[NumberRou];
	
	int pmax = 16;
	int pmin = 4;
	int sumPortion = 0;
	
	for(int g=0; g<NumberRou; g++){
		Rou[g] = sumPortion += pmin + (pmax-pmin+1)*(Fitness[g]-Fmin)/(Fmax-Fmin);
	}
}

//룰렛 만들기. 순위기반 선택  
void GeneAlgo::toMakeRouByOrder(){
	if(Rou != nullptr)
		delete[] Rou; //이전의 룰렛 배열은 지워버린다 
	NumberRou = NumberGen/4; //전체 인구의 4분의 1
	Rou = new int[NumberRou];

	int pmax = 16;
	int pmin = 4;
	int sumPortion = 0;
	for(int g=0; g<NumberRou; g++){
		Rou[g] = sumPortion += pmax + g * (pmin - pmax) / (NumberRou -1);
	}
}

//룰렛 돌려서 숫자 찾기
const int GeneAlgo::toRou(){
	int rouPoint = rand()%Rou[NumberRou-1];
	int rou=0; //리턴할 값 
	
	for(; rou<NumberRou && rouPoint >= Rou[rou]; rou++); // {} 없음 주의 

	return rou;
}

//세대 교체. 자식 세대는 부모세대가 된다.
void GeneAlgo::toReplace(){
	if(Par != nullptr)
		delete[] Par;
	
	NumberPar = NumberGen;
	Par = Gen;
	NumberGen = 0;
	Gen = nullptr;
}

//번식. 부모 세대를 바탕으로 새로운 자식 세대를 만든다.
void GeneAlgo::toReproduce(const TentMap *const tentMap){
	if(Gen != nullptr)
		delete[] Gen;
		
	NumberGen = 40;
	Gen = new Chrom[NumberGen];
	
	int sectA = 4; //서열대로 가져옴 
	int sectB = sectA + 4; //무성생식 
	
	for(int g=0; g<sectA; g++){
		toChromFromMother(Gen+g, Par+g, tentMap);
	}

	for(int g=sectA; g<sectB; g++){
		int m = toRou();
		toChromFromMother(Gen+g, Par+m, tentMap);
		
		float point = 1.0f / (RAND_MAX+1) * rand();
		if(point < .4f)
			toMutateSingle(Gen+g, tentMap);
		else if(point < .8f)
			toMutateDouble(Gen+g, tentMap);
		else
			toMutateTriple(Gen+g, tentMap);
	}

	
	for(int g=sectB; g<NumberGen; g++){
		int m = toRou();
		int f = toRou();
		toChromFromParent(Gen+g, Par+m, Par+f, tentMap);
		
		float point = 1.0f / (RAND_MAX+1) * rand();
		if(point < .4f)
			toMutateSingle(Gen+g, tentMap);
		else if(point < .8f)
			toMutateDouble(Gen+g, tentMap);
		else
			toMutateTriple(Gen+g, tentMap);
	}
}

//교대 
void GeneAlgo::toSwapGen(int g, int h){
	if(Gen != nullptr){
		char *const buffer = Gen[g].locus;
		Gen[g].locus = Gen[h].locus;
		Gen[h].locus = buffer;
	}
	if(Fitness != nullptr){
		int buffer = Fitness[g];
		Fitness[g] = Fitness[h];
		Fitness[h] = buffer;
	}
}

//퀵정렬
void GeneAlgo::toQuickSort(const int zeroth, const int llast){
	if( llast-zeroth <= 1)//1개 이하일 때 할 것이 없다 
		return;
	if( llast-zeroth == 2){//2개일 때 
		if(Fitness[zeroth] < Fitness[zeroth+1]) 
			toSwapGen(zeroth, zeroth+1);
		return;
	}
	
	int pivot = zeroth;
	int midpoint = (zeroth+llast+1)/2;//중간점
	int g = zeroth+1;
	int h = llast-1;
	
	while(g<h){
		for(; (Fitness[h]<Fitness[pivot] || (Fitness[h]==Fitness[pivot] && h>midpoint) ) && g<h; h--);
		for(; (Fitness[g]>Fitness[pivot] || (Fitness[g]==Fitness[pivot] && h<=midpoint) ) && g<h; g++);
		if(g<h && Fitness[g]<Fitness[h])
			toSwapGen(g, h);
		else if(g<h && Fitness[g]==Fitness[h])
			h--;
	}
	
	if(Fitness[g]>Fitness[pivot]){
		toSwapGen(pivot, g);
		pivot = g;
	} else if (Fitness[g]==Fitness[pivot]){
		pivot = g;
	}
	toQuickSort(zeroth, pivot);
	toQuickSort(pivot+1, llast);
}

//결과 출력
void GeneAlgo::toPrintOut(const TentMap *const tentMap){
	system("cls");
	printf("Tents And Trees Solver Ver. 0.50 by Naoever.\n");
	printf("18th January 2019.\n");
	
	printf("Solving in generation %d.\n", Generation);
	printf("Fitness %d to %d in this generation.\n", Fmax, Fmin);

	printf("The Best Gene is ");
	for(int k=0; k < tentMap->NumberTrees; k++){
		printf("%d", Best->locus[k]);
	}
	printf(" now.\nAnd its Finess is %d.\n", Fbest);

	char **const map= new char *[tentMap->Size];
	for (int i=0; i < tentMap->Size; i++){
		map[i] = new char[tentMap->Size];
		for (int j=0; j<tentMap->Size; j++){
			map[i][j] = tentMap->Map[i][j];
		}
	}

	for (int k=0; k < tentMap->NumberTrees; k++){
		char i;
		char j;
		tentMap->toGetTentXY(k, Best->locus[k], &i, &j);
		map[i][j] = 4; //4인 이유는 그냥 가장 텐트 모양과 닮아서
	}

	for (int i=0; i < tentMap->Size; i++){
		printf("  ");
		for (int j=0; j<tentMap->Size; j++){
			if ( map[i][j] > 0)
				printf("%d ", map[i][j]);
			else
				printf("_ ");
		}
		printf("\n");
	}

	for (int i=0; i<tentMap->Size; i++){
		delete[] map[i];
	}
	delete[] map;
}

//생성자
GeneAlgo::GeneAlgo(): 
	Fbest(-0x40000000), NumberGen(0), NumberPar(0), Fmax(-0x40000000), Fmin(+0x40000000), NumberRou(0), Generation(0),
	Best(nullptr), Gen(nullptr), Par(nullptr), Fitness(nullptr), Rou(nullptr){
}

//소멸자
GeneAlgo::~GeneAlgo(){
	if (Best != nullptr)
		delete Best;

	if (Gen != nullptr) 
		delete[] Gen;

	if (Par != nullptr) 
		delete[] Par;
		
	if (Fitness != nullptr) 
		delete[] Fitness;

	if (Rou != nullptr)
		delete[] Rou;
}

#endif
