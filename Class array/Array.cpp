//Бусыгина Татьяна, ИВТ-22

#define _USE_MATH_DEFINES
#include "Array.h"
#include <cassert>
#include <iostream>

using namespace std;

// ///Тест работы функции сортировки слиянием
// void merge_assert()
// {
// 	//целые числа
// 	int* int_arr = new int[7]{ 64, 34, 25, 12, 22, 11, 90 };
// 	int* int_arr_sort = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };
// 	int* int_arr0 = new int[7]{ 90, 64, 34, 25, 22, 12, 11 };
// 	int* int_arr2 = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };

// 	merge_sort(int_arr, 0, 6);
// 	merge_sort(int_arr0, 0, 6);
// 	merge_sort(int_arr2, 0, 6);
// 	for (size_t i = 0; i < 7; i++)
// 	{
// 		assert(int_arr[i] == int_arr_sort[i]);
// 		assert(int_arr0[i] == int_arr_sort[i]);
// 		assert(int_arr2[i] == int_arr_sort[i]);
// 	}
// 	delete[] int_arr;
// 	delete[] int_arr_sort;
// 	delete[] int_arr0;
// 	delete[] int_arr2;


// 	//целые числа, повторяющиеся элементы
// 	int* int_arr1 = new int[7]{ 64, 34, 22, 22, 22, 11, 90 };
// 	int* int_arr_sort1 = new int[7]{ 11, 22, 22, 22, 34, 64, 90 };

// 	merge_sort(int_arr1, 0, 6);
// 	for (size_t i = 0; i < 7; i++)
// 	{
// 		assert(int_arr1[i] == int_arr_sort1[i]);
// 	}
// 	delete[] int_arr1;
// 	delete[] int_arr_sort1;

// 	//дробные числа
// 	double* double_arr = new double[3]{ 1.03, 1.01, 1.02 };
// 	double* double_arr_sort = new double[3]{ 1.01, 1.02, 1.03 };
// 	merge_sort(double_arr, 0, 2);
// 	for (size_t i = 0; i < 3; i++)
// 	{
// 		assert(double_arr[i] == double_arr_sort[i]);
// 	}
// 	delete[] double_arr;
// 	delete[] double_arr_sort;
// }

// ///Тест последовательного поиска
// void search_assert()
// {

// 	int* arr0 = new int[5] { 1, 2, 3, 4, 5 };
// 	assert(binary_search(arr0, 5, 3) == 2);		//успешный поиск элемента в массиве
// 	delete[] arr0;

// 	int* arr1 = new int[5] { 1, 2, 3, 4, 5 };
// 	assert(binary_search(arr1, 5, 6) == 0);		//неудачный поиск элемента в массиве
// 	delete[] arr1;

// 	int* arr2 = new int[0] {};
// 	assert(binary_search(arr2, 0, 5) == 0);		//пустой массив
// 	delete[] arr2;

// 	int* arr3 = new int[1] { 10 };
// 	assert(binary_search(arr3, 1, 10) == 0);	//массив с одним элементом(искомый элемент) :

// 	assert(binary_search(arr3, 1, 5) == 0);		//массив с одним элементом(неискомый элемент) :
// 	delete[] arr3;
// }

// ///Тест оператора []
// void test_operator_brackets()
// {
//     Array<int> arr(5);
//     arr.add_last(10);
//     assert(arr[0] == 10);
// }

// ///Тест изменения размера массива
// void test_resize()
// {
//     Array<int> arr(5);
//     arr.resize(3);
//     assert(arr.length() == 3);
// }

// ///Тест добавления элемента в конец массива
// void test_add_last()
// {
//     Array<int> arr(2);
//     arr.add_last(10);
//     arr.add_last(20);
//     arr.add_last(30); // должно увеличиться размер массива
//     assert(arr.length() == 3);
// }

// ///Тест удаления последнего элемента
// void test_del_last()
// {
//     Array<int> arr(3);
//     arr.add_last(10);
//     arr.add_last(20);
//     arr.del_last();
//     assert(arr.length() == 1);
// }