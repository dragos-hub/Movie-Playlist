//
// Created by isacd on 3/30/2025.
//
#include "ui.h"
#include <iostream>
#include <limits>
#include <algorithm>

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message) : std::runtime_error(message) {}
};

class Validator {
public:
    static void validateMovie(const Movie& movie) {
        if (movie.getTitle().empty()) {
            throw ValidationException("Title cannot be empty.");
        }
        if (movie.getGenre().empty()) {
            throw ValidationException("Genre cannot be empty.");
        }
        if (movie.getYear() < 1900 || movie.getYear() > 2025) {
            throw ValidationException("Year must be between 1900 and 2025.");
        }
        if (movie.getLikes() < 0) {
            throw ValidationException("Likes must be non-negative.");
        }
        if (movie.getTrailer().empty()) {
            throw ValidationException("Trailer URL cannot be empty.");
        }
    }
};

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& message) : std::runtime_error(message) {}
};

void UI::run()
{
    std::cout << "Choose file type for watch list (1 for CSV, 2 for HTML): ";
    std::string choice;
    std::cin >> choice;

    if (choice == "1") {
        this->service.setWatchListFileType("csv");
    } else if (choice == "2") {
        this->service.setWatchListFileType("html");
    } else {
        std::cout << "Invalid choice. Defaulting to CSV.\n";
        this->service.setWatchListFileType("csv");
    }
    while (true)
    {
        std::cout << "Enter mode (1 for User Mode 2 for Administator Mode): ";
        std::string mode;
        std::cin >> mode;
        if (mode == "1")
        {
            this->printUserMenu();
            break;
        }
        else if (mode == "2")
        {
            this->printAdmMenu();

            break;
        }
        else
        {
            std::cout << "Invalid mode. Please try again.\n";
        }
    }
}

void UI::printAdmMenu()
{
    while (true)
    {
        std::cout << "1. Add movie.\n";
        std::cout << "2. Delete movie.\n";
        std::cout << "3. Update movie.\n";
        std::cout << "4. Print all movies.\n";
        std::cout << "0. Exit.\n";
        std::string command;
        std::cin >> command;
        if (command == "0")
        {
            break;
        }
        else if (command == "1")
        {
            this->addMovieToAdm();
        }
        else if (command == "2")
        {
            this->deleteMovieFromAdm();
        }
        else if (command == "3")
        {
            this->updateMovieFromAdm();
        }
        else if (command == "4")
        {
            this->printAllMovies();
        }
        else
        {
            std::cout << "Invalid command. Please try again.\n";
        }
    }
}

