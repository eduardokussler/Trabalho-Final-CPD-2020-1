#include <iostream>
#include <string>
#include "csv.h"
#include "TabelaHash.h"
#include "Tags.h"

using namespace io;
using namespace std;

int main() {
  // Leitura do arquivo de rating
  RATING avaliacao;
  MOVIE filme;
  string lixo;
  DADOS busca;
  TabelaHash* hashtable = new TabelaHash();
  TagsFilme* tabelaTags = new TagsFilme();
  CSVReader<4, trim_chars<' '>, double_quote_escape<',','\"'>> minirating ("./Dados_clean/rating.csv");
  minirating.read_header(ignore_no_column,"userId","movieId","rating","timestamp");
  while(minirating.read_row(avaliacao.userId, avaliacao.movieId,avaliacao.avaliacao, lixo)) {
    hashtable->insere(avaliacao);
    //printf("User: %d\nMovieID: %d\nRating: %f\n", avaliacao.userId, avaliacao.movieId,avaliacao.avaliacao);
  }
  CSVReader<3, trim_chars<' '>, double_quote_escape<',','\"'>> movie_clean ("./Dados_clean/movie_clean.csv");
  movie_clean.read_header(ignore_no_column, "movieId", "title","genres");
  while(movie_clean.read_row(filme.movieId, filme.titulo, filme.generos)) {
   hashtable->insere(filme);
   //printf("movieID: %d\n title: %s, genres: %s", filme.movieId, filme.titulo.c_str(), filme.generos.c_str());
  }
 
  CSVReader<4, trim_chars<' '>, double_quote_escape<',','\"'>> tags ("./Dados_clean/tag_clean.csv");
  tags.read_header(ignore_no_column,"userId","movieId","tag","timestamp");
  TAG tagLida;
  int user;
  while(tags.read_row(user, tagLida.movieId, tagLida.tag, lixo)) {
    tabelaTags->insere(tagLida);
  }
  // Resultado esperado = 8641
  cout << tabelaTags->busca("Steve Carell")[0] << endl;
  return 0;
}