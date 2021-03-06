
#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;

int main()
{
	double x[10][10], y[10][10], z[10][10], b[10][10], mult[10][10];
	int r1, c1, r2, c2, i, j, k;
	r1 = 3;
	r2 = 3;
	c1 = 3;
	c2 = 1;


	const double PI = 3.14159265;

	// If column of first matrix in not equal to row of second matrix,
	// ask the user to enter the size of matrix again.
	while (c1 != r2)
	{
		cout << "Error! column of first matrix not equal to row of second.";

		cout << "Enter rows and columns for first matrix: ";
		cin >> r1 >> c1;


	}

	// Storing elements of first matrix.

	cout << endl << "Enter the coordinates x,y and z" << endl;
	for (i = 0; i < r2; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << "Enter element " << i + 1 << j + 1 << " : ";
			cin >> b[i][j];
		}

	// Storing elements of second matrix.
	cout << "Enter the degree of rotation" << endl;
	double degrees, radians;
	cin >> degrees;
	radians = degrees * PI / 180.0;
#pragma omp parallel for
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c1; ++j)
		{	
			
			x[i][j] = 0;
			y[i][j] = 0;
			z[i][j] = 0;
		}


omp_set_dynamic(9);
	// Initializing elements of matrix mult to 0.
#pragma omp master
#pragma omp parallel for
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			
			mult[i][j] = 0;
		}
#pragma omp flush(mult)
	x[0][0] = 1;
	x[1][1] = cos(radians);
	x[1][2] = -sin(radians);
	x[2][1] = sin(radians);
	x[2][2] = cos(radians);
	y[0][0] = cos(radians);
	y[0][2] = sin(radians);
	y[1][1] = 1;
	y[2][0] = -sin(radians);
	y[2][2] = cos(radians);
	z[0][0] = cos(radians);
	z[0][1] = -sin(radians);
	z[1][0] = sin(radians);
	z[1][1] = cos(radians);
	z[2][2] = 1;



	// Multiplying matrix a and b and storing in array mult.



	/*for(i=0;i<3;++i)
	{
		cout<<endl;
		for(j=0;j<3;++j)
			cout<<x[i][j]<<"    ";
	}
	*/
#pragma omp critical
#pragma omp parallel for
	for (i = 0; i < r1; ++i)

	{
		for (j = 0; j < c2; ++j)
		{
			
			for (k = 0; k < c1; ++k)
			{
				
				mult[i][j] += x[i][k] * b[k][j];
			}
		}
		cout << "Executing thread : " << omp_get_thread_num() << endl;
	}
	// Displaying the multiplication of two matrix.
	#pragma omp flush(mult)

	cout << endl << "Rotation about x axis by " << degrees << " degrees" << endl;
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << " " << mult[i][j];
			if (j == c2 - 1)
				cout << endl;
		}

#pragma omp master
#pragma omp parallel for
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			mult[i][j] = 0;
		}
#pragma omp flush(mult)

#pragma omp critical
#pragma omp parallel for
	for (i = 0; i < r1; ++i)

	{
		for (j = 0; j < c2; ++j)
		{
			for (k = 0; k < c1; ++k)
			{
				
				mult[i][j] += y[i][k] * b[k][j];
			}
		}
		cout << "Executing thread : " << omp_get_thread_num() << endl;
	}
	// Displaying the multiplication of two matrix.
	#pragma omp flush(mult)

	cout << endl << "Rotation about y axis by " << degrees << " degrees" << endl;
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << " " << mult[i][j];
			if (j == c2 - 1)
				cout << endl;
		}

#pragma omp master
#pragma omp parallel for
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			
			mult[i][j] = 0;
		}
#pragma omp flush(mult)

#pragma omp critical
#pragma omp parallel for
	for (i = 0; i < r1; ++i)

	{
		for (j = 0; j < c2; ++j)
		{
			for (k = 0; k < c1; ++k)
			{
				
				
				mult[i][j] += z[i][k] * b[k][j];
			}
		}
		cout << "Executing thread : " << omp_get_thread_num() << endl;
		if (i == (r1 - 1))
		{
			cout << "Parallel region: " << omp_in_parallel() << endl;
			cout << "Number of threads: " << omp_get_num_threads() << endl;
			cout << "Setting of omp_set_dynamic: " << omp_get_dynamic() << endl;
			

		}
	}
	#pragma omp flush(mult)
	
	// Displaying the multiplication of two matrix.


	cout << endl << "Rotation about z axis by " << degrees << " degrees" << endl;
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << " " << mult[i][j];
			if (j == c2 - 1)
				cout << endl;
		}


	return 0;

}
