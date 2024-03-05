//Бусыгина Татьяна, ИВТ-22

//Вычислить несколько значений функции Аккермана для неотрицательных чисел m и n:

//            m+1,               n = 0
//A(n, m) = { A(n-1, 1),         n <> 0, m = 0     
//            A(n-1 ,A(n,m-1)),  n > 0,  m >= 0

#include <iostream>
#include <cassert>
#include "recursion.h"

using namespace std;

int main(int argc, char* argv[]){

	int n, m;

	assert_ackerman();
	if (argc > 1) 					//если в командной строке есть какие-то аргументы
	{
		n = stoul(argv[1]); 		//считываем значения								
		m = stoul(argv[2]);	
	}
	else
	{
		cout << "Enter n: " << endl;
		cin >> n;
		cout << "Enter m: " << endl;
		cin >> m;
	}

	cout << "Result: " << ackerman(n, m);

	int x = 0;
	stack_depth(x);
}