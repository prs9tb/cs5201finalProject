/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: driver.cpp
/// Purpose: main program for testing FullMatrix and Vector

#include <iostream>
#include <fstream>
#include <string>

#include "Vector.h"
#include "MatrixBase.h"
#include "FullMatrix.h"
#include "SymmMatrix.h"
#include "GlobalFunctions.h"
#include "GlobalPDE.hpp"
#include "Tests.h"

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
  
  
  UpperTriMatrix<double> upper(aMatrix);
  cout<<"Upper Tri = "<<endl;
  cout<<upper<<endl;
  
  cout<<"Solving for Ax=b : ";
  Vector<double> xVec = upper.solve(bVec);
  cout<<xVec<<endl;
  
  return 0;
  
	cout<<"Running unit tests ...."<<endl;
	
	testVectorClass();
	testFullMatrixClass();
	// testSymmMatrixClass();
	
	return 0;
}

