#pragma once
#include "Service.h"

typedef struct {
	Service* service;
}Ui;

Ui* createUi(Service* service);

void destroyUi(Ui*);

void startMenu(Ui*);