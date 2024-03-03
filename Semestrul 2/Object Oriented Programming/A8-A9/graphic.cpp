#include "graphic.h"



GraphicInterface::GraphicInterface(QWidget* parent)
{
	selectedMovie.setTitle("null");
	Layout = new QVBoxLayout();
	buttonAdmin = new QPushButton("Admin Mode");
	buttonUser = new QPushButton("User Mode");
	windowAdmin = new QWidget();
	windowUser = new QWidget();
	addToWatchlist = new QWidget();
	chart = new QWidget();
	QPushButton* showChart = new QPushButton("Show Chart");
	this->setLayout(Layout);
	Layout->addWidget(buttonAdmin);
	Layout->addWidget(buttonUser);
	Layout->addWidget(showChart);
	watchListRepo->setName("moviescsv.csv");
	createWindowUser();
	createWindowAdmin();
	addToWatchlistWindow();
	QObject::connect(this->buttonAdmin, &QPushButton::clicked, this, &GraphicInterface::pushButtonForAdminInterface);
	QObject::connect(this->buttonUser, &QPushButton::clicked, this, &GraphicInterface::pushButtonForUserInterface);
	QObject::connect(showChart, &QPushButton::clicked, this, &GraphicInterface::createChart);
	
}

void GraphicInterface::printWatchlist() {
	try {
		if (watchListRepo->getSize() == 0) {
			QMessageBox::warning(this, "Exception", "There is nothing to display.");

		}
		else {
			watchListRepo->printSpecificFile();
			watchListRepo->displayMovies();
		}

	}
	catch (FileException& exception) {
		QMessageBox::warning(this, "Exception", exception.what());
	}
}

//void GraphicInterface::createChart() {
//	int maxCount = -123;
//	QChart* mainChart = new QChart();
//	mainChart->setTitle("The genres");
//	mainChart->setAnimationOptions(QChart::AllAnimations);
//	QVBoxLayout* chartLayout = new QVBoxLayout();
//	chart->setLayout(chartLayout);
//	QStringList listOfGenre;
//	QBarCategoryAxis* axis =new QBarCategoryAxis();
//	QMap<std::string, int> uniqueGenresCount;
//	for (auto movie : this->serv.getAll()) {
//		uniqueGenresCount[movie.getGenre()]++;
//	}
//	for (const int count : uniqueGenresCount.values()) {
//		if (count > maxCount) {
//			maxCount = count;
//		}
//	}
//	for (int index = 0; index < uniqueGenresCount.size(); ++index)
//	{	
//		std::string genre = uniqueGenresCount.keys().value(index);
//		QString genreQString = QString::fromStdString(genre);
//		listOfGenre << genreQString;
//	}
//	axis->append(listOfGenre);
//	mainChart->createDefaultAxes();
//	QBarSeries* series = new QBarSeries();
//	for (int index = 0; index < uniqueGenresCount.size(); ++index) {
//		std::string genre = uniqueGenresCount.keys().value(index);
//		QString genreQString = QString::fromStdString(genre);
//		int count = uniqueGenresCount.value(genre);
//		int barHeight = chartHeight * count / maxCount; // Calculate the height of each bar
//
//		 Create a rectangle item for the bar
//		QBarSet* line = new QBarSet(genreQString);
//		*line << count;
//
//		series->append(line);
//		mainChart->addSeries(series);
//		QGraphicsRectItem* bar = new QGraphicsRectItem(startX, startY - barHeight, barWidth, barHeight);
//		bar->setBrush(Qt::blue); // Set the bar color
//
//		 Add the bar to the scene
//		scene->addItem(bar);
//
//		 Move to the next position
//		startX += barWidth + gap;
//	}
//	mainChart->setAxisX(axis, series);
//	mainChart->legend()->setVisible(true);
//	mainChart->legend()->setAlignment(Qt::AlignBottom);
//	QChartView* view = new QChartView(mainChart);
//	view->setRenderHint(QPainter::Antialiasing);
//	QPalette palett = qApp->palette();
//	palett.setColor(QPalette::Window, QRgb(0xfffff));
//	palett.setColor(QPalette::WindowText, QRgb(0x988878));
//	qApp->setPalette(palett);
//	chartLayout->addWidget(view);
//
//
//	chart->setLayout(chartLayout);
//	chartLayout->addWidget(view);
//	chart->setLayout(chartLayout);
//	chart->show();
//}


