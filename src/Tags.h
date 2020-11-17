// Classe que irá manejar a tabela hash com as tags dos filmes
// A tabela hash armazenará:
// A tag - chave
// Um vetor com os ids dos filmes associados a essa tag

#include <math.h>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

typedef struct tag {
  int movieId = 0;
  string tag = "";
}TAG;


// Estrutura que guarda os dados necessários para manipulação da tabela Hash
typedef struct DadosTabelaTag {
  string tag = "";
  long unsigned int chave;
  // ids
  vector<int> movieIds;
  bool usado = false; //Se já foi usado alguma vez
  bool ocupado = false; // Se está sendo usado no momento
} DADOSTABELATAG;

// Estrutura para o retorno da função que calcula o hash
typedef struct posechave {
  long unsigned int chave;
  int pos;
}POSECHAVE;


class TagsFilme {
  // São 465,564 tags, então uma tabela com esse valor de M deve manter um desempenho bom,
  // ainda mais usando double hashing
  static const int segundoPrimo = 182659;
private:
  const int M;
  vector<DADOSTABELATAG> tabela;
  // Calcula o inteiro correspondente a string de tag
  long unsigned int calcChave(string nome) {
    long unsigned int chave = 0;
    int a = 37;
    for(int i = 0; i < nome.length(); i++) {
      // Atribui um peso a cada caractere do nome
      chave += (int)nome[i] * (int)pow(a, i);
    }
    
    return chave;
  }
  // Retorna uma estrutura com:
  // pos, a posição na tabela
  // chave, a chave calculada a partir da string tag     
  POSECHAVE hash(string tag) {
    int i = 0;
    long unsigned int chave = calcChave(tag);
    int pos = chave % M;
    while(tabela[pos].ocupado && tabela[pos].tag != tag) {
      i++;
      // Segundo hash em caso de colisão
      pos = (chave + (i *(1 + (chave % segundoPrimo)))) % M;
      //printf("POSIÇÃO: %d", pos);
      //printf("pos: %d", pos);
    }
    
    POSECHAVE posEchave;
    posEchave.pos = pos;
    posEchave.chave = chave;
    return posEchave;
  }
public:
  TagsFilme(int size) : M(size), tabela(size){}


  void insere(TAG tag) {
    POSECHAVE posEchave = hash(tag.tag);
    int pos = posEchave.pos;
    long unsigned int chave = posEchave.chave;
    tabela[pos].chave = chave;
    tabela[pos].tag = tag.tag;
    // Testa se o filme já está incluso no vetor de ids
    if(find(tabela[pos].movieIds.begin(), tabela[pos].movieIds.end(), tag.movieId) == tabela[pos].movieIds.end()) {
      tabela[pos].movieIds.push_back(tag.movieId);
    }
    tabela[pos].ocupado = true;
    tabela[pos].usado = true;
  }


  // Busca os dados do filme com tal id,
  // Retorna um vector com os ids dos filmes com aquela tag;
  // Retorna um vector com -1 se não encontrou; 
  vector<int> busca(string tagBusca) {
    int pos = 0;
    POSECHAVE posEchave = hash(tagBusca);
    long unsigned int chave = posEchave.chave;
    int i = 0;
    pos = posEchave.pos;
    do {
      pos = (chave + (i *(1 + (chave % segundoPrimo)))) % M;
      if(tabela[pos].ocupado && tabela[pos].tag == tagBusca) {
        return tabela[pos].movieIds;
      } else {
        i++;
      }
    } while(tabela[pos].usado);
    // Não encontrou filme com esse id  
    vector<int> tmp;
    return tmp;
  }
};

