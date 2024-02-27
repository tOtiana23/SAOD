//Бусыгина Татьяна, ИВТ-22

#include <chrono>					//chrono — предоставляет набор типов и функций для работы со временем.
#include <iostream>					//iostream - стандартный библиотечный заголовочный файл для работы с потоками ввода-вывода 
#include <ctime>					//ctime используется для работы с датой и временем
#include <algorithm>				//для сортировки
#include "data_structer_mod.h"		//мой модуль

using namespace std;
using namespace chrono; 

int main() {

	//Ассерты
	is_sorted_assert();					//проверка на сортировку
	search_assert();					//последовательный поиск
	bubble_assert();					//сортировка пузырьком
	binary_search_assert();				//бинарный поиск
	interpolation_search_assert();		//интерполяционный поиск


	setlocale(0, "Russian");			//подключаем русский язык
	srand(time(0));						//Srand - Это инициализация генератора случайных чисел, time - возвращает 
										//текущее календарное время системы, в качестве аргумента она принимает указатель на
										//переменную типа time_t, которой и будет присвоено календарное время


	///выгрузка массива из бинарного файла
	//size = array_size_form_file("1");				// Находим кол-во элементов мас из файла
	//float* a = new float[size]; 						// Выделяем память под динамический массив
	//array_from_bin_file(arr, size, "1");				// Считываем массив из файла
	//cout << endl;
	//print_array(arr, size);					   	 		// Выводим массив на экран 
	//delete[] arr;

	///ввод названия текстового файла
	//string file_name; //имя файла для вывода массива
	//cout << "Введите название текстового файла (.txt)" << endl;
	//cin >> file_name;
	//array_to_file(arr, size, "1.txt");//вывод массива в текстовый файл
	///ввод названия бинарного файла
	//cout << "Введите название бинарного файла" << endl;
	//cin >> file_name;
	//array_to_bin_file(arr, size, "1");//вывод массива в бинарный файл
	
	///Замеряем время
	size_t size = 1000000;												//размер массива, size_t – беззнаковый целочисленный тип
	for (int i = 0; size < 10000000; i++) {
		cout << "Размер массива: " << size << endl;
		float* arr = new float[size];									//выделяем память под массив
		rand_fill_array(arr, size, 4, 5);								//заполнение массива рандомными числами в заданном диапазоне
		int time = 0;
		int iteration = 100;
		auto t0 = steady_clock::now();									//начальная отметка времени
		for (size_t i = 0; i < iteration; i++) {
			
		}
		auto t1 = steady_clock::now();									//конечная отметка времени
		auto delta = duration_cast<milliseconds>(t1 - t0);				//разница между временем t1 и t0 приводится к миллисекундам
		time = delta.count();
		cout << "Время (миллесекунды): " << time/iteration << endl;		//выводим результат
		size += 1000000;												//увеличиваем размер массива для следующего замера
	}



	int arr[] = { 64, 34, 25, 12, 22, 11, 90 };		//создаем массив с числами для сортировки и поиска
	int n = sizeof(arr) / sizeof(arr[0]);			//вычисляем размер массива
	sort(arr, arr + n);								//сортируем массив по возрастанию
	print_array(arr, n);							//вывод массива в консоль
	cout << binary_search(arr, n, 34);				//ищем элемент в массиве и выводим его индекс
	

	////поиск элемента в массиве
	//float el = 6.8;
	//unsigned check = search(arr, size, el);
	//(search(arr, size, el) == -1) ? cout << "Элемент " << el << " не найден в этом массиве" << endl :
	//	cout << "Элемент " << el << " найден с индексом: " << check << endl;

	////проверка массива на сортировку
	//bool check1 = is_sorted(arr, size, 'l');
	//check1 ? cout << "Массив отсортирован" << endl : cout << "Массив не отсортирован" << endl;
	//delete[] arr;//очищаем память

}





