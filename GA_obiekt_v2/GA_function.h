#include<std_lib_facilities.h>
#include<C:\Users\Wojtek\source\repos\GA_obiekt\GA_obiekt\GA.h>
#include<bitset>
int size_pop{ 50 };
int dim =1;
double LOW{ -12.6 };
double UP{ 12.6 };
double function(vector<double>x) {
	int dim = x.size();
	double sum = 0;
	for (int i = 0; i < dim; i++) {
		sum +=(1 / (0.1 + abs(x[i]))*(1 + cos(x[i])));
	}
	return sum;
}
double Uniform_Mersenne(double Low, double Up) {
	random_device seed;
	mt19937 gen(seed());
	uniform_real_distribution<double> dist(Low, Up);
	return dist(gen);
}
osobnik::osobnik(int dim) {
		for (int i = 0; i < dim; i++) {
		double v=Uniform_Mersenne(LOW,UP);
		guy.push_back(v);
	}
}
vector<osobnik> GA::sort(vector<osobnik>o) {
	for (int i = 0; i < o.size(); i++) {
		for (int j = 0; j < o.size()-1; j++){
			if (o[j].value > o[j + 1].value)
				swap(o[j], o[j + 1]);
	}
}
	return o;
}

vector<osobnik> GA::replace(vector<osobnik>o) {
	vector<osobnik>temp2;
	for (int i = 0; i < size_pop; i++) {
		if (temp2.size() < size_pop) {
			if (o[i].fitness != 0) {
				if (o[i].fitness > 10) {
					o[i].fitness -= 6;
				}
				for (int j = 0; j < o[i].fitness; j++){
					if (temp2.size() < size_pop) {
						temp2.push_back(o[i]);
					}
				}
			}
		}
	}
	return temp2;
}
void  GA::first_generation() {				
	for (int i = 0; i < size_pop; i++) {
		osobnik w(dim);					
		osobnicy.push_back(w);
	}
}
void GA::check_population() {

	vector<osobnik>pop;
	double sum = 0;
	vector<osobnik>temp;
	for (int i = 0; i < osobnicy.size(); i++) {
		osobnicy[i].value = 0;
		osobnicy[i].value += function(osobnicy[i].guy);
		sum += osobnicy[i].value;
		pop.push_back(osobnicy[i]);
	}
	for (int i{ 0 }; i < size_pop; i++) {
		double fit{ (pop[i].value / sum) * 100 };
		int F{ int(fit) };
		double X = fit - F;
		pop[i].fitness = F;
		double RF{ 0 + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (1 - 0))) };
		if (RF < X)
		{
			pop[i].fitness+=1;
		}
	}
	pop = sort(pop);
	pop=replace(pop);
	swap(osobnicy, temp);
	swap(osobnicy, pop);
	genes_coding();
	mutations(); 
	offspring();
	genes_decoding();
	cout << "\n\n New generation " << "\n\n";
for (int i = 0; i < size_pop; i++) {
			cout <<"Wartosc funkcji: "<< osobnicy[i].value <<" dla osobnika: "<<i+1<<" w pokoleniu: "<< generation+1 << " population size: "<< osobnicy.size()<<"\n";
	}
generation++;
}
void GA::genes_coding() {
	stringstream bits;
	vector<string>temp;
	for (int i = 0; i < size_pop; i++) {
		for (int j = 0; j < osobnicy[i].guy.size(); j++) {
			if (osobnicy[i].guy[j] < 0) {
				osobnicy[i].guy[j] *= (-1);
				bits << "1";
			}
			else {
				bits << "0";
			}
			int Full = osobnicy[i].guy[j];
			double part = osobnicy[i].guy[j];
			double eq = (part - Full) * 100;
			bits << bitset<8>(Full).to_string();
			bits << bitset<8>(eq).to_string();
			temp.push_back(bits.str());
			bits.str("");
		}
		swap(osobnicy[i].genome, temp);
		temp.clear();
	}
}
void GA::mutations() {
	vector<string>temp;
	string s;
	for (int i{ 0 }; i < size_pop; i++) {
		for (int j = 0; j < osobnicy[i].genome.size(); j++) {
			s = osobnicy[i].genome[j];
for (int k{ 0 }; k < s.size(); k++) {
			int RF = Uniform_Mersenne(1, 100);
			if (RF<=18) {
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
		temp.clear();
	}
}
void GA::genes_decoding() {
	vector<int>full;
	vector<double>part;
	vector<double>temp;
	for (int i = 0; i < size_pop; i++) {
		for (int j = 0; j < osobnicy[i].genome.size(); j++) {
			full.clear();
			part.clear();
			string s = osobnicy[i].genome[j];
			if (s[0] == '0') {
				for (int i = 8; i >= 1; i--) {
					full.push_back(s[i] - 48);
				}
				for (int i = 16; i >= 9; i--) {
					part.push_back(s[i] - 48);
				}
				int	F{ 0 };
				double	P{ 0.0 };
				for (int i = 0; i < 8; i++) {
					F += full[i] * pow(2, i);
					P += part[i] * pow(2, i);
				}
				temp.push_back(F + (P / 100.0));
			}
			if (s[0] == '1') {
				for (int i = 8; i >= 1; i--) {
					full.push_back(s[i] - 48);
				}
				for (int i = 16; i >= 9; i--) {
					part.push_back(s[i] - 48);
				}
				int	F{ 0 };
				double	P{ 0.0 };
				for (int i = 0; i < 8; i++) {
					F += full[i] * pow(2, i);
					P += part[i] * pow(2, i);
				}
				temp.push_back(-1 * (F + (P / 100.0)));
			}
		}
		swap(osobnicy[i].guy, temp);
		temp.clear();
	}
	
}
void GA::offspring() {
	vector<string>t;
	stringstream off;
	int Fpoz{ 0 };
	int Mpoz{ 49 };
	int popl{ 0 };
	for (int i = 0; i < size_pop; i++) {
		if (Fpoz <= 25 , Mpoz >25) {
			for (int j = 0; j < osobnicy[i].genome.size(); j++) {
				string s = osobnicy[Fpoz].genome[j];
				string m = osobnicy[Mpoz].genome[j];
				//1st 
				off << '0';
				for (int i = 1; i <= 4; i++) {
					off << s[i];
				}
				for (int i = 5; i <= 8; i++) {
					off << s[i];
				}

				for (int i = 9; i <= 12; i++) {
					off << m[i];
				}
				for (int i = 13; i <= 16; i++) {
					off << m[i];
				}
				t.push_back(off.str());
				swap(osobnicy[popl].genome, t);
				t.clear();
				popl++;
				off.str("");
				//2nd
				off << '1';
				for (int i = 1; i <= 4; i++) {
					off << m[i];
				}
				for (int i = 5; i <= 8; i++) {
					off << m[i];
				}
				for (int i = 9; i <= 12; i++) {
					off << s[i];
				}

				for (int i = 13; i <= 16; i++) {
					off << s[i];
				}
				t.push_back(off.str());
			swap(osobnicy[popl].genome, t);
			t.clear();
			popl++;
				off.str("");

			}
			
			Fpoz++;
			Mpoz--;

		}
	}
	}
void GA::life(int g) {
first_generation();
	for (int i = 0; i < g; i++) {
		check_population();
	}
	
}