
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
		50,
		97,
		250,
		482,
		1000,
		2000,
		2400
	};
	
	double Vout[] {
		0.936,
		1.78,
		4.12,
		6.48,
		8.16,
		8.96,
		8.96
	};
	double Vin[] {
		9.44,
		9.44,
		9.28,
		9.28,
		9.28,
		9.44,
		9.44
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
		1,
		0.2,
		0.3,
		0.3,
		0.2,
		0.1,
		0.1
	};
	
	double dY2[] {
		4,
		2,
		4,
		4,
		5,
		5,
		4
	};
	
	cout << "\n\n\n";
	cout << " ==== PHASES ====\n";
	
	for(int i=0; i<sizeof(freq) / sizeof(double); ++i) {
		printf("%.0f input frequency:\nPhase\\;=\\frac{%.1f}{%.0f}\\times360=%.1f\n\n",freq[i],dY1[i],dY2[i], dY1[i]/dY2[i] * 360);
	}
	
	cout << endl;
	return 0;
}
