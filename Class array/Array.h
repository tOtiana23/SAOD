//Бусыгина Татьяна, ИВТ-22


#ifndef ARRAY_H
#define ARRAY_H
#include <cassert>
#include <iostream>

using namespace std;

template <typename Arr>
class Array
{
private:

	///указатель на начало массива
	Arr* array;

	///индекс последней свободной ячейки
	size_t last_index;

	///размер массива
	size_t size;

public:

	///Конструктор без параметров
	Array()
	{
		array = nullptr;
		last_index = 0;
		size = 0;
	}

	///Конструктор с параметрами
	Array(size_t size_arr)
	{
		if (size_arr > 0)
		{
			size = size_arr;
			last_index = size_arr;
			array = new Arr[size];
		}
		else throw invalid_argument("Size must be > 0");
	}

	///Переопределение оператора []
	Arr& operator[](size_t index)
	{
		if (index < size)
		{
			return array[index];
		}
		else throw invalid_argument("Index must be within the bounds of the array"); 
	}

	///Изменение размера массива
	void resize(size_t new_size)
	{
		last_index = new_size;
		size = new_size;
	}

	///Количество элементов в массиве
	size_t length()
	{
		return last_index;
	}

	///Добавляем элемент в конец массива
	void add_last(Arr new_element)
	{
		if (last_index < size) //если есть свободное место, то добавляем
		{
			array[last_index] = new_element;
			last_index ++;
		} 
		else
		{
			Arr* new_array = new Arr[2*size]; //выделяем в два раза больше памяти для будущего добавления
			memcpy(new_array, array, size * sizeof(new_array)); //умножаем на size потому что размер в байтах
			size *= 2;
			array = new Arr[size];
			memcpy(array, new_array, size * sizeof(array));
			array[last_index] = new_element;
			last_index ++;
			delete[] new_array;
		}
	}


	///Удаление последнего элемента
	void del_last() 
    { 
        if (last_index >= 0) 
        { 
            last_index --; 
        } 
        else 
        { 
            throw invalid_argument("This array is empty!"); 
        } 
    }


	///Ищем элемент check в массиве, возвращается индекс первого вхождения искомого элемента
	long long search(Arr check)
	{
		for (size_t i = 0; i < last_index; ++i)
		{
			 if ((abs(array[i] - check) < 0.00001))
            {
                return i;
            }
            else if (array[i] == check)
            {
                return i;
            }
		}
		return -1; //иначе возвращаем -1
	}


	///Функция для слияния двух подмассивов arr, где left начало массива = 0, right = размеру массива 
	///mid - середина массива, по которой мы делим (вычисляется в функции merge_sort)
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
	void merge_sort(Arr* arr, size_t left = 0, size_t right = 0) {
		right = last_index;
		if (left < right) { 									//проверка, что левое значение меньше правого

			size_t mid = left + (right - left) / 2; 			//вычисление середины массива

			merge_sort(arr, left, mid); 					//рекурсивный вызов merge_sort для левой части массива
			merge_sort(arr, mid + 1, right); 				//рекурсивный вызов merge_sort для правой части массива

			merge(arr, left, mid, right); 					//вызов функции merge для слияния двух отсортированных подмассивов
		}
	}

	///Деструктор
	~Array()
	{
		if (array = nullptr)
			delete array;
		else
			delete[] array;
	}

};

///Тест работы функции сортировки слиянием
void merge_assert()
{
	Array<int> arr_int;
	//целые числа
	int* int_arr = new int[7]{ 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr_sort = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr0 = new int[7]{ 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr2 = new int[7]{ 11, 12, 22, 25, 34, 64, 90 };

	arr_int.merge_sort(int_arr, 0, 6);
	arr_int.merge_sort(int_arr0, 0, 6);
	arr_int.merge_sort(int_arr2, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}


	// //целые числа, повторяющиеся элементы
	// int* int_arr1 = new int[7]{ 64, 34, 22, 22, 22, 11, 90 };
	// int* int_arr_sort1 = new int[7]{ 11, 22, 22, 22, 34, 64, 90 };

	// arr_int.merge_sort(int_arr1, 0, 6);
	// for (size_t i = 0; i < 7; i++)
	// {
	// 	assert(int_arr1[i] == int_arr_sort1[i]);
	// }
	// delete[] int_arr1;
	// delete[] int_arr_sort1;

	// Array<double> arr_double;
	// //дробные числа
	// double* double_arr = new double[3]{ 1.03, 1.01, 1.02 };
	// double* double_arr_sort = new double[3]{ 1.01, 1.02, 1.03 };
	// arr_double.merge_sort(double_arr, 0, 2);
	// for (size_t i = 0; i < 3; i++)
	// {
	// 	assert(double_arr[i] == double_arr_sort[i]);
	// }
	// delete[] double_arr;
	// delete[] double_arr_sort;
}

///Тест последовательного поиска
void search_assert()
{
	Array<int> arr_int(5);
	for(size_t i = 0; i < 5; i++)
	{
		arr_int[i] = i;
	}
	assert(arr_int.search(3) == 3);		//успешный поиск элемента в массиве
	assert(arr_int.search(6) == -1);	//нет элемента
	arr_int.add_last(4);
	assert(arr_int.length() == 6);

	Array<double> arr_double(5);
	for (size_t i = 0; i < 5; i++)
    {
        arr_double[i] = i * 0.1;
    }
    assert(arr_double.search(0.3) == 3); // успешный поиск элемента в массиве
	assert(arr_double.search(0.6) == -1);	//нет элемента
}

///Тест оператора []
void test_operator_brackets()
{
    Array<int> arr(5);
    arr.add_last(10);
    assert(arr[5] == 10);
}

///Тест изменения размера массива
void test_resize()
{
    Array<int> arr(5);
    arr.resize(3);
    assert(arr.length() == 3);
}

///Тест добавления элемента в конец массива
void test_add_last()
{
    Array<int> arr(2);
    arr.add_last(10);
    arr.add_last(20);
    arr.add_last(30);
    assert(arr.length() == 5);
}

///Тест удаления последнего элемента
void test_del_last()
{
    Array<int> arr(3);
    arr.add_last(10);
    arr.add_last(20);
    arr.del_last();
    assert(arr.length() == 4);
}

#endif
