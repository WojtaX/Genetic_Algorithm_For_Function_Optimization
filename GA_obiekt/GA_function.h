#include "GA.h"
#include<bitset>
int size_pop{ 50 };
int dim =1;
double LOW{ 0 };
double UP{  20};
double function(vector<double>x) {
	int dim = x.size();
	double sum = 0;
	for (int i = 0; i < dim; i++) {
		sum += (1 / (0.1 + abs(x[i]))*(1 + cos(x[i])));
		//sum += sin(x[i]);
		//sum=cos(x[i]);
		//sum += (-x[i])*(-x[i]) + 100;
	}
	return sum;
}

double Uniform_Mersenne(double Low, double Up) {
	random_device seed;
	mt19937 gen(seed());
	uniform_real_distribution<double> dist(Low, Up);
	return dist(gen);
}
int int_Uniform_Mersenne(int Low, int Up) {
	random_device seed;
	mt19937 gen(seed());
	uniform_int_distribution<int> dist(Low, Up);
	return dist(gen);
}
Individual::Individual(int dim) {
		for (int i = 0; i < dim; i++) {
		double first_guy=Uniform_Mersenne(LOW,UP);
		guy.push_back(first_guy);
	}
}
vector<Individual> GA::sort(vector<Individual>o) {
	for (int i = 0; i < o.size(); i++) {
		for (int j = 0; j < o.size()-1; j++){
			if (o[j].value > o[j + 1].value)
				swap(o[j], o[j + 1]);
	}
}
	return o;
}

vector<Individual> GA::fitness(vector<Individual>o,double sum) {
	vector<Individual>temp_population;
	int fitness_size{ 0 };
	double fit_mid{ 0 };
	for (int i{ 0 }; i < size_pop; i++) {
		o[i].fitness = 0;
		double fit{ (o[i].value * 100) / sum };  //procetowy udzial w sumie wartosci 
		int F{ int(fit) };
		double X = fit - F;
		o[i].fitness = F;
		double RF{ 0 + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (1 - 0))) };
		if (RF < X)
		{
			o[i].fitness += 1;
		}
fitness_size += o[i].fitness;
	}
fit_mid=( fitness_size / size_pop );
	for (int i{ 0 }; i < size_pop; i++) {
		if (o[i].fitness != 0) {
			int fit = ((o[i].fitness*size_pop)/100); //ilosc miejsc w populacji na podstawie procentowego udzialu w sumie wartosci 
			if (temp_population.size() != size_pop, o[i].fitness > 0) {
				for (int j{ 0 }; j < fit; j++) {
					if (temp_population.size() != size_pop) {
						temp_population.push_back(o[i]);
					}
				}
			}
		}
}
		while (temp_population.size() != size_pop) {
			int r = int_Uniform_Mersenne(19,31);      //losowanie z przedzialu srednich osobnikow-uzupelnienie luk osobowych 
			temp_population.push_back(osobnicy[r]);
		}
	
	return temp_population;
}
void  GA::first_generation() {				
	for (int i{ 0 }; i < size_pop; i++) {
		Individual w(dim);					
		osobnicy.push_back(w);
	}
}
void GA::life() {
	vector<Individual>pop;
	double sum{ 0 };
	vector<Individual>temp;
	for (int i{ 0 }; i < osobnicy.size(); i++) {
		osobnicy[i].value = 0;
		osobnicy[i].value += function(osobnicy[i].guy);
		sum += osobnicy[i].value;
		pop.push_back(osobnicy[i]);
	}
	pop= fitness(pop,sum) ;
	pop=sort(pop) ;
	vector<Individual>().swap(osobnicy);
	swap(osobnicy, pop);
	
cout << "\n\n New generation " << "\n\n";
double sum_v{ 0 };
for (int i{ 0 }; i < osobnicy.size(); i++) {
	for (int j{ 0 }; j < osobnicy[i].guy.size(); j++) {
		cout << "wartosc " << osobnicy[i].value << " argument " << osobnicy[i].guy[j] << " w pokoleniu " << generation + 1 << " rozmiar populacji " << osobnicy.size() << "\n";
	}
	
	
}


	genes_coding();
	mutations(); 
	offspring();
	genes_decoding();
	//RangeProtecting();
	
generation++;
}
void GA::genes_coding() {
	stringstream bits;
	vector<string>temp;
	for (int i{ 0 }; i < size_pop; i++) {
		for (int j{ 0 }; j < osobnicy[i].guy.size(); j++) {
			if (osobnicy[i].guy[j] < 0) {
				osobnicy[i].guy[j] *= (-1);
				bits << "1";
			}
			else {
				bits << "0";
			}
			int Full{ int(osobnicy[i].guy[j]) };
			double part{ osobnicy[i].guy[j] };
			double eq{ (part - Full) * 100 };
			bits << bitset<8>(Full).to_string();
			bits << bitset<8>(eq).to_string();
			temp.push_back(bits.str());
			bits.str("");
		}
		swap(osobnicy[i].genome, temp);
		vector<string>().swap(temp);
	}
}
void GA::mutations() {
	vector<string>temp;
	for (int i{ 0 }; i < size_pop; i++) {
		for (int j = 0; j < osobnicy[i].genome.size(); j++) {
			string s{ osobnicy[i].genome[j] };
for (int k{ 0 }; k < s.size(); k++) {
	int RF{int( Uniform_Mersenne(1, 100)) };
			if (RF<=9) {
					if (s[k] == '1') {
						s[k] = '0';
					}
					else {
						s[k] = '1';
					}
				}
			
			}
temp.push_back(s);
		}

		swap(osobnicy[i].genome, temp);
		vector<string>().swap(temp);
	}
}
void GA::genes_decoding() {
	vector<int>full;
	vector<double>part;
	vector<double>temp;
	for (int i{ 0 }; i < size_pop; i++) {
		for (int j{ 0 };j < osobnicy[i].genome.size(); j++) {
			vector<int>().swap(full);
			vector<double>().swap(part);
			string s = osobnicy[i].genome[j];
s.size();
			if (s[0] == '0') {
				for (int i{ 8 }; i >= 1; i--) {
					full.push_back(s[i] - 48);
					
				}
				for (int i = 17; i >= 9; i--) {
					part.push_back(s[i] - 48);
				}
				int	F{ 0 };
				double	P{ 0.0 };
				for (int i{ 0 }; i < 8; i++) {
					F += full[i] * pow(2, i);
					P += part[i] * pow(2, i);
				}
				temp.push_back(F + (P / 100.0));
			}
			if (s[0] == '1') {
				for (int i{ 8 }; i >= 1; i--) {
					full.push_back(s[i] - 48);
				}
				for (int i = 17; i >= 9; i--) {
					part.push_back(s[i] - 48);
				}
				int	F{ 0 };
				double	P{ 0.0 };
				for (int i{ 0 }; i < 8; i++) {
					F += full[i] * pow(2, i);
					P += part[i] * pow(2, i);
				}
				temp.push_back(-1 * (F + (P / 100.0)));
			}
		}
		swap(osobnicy[i].guy, temp);
		vector<double>().swap(temp);
	}
	
}
void GA::offspring() {
	vector<string>temp_offspring;
	stringstream off;
	int Fpoz{ 0 };
	int Mpoz{ 49 };
	int popl{ 0 };
	for (int i{ 0 }; i < size_pop; i++) {
		if (Fpoz <= 25 , Mpoz >25) {
			for (int j{ 0 }; j < osobnicy[i].genome.size(); j++) {
				string s{ osobnicy[Fpoz].genome[j] };
				string m{ osobnicy[Mpoz].genome[j] };
				//1st 
				off << '0';
				for (int i{ 1 }; i <= 4; i++) {
					off << s[i];
				}
				for (int i{ 5 }; i <= 9; i++) {
					off << s[i];
				}

				for (int i{ 10 }; i <= 13; i++) {
					off << m[i];
				}
				for (int i{ 14 }; i <= 17; i++) {
					off << m[i];
				}
				temp_offspring.push_back(off.str());
				swap(osobnicy[popl].genome, temp_offspring);
				vector<string>().swap(temp_offspring);
				popl++;
				off.str("");
				//2nd
				off << '1';
				for (int i{ 1 }; i <= 4; i++) {
					off << m[i];
				}
				for (int i{ 5 }; i <= 9; i++) {
					off << m[i];
				}
				for (int i{ 10 }; i <= 13; i++) {
					off << s[i];
				}

				for (int i{ 14 }; i <= 17; i++) {
					off << s[i];
				}
				temp_offspring.push_back(off.str());
			swap(osobnicy[popl].genome, temp_offspring);
			vector<string>().swap(temp_offspring);
			popl++;
				off.str("");

			}
			
			Fpoz++;
			Mpoz--;

		}
	}
	}
void GA::RangeProtecting() {
	for (int i = 0; i < osobnicy.size(); i++) {
		for (int j = 0; j < osobnicy[i].guy.size(); j++) {
			if (osobnicy[i].guy[j] < LOW) {
				osobnicy[i].guy[j] = LOW;
			}
			else
				if (osobnicy[i].guy[j] > UP) {
					osobnicy[i].guy[j] = UP;
				}
		}
	}
}