#include "Service.h"
#include <stdexcept>


void Service::setWatchListFileType(const std::string& fileType) {
    this->watchListFileType = fileType;
    if (fileType == "csv") {
        this->watchListFile = new CSVWatchListFile();
    } else if (fileType == "html") {
        this->watchListFile = new HTMLWatchListFile();
    } else {
        throw std::invalid_argument("Invalid file type.");
    }
}

void Service::saveWatchList() {
    if (!this->watchListFile) {
        throw std::runtime_error("Watch list file type not set.");
    }
    this->watchListFile->save(this->repo->getWatchList(), "watchlist." + this->watchListFileType);
}




void Service::addMovieService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
    try {
        Movie m{title, genre, year, likes, trailer};
        this->repo->addMovie(m);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error adding movie: ") + e.what());
    }
}

void Service::deleteMovieService(const std::string& title) {
    try {
        this->repo->deleteMovie(title);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error deleting movie: ") + e.what());
    }
}

void Service::updateMovieService(const std::string& old_title, const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
    try {
        this->repo->updateMovie(old_title, title, genre, year, likes, trailer);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error updating movie: ") + e.what());
    }
}

void Service::addToWatchService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
    try {
        Movie m{title, genre, year, likes, trailer};
        this->repo->addToWatchList(m);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error adding to watch list: ") + e.what());
    }
}

void Service::deleteToWatchService(const std::string& title) {
    try {
        this->repo->deleteMovieWatchList(title);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error deleting movie: ") + e.what());
    }
}