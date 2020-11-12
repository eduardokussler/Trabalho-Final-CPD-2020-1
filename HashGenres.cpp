#include "HashGenres.h"


HashGenres::HashGenres(int size)
{
    this->size = size;
    hashTable = std::vector<std::vector<int>>(size, std::vector<int>());
    genre_name = std::vector<std::string>(size,"");
}

const std::vector<int>& HashGenres::get(const std::string &genre)
{
    int hash = hashCode(genre);
    while (genre_name[hash] != genre) {
        hash = (hash + 1) % size;
    }
    return hashTable[hash];
}

void HashGenres::insert(int ID, const std::string &genres)
{
    std::vector<std::string> genre_list = parse(genres);
    for (std::string genre: genre_list) {
        unsigned hash = hashCode(genre);
        while (genre_name[hash] != "" && genre_name[hash] != genre) {
            hash = (hash + 1) % size;
        }
        hashTable[hash].push_back(ID);
        genre_name[hash] = genre;
    }
}

unsigned HashGenres::hashCode(const std::string &genre)
{
    unsigned hash = 0;
    for (int i = 0; i < genre.length(); i++) {
        hash = (genre[i] + (31 * hash)) % size;
    }
    return hash;
}

std::vector<std::string> HashGenres::parse(const std::string &genres)
{
    std::stringstream ss_genres(genres);
    std::vector<std::string> genre_list;
    std::string temp;
    while (std::getline(ss_genres, temp, '|')) {
        genre_list.push_back(temp);
    }
    return genre_list;
}
