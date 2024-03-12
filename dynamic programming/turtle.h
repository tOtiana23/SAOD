//Бусыгина Татьяна, ИВТ-22

//Вариант 2. Задача Черепашка
//На квадратной доске расставлены целые неотрицательные числа. Черепашка, находящаяся в левом верхнем углу, 
//мечтает попасть в правый нижний. При этом она может переползать только в клетку справа или снизу и хочет, 
//чтобы сумма всех чисел, оказавшихся у нее на пути, была бы максимальной. Определить эту сумму. 
//Формат входных данных Первая строка — N — размер доски. Далее следует N строк, каждая из которых содержит 
//N целых чисел, представляющие доску. Формат выходных данных Одно число — максимальная сумма.

#include <iostream>
#include <iomanip>


using namespace std;

///Ручное заполнение матрицы matrix размера size
template <typename A>
void hand_fill_matrix(A& matrix, size_t size)
{
	for (size_t i = 0; i < size; i++){
		for (size_t j = 0; j < size; j++){
			cout << "Enter value of cell [" << i << "][" << j << "] : ";
			cin >> matrix[i][j];
		}
	}
}

///Вывод матрицы matrix размера size в консоль
template <typename A>
void print_matrix(const A& matrix, size_t size)
{
	for (size_t i = 0; i < size; i++){
		for (size_t j = 0; j < size; j++){
			cout << left << setw(5) << matrix[i][j];
		}
		cout << endl;
	}
}

//Исполняем мечту черепашки
///Ищем наибольшую сумму элементов от [0][0] до [size][size] матрицы matrix размера size
template <typename A>
A count(A matrix, size_t size)
{
	//изменяем элементы первой строки (кроме первого) на сумму текущего элемента и предыдущего
	for (size_t i = 1; i < size; i++) {
        matrix[i][0] += matrix[i - 1][0];}

	//изменяем элементы первого столбца(кроме первого) на сумму текущего элемента и предыдущего
    for (size_t j = 1; j < size; j++) {  
        matrix[0][j] += matrix[0][j - 1];}

    //идём к мечте, выбираем наибольший элемент и суммируем, в последней ячейке будет максимальная сумма
	for (size_t i = 1; i < size; i++) { 
        for (size_t j = 1; j < size; j++) {  
            matrix[i][j] += max(matrix[i - 1][j], matrix[i][j - 1]);
        }
    }
    return matrix;

}