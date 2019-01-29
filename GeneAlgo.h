#ifndef GeneAlgo_H
#define GeneAlgo_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Treecomm.h"
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

	//����
	const char operator[](const int i) const;

	//������
	Chrom();

	//�Ҹ��� 
	~Chrom();
};

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
#endif