void GraphicInterface::createChart() {
	chart->deleteLater();
	chart = new QWidget();
	int maxCount = 0;
	QChart* mainChart = new QChart();
	mainChart->setTitle("The genres");
	mainChart->setAnimationOptions(QChart::AllAnimations);

	QVBoxLayout* chartLayout = new QVBoxLayout();

	QStringList listOfGenre;
	QMap<QString, int> uniqueGenresCount;
	QMap<std::string, int> uniqueGenresCountString;
	for (auto movie : this->serv.getAll()) {
		QString genre = QString::fromStdString(movie.getGenre());
		if (!uniqueGenresCount.contains(genre)) {
			uniqueGenresCount[genre] = 1;
		}
		else
			uniqueGenresCount[genre]++;
	}
	for (int index = 0; index < uniqueGenresCount.size(); index++) {
		QString genreAcm = uniqueGenresCount.keys().at(index);
	}
	QBarCategoryAxis* axis = new QBarCategoryAxis();
	axis->append(uniqueGenresCount.keys());
	axis->hide();
	//mainChart->addAxis(axis, Qt::AlignBottom);

	QBarSeries* series = new QBarSeries();

	for (auto genre : uniqueGenresCount.keys()) {
		int count = uniqueGenresCount.value(genre);
		if (count > maxCount) {
			maxCount = count;
		}
		QBarSet* barSet = new QBarSet(genre);
		*barSet << count;
		series->append(barSet);
	}
	
	QValueAxis* valueAxis = new QValueAxis();
	valueAxis->setRange(0, maxCount);
	valueAxis->setTickCount(1);
	mainChart->setAxisY(valueAxis);
	series->attachAxis(valueAxis);
	mainChart->addSeries(series);

	mainChart->legend()->setVisible(true);
	mainChart->legend()->setAlignment(Qt::AlignTop);

	mainChart->setTheme(QChart::ChartThemeLight);

	QChartView* view = new QChartView(mainChart);
	view->setRenderHint(QPainter::Antialiasing);

	chartLayout->addWidget(view);
	chart->setLayout(chartLayout);
	chart->resize(500, 400);
	chart->show();
}



void GraphicInterface::initializeCSV() {
	//watchListRepoCopy.clear();
	try {
		watchListRepoCopy = new CSVFile{};
		for (auto movie : watchListRepo->getAll()) {
			watchListRepoCopy->addMovie(movie);
		}
		watchListRepo = new CSVFile{};
		watchListRepo->setName("moviescsv.csv");
		for (auto movie : watchListRepoCopy->getAll()) {
			watchListRepo->addMovie(movie);
		}
		watchListRepo->printSpecificFile();
	}
	catch (FileException& exception) {
		QMessageBox::warning(this, "Exception", exception.what());
	}

}

void GraphicInterface::initializeHTML() {
	//watchListRepo = new HTMLFile{};
	//watchListRepo->setName("movieshtml.csv");
	watchListRepoCopy = new HTMLFile{};
	for (auto movie : watchListRepo->getAll()) {
		watchListRepoCopy->addMovie(movie);
	}
	watchListRepo = new HTMLFile{};
	watchListRepo->setName("movieshtml.html");
	for (auto movie : watchListRepoCopy->getAll()) {
		watchListRepo->addMovie(movie);
	}
	watchListRepo->printSpecificFile();
}

void GraphicInterface::pushButtonForAdminInterface() {
	this->hide();
	windowAdmin->show();

}

void GraphicInterface::addMovieToRepo() {
	addInterfaceForRepo = new QWidget();
	QVBoxLayout* addLayout = new QVBoxLayout();
	QFormLayout* optionsForAdd = new QFormLayout();
	QLabel* titleLabel = new QLabel("Title : ");
	QLabel* genreLabel = new QLabel("Genre : ");
	QLabel* yearLabel = new QLabel("Year of release : ");
	QLabel* likesLabel = new QLabel("Likes : ");
	QLabel* trailerLabel = new QLabel("Link for trailer : ");
	titleLine = new QLineEdit();
	genreLine = new QLineEdit();
	yearLine = new QLineEdit();
	likesLine = new QLineEdit();
	trailerLine = new QLineEdit();
	QPushButton* addButtonToRepo = new QPushButton("Add the movie inputted.");
	optionsForAdd->addRow(titleLabel, titleLine);
	optionsForAdd->addRow(genreLabel, genreLine);
	optionsForAdd->addRow(yearLabel, yearLine);
	optionsForAdd->addRow(likesLabel, likesLine);
	optionsForAdd->addRow(trailerLabel, trailerLine);
	addInterfaceForRepo->setLayout(addLayout);
	addLayout->addLayout(optionsForAdd);
	addLayout->addWidget(addButtonToRepo);
	QObject::connect(addButtonToRepo, &QPushButton::clicked, this, &GraphicInterface::addButtonForRepo);
	addInterfaceForRepo->show();
}

