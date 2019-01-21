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
	char X; // 가로가 x좌표이고 
	char Y; // 세로가 y좌표이다. 일반적인 좌표게와 다르므로 주의.
	
	//생성자 
	TreeCoordinate();
	 
	//소멸자
	~TreeCoordinate(); 
};

//생성자 
TreeCoordinate::TreeCoordinate() : X(0), Y(0){
}

//소멸자 
TreeCoordinate::~TreeCoordinate(){
}



class TreeCheck{
	public:
	char K; // 체크해야할 두 나무 중 앞 나무의 번호 
	char L; // 체크해야할 두 나무 중 뒤 나무의 번호. 반드시 K < L 이어야 한다.
	const char (*CollisMap)[4]; //충돌체크
	
	
	//생성자
	TreeCheck();

	//소멸자
	~TreeCheck();

	//접근 
	const char *const operator[](const int i) const;
};


//접근 
const char *const TreeCheck::operator[](const int i) const{
	return this->CollisMap[i];
}



//생성자 
TreeCheck::TreeCheck() : K(0), L(0), CollisMap(NULL){
}


//소멸자
TreeCheck::~TreeCheck(){
}

// 풀어야 하는 문제를 담은 클래스
class TentMap {
	public:
	//변수들 
	//문제의 정사각형의 가로 또는 세로 크기 
	char Size;
	 
	// 나무 개수 
	char NumberTrees;
	
	// 문제를 정사각형으로 나타낸 그림들. size * size 배열. 
	char **Map;
	
	// 가로열 또는 세로열에 있어야 하는 텐트의 수 
	char *Col; //세로 
	char *Row; //가로 		
	
	//각나무들의 x, y 좌표를 담은 배열
	TreeCoordinate *Tree;
	
	// 각 나무에 놓을 수 있는 텐트의 방향들 담은 배열 
	char *TreeDirection;
	
	//충돌체크해야 하는 나무들의 쌍과 그 충돌 패턴
	TreeCheck *TreeChecker;
	
	// 그 쌍들의 갯수
	char NumberTreeCheck;
	
	//함수들 
	
	//K번째 나무와 유전자를 통해 텐트의 X, Y좌표를 얻는 함수
	void toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const;
	
	//생성자. 문제 데이터를 읽지는 않는다
	TentMap();
	
	//읽기
	void toReadFromCSV(const char *const filename);
	
	//소멸자 
	~TentMap();
};

//K번째 나무와 유전자를 통해 텐트의 X, Y좌표를 얻는 함수
void TentMap::toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const{
	if(Tree != NULL){
		TreeCoordinate *tree = &(Tree[k]);
		//X좌표
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
		
		//Y좌표
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
		*tentX = -1; *tentY = -1; //-1은 오류값 
	}
}


//생성자. 문제 데이터를 읽지는 않는다. 
TentMap::TentMap() : 
	Size(0), NumberTrees(0), NumberTreeCheck(0), 
	Map(NULL), Row(NULL), Col(NULL), Tree(NULL), 
	TreeDirection(NULL), TreeChecker(NULL){
}

//읽기
void TentMap::toReadFromCSV(const char *const filename){
	FILE* fp = fopen(filename, "r");
	char *buffer = NULL;
	
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
					//printf("Tree [%d]: x=%d, y=%d.\n", k, Tree[k].x, Tree[k].y);
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
			char direc = Direc::DirectNorthEastSouthWest; // a. k. a. 15
			
			//북쪽 체크
			if (x == 0 || Map[x-1][y] == 1)
				direc &= Direc::NotDirectNorth;

			//남쪽 체크
			if (x == Size-1 || Map[x+1][y] == 1)
				direc &= Direc::NotDirectSouth;

			//서쪽 체크
			if (y == 0 || Map[x][y-1] == 1)
				direc &= Direc::NotDirectWest;

			//동쪽 체크
			if (y == Size-1 || Map[x][y+1] == 1)
				direc &= Direc::NotDirectEast;
			
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

//소멸자 
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
