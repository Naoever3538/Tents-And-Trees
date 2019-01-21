#ifndef GeneAlgo_H
#define GeneAlgo_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"

//����ü 
struct Chrom{
	public:
	//������ ��ġ�� 
	char* locus;
	
	//���� 
	char &operator[](const int i);

	//������
	Chrom();

	//�Ҹ��� 
	~Chrom();
};

//����
char &Chrom::operator[](const int i){
	return this->locus[i];
}


//������
Chrom::Chrom() : locus(NULL){
}

//�Ҹ��� 
Chrom::~Chrom(){
	if (locus != NULL)
		delete[] locus;	
}

// ������ Ǫ�� Ŭ����
class GeneAlgo {
	public:
	Chrom* Best; //������ 
	int Fbest;
	
	private:
	//����� 
	int Generation; //�� ���� ��ȣ. ù ����� 0 ������ 1 ���� 
	int NumberGen; //�� ������ �α��� 
	Chrom* Gen; //�� ����
	int NumberPar; //�θ� ������ �α��� 
	Chrom* Par; //�θ� ����
	
	//���յ��� 
	int Fmax; //
	int Fmin; //
	int *Fitness; //������ ���յ�
	
	//�귿 
	int NumberRou; // �Ʒ� �迭�� ���� 
	int *Rou; //�귿 �迭 

	
	public:
	//���������� ������ Ǫ�� �Լ� 
	void toSolve(const TentMap *const tentMap);

	//����ü�� �θ� ���� �����ϴ� �Լ� 
	void toChromFromNothing(Chrom *const chrom, const TentMap *const tentMap);

	//����ü�� ��ģ���κ��� �����޾� �����ϴ� �Լ� 
	void toChromFromMother(Chrom *const chrom, const Chrom *const mother, const TentMap *const tentMap);

	//����ü�� ��ģ���κ��� �����޾� �����ϴ� �Լ�. ��, ������ ������ 
	void toChromFromParent(Chrom *const chrom, const Chrom *const mother, const Chrom *const father, const TentMap *const tentMap);

	//����ü�� ���������ϴ��Լ�. ������ ������ Ȯ���� 
	void toMutate(Chrom *const chrom, const float mutaRate, const TentMap *const tentMap);
	
	//�������� 1��
	void toMutateSingle(Chrom *const chrom, const TentMap *const tentMap);
	
	//�������� 2�� 
	void toMutateDouble(Chrom *const chrom, const TentMap *const tentMap);
	
	//�������� 3�� 
	void toMutateTriple(Chrom *const chrom, const TentMap *const tentMap);
	
	//���յ�
	const int toFit(Chrom *const chrom, const TentMap *const tentMap);
	
	//ù ���� �����
	void toFirstGen(const TentMap *const tentMap);

	//���� ���ϱ� 
	void toFitGen(const TentMap *const tentMap);
	
	//�귿 �����. �귿�� ����  
	void toMakeRou();

	//�귿 �����. ������� ���� 
	void toMakeRouByOrder();
	
	//�귿 ������ ���� ã�� 
	const int toRou();

	//���� ��ü. �ڽ� ����� �θ𼼴밡 �ȴ�. 
	void toReplace();
	
	//����. �θ� ���븦 �������� ���ο� �ڽ� ���븦 �����.
	void toReproduce(const TentMap *const tentMap);

	//����ü�� �±���(������ ���ؼ�) 
	void toSwapGen(int g, int h);

	//������
	void toQuickSort(int zeroth, int llast);
	
	//��� ���
	void toPrintOut(const TentMap *const tentMap);

	//������
	GeneAlgo();

	//�Ҹ��� 
	~GeneAlgo();
};

//���������� ������ Ǫ�� �Լ�
void GeneAlgo::toSolve(const TentMap *const tentMap){
	//���� �ʱ�ȭ 
	srand(time(NULL));
			
	do {
		//2õ���븶�� �� ���븦 ��� ����� ���ο� ���밡 ���۵ȴ�
		if( Generation == 0 || (Generation > 2000 && Generation%2000 == 1))  
			toFirstGen(tentMap);

		//��
		toFitGen(tentMap);

		if (Fbest==0)
			break;
			
		//����
		toQuickSort(0, NumberGen);
		
		if(Generation%2000 == 0) //2õ���븶�� ���� ��Ȳ�� ����Ʈ
			toPrintOut(tentMap);
		
		//�귿 �����
		toMakeRou();
		//if(Generation == 0)
		//	toMakeRouByOrder(); //������ݼ���
		
		//���� ��ü. �ڽ� ����� �θ𼼴밡 �ȴ�.
		toReplace();
		Generation++;
		
		//����. �θ� ���븦 �������� ���ο� �ڽ� ���븦 �����.
		toReproduce(tentMap);
	} while (1);
	
	toPrintOut(tentMap);
	
	//printf("%d : %d", generation, Fmax, Fmin);
}