void GraphicInterface::updateMovieFromRepo() {
	updateInterfaceForRepo = new QWidget();
	QHBoxLayout* updateLayout = new QHBoxLayout();
	QVBoxLayout* inputLayout = new QVBoxLayout();
	QVBoxLayout* newInputLayout = new QVBoxLayout();
	QFormLayout* optionsForUpdate = new QFormLayout();
	QFormLayout* optionsForUpdateNewInput = new QFormLayout();
	QLabel* titleLabel = new QLabel("Title : ");
	QLabel* genreLabel = new QLabel("Genre : ");
	QLabel* yearLabel = new QLabel("Year of release : ");
	QLabel* likesLabel = new QLabel("Likes : ");
	QLabel* trailerLabel = new QLabel("Link for trailer : ");
	titleLine = new QLineEdit();
	genreLine = new QLineEdit();
	yearLine = new QLineEdit();
	likesLine = new QLineEdit();
	trailerLine = new QLineEdit();
	QLabel* titleLabelUpdate = new QLabel("New Title : ");
	QLabel* genreLabelUpdate = new QLabel("New Genre : ");
	QLabel* yearLabelUpdate = new QLabel("New Year of release : ");
	QLabel* likesLabelUpdate = new QLabel("New Likes : ");
	QLabel* trailerLabelUpdate = new QLabel("New Link for trailer : ");
	titleLineUpdate = new QLineEdit();
	genreLineUpdate = new QLineEdit();
	yearLineUpdate = new QLineEdit();
	likesLineUpdate = new QLineEdit();
	trailerLineUpdate = new QLineEdit();
	QPushButton* updateButtonToRepo = new QPushButton("Update the movie inputted.");
	optionsForUpdate->addRow(titleLabel, titleLine);
	optionsForUpdate->addRow(genreLabel, genreLine);
	optionsForUpdate->addRow(yearLabel, yearLine);
	optionsForUpdate->addRow(likesLabel, likesLine);
	optionsForUpdate->addRow(trailerLabel, trailerLine);
	optionsForUpdateNewInput->addRow(titleLabelUpdate, titleLineUpdate);
	optionsForUpdateNewInput->addRow(genreLabelUpdate, genreLineUpdate);
	optionsForUpdateNewInput->addRow(yearLabelUpdate, yearLineUpdate);
	optionsForUpdateNewInput->addRow(likesLabelUpdate, likesLineUpdate);
	optionsForUpdateNewInput->addRow(trailerLabelUpdate, trailerLineUpdate);
	updateInterfaceForRepo->setLayout(inputLayout);
	updateLayout->addLayout(optionsForUpdate);
	updateLayout->addLayout(optionsForUpdateNewInput);
	inputLayout->addLayout(updateLayout);
	inputLayout->addWidget(updateButtonToRepo);
	QObject::connect(updateButtonToRepo, &QPushButton::clicked, this, &GraphicInterface::updateMovieButtonFromRepo);
	updateInterfaceForRepo->show();
}

