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
	ifstream ifs;
	string filename;
	bool fileForInput = false;
	
	if (argc > 1)
	{
		filename = argv[1];
		fileForInput = true;
	}
	
	while (fileForInput && ifs.is_open() == false)
	{
		if ( filename == "" )
		{
			cout<<"Enter input file:"<<endl;
		   	cin >> filename;
		}
		ifs.open(filename.c_str());
		filename = "";
	}
	
  const int n = 30;
	cout<<" **** N = "<<n<<"  ***** "<<endl;
	
  // const double MAX_TIME = 16000;
  long setupStart = getNow();
	cout<<"Setup: ";
  Vector<double> bVec = genBpdeVector<double>(n);
  // cout<<"genBvec("<<n<<"):  "<<bVec<<endl;
  SymmMatrix<double> aMatrix = genApdeMatrix<double>(n);
  // cout<<"genApdeMatrix("<<n<<") :  "<<endl<<aMatrix<<endl;
  long setupEnd = getNow();
	cout<< (setupEnd-setupStart) <<" milliseconds"<<endl;
  
  FullMatrix<double> fullA(aMatrix);
  GaussianSolver<double> gauss;
  SubstitutionSolver<double> subSolver;
  CholeskySolver<double> cholesky;
  
  cout<<"Gauss solve: ";
	long gaussStart = getNow();
  Vector<double> xVecGauss = gauss(fullA, bVec);
	long gaussEnd = getNow();
	cout<< gaussEnd-gaussStart << " milliseconds "<<endl;
  // cout<<"xVec Gauss = "<<xVecGauss<<endl;

  cout<<"xVec Cholesky solve: ";
	long choleskyStart = getNow();
  Vector<double> xVecCholesky = cholesky(aMatrix, bVec);
	long choleskyEnd = getNow();
	cout<< choleskyEnd-choleskyStart << " milliseconds "<<endl;
	
  cout<< "Error : ";
	long errorStart = getNow();
	Vector<double> errorVec = testApprox(xVecGauss);
	const int size = n-1;
  // const int size = sqrt(errorVec.size());
  FullMatrix<double> errorMatrix(size, size);
  for (int r=0 ; r<size; r++)
    for (int c=0 ; c<size ; c++)
    {
        double val = errorVec[r*c + c];
        errorMatrix(r,c) = val;
    }
	long errorEnd = getNow();
	cout<< (errorEnd-errorStart) <<" milliseconds"<<endl;
	
	cout<<"Total: "<< errorEnd-setupStart << " milliseconds"<<endl;
	
  // cout<<"millis duration: "<<diffTime<<endl;
  // cout<<"Error Matrix : "<<endl;
  // cout<<errorMatrix<<endl;
  
  return 0;
  
	// cout<<"Running unit tests ...."<<endl;
	// testVectorClass();
	// testFullMatrixClass();
	// testSymmMatrixClass();
	
	return 0;
}