//����ü�� �θ� ���� �����ϴ� �Լ� 
void GeneAlgo::toChromFromNothing(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int)(tentMap -> NumberTrees);
	
	//�����ڿ� ���� ���� Ȯ��
	if(chrom -> locus == NULL){
			chrom -> locus = new char[numberTrees];
	}
	
	//�� ������ ���� �� �ִ� ������ ����Ͽ� ������ �ʱ�ȭ 
	for(int k=0; k < numberTrees; k++){
		chrom->locus[k] = Direc::Action[treeDirection[k]]();
	}
}

//����ü�� ��ģ���κ��� �����޾� �����ϴ� �Լ� 
void GeneAlgo::toChromFromMother(Chrom *const chrom, const Chrom *const mother, const TentMap *const tentMap){
	const int numberTrees = (int) (tentMap -> NumberTrees);
	
	//����ü�� ���� ���� Ȯ�� 
	if(chrom -> locus == NULL){
			chrom -> locus = new char[numberTrees];
	}

	//��ģ���κ��� ���� 
	for(int k=0; k < numberTrees; k++){
		chrom->locus[k] = mother->locus[k] ;
	}
}

//����ü�� ��ģ���κ��� �����޾� �����ϴ� �Լ� 
void GeneAlgo::toChromFromParent(Chrom *const chrom, const Chrom *const mother, const Chrom *const father, const TentMap *const tentMap){
	const int numberTrees = (int) (tentMap -> NumberTrees);
	
	//����ü�� ���� ���� Ȯ�� 
	if(chrom -> locus == NULL){
			chrom -> locus = new char[numberTrees];
	}
	
	//�������� ����
	int cross = rand() % (numberTrees - 1) + 1; //1���� (numberTrees - 1)������ �յ� ���� 

	//��ģ���κ��� ����
	for(int k=0; k < cross; k++){
		chrom->locus[k] = mother->locus[k] ;
	}

	//��ģ���κ��� ���� 
	for(int k=cross; k < numberTrees; k++){
		chrom->locus[k] = father->locus[k] ;
	}
}

//����ü�� ���������ϴ��Լ�. ������ ������ Ȯ����
void GeneAlgo::toMutate(Chrom *const chrom, const float mutaRate, const TentMap *const tentMap){
	if(mutaRate <= 0) //������������ 0���� �۰ų� ������ �� ���� ����.
		return;

	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int) (tentMap -> NumberTrees);
		
	for(int k=0; k < numberTrees; k++){
		if( 1.0f / (RAND_MAX+1) * rand() < mutaRate){ //Ȯ�� ���� ����: 0���� 1������ �յ� ���� 
			switch(chrom->locus[k]){
				case Direc::GeneNorth:
					chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectNorth]();
					break;
				case Direc::GeneEast:
					chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectEast]();
					break;
				case Direc::GeneSouth:
					chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectSouth]();
					break;
				case Direc::GeneWest:
					chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectWest]();
					break;
			}
		}			
	}	
}

//�������� 1��
void GeneAlgo::toMutateSingle(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int) (tentMap -> NumberTrees);
	int k = rand() % (int) (tentMap -> NumberTrees);
	{
		switch(chrom->locus[k]){
			case Direc::GeneNorth:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectNorth]();
				break;
			case Direc::GeneEast:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectEast]();
				break;
			case Direc::GeneSouth:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectSouth]();
				break;
			case Direc::GeneWest:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectWest]();
				break;
		}
	}
}

