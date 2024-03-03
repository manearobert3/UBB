#include <iostream>
#include <Windows.h>
#include <string>
#include "Header.h"
#include <crtdbg.h>
#include "service.h"
#include "UI.h"
#include"test.h"

int main()
{
	Test::testRepository();
	Test::testMovie();
	system("color d0");
	Repository repo{};
	Service serv{ repo };
	UI ui{ serv };
	ui.mainProgram();
	_CrtDumpMemoryLeaks();

}