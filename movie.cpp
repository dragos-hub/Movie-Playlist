//
// Created by isacd on 3/29/2025.
//

#include "movie.h"
#include <string>
#include <stdexcept>

class InvalidYearException : public std::runtime_error {
public:
  explicit InvalidYearException(const std::string& message)
      : std::runtime_error(message) {}
};

Movie::Movie() : title{""}, genre{""}, year{0}, likes{0}, trailer{""}
{
}

// Parameterized constructor
Movie::Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
    : title{title}, genre{genre}, year{year}, likes{likes}, trailer{trailer} {
  if (year < 1900 || year > 2025) {
    throw InvalidYearException("Year must be between 1900 and 2025.");
  }
  if (likes < 0) {
    throw std::invalid_argument("Likes must be positive.");
  }
}

// Destructor
Movie::~Movie() {
}

// Function to update movie details
void Movie::updateMovie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
  if (year < 1900 || year > 2025) {
    throw InvalidYearException("Year must be between 1900 and 2025.");
  }
  if (likes < 0) {
    throw std::invalid_argument("Likes must be positive.");
  }
  this->title = title;
  this->genre = genre;
  this->year = year;
  this->likes = likes;
  this->trailer = trailer;
}