#include "list.h"
#include <cassert>

//Бусыгина Татьяна, ИВТ-22
template <typename Type>
///Класс очередь
class Queue : private List<Type>
{
public:

    ///добавление элемента в очередь, element то, что добавляем
    void enqueue(Type element)
    {
        this->add_first(element);
    }

    ///удаление элемента из очереди
    Type dequeue()
    {
        if (this->isEmpty())
        {
            return Type();
        }
        Type val = this->get_node(this->sizes() - 1)->data;
        this->del_last();
        return val;
    }

    ///проверяет пуста ли очередь
    bool isEmpty() {
        bool empty = false;
        if (this->sizes() == 0)
            empty = true;
        return empty;
    }

    ///возращает последний элемент очереди, если список пуст, то 0
    Type peek() {
        if (this->isEmpty())
        {
            return 0;
        }
        return this->get_node(this->sizes() - 1)->data;
    }

    ///Последний элемент очереди
    Type get_tail() {
        return this->get_node(0)->data;
    }

    ///Первый элемент очереди
    Type get_head() {
        return this->get_node(this->sizes() - 1)->data;
    }

    ///Размер очереди
    size_t size() {
        return this->sizes();
    }

};

///Тестирование метода enqueue 
void test_enqueue() {

    Queue<int> queue;

    queue.enqueue(1);
    assert(queue.get_tail() == 1);

    queue.enqueue(2);
    assert(queue.get_tail() == 2);

    queue.enqueue(3);
    assert(queue.get_tail() == 3);

    Queue<double> queue1;

    queue1.enqueue(1.1);
    assert(queue1.get_tail() == 1.1);

    queue1.enqueue(2.2);
    assert(queue1.get_tail() == 2.2);

    queue1.enqueue(3.3);
    assert(queue1.get_tail() == 3.3);
}

///Тестирование метода dequeue
void test_dequeue() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue.dequeue();
    assert(queue.size() == 2);
    assert(queue.get_tail() == 3);

    queue.dequeue();
    assert(queue.size() == 1);
    assert(queue.get_tail() == 3);


    Queue<double> queue1;

    queue1.enqueue(1.1);
    queue1.enqueue(2.2);
    queue1.enqueue(3.3);

    queue1.dequeue();
    assert(queue1.size() == 2);
    assert(queue1.get_tail() == 2.2);

    queue1.dequeue();
    assert(queue1.size() == 1);
    assert(queue1.get_tail() == 3.3);

    queue1.dequeue();
    assert(queue1.get_tail() == 0.0);

}

