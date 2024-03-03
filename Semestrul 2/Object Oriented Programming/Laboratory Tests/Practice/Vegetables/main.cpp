#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include "gui.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GUI gui;
	gui.show();
	return a.exec();
}
