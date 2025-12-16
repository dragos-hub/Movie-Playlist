#pragma once
#include <QLabel>
#include <qwidget.h>
#include "Service.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

#include "observer.h"

class GUIAdmin : public QWidget{
    Q_OBJECT
private:
    Service& serv;

    QListWidget* allMovies;
    QLineEdit* lineTitle;
    QLineEdit* lineGenre;
    QLineEdit* lineYear;
    QLineEdit* lineLikes;
    QLineEdit* lineLink;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;

    QPushButton* copyButton;
    QListWidget* playlist;

    QPushButton* playButton;
    QPushButton* nextButton;

public:
    GUIAdmin(Service& serv);
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();

    void addButtonHandler();
    void removeButtonHandler();
    void updateButtonHandler();
};

class GUIUser : public QWidget, public Observer {
    Q_OBJECT
private:
    Service& serv;

    //genre filtering
    QLineEdit* genreEdit;
    QPushButton* searchButton;

    // current movie
    QLabel *genreLabel, *yearLabel, *likesLabel, *linkLabel;
    QLabel *titleLabel;
    QPushButton* addButton;
    QPushButton* nextButton;

    //watchlist
    QTableWidget* watchlistTable;
    QPushButton* deleteButton;

    std::vector<Movie> movieList;
    int index = 0;

public:
    GUIUser(Service& serv);

private slots:
    void searchGenreButton();
    void showCurrMovie();
    void addMovieButton();
    void nextMovieButton();
    void deleteMovieButton();
    void update() override;
};

