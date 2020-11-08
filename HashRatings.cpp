#include "HashRatings.h"

HashRatings::HashRatings(int size)
{
    hashTable = std::vector<std::vector<Rating>>(size, std::vector<Rating>());
}

int HashRatings::hashCode(int val)
{
    return val;
}

void HashRatings::insert(int val, int ID, double rating)
{
    hashTable[hashCode(val)].push_back(Rating(ID,rating));
}

const std::vector<Rating> &HashRatings::get(int val)
{
    return hashTable[hashCode(val)];
}
