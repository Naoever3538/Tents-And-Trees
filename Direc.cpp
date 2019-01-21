#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "direc.h"


// �ƹ� ���⵵ �� �� ���� ��: (�ϴ¼� ���� ������ ���Ѵ�)
char Direc::toLocus() {
	return GeneNorth;
}

// ���ʸ� ������ ���
char Direc::toLocusNorth() { 
	return GeneNorth;
}

// ���ʸ� ������ ���
char Direc::toLocusEast() { 
	return GeneEast;
}

// ���ʰ� ������ ������ ���. ���� ����. 
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

const Direc::TypeAction Direc::Action[16] = {
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