void GraphicInterface::updateMovieButtonFromRepo() {
	Movie movieExistent,newMovie;
	std::string title = titleLine->text().toStdString();
	std::string genre = genreLine->text().toStdString();
	std::string yearOfRelease = yearLine->text().toStdString();
	std::string likes = likesLine->text().toStdString();
	std::string trailer = trailerLine->text().toStdString();
	std::string titleUpdate = titleLineUpdate->text().toStdString();
	std::string genreUpdate = genreLineUpdate->text().toStdString();
	std::string yearOfReleaseUpdate = yearLineUpdate->text().toStdString();
	std::string likesUpdate = likesLineUpdate->text().toStdString();
	std::string trailerUpdate = trailerLineUpdate->text().toStdString();
	try
	{
		MovieValidator::validate(title, genre, yearOfRelease, likes, trailer);
		movieExistent.setGenre(genre);
		movieExistent.setLikes(std::stoi(likes));
		movieExistent.setYearOfRelease(std::stoi(yearOfRelease));
		movieExistent.setTrailer(trailer);
		movieExistent.setTitle(title);
		try
		{
			
				MovieValidator::validate(titleUpdate, genreUpdate, yearOfReleaseUpdate, likesUpdate, trailerUpdate);
				newMovie.setGenre(genreUpdate);
				newMovie.setLikes(std::stoi(likesUpdate));
				newMovie.setYearOfRelease(std::stoi(yearOfReleaseUpdate));
				newMovie.setTrailer(trailerUpdate);
				newMovie.setTitle(titleUpdate);
				this->serv.updateMovie(movieExistent, newMovie);
				if (filename != "null") {
					this->serv.saveToFileServ(filename);
				}
		}
		catch (InexistentMovieException& exception)
		{
			QMessageBox::warning(this, "Exception", exception.what());
		}
		catch (DuplicateMovieException& exception)
		{
			QMessageBox::warning(this, "Exception", exception.what());
		}
	}
	catch (MovieException& errors)
	{
		QString errorMessage;
		for (auto error : errors.getErrors())
			errorMessage += QString::fromStdString(error + "\n");
		QMessageBox::warning(this, "Exception", errorMessage);
	}


	titleLineUpdate->clear();
	genreLineUpdate->clear();
	yearLineUpdate->clear();
	likesLineUpdate->clear();
	trailerLineUpdate->clear();
	titleLine->clear();
	genreLine->clear();
	yearLine->clear();
	likesLine->clear();
	trailerLine->clear();
	updateInterfaceForRepo->hide();
	populateListFromRepo();
}

void GraphicInterface::removeMovieFromRepo() {
	removeInterfaceForRepo = new QWidget();
	QVBoxLayout* removeLayout = new QVBoxLayout();
	QFormLayout* optionsForRemove = new QFormLayout();
	QLabel* titleLabel = new QLabel("Title : ");
	QLabel* genreLabel = new QLabel("Genre : ");
	QLabel* yearLabel = new QLabel("Year of release : ");
	QLabel* likesLabel = new QLabel("Likes : ");
	QLabel* trailerLabel = new QLabel("Link for trailer : ");
	titleLine = new QLineEdit();
	genreLine = new QLineEdit();
	yearLine = new QLineEdit();
	likesLine = new QLineEdit();
	trailerLine = new QLineEdit();
	QPushButton* removeButtonToRepo = new QPushButton("Remove the movie inputted.");
	optionsForRemove->addRow(titleLabel, titleLine);
	optionsForRemove->addRow(genreLabel, genreLine);
	optionsForRemove->addRow(yearLabel, yearLine);
	optionsForRemove->addRow(likesLabel, likesLine);
	optionsForRemove->addRow(trailerLabel, trailerLine);
	removeInterfaceForRepo->setLayout(removeLayout);
	removeLayout->addLayout(optionsForRemove);
	removeLayout->addWidget(removeButtonToRepo);
	QObject::connect(removeButtonToRepo, &QPushButton::clicked, this, &GraphicInterface::removeMovieButtonFromRepo);
	removeInterfaceForRepo->show();
}

void GraphicInterface::removeMovieButtonFromRepo() {
	Movie movie;
	std::string title = titleLine->text().toStdString();
	std::string genre = genreLine->text().toStdString();
	std::string yearOfRelease = yearLine->text().toStdString();
	std::string likes = likesLine->text().toStdString();
	std::string trailer = trailerLine->text().toStdString();
	try
	{
		MovieValidator::validate(title, genre, yearOfRelease, likes, trailer);
		movie.setGenre(genre);
		movie.setLikes(std::stoi(likes));
		movie.setYearOfRelease(std::stoi(yearOfRelease));
		movie.setTrailer(trailer);
		movie.setTitle(title);
		try
		{
			this->serv.removeMovie(movie);
			if (filename != "null") {
				this->serv.saveToFileServ(filename);
			}
		}
		catch (InexistentMovieException& exception)
		{
			QMessageBox::warning(this, "Exception", exception.what());
		}
	}
	catch (MovieException& errors)
	{
		QString errorMessage;
		for (auto error : errors.getErrors())
			errorMessage += QString::fromStdString(error + "\n");
		QMessageBox::warning(this, "Exception", errorMessage);
	}
	titleLine->clear();
	genreLine->clear();
	yearLine->clear();
	likesLine->clear();
	trailerLine->clear();
	removeInterfaceForRepo->hide();
	populateListFromRepo();
}

void GraphicInterface::addButtonForRepo() {
	Movie movie;
	std::string title = titleLine->text().toStdString();
	std::string genre = genreLine->text().toStdString();
	std::string yearOfRelease = yearLine->text().toStdString();
	std::string likes = likesLine->text().toStdString();
	std::string trailer = trailerLine->text().toStdString();
	try
	{
		MovieValidator::validate(title, genre, yearOfRelease, likes, trailer);
		movie.setGenre(genre);
		movie.setLikes(std::stoi(likes));
		movie.setYearOfRelease(std::stoi(yearOfRelease));
		movie.setTrailer(trailer);
		movie.setTitle(title);
		try
		{
			this->serv.addMovie(movie);
			if (filename != "null") {
				this->serv.saveToFileServ(filename);
			}
		}
		catch (DuplicateMovieException& exception)
		{
			QMessageBox::warning(this, "Exception", exception.what());
		}
	}
	catch (MovieException& errors)
	{
		QString errorMessage;
		for (auto error : errors.getErrors())
			errorMessage += QString::fromStdString(error + "\n");
			QMessageBox::warning(this, "Exception",errorMessage);
	}
	titleLine->clear();
	genreLine->clear();
	yearLine->clear();
	likesLine->clear();
	trailerLine->clear();
	addInterfaceForRepo->hide();
	populateListFromRepo();

}

void GraphicInterface::backButtonFunction() {
	windowAdmin->hide();
	windowUser->hide();
	this->show();
}

void GraphicInterface::populateListForAdmin()
{
	try {
		this->movieList->clear();
		this->filename = this->inputFileLine->text().toStdString();
		this->serv.readFromFileServ(filename);
		for (auto movie : this->serv.getAll()) {
			std::string s = movie.getTitle() + ", " + std::to_string(movie.getLikes()) + ", " + movie.getGenre() + "," + std::to_string(movie.getYearOfRelease()) + ", " + movie.getTrailer();
			this->movieList->addItem(QString::fromStdString(s));
		}
	}
	catch (FileException& exception) {
		QMessageBox::warning(this, "Exception", exception.what());
	}
}

void GraphicInterface::populateListFromRepo()
{
	this->movieList->clear();
	for (auto movie : this->serv.getAll()) {
		std::string stringOfEveryMovie = movie.getTitle() + ", " + std::to_string(movie.getLikes()) + ", " + movie.getGenre() + "," + std::to_string(movie.getYearOfRelease()) + ", " + movie.getTrailer();
		this->movieList->addItem(QString::fromStdString(stringOfEveryMovie));
	}
}

void GraphicInterface::deleteMovieFromWatchListFunction(QListWidgetItem* item) {
	std::string movieString = item->text().toStdString();
	//std::string genre, trailer, title, likes, year;
	for (auto movie : watchListRepo->getAll()) {
		std::string stringOfEveryMovie = movie.getTitle() + ", " + std::to_string(movie.getLikes()) + ", " + movie.getGenre() + "," + std::to_string(movie.getYearOfRelease()) + ", " + movie.getTrailer();
		if (movieString == stringOfEveryMovie) {
			selectedMovie = movie;
			break;
		}
	}
}

void GraphicInterface::addToWatchlistWindow() {
		QLabel* label = new QLabel("Do you want to add the movie to the watch list?");

		QVBoxLayout* layout = new QVBoxLayout();
		QHBoxLayout* buttonLayout = new QHBoxLayout();
		layout->addWidget(label);
		layout->setAlignment(Qt::AlignCenter);
		yesLikeMovie = new QPushButton("yes");
		noLikeMovie = new QPushButton("no");
		buttonLayout->addWidget(yesLikeMovie);
		buttonLayout->addWidget(noLikeMovie);
		layout->addLayout(buttonLayout);
		addToWatchlist->setLayout(layout);
		QObject::connect(noLikeMovie, &QPushButton::clicked, this, &GraphicInterface::pressedNoWatchlistPopUp);
		QObject::connect(yesLikeMovie, &QPushButton::clicked, this, &GraphicInterface::pressedYesWatchlistPopUp);
}

