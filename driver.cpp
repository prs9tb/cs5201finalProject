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
	
	/*
	cout<< "Error Checking: ";
	long errorStart = getNow();
	Vector<double> errorVec = testApprox(xVecGauss);
	
	const int size = n - 1;
	FullMatrix<double> errorMatrix(size, size);
	for (int r=0 ; r<size; r++)
	for (int c=0 ; c<size ; c++)
	{
		double val = errorVec[r*c + c];
		errorMatrix(r,c) = val;
	}
	long errorEnd = getNow();
	cout<< (errorEnd-errorStart) <<" milliseconds"<<endl;
	
	cout<<"Total: "<< getNow()-setupStart << " milliseconds"<<endl;
	char input;
	
	cout<<"See Error Summary? (y/n) : ";
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		double ele = errorMatrix(0,0);
		double absEle = ele>=0? ele : -ele;
		double errorMin = absEle;
		double errorMax = absEle;
		double errorAvg = 0;
		for (int r=0 ; r<size ; r++)
			for (int c=0 ; c<size ; c++)
			{
				ele = errorMatrix(r,c);
				absEle = ele>=0? ele : -ele;
				if (absEle > errorMax) errorMax = absEle;
				if (absEle < errorMin) errorMin = absEle;
				errorAvg += absEle;
			}
		errorAvg /= size*size;
		
		cout<<"\tError min: "<<errorMin<<endl;
		cout<<"\tError max: "<<errorMax<<endl;
		cout<<"\tError avg: "<<errorAvg<<endl;
	}
	
	cout<<"See Error raw data? (y/n): ";
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		cout<<"Error Matrix : "<<endl;
		cout<<errorMatrix<<endl;
	}
	
	// cout<<"millis duration: "<<diffTime<<endl;
	
	return 0;
	
	// cout<<"Running unit tests ...."<<endl;
	// testVectorClass();
	// testFullMatrixClass();
	// testSymmMatrixClass();
	
	return 0;
	*/
}

