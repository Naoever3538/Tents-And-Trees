#ifndef Direc_Cpp
#define Direc_Cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "direc.h"

// 각 나무에 놓을 수 있는 텐트의 방향을 따라 랜덤하게 유전자(한 위치)를 생성하는 함수들
// 아무 방향도 갈 수 없을 때: (하는수 없이 북쪽을 향한다)
char Direc::toLocus(){
	return (char) EnumGene::North;
}

// 북쪽만 가능한 경우
char Direc::toLocusNorth(){
	return (char) EnumGene::North;
}

// 동쪽만 가능한 경우
char Direc::toLocusEast(){
	return (char) EnumGene::East;
}

// 북쪽과 동쪽이 가능한 경우. 이하 같다. 
char Direc::toLocusNorthEast(){
	int i=rand()%2;
	return (i==0) ? (char) EnumGene::North : (char) EnumGene::East;
}

char Direc::toLocusSouth(){
	return (char) EnumGene::South;
}

char Direc::toLocusNorthSouth(){
	int i=rand()%2;
	return (i==0) ? (char) EnumGene::North : (char) EnumGene::South;
}

char Direc::toLocusEastSouth(){
	int i=rand()%2;
	return (i==0) ?(char) EnumGene::East : (char) EnumGene::South;
}

char Direc::toLocusNorthEastSouth(){
	int i=rand()%3;
	return (i==0) ? (char) EnumGene::North : (i==1) ? (char) EnumGene::East : (char) EnumGene::South;
}

char Direc::toLocusWest(){
	return (char) EnumGene::West;
}

char Direc::toLocusNorthWest(){
	int i=rand()%2;
	return (i==0) ? (char) EnumGene::North : (char) EnumGene::West;
}

char Direc::toLocusEastWest(){
	int i=rand()%2;
	return (i==0) ?(char) EnumGene::East : (char) EnumGene::West;
}

char Direc::toLocusNorthEastWest(){
	int i=rand()%3;
	return (i==0) ? (char) EnumGene::North : (i==1) ? (char) EnumGene::East : (char) EnumGene::West;
}

char Direc::toLocusSouthWest(){
	int i=rand()%2;
	return (i==0) ? (char) EnumGene::South : (char) EnumGene::West;
}

char Direc::toLocusNorthSouthWest(){
	int i=rand()%3;
	return (i==0) ? (char) EnumGene::North : (i==1) ? (char) EnumGene::South : (char) EnumGene::West;
}

char Direc::toLocusEastSouthWest(){
	int i=rand()%3;
	return (i==0) ? (char) EnumGene::East : (i==1) ? (char) EnumGene::South : (char) EnumGene::West;
}

char Direc::toLocusNorthEastSouthWest(){
	int i=rand()%4;
	return (i==0) ? (char) EnumGene::North : (i==1) ? (char) EnumGene::East : (i==2) ? (char) EnumGene::South : (char) EnumGene::West;
}

//위 함수들의 포인터를 순차적으로 담은 배열
const Direc::ActionType Direc::Action[16] = {
	&Direc::toLocus, // 아무 방향도 갈 수 없을 때: (하는수 없이 북쪽을 향한다)
	&Direc::toLocusNorth, // 북쪽만 가능한 경우 
	&Direc::toLocusEast, // 동쪽만 가능한 경우 
	&Direc::toLocusNorthEast, // 북쪽과 동쪽이 가능한 경우. 이하 같다. 
	&Direc::toLocusSouth,
	&Direc::toLocusNorthSouth,
	&Direc::toLocusEastSouth,
	&Direc::toLocusNorthEastSouth,
	&Direc::toLocusWest,
	&Direc::toLocusNorthWest,
	&Direc::toLocusEastWest,
	&Direc::toLocusNorthEastWest,
	&Direc::toLocusSouthWest,
	&Direc::toLocusNorthSouthWest,
	&Direc::toLocusEastSouthWest,
	&Direc::toLocusNorthEastSouthWest
};

#endif
