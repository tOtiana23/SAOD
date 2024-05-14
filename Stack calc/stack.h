//Бусыгина Татьяна, ИВТ-22
#include "list.h" 
#include <cassert> 
#include <iostream>

///Класс Stack
template <typename T> 
class Stack : public List<T> //Наследование от двусвязного списка
{ 
public: 
    ///Добавление элемента в вершину стека, element - то, что добавляем
    void push(T element) 
    { 
        this->add_first(element); 
    } 
 
    ///Удаление элемента из вершины стека
    void pop() 
    { 
        //проверяем, что стек не пустой
        if (this->sizes() == 0) { 
            throw out_of_range("Stack is empty!"); 
            return; } 
        //удаляем
        this->del_first(); 
    } 
}; 
 
///Тестирование метода push 
void test_push() { 
    Stack<int> stack; 
 
    stack.push(1); 
    assert(stack.get_node(0)->data == 1); 
 
    stack.push(2); 
    assert(stack.get_node(0)->data == 2); 
    stack.push(3); 
 
    assert(stack.get_node(1)->data == 2); 
    assert(stack.get_node(0)->data == 3); 

    Stack<double> stack1; 
 
    stack1.push(1.1); 
    assert(stack1.get_node(0)->data == 1.1); 
 
    stack1.push(2.2); 
    assert(stack1.get_node(0)->data == 2.2); 

    stack1.push(3.3); 
    assert(stack1.get_node(1)->data == 2.2); 
    assert(stack1.get_node(0)->data == 3.3); 
} 
 
///Тестирование метода pop 
void test_pop() { 
    Stack<int> stack; 
 
    stack.push(1); 
    stack.push(2); 
    stack.push(3); 
 
    stack.pop(); 
    assert(stack.sizes() == 2); 
    assert(stack.get_node(0)->data  == 2); 
 
    stack.pop(); 
    assert(stack.sizes() == 1); 
    assert(stack.get_node(0)->data  == 1); 
 

    Stack<double> stack1; 
 
    stack1.push(1.1); 
    stack1.push(2.2); 
    stack1.push(3.3); 
 
    stack1.pop(); 
    assert(stack1.sizes() == 2); 
    assert(stack1.get_node(0)->data  == 2.2); 
 
    stack1.pop(); 
    assert(stack1.sizes() == 1); 
    assert(stack1.get_node(0)->data  == 1.1); 
} 
