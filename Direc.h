#ifndef Direc_H
#define Direc_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Treecomm.h"

//텐트의 방향을 담고 그 유전자(한 위치) 생성을 담당하는 클래스.
//이 클래스의 핵심은 아래에 정의된 16개 함수를 담는 포인터의 배열를 만들어서 수행할 수 있게 하는 것이다.
//이제 더이상 오브젝트를 만들지 않고 Direc::Action 배열을 통해 접근할 수 있다.
//더이상 클래스의 오브젝트를 생성할 필요가 없다.
class Direc {
	//private:
	//유일한 static 아닌 변수.
	//char (*actionLocus)();
	
	public:
	//생성자
	Direc(){
	}
	
	//소멸자 
	~Direc(){
	}
			
	#ifndef __NoNeedMonitor
	//방향들의 수치를 받아 스트링으로 내는 함수
	static const char *toString(const char direc){
		switch (direc){
			case 0:
				return "No Direction";
			case 1:
				return "North";
			case 2:
				return "East";
			case 3:
				return "North East";
			case 4:
				return "South";
			case 5:
				return "North South";
			case 6:
				return "East South";
			case 7:
				return "North East South";
			case 8:
				return "West";
			case 9:
				return "North West";
			case 10:
				return "East West";
			case 11:
				return "North East West";
			case 12:
				return "South West";
			case 13:
				return "North South West";
			case 14:
				return "East South West";
			case 15:
				return "North East South West";
		}
	}
	#endif

	// 각 나무에 놓을 수 있는 텐트의 방향을 따라 랜덤하게 유전자(한 위치)를 생성하는 함수들
	static char toLocus(); // 아무 방향도 갈 수 없을 때: (하는수 없이 북쪽을 향한다)
	static char toLocusNorth(); // 북쪽만 가능한 경우 
	static char toLocusEast(); // 동쪽만 가능한 경우 
	static char toLocusNorthEast(); // 북쪽과 동쪽이 가능한 경우. 이하 같다. 
	static char toLocusSouth();
	static char toLocusNorthSouth();
	static char toLocusEastSouth();
	static char toLocusNorthEastSouth();
	static char toLocusWest();
	static char toLocusNorthWest();
	static char toLocusEastWest();
	static char toLocusNorthEastWest();
	static char toLocusSouthWest();
	static char toLocusNorthSouthWest();
	static char toLocusEastSouthWest();
	static char toLocusNorthEastSouthWest(); //모든방향
	
	//위 함수들의 포인터를 순차적으로 담은 배열 
	typedef char (*ActionType)();
	static const ActionType Action[16];
};
#endif
