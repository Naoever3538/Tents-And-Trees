#ifndef TentMap_Cpp
#define TentMap_Cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Treecomm.h"
#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"

//K��° ������ �����ڸ� ���� ��Ʈ�� X, Y��ǥ�� ��� �Լ�
void TentMap::toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const{
	if(Tree != nullptr){
		TreeCoordinate *tree = &(Tree[k]);
		//X��ǥ
		switch(locus){
			case (char) EnumGene::South:
				*tentX = (tree->X < Size-1) ? (tree->X + 1) : -1;
				break;
			case (char) EnumGene::North: 
				*tentX = (tree->X > 0) ? (tree->X - 1) : -1;
				break;			
			default:
				*tentX = tree->X;
		} 
		
		//Y��ǥ
		switch(locus){
			case (char) EnumGene::East:
				*tentY = (tree->Y < Size-1) ? (tree->Y + 1) : -1;
				break;
			case (char) EnumGene::West:
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
	Map(nullptr), Row(nullptr), Col(nullptr), Tree(nullptr), 
	TreeDirection(nullptr), TreeChecker(nullptr){
}

//�б�
void TentMap::toReadFromCSV(const char *const filename){
	FILE* fp = fopen(filename, "r");
	char *buffer = nullptr;
	
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
			char direc = (char) EnumDirec::NorthEastSouthWest; // a. k. a. 15
			
			//���� üũ
			if (x == 0 || Map[x-1][y] == 1)
				direc &= (char) EnumDirec::NotNorth;

			//���� üũ
			if (x == Size-1 || Map[x+1][y] == 1)
				direc &= (char) EnumDirec::NotSouth;

			//���� üũ
			if (y == 0 || Map[x][y-1] == 1)
				direc &= (char) EnumDirec::NotWest;

			//���� üũ
			if (y == Size-1 || Map[x][y+1] == 1)
				direc &= (char) EnumDirec::NotEast;
			
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
				auto collisMap = Collis::toGetCollisMap(Tree[k], Tree[l]);
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
TentMap::~TentMap(){
	if (Map != nullptr){
		for (int i=0; i<Size; i++){
			delete[] Map[i];
		}
		delete[] Map;
	}

	if (Row != nullptr)
		delete[] Row;

	if (Col != nullptr)
		delete[] Col;

	if (Tree != nullptr)
		delete[] Tree;

	if (TreeDirection != nullptr)
		delete[] TreeDirection;

	if (TreeChecker != nullptr)
		delete[] TreeChecker;
}

#endif
