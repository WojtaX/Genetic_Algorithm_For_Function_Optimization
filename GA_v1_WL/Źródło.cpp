#include<iostream>
#include<C:\Users\Wojtek\source\repos\GA_obiekt\GA_obiekt\GA_function.h>
using namespace std;
int main() {

	GA t;
	t.first_generation();
	
	for (int i = 0; i < 50; i++) {
		t.life();
	}
	

	keep_window_open();
	return 0;
}