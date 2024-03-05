//Бусыгина Татьяна, ИВТ-22

//Вычислить несколько значений функции Аккермана для неотрицательных чисел m и n:

//            m+1,               n = 0
//A(n, m) = { A(n-1, 1),         n <> 0, m = 0     
//            A(n-1 ,A(n,m-1)),  n > 0,  m >= 0


#include <cassert>
#include <iostream>

using namespace std;


template <typename I>
///Рекурсивная функция для вычисления значений функции Аккермана, m и n - неотрицательные значения, на которых производим вычисления
I ackerman(I n, I m) {
    if (n == 0)
        return m + 1;
    else if (m == 0)
        return ackerman(n - 1, 1);
    else
        return ackerman(n - 1, ackerman(n, m - 1));
}

///Assert для функции Аккермана
void assert_ackerman()
{
	assert(ackerman(3, 4) == 125);
	assert(ackerman(4, 0) == 13);
	assert(ackerman(0, 7) == 8);
}

///Измеряем глубину стека
int stack_depth(int& x)
{
	cout << x << endl;
	x += 1;
	stack_depth(x);
	return 0;

}