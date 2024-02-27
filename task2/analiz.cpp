//Бусыгина Татьяна, ИВТ-22
/*Напишите программу для поиска второго по величине элемента в списке из N значений. 
Сколько сравнений делает Ваш алгоритм в наихудшем случае? Результаты тестирования вывести в текстовый файл.*/

/*В наихудшем случае алгоритм делает n-1 сравнений*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cassert>


using namespace std;

template <typename Arr>
Arr find(const vector<Arr>& nums) 
{
    Arr first = -1000;
    Arr second = -1000;

    for (Arr num : nums)
    { 
        if (num > first)
        {
            second = first;
            first = num;
        } else if (num > second && num != first)
        {
            second = num;
        }
    }
    return second;
}

void asserts()
{
    //Тест на пустом векторе
    assert(find(vector<int>()) == -1000);

    //Тест на векторе с одним элементом
    assert(find(vector<int>{42}) == -1000);

    //Тест на векторе с повторяющимися элементами
    assert(find(vector<int>{1, 1, 1, 1}) == -1000);

    //Тест на целых числах
    assert(find(vector<int>{3, 5, 2, 7, 4}) == 5);

    //Тест на дробных числах
    assert(abs(find(vector<double>{3.5, 1.2, 7.8, 4.9}) - 4.9) < 1e-9);

}

int main() {
    asserts();
    vector<vector<int>> test = {
        {1, 2, 3, 4, 5},
        {10, 20, 30, 40, 50},
        {5, 4, 3, 2, 1}
    };

    ofstream file("results.txt");//открываем файл
    if (!file.is_open())//если файл не открыт, то выводим ошибку
    {
        throw runtime_error("File not found");  
        return 0;
    }

    for (const auto& test : test) { 
        int result = find(test); //записываем полученный элемент
        file << "Test case: ";
        for (int num : test) { 
            file << num << " "; //выводим элементы
        }
        file << endl << "Second largest element: " << result << endl; //выводим результат в файл
    }

    file.close();//закрываем файл
}
