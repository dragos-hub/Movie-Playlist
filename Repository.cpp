#include <algorithm>
#include <fstream>
#include "Repository.h"



class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& message) : std::runtime_error(message) {}
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message) : std::runtime_error(message) {}
};

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& message) : std::runtime_error(message) {}
};


Repository::Repository() :moviesFile("movies.txt"), watchlistFile("watchlist.txt")
{
    this->loadFromFile();
}
Repository::Repository(const std::string& moviesFile, const std::string& watchlistFile)
    : moviesFile(moviesFile), watchlistFile(watchlistFile) {
    this->loadFromFile();
}

Repository::~Repository() {
    this->saveToFile();
}


void Repository::loadFromFile() {
    // Load movies
    std::ifstream moviesInput(this->moviesFile);
    if (!moviesInput.is_open()) {
        throw std::runtime_error("Could not open movies file: " + this->moviesFile);
    }
    Movie movie;
    while (moviesInput >> movie) {
        this->movies.push_back(movie);
    }
    moviesInput.close();

    // Load watchlist
    std::ifstream watchlistInput(this->watchlistFile);
    if (!watchlistInput.is_open()) {
        throw std::runtime_error("Could not open watchlist file: " + this->watchlistFile);
    }
    while (watchlistInput >> movie) {
        this->watch_list.push_back(movie);
    }
    watchlistInput.close();
}

void Repository::saveToFile() {
    // Save movies
    std::ofstream moviesOutput(this->moviesFile);
    if (!moviesOutput.is_open()) {
        throw std::runtime_error("Could not open movies file: " + this->moviesFile);
    }
    for (const auto& movie : this->movies) {
        moviesOutput << movie << "\n";
    }
    moviesOutput.close();

    // Save watchlist
    std::ofstream watchlistOutput(this->watchlistFile);
    if (!watchlistOutput.is_open()) {
        throw std::runtime_error("Could not open watchlist file: " + this->watchlistFile);
    }
    for (const auto& movie : this->watch_list) {
        watchlistOutput << movie << "\n";
    }
    watchlistOutput.close();
    this->notify();
}

void Repository::addMovie(const Movie& m) {
    auto it = std::find_if(this->movies.begin(), this->movies.end(), [&m](const Movie& movie) {
        return movie.getTitle() == m.getTitle();
    });
    if (it != this->movies.end()) {
        throw RepositoryException("Movie already exists.");
    }
    if (m.getTitle() == "")
        throw ValidationException("Title cannot be empty.");
    if (m.getYear() < 1800 || m.getYear() > 2024)
        throw ValidationException("Year must be between 1800 and 2024.");
    if (m.getGenre() == "")
        throw ValidationException("Genre cannot be empty.");
    if (m.getTrailer() == "")
        throw ValidationException("Trailer cannot be empty.");
    this->movies.push_back(m);
    this->saveToFile();
}

void Repository::deleteMovie(const std::string& title) {
    auto it = std::find_if(this->movies.begin(), this->movies.end(), [&title](const Movie& movie) {
        return movie.getTitle() == title;
    });
    if (it == this->movies.end()) {
        throw RepositoryException("Movie not found.");
    }
    // this->movies.erase(it);
    // try {
    //     deleteMovieWatchList(title);
    // } catch (const std::invalid_argument&){
    //     //movie not in watchlist, do nothing
    // }
    this->saveToFile();
}

void Repository::updateMovie(const std::string& old_title, const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
    auto it = std::find_if(this->movies.begin(), this->movies.end(), [&old_title](const Movie& movie) {
        return movie.getTitle() == old_title;
    });
    if (it == this->movies.end()) {
        throw std::invalid_argument("Movie not found.");
    }
    it->updateMovie(title, genre, year, likes, trailer);
    this->saveToFile();
}

void Repository::addToWatchList(const Movie& m) {
    this->watch_list.push_back(m);
    this->saveToFile();
}

void Repository::deleteMovieWatchList(const std::string& title) {
    auto it = std::find_if(this->watch_list.begin(), this->watch_list.end(), [&title](const Movie& movie) {
        return movie.getTitle() == title;
    });
    if (it == this->watch_list.end()) {
        throw std::invalid_argument("Movie not found.");
    }
    this->watch_list.erase(it);
    this->saveToFile();
}

std::vector<Movie> Repository::getMoviesFromGenre(const std::string& genre) {
    std::vector<Movie> filteredMovies;
    std::copy_if(this->movies.begin(), this->movies.end(), std::back_inserter(filteredMovies), [&genre](const Movie& movie) {
        return movie.getGenre() == genre;
    });
    return filteredMovies;
}

int Repository::getGenreSize(const std::string& genre) {
    return std::count_if(this->movies.begin(), this->movies.end(), [&genre](const Movie& movie) {
        return movie.getGenre() == genre;
    });
}