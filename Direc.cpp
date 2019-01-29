#ifndef Direc_Cpp
#define Direc_Cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "direc.h"

// �� ������ ���� �� �ִ� ��Ʈ�� ������ ���� �����ϰ� ������(�� ��ġ)�� �����ϴ� �Լ���
// �ƹ� ���⵵ �� �� ���� ��: (�ϴ¼� ���� ������ ���Ѵ�)
char Direc::toLocus(){
	return (char) EnumGene::North;
}

// ���ʸ� ������ ���
char Direc::toLocusNorth(){
	return (char) EnumGene::North;
}

// ���ʸ� ������ ���
char Direc::toLocusEast(){
	return (char) EnumGene::East;
}

// ���ʰ� ������ ������ ���. ���� ����. 
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

//�� �Լ����� �����͸� ���������� ���� �迭
const Direc::ActionType Direc::Action[16] = {
	&Direc::toLocus, // �ƹ� ���⵵ �� �� ���� ��: (�ϴ¼� ���� ������ ���Ѵ�)
	&Direc::toLocusNorth, // ���ʸ� ������ ��� 
	&Direc::toLocusEast, // ���ʸ� ������ ��� 
	&Direc::toLocusNorthEast, // ���ʰ� ������ ������ ���. ���� ����. 
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
