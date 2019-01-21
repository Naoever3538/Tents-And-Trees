#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "direc.h"


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

const Direc::TypeAction Direc::Action[16] = {
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