//�������� 2��
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
			case Direc::GeneNorth:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectNorth]();
				break;
			case Direc::GeneEast:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectEast]();
				break;
			case Direc::GeneSouth:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectSouth]();
				break;
			case Direc::GeneWest:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectWest]();
				break;
		}
	}
	
	{
		switch(chrom->locus[l]){
			case Direc::GeneNorth:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectNorth]();
				break;
			case Direc::GeneEast:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectEast]();
				break;
			case Direc::GeneSouth:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectSouth]();
				break;
			case Direc::GeneWest:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectWest]();
				break;
		}
	}
}

//�������� 3��
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
			case Direc::GeneNorth:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectNorth]();
				break;
			case Direc::GeneEast:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectEast]();
				break;
			case Direc::GeneSouth:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectSouth]();
				break;
			case Direc::GeneWest:
				chrom->locus[k] = Direc::Action[treeDirection[k] & Direc::NotDirectWest]();
				break;
		}
	}

	{
		switch(chrom->locus[l]){
			case Direc::GeneNorth:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectNorth]();
				break;
			case Direc::GeneEast:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectEast]();
				break;
			case Direc::GeneSouth:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectSouth]();
				break;
			case Direc::GeneWest:
				chrom->locus[l] = Direc::Action[treeDirection[l] & Direc::NotDirectWest]();
				break;
		}
	}

	{
		switch(chrom->locus[m]){
			case Direc::GeneNorth:
				chrom->locus[m] = Direc::Action[treeDirection[m] & Direc::NotDirectNorth]();
				break;
			case Direc::GeneEast:
				chrom->locus[m] = Direc::Action[treeDirection[m] & Direc::NotDirectEast]();
				break;
			case Direc::GeneSouth:
				chrom->locus[m] = Direc::Action[treeDirection[m] & Direc::NotDirectSouth]();
				break;
			case Direc::GeneWest:
				chrom->locus[m] = Direc::Action[treeDirection[m] & Direc::NotDirectWest]();
				break;
		}
	}
}

