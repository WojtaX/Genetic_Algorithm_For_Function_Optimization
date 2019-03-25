#include<std_lib_facilities.h>


class osobnik{
public:
	//attributes
	vector<double>guy;
	vector<string>genome;
	double value;
	int fitness;

	osobnik(int dim);
	//osobnik():guy{0},genome{0},value{0},fitness{0}{}
};


class GA {
public:
	//attributes
	vector<osobnik> osobnicy;
	int generation{ 0 };

		//functions
	void genes_coding();
	void mutations();
	void genes_decoding();
	void offspring();
	vector<osobnik> fitness(vector<osobnik>osobnik,double sum);
	vector<osobnik>sort(vector<osobnik>osobnik);
	void first_generation();
	void life();

};