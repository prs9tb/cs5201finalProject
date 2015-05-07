
#include "Tests.h"

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
	
	SymmMatrix<int> empty3(symm.rows());
	cout<<"Calc Tests: - itself test..."<<endl;
	assert (empty3 == (symm - symm));
	
	cout<<"Calc Tests: + itself test ..."<<endl;
	assert ( (2*symm) == (symm+symm));
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
