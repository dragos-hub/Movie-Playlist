#pragma once
#include <vector>
#include <string>
#include "movie.h"
#include "observer.h"

class Repository : public Subject{
private:
    std::vector<Movie> movies;
    std::vector<Movie> watch_list;
    std::string moviesFile = "movies.txt";
    std::string watchlistFile = "watchlist.txt";

public:
    Repository(const std::string& moviesFile, const std::string& watchlistFile);
    Repository();
    ~Repository();
    void loadFromFile();
    void saveToFile();
    void addMovie(const Movie& m);
    void deleteMovie(const std::string& title);
    void updateMovie(const std::string& old_title, const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
    std::vector<Movie> getMovies() const { return this->movies; }
    std::vector<Movie> getMoviesFromGenre(const std::string& genre);
    int getGenreSize(const std::string& genre);
    int getNumberOfMovies() const { return this->movies.size(); }

    void likeMovie(Movie& m);
    void addToWatchList(const Movie& m);
    std::vector<Movie> getWatchList() const { return this->watch_list; }
    int getNumberOfMoviesWatchList() const { return this->watch_list.size(); }
    void deleteMovieWatchList(const std::string& title);
};