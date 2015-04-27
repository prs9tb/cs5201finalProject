
#include <iostream>
#include <assert.h>
#include <stdexcept>
#include "Tests.h"

/*
#include <iostream>
using std::cout;
using std::endl;
void report() const
{
	cout<<"Dims: "<<m_rows<<" x "<<m_cols<<"   m_data = "<<endl;
	for (int r=0 ; r<m_rows ; r++)
		cout<<m_data[r]<<endl;
}
*/

using namespace std;

template<class MT, class DT>
void testCalcOps(const MatrixBase<MT,DT>& matrix)
{
	const int rows = matrix.rows();
	const int cols = matrix.cols();
	
	MT empty(rows, cols);
	cout<<"Calc Tests: - itself test..."<<endl;
	assert (empty == (matrix-matrix));
	
	cout<<"Calc Tests: + itself test ..."<<endl;
	DT twice(2);
	assert ( (matrix*twice) == (matrix+matrix));
	
	if (rows == cols)
	{
		cout<<"Calc Tests: * op test ..."<<endl;
		cout<<matrix<<endl<<" * itself becomes: "<<endl;
		cout<< (matrix*matrix) <<endl;
	}
}

void testTriDiagMatrixClass()
{
	cout<<"****** TriDiagonal Matrix tests: *******"<<endl;
	cout<<"Default constructor Test ..."<<endl;
	TriDiagMatrix<int> empty;
	assert (empty.rows() == 0 && empty.cols() == 0);
	
	cout<<"Dimensioned constructor Test ..."<<endl;
	TriDiagMatrix<int> square(4);
	assert (square.rows() == 4 && square.cols() == 4);
	
	cout<<"Sized constructor Test ..."<<endl;
	TriDiagMatrix<int> rect(5, 4);
	assert (rect.rows() == 5 && rect.cols() == 4);
	
	cout<<"== ops Test ..."<<endl;
	assert (rect == rect);
	assert (rect != square);
	TriDiagMatrix<int> empty2;
	assert (empty == empty2);
	
	cout<<"operator[] Test: eles increase..."<<endl;
	int rows = rect.rows();
	int cols = rect.cols();
	for (int r=0 ; r<rows ; r++)
		for (int c=0 ; c<cols ; c++)
		{
			const int diff = (r>c)? r-c:c-r;
			if (diff <= 1)
				rect(r,c) = r*c;
		}
	
	cout<<"Output Stream operator test..."<<endl;
	cout<<rect<<endl;
	
	cout<<"Copy constructor Test ..."<<endl;
	TriDiagMatrix<int> myCopy(rect);
	assert (myCopy == rect);
	
	cout<<"= operator Test ... "<<endl;
	rect = myCopy;
	assert (rect == myCopy);
	
	cout<<"row_multi with 1 test: "<<endl;
	rect.row_multi(1, 1);
	assert (rect == myCopy);
	
	cout<<"row_multi_add with 0 test..."<<endl;
	rect.row_multi_add(1, 0, 2);
	assert(rect == myCopy);
	
	testCalcOps(rect);
}

void testDiagMatrixClass()
{
	cout<<"****** Diagonal Matrix tests: *******"<<endl;
	cout<<"Default constructor Test ..."<<endl;
	DiagMatrix<int> empty;
	assert (empty.rows() == 0 && empty.cols() == 0);
	
	cout<<"Dimensioned constructor Test ..."<<endl;
	DiagMatrix<int> square(4);
	assert (square.rows() == 4 && square.cols() == 4);
	
	cout<<"Sized constructor Test ..."<<endl;
	DiagMatrix<int> rect(5, 4);
	assert (rect.rows() == 5 && rect.cols() == 4);
	
	cout<<"== ops Test ..."<<endl;
	assert (rect == rect);
	assert (rect != square);
	DiagMatrix<int> empty2;
	assert (empty == empty2);
	
	cout<<"operator[] Test: eles increase..."<<endl;
	int rows = rect.rows();
	int cols = rect.cols();
	const int diagLen = (rows>cols)? cols:rows;
	for (int i=0 ; i<diagLen ; i++)
	{
		if (i == 0)
			rect(i,i) = 1;
		else if (i == 1)
			rect(i,i) = 2;
		else
			rect(i,i) = rect(i-1,i-1) + rect(i-2,i-2);
		square(i,i) = rect(i,i)*rect(i,i);
	}
	
	cout<<"Output Stream operator test..."<<endl;
	cout<<rect<<endl;
	
	cout<<"Copy constructor Test ..."<<endl;
	DiagMatrix<int> myCopy(rect);
	assert (myCopy == rect);
	
	cout<<"= op Test: "<<endl;
	rect = myCopy;
	assert (rect == myCopy);
	
	cout<<"row_multi with 1 test: "<<endl;
	rect.row_multi(1, 1);
	assert (rect == myCopy);
	
	cout<<"row_multi_add with 0 test..."<<endl;
	rect.row_multi_add(1, 0, 2);
	assert(rect == myCopy);
	
	testCalcOps(rect);
	
	cout<<"* op test:  this: "<<endl;
	cout<< square <<"  times itself is: "<<endl;
	cout<< (square * square) <<endl;
}



