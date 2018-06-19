#include<systemc>
#include<iostream>

using namespace std;
using namespace sc_core;

SC_MODULE (hello_world) {

	sc_in<bool> a, b;

	sc_out<bool> c;


	SC_CTOR (hello_world) {
		SC_METHOD(executar);
		sensitive << a << b;
	}

	void executar() {
		if(a.read() && b.read()){
			cout << "Hello World" << endl;
			c.write(!c.read());
		}
	}

};

int sc_main(int argc, char **argv){
	sc_signal<bool> entrada_a, entrada_b, saida_c;

	hello_world hw("hello");

	entrada_a.write(true);
	entrada_b.write(true);

	sc_start();

	hw.a(entrada_a);
	hw.b(entrada_b);
	hw.c(saida_c);

	cout << "" << saida_c.read() << endl;
	return 0;
}

/* pra executar

g++ -I$HOME/systemc/include -L$HOME/systemc/lib-linux64/ hello.cpp -o hello -lm -lsystemc

*/