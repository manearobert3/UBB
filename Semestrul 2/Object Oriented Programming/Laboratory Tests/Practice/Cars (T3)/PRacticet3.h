#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PRacticet3.h"
#include "Service.h"


class PRacticet3 : public QMainWindow
{
    Q_OBJECT

public:
    PRacticet3(Service& service, QWidget *parent = nullptr);
    ~PRacticet3();

private:
    Ui::PRacticet3Class ui;

	Service& service;
	QListWidget* carListWidget;
	void connectSignalAndSlots();
	int getSelectedIndex() const;
	void populateAllCarsList();
	void populateOldCarsList();

	void addCarGUI();
	void deleteCarGUI();
	void listAllCarsGUI();
	void updateCarGUI();
};
