#include<systemc>
#include<iostream>

using namespace std;
using namespace sc_core;

SC_MODULE (full_adder) {

	sc_in<bool> a, b, c_in;

	sc_out<bool> s, c_out;


	SC_CTOR (full_adder) {
		SC_METHOD(somar);
		sensitive << a << b << c_in;
	}

	void somar() {
		s.write(xor(xor(a.read(),b.read()),c_in.read()));
		c_out.write((xor(a.read(),b.read()) && c_in.read()) || (a && b));
	}

	bool xor(bool a, bool b){
		return (!a && b) || ( a && !b);
	}

};

int sc_main(int argc, char **argv){
	sc_signal<bool> a[4], b[4], c[4], zero, overflow;

	int n = 4;

	full_adder *fa[n];


	for (int i = 0; i < n; ++i)
	{
		adder[i] = new full_adder("somador");
	}

	for (int i = 0; i < n; ++i)
	{
		adder[i]->a(a[i]);
		adder[i]->b(b[i]);
		adder[i]->c_out(c[i]);

		if(i == 1) adder[0]->c_in(zero);
		else adder[i]->c_in(adder[i-1]->c_out);
	}

	sc_start();
	
	return 0;
}

/* pra executar

export LD_LIBRARY_PATH=$HOME/systemc/lib-linux64

g++ -I$HOME/systemc/include -L$HOME/systemc/lib-linux64/ fulladder.cpp -o adder -lm -lsystemc && ./adder

*/