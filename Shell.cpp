#include "Shell.h"

void Shell::readFiles()
{
    RATING avaliacao;
    MOVIE filme;
    string lixo;
    TAG tagLida;
    int user;

    io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> minirating("./Dados_clean/rating.csv");
    minirating.read_header(io::ignore_no_column, "userId", "movieId", "rating", "timestamp");
    while (minirating.read_row(avaliacao.userId, avaliacao.movieId, avaliacao.avaliacao, lixo)) {
        hashtable->insere(avaliacao);
        hashRatings.insert(avaliacao.userId, avaliacao.movieId, avaliacao.avaliacao);
        //printf("User: %d\nMovieID: %d\nRating: %f\n", avaliacao.userId, avaliacao.movieId,avaliacao.avaliacao);
    }

    io::CSVReader<3, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> movie_clean("./Dados_clean/movie_clean.csv");
    movie_clean.read_header(io::ignore_no_column, "movieId", "title", "genres");
    while (movie_clean.read_row(filme.movieId, filme.titulo, filme.generos)) {
        hashtable->insere(filme);
        trie.insert(filme.titulo, filme.movieId);
        hashGenres.insert(filme.movieId, filme.generos);
        //printf("movieID: %d\n title: %s, genres: %s", filme.movieId, filme.titulo.c_str(), filme.generos.c_str());
    }

    io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> tags("./Dados_clean/tag_clean.csv");
    tags.read_header(io::ignore_no_column, "userId", "movieId", "tag", "timestamp");
    while (tags.read_row(user, tagLida.movieId, tagLida.tag, lixo)) {
        tabelaTags->insere(tagLida);
    }
}

void Shell::readShell()
{

}

void Shell::movie(const std::string& str)
{

}

void Shell::user(int ID)
{

}

void Shell::top10Genre(const std::string& str)
{

}

void Shell::tags(std::vector<std::string>& tagList)
{

}

int Shell::partition(std::vector<std::vector<std::string>>& table, std::vector<int>& ratings, int lo, int hi) {
    int pivot = ratings[lo];
    int i = lo, j = hi + 1;
    while (true) {
        while (ratings[++i] < pivot)
            if (i == hi) break;

        while (pivot < ratings[--j])
            if (j == lo) break;

        if (i >= j)
            break;
        if (ratings[i] != ratings[j]) {
            std::swap(ratings[i], ratings[j]);
            std::swap(table[i], table[j]);
        }
    }
    if (ratings[lo] != ratings[j]) {
        std::swap(table[lo], table[j]);
        std::swap(table[lo], table[j]);
    }
    return j;
}

void Shell::quicksort(std::vector<std::vector<std::string>>& table, std::vector<int>& ratings, int lo, int hi) {
    if (lo < hi) {
        int j = partition(table, ratings, lo, hi);
        quicksort(table, ratings, lo, j - 1);
        quicksort(table, ratings, j + 1, hi);
    }
}

void Shell::printTable(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& table, const std::vector<int>& ratings)
{
    TextTable t('-', '|', '+');

    for (const std::string &header : headers) {
        t.add(header);
    }
    t.endOfRow();

    int i = 0;
    for (const std::vector<std::string> &line: table) {
        for (const std::string& str : line) {
            t.add(str);
        }
        t.add(to_string(ratings[0]));
        ++i;
    }
    t.endOfRow();

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << t;
}
