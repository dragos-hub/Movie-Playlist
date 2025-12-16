//
// Created by isacd on 5/22/2025.
//

#include "GUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <qgridlayout.h>
#include <vector>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>

using namespace std;

GUIAdmin::GUIAdmin(Service& serv): serv{serv}
{
    this->resize(800, 600); // Resize the GUI window
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUIAdmin::initGUI()
{
    QVBoxLayout* adminLayout = new QVBoxLayout{};

    QLabel* titleLabel = new QLabel("Admin Panel");
    QFont titleFont("Arial", 20, QFont::Bold); // Set font size and style
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter); // Center the title
    adminLayout->addWidget(titleLabel);

    QLabel* allMoviesLable = new QLabel("All movies");
    adminLayout->addWidget(allMoviesLable);

    QHBoxLayout* mainWindow = new QHBoxLayout{ this };

    mainWindow->addLayout(adminLayout);

    allMovies = new QListWidget{};
    adminLayout->addWidget(allMovies);

    QFormLayout* movieDetails = new QFormLayout{};
    lineTitle = new QLineEdit{};
    lineGenre = new QLineEdit{};
    lineYear = new QLineEdit{};
    lineLikes = new QLineEdit{};
    lineLink = new QLineEdit{};

    movieDetails->addRow("Title", lineTitle);
    movieDetails->addRow("Genre", lineGenre);
    movieDetails->addRow("Year", lineYear);
    movieDetails->addRow("Likes", lineLikes);
    movieDetails->addRow("Link", lineLink);

    adminLayout->addLayout(movieDetails);

    QGridLayout* adminButtonsLayout = new QGridLayout{};

    addButton = new QPushButton{ "Add" };
    deleteButton = new QPushButton{ "Remove" };
    updateButton = new QPushButton{ "Update" };

    adminButtonsLayout->addWidget(addButton, 0, 0);
    adminButtonsLayout->addWidget(deleteButton, 0, 1);
    adminButtonsLayout->addWidget(updateButton, 0, 2);

    adminLayout->addLayout(adminButtonsLayout);
}

void GUIAdmin::populateList()
{
  if(allMovies->count() > 0)
    allMovies->clear();

  vector<Movie> movies = this->serv.getMoviesService();

  for (const Movie& m : movies)
  {
    allMovies->addItem(QString::fromStdString("Movie: " + m.getTitle() + "\nGenre: "
        + m.getGenre() + "\nYear: " + std::to_string(m.getYear()) + "\nLikes: " +
        std::to_string(m.getLikes()) + "\nTrailer: " + m.getTrailer() + "\n-----"));
  }
}

void GUIAdmin::connectSignalsAndSlots()
{
    QObject::connect(deleteButton, &QPushButton::clicked, this, &GUIAdmin::removeButtonHandler);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUIAdmin::addButtonHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUIAdmin::updateButtonHandler);
}

void GUIAdmin::addButtonHandler()
{
    string title = lineTitle->text().toStdString();
    string genre = lineGenre->text().toStdString();
    int year = lineYear->text().toInt();
    int likes = lineLikes->text().toInt();
    string link = lineLink->text().toStdString();

    try
    {
        this->serv.addMovieService(title, genre, year, likes, link);
        QMessageBox::information(this, "Success", "Movie added successfully!");
    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
    this->populateList();
}

void GUIAdmin::removeButtonHandler() {
    QListWidgetItem* selectedItem = allMovies->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Warning", "No movie selected!");
        return;
    }

    QString selectedText = selectedItem->text();
    std::string title = selectedText.toStdString();

    // Find the position of "Movie: " and extract the title
    size_t startPos = title.find("Movie: ");
    if (startPos != std::string::npos) {
        startPos += 7; // Move past "Movie: "
        size_t endPos = title.find("\n", startPos);
        if (endPos != std::string::npos) {
            title = title.substr(startPos, endPos - startPos); // Extract the title
        }
    }

    try {
        // Remove the movie from the repository
        this->serv.deleteMovieService(title);
        QMessageBox::information(this, "Success", "Movie removed successfully!");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }

    // Refresh the list
    this->populateList();
}

void GUIAdmin::updateButtonHandler() {
    // Get the selected item from the list
    QListWidgetItem* selectedItem = allMovies->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Warning", "No movie selected!");
        return;
    }

    // Extract the title of the selected movie
    QString selectedText = selectedItem->text();
    std::string oldTitle = selectedText.toStdString();
    size_t startPos = oldTitle.find("Movie: ");
    if (startPos != std::string::npos) {
        startPos += 7; // Move past "Movie: "
        size_t endPos = oldTitle.find("\n", startPos);
        if (endPos != std::string::npos) {
            oldTitle = oldTitle.substr(startPos, endPos - startPos); // Extract the title
        }
    }

    // Retrieve new details from input fields
    std::string newTitle = lineTitle->text().toStdString();
    std::string genre = lineGenre->text().toStdString();
    int year = lineYear->text().toInt();
    int likes = lineLikes->text().toInt();
    std::string link = lineLink->text().toStdString();

    try {
        // Update the movie in the repository
        this->serv.updateMovieService(oldTitle, newTitle, genre, year, likes, link);
        QMessageBox::information(this, "Success", "Movie updated successfully!");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }

    // Refresh the list
    this->populateList();
}

