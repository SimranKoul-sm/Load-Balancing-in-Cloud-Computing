#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int a[10][10], b[10][10], mult[10][10], r1, c1, r2, c2, i, j, k;

	cout << "Enter rows and columns for graphic matrix: ";
	cin >> r2 >> c2;
	r1 = r2;
	c1 = c2;


	// If column of first matrix in not equal to row of second matrix,
	// ask the user to enter the size of matrix again.
	while (c1 != r2)
	{
		cout << "Error! column of first matrix not equal to row of second.";

		cout << "Enter rows and columns for first matrix: ";
		cin >> r1 >> c1;


	}

	// Storing elements of first matrix.

	cout << endl << "Enter elements of the graphic:" << endl;
	for (i = 0; i < r2; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << "Enter element of graphics" << i + 1 << j + 1 << " : ";
			cin >> b[i][j];
		}

	// Storing elements of second matrix.
	cout << endl << "Enter scaling factors" << endl;
	int scale[10];
	for (i = 0; i < r1; ++i)
		cin >> scale[i];

# pragma omp for
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c1; ++j)
		{
			a[i][j] = scale[i];
		}

	// Initializing elements of matrix mult to 0.
#pragma omp master
# pragma omp parallel for
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			mult[i][j] = 0;
		}

	for (i = 0; i < r1; ++i)
	{
		for (j = 0; j < c1; ++j)
		{
			cout << a[i][j];
		}
		cout << endl;
	}



	// Multiplying matrix a and b and storing in array mult.

	omp_set_dynamic(9);
#pragma omp critical
#pragma omp parallel 
	{
		#pragma omp for nowait
		for (i = 0; i < r1; ++i)

		{


			for (j = 0; j < c2; ++j)
			{

				mult[i][j] = a[i][j] + b[i][j];
			}
			cout << "Executing thread : " << omp_get_thread_num() << endl;
			if (i == (r1 - 1))
			{
				//cout << "Parallel region: " << omp_in_parallel() << endl;
				cout << "Number of threads: " << omp_get_num_threads() << endl;
				//cout << "Setting of omp_set_dynamic: " << omp_get_dynamic() << endl;
				cout << " Number of seconds between processor clock ticks: " << omp_get_wtick();

			}
		}
		// Displaying the multiplication of two matrix.
	}

	cout << endl << "Output Matrix: " << endl;
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << " " << mult[i][j];
			if (j == c2 - 1)
				cout << endl;
		}

	return 0;

}