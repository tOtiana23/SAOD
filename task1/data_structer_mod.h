//Бусыгина Татьяна, ИВТ-22

#ifndef DATA_STRUCTER_MOD_H
#define DATA_STRUCTER_MOD_H
#include <fstream>				//fstream определяет базовые типы для чтения и записи файлов
#include <iomanip>
#include <cassert>				//cassert — необходимо для применения макроса assert()

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


///Вывод массива arr размера size в текстовый файл file_name
template <typename Arr>
void array_to_file(Arr* arr, size_t size, const string& file_name)
{
	ofstream file(file_name);								//открытие файла Out file stream
	if (!file.is_open())									//если не открыт файл
	{
		throw runtime_error("File not found");				//то выводим ошибку
	}
	for (unsigned i = 0; i < size; i++)						//цикл для вывода массива в файл
	{
		file << arr[i] << endl;								//выводим элемент
	}
}


///Функция вывода массива arr размера size в бинарный файл file_name
template <typename Arr>
void array_to_bin_file(Arr* arr, size_t size, const string& file_name)
{
	ofstream file(file_name, ios::binary);										//запись в файл
	if (file.is_open()) {														//проверяем, открыт ли файл

		file.write(reinterpret_cast<const char*>(&size), sizeof(size));			//записываем размер массива
																				//reinterpret_cast используется для преобразования указателя 
																				//некоторого типаданных в указатель другого типа 
																				//sizeof возвращает размер переданной переменной в байтах

		file.write(reinterpret_cast<const char*>(arr), sizeof(float) * size);	//записываем массив
		file.close();															//закрываем файл
	}
	else {
		throw runtime_error("File_is_not_found_:(");							//если нет такого файла, то выводим ошибкуi
	}
}


///Вывод массива arr размера size на экран
template <typename Arr>
void print_array(Arr* arr, size_t size)
{
	for (unsigned i = 0; i < size; i++)					//цикл от 0 до конца массива
		cout << setprecision(3) << arr[i] << " ";		//происходит вывод с округлением в цикле
	cout << endl;
}


///Проверка отсортирован ли динамический массив arr размера size, l - по убыванию, иначе по возрастанию
template<typename Arr>
bool is_sorted(const Arr* arr, size_t size, const char mode = 'b')
{
	if (size == 0 || size == 1)
		return true;

	if (mode == 'l')
		for (size_t i = 0; i < size - 1; i++) {
			if (arr[i] < arr[i + 1]) return false;}
	else
		for (size_t i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) return false;
		}
	return true;
}


///Последовательный поиск элемента check в массиве arr размера size
template<typename Arr>
long long int search(const Arr* arr, size_t size, Arr check)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i] == check)
			return i;					//если нашли элемент, то возвращаем его индекс
		return -1;						//иначе возвращаем -1
	}
}


///Сортировка пузырьком массива arr размера size
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


///Бинарный поиск элемента check в отсортированном по возрастанию массиве arr размера size
template <typename Arr>
long long int binary_search(Arr* arr, size_t size, Arr check)
{
	int low = 0;					//нижняя граница
	int high = size;				//верхняя граница
	int mean;						//середина

	while (low <= high)				//пока нижняя граница не превысила верхнюю
	{
		mean = (low + high) / 2;	//Находим средину диапазона
		if (arr[mean] == check)		//если искомый элемент в центре
			return mean;			//возвращаем его
		if (arr[mean] > check)		//если искомый элемент меньше текущего
			high = mean - 1;		//то сдвигаем верхнюю границу вниз
		else
			low = mean + 1;			//иначе сдвигаем нижнюю границу вверх 
	}
	return 0;
}


///Интерполяционный поиск элемента check в отсортированном массиве arr размера size
template<typename Arr>
long long int interpolation_search(Arr* arr, size_t size, int check)
{
	int low = 0;					//нижний индекс массива
	int high = size - 1;			//верхний индекс массива

	//пока нижний индекс не превышает верхний и целевой элемент находится в диапазоне от arr[low] до arr[high]
	while (low <= high && check >= arr[low] && check <= arr[high]) {

		if (low == high) {			//если нижний индекс равен верхнему индексу
			if (arr[low] == check)	//если элемент в позиции low равен целевому элементу, возвращаем low
				return low;
			return -1;				//иначе элемент не найден, возвращаем -1
		}

		//вычисляем примерное положение целевого элемента по формуле интерполяции
		int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (check - arr[low]));
							
		if (arr[pos] == check)		//если элемент в позиции pos равен целевому элементу, возвращаем pos
			return pos;								
		else if (arr[pos] < check)	//если элемент в позиции pos меньше целевого элемента, смещаемся вправо
			low = pos + 1;
		else						//иначе смещаемся влево
			high = pos - 1;
	}				
	return -1;						//элемент не найден, возвращаем -1
}

