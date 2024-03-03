#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Repository.h"
#include "Service.h"
#include "ui.h"
#include "DynamicArray.h"

int main()
{
	//testDynamicArray();
	//testRepository();
	//testOffer();
	//testService(); 
	Repository* repo = createRepo();
	Service* ctrl = createService(repo);
	Ui* ui = createUi(ctrl);
	startMenu(ui);
	destroyUi(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}

