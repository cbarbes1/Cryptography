#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main()
{
	vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	/*
	for(int i = 0; i<matrix.size(); i++){
		cout<<"[";
		for(int j = 0; j<matrix.size(); j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<"]"<<endl;
	}*/
	#pragma omp parallel num_thread(3)
	{
		int index = omp_get_thread_num();
		for(int i = 0; i<matrix.size(); i++){
			for(int j = 0; j<matrix.size(); j++){
				
	return 0;
}
