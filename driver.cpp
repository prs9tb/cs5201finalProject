/// Programmer: Patrick Sullivan, Abira Das
/// Date: 5/1/15
/// Class: CS 5201 (Price)
/// File: driver.cpp
/// Purpose: main program for testing Cholesky and Gaussian on Poisson's Equation

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "Vector.h"
#include "MatrixBase.h"
#include "FullMatrix.h"
#include "SymmMatrix.h"
#include "GlobalFunctions.h"
#include "GlobalPDE.h"
#include "Tests.h"
#include "SubstitutionSolver.h"
#include "GaussianSolver.h"
#include "CholeskySolver.h"

using namespace std;

int main(int argc, char * argv[])
{
	int n;
	if(argc == 1)
	{
		cout<<"Enter N:";
		cin >> n;
	}
	else
		n = atoi(argv[1]);
	cout<<" ****** N = "<<n<<" ******* "<<endl;
	
	long setupStart = getNow();
	cout<<"Setup: ";
	Vector<double> bVec = genBpdeVector<double>(n);
	SymmMatrix<double> aMatrix = genApdeMatrix<double>(n);
	long setupEnd = getNow();
	cout<< (setupEnd-setupStart) <<" milliseconds"<<endl;
	
	FullMatrix<double> fullA(aMatrix);
	GaussianSolver<double> gauss;
	SubstitutionSolver<double> subSolver;
	CholeskySolver<double> cholesky;
	
	cout<<" ****** Gaussian Elimination ******"<<endl;
	cout<<"Solve time: ";
	long gaussStart = getNow();
	Vector<double> xVecGauss = gauss(fullA, bVec);
	long gaussEnd = getNow();
	cout<< gaussEnd-gaussStart << " milliseconds "<<endl;
	analyzeApproximation(xVecGauss);
	
	cout<<endl<<" ****** Cholesky Decomposition and Substitution ******"<<endl;
	cout<<"Solve time: ";
	long choleskyStart = getNow();
	Vector<double> xVecCholesky = cholesky(aMatrix, bVec);
	long choleskyEnd = getNow();
	cout<< choleskyEnd-choleskyStart << " milliseconds "<<endl;
	analyzeApproximation(xVecCholesky);	
	
	cout<<" ******** THE END *********"<<endl;
	return 0;
}

