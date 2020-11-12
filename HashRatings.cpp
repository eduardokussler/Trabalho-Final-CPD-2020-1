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
    if (val < 0 || val > hashTable.size() - 1) {
        return empty;
    }
    return hashTable[hashCode(val)];
}
