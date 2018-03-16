#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/*-----------------------  Function Declarations -----------------------------*/
//  Initialize the simulation
	void init(double* u, double* uOLD);

//  Calculate the accelertion of each mass
	void forces(double* u, double* a);

//  Integrate newton's equations of motion
	void verlet(double* u, double* uOLD, double* a, int step);

//  Write displacements to file
	void write(double* u);

//  Write k and omega to file
	void writeE(double e);
/*----------------------------------------------------------------------------*/

/*--------------------------  Global Variables  ------------------------------*/
//  Simulation parameters
int		N = 10000,		//  Number of nodes
		STEPS = 0;	//  Number of time steps

double	D = 1.0,		//  Distance between masses
		K = 1.0,		//	Spring constant
		M = 1.0,		// 	Mass

		F = 0.01,		//  Frequency of exitation 

		dt = 0.1;		//	Time step size

#define PI 3.1415926535

/*----------------------------------------------------------------------------*/

//  Main function
int main(){
	
	//  Local variables
	double u[N];	//	Displacement of masses at current timestep
	double uOLD[N];	//	Displacement of masses at previous timestep
	double a[N];	//	Acceleration of each mass


	//  Main loop
	for(int j = 2; j < 10000; j++){
		F = j/10000.00;

		//  Initialize simulation
		init(u, uOLD);
		
		for(int i = 0; i < 1/(dt*F); i++){
			forces(u, a);
			verlet(u, uOLD, a, i);
			//write(u);

			if(i % 100 == 0){
			//	cout << i << endl;
			}
		}

		int e = N-1;
		while(u[e] < 0.0001){
			e = e - 1;
		}
		writeE(e);
		cout << endl << e << endl << endl;
	}
}

//  Initialize
void init(double* u, double* uOLD){

	//  Initialize displacement of masses
	for(int i = 0; i < N; i++) {
		u[i] = 0;
		uOLD[i] = 0;
	}
}


//  Calculate the accelertion of each mass
void forces(double* u, double* a){

	//  Calculate acceleration of each mass
	for(int i = 0; i < N; i++) {
		if(i == 0){
			a[i] = - (2*u[i] - u[i+1])*K / M;
		}
		else if(i == N-1){
			a[i] = - (2*u[i] - u[i-1])*K / M;
		}
		else{
			a[i] = (-2*u[i] + u[i-1] + u[i+1])*K / M;
		}
	}
}

//  Integrate newton's equations of motion
void verlet(double* u, double* uOLD, double* a, int step){


	for(int i = 0; i < N; i++) {
		double temp = u[i];
		//  Enforce left boundary condition
		if(i == 0 && 2*PI*F*dt*step <= 2*PI){
			u[i] = 0.05*sin(2*PI*F*dt*step);
		}
		//  Enforce right boundary condition
		else if(i == N-1){
			u[i] = 2*u[i] - uOLD[i] + dt*dt*a[i];
		}
		else{
			u[i] = 2*u[i] - uOLD[i] + dt*dt*a[i];
		}
		uOLD[i] = temp;
	}
}

//  Write the positions to file
void write(double* u){
	ofstream f;
	f.open("u.dat", std::fstream::app);
	
	for(int i = 0; i < N; i++) {
		if(i%2==0){
			f << i*D << "\t" << u[i] << endl;
		}
	}

	f << endl << endl << endl;

	f.close();
}

void writeE(double e){
	ofstream f;
	f.open("eF.dat", std::fstream::app);
	double k, w;

	k = 2*PI/e;
	w = 2*PI*F;

	f << k << "\t" << w << endl;

	f.close();
}

