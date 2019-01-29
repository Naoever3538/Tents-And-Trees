#ifndef TentMap_H
#define TentMap_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Treecomm.h"
#include "Direc.h"
#include "TentMap.h"
#include "Collis.h"

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

#endif
