#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/*-----------------------  Function Declarations -----------------------------*/
//  Initialize the simulation
	void init(double* u, double* uOLD);

//  Calculate the accelertion of each mass
	void forces(double* u, double* a, int step);

//  Integrate newton's equations of motion
	void verlet(double* u, double* uOLD, double* a, int step);

//  Write displacements to file
	void write(double* u);

//  Write k and omega to file
	void writeE(double e, double inert, int step);
/*----------------------------------------------------------------------------*/

/*--------------------------  Global Variables  ------------------------------*/
//  Simulation parameters
int		N = 100,		//  Number of nodes

		STEPS = 100000;	//  Number of time steps

double	D = 1.0,		//  Distance between masses
		K = 1.0,		//	Spring constant
		M = 1.0,		// 	Mass

		F = 2.01,		//  Frequency of exitation 

		dt = 0.01;		//	Time step size

#define PI 3.1415926535897 

/*----------------------------------------------------------------------------*/

//  Main function
int main(){
	
	//  Local variables
	double u[N];	//	Displacement of masses at current timestep
	double uOLD[N];	//	Displacement of masses at previous timestep
	double a[N];	//	Acceleration of each mass


	//  Main loop
//	for(int j = 2; j < 10000; j++){
//		F = j/10000.00;

		//  Initialize simulation
		init(u, uOLD);
		
		for(int i = 0; i < STEPS; i++){
			forces(u, a, i);
			verlet(u, uOLD, a, i);
			if(i % 100 == 0){
				write(u);
			}

			if(i % 100 == 0){
				cout << "Step: " << i << endl;
			}
		}

/*		int e = N-1;
		while(u[e] < 0.0001){
			e = e - 1;
		}
		writeE(e);
		cout << endl << e << endl << endl;*/
//	}
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
void forces(double* u, double* a, int step){
	double forcing_term, inert;

	//  Calculate acceleration of each mass
	for(int i = 0; i < N; i++) {
		if(i == 0){
			forcing_term = 2.5*cos(F*dt*step) / M;
			inert = (- u[i] + u[i+1])*K / M;
			a[i] = forcing_term + inert;
		//	writeE(forcing_term, inert, step);
		}
		else if(i == N-1){
			a[i] = (- u[i] + u[i-1])*K / M;
		}
		else{
			a[i] = (-2.0*u[i] + u[i-1] + u[i+1])*K / M;
		}
	}
}

//  Integrate newton's equations of motion
void verlet(double* u, double* uOLD, double* a, int step){

	double temp[N];
	double d,e;
	for(int i = 0; i < N; i++) {
		temp[i] = u[i];
	}

	for(int i = 0; i < N; i++) {
		//  Enforce left boundary condition
		if(i == 0){
			d = 2.0*u[i] - uOLD[i];
			e = dt*dt*a[i];
			u[i] = d + e;
			writeE(u[i], uOLD[i], step);
		}
		//  Enforce right boundary condition
		else if(i == N-1){
			u[i] =2.0*u[i] - uOLD[i] + dt*dt*a[i];
		}
		else{
			u[i] = 2.0*u[i] - uOLD[i] + dt*dt*a[i];
		}
	}

	for (int i=0; i < N; i++) {
		uOLD[i] = temp[i];
	}
}

//  Write the positions to file
void write(double* u){
	ofstream f;
	f.open("u.dat", std::fstream::app);
	
	for(int i = 0; i < N; i++) {
		//if(i%2==0){
			f << i*D << "\t" << u[i] << endl;
		//}
	}

	f << endl << endl << endl;

	f.close();
}

void writeE(double e, double inert, int step){
	ofstream f;
	f.open("eF.dat", std::fstream::app);
	//double k, w;

	//k = 2*PI/e;
	//w = 2*PI*F;

	//f << k << "\t" << w << endl;
	double t;

	t = step*dt;

	f << t << "\t" << e << "\t" << inert <<  endl;

	f.close();
}

