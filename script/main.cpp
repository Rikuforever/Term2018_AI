#include <stdio.h>

#include "Tree.h"
#include "Node.h"
#include "Data_Play.h"
#include "Data_MinMax.h"

int main(int argc, char *argv[]) {
	// Build Tree
	Tree T;
	Grid testGrid;
	Data_Play dataF(testGrid, FIRST, 1, false);
	Data_Play dataS(testGrid, SECOND, 1, false);

	
	Node N1(T); N1.Set_PlayData(dataF);
	Node N2(T); N2.Set_PlayData(dataS);
	Node N3(T); N3.Set_PlayData(dataF);
	Node N4(T); N4.Set_PlayData(dataS);
	Node N5(T); N5.Set_PlayData(dataF);

					 T.Set_Root(N1);
	N1.AddChild(N2); N1.AddChild(N3); N1.AddChild(N4);
					 N3.AddChild(N5);

					 T.PrintTree();

	system("pause");

	return 0;
}