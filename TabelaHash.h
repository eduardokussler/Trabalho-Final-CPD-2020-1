// Classe que irá manejar a tabela hash
// A tabela hash armazenará:
// Nome do filme
// Lista de gêneros
// Total de avaliações
// Média das avaliações
// Id do filme - Chave


#include <string>
#include <iostream>
#include "estruturas.h"

using namespace std;



// Estrutura que guarda os dados necessários para manipulação da tabela Hash
typedef struct DadosTabela {
  string titulo = "";
  string generos = "";
  int totAvaliacoes = 0;
  // Soma de todas as notas dadas ao filme
  double somaAval = 0;
  int id = 0;
  bool usado = false; //Se já foi usado alguma vez
  bool ocupado = false; // Se está sendo usado no momento
} DADOSTABELA;




class TabelaHash {
  // São 27,278 ids, então uma tabela com esse valor de M deve manter um desempenho bom,
  // ainda mais usando double hashing
  static const int M = 42337;
  static const int segundoPrimo = 19609;
private:
  DADOSTABELA tabela[M];
  int hash(int id) {
    int i = 0;
     
    int pos = id % M;
    while(tabela[pos].ocupado && tabela[pos].id != id) {
      i++;
      // Segundo hash em caso de colisão
      pos = (id + (i *(1 + (id % segundoPrimo)))) % M;
    }
    
    return pos;
  }
public:
  TabelaHash() = default;


  // Insere pode receber dados de ratings.csv ou de movie.csv, e cada tem um comportamento
  // diferente para cada um


  // Insere recebendo um rating, apenas atualiza a média e o total de avaliações e movieId
  void insere(RATING rating) {
    int pos = hash(rating.movieId);
    // Atualiza os dados relativos à nota
    tabela[pos].totAvaliacoes += 1;
    tabela[pos].somaAval += rating.avaliacao;

    // Caso o arquivo de rating seja acessado primeiro
    // esses campos precisam ser preenchidos para não haver perda de dados
    tabela[pos].id = rating.movieId;
    tabela[pos].ocupado = true;
    tabela[pos].usado = true;
  }

  // Insere recebendo um filme, seta titulo, generos e movieId
  void insere(MOVIE movie) {
    int pos = hash(movie.movieId);
    tabela[pos].ocupado = true;
    tabela[pos].usado = true;
    tabela[pos].titulo = movie.titulo;
    tabela[pos].id = movie.movieId;
    tabela[pos].generos = movie.generos;
  }

  // Busca os dados do filme com tal id,
  // Retorna uma estrutura com id = -1, caso não exista na tabela um filme com aquele id.  
  DADOS busca(int id) {
    int pos = 0;
    int i = 0;
    // Variavel temporária para formar o retorno da função
    DADOS tmp;
    do {
      pos = (id + (i *(1 + (id % segundoPrimo)))) % M;
      if(tabela[pos].ocupado && tabela[pos].id == id) {
        tmp.generos = tabela[pos].generos;
        tmp.id = tabela[pos].id;
        tmp.media = tabela[pos].somaAval / tabela[pos].totAvaliacoes;
        tmp.titulo = tabela[pos].titulo;
        tmp.totAvaliacoes = tabela[pos].totAvaliacoes;
        return tmp;
      } else {
        i++;
      }
    } while(tabela[pos].usado);
    // Não encontrou filme com esse id  
    tmp.id = -1;
    return tmp;
  }
};

