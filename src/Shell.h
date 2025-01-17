#pragma once
#include <iostream>
#include "../libs/csv.h"
#include "TabelaHash.h"
#include "HashRatings.h"
#include "Trie.h"
#include "Tags.h"
#include "HashGenres.h"
#include "../libs/TextTable.h"
#include <algorithm>



class Shell
{

public:
	Shell(int sizeHM, int sizeHT, int sizeHR, int sizeHG) : hashtable(std::make_shared<TabelaHash>(sizeHM)), tabelaTags(std::make_shared<TagsFilme>(sizeHT)), hashRatings(sizeHR), trie(), hashGenres(sizeHG){}
	void readFiles();
	void readShell();
private:
	void movie(const std::string& str);
	void user(int ID);
	void topGenre(int n, const std::string& str);
	void tags(std::vector<std::string>& tagList);

	void printTable(const std::vector<DADOS>& table);
	void printTable(const std::vector<DADOS>& table, std::vector<Rating> &ratings);

	string trim(const string& str);
	int partition_mean(std::vector<DADOS> &filmes, int lo, int hi);
	void quicksort_mean(std::vector<DADOS> &filmes, int lo, int hi);
	std::vector<DADOS> intersection(std::vector<DADOS> l1, std::vector<DADOS> l2);
	std::vector<std::string> parseTags(std::string str);
	bool OnlySpaces(const std::string &str);

	std::shared_ptr<TabelaHash> hashtable;
	std::shared_ptr<TagsFilme> tabelaTags;
	HashRatings hashRatings;
	Trie trie;
	HashGenres hashGenres;
};

