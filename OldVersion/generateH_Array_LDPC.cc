#include <iostream>
#include <vector>
using namespace std;

std::vector<std::vector<int>> Identity(int num)
{
	int row, col;

	std::vector<std::vector<int>> matrix(num);
	for (int i = 0; i < num; i++)
		matrix[i].resize(num);

	for (row = 0; row < num; row++)
	{
		for (col = 0; col < num; col++)
		{
			// Checking if row is equal to column
			if (row == col)
				matrix[row][col] = 1;
				//matrix[row*num + col] = 1;
			else
				matrix[row][col] = 0;
				//matrix[row*num + col] = 0;
		}
	}

	return matrix;
}

/*template<class ty>
ty circshift(ty out, const ty in, int xdim, int ydim, int xshift, int yshift)
{
	for (int i = 0; i < xdim; i++)
	{
		int ii = (i + xshift) % xdim;
		for (int j = 0; j < ydim; j++)
		{
			int jj = (j + yshift) % ydim;
			out[ii][jj] = in[i][j];
		}
	}
	return out;
}*/

std::vector<std::vector<int>> circshiftV2(std::vector<std::vector<int>> in, int yshift)
{
	std::vector<std::vector<int>> out(in.size(),std::vector<int>(in[0].size()));
	for (size_t i = 0; i < in.size(); i++)
	{
		for (size_t j = 0; j < in[0].size(); j++)
		{
			int jj = (j + yshift) % in[0].size();
			out[i][jj] = in[i][j];
		}
	}
	return out;
}

// Function to form upper triangular matrix
//void upper(int **matrix, int row, int col)
std::vector<std::vector<int>> upper(std::vector<std::vector<int>> matrix, int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (i > j)
				matrix[i][j] = 0;
				//matrix[i*row +j] = 0;
		}
	}
	return matrix;
}

// void display(std::vector<std::vector<int>> a)
// {
// 	for (size_t i = 0; i < a.size(); ++i)
// 	{
// 		for (size_t j = 0; j < a[0].size(); ++j)
// 			cout << a[i][j] << " ";
// 		cout << endl;
// 	}
// 	cout << endl;
// }

std::vector<std::vector<int>> mergeMatrix(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B)
{
	std::vector<std::vector<int>> C = A;
	for (size_t k = 0; k < B.size(); k++)
	{
		for (size_t l = 0; l < B[0].size(); l++)
			C[k].push_back(B[k][l]);
	}

	return C;
}

// input matrix IN and output matrix OUT, "n" should be called power
std::vector<std::vector<int>> pow(std::vector<std::vector<int>> IN, std::vector<std::vector<int>> OUT, int n)
{
	for (size_t i = 0; i < OUT.size(); ++i)
		for (size_t j = 0; j < OUT[0].size(); ++j)
			OUT[i][j] = (i == j);

	std::vector<std::vector<int>> temp(IN.size());
	for (size_t i = 0; i < IN.size(); i++)
		temp[i].resize(IN[0].size());

	for (int w = 0; w<n; w++)
	{
		for (size_t i = 0; i<IN.size(); i++)
		{
			for (size_t j = 0; j<IN[0].size(); j++)
			{
				temp[i][j] = 0;
				for (size_t k = 0; k<IN[0].size(); k++)
				{
					temp[i][j] += OUT[i][k] * IN[k][j];
				}
			}
		}

		for (size_t i = 0; i<IN.size(); i++) {
			for (size_t j = 0; j<IN[0].size(); j++)
			{
				OUT[i][j] = temp[i][j];
			}
		}
	}
	return OUT;
}

//int ** generateH_Array_LDPC(int p, int j, int k)
std::vector<std::vector<int>> generateH_Array_LDPC(int p, int j, int k)
{
	std::vector<std::vector<int>> H(j*p);
	for (int i = 0; i < j*p; i++)
		H[i].resize(k*p);

	std::vector<std::vector<int>> I = Identity(p);

	std::vector<std::vector<int>> a = I;
	//a = circshift(a, I, p, p, 0, 1);
	a = circshiftV2(I, 1);

	//std::vector<std::vector<int>> tempa(a.size());
	//for (size_t i = 0; i < a.size(); i++)
	//	tempa[i].resize(a[0].size());
    int startIndex, startIndex2;
    int ROW_COUNT = j*p;
	[[maybe_unused]]  int COLUMN_COUNT = k*p;

	std::vector<std::vector<int> > H_A(ROW_COUNT, std::vector<int>(COLUMN_COUNT));

	for (int n = 1; n <= j; n++)
	{
		startIndex = (n - 1)*p;
		for (int m = 1; m <= k; m++)
		{
			startIndex2 = (m - 1)*p;
			std::vector<std::vector<int>> tempa(a.size(), std::vector<int>(a[0].size(), 0));

			tempa = pow(a, tempa, (n - 1)*(m - 1));

			for (int nn = 0; nn < p; nn++)
			{
				for (int m = 0; m < p; m++)
					H_A[startIndex + nn][startIndex2 + m] = tempa[nn][m];
			}
		}
	}

/*	std::vector<std::vector<int>> H_S(j*p);
	for (int i = 0; i < j*p; i++)
		H_S[i].resize(k*p);*/

	std::vector<std::vector<int> > H_S(ROW_COUNT, std::vector<int>(COLUMN_COUNT));
	//std::vector<std::vector<int> > H_S(ROW_COUNT);

	
	for (int n = 1; n <= j; n++)
	{
		startIndex = (n - 1)*p;
		//std::vector<std::vector<int>> tempM(p);
		std::vector<std::vector<int>> tempM(p,std::vector<int>(COLUMN_COUNT));
		for (int nn = 0; nn < p; nn++)
		{
			for (int m = 0; m < k*p; m++)
				tempM[nn][m] = H_A[startIndex + nn][m];
				//tempM[nn].push_back(H_A[startIndex + nn][m]);
		}

		//std::vector<std::vector<int>> a = tempM;
		//a = circshift(a, tempM, p, p, 0, (n - 1)*p);

		std::vector<std::vector<int>> a = circshiftV2(tempM, (n - 1)*p);		
		tempM = a;

		for (int nn = 0; nn < p; nn++)
		{
			for (int m = 0; m < k*p; m++)
				H_S[startIndex + nn][m] = tempM[nn][m];
				//H_S[startIndex + n].push_back(tempM[n][m]);
		}

		//delete[] tempM;
		tempM.clear();
	}

	std::vector<std::vector<int>> firstSubMatrix(j*p);
	for (int nn = 0; nn < j*p; nn++)
	{
		for (int m = 0; m < j*p; m++)
			firstSubMatrix[nn].push_back(H_S[nn][m]);
	}

	//upper(firstSubMatrix, sizeof(H_S), sizeof(H_S[0]));
	firstSubMatrix = upper(firstSubMatrix, H_S.size(), H_S[0].size());

	std::vector<std::vector<int>> secondSubMatrix(j*p);
	for (int nn = 0; nn < j*p; nn++)
	{
		for (int m = j*p; m < k*p; m++)
			secondSubMatrix[nn].push_back(H_S[nn][m]);
	}

	H = mergeMatrix(firstSubMatrix, secondSubMatrix);


	//delete[] I;
	//delete[] H_A;
	//delete[] H_S;
	//delete[] firstSubMatrix;
	//delete[] secondSubMatrix;

	I.clear();
	H_A.clear();
	H_S.clear();
	firstSubMatrix.clear();
	secondSubMatrix.clear();

	// cout << "H:" << endl;
	// display(H);
	
	return H;

}