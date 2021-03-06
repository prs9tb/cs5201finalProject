//Abira Das and Patrick Sullivan
//GlobalPDE.hpp
//functions for generating the A & b matricies
//of Poisson's equation

#include "GlobalPDE.h"

using namespace std;

// HOW TO CALL::::
// approx = pdeApproxmate<DataType, MatrixType>(n, solver);

template <class DT, class MT, class ST>
Vector<DT> pdeApproximate(const int n, const ST& solver)
{
	Vector<DT> bVector = genBpdeVector<DT>(n);
	MT aMatrix(genApdeMatrix<DT>(n));
	Vector<DT> approximations = solver(aMatrix, bVector);
	return approximations;
}

template <class DT>
SymmMatrix<DT> genApdeMatrix(unsigned int n)
{
	const int size = (n-1)*(n-1);
	SymmMatrix<DT> aMatrix(size, size);
	
	const DT oneEle(1);
	const DT negQuarterEle( -1.0/4.0 );
	int col;
	
	for (int diag=0 ; diag<size ; diag++)   //set diagonals to 1
		aMatrix(diag,diag) = oneEle;
	
	const int skip = n-1 ;
	for (int row=1 ; row<size ; row++)    //set -1/4 diagonal with skips
	{
		if ( row % skip == 0)
			continue;
		col = row - 1;
		aMatrix(row, col) = negQuarterEle;
	}
	
	for (int row=n-1 ; row<size ; row++)  //set -1/4 diagonal without skips
	{
		col = row - (n-1);
		aMatrix(row,col) = negQuarterEle;
	}
	
	return aMatrix;
}

template <class DT>
Vector<DT> genBpdeVector(int n)
{
	Vector<DT> bVector((n-1) * (n-1));
	
	double deltaX = (X_MAX - X_MIN) / n;
	double deltaY = (Y_MAX - Y_MIN) / n;
	int bIndex = 0;
	
	double left, right, top, bot;
	double x, y;
	
	for (int i=1 ; i<n ; i++)
	{
		y = Y_MIN + deltaY * i;
		for (int j=1 ; j<n ; j++)
		{
			//increment/decrement x & y values
			x = X_MIN + deltaX * j;
			left = x - deltaX;
			right = x + deltaX;
			top = y + deltaY;
			bot = y - deltaY;
	  
			//get edge function values
			if (left == X_MIN)
				bVector[bIndex] += DT(poissonEdge(left, y));
			if (right == X_MAX)
				bVector[bIndex] += DT(poissonEdge(right, y));
			if (bot == Y_MIN)
				bVector[bIndex] += DT(poissonEdge(x, bot));
			if (top == Y_MAX)
				bVector[bIndex] += DT(poissonEdge(x, top));
			bIndex++;
		}
	}
	
	bVector *= 0.25;
	return bVector;
}

inline double poissonEdge(double x, double y)
{
	if (x == X_MIN) return sin(y);
	if (x == X_MAX)	return 0;
	if (y == Y_MIN)	return sin(x);
	if (y == Y_MAX)	return 0;
	throw RangeError("x,y is not on poisson edge");   //otherwise, throw error
	return 0;
}

template <class MT, class DT>
FullMatrix<DT> getErrorMatrix(const MatrixBase<MT, DT>& approxMatrix)
{
	FullMatrix<DT> errorMatrix(approxMatrix);   //set equal to approx
	const int rows = errorMatrix.rows();
	const int cols = errorMatrix.cols();
	const int n = rows+1;
	
	const double deltaX = (X_MAX - X_MIN) / n;
	const double deltaY = (Y_MAX - Y_MIN) / n;
	
	double x, y;
	for (int r=0 ; r<rows ; r++)    //loops through x & y values
	{
		y = Y_MIN + deltaY + r*deltaY;
		for (int c=0 ; c<cols ; c++)
		{
			x = X_MIN + deltaX + c*deltaX;
			errorMatrix(r,c) -= poissonAnalytical(x,y); //subtract analytical value
		}
	}
	return errorMatrix;
}


void analyzeApproximation(const Vector<double>& approxVec)
{
	const int numApproximations = approxVec.size();
	const int size = sqrt(numApproximations);
	const int n = size + 1;
	char input;
	FullMatrix<double> approxMatrix(size, size);
	
	for (int r=0 ; r<size ; r++)
		for (int c=0 ; c<size ; c++)
			approxMatrix(r,c) = approxVec[r*size + c];
			
	cout<< "Error Checking: ";
	long errorStart = getNow();
	FullMatrix<double> errorMatrix = getErrorMatrix(approxMatrix);
	long errorEnd = getNow();
	cout<< (errorEnd-errorStart) <<" milliseconds"<<endl;
	
	cout<<"See Error Summary? (y/n) : ";    //prompts user
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		double ele = errorMatrix(0,0);      //error summary
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
		errorAvg /= numApproximations;
		
		cout<<"\tError min: "<<errorMin<<endl;
		cout<<"\tError max: "<<errorMax<<endl;
		cout<<"\tError avg: "<<errorAvg<<endl;
		
		cout<<"See Error raw data? (y/n): ";    //error raw data
		cin >> input;
		// input= 'y'; cout<<endl;
		if (input == 'y' || input == 'Y')
			cout<<errorMatrix<<endl;
		
		cout<<"See Approximations raw data? (y/n) : ";    //approximations
		cin >> input;
		// input= 'y';  cout<<endl;
		if (input == 'y' || input == 'Y')
			cout << approxMatrix <<endl;
			
		cout<<"See Analytical values? (y/n): ";     //analytical solutions
		cin >> input; 
		// input= 'y';  cout<<endl;
		if (input == 'y' || input == 'Y')
		{
			const int rows = errorMatrix.rows();
			const int cols = errorMatrix.cols();
			FullMatrix<double> anaMatrix(rows, cols);
			const double deltaX = (X_MAX - X_MIN) / n;
			const double deltaY = (Y_MAX - Y_MIN) / n;
			double x, y;
			for (int r=0 ; r<rows ; r++)
			{
				y = Y_MIN + deltaY + r*deltaY;
				for (int c=0 ; c<cols ; c++)
				{
					x = X_MIN + deltaX + c*deltaX;
					anaMatrix(r,c) = poissonAnalytical(x,y);
				}
			}
			cout<<anaMatrix<<endl;
		}
	}
	
}