void UI::addMovieToAdm() {
    std::string title, genre, trailer;
    int year, likes;
    try {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter title: ";
        std::getline(std::cin, title);

        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);

        std::cout << "Enter year: ";
        std::cin >> year;
        if (std::cin.fail()) throw InputException("Invalid input for year.");

        std::cout << "Enter likes: ";
        std::cin >> likes;
        if (std::cin.fail()) throw InputException("Invalid input for likes.");

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter trailer: ";
        std::getline(std::cin, trailer);

        Movie movie(title, genre, year, likes, trailer);
        Validator::validateMovie(movie);
        this->service.addMovieService(title, genre, year, likes, trailer);
    } catch (const ValidationException& e) {
        std::cout << "Validation error: " << e.what() << std::endl;
    } catch (const InputException& e) {
        std::cout << "Input error: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UI::deleteMovieFromAdm() {
    std::string title;
    try {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter title: ";
        std::getline(std::cin, title);

        if (title.empty()) {
            throw InputException("Title cannot be empty.");
        }

        this->service.deleteMovieService(title);
        std::cout << "Movie successfully deleted.\n";
    } catch (const InputException& e) {
        std::cout << "Input error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UI::updateMovieFromAdm() {
    std::string original_title, title, genre, trailer;
    int year, likes;
    try {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter the title of the movie to update: ";
        std::getline(std::cin, original_title);

        if (original_title.empty()) {
            throw InputException("Original title cannot be empty.");
        }

        std::cout << "Enter new title: ";
        std::getline(std::cin, title);

        std::cout << "Enter new genre: ";
        std::getline(std::cin, genre);

        std::cout << "Enter new year: ";
        std::cin >> year;
        if (std::cin.fail()) throw InputException("Invalid input for year.");

        std::cout << "Enter new likes: ";
        std::cin >> likes;
        if (std::cin.fail()) throw InputException("Invalid input for likes.");

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter new trailer: ";
        std::getline(std::cin, trailer);

        Movie movie(title, genre, year, likes, trailer);
        Validator::validateMovie(movie);

        this->service.updateMovieService(original_title, title, genre, year, likes, trailer);
        std::cout << "Movie successfully updated.\n";
    } catch (const ValidationException& e) {
        std::cout << "Validation error: " << e.what() << std::endl;
    } catch (const InputException& e) {
        std::cout << "Input error: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UI::printUserMenu() {
    while (true) {
        std::string choice;
        std::cout << "1. Go through movies of a genre.\n";
        std::cout << "2. Delete a movie from watch list.\n";
        std::cout << "3. See all movies from watch list.\n";
        std::cout << "0. Exit.\n";
        std::cin >> choice;
        if (choice == "0") {
            this->service.saveWatchList();
            break;
        }
        try {
            int choiceInt = std::stoi(choice);
            switch (choiceInt) {
                case 1: {
                    std::cout << "Enter genre: ";
                    std::string genre;
                    std::cin >> genre;

                    std::vector<Movie> genreMovies = this->service.getMoviesFromGenre(genre);

                    if (genre == "-")
                        genreMovies = this->service.getMoviesService();

                    if (genreMovies.empty()) {
                        std::cout << "No movies found for the genre: " << genre << "\n";
                        break;
                    }

                    for (size_t i = 0; i < genreMovies.size(); i++) {
                        const Movie& movie = genreMovies[i];
                        std::cout << movie.getTitle() << " " << movie.getGenre() << " " << movie.getYear() << " " << movie.getLikes() << "\n";
                        std::cout << movie.getTrailer() << "\n";

                        bool alreadyInWatchList = std::any_of(
                            this->service.getWatchedMovies().begin(),
                            this->service.getWatchedMovies().end(),
                            [&movie](const Movie& m) { return m.getTitle() == movie.getTitle(); }
                        );

                        if (!alreadyInWatchList) {
                            std::cout << "Do you like the movie? (1 for yes, 2 for no): ";
                            std::cin >> choice;
                            int likeChoice = std::stoi(choice);

                            if (likeChoice == 1) {
                                this->service.updateMovieService(movie.getTitle(), movie.getTitle(), movie.getGenre(), movie.getYear(), movie.getLikes() + 1, movie.getTrailer());
                            }
                            std::cout << "Add it to watch list? (1 for yes, 2 for no): ";
                            std::cin >> choice;
                            int addChoice = std::stoi(choice);
                            if (addChoice == 1) {
                                this->service.addToWatchService(movie.getTitle(), movie.getGenre(), movie.getYear(), movie.getLikes(), movie.getTrailer());
                                std::cout << "Movie added to watch list.\n";
                            }
                        } else {
                            std::cout << "Movie is already in the watch list. Delete it? (1 for yes, 2 for no): ";
                            std::cin >> choice;
                            if (choice == "1") {
                                this->service.deleteToWatchService(movie.getTitle());
                                std::cout << "Movie deleted from watch list.\n";
                            } else if (choice != "2") {
                                std::cout << "Invalid choice.\n";
                            }
                        }

                        std::cout << "Go next? (1 for yes, 2 for no): ";
                        std::cin >> choice;
                        int continuInt = std::stoi(choice);
                        if (continuInt == 2) {
                            break;
                        } else if (continuInt == 1 && i >= genreMovies.size() - 1) {
                            i = -1; // Reset to start
                        }
                    }
                    break;
                }
                case 2: {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                    std::cout << "Enter title: ";
                    std::string title;
                    std::getline(std::cin, title);
                    try {
                        this->service.deleteToWatchService(title);
                        std::cout << "Movie successfully deleted from the watch list.\n";
                        std::cout << "Did you like the movie? (1 for yes, 2 for no): ";
                        std::cin >> choice;
                        if (choice == "1") {
                            for (const auto& movie : this->service.getMoviesService()) {
                                if (movie.getTitle() == title) {
                                    this->service.updateMovieService(
                                        title,
                                        movie.getTitle(),
                                        movie.getGenre(),
                                        movie.getYear(),
                                        movie.getLikes() + 1,
                                        movie.getTrailer()
                                    );
                                    std::cout << "The number of likes for the movie has been updated.\n";
                                    break;
                                }
                            }
                        }
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 3: {
                    for (const auto& movie : this->service.getWatchedMovies()) {
                        std::cout << movie.getTitle() << " - " << movie.getGenre() << " - " << movie.getYear() << " - " << movie.getLikes() << "\n";
                        std::cout << "Trailer link: " << movie.getTrailer() << "\n";
                    }
                    break;
                }
                case 4: {
                    this->service.saveWatchList();
                    std::string fileType = this->service.getWatchListFileType();
                    std::string fileName = "watchlist." + fileType;
                    if (fileType == "csv") {
                        system(("notepad " + fileName).c_str()); // Open CSV with Notepad
                    } else if (fileType == "html") {
                        system(("start " + fileName).c_str()); // Open HTML with default browser
                    } else {
                        std::cout << "Unknown file type.\n";
                    }
                    break;
                }
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void UI::printAllMovies() {
    for (const auto& movie : this->service.getMoviesService()) {
        std::cout << movie.getTitle() << " - " << movie.getGenre() << " - " << movie.getYear() << " - " << movie.getLikes() << "\n";
        std::cout << "Trailer link: " << movie.getTrailer() << "\n";
    }
}