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
    }

    io::CSVReader<3, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> movie_clean("./Dados_clean/movie_clean.csv");
    movie_clean.read_header(io::ignore_no_column, "movieId", "title", "genres");
    while (movie_clean.read_row(filme.movieId, filme.titulo, filme.generos)) {
        hashtable->insere(filme);
        trie.insert(filme.titulo, filme.movieId);
        hashGenres.insert(filme.movieId, filme.generos);
    }

    io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> tags("./Dados_clean/tag_clean.csv");
    tags.read_header(io::ignore_no_column, "userId", "movieId", "tag", "timestamp");
    while (tags.read_row(user, tagLida.movieId, tagLida.tag, lixo)) {
        tabelaTags->insere(tagLida);
    }
    std::cout << "Estruturas Carregadas" << std::endl;
}

string Shell::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first){
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> Shell::parseTags(std::string str) {
    str = trim(str);
    std::vector<std::string> lst;
    std::string delimiter = "'";

    if (str[0] != '\'')
        throw exception();
    str[0] = ' ';
    std::size_t pos;
    while((pos = str.find(delimiter)) != std::string::npos) {
        std::string token = str.substr(0, pos);
        token = token.substr(1,token.size() - 1);
        //token = trim(token);
        lst.push_back(token);
        str.erase(0, pos + delimiter.length());
        str = trim(str);
        if (str.length() == 0) {
            return lst;
        }
        if (str[0] != '\'') {
            throw exception();
        }
        str[0] = ' ';
    }
    throw exception();
}

bool Shell::OnlySpaces(const std::string &str) {
    for(auto i:str) {
        if (i != ' ')
            return false;
    }
    return true;
}

void Shell::readShell()
{
    std::string name;
    std::cout << "$ ";
    while(std::getline(std::cin, name)) {
        std::string delimiter = " ";
        auto pos = name.find(delimiter);
        
        std::string token = name.substr(0, pos); 
        name.erase(0, pos + delimiter.length());
        ////name.
        try {
            if ((token == "exit" && pos == std::string::npos) || (token== "exit" && OnlySpaces(name)))
                break;
            if(pos == std::string::npos) {
                throw exception();
            }
            if(token == "user") {
                int userID = std::stoi(name);
                user(userID);
            }else if (token == "tags") {
                auto lstTags = parseTags(name);
                tags(lstTags);
            }else if (token == "movie") {
                name = trim(name);
                if (name.size() == 0) 
                    throw exception();
                movie(name);
            } else if (token.size() >= 3 && token.substr(0, 3) == "top"){
                int n = std::stoi(token.erase(0, 3));
                if (n <= 0)
                    throw exception();
                name = trim(name);

                if (name.size() == 0) 
                    throw exception();
                topGenre(n, name);
            } else {
                std::cout << "Unknown Command" << std::endl;
            }
        } catch(exception e) {
            std::cout << "Invalid Args" << std::endl;
        }
        std::cout << "$ ";
    }
}

void Shell::movie(const std::string& str)
{
    std::vector<DADOS> filmes;
    auto lstIDS = trie.substringSearch(str);
    for(auto ids: lstIDS){
        filmes.push_back(hashtable->busca(ids));
    }
    quicksort_mean(filmes, 0, filmes.size() - 1);
    printTable(filmes);
}

void Shell::user(int ID)
{
    std::vector<Rating> lstRatings = hashRatings.get(ID);
    std::vector<DADOS> filmes;
    for(auto rating: lstRatings) {
        filmes.push_back(hashtable->busca(rating.getID()));
    }
    printTable(filmes,lstRatings);
}

void Shell::topGenre(int n, const std::string& str)
{
    auto lstIDS = hashGenres.get(str);
    std::vector<DADOS> filmes;
    for(auto id: lstIDS) {
        filmes.push_back(hashtable->busca(id));
    }
    quicksort_mean(filmes, 0, filmes.size() - 1);
    std:vector<DADOS> maisde1000;
    for(DADOS filme: filmes) {
        if(maisde1000.size() == n)
            break;
        if(filme.totAvaliacoes >= 1000) {
            maisde1000.push_back(filme);
        }
    }
    printTable(maisde1000);
}

void Shell::tags(std::vector<std::string>& tagList)
{
    std::vector<int> ids;
    std::vector<DADOS> filmes;
    DADOS buscado;

    ids = tabelaTags->busca(tagList[0]);

    for(int id: ids){
        buscado = hashtable->busca(id);
        filmes.push_back(buscado);
    }  
    for(int i = 1; i < tagList.size(); ++i) {
        std::vector<DADOS> temp;
        ids = tabelaTags->busca(tagList[i]);
        for(int id: ids){
            buscado = hashtable->busca(id);
            temp.push_back(buscado);
        }

        filmes = intersection(filmes,temp);
    }

    printTable(filmes);
}


std::vector<DADOS> Shell::intersection(std::vector<DADOS> l1, std::vector<DADOS> l2) {
    std::vector<DADOS> lnew;
    for(auto v1: l1) {
        if(find(l2.begin(), l2.end(), v1) != l2.end()) {
            lnew.push_back(v1);
        }   
    }
    return lnew;
}


int Shell::partition_id(std::vector<DADOS> &filmes, int lo, int hi) {
    int pivot = filmes[lo].id;
    int i = lo, j = hi + 1;
    while (true) {
        while (filmes[++i].id > pivot)
            if (i == hi) break;

        while (pivot > filmes[--j].id)
            if (j == lo) break;

        if (i >= j)
            break;
        if (filmes[i] != filmes[j]) {
            std::swap(filmes[i], filmes[j]);
        }
    }
    if (filmes[lo] != filmes[j]) {
        std::swap(filmes[lo], filmes[j]);
    }
    return j;
}

void Shell::quicksort_id(std::vector<DADOS> &filmes, int lo, int hi) {
    if (lo < hi) {
        int j = partition_id(filmes, lo, hi);
        quicksort_id(filmes, lo, j - 1);
        quicksort_id(filmes, j + 1, hi);
    }
}


int Shell::partition_mean(std::vector<DADOS> &filmes, int lo, int hi) {
    double pivot = filmes[lo].media;
    int i = lo, j = hi + 1;
    while (true) {
        while (filmes[++i].media > pivot)
            if (i == hi) break;

        while (pivot > filmes[--j].media)
            if (j == lo) break;

        if (i >= j)
            break;
        if (filmes[i] != filmes[j]) {
            std::swap(filmes[i], filmes[j]);
        }
    }
    if (filmes[lo] != filmes[j]) {
        std::swap(filmes[lo], filmes[j]);
    }
    return j;
}

void Shell::quicksort_mean(std::vector<DADOS> &filmes, int lo, int hi) {
    if (lo < hi) {
        int j = partition_mean(filmes, lo, hi);
        quicksort_mean(filmes, lo, j - 1);
        quicksort_mean(filmes, j + 1, hi);
    }
}

void Shell::printTable(const std::vector<DADOS>& table)
{
    TextTable t('-', '|', '+');
    std::vector<std::string> headers = {"movieID","Title","Genres","Rating","Count"};

    for (const std::string &header : headers) {
        t.add(header);
    }
    t.endOfRow();

    if(table.empty()) {
        t.add("");
        t.add("");
        t.add("");
        t.add("");
        t.add("");
        t.endOfRow();
    }

    for(DADOS line: table) {
        t.add(std::to_string(line.id));
        t.add(line.titulo);
        t.add(line.generos);
        t.add(std::to_string(line.media));
        t.add(std::to_string(line.totAvaliacoes));
        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << t;
}

void Shell::printTable(const std::vector<DADOS>& table, std::vector<Rating> &ratings)
{
    TextTable t('-', '|', '+');
    std::vector<std::string> headers = {"Rating","movieID","Title","Genres","Rating","Count"};

    for (const std::string &header : headers) {
        t.add(header);
    }
    t.endOfRow();

    int i = 0;
    if(table.empty()) {
        t.add("");
        t.add("");
        t.add("");
        t.add("");
        t.add("");
        t.add("");
        t.endOfRow();
    }

    for(DADOS line: table) {
        t.add(std::to_string(ratings[i].getRating()));
        t.add(std::to_string(line.id));
        t.add(line.titulo);
        t.add(line.generos);
        t.add(std::to_string(line.media));
        t.add(std::to_string(line.totAvaliacoes));
        t.endOfRow();
        ++i;
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << t;
}
