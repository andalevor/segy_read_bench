#include <ISEGY.hpp>
#include <iostream>

using namespace sedaman;
using namespace std;

int main(){
	ISEGY sgy("filt_mig.sgy");
	double sum = 0.0;
	while (sgy.has_trace()) {
		Trace trc = sgy.read_trace();
		for (auto samp : trc.samples())
			sum += samp;
	}
	cout << "Sum = " << sum << endl;
}
