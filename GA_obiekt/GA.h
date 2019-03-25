#include "std_lib_facilities.h"

class Individual{
public:
	//attributes
	vector<double>guy;
	vector<string>genome;
	double value;
	int fitness;

	Individual(int dim);
	
};


class GA {
public:
	//attributes
	vector<Individual> osobnicy;
	int generation{ 0 };
	double fit;


		//functions
	void genes_coding();
	void mutations();
	void genes_decoding();
	void offspring();
	vector<Individual> fitness(vector<Individual>osobnik,double sum);
	vector<Individual>sort(vector<Individual>osobnik);
	void first_generation();
	void life();
	void RangeProtecting();

};
