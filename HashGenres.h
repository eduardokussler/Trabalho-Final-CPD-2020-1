#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

class HashGenres
{
public:
	const std::vector<int> empty;

	HashGenres(int size);

	const std::vector<int>& get(std::string genre);
	void insert(int ID, std::string genres);
private:
	unsigned hashCode(const std::string &genre);
	std::vector<std::string> parse(const std::string &genres);;

	int size;
	std::vector<std::string> genre_name;
	std::vector<std::vector<int>> hashTable;
};

