#ifndef TentMap_Cpp
#define TentMap_Cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Treecomm.h"
#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"

//K번째 나무와 유전자를 통해 텐트의 X, Y좌표를 얻는 함수
void TentMap::toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const{
	if(Tree != nullptr){
		TreeCoordinate *tree = &(Tree[k]);
		//X좌표
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
		
		//Y좌표
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
		*tentX = -1; *tentY = -1; //-1은 오류값 
	}
}


//생성자. 문제 데이터를 읽지는 않는다. 
TentMap::TentMap() : 
	Size(0), NumberTrees(0), NumberTreeCheck(0), 
	Map(nullptr), Row(nullptr), Col(nullptr), Tree(nullptr), 
	TreeDirection(nullptr), TreeChecker(nullptr){
}

//읽기
void TentMap::toReadFromCSV(const char *const filename){
	FILE* fp = fopen(filename, "r");
	char *buffer = nullptr;
	
	//파일의 첫줄을 읽어 맵의 크기를 구한다 
	{
		buffer = new char[64];
		fgets(buffer, sizeof(char) * 64, fp);    
		Size = (char) atoi(buffer);
    	delete[] buffer;
	}
	
	//내용을 읽기
	{
		//맵 
		Map = new char *[Size];
		for (int i=0; i<Size; i++){
			Map[i] = new char[Size];
			
			buffer = new char[64];
			fgets(buffer, sizeof(char) * 64, fp);
			
			char *ptr = strtok(buffer, ","); //컴마를 기준으로 문자열을 자름 
			Map[i][0] = (char) atoi(ptr);
			
			for (int j=1; j<Size; j++){
				char *ptr = strtok(NULL, ","); //컴마를 기준으로 문자열을 자름 	
				Map[i][j] = (char) atoi(ptr);
			}
	    	delete[] buffer;
		}

		//열
		{
			Col = new char[Size];
			buffer = new char[64];
			fgets(buffer, sizeof(char) * 64, fp);
					
			char *ptr = strtok(buffer, ","); //컴마를 기준으로 문자열을 자름 
			Col[0] = (char) atoi(ptr);
				
			for (int j=1; j<Size; j++){
				char *ptr = strtok(NULL, ","); //컴마를 기준으로 문자열을 자름 	
				Col[j] = (char) atoi(ptr);
			}
			delete[] buffer;
		}
		
		//행. 이 때 나무 갯수를 계산한다. 
		{
			Row = new char[Size];
			NumberTrees = (char) 0;
			buffer = new char[64];
			fgets(buffer, sizeof(char) * 64, fp);
					
			char *ptr = strtok(buffer, ","); //컴마를 기준으로 문자열을 자름 
			Row[0] = (char) atoi(ptr);
			NumberTrees += Row[0];
				
			for (int j=1; j<Size; j++){
				char *ptr = strtok(NULL, ","); //컴마를 기준으로 문자열을 자름 	
				Row[j] = (char) atoi(ptr);
				NumberTrees += Row[j];
			}
			delete[] buffer;
		}	
	}
    fclose(fp);    // 파일 포인터 닫기

	
	//나무의 좌표 구하기;
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

	//나무들이 텐트를 놓을 수 있는 방향
	{
		TreeDirection =	new char[(int)NumberTrees];
		for (int k=0; k<(int)NumberTrees; k++){
			TreeCoordinate *tree = &(Tree[k]);
			char x = tree->X;
			char y = tree->Y;
			char direc = (char) EnumDirec::NorthEastSouthWest; // a. k. a. 15
			
			//북쪽 체크
			if (x == 0 || Map[x-1][y] == 1)
				direc &= (char) EnumDirec::NotNorth;

			//남쪽 체크
			if (x == Size-1 || Map[x+1][y] == 1)
				direc &= (char) EnumDirec::NotSouth;

			//서쪽 체크
			if (y == 0 || Map[x][y-1] == 1)
				direc &= (char) EnumDirec::NotWest;

			//동쪽 체크
			if (y == Size-1 || Map[x][y+1] == 1)
				direc &= (char) EnumDirec::NotEast;
			
			TreeDirection[k] = direc; 
		}
	}
	
	//충돌체크해야 하는 나무들의 쌍 구하기
	{
		int treeCheckerSize = (int) NumberTrees * 4;// 한 나무당 충돌이 네개면 충분
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

//소멸자 
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