GUIUser::GUIUser(Service& serv) : serv{ serv } {
    this->resize(550, 600);

    QVBoxLayout* UserLayout = new QVBoxLayout();

    QLabel* titleLabel2 = new QLabel("PlayList");
    QFont titleFont("Arial", 13, QFont::Bold); // Set font size and style
    titleLabel2->setFont(titleFont);
    titleLabel2->setAlignment(Qt::AlignCenter); // Center the title
    UserLayout->addWidget(titleLabel2);

    // Genre Layout
    QHBoxLayout* genreLayout = new QHBoxLayout();
    genreEdit = new QLineEdit();
    searchButton = new QPushButton("Search");

    genreLayout->addWidget(new QLabel("Genre: "));
    genreLayout->addWidget(genreEdit);
    genreLayout->addWidget(searchButton);

    connect(searchButton, &QPushButton::clicked, this, &GUIUser::searchGenreButton);

    // Current Movie
    QVBoxLayout* movieLayout = new QVBoxLayout();
    movieLayout->addWidget(new QLabel("Current Movie:"));

    QFormLayout* form = new QFormLayout();
    titleLabel = new QLabel();
    genreLabel = new QLabel();
    yearLabel = new QLabel();
    likesLabel = new QLabel();
    linkLabel = new QLabel();
    form->addRow("Title:", titleLabel);
    form->addRow("Genre:", genreLabel);
    form->addRow("Year:", yearLabel);
    form->addRow("Likes:", likesLabel);
    form->addRow("Link:", linkLabel);
    movieLayout->addLayout(form);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add");
    buttonLayout->addWidget(addButton);
    nextButton = new QPushButton("Next");
    buttonLayout->addWidget(nextButton);

    movieLayout->addLayout(buttonLayout);

    UserLayout->addLayout(genreLayout);
    UserLayout->addLayout(movieLayout);

    connect(addButton, &QPushButton::clicked, this, &GUIUser::addMovieButton);
    connect(nextButton, &QPushButton::clicked, this, &GUIUser::nextMovieButton);

    // Watchlist
    QVBoxLayout* watchlistLayout = new QVBoxLayout();

    watchlistTable = new QTableWidget(this);
    watchlistTable->setColumnCount(5);
    watchlistTable->setHorizontalHeaderLabels({"Title", "Genre", "Year", "Likes", "Link"});

    watchlistLayout->addWidget(watchlistTable);

    deleteButton = new QPushButton("Delete");
    watchlistLayout->addWidget(deleteButton);
    UserLayout->addLayout(watchlistLayout);
    connect(deleteButton, &QPushButton::clicked, this, &GUIUser::deleteMovieButton);

    update();
    this->setLayout(UserLayout);
}

void GUIUser::searchGenreButton() {
    std::string genre = genreEdit->text().toStdString();
    movieList = serv.getMoviesFromGenre(genre);
    cout << "a";
    index = 0;

    showCurrMovie();
}

void GUIUser::showCurrMovie() {
    if (movieList.size() == 0) {
        cout << "No movies found" << endl;
        return;
    }
    if (movieList.empty()) {
        qDebug() << "Movie list is empty.";
        cout << "Empty";
        return;
    }
    cout << movieList.size() << endl;
    Movie m = movieList[index];
    cout << "gfh " << index << endl;
    titleLabel->setText(QString::fromStdString(m.getTitle()));
    cout << "asd";
    cout << titleLabel->text().toStdString() << endl;
    genreLabel->setText(QString::fromStdString(m.getGenre()));
    yearLabel->setText(QString::number(m.getYear()));
    likesLabel->setText(QString::number(m.getLikes()));
    linkLabel->setText(QString::fromStdString(m.getTrailer()));

    QDesktopServices::openUrl(QUrl(QString::fromStdString(m.getTrailer())));
    cout << "b";
}
void GUIUser::addMovieButton() {
    Movie m = movieList[index];
    std::string title = titleLabel->text().toStdString();
    std::string genre = genreLabel->text().toStdString();
    int year = yearLabel->text().toInt();
    int likes = likesLabel->text().toInt();
    std::string link = linkLabel->text().toStdString();
    serv.addToWatchService(title, genre, year, likes, link);
    update();
}

void GUIUser::nextMovieButton() {
    if (movieList.size() == 0) {
        return;
    }
    index = (index + 1) % movieList.size();
    showCurrMovie();
}

void GUIUser::deleteMovieButton() {
    int row = watchlistTable->currentRow();
    if (row < 0) return;

    std::string title = watchlistTable->item(row, 0)->text().toStdString();

    serv.deleteToWatchService(title);
    update();
}

void GUIUser::update() {
    watchlistTable->setRowCount(0);

    std::vector<Movie> watchlist = serv.getWatchedMovies();

    for (const auto& m : watchlist) {
        int row = watchlistTable->rowCount();
        watchlistTable->insertRow(row);
        watchlistTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(m.getTitle())));
        watchlistTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(m.getGenre())));
        watchlistTable->setItem(row, 2, new QTableWidgetItem(QString::number(m.getYear())));
        watchlistTable->setItem(row, 3, new QTableWidgetItem(QString::number(m.getLikes())));
        watchlistTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(m.getTrailer())));
    }
}

