#ifndef Collis_H
#define Collis_H

#include <stdio.h>
#include <stdlib.h>

#include "Treecomm.h"

// 충돌을 판정하는 클래스. 이 클래스는 오브젝트를 만들지 않는다.
// static 아는 변수와 함수가 없다. 
class Collis{
	public:
	//생성자
	Collis();

	//소멸자 
	~Collis();
	
	typedef const char HalfMapType;
	typedef HalfMapType &HalfMapReferenceType;
	typedef HalfMapType *HalfMapPointerType;
	typedef HalfMapType HalfMapArrayType[4];
	
	typedef HalfMapArrayType MapType;
	typedef HalfMapArrayType &MapReferenceType;
	typedef MapType MapArrayType[4];
	typedef MapType *MapPointerType;

	//충돌의 패턴 
	static MapArrayType Collis01; //두번째 나무가 첫번째 나무와 X= 0, Y= 1 차이 
	static MapArrayType Collis02; //두번째 나무가 첫번째 나무와 X= 0, Y= 2 차이
	static MapArrayType Collis03; //두번째 나무가 첫번째 나무와 X= 0, Y= 3 차이
	static MapArrayType Collis13n; //두번째 나무가 첫번째 나무와 X= 1, Y=-3 차이
	static MapArrayType Collis12n; //두번째 나무가 첫번째 나무와 X= 1, Y=-2 차이
	static MapArrayType Collis11n; //두번째 나무가 첫번째 나무와 X= 1, Y=-1 차이
	static MapArrayType Collis10; //두번째 나무가 첫번째 나무와 X= 1, Y= 0 차이
	static MapArrayType Collis11; //두번째 나무가 첫번째 나무와 X= 1, Y= 1 차이
	static MapArrayType Collis12; //두번째 나무가 첫번째 나무와 X= 1, Y= 2 차이
	static MapArrayType Collis13; //두번째 나무가 첫번째 나무와 X= 1, Y= 3 차이
	static MapArrayType Collis22n; //두번째 나무가 첫번째 나무와 X= 2, Y=-2 차이
	static MapArrayType Collis21n; //두번째 나무가 첫번째 나무와 X= 2, Y=-1 차이
	static MapArrayType Collis20; //두번째 나무가 첫번째 나무와 X= 2, Y= 0 차이
	static MapArrayType Collis21; //두번째 나무가 첫번째 나무와 X= 2, Y= 1 차이
	static MapArrayType Collis22; //두번째 나무가 첫번째 나무와 X= 2, Y= 2 차이
	static MapArrayType Collis31n; //두번째 나무가 첫번째 나무와 X= 3, Y=-1 차이
	static MapArrayType Collis30; //두번째 나무가 첫번째 나무와 X= 3, Y= 0 차이
	static MapArrayType Collis31; //두번째 나무가 첫번째 나무와 X= 3, Y= 1 차이
	
	//나무 두 개의 좌표를 받아 충돌 체크 필요성을 판정하고, 충돌맵 (char [4][4])의 주소를 리턴 
	static MapPointerType toGetCollisMap(const TreeCoordinate treeK, const TreeCoordinate treeL);
};

#endif
