#pragma once
#include "Service.h"
#include <iostream>

class UI {
private:
    Service service;

public:
    UI(const Service& service) : service{service} {}
    void run();
    void printAdmMenu();
    void printUserMenu();
    void printAllMovies();
    void addMovieToAdm();
    void deleteMovieFromAdm();
    void updateMovieFromAdm();
};