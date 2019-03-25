#include<iostream>
#include "GA_function.h"
using namespace std;
int main() {

	GA t;
	t.first_generation();
	
	for (int i = 0; i < 20; i++) {
		t.life();
	}
	

	keep_window_open();
	return 0;
}