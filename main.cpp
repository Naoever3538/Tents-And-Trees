#include <stdio.h>
#include "Direc.h"
#include "Collis.h"
#include "TentMap.h"
#include "GeneAlgo.h"


int main (void) {
	TentMap tentMap;
	tentMap.toReadFromCSV("c:\\devcdata\\1414.csv");
	
	GeneAlgo geneAlgo;
	geneAlgo.toSolve(&tentMap);
	
	return 0;
}

