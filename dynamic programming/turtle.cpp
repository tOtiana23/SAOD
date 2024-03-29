//Бусыгина Татьяна, ИВТ-22

//Вариант 2. Задача Черепашка
//На квадратной доске расставлены целые неотрицательные числа. Черепашка, находящаяся в левом верхнем углу, 
//мечтает попасть в правый нижний. При этом она может переползать только в клетку справа или снизу и хочет, 
//чтобы сумма всех чисел, оказавшихся у нее на пути, была бы максимальной. Определить эту сумму. 
//Формат входных данных Первая строка — N — размер доски. Далее следует N строк, каждая из которых содержит 
//N целых чисел, представляющие доску. Формат выходных данных Одно число — максимальная сумма.

#include <iostream>
#include <string>
#include "turtle.h"

using namespace std;


int main(int argc, char* argv[])
{
	size_t size;
	size_t board[4][4];

	if (argc > 1){										//если в командной строке есть какие-то аргументы
		size = stoul(argv[1]);}							//то считываем оттуда размер матрицы

	else{
		cout << "Enter board size: "; 					//иначе запрашиваем его у пользователя
		cin >> size;}

	hand_fill_matrix(board, size); 						//заполнение матрицы
	print_matrix(board, size);    						//вывод матрицы
	count(board, size); 								//считаем максимальную сумму
	cout << "Max sum: " << board[size - 1][size - 1]; 	//выводим ответ
}