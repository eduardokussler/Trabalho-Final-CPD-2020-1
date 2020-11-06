#include <iostream>
#include <string>
#include "csv.h"
#include "TabelaHash.h"

using namespace io;
using namespace std;

int main() {
  // Leitura do arquivo de rating
  RATING avaliacao;
  MOVIE filme;
  string lixo;
  TabelaHash* hashtable = new TabelaHash();
  CSVReader<4> minirating ("./Dados_clean/minirating.csv");
  minirating.read_header(ignore_no_column,"userId","movieId","rating","timestamp");
  while(minirating.read_row(avaliacao.userId, avaliacao.movieId,avaliacao.avaliacao, lixo)) {
    hashtable->insere(avaliacao);
  }
  CSVReader<3, trim_chars<' '>, double_quote_escape<',','\"'>> movie_clean ("./Dados_clean/movie_clean.csv");
  movie_clean.read_header(ignore_no_column, "movieId", "title","genres");
  while(movie_clean.read_row(filme.movieId, filme.titulo, filme.generos)) {
    hashtable->insere(filme);
    //printf("movieID: %d\n title: %s, genres: %s", filme.movieId, filme.titulo.c_str(), filme.generos.c_str());
  }
  return 0;
}