#include <iostream>
#include <string>
using namespace std;

// Estrutura que guarda os dados usados nas demais partes do programa 
typedef struct dados {
  string titulo = "";
  string generos = "";
  int totAvaliacoes = 0;
  double media = 0;
  int id = 0;
} DADOS;

// Estrutura de leitura dos dados do arquivo rating.csv
typedef struct rating {
  int userId = 0;
  int movieId = 0;
  double avaliacao = 0;
  string timestamp = "";
} RATING;

// Estrutura para a leitura dos dados do arquivo movie.csv
typedef struct movie {
  int movieId = 0;
  string titulo = "";
  string generos = "";
} MOVIE;