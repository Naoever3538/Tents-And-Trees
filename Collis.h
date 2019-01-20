#ifndef Collis_H
#define Collis_H

#include <stdio.h>
#include <stdlib.h>

// 충돌을 판정하는 클래스. 이 클래스는 오브젝트를 만들지 않는다.
// static 아는 변수와 함수가 없다. 
class Collis{
	public:
	//생성자
	Collis();

	//소멸자 
	~Collis();

	//각 나무에 해당하는 유전자가 지시하는 텐트 방향
	static const char GeneNorth = 0;
	static const char GeneEast  = 1;
	static const char GeneSouth = 2;
	static const char GeneWest  = 3;


	//충돌의 종류. 수치가 높으면 큰 충돌이다
	static const char Zero = 0; //충돌이 없다 
	static const char A = 1; // 텐트-텐트 대각선 충돌 
	static const char B = 2; // 텐트-텐트 좌우상하 출동 
	static const char C = 3; // 텐트-텐트 동일위치 충돌 
	static const char D = 4; // 텐트-나무 동일위치 충돌
		
	//충돌의 패턴 
	static const char Collis01 [4][4]; //두번째 나무가 첫번째 나무와 X= 0, Y= 1 차이 
	static const char Collis02 [4][4]; //두번째 나무가 첫번째 나무와 X= 0, Y= 2 차이
	static const char Collis03 [4][4]; //두번째 나무가 첫번째 나무와 X= 0, Y= 3 차이
	static const char Collis13n[4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y=-3 차이
	static const char Collis12n[4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y=-2 차이
	static const char Collis11n[4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y=-1 차이
	static const char Collis10 [4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y= 0 차이
	static const char Collis11 [4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y= 1 차이
	static const char Collis12 [4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y= 2 차이
	static const char Collis13 [4][4]; //두번째 나무가 첫번째 나무와 X= 1, Y= 3 차이
	static const char Collis22n[4][4]; //두번째 나무가 첫번째 나무와 X= 2, Y=-2 차이
	static const char Collis21n[4][4]; //두번째 나무가 첫번째 나무와 X= 2, Y=-1 차이
	static const char Collis20 [4][4]; //두번째 나무가 첫번째 나무와 X= 2, Y= 0 차이
	static const char Collis21 [4][4]; //두번째 나무가 첫번째 나무와 X= 2, Y= 1 차이
	static const char Collis22 [4][4]; //두번째 나무가 첫번째 나무와 X= 2, Y= 2 차이
	static const char Collis31n[4][4]; //두번째 나무가 첫번째 나무와 X= 3, Y=-1 차이
	static const char Collis30 [4][4]; //두번째 나무가 첫번째 나무와 X= 3, Y= 0 차이
	static const char Collis31 [4][4]; //두번째 나무가 첫번째 나무와 X= 3, Y= 1 차이
	
	//나무 두 개의 좌표를 받아 충돌 체크 필요성을 판정하고, 충돌맵 (char [4][4])의 주소를 리턴 
	static const char (*toGetCollisMap (const char kX, const char kY, const char lX, const char lY))[4]{
		switch (lX - kX) {
			case 0:
				switch (lY - kY) {
					case 1:
						return Collis01;
					case 2:
						return Collis02;
					case 3:
						return Collis03;
					default:
						return NULL; //충돌하지 않음 
				}
			case 1:
				switch (lY - kY) {
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
						return NULL; //충돌하지 않음 
				}
			case 2:
				switch (lY - kY) {
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
						return NULL; //충돌하지 않음 
				}
			case 3:
				switch (lY - kY) {
					case -1:
						return Collis31n;
					case 0:
						return Collis30;
					case 1:
						return Collis31;
					default:
						return NULL; //충돌하지 않음 
				}
			default:
				return NULL;
		}
	}
};

const char Collis::Collis01 [4][4] = {{2,0,0,4}, {4,4,4,4}, {0,0,2,4}, {0,0,0,4}}; //두번째 나무가 첫번째 나무와 X= 0, Y= 1 차이
const char Collis::Collis02 [4][4] = {{0,0,0,0}, {0,0,0,3}, {0,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 0, Y= 2 차이
const char Collis::Collis03 [4][4] = {{0,0,0,0}, {0,0,0,2}, {0,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 0, Y= 3 차이
const char Collis::Collis13n[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,1,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y=-3 차이
const char Collis::Collis12n[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,2,0,0}, {2,2,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y=-2 차이
const char Collis::Collis11n[4][4] = {{1,0,0,0}, {0,1,0,0}, {1,3,1,0}, {3,1,0,1}}; //두번째 나무가 첫번째 나무와 X= 1, Y=-1 차이
const char Collis::Collis10 [4][4] = {{4,0,0,0}, {4,2,0,0}, {4,4,4,4}, {4,0,0,2}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 0 차이
const char Collis::Collis11 [4][4] = {{1,0,0,0}, {3,1,0,1}, {1,0,1,3}, {0,0,0,1}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 1 차이
const char Collis::Collis12 [4][4] = {{0,0,0,0}, {2,0,0,2}, {0,0,0,2}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 2 차이
const char Collis::Collis13 [4][4] = {{0,0,0,0}, {0,0,0,1}, {0,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 1, Y= 3 차이
const char Collis::Collis22n[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,1,0,0}, {1,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y=-2 차이
const char Collis::Collis21n[4][4] = {{0,0,0,0}, {0,0,0,0}, {2,2,0,0}, {2,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y=-1 차이
const char Collis::Collis20 [4][4] = {{0,0,0,0}, {0,0,0,0}, {3,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y= 0 차이
const char Collis::Collis21 [4][4] = {{0,0,0,0}, {2,0,0,0}, {2,0,0,2}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y= 1 차이
const char Collis::Collis22 [4][4] = {{0,0,0,0}, {1,0,0,0}, {0,0,0,1}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 2, Y= 2 차이
const char Collis::Collis31n[4][4] = {{0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 3, Y=-1 차이
const char Collis::Collis30 [4][4] = {{0,0,0,0}, {0,0,0,0}, {2,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 3, Y= 0 차이
const char Collis::Collis31 [4][4] = {{0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //두번째 나무가 첫번째 나무와 X= 3, Y= 1 차이

//생성자
Collis::Collis(){
}

//소멸자
Collis::~Collis(){
}

#endif
