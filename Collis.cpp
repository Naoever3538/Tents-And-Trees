#ifndef Collis_Cpp
#define Collis_Cpp

#include <stdio.h>
#include <stdlib.h>

#include "Treecomm.h"
#include "Collis.h"

const Collis::MapArrayType Collis::Collis01  = {{2,0,0,4}, {4,4,4,4}, {0,0,2,4}, {0,0,0,4}}; //두번째 나무가 첫번째 나무와 X= 0, Y= 1 차이
const Collis::MapArrayType Collis::Collis02  = {{0,0,0,1}, {1,0,0,3}, {0,0,0,1}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 0, Y= 2 차이
const Collis::MapArrayType Collis::Collis03  = {{0,0,0,0}, {0,0,0,2}, {0,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 0, Y= 3 차이
const Collis::MapArrayType Collis::Collis13n = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,1,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y=-3 차이
const Collis::MapArrayType Collis::Collis12n = {{0,0,0,0}, {0,0,0,0}, {0,2,0,0}, {2,2,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y=-2 차이
const Collis::MapArrayType Collis::Collis11n = {{1,0,0,0}, {0,1,0,0}, {1,3,1,0}, {3,1,0,1}}; //두번째 나무가 첫번째 나무와 X= 1, Y=-1 차이
const Collis::MapArrayType Collis::Collis10  = {{4,0,0,0}, {4,2,0,0}, {4,4,4,4}, {4,0,0,2}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 0 차이
const Collis::MapArrayType Collis::Collis11  = {{1,0,0,0}, {3,1,0,1}, {1,0,1,3}, {0,0,0,1}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 1 차이
const Collis::MapArrayType Collis::Collis12  = {{0,0,0,0}, {2,0,0,2}, {0,0,0,2}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 2 차이
const Collis::MapArrayType Collis::Collis13  = {{0,0,0,0}, {0,0,0,1}, {0,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 3 차이
const Collis::MapArrayType Collis::Collis22n = {{0,0,0,0}, {0,0,0,0}, {0,1,0,0}, {1,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y=-2 차이
const Collis::MapArrayType Collis::Collis21n = {{0,0,0,0}, {0,0,0,0}, {2,2,0,0}, {2,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y=-1 차이
const Collis::MapArrayType Collis::Collis20  = {{0,0,0,0}, {1,0,0,0}, {3,1,0,0}, {1,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y= 0 차이
const Collis::MapArrayType Collis::Collis21  = {{0,0,0,0}, {2,0,0,0}, {2,0,0,2}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y= 1 차이
const Collis::MapArrayType Collis::Collis22  = {{0,0,0,0}, {1,0,0,0}, {0,0,0,1}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y= 2 차이
const Collis::MapArrayType Collis::Collis31n = {{0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 3, Y=-1 차이
const Collis::MapArrayType Collis::Collis30  = {{0,0,0,0}, {0,0,0,0}, {2,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 3, Y= 0 차이
const Collis::MapArrayType Collis::Collis31  = {{0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 3, Y= 1 차이

//나무 두 개의 좌표를 받아 충돌 체크 필요성을 판정하고, 충돌맵 (char [4][4])의 주소를 리턴 
Collis::MapPointerType Collis::toGetCollisMap(const TreeCoordinate treeK, const TreeCoordinate treeL){
	switch (treeL.X - treeK.X) {
		case 0:
			switch (treeL.Y - treeK.Y) {
				case 1:
					return Collis01;
				case 2:
					return Collis02;
				case 3:
					return Collis03;
				default:
					return nullptr; //충돌하지 않음 
			}
		case 1:
			switch (treeL.Y - treeK.Y) {
				case -3:
					return Collis13n;
				case -2:
					return Collis12n;
				case -1:
					return Collis11n;
				case 0:
					return Collis10;
				case 1:
					return Collis11;
				case 2:
					return Collis12;
				case 3:
					return Collis13;
				default:
					return nullptr; //충돌하지 않음 
			}
		case 2:
			switch (treeL.Y - treeK.Y) {
				case -2:
					return Collis22n;
				case -1:
					return Collis21n;
				case 0:
					return Collis20;
				case 1:
					return Collis21;
				case 2:
					return Collis22;
				default:
					return nullptr; //충돌하지 않음 
			}
		case 3:
			switch (treeL.Y - treeK.Y) {
				case -1:
					return Collis31n;
				case 0:
					return Collis30;
				case 1:
					return Collis31;
				default:
					return nullptr; //충돌하지 않음 
			}
		default:
			return nullptr; //충돌하지 않음 
	}
}


//생성자
Collis::Collis(){
}

//소멸자
Collis::~Collis(){
}

#endif
