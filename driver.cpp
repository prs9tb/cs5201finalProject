/// Programmer: Patrick Sullivan, Abira Das
/// Date: 5/1/15
/// Class: CS 5201 (Price)
/// File: driver.cpp
/// Purpose: main program for testing Cholesky and Gaussian on Poisson's Equation

#include <iostream>
#include <fstream>
#include <string>

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
  
  SubstitutionSolver<double> subSolver;
  CholeskySolver<double> cholesky;
  
  
  
  LowerTriMatrix<double> lower(aMatrix);
  cout<<"lower Tri = "<<endl;
  cout<<lower<<endl;
  
  cout << "Cholesky decomposition: " << endl;
  cout << cholesky(aMatrix, bVec) << endl;

  
  /*
  Vector<double> xVec = aMatrix.solve(bVec);
  cout<<"Solving for Ax=b : ";
  cout<<xVec<<endl;
  */
  
  //----------------analytical solution--------------------//
  
  Vector<double> analyticalAnswers((n-1)*(n-1));
  double x = M_PI/n;    //set x and y
  double y = M_PI/n;
  int ans =0;
   
  for(int i =0; i < (n-1) ; i ++)
  {
    for(int j =0; j < (n-1); j ++)
    { 
      analyticalAnswers[ans] = poissonAnalytical(x, y);
      x += M_PI/n;
      ans ++;
    }
    x = M_PI/n;   //bring x back to front
    y += M_PI/n;  //increase y
  }
  
  cout << "Analytical answers for n = " << n << ":" << endl;
  cout << analyticalAnswers << endl;
  
  
  
  return 0;
  
	cout<<"Running unit tests ...."<<endl;
	
	testVectorClass();
	testFullMatrixClass();
	// testSymmMatrixClass();
	
	return 0;
}