///Тест интерполяционного поиска
void interpolation_search_assert()
{
	int* arr = new int[10] { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
	assert(interpolation_search(arr, 10, 12) == 5);		//успешный поиска

	assert(interpolation_search(arr, 10, 7) == -1);		//неудачный поиска
	delete[] arr;

	int* arr2 = new int[0] {};
	assert(interpolation_search(arr2, 0, 5) == -1);		//поиск в пустом массиве
	delete[] arr2;

	int* arr3 = new int[1] {10};
	assert(interpolation_search(arr3, 1, 10) == 0);		//поиск в массиве с одним элементом
	delete[] arr3;
}

///Тест последовательного поиска
void search_assert()
{

	int* arr0 = new int[5] { 1, 2, 3, 4, 5 };
	assert(binary_search(arr0, 5, 3) == 2);		//успешный поиск элемента в массиве
	delete[] arr0;

	int* arr1 = new int[5] { 1, 2, 3, 4, 5 };
	assert(binary_search(arr1, 5, 6) == 0);		//неудачный поиск элемента в массиве
	delete[] arr1;

	int* arr2 = new int[0] {};
	assert(binary_search(arr2, 0, 5) == 0);		//пустой массив
	delete[] arr2;

	int* arr3 = new int[1] { 10 };
	assert(binary_search(arr3, 1, 10) == 0);	//массив с одним элементом(искомый элемент) :

	assert(binary_search(arr3, 1, 5) == 0);		//массив с одним элементом(неискомый элемент) :
	delete[] arr3;
}

///Тест проверки на сортировку
void is_sorted_assert()
{
	unsigned* int_arr1 = new unsigned[3] {1, 2, 3};
	unsigned* int_arr2 = new unsigned[3] {4, 2, 3};
	assert(is_sorted(int_arr1, 3));
	assert(is_sorted(int_arr2, 3) == false);
	delete[] int_arr1;
	delete[] int_arr2;

	double* double_arr1 = new double[3] {1.01, 1.02, 1.03};
	double* double_arr2 = new double[3] {1.01, 1.002, 1.03};
	double* double_arr3 = new double[3] {1.01, 1.002, 1.0003};
	assert(is_sorted(double_arr1, 3));
	assert(is_sorted(double_arr2, 3) == false);
	assert(is_sorted(double_arr3, 3, 'l'));
	delete[] double_arr1;
	delete[] double_arr2;
	delete[] double_arr3;

	std::string* string_arr1 = new std::string[3]{ "aaa", "aab", "aac" };
	std::string* string_arr2 = new std::string[3]{ "aad", "aab", "aac" };
	assert(is_sorted(string_arr1, 3));
	assert(is_sorted(string_arr2, 3) == false);
	delete[] string_arr1;
	delete[] string_arr2;

}

///Тест функции бинарного поиска
void binary_search_assert()
{
	int* arr0 = new int[5] { 1, 2, 3, 4, 5 };
	assert(binary_search(arr0, 5, 3) == 2);			//успешный поиск элемента в массиве
	delete[] arr0;

	int* arr1 = new int[5] { 1, 2, 3, 4, 5 };
	assert(binary_search(arr1, 5, 6) == 0);			//неудачный поиск элемента в массиве
	delete[] arr1;

	int* arr2 = new int[0] {};
	assert(binary_search(arr2, 0, 5) == 0);			//пустой массив 
	delete[] arr2;

	int* arr3 = new int[1] { 10 };
	assert(binary_search(arr3, 1, 10) == 0);		//массив с одним элементом(искомый элемент)

	assert(binary_search(arr3, 1, 5) == 0); 		//массив с одним элементом(неискомый элемент)
	delete[] arr3;
}

//Тест работы функции сортировки
void bubble_assert()
{
	//целые числа
	int* int_arr = new int[7] {64, 34, 25, 12, 22, 11, 90};
	int* int_arr_sort = new int[7] {11, 12, 22, 25, 34, 64, 90};

	bubble_sort(int_arr, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;

	//дробные числа
	double* double_arr = new double[3] { 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3] { 1.01, 1.02, 1.03 };
	bubble_sort(double_arr, 3);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}

/////Поиск кол-ва элементов массива в файле
//unsigned array_size_form_file(const string& file_name)
//{
//	unsigned res = 0;                                   //переменная для счета кол-ва строк
//	string line;                                        //строка, с помощью которой ищем кол-во строк
//	ifstream file(file_name);                           //открытие файла In file stream
//	if (!file.is_open())                                //если не открыт файл
//	{
//		throw runtime_error("File not found");			//если что, то в ошибку
//		// return 0;
//	}
//	while (getline(file, line))                         //цикл счёта кол-ва строк -> кол-ва элементов массива
//	{
//		res++;											//цикл будет жить, пока getline делает переходы
//	}
//	file.close();                                       //закрыть файл
//	if (res == 0)                                       //ошибка, если файл пуст
//		throw runtime_error("Array not found in file - file is empty");
//}
//
/////Выгоняет массив из бинарного файла
//template<typename Arr>
//void array_from_bin_file(Arr*& arr, size_t& size, const string& file_name)
//{
//	ifstream file(file_name, ios::binary);
//	file.read(reinterpret_cast<char*>(&size), sizeof(size));
//	arr = new float[size];
//	file.read(reinterpret_cast<char*>(arr), sizeof(float) * size);
//	file.close();
//}


#endif