#ifndef GeneAlgo_Cpp 
#define GeneAlgo_Cpp

#include <stdio.h>

#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"
#include "GeneAlgo.h"

//class chrom
//����
char &Chrom::operator[](const int i){
	return this->locus[i];
}

const char Chrom::operator[](const int i) const{
	return this->locus[i];
}

//������
Chrom::Chrom() : locus(nullptr){
}

//�Ҹ���
Chrom::~Chrom(){
	if (locus != nullptr)
		delete[] locus;	
}

//class GeneAlgo
//���������� ������ Ǫ�� �Լ�
void GeneAlgo::toSolve(const TentMap *const tentMap){
	//���� �ʱ�ȭ 
	srand(time(nullptr));
			
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
		
		//���� ��ü. �ڽ� ����� �θ𼼴밡 �ȴ�.
		toReplace();
		Generation++;
		
		//����. �θ� ���븦 �������� ���ο� �ڽ� ���븦 �����.
		toReproduce(tentMap);
	} while (1);
	
	toPrintOut(tentMap);
}

//����ü�� �θ� ���� �����ϴ� �Լ� 
void GeneAlgo::toChromFromNothing(Chrom *const chrom, const TentMap *const tentMap){
	const char* const treeDirection = tentMap -> TreeDirection;
	const int numberTrees = (int)(tentMap -> NumberTrees);
	
	//�����ڿ� ���� ���� Ȯ��
	if(chrom -> locus == nullptr){
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
	if(chrom -> locus == nullptr){
			chrom -> locus = new char[numberTrees];
	}

	//��ģ���κ��� ���� 
	for(int k=0; k < numberTrees; k++){
		chrom->locus[k] = mother->locus[k];
	}
}

//����ü�� ��ģ���κ��� �����޾� �����ϴ� �Լ� 
void GeneAlgo::toChromFromParent(Chrom *const chrom, const Chrom *const mother, const Chrom *const father, const TentMap *const tentMap){
	const int numberTrees = (int) (tentMap -> NumberTrees);
	
	//����ü�� ���� ���� Ȯ�� 
	if(chrom -> locus == nullptr){
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

//�������� 1��
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

//���յ�
const int GeneAlgo::toFit(Chrom *const chrom, const TentMap *const tentMap){
	int fitness = 0; //���յ��� ���ʴ� 0���� �ϰ� ��� ������
	
	//�浹 ó�� 
	for(int c=0; c < tentMap->NumberTreeCheck; c++){
		int k = (int)(tentMap->TreeChecker[c].K);
		int l = (int)(tentMap->TreeChecker[c].L);
		auto collisMap = tentMap->TreeChecker[c].CollisMap;
		
		switch(collisMap[(int)(chrom->locus[k])][(int)(chrom->locus[l])]){
			case (char) EnumCollis::A:
				fitness -= 2; //�밢�� 
				break;
			case (char) EnumCollis::B:
				fitness -= 4; //���� 
				break;
			case (char) EnumCollis::C:
				fitness -= 8; //������ġ 
				break;
			case (char) EnumCollis::D:
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
	
	if(Fitness != nullptr)
		delete[] Fitness; //������ ���յ� �迭�� ���������� 
	Fitness = new int[NumberGen];
	
	for(int g=0; g<NumberGen;g++){
		Fitness[g] = toFit(Gen+g, tentMap);
		
		if (Fbest<Fitness[g]){
			if (Best != nullptr)
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
	if(Rou != nullptr)
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
	if(Rou != nullptr)
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
	if(Par != nullptr)
		delete[] Par;
	
	NumberPar = NumberGen;
	Par = Gen;
	NumberGen = 0;
	Gen = nullptr;
}

//����. �θ� ���븦 �������� ���ο� �ڽ� ���븦 �����.
void GeneAlgo::toReproduce(const TentMap *const tentMap){
	if(Gen != nullptr)
		delete[] Gen;
		
	NumberGen = 40;
	Gen = new Chrom[NumberGen];
	
	int sectA = 4; //������� ������ 
	int sectB = sectA + 4; //�������� 
	
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

//���� 
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
	} else if (Fitness[g]==Fitness[pivot]){
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
	Best(nullptr), Gen(nullptr), Par(nullptr), Fitness(nullptr), Rou(nullptr){
}

//�Ҹ���
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