void GraphicInterface::pressedNoWatchlistPopUp() {
	addToWatchlist->hide();
}

void GraphicInterface::populateWatchList() {
	this->watchlist->clear();
	for (auto movie : watchListRepo->getAll()) {
		std::string s = movie.getTitle() + ", " + std::to_string(movie.getLikes()) + ", " + movie.getGenre() + "," + std::to_string(movie.getYearOfRelease()) + ", " + movie.getTrailer();
		this->watchlist->addItem(QString::fromStdString(s));
	}
}

void GraphicInterface::pressedYesWatchlistPopUp()
{
	if (watchListRepo->checkAuthenticity(this->serv.getMovieAtIndex(indexForOneByOneMovie))== false)
	{
		watchListRepo->addMovie(this->serv.getMovieAtIndex(indexForOneByOneMovie));
	}
	else {
		QMessageBox::warning(this, "Exception", "There is already the specified movie in the watch list");
	}
	populateWatchList();
	addToWatchlist->hide();
}

void GraphicInterface::createWindowAdmin() {
	QVBoxLayout* adminLayout;
	adminLayout = new QVBoxLayout();
	movieList = new QListWidget();
	optionsForAdmin = new QFormLayout();
	addMovieButton = new QPushButton("Add Movie");
	removeMovieButton = new QPushButton("Remove Movie");
	updateMovieButton = new QPushButton("Update Movie");
	addMovieLine = new QLineEdit();
	removeMovieLine = new QLineEdit();
	updateMovieLine = new QLineEdit();
	backButtonAdmin = new QPushButton("Go back");
	optionsForAdmin->addRow(addMovieButton/*,addMovieLine*/);
	optionsForAdmin->addRow(removeMovieButton/*,removeMovieLine*/);
	optionsForAdmin->addRow(updateMovieButton/*, updateMovieLine*/);
	adminLayout->addLayout(optionsForAdmin);
	adminLayout->addWidget(movieList);
	adminLayout->addWidget(backButtonAdmin);
	windowAdmin->setLayout(adminLayout);
	inputFileLine = new QLineEdit();
	inputFileButton = new QPushButton("Filename");
	optionsForAdmin->addRow(inputFileButton, inputFileLine);
	//windowAdmin->show();
	QObject::connect(inputFileButton, &QPushButton::clicked, this, &GraphicInterface::populateListForAdmin);
	QObject::connect(backButtonAdmin, &QPushButton::clicked, this, &GraphicInterface::backButtonFunction);
	QObject::connect(addMovieButton, &QPushButton::clicked, this, &GraphicInterface::addMovieToRepo);
	QObject::connect(removeMovieButton, &QPushButton::clicked, this, &GraphicInterface::removeMovieFromRepo);
	QObject::connect(updateMovieButton, &QPushButton::clicked, this, &GraphicInterface::updateMovieFromRepo);
}

