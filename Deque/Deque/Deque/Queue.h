#include "list.h"
#include <cassert>

//�������� �������, ���-22
template <typename T>
///����� �������
class Queue : public List<T>
{
public:

    ///���������� �������� � �������, element ��, ��� ���������
    void enqueue(T element)
    {
        this->add_first(element);
    }

    ///�������� �������� �� �������
    T dequeue()
    {
        if (this->isEmpty())
        {
            return T();
        }
        T val = this->get_node(this->sizes() - 1)->data;
        this->del_last();
        return val;
    }

    ///��������� ����� �� �������
    bool isEmpty() {
        bool empty = false;
        if (this->sizes() == 0)
            empty = true;
        return empty;
    }

    ///��������� ��������� ������� �������, ���� ������ ����, �� 0
    T peek() {
        if (this->isEmpty())
        {
            return 0;
        }
        return this->get_node(this->sizes() - 1)->data;
    }

    ///��������� ������� �������
    T get_tail() {
        return this->get_node(0)->data;
    }

    ///������ ������� �������
    T get_head() {
        return this->get_node(this->sizes() - 1)->data;
    }

    ///������ �������
    size_t size() {
        return this->sizes();
    }

};

///������������ ������ enqueue 
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

///������������ ������ dequeue
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

