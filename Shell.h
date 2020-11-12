#pragma once
#include "csv.h"
#include "TabelaHash.h"
#include "HashRatings.h"
#include "Trie.h"
#include "Tags.h"
#include "HashGenres.h"
#include "TextTable.h"


class Shell
{
public:
	Shell() : hashtable(new TabelaHash()), tabelaTags(new TagsFilme()), hashRatings(138493), trie(), hashGenres(41){}

	void readFiles();
	void readShell();
	void movie(const std::string& str);
	void user(int ID);
	void top10Genre(const std::string& str);
	void tags(std::vector<std::string>& tagList);
	void quicksort(std::vector<std::vector<std::string>>& table, std::vector<int>& ratings, int lo, int hi);
	int partition(std::vector<std::vector<std::string>>& table, std::vector<int>& ratings, int lo, int hi);
	void printTable(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& table, const std::vector<int>& ratings);
private:
	TabelaHash* hashtable;
	TagsFilme* tabelaTags;
	HashRatings hashRatings;
	Trie trie;
	HashGenres hashGenres;
};

