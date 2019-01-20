#ifndef Direc_H
#define Direc_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//텐트의 방향을 담고 그 유전자(한 위치) 생성을 담당하는 클래스
//이 클래스의 핵심은 아래에 정의된 16개 함수를 담는 포인터를 만들어서 수행할 수 있게 하는 것이다.
//아래 16개 함수를 각자 하나씩 지시하는 16개의 Direc 오브젝트를 만든다.
//그 오브젝트 16개를 순차적으로 담는 길이 16의 배열을 만드는 것이 핵심이다. 

class Direc {
	private:
	//유일한 static 아닌 변수.
	char (*actionLocus)();
	
	public:
	//생성자
	Direc() : actionLocus(NULL){
	}
	
	//소멸자 
	~Direc(){
	}
	
	//지시하는 함수를 수행하여 랜덤한 수를 뱉어낸다
	char toGet() const{
		return (*actionLocus)();
	}
	
	//배열을 만들어 던지는 함수
	static const Direc* toGenerateArray(){
		Direc* array = new Direc[16];
		array[0].actionLocus = toLocus;
		array[1].actionLocus = toLocusNorth;
		array[2].actionLocus = toLocusEast;
		array[3].actionLocus = toLocusNorthEast;
		array[4].actionLocus = toLocusSouth;
		array[5].actionLocus = toLocusNorthSouth;
		array[6].actionLocus = toLocusEastSouth;
		array[7].actionLocus = toLocusNorthEastSouth;
		array[8].actionLocus = toLocusWest;
		array[9].actionLocus = toLocusNorthWest;
		array[10].actionLocus = toLocusEastWest;
		array[11].actionLocus = toLocusNorthEastWest;
		array[12].actionLocus = toLocusSouthWest;
		array[13].actionLocus = toLocusNorthSouthWest;
		array[14].actionLocus = toLocusEastSouthWest;
		array[15].actionLocus = toLocusNorthEastSouthWest;		
		return array;
	}
	
	//아래는 각종의 static 함수와 변수들이다. 
	//방향들
	static const char Direct = 0; // 아무 방향도 불가능한경우 
	static const char DirectNorth = 1; // 북쪽만 가능한 경우 
	static const char DirectEast = 2; // 동쪽만 가능한 경우 
	static const char DirectNorthEast = 3; // 북쪽과 동쪽이 가능한 경우. 이하 같다. 
	static const char DirectSouth = 4;
	static const char DirectNorthSouth = 5;
	static const char DirectEastSouth = 6;
	static const char DirectNorthEastSouth = 7;
	static const char DirectWest = 8;
	static const char DirectNorthWest = 9;
	static const char DirectEastWest = 10;
	static const char DirectNorthEastWest = 11;
	static const char DirectSouthWest = 12;
	static const char DirectNorthSouthWest = 13;
	static const char DirectEastSouthWest = 14;
	static const char DirectNorthEastSouthWest = 15; //모든방향

	//방향들의 Complement, 다 쓸 데가 있다 
	static const char NotDirect = 15; // 아무 방향도 불가능한경우 
	static const char NotDirectNorth = 14; // 북쪽만 가능한 경우 
	static const char NotDirectEast = 13; // 동쪽만 가능한 경우 
	static const char NotDirectNorthEast = 12; // 북쪽과 동쪽이 가능한 경우. 이하 같다. 
	static const char NotDirectSouth = 11;
	static const char NotDirectNorthSouth = 10;
	static const char NotDirectEastSouth = 9;
	static const char NotDirectNorthEastSouth = 8;
	static const char NotDirectWest = 7;
	static const char NotDirectNorthWest = 6;
	static const char NotDirectEastWest = 5;
	static const char NotDirectNorthEastWest = 4;
	static const char NotDirectSouthWest = 3;
	static const char NotDirectNorthSouthWest = 2;
	static const char NotDirectEastSouthWest = 1;
	static const char NotDirectNorthEastSouthWest = 0; //모든방향
	
	//각 나무에 해당하는 유전자가 지시하는 텐트 방향 
	static const char GeneNorth = 0;
	static const char GeneEast = 1;
	static const char GeneSouth = 2;
	static const char GeneWest = 3;
	
	//방향들의 수치를 받아 스트링으로 내는 함수
	#ifndef __NoNeedMnitor
	static const char * toString(const char direc){
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
};

// 아무 방향도 갈 수 없을 때: (하는수 없이 북쪽을 향한다)
char Direc::toLocus() {
	return GeneNorth;
}

// 북쪽만 가능한 경우
char Direc::toLocusNorth() { 
	return GeneNorth;
}

// 동쪽만 가능한 경우
char Direc::toLocusEast() { 
	return GeneEast;
}

// 북쪽과 동쪽이 가능한 경우. 이하 같다. 
char Direc::toLocusNorthEast() { 
	int i=rand()%2;
	return (i==0) ? GeneNorth : GeneEast;
}

char Direc::toLocusSouth() { 
	return GeneSouth;
}

char Direc::toLocusNorthSouth() { 
	int i=rand()%2;
	return (i==0) ? GeneNorth : GeneSouth;
}

char Direc::toLocusEastSouth() { 
	int i=rand()%2;
	return (i==0) ? GeneEast : GeneSouth;
}

char Direc::toLocusNorthEastSouth() { 
	int i=rand()%3;
	return (i==0) ? GeneNorth : (i==1) ? GeneEast : GeneSouth;
}

char Direc::toLocusWest() { 
	return GeneWest;
}

char Direc::toLocusNorthWest() { 
	int i=rand()%2;
	return (i==0) ? GeneNorth : GeneWest;
}

char Direc::toLocusEastWest() { 
	int i=rand()%2;
	return (i==0) ? GeneEast : GeneWest;
}

char Direc::toLocusNorthEastWest() {
	int i=rand()%3;
	return (i==0) ? GeneNorth : (i==1) ? GeneEast : GeneWest;
}

char Direc::toLocusSouthWest() { 
	int i=rand()%2;
	return (i==0) ? GeneSouth : GeneWest;
}

char Direc::toLocusNorthSouthWest() { 
	int i=rand()%3;
	return (i==0) ? GeneNorth : (i==1) ? GeneSouth : GeneWest;
}

char Direc::toLocusEastSouthWest() { 
	int i=rand()%3;
	return (i==0) ? GeneEast : (i==1) ? GeneSouth : GeneWest;
}

char Direc::toLocusNorthEastSouthWest() { 
	int i=rand()%4;
	return (i==0) ? GeneNorth : (i==1) ? GeneEast : (i==3) ? GeneSouth : GeneWest;
}
#endif