//���յ�
const int GeneAlgo::toFit(Chrom *const chrom, const TentMap *const tentMap){
	int fitness = 0; //���յ��� ���ʴ� 0���� �ϰ� ��� ������
	
	//�浹 ó�� 
	for(int c=0; c < tentMap->NumberTreeCheck; c++) {
		int k = (int)(tentMap->TreeChecker[c].K);
		int l = (int)(tentMap->TreeChecker[c].L);
		const char (*collisMap)[4] = tentMap->TreeChecker[c].CollisMap;
		int m = (int)(chrom->locus[k]);
		int n = (int)(chrom->locus[l]);
		
		switch(collisMap[m][n]){
			case 1:
				fitness -= 2; //�밢�� 
				break;
			case 2:
				fitness -= 4; //���� 
				break;
			case 3:
				fitness -= 8; //������ġ 
				break;
			case 4:
				fitness -= 16; //��Ʈ-���� 
		}
	}
	
	//�࿭�� �������� 
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

//ù ���� �����
void GeneAlgo::toFirstGen(const TentMap *const tentMap){
	if(Gen != NULL)
		delete[] Gen;
		
	NumberGen = 40;
	Gen = new Chrom[NumberGen];
	
	for(int g=0; g<NumberGen; g++){
		toChromFromNothing(Gen+g, tentMap);
	}
}

//���� ���ϱ� 
void GeneAlgo::toFitGen(const TentMap *const tentMap){
	Fmax = -0x4000000;
	Fmin = +0x4000000;
	
	if(Fitness != NULL)
		delete[] Fitness; //������ ���յ� �迭�� ���������� 
	Fitness = new int[NumberGen];
	
	for(int g=0; g<NumberGen;g++){
		Fitness[g] = toFit(Gen+g, tentMap);
		
		if (Fbest<Fitness[g]){
			if (Best != NULL)
				delete Best;
			Best = new Chrom;
			toChromFromMother(Best, Gen+g, tentMap);
			Fbest = Fitness[g]; //�ּ��� ���յ� ���� 
		}
		
		//Fbest�� ��ü ���� �ּ��̸� 
		Fmax = (Fmax>Fitness[g]) ? Fmax : Fitness[g]; //Fmax�� �� ������ ��ü ���� �ּ��̴� 
		Fmin = (Fmin<Fitness[g]) ? Fmin : Fitness[g];	
	}
}

//�귿 �����. �귿�� ����  
void GeneAlgo::toMakeRou(){
	if(Rou != NULL)
		delete[] Rou; //������ �귿 �迭�� ����������
	NumberRou = NumberGen;
	Rou = new int[NumberRou];
	
	int pmax = 16;
	int pmin = 4;
	int sumPortion = 0;
	
	for(int g=0; g<NumberRou; g++){
		Rou[g] = sumPortion += pmin + (pmax-pmin+1)*(Fitness[g]-Fmin)/(Fmax-Fmin);
	}
}

//�귿 �����. ������� ����  
void GeneAlgo::toMakeRouByOrder(){
	if(Rou != NULL)
		delete[] Rou; //������ �귿 �迭�� ���������� 
	NumberRou = NumberGen/4; //��ü �α��� 4���� 1
	Rou = new int[NumberRou];

	int pmax = 16;
	int pmin = 4;
	int sumPortion = 0;
	for(int g=0; g<NumberRou; g++){
		Rou[g] = sumPortion += pmax + g * (pmin - pmax) / (NumberRou -1);
	}
}

//�귿 ������ ���� ã��
const int GeneAlgo::toRou(){
	int rouPoint = rand()%Rou[NumberRou-1];
	int rou=0; //������ �� 
	
	for(; rou<NumberRou && rouPoint >= Rou[rou]; rou++); // {} ���� ���� 

	return rou;
}

//���� ��ü. �ڽ� ����� �θ𼼴밡 �ȴ�.
void GeneAlgo::toReplace(){
	if(Par != NULL)
		delete[] Par;
	
	NumberPar = NumberGen;
	Par = Gen;
	NumberGen = 0;
	Gen = NULL;
}

//����. �θ� ���븦 �������� ���ο� �ڽ� ���븦 �����.
void GeneAlgo::toReproduce(const TentMap *const tentMap){
	if(Gen != NULL)
		delete[] Gen;
		
	NumberGen = 40;
	Gen = new Chrom[NumberGen];
	
	int sectA = 4; //������� ������ 
	int sectB = sectA + 4; //�������� 
	
	for(int g=0; g<sectA; g++){
		/*
		int m = toRou();
		float mutaRate;
		if(Fitness[m] < -tentMap->NumberTrees*5)
			mutaRate = .15f;
		else if(Fitness[m] < -tentMap->NumberTrees)
			mutaRate = .03f * (-Fitness[m] / tentMap->NumberTrees); //���յ��� �������� ������������ �ö󰣴� 
		else
			mutaRate = .03f;
		toChromFromMother(Gen+g, Par+m, mutaRate, direc, tentMap);
		*/
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

//���� 
void GeneAlgo::toSwapGen(int g, int h){
	if(Gen != NULL){
		char *const buffer = Gen[g].locus;
		Gen[g].locus = Gen[h].locus;
		Gen[h].locus = buffer;
	}
	if(Fitness != NULL){
		int buffer = Fitness[g];
		Fitness[g] = Fitness[h];
		Fitness[h] = buffer;
	}
}

//������
void GeneAlgo::toQuickSort(const int zeroth, const int llast){
	if( llast-zeroth <= 1)//1�� ������ �� �� ���� ���� 
		return;
	if( llast-zeroth == 2){//2���� �� 
		if(Fitness[zeroth] < Fitness[zeroth+1]) 
			toSwapGen(zeroth, zeroth+1);
		return;
	}
	
	int pivot = zeroth;
	int midpoint = (zeroth+llast+1)/2;//�߰���
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
	} else if ((Fitness[g]==Fitness[pivot])){
		pivot = g;
	}
	toQuickSort(zeroth, pivot);
	toQuickSort(pivot+1, llast);
}

//��� ���
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
		map[i][j] = 4; //4�� ������ �׳� ���� ��Ʈ ���� ��Ƽ�
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

//������
GeneAlgo::GeneAlgo(): 
	Fbest(-0x40000000), NumberGen(0), NumberPar(0), Fmax(-0x40000000), Fmin(+0x40000000), NumberRou(0), Generation(0),
	Best(NULL), Gen(NULL), Par(NULL), Fitness(NULL), Rou(NULL){
}

//�Ҹ���
GeneAlgo::~GeneAlgo(){
	if (Best != NULL)
		delete Best;

	if (Gen != NULL) 
		delete[] Gen;

	if (Par != NULL) 
		delete[] Par;
		
	if (Fitness != NULL) 
		delete[] Fitness;

	if (Rou != NULL)
		delete[] Rou;
}
#endif
