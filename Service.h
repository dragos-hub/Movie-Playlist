#pragma once
#include "Repository.h"
#include <vector>
#include <string>


class WatchListFile {
public:
    virtual void save(const std::vector<Movie>& watchList, const std::string& fileName) = 0;
    virtual ~WatchListFile() = default;
};

class CSVWatchListFile : public WatchListFile {
public:
    void save(const std::vector<Movie>& watchList, const std::string& fileName) override {
        std::ofstream outFile(fileName);
        if (!outFile.is_open()) {
            throw std::runtime_error("Could not open file: " + fileName);
        }
        for (const auto& movie : watchList) {
            outFile << movie.getTitle() << "," << movie.getGenre() << "," << movie.getYear() << ","
                    << movie.getLikes() << "," << movie.getTrailer() << "\n";
        }
        outFile.close();
    }
};

class HTMLWatchListFile : public WatchListFile {
public:
    void save(const std::vector<Movie>& watchList, const std::string& fileName) override {
        std::ofstream outFile(fileName);
        if (!outFile.is_open()) {
            throw std::runtime_error("Could not open file: " + fileName);
        }
        outFile << "<!DOCTYPE html>\n<html>\n<head>\n<title>Watch List</title>\n</head>\n<body>\n";
        outFile << "<table border=\"1\">\n<tr><th>Title</th><th>Genre</th><th>Year</th><th>Likes</th><th>Trailer</th></tr>\n";
        for (const auto& movie : watchList) {
            outFile << "<tr><td>" << movie.getTitle() << "</td><td>" << movie.getGenre() << "</td><td>"
                    << movie.getYear() << "</td><td>" << movie.getLikes() << "</td><td><a href=\""
                    << movie.getTrailer() << "\">Link</a></td></tr>\n";
        }
        outFile << "</table>\n</body>\n</html>";
        outFile.close();
    }
};

class Service {
private:
    Repository* repo;
    WatchListFile* watchListFile;
    std::string watchListFileType;
public:
    Service(Repository* repo) : repo(repo), watchListFile(nullptr), watchListFileType("csv") {}

    void setWatchListFileType(const std::string& fileType);
    void saveWatchList();
    std::string getWatchListFileType() {return this->watchListFileType;}

    void addMovieService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
    void deleteMovieService(const std::string& title);
    void updateMovieService(const std::string& old_title, const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    std::vector<Movie> getMoviesService() { return this->repo->getMovies(); }
    int getGenreSize(const std::string& genre) { return this->repo->getGenreSize(genre); }
    std::vector<Movie> getMoviesFromGenre(const std::string& genre) { return this->repo->getMoviesFromGenre(genre); }
    int getNumberOfMovies() { return this->repo->getNumberOfMovies(); }

    void addToWatchService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
    void deleteToWatchService(const std::string& title);
    int getNumberWatchedMovies() { return this->repo->getNumberOfMoviesWatchList(); }
    std::vector<Movie> getWatchedMovies() { return this->repo->getWatchList(); }

    ~Service() {
        delete this->watchListFile;
    }
};
