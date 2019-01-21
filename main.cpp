#include <stdio.h>
#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"
#include "GeneAlgo.h"

#define __NoNeedMonitor 0x0000LL

int main (void) {
	TentMap tentMap;
	tentMap.toReadFromCSV("c:\\devcdata\\1.csv");
	
	GeneAlgo geneAlgo;
	geneAlgo.toSolve(&tentMap);
	
	return 0;
}

