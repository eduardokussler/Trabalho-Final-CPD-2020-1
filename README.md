# Trabalho-Final-CPD-2020-1
Resolução do trabalho final da disciplina de Classificação e Pesquisa de Dados - UFRGS.
Criação de estrutras para realização de queries no dataset MovieLens 20M. [(disponível aqui)](https://www.kaggle.com/grouplens/movielens-20m-dataset).
Arquivos tag.csv, rating.csv e movie.csv foram usados.

As queries disponíveis são:
* movie < Nome ou prefixo de um filme >, retorna a lista de filmes com nome igual ou com o prefixo
* user < user_id >, retorna os filmes avaliados pelo usuário com a nota dada por esse usuário.
* top< N > "< genero >", N é um número, retorna os topN filmes daquele genero
* tags '< tag1 >' '< tag2 >' ..., retorna os filmes que possuem como tag < tag1 > E < tag2 >... e < tagN >

Para compilar utilize o makefile.

obs:

Foram usadas bibliotecas para [leitura do csv](https://github.com/ben-strasser/fast-cpp-csv-parser) (csv.h) e para imprimir as [tabelas](https://github.com/haarcuba/cpp-text-table) (TextTable.h):



Foi feita uma estrutura para generos, ela coloca todas strings em uppercase na inserção, e a busca coloca a string em uppercase para fazer a busca.
É necessario colocar os arquivos de dados rating.csv, tag_clean.csv e movie_clean.csv em uma pasta Dados_clean.
