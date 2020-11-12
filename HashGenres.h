#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class HashGenres
{
public:
	HashGenres(int size);

	const std::vector<int>& get(const std::string &genre);
	void insert(int ID, const std::string &genres);
private:
	unsigned hashCode(const std::string &genre);
	std::vector<std::string> parse(const std::string &genres);;

	int size;
	std::vector<std::string> genre_name;
	std::vector<std::vector<int>> hashTable;
};

