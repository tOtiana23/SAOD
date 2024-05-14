#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

//Бусыгина Татьяна, ИВТ-22
//Задача на жадные алгоритмы, поиск наибольшей стоимости предметов, которые можно положить в рюкзак с ограниченной вместимостью
struct Item {
    int weight; //вес предмета
    int value; //стоимость предмета
};

//Сравнение предметов по отношению стоимости к весу (ценность)
bool compareItems(Item i1, Item i2) {
    return (double)i1.value / i1.weight > (double)i2.value / i2.weight; 
}

///Поиск наибольшей стоимости
int knapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(), compareItems); //сортировка предметов по убыванию отношения стоимости к весу
    //items.begin() и items.end() задают диапазон элементов, который нужно отсортировать. compareItems — это функция сравнения, которая определяет порядок сортировки
    //Если функция compareItems(a, b) возвращает true, то элемент a будет расположен перед элементом b в отсортированном массиве. Если она возвращает false, то элементы останутся в том же порядке, в котором они были изначально.
    int totalValue = 0;
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value; // добавление стоимости предмета, если есть место в рюкзаке
            capacity -= item.weight; // вычитание веса добавленного предмета из вместимости
        } else {
            totalValue += (double)capacity / item.weight * item.value; // добавление части стоимости предмета, если места не хватает
            break;
        }
    }

    return totalValue; // возвращение общей стоимости предметов в рюкзаке
}

void test() {
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    int capacity = 60;
    assert(knapsack(items, capacity) == 280);
    capacity = 20;
    assert(knapsack(items, capacity) == 110); 
    capacity = 0;
    assert(knapsack(items, capacity) == 0);
}

int main(int argc, char* argv[]) {
    test();
    
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    int capacity;

    
    if (argc > 1) {
    capacity = atoi(argv[1]);
        
    }
    else{
        capacity = 50;
    }

    int result = knapsack(items, capacity);
    
    cout << "Max cost: " << result << endl;

    return 0;
}