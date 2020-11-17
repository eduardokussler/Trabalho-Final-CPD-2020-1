#pragma once
#include <vector>
#include "Rating.h"

class HashRatings
{
public:
	const std::vector<Rating> empty;

	HashRatings(int size);

	const std::vector<Rating>& get(int val);
	void insert(int val, int ID, double rating);
private:
	int hashCode(int val);

	std::vector<std::vector<Rating>> hashTable;
};

