#include <stdio.h>

#include "Data_Play.h"

int main(int argc, char *argv[]) {
	Grid testGrid;
	Data_Play data(testGrid, FIRST, 1, false);

	printf("%d", data.Get_Grid()[0][0]);

	Grid& helloGrid = data.Get_Grid();
	helloGrid[0][0] = FIRST;
	printf("%d", data.Get_Grid()[0][0]);

	system("pause");

	return 0;
}