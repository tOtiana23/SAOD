//Бусыгина Татьяна, ИВТ-22

#include <cassert>	
#include <iomanip>
#include <iostream>	

using namespace std;


///Заполнение массива arr размера size рандомными числами в заданном диапазоне high, low
template <typename Arr>
void rand_fill_array(Arr* arr, size_t size, float high, float low)
{
	int diap = high - low;									//диапозон рандома
	for (size_t i = 0; i < size; i++)						//цикл для ввода заполнения
	{
		arr[i] = (float)rand() / RAND_MAX * diap + low;		//сама функция заполнения массива
															//RAND_MAX - константа записанная в бибилиотеке cstdlib
	}
}

///Вывод массива arr размера size на экран
template <typename Arr>
void print_array(Arr* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)					//цикл от 0 до конца массива
		cout << setprecision(3) << arr[i] << " ";		//происходит вывод с округлением в цикле
	cout << endl;
}

///Сортировка пузырьком массива arr размера size по возрастанию
//1.Лучший случай: O(n) 
//2.Среднее: O(n2) 
//3.Худшее: O(n2) 
template<typename Arr>
void bubble_sort(Arr* arr, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1])				//если предыдущий элемент больше следующего
			{
				swap(arr[j], arr[j + 1]);			//меняем местами
			}
	}
}

///Тест работы функции сортировки пузырьком
void bubble_assert()
{
	//целые числа
	int* int_arr = new int[7]{ 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr_sort = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr0 = new int[7]{ 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr2 = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };

	bubble_sort(int_arr, 7);
	bubble_sort(int_arr0, 7);
	bubble_sort(int_arr2, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr0;
	delete[] int_arr2;
	delete[] int_arr_sort;


	//целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7]{ 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7]{ 11, 22, 22, 22, 34, 64, 90 };

	bubble_sort(int_arr1, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	//дробные числа
	double* double_arr = new double[3]{ 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3]{ 1.01, 1.02, 1.03 };
	bubble_sort(double_arr, 3);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}

///Функция для слияния двух подмассивов arr, где left начало массива = 0, right = размеру массива 
///mid - середина массива, по которой мы делим (вычисляется в функции merge_sort)
template <typename Arr>
void merge(Arr* arr, size_t left, size_t mid, size_t right) {
	size_t n1 = mid - left + 1; 					//вычисление размера левого подмассива
	size_t n2 = right - mid; 						//вычисление размера правого подмассива

	Arr* l = new Arr[n1]; 							//динамическое выделение памяти для массива L, R
	Arr* r = new Arr[n2];

	memcpy(l, &arr[left], n1 * sizeof(Arr)); 		//копирование данных во временный массив L
	memcpy(r, &arr[mid + 1], n2 * sizeof(Arr)); 	//копирование данных во временный массив R

	size_t i = 0;									//инициализация индексов для объединения двух подмассивов
	size_t j = 0;
	size_t k = left;

	while (i < n1 && j < n2) { 						//слияние двух подмассивов в основной массив arr
		if (l[i] <= r[j]) {
			arr[k] = l[i];
			i++;
		}
		else {
			arr[k] = r[j];
			j++;
		}
		k++;
	}

	if(i < n1){
    memcpy(&arr[k], &l[i], (n1 - i) * sizeof(Arr)); //добавление оставшихся элементов из левого подмассива
    k += n1 - i;
  }

  if(j < n2){
    memcpy(&arr[k], &r[j], (n2 - j) * sizeof(Arr)); //добавление оставшихся элементов из правого подмассива
    k += n2 - j;
  }

	delete[] l;
	delete[] r;
}

///Функция для рекурсивной сортировки слиянием массива arr, где left начало массива = 0, а right = размеру массива по возрастанию
//1.Лучший случай: O(n log n)
//2.Средний случай:O(n log n)
//3.Худший случай: O(n log n)
template <typename Arr>
void merge_sort(Arr* arr, size_t left, size_t right) {
	if (left < right) { 									//проверка, что левое значение меньше правого

		size_t mid = left + (right - left) / 2; 			//вычисление середины массива

		merge_sort(arr, left, mid); 					//рекурсивный вызов merge_sort для левой части массива
		merge_sort(arr, mid + 1, right); 				//рекурсивный вызов merge_sort для правой части массива

		merge(arr, left, mid, right); 					//вызов функции merge для слияния двух отсортированных подмассивов
	}
}


///Тест работы функции сортировки слиянием
void merge_assert()
{
	//целые числа
	int* int_arr = new int[7]{ 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr_sort = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr0 = new int[7]{ 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr2 = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };

	merge_sort(int_arr, 0, 6);
	merge_sort(int_arr0, 0, 6);
	merge_sort(int_arr2, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;
	delete[] int_arr0;
	delete[] int_arr2;


	//целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7]{ 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7]{ 11, 22, 22, 22, 34, 64, 90 };

	merge_sort(int_arr1, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	//дробные числа
	double* double_arr = new double[3]{ 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3]{ 1.01, 1.02, 1.03 };
	merge_sort(double_arr, 0, 2);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}

///Сортировка методом Шелла массива arr размера size, d - середина, на каждой итерации уменьшаем в 2 раза
//1.Лучший случай O(n log n)
//2.Средний случай O(n^3/2)
//3.Худший случай O(n^2)
template <typename Arr>
void shell_sort(Arr* arr, size_t size)
{
	for (size_t step = size / 2; step > 0; step /= 2) {		//первоначальный шаг - середина, на каждой итерации уменьшаем в 2 раза
		for (size_t i = step; i < size; i++) {					//идём по массиву с середины до конца
			Arr temp = arr[i];
			size_t j;
			for (j = i; j >= step && arr[j - step] > temp; j -= step) { //сравниваем и меняем
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}

	}
}

///Тест работы функции методом Шелла
void shell_assert()
{
	//целые числа
	int* int_arr = new int[7]{ 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr0 = new int[7]{ 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr_sort = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr2 = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };

	shell_sort(int_arr, 7);
	shell_sort(int_arr0, 7);
	shell_sort(int_arr2, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;
	delete[] int_arr0;
	delete[] int_arr2;


	//целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7]{ 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7]{ 11, 22, 22, 22, 34, 64, 90 };

	shell_sort(int_arr1, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	//дробные числа
	double* double_arr = new double[3]{ 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3]{ 1.01, 1.02, 1.03 };
	shell_sort(double_arr, 3);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}

///Меняем местами два элемента a и b
template <typename A>
void swap(A* a, A* b) {
    A temp = *a;
    *a = *b;
    *b = temp;
}


///Разделяем массив arr на две части - больше и меньше опорного элемента
template <typename A>
A partition(A* arr, size_t low, size_t high) {
    A pivot = arr[high];					//опорный элемент - последний элемент массива
    size_t i = low - 1;							//индекс для разделения элементов на две группы: меньше опорного и больше опорного
    for (size_t j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);			//меняем местами текущий элемент с элементом на позиции i
        }
    }
    swap(&arr[i + 1], &arr[high]);			//помещаем опорный элемент между двумя группами
    return i + 1; 							//возвращаем индекс опорного элемента
}

///Быстрая сортировка массива arr
//1.Лучший случай: O(n log n)
//2.Средний случай: O(n log n)
//3.Худший случай: O(n^2)
template <typename A>
void quick_sort(A* arr, size_t low, size_t high) {
    if (low < high) {
        A pivot = partition(arr, low, high);	//выбираем опорный элемент и вызываем функцию partition
        quick_sort(arr, low, pivot - 1); 		//рекурсивно сортируем элементы меньше опорного
        quick_sort(arr, pivot + 1, high);  		//рекурсивно сортируем элементы больше опорного
    }
}


///Тест работы функции сортировки слиянием
void quick_assert()
{
	//целые числа
	int* int_arr = new int[7]{ 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr_sort = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr0 = new int[7]{ 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr2 = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };

	quick_sort(int_arr, 0, 6);
	quick_sort(int_arr0, 0, 6);
	quick_sort(int_arr2, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;
	delete[] int_arr0;
	delete[] int_arr2;


	//целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7]{ 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7]{ 11, 22, 22, 22, 34, 64, 90 };

	quick_sort(int_arr1, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	//дробные числа
	double* double_arr = new double[3]{ 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3]{ 1.01, 1.02, 1.03 };
	quick_sort(double_arr, 0.0, 2.0);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}
