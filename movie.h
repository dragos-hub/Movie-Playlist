#pragma once
#include <string>
#include <iostream>
#include <fstream>



class Movie {
private:
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;

public:
    Movie();
    Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
    ~Movie();
    void updateMovie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
    std::string getTitle() const { return this->title; }
    std::string getGenre() const { return this->genre; }
    int getYear() const { return this->year; }
    int getLikes() const { return this->likes; }
    std::string getTrailer() const { return this->trailer; }
};

// Overload the insertion operator for writing a Movie to a file or console
inline std::ostream& operator<<(std::ostream& out, const Movie& movie) {
    out << movie.getTitle() << "," << movie.getGenre() << "," << movie.getYear() << ","
        << movie.getLikes() << "," << movie.getTrailer();
    return out;
}

// Overload the extraction operator for reading a Movie from a file or console
inline std::istream& operator>>(std::istream& in, Movie& movie) {
    std::string title, genre, trailer;
    int year, likes;

    std::getline(in, title, ',');
    std::getline(in, genre, ',');
    in >> year;
    in.ignore(1, ','); // Ignore the comma
    in >> likes;
    in.ignore(1, ','); // Ignore the comma
    std::getline(in, trailer);

    if (!title.empty() && !genre.empty() && !trailer.empty()) {
        movie = Movie(title, genre, year, likes, trailer);
    }
    return in;
}