void GraphicInterface::createWindowUser() {
	QVBoxLayout* bigLayout = new QVBoxLayout();
	QHBoxLayout* mainLayout = new QHBoxLayout();
	QVBoxLayout* userLayout = new QVBoxLayout();
	QVBoxLayout* watchListLayout = new QVBoxLayout();
	QFormLayout* layoutGenre = new QFormLayout();
	QHBoxLayout* layoutButtons = new QHBoxLayout();
	buttonCSVAdmin = new QPushButton("CSV File type for WatchList");
	buttonHTMLAdmin = new QPushButton("HTML File type for WatchList");
	QPushButton* Print = new QPushButton("Print WatchList");
	giveGenreButton = new QPushButton("Input Genre");
	giveGenreLine = new QLineEdit();
	layoutGenre->addRow(giveGenreButton, giveGenreLine);
	listOneByOne = new QListWidget();
	userLayout->addLayout(layoutGenre);
	userLayout->addWidget(listOneByOne);
	//windowUser->setLayout(mainLayout);
	likeMovie = new QPushButton("Like");
	//addMovieToWatchlist = new QPushButton("Add to watchlist");
	nextMovie = new QPushButton("Next");
	layoutButtons = new QHBoxLayout();
	layoutButtons->addWidget(likeMovie);
	layoutButtons->addWidget(nextMovie);
	//layoutButtons->addWidget(addMovieToWatchlist);
	userLayout->addLayout(layoutButtons);
	deleteMovieFromWatchlist = new QPushButton("Delete Movie");
	likeMovieFromWatchlist = new QPushButton("Like Movie");
	watchlist = new QListWidget();
	movieListName = new QLabel("Watch List:");
	movieListName->setStyleSheet("font-weight: bold; color: blue");
	watchListLayout->addWidget(movieListName);
	watchListLayout->addWidget(watchlist);
	buttonsFromWatchlist = new QHBoxLayout();
	QLabel* WatchListTypeLabel = new QLabel("Choose watch list type (default is CSV): ");
	buttonsFromWatchlist->addWidget(deleteMovieFromWatchlist);
	buttonsFromWatchlist->addWidget(likeMovieFromWatchlist);
	watchListLayout->addLayout(buttonsFromWatchlist);
	mainLayout->addLayout(userLayout);
	mainLayout->addLayout(watchListLayout);
	bigLayout->addLayout(mainLayout);
	bigLayout->addWidget(WatchListTypeLabel);
	bigLayout->addWidget(buttonCSVAdmin);
	bigLayout->addWidget(buttonHTMLAdmin);
	bigLayout->addWidget(Print);
	backButtonUser = new QPushButton("Back");
	bigLayout->addWidget(backButtonUser);
	windowUser->setLayout(bigLayout);

	QObject::connect(backButtonUser, &QPushButton::clicked, this, &GraphicInterface::backButtonFunction);
	QObject::connect(giveGenreButton, &QPushButton::clicked, this, &GraphicInterface::verifyGenre);
	QObject::connect(nextMovie, &QPushButton::clicked, this, &GraphicInterface::nextMovieInLine);
	QObject::connect(watchlist, &QListWidget::itemClicked, this, &GraphicInterface::deleteMovieFromWatchListFunction);
	QObject::connect(likeMovie, &QPushButton::clicked, this, &GraphicInterface::showAddToWatchlistWindow);
	QObject::connect(deleteMovieFromWatchlist, &QPushButton::clicked, this, &GraphicInterface::deleteSelectedMovieFromWatchListFunction);
	QObject::connect(likeMovieFromWatchlist, &QPushButton::clicked, this, &GraphicInterface::increaseLikeCountForMovieFromWatchlist);
	QObject::connect(this->buttonCSVAdmin, &QPushButton::clicked, this, &GraphicInterface::initializeCSV);
	QObject::connect(this->buttonHTMLAdmin, &QPushButton::clicked, this, &GraphicInterface::initializeHTML);
	QObject::connect(Print, &QPushButton::clicked, this, &GraphicInterface::printWatchlist);
}

void GraphicInterface::increaseLikeCountForMovieFromWatchlist() {
	if (selectedMovie.getTitle() == "null")
	{
		QMessageBox::warning(this, "Exception", "There is nothing to like selected.");
	}
	else
	{
		Movie repoMovie = selectedMovie;
		for (int index = 0; index < watchListRepo->getSize(); index++) {
			if (watchListRepo->getMovieAtIndex(index) == selectedMovie) {
				selectedMovie.setLikes(selectedMovie.getLikes() + 1);
				watchListRepo->update(watchListRepo->getMovieAtIndex(index), selectedMovie);
			}
		}
		this->serv.updateMovie(repoMovie, selectedMovie);
		if(filename!="null")
			this->serv.saveToFileServ(filename);
		populateListFromRepo();
		populateListOneByOne();
		populateWatchList();
	}
}

void GraphicInterface::deleteSelectedMovieFromWatchListFunction() {
	if (selectedMovie.getTitle() == "null") {
		QMessageBox::warning(this, "Exception", "There is nothing to delete selected.");

	}
	if (selectedMovie.getTitle() != "null")
		watchListRepo->remove(selectedMovie);
	populateWatchList();
	selectedMovie.setTitle("null");

}
void GraphicInterface::showAddToWatchlistWindow() {
	if(listOneByOne->count()>0)
	addToWatchlist->show();
	else {
		QMessageBox::warning(this, "Exception", "There is nothing to like.");
	}
}

void GraphicInterface::pushButtonForUserInterface() {
	this->hide();
	windowUser->show();
}

void GraphicInterface::verifyGenre() {
	genreForMovie = giveGenreLine->text().toStdString();
	indexForOneByOneMovie = 0;
	Movie movie;
	verifyExistence = false;
	listOneByOne->clear();
	if (genreForMovie != "null")
	{
		for (auto movie : this->serv.getAll()) {
			if (movie.getGenre() == genreForMovie)
			{
				verifyExistence = true;
				break;
			}
		}
	}
	if (verifyExistence == false and genreForMovie!="null") {
		QMessageBox::warning(this, "Exception", "There is no such genre in the list of movies");
	}
	if (verifyExistence == true and genreForMovie != "null")
	{
		while (indexForOneByOneMovie < this->serv.getSize() and genreForMovie != this->serv.getMovieAtIndex(indexForOneByOneMovie).getGenre())
			indexForOneByOneMovie++;
		movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
		std::string stringOneByOne = "Title: "+ movie.getTitle() + "\n" + "Likes: "+ std::to_string(movie.getLikes()) + "\n"+"Genre: " + movie.getGenre() + "\n" +"Year Of Release: " + std::to_string(movie.getYearOfRelease()) + "\n"+"Trailer Link: " + movie.getTrailer();
			listOneByOne->addItem(QString::fromStdString(stringOneByOne));

	}
	else if (genreForMovie == "null" and this->serv.getAll().size()>0) {
			movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
			std::string stringOneByOne = "Title: " + movie.getTitle() + "\n" + "Likes: " + std::to_string(movie.getLikes()) + "\n" + "Genre: " + movie.getGenre() + "\n" + "Year Of Release: " + std::to_string(movie.getYearOfRelease()) + "\n" + "Trailer Link: " + movie.getTrailer();
			listOneByOne->addItem(QString::fromStdString(stringOneByOne));
		}
	//giveGenreLine->clear();
	}

void GraphicInterface::populateListOneByOne() {
	listOneByOne->clear();
	Movie movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
	//movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
	std::string stringOneByOne = "Title: " + movie.getTitle() + "\n" + "Likes: " + std::to_string(movie.getLikes()) + "\n" + "Genre: " + movie.getGenre() + "\n" + "Year Of Release: " + std::to_string(movie.getYearOfRelease()) + "\n" + "Trailer Link: " + movie.getTrailer();
	listOneByOne->addItem(QString::fromStdString(stringOneByOne));
}

void GraphicInterface::nextMovieInLine() {
	indexForOneByOneMovie++;
	Movie movie;
	listOneByOne->clear();
	if (genreForMovie == "null") {
		if (indexForOneByOneMovie >= this->serv.getAll().size())
		{
			indexForOneByOneMovie = 0;
		}
		movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
		std::string stringOneByOne = "Title: " + movie.getTitle() + "\n" + "Likes: " + std::to_string(movie.getLikes()) + "\n" + "Genre: " + movie.getGenre() + "\n" + "Year Of Release: " + std::to_string(movie.getYearOfRelease()) + "\n" + "Trailer Link: " + movie.getTrailer();
		listOneByOne->addItem(QString::fromStdString(stringOneByOne));
	}
	else if (genreForMovie != "null" and verifyExistence == true) {
		while (this->serv.getMovieAtIndex(indexForOneByOneMovie).getGenre() != genreForMovie)
		{
			indexForOneByOneMovie++;

			if (indexForOneByOneMovie >= this->serv.getAll().size())
				indexForOneByOneMovie = 0;
		}
		movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
		//movie = this->serv.getMovieAtIndex(indexForOneByOneMovie);
		std::string stringOneByOne = "Title: " + movie.getTitle() + "\n" + "Likes: " + std::to_string(movie.getLikes()) + "\n" + "Genre: " + movie.getGenre() + "\n" + "Year Of Release: " + std::to_string(movie.getYearOfRelease()) + "\n" + "Trailer Link: " + movie.getTrailer();
		listOneByOne->addItem(QString::fromStdString(stringOneByOne));
	}
	else if (genreForMovie != "null" and verifyExistence == false) {
		QMessageBox::warning(this, "Exception", "There is no such genre in the list of movies");
	}

}

