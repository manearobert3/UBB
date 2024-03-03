#pragma once
#include <qwidget.h>
#include<qlineedit.h>
#include<qpushbutton.h>
#include<qstring.h>
#include<qlistview.h>
#include<qlistview.h>
#include<qvboxlayout>
#include "service.h"
#include <qlistwidget.h>
#include<qlabel.h>
#include<qformlayout.h>
#include<qstyle.h>
#include <qpalette.h>
#include <qdebug.h>
#include<qmessagebox.h>
#include "movieValidator.h"
#include "RepositoryException.h"
#include "sendtofile.h"
#include "CSVFile.h"
#include "html.h"
#include<Qtcharts/Qchartview>
#include<Qtcharts/Qbarseries>
#include<Qtcharts/qbarset>
#include<Qtcharts/qlegend>
#include<Qtcharts/qbarcategoryaxis>
#include<Qtcharts/qhorizontalStackedBarSeries>
#include<Qtcharts/Qlineseries>
#include<Qtcharts/QcategoryAxis>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QFont>
#include<qcolor>

class GraphicInterface : public QWidget {
private:
	Service serv;
	SendToFile* watchListRepo = new CSVFile{};
	SendToFile* watchListRepoCopy;
	QVBoxLayout* Layout;
	QListWidget* adminList;
	QListWidget* userList;
	QPushButton* buttonAdmin;
	QPushButton* buttonUser;
	QPushButton* buttonCSVAdmin;
	QPushButton* buttonHTMLAdmin;
	QLineEdit* search;
	QLabel* label;
	QWidget* windowChooseMode;
	QWidget* windowAdmin;
	QWidget* windowUser;
	QWidget* addToWatchlist;
	QListWidget* movieList;
	QFormLayout* optionsForAdmin;
	QPushButton* addMovieButton;
	QPushButton* removeMovieButton;
	QPushButton* updateMovieButton;
	QPushButton* yesLikeMovie;
	QPushButton* noLikeMovie;
	QLineEdit* addMovieLine ;
	QLineEdit* removeMovieLine;
	QLineEdit* updateMovieLine;
	QLineEdit* inputFileLine;
	QPushButton* inputFileButton;
	QPushButton* backButtonAdmin;
	QPushButton* backButtonUser;
	QPushButton* giveGenreButton;
	QLineEdit* giveGenreLine;
	QListWidget* listOneByOne;
	QPushButton* likeMovie;
	QPushButton* addMovieToWatchlist;
	QPushButton* nextMovie;
	QPushButton* deleteMovieFromWatchlist;
	QPushButton* likeMovieFromWatchlist;
	QListWidget* watchlist;
	QHBoxLayout* buttonsFromWatchlist;
	QLabel* movieListName;
	std::string filename = "null";
	QLineEdit* titleLine;
	QLineEdit* titleLineUpdate;
	QLineEdit* genreLine; 
	QLineEdit* genreLineUpdate;
	QLineEdit* yearLine;
	QLineEdit* yearLineUpdate;
	QLineEdit* likesLine;
	QLineEdit* likesLineUpdate;
	QLineEdit* trailerLine;
	QLineEdit* trailerLineUpdate;
	QWidget* removeInterfaceForRepo;
	QWidget* updateInterfaceForRepo;
	QWidget* addInterfaceForRepo;
	int indexForOneByOneMovie;
	bool verifyExistence = false;
	std::string genreForMovie/*= "null"*/;
	Movie selectedMovie;
	QWidget* chart;
public:
	GraphicInterface(QWidget* parent = Q_NULLPTR);
	~GraphicInterface() {};
	void populateListFromRepo();
	void createWindowUser();
	void addToWatchlistWindow();
	void populateWatchList();
	void updateAdminList();
	void createWindowAdmin();
	void createChart();
public slots:
	void verifyGenre();
	void pushButtonForAdminInterface();
	void pushButtonForUserInterface();
	void populateListForAdmin();
	void backButtonFunction();
	void addMovieToRepo();
	void addButtonForRepo();
	void removeMovieFromRepo();
	void removeMovieButtonFromRepo();
	void updateMovieFromRepo();
	void updateMovieButtonFromRepo();
	void nextMovieInLine();
	void showAddToWatchlistWindow();
	void pressedNoWatchlistPopUp();
	void pressedYesWatchlistPopUp();
	void deleteSelectedMovieFromWatchListFunction();
	void deleteMovieFromWatchListFunction(QListWidgetItem* item);
	void increaseLikeCountForMovieFromWatchlist();
	void populateListOneByOne();
	void initializeCSV();
	void initializeHTML();
	void printWatchlist();
};

