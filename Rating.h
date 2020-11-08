#pragma once

class Rating
{
public:
	Rating(int ID, double rating) : ID(ID), rating(rating){}

	double getRating();
	int getID();
private:
	int ID;
	double rating;
};

