#include <iostream>
#include <string>
#include "HashRatings.h"
#include "Trie.h"
#include "csv.h"


void teste1() {
    double rating;
    int user, movie;
    std::string lixo;

    HashRatings hr(138493);
    io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> ratings("./Dados_clean/rating.csv");
    ratings.read_header(io::ignore_no_column, "userId", "movieId", "rating", "timestamp");
    while (ratings.read_row(user, movie, rating, lixo)) {
        hr.insert(user, movie, rating);
    }

    auto ls = hr.get(4);
    for (auto i : ls) {
        std::cout << i.getID() << " " << i.getRating() << std::endl;
    }
}

void teste2() {
    int ID;
    std::string movie;
    std::string lixo;

    Trie tr;
    io::CSVReader<3, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> movie_clean("./Dados_clean/movie_clean.csv");
    movie_clean.read_header(io::ignore_no_column, "movieId", "title", "genres");
    while (movie_clean.read_row(ID, movie, lixo)) {
        tr.insert(movie, ID);
    }

    auto ls = tr.substringSearch("Star Wa");
    for (auto i : ls) {
        std::cout << i << std::endl;
    }
}

int main() {
    teste1();
    teste2();
    return 0;
}