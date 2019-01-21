#ifndef TentMap_H
#define TentMap_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Direc.h"
#include "Collis.h"

struct TreeCoordinate{
	public:
	char X; // ���ΰ� x��ǥ�̰� 
	char Y; // ���ΰ� y��ǥ�̴�. �Ϲ����� ��ǥ�Կ� �ٸ��Ƿ� ����.
	
	//������ 
	TreeCoordinate();
	 
	//�Ҹ���
	~TreeCoordinate(); 
};

//������ 
TreeCoordinate::TreeCoordinate() : X(0), Y(0){
}

//�Ҹ��� 
TreeCoordinate::~TreeCoordinate(){
}



class TreeCheck{
	public:
	char K; // üũ�ؾ��� �� ���� �� �� ������ ��ȣ 
	char L; // üũ�ؾ��� �� ���� �� �� ������ ��ȣ. �ݵ�� K < L �̾�� �Ѵ�.
	const char (*CollisMap)[4]; //�浹üũ
	
	
	//������
	TreeCheck();

	//�Ҹ���
	~TreeCheck();

	//���� 
	const char *const operator[](const int i) const;
};


//���� 
const char *const TreeCheck::operator[](const int i) const{
	return this->CollisMap[i];
}



//������ 
TreeCheck::TreeCheck() : K(0), L(0), CollisMap(NULL){
}


//�Ҹ���
TreeCheck::~TreeCheck(){
}

// Ǯ��� �ϴ� ������ ���� Ŭ����
class TentMap {
	public:
	//������ 
	//������ ���簢���� ���� �Ǵ� ���� ũ�� 
	char Size;
	 
	// ���� ���� 
	char NumberTrees;
	
	// ������ ���簢������ ��Ÿ�� �׸���. size * size �迭. 
	char **Map;
	
	// ���ο� �Ǵ� ���ο��� �־�� �ϴ� ��Ʈ�� �� 
	char *Col; //���� 
	char *Row; //���� 		
	
	//���������� x, y ��ǥ�� ���� �迭
	TreeCoordinate *Tree;
	
	// �� ������ ���� �� �ִ� ��Ʈ�� ����� ���� �迭 
	char *TreeDirection;
	
	//�浹üũ�ؾ� �ϴ� �������� �ְ� �� �浹 ����
	TreeCheck *TreeChecker;
	
	// �� �ֵ��� ����
	char NumberTreeCheck;
	
	//�Լ��� 
	
	//K��° ������ �����ڸ� ���� ��Ʈ�� X, Y��ǥ�� ��� �Լ�
	void toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const;
	
	//������. ���� �����͸� ������ �ʴ´�
	TentMap();
	
	//�б�
	void toReadFromCSV(const char *const filename);
	
	//�Ҹ��� 
	~TentMap();
};

//K��° ������ �����ڸ� ���� ��Ʈ�� X, Y��ǥ�� ��� �Լ�
void TentMap::toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const{
	if(Tree != NULL){
		TreeCoordinate *tree = &(Tree[k]);
		//X��ǥ
		switch(locus){
			case Direc::GeneSouth:
				*tentX = (tree->X < Size-1) ? (tree->X + 1) : -1;
				break;
			case Direc::GeneNorth : 
				*tentX = (tree->X > 0) ? (tree->X - 1) : -1;
				break;			
			default:
				*tentX = tree->X;
		} 
		
		//Y��ǥ
		switch(locus){
			case Direc::GeneEast :
				*tentY = (tree->Y < Size-1) ? (tree->Y + 1) : -1;
				break;
			case Direc::GeneWest :
				*tentY = (tree->Y > 0) ? (tree->Y - 1) : -1;
				break;			
			default:
				*tentY = tree->Y;
		}
	} else{
		*tentX = -1; *tentY = -1; //-1�� ������ 
	}
}


//������. ���� �����͸� ������ �ʴ´�. 
TentMap::TentMap() : 
	Size(0), NumberTrees(0), NumberTreeCheck(0), 
	Map(NULL), Row(NULL), Col(NULL), Tree(NULL), 
	TreeDirection(NULL), TreeChecker(NULL){
}

//�б�
void TentMap::toReadFromCSV(const char *const filename){
	FILE* fp = fopen(filename, "r");
	char *buffer = NULL;
	
	//������ ù���� �о� ���� ũ�⸦ ���Ѵ� 
	{
		buffer = new char[64];
		fgets(buffer, sizeof(char) * 64, fp);    
		Size = (char) atoi(buffer);
    	delete[] buffer;	
	}
	
	//������ �б�
	{
		//�� 
		Map = new char *[Size];
		for (int i=0; i<Size; i++){
			Map[i] = new char[Size];
			
			buffer = new char[64];
			fgets(buffer, sizeof(char) * 64, fp);
			
			char *ptr = strtok(buffer, ","); //�ĸ��� �������� ���ڿ��� �ڸ� 
			Map[i][0] = (char) atoi(ptr);
			
			for (int j=1; j<Size; j++){
				char *ptr = strtok(NULL, ","); //�ĸ��� �������� ���ڿ��� �ڸ� 	
				Map[i][j] = (char) atoi(ptr);
			}
	    	delete[] buffer;
		}

		//��
		{
			Col = new char[Size];
			buffer = new char[64];
			fgets(buffer, sizeof(char) * 64, fp);
					
			char *ptr = strtok(buffer, ","); //�ĸ��� �������� ���ڿ��� �ڸ� 
			Col[0] = (char) atoi(ptr);
				
			for (int j=1; j<Size; j++){
				char *ptr = strtok(NULL, ","); //�ĸ��� �������� ���ڿ��� �ڸ� 	
				Col[j] = (char) atoi(ptr);
			}
			delete[] buffer;
		}
		
		//��. �� �� ���� ������ ����Ѵ�. 
		{
			Row = new char[Size];
			NumberTrees = (char) 0;
			buffer = new char[64];
			fgets(buffer, sizeof(char) * 64, fp);
					
			char *ptr = strtok(buffer, ","); //�ĸ��� �������� ���ڿ��� �ڸ� 
			Row[0] = (char) atoi(ptr);
			NumberTrees += Row[0];
				
			for (int j=1; j<Size; j++){
				char *ptr = strtok(NULL, ","); //�ĸ��� �������� ���ڿ��� �ڸ� 	
				Row[j] = (char) atoi(ptr);
				NumberTrees += Row[j];
			}
			delete[] buffer;
		}	
	}
    fclose(fp);    // ���� ������ �ݱ�

	
	//������ ��ǥ ���ϱ�;
	{
		Tree =	new TreeCoordinate[(int)NumberTrees];
		int k = 0;
		for (int i=0; i<Size && k<(int)NumberTrees; i++){
			for (int j=0; j<Size && k<(int)NumberTrees ; j++){
				if( Map[i][j] == (char) 1 ){
					Tree[k].X = (char) i;
					Tree[k].Y = (char) j;
					//printf("Tree [%d]: x=%d, y=%d.\n", k, Tree[k].x, Tree[k].y);
					k++;
				}
			}
		}
	}

	//�������� ��Ʈ�� ���� �� �ִ� ����
	{
		TreeDirection =	new char[(int)NumberTrees];
		for (int k=0; k<(int)NumberTrees; k++){
			TreeCoordinate *tree = &(Tree[k]);
			char x = tree->X;
			char y = tree->Y;
			char direc = Direc::DirectNorthEastSouthWest; // a. k. a. 15
			
			//���� üũ
			if (x == 0 || Map[x-1][y] == 1)
				direc &= Direc::NotDirectNorth;

			//���� üũ
			if (x == Size-1 || Map[x+1][y] == 1)
				direc &= Direc::NotDirectSouth;

			//���� üũ
			if (y == 0 || Map[x][y-1] == 1)
				direc &= Direc::NotDirectWest;

			//���� üũ
			if (y == Size-1 || Map[x][y+1] == 1)
				direc &= Direc::NotDirectEast;
			
			TreeDirection[k] = direc; 
		}
	}
	
	//�浹üũ�ؾ� �ϴ� �������� �� ���ϱ�
	{
		int treeCheckerSize = (int) NumberTrees * 4;// �� ������ �浹�� �װ��� ���
		TreeChecker = new TreeCheck[treeCheckerSize];
		NumberTreeCheck = 0;
		for (int k=0; k<(int)NumberTrees-1; k++){
			for (int l=k+1; l<(int)NumberTrees; l++){
				const char (*collisMap)[4] = Collis::toGetCollisMap(Tree[k].X,Tree[k].Y, Tree[l].X, Tree[l].Y);
				if (collisMap != NULL){ 
					TreeChecker[(int) NumberTreeCheck].K = (char) k;
					TreeChecker[(int) NumberTreeCheck].L = (char) l;
					TreeChecker[(int) NumberTreeCheck].CollisMap = collisMap;
					NumberTreeCheck++;
				}
			}
		}
	}
}

//�Ҹ��� 
TentMap::~TentMap() {
	if (Map != NULL) {
		for (int i=0; i<Size; i++){
			delete[] Map[i];
		}
		delete[] Map;
	}

	if (Row != NULL) 
		delete[] Row;

	if (Col != NULL) 
		delete[] Col;

	if (Tree != NULL) 
		delete[] Tree;

	if (TreeDirection != NULL) 
		delete[] TreeDirection;

	if (TreeChecker != NULL) 
		delete[] TreeChecker;
}

#endif
