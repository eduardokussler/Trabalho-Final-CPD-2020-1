#pragma once
#include <iostream>
#include "csv.h"
#include "TabelaHash.h"
#include "HashRatings.h"
#include "Trie.h"
#include "Tags.h"
#include "HashGenres.h"
#include "TextTable.h"
#include <algorithm>



class Shell
{
public:
	Shell() : hashtable(new TabelaHash()), tabelaTags(new TagsFilme()), hashRatings(138494), trie(), hashGenres(41){}

	void readFiles();
	void readShell();
	void movie(const std::string& str);
	void user(int ID);
	string trim(const string& str);
	void topGenre(int n, const std::string& str);
	void tags(std::vector<std::string>& tagList);
	void quicksort_id(std::vector<DADOS> &filmes, int lo, int hi);
	int partition_id(std::vector<DADOS> &filmes, int lo, int hi);
	void quicksort_mean(std::vector<DADOS> &filmes, int lo, int hi);
	int partition_mean(std::vector<DADOS> &filmes, int lo, int hi);
	std::vector<DADOS> intersection(std::vector<DADOS> l1, std::vector<DADOS> l2);
	void printTable(const std::vector<DADOS>& table);
	void printTable(const std::vector<DADOS>& table, std::vector<Rating> &ratings);
	std::vector<std::string>parseTags(std::string str);
	bool OnlySpaces(const std::string &str);
private:
	TabelaHash* hashtable;
	TagsFilme* tabelaTags;
	HashRatings hashRatings;
	Trie trie;
	HashGenres hashGenres;
};

