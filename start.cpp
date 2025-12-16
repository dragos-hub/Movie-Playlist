// #include <iostream>
// #include "ui.h"
// #include "Repository.h"
// #include "Service.h"
// #include "tests.h"
//
// int main() {
//     // testMovieClass();
//     // testRepository();
//     // testService();
//     // test_getgenre();
//     // testDynamicVector();
//     // testSA();
//     Repository repo;
//     if (repo.getNumberOfMovies() == 0) {
//         repo.addMovie(Movie("Inception", "Sci-Fi", 2010, 2000000, "https://youtu.be/YoHD9XEInc0"));
//         repo.addMovie(Movie("The Dark Knight", "Action", 2008, 2500000, "https://youtu.be/EXeTwQWrcwY"));
//         repo.addMovie(Movie("Interstellar", "Sci-Fi", 2014, 1800000, "https://youtu.be/zSWdZVtXT7E"));
//         repo.addMovie(Movie("The Matrix", "Sci-Fi", 1999, 1700000, "https://youtu.be/vKQi3bBA1y8"));
//         repo.addMovie(Movie("Pulp Fiction", "Crime", 1994, 1600000, "https://youtu.be/s7EdQ4FqbhY"));
//         repo.addMovie(Movie("The Shawshank Redemption", "Drama", 1994, 2300000, "https://youtu.be/6hB3S9bIaco"));
//         repo.addMovie(Movie("The Godfather", "Crime", 1972, 2200000, "https://youtu.be/sY1S34973zA"));
//         repo.addMovie(Movie("The Lord of the Rings: The Return of the King", "Fantasy", 2003, 2100000, "https://youtu.be/r5X-hFf6Bwo"));
//         repo.addMovie(Movie("Forrest Gump", "Drama", 1994, 1900000, "https://youtu.be/bLvqoHBptjg"));
//         repo.addMovie(Movie("Fight Club", "Drama", 1999, 1500000, "https://youtu.be/SUXWAEX2jlg"));
//     }
//     Service service(&repo);
//     UI ui(service);
//     ui.run();
//     return 0;
// }

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include "Repository.h"
#include "Service.h"
#include "GUI.h"
#include "start.moc"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Repository repo("movies.txt", "watchlist.txt");
    if (repo.getNumberOfMovies() == 0) {
        repo.addMovie(Movie("Inception", "Sci-Fi", 2010, 2000000, "https://youtu.be/YoHD9XEInc0"));
        repo.addMovie(Movie("The Dark Knight", "Action", 2008, 2500000, "https://youtu.be/EXeTwQWrcwY"));
        repo.addMovie(Movie("Interstellar", "Sci-Fi", 2014, 1800000, "https://youtu.be/zSWdZVtXT7E"));
        repo.addMovie(Movie("The Matrix", "Sci-Fi", 1999, 1700000, "https://youtu.be/vKQi3bBA1y8"));
        repo.addMovie(Movie("Pulp Fiction", "Crime", 1994, 1600000, "https://youtu.be/s7EdQ4FqbhY"));
        repo.addMovie(Movie("The Shawshank Redemption", "Drama", 1994, 2300000, "https://youtu.be/6hB3S9bIaco"));
        repo.addMovie(Movie("The Godfather", "Crime", 1972, 2200000, "https://youtu.be/sY1S34973zA"));
        repo.addMovie(Movie("The Lord of the Rings: The Return of the King", "Fantasy", 2003, 2100000, "https://youtu.be/r5X-hFf6Bwo"));
        repo.addMovie(Movie("Forrest Gump", "Drama", 1994, 1900000, "https://youtu.be/bLvqoHBptjg"));
        repo.addMovie(Movie("Fight Club", "Drama", 1999, 1500000, "https://youtu.be/SUXWAEX2jlg"));
    }
    Service serv(&repo);
    GUIAdmin gui{serv};
    gui.setWindowTitle("Admin");
    gui.show();

    GUIUser user(serv);
    //repo.addObserver(&user);
    user.setWindowTitle("User");
    user.show();
    return app.exec();
}