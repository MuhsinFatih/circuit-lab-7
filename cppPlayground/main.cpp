
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <math.h>
using namespace std;
#include <map>
#define REP(size) for(size_t i=0, length=size; i<length; ++i)
#define REPW(size)  size_t w,length; length=size \
while(w<length)
#define vi  vector<int>
#define vs  vector<string>
#define st  size_t

int main(int argc, const char * argv[]) {
	
	
	
	double freq[] = {
		150,
		318,
		1000,
		1600,
		5000,
		7900,
		10000
	};
	
	double Vout[] {
		4.4,
		4.6,
		4.6,
		4.28,
		3,
		2.18,
		1.8
	};
	double Vin[] {
		9.52,
		10.2,
		10.4,
		10.0,
		10.0,
		10.0,
		10.0
	};
	double gains[7];
	
	
	cout << " ======= GAINS =======\n";
	
	for(int i=0; i<sizeof(freq) / sizeof(double); ++i) {
		gains[i] = Vout[i]/Vin[i];
		printf("%.0f input frequency:\nGain\\;=\\;\\frac{V_{out}}{V_{in}}=\\frac{%.3f}{%.3f}=%.3f\n",freq[i],Vout[i],Vin[i],gains[i]);
	}
	
	cout << "\n\n\n";
	cout << " ==== GAINS in db ====\n";
	
	for(int i=0; i<sizeof(freq) / sizeof(double); ++i) {
		printf("%.0f input frequency:\nGain(db)\\;=\\;20\\log(%.3f)=%.3f\n\n",freq[i], gains[i], 20 * log(gains[i]));
	}
	
	
	
	
	
	double dY1[] {
		0.05,
		0,
		0.1,
		0.2,
		0.3,
		0.25,
		0.2
	};
	
	double dY2[] {
		6.5,
		3,
		5,
		6,
		4,
		2.5,
		2
	};
	
	cout << "\n\n\n";
	cout << " ==== PHASES ====\n";
	
	for(int i=0; i<sizeof(freq) / sizeof(double); ++i) {
		printf("%.0f input frequency:\nPhase\\;=\\frac{%.1f}{%.1f}\\times360=%.1f\n\n",freq[i],dY1[i] * 2,dY2[i], (dY1[i] * 2) / dY2[i] * 360);
	}
	
	
	cout << endl;
	return 0;
}