void testSymmMatrixClass()
{
	cout<<"****** Symmetrical Matrix tests: *******"<<endl;
	cout<<"Default constructor Test ..."<<endl;
	SymmMatrix<int> empty;
	assert (empty.rows() == 0 && empty.cols() == 0);
	
	cout<<"Dimensioned constructor Test ..."<<endl;
	SymmMatrix<int> symm(3);
	assert (symm.rows() == 3 && symm.cols() == 3);
	
	cout<<"Sized constructor Test ..."<<endl;
	try{
		SymmMatrix<int> rect(5, 4);
		assert (rect.rows() && false);
	}
	catch (logic_error& e) {}
	
	cout<<"== ops Test ..."<<endl;
	SymmMatrix<int> empty2;
	assert (empty == empty2);
	assert (symm == symm);
	assert (symm != empty);
	
	cout<<"operator[] Test: eles increase..."<<endl;
	int rows = symm.rows();
	int cols = symm.cols();
	int count = 0;
	for (int r=0 ; r<rows ; r++)
	{
		const int colMax = (r<cols)? r+1 : cols;
		for (int c=0 ; c<colMax; c++)
		{
			count++;
			if (c == 0)
				symm(r,c) = count;
			else
				symm(r,c) = symm(r,c-1) + 1;
		}
	}
	cout<<"Output Stream operator test..."<<endl;
	cout<<symm<<endl;
	
	cout<<"Copy constructor Test ..."<<endl;
	SymmMatrix<int> myCopy(symm);
	assert (myCopy == symm);
	
	cout<<"= op Test: "<<endl;
	symm = myCopy;
	assert (symm == myCopy);
	
	cout<<"row_multi with 1 test: "<<endl;
	symm.row_multi(1, 1);
	assert (symm == myCopy);
	
	cout<<"row_multi_add with 0 test..."<<endl;
	symm.row_multi_add(1, 0, 2);
	assert(symm == myCopy);
	
	SymmMatrix<int> empty3(symm.rows());
	cout<<"Calc Tests: - itself test..."<<endl;
	assert (empty3 == (symm - symm));
	
	cout<<"Calc Tests: + itself test ..."<<endl;
	assert ( (2*symm) == (symm+symm));
}

void testLowMatrixClass()
{
	cout<<"****** Lower Triangular Matrix tests: *******"<<endl;
	cout<<"Default constructor Test ..."<<endl;
	LowerTriMatrix<int> empty;
	assert (empty.rows() == 0 && empty.cols() == 0);
	
	cout<<"Dimensioned constructor Test ..."<<endl;
	LowerTriMatrix<int> threeSquare(3);
	assert (threeSquare.rows() == 3 && threeSquare.cols() == 3);
	
	cout<<"Sized constructor Test ..."<<endl;
	LowerTriMatrix<int> rect(5, 4);
	assert (rect.rows() == 5 && rect.cols() == 4);
	
	cout<<"== ops Test ..."<<endl;
	assert (rect == rect);
	assert (rect != threeSquare);
	LowerTriMatrix<int> empty2;
	assert (empty == empty2);
	
	cout<<"operator[] Test: eles increase..."<<endl;
	int rows = rect.rows();
	int cols = rect.cols();
	int count = 0;
	for (int r=0 ; r<rows ; r++)
	{
		const int colMax = (r<cols)? r+1 : cols;
		for (int c=0 ; c<colMax; c++)
		{
			count++;
			if (c == 0)
				rect(r,c) = count;
			else
				rect(r,c) = rect(r,c-1) + 1;
		}
	}
	cout<<"Output Stream operator test..."<<endl;
	cout<<rect<<endl;
	
	cout<<"Copy constructor Test ..."<<endl;
	LowerTriMatrix<int> myCopy(rect);
	assert (myCopy == rect);
	
	cout<<"= op Test: "<<endl;
	rect = myCopy;
	assert (rect == myCopy);
	
	cout<<"row_multi with 1 test: "<<endl;
	rect.row_multi(1, 1);
	assert (rect == myCopy);
	
	cout<<"row_multi_add with 0 test..."<<endl;
	rect.row_multi_add(1, 0, 2);
	assert(rect == myCopy);
	
	cout<<"row_multi_add(2,3,3) = "<<endl;
	rect.row_multi_add(2,2,3);
	cout<<rect<<endl;
	
	testCalcOps(rect);
	
	cout<<"* op test:  "<<endl;
	for (int r=0 ; r<3 ; r++)
		for (int c=0 ; c<=r ; c++)
			threeSquare(r,c) = r + r* (c+1);
	cout<< threeSquare <<endl;
	cout<< (threeSquare * threeSquare) <<endl;
}

void testUpperMatrixClass()
{
	cout<<"****** Upper Triangular Matrix tests: *******"<<endl;
	cout<<"Default constructor Test ..."<<endl;
	UpperTriMatrix<int> empty;
	assert (empty.rows() == 0 && empty.cols() == 0);
	
	cout<<"Dimensioned constructor Test ..."<<endl;
	UpperTriMatrix<int> threeSquare(3);
	assert (threeSquare.rows() == 3 && threeSquare.cols() == 3);
	
	cout<<"Sized constructor Test ..."<<endl;
	UpperTriMatrix<int> rect(5, 4);
	assert (rect.rows() == 5 && rect.cols() == 4);
	
	cout<<"== ops Test ..."<<endl;
	assert (rect == rect);
	assert (rect != threeSquare);
	UpperTriMatrix<int> empty2;
	assert (empty == empty2);
	
	cout<<"operator[] Test: eles increase..."<<endl;
	int rows = rect.rows();
	int cols = rect.cols();
	int count = 0;
	for (int r=0 ; r<rows ; r++)
	{
		// const int colMax = (r > cols)? 0 : cols-r ;
		for (int c=r ; c<cols; c++)
		{
			count++;
			if (c == r)
				rect(r,c) = count;
			else
				rect(r,c) = rect(r,c-1) + 1;
		}
	}
	cout<<"Output Stream operator test..."<<endl;
	cout<<rect<<endl;
	
	cout<<"Copy constructor Test ..."<<endl;
	UpperTriMatrix<int> myCopy(rect);
	assert (myCopy.rows() == rect.rows());
	assert (myCopy == rect);
	
	cout<<"= op Test: "<<endl;
	rect = myCopy;
	assert (rect == myCopy);
	
	cout<<"row_multi with 1 test: "<<endl;
	rect.row_multi(1, 1);
	assert (rect == myCopy);
	
	cout<<"row_multi_add with 0 test..."<<endl;
	rect.row_multi_add(1, 0, 2);
	assert(rect == myCopy);
	
	cout<<"row_multi_add(3,3,2) = "<<endl;
	rect.row_multi_add(3,2,2);
	cout<<rect<<endl;
	
	testCalcOps(rect);
	
	cout<<"* op test:  "<<endl;
	for (int r=0 ; r<3 ; r++)
		for (int c=r ; c<3 ; c++)
			threeSquare(r,c) = r + (r+1) * (c+1);
	cout<< threeSquare <<endl<<" * itself is "<<endl;
	cout<< (threeSquare * threeSquare) <<endl;
}


