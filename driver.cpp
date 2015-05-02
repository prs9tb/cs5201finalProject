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
	
  
  const int n = 4;
  
  
  cout<<"genBvec("<<n<<"):  "<<endl;
  Vector<double> bVec = genBpdeVector<double>(n);
  cout<<bVec<<endl;
  
  cout<<"genApdeMatrix("<<n<<") :  "<<endl;
  SymmMatrix<double> aMatrix = genApdeMatrix<double>(n);
  cout<<aMatrix<<endl;
  
  FullMatrix<double> fullA(aMatrix);
  
  GaussianSolver<double> gauss;
  SubstitutionSolver<double> subSolver;
  CholeskySolver<double> cholesky;
  
  Vector<double> xVecGauss = gauss(fullA, bVec);
  cout<<" xVec Gauss = "<<xVecGauss<<endl;
  
  // LowerTriMatrix<double> lowerA(aMatrix);
  // cout<<"lower Tri = "<<endl;
  // cout<<lowerA<<endl;
  
  Vector<double> xVecCholesky = cholesky(aMatrix, bVec);
  cout<<" xVec Cholesky = "<<xVecCholesky<<endl;
  
  // cout << "Cholesky decomposition: " << endl;
  // cout << cholesky(aMatrix, bVec) << endl;

  
  /*
  Vector<double> xVec = aMatrix.solve(bVec);
  cout<<"Solving for Ax=b : ";
  cout<<xVec<<endl;
  */
  
  //----------------analytical solution--------------------//
  
  
  Vector<double> errorVec = testApprox(xVecGauss);
  
  
  const int size = std::sqrt(errorVec.size());
  
  
  FullMatrix<double> errorMatrix(size, size);
  
  for (int r=0 ; r<size; r++)
    for (int c=0 ; c<size ; c++)
    {
        double val = errorVec[r*c + c];
        errorMatrix(r,c) = val;
    }
    
  cout<<"Error Matrix : "<<endl;
  cout<<errorMatrix<<endl;
  
  
  
  // cout<<"Error: "<<testApprox(xVecCholesky)<<endl;
  
  
  return 0;
  
	cout<<"Running unit tests ...."<<endl;
	
	testVectorClass();
	testFullMatrixClass();
	// testSymmMatrixClass();
	
	return 0;
}