void testFullMatrixClass()
{
	cout<<"****** Full Matrix tests: *******"<<endl;
	cout<<"Default constructor Test ..."<<endl;
	FullMatrix<int> empty;
	assert (empty.rows() == 0 && empty.cols() == 0);
	
	cout<<"Dimensioned constructor Test... "<<endl ;
	FullMatrix<int> threeSquare(3);
	assert (threeSquare.rows() == 3 && threeSquare.cols() == 3);
	
	cout<<"Sized constructor Test... "<<endl ;
	FullMatrix<int> rect(4, 3);
	assert (rect.rows() == 4 && rect.cols() == 3);
	
	cout<<"operator() Test: elements increase"<<endl;
	int count = 0;
	for (unsigned int r=0 ; r<rect.rows() ; r++)
		for (unsigned int c=0 ; c<rect.cols() ; c++)
		{
			count++;
			if (c == 0) rect(r,c) = count;
			else rect(r,c) = 1 + rect(r,c-1);
		}
		
	cout<<"Output Stream operator test... "<<endl;
	cout<<rect<<endl;
	
	cout<<"== op test..."<<endl;
	assert (rect == rect);
	assert (rect != empty);
	assert (rect != threeSquare);
	
	cout<<"Copy constructor Test ..."<<endl;
	FullMatrix<int> myCopy(rect);
	assert (rect == myCopy);
	
	cout<<"Resize Test... "<<endl;
	myCopy.resize(4, 4);
	assert (myCopy.rows() == 4 && myCopy.cols() == 4);
	
	cout<<"= op Test... "<<endl;
	rect = myCopy;
	assert (rect == myCopy);
	
	try{
		cout<<"Index Error: ";
		myCopy(999,999) = 7;
	}
	catch(logic_error& e)
	{
		cout<<" Caught!"<<endl;
	}
	
	try{
		cout<<"Size Mismatch Error: ";
		threeSquare *= myCopy;
	}
	catch(logic_error& e)
	{
		cout<<" Caught!"<<endl;
	}
	
	cout<<"row_multi by 1 test..."<<endl;
	myCopy.row_multi(1,1);
	assert(myCopy== rect);
	
	cout<<"row_multi_add with 0 test..."<<endl;
	rect.row_multi_add(1, 0, 2);
	assert(rect == myCopy);
	
	cout<<"row_multi_add(2,3,3) = "<<endl;
	myCopy.row_multi_add(2,2,3);
	cout<<myCopy<<endl;
	
	cout<<"row_multi_add(3,0,1) = "<<endl;
	myCopy.row_multi_add(3,0,1);
	cout<<myCopy<<endl;
	
	testCalcOps(myCopy);
	
	cout<<"FullMatrix tests done!"<<endl;
}

void testVectorClass()
{
	cout<<"Default constructor Test: " ;
	Vector<int> emptyVec;
	cout<<emptyVec<<endl;
	
	cout<<"Sized constructor Test: " ;
	Vector<int> threeInts(3);
	cout<<threeInts<<endl;
	
	cout<<"Sized + init constructor Test: ";
	Vector<int> fourInts(4, 4);
	cout<<fourInts<<endl;
	
	cout<<"Sized + dataArray constructor Test: ";
	int dataArray[] = {1, 5, -2, 4};
	Vector<int> dataVec(4, dataArray);
	cout<<dataVec<<endl;
	
	cout<<"operator[] Test: "<<dataVec<<" eles-1 = ";
	for (unsigned int i=0 ; i<dataVec.size() ; i++)
		dataVec[i] = dataVec[i] - 1;
	cout<<dataVec<<endl;
	
	cout<<"Resize Test +++: "<<dataVec;
	dataVec.resize(6);
	cout<<" size 6 = "<<dataVec<<endl;
	dataVec[5] = 4;
	cout<<"Resize Test ---: "<<dataVec;
	dataVec.resize(4);
	cout<<" size 4 = "<<dataVec<<endl;
	
	Vector<int> dumVec(3, 6);
	cout<<"= Test: "<<dumVec;
	cout<<" changes to dataVec: "; 
	dumVec = dataVec;
	cout<<dumVec<<endl;
	
	cout<<"Calc Tests: "<<endl;
	cout<<"\t"<<dumVec<<" + itself = "<< (dumVec+dumVec) <<endl;
	cout<<"\t"<<dumVec<<" - itself = "<< (dumVec-dumVec) <<endl;
	cout<<"\t"<<dumVec<<" * itself = "<< (dumVec*dumVec) <<endl;
	cout<<"\t"<<dumVec<<" * "<<fourInts<<" = "<< (dumVec*fourInts) <<endl;
	cout<<"\t"<<dumVec<<" negation = "<< (-dumVec) <<endl;
	
	cout<<"Relations Tests: "<<endl;
	if (dumVec == dumVec)
		cout<<"\t"<<dumVec<<" is == to "<<dumVec<<endl;
	else
		cout<<"\t"<<dumVec<<" is != to "<<dumVec<<endl;
		
	if (dumVec == fourInts)
		cout<<"\t"<<dumVec<<" is == to "<<fourInts<<endl;
	else
		cout<<"\t"<<dumVec<<" is != to "<<fourInts<<endl;
	
	cout<<"Vector tests done!"<<endl<<endl;
}
