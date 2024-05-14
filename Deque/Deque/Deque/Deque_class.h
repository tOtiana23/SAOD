#include "Queue.h"
#include <cassert>

//�������� �������, ���-22
template <typename Type>
/// <summary>
/// ����� ������������ �������, ����������� �� ������� �������
/// </summary>
class Deque : private Queue<Type>
{
public:

    ///���������� �������� � ������ �������, element - ����������� ������� 
    //���������: O(1) 
    void push_front(Type element)
    {
        this->enqueue(element);
    }

    ///���������� �������� � ����� �������, element - ����������� �������
    //���������: O(1) 
    void push_back(Type element)
    {
        this->add_last(element);
    }

    ///�������� �������� �� ����� �������, ���������� �������� ���������� ��������, ��� 
    //�������� �� ��������� ��� Type, ���� ������� ����� 
    //���������: O(1) 
    Type pop_back()
    {
        return this->dequeue();
    }

    ///�������� �������� �� ������ �������, ���������� �������� ���������� ��������, ��� 
    //�������� �� ��������� ��� Type, ���� ������� ����� 
    //���������: O(1) 
    Type pop_front()
    {
        //���� �����, �� ���������� �������� �� ��������� 
        if (this->isEmpty())
        {
            return Type();
        }

        Type val = this->get_node(0)->data;
        this->del_first();
        return val;
    }

    ///�������� �� ������� 
    //���������: O(1) 
    bool is_empty()
    {
        return this->Queue<Type>::isEmpty();
    }

    ///���������� �������� ����� ������� 
    Type get_back() {
        return this->get_tail();
    }

    ///���������� �������� ������ ������� 
    Type get_front() {
        return this->get_head();
    }

    /// ������� � ������
    string to_string() const {
        return this->to_string();
    }

    ///���������� ������ ������� 
    size_t length() {
        return this->Queue<Type>::size();
    }

    ///������� ������� 
    //���������: O(n) 
    void clear()
    {
        while (!this->isEmpty())
        {
            this->dequeue();
        }
    }
};

///���� ������ push_front
void test_push_front() {
    Deque<int> queue;

    queue.push_front(1);
    assert(queue.get_back() == 1);

    queue.push_front(2);
    assert(queue.get_back() == 2);
    queue.push_front(3);

    assert(queue.get_front() == 1);
    assert(queue.get_back() == 3);
}

///���� ������ push_back
void test_push_back() {

    Deque<int> queue;

    queue.push_back(1);
    assert(queue.get_front() == 1);

    queue.push_back(2);
    assert(queue.get_front() == 2);
    queue.push_back(3);

    assert(queue.get_back() == 1);
    assert(queue.get_front() == 3);
}

///���� ������ pop_back 
void test_pop_back() {

    Deque<int> queue;

    queue.push_front(1);
    queue.push_front(2);
    queue.push_front(3);

    queue.pop_back();
    assert(queue.length() == 2);

    assert(queue.get_back() == 3);

    queue.pop_back();
    assert(queue.length() == 1);
    assert(queue.get_back() == 3);

    assert(queue.pop_back() == 3);
    assert(queue.length() == 0);

    //�������� �� ������ ������ ������� double 
    Deque<double> queueEmpty;
    assert(queueEmpty.pop_back() == 0.0);

    //�������� �� ������ ������ ������� ����� 
    Deque<string> queueEmpty2;
    assert(queueEmpty2.pop_back() == "");
}

///���� ������ pop_front 
void test_pop_front() {

    Deque<int> queue;

    queue.push_back(1);
    queue.push_back(2);
    queue.push_back(3);

    queue.pop_front();
    assert(queue.length() == 2);

    assert(queue.get_front() == 3);

    queue.pop_front();
    assert(queue.length() == 1);
    assert(queue.get_front() == 3);

    assert(queue.pop_front() == 3);
    assert(queue.length() == 0);

    //�������� �� ������ ������ ������� double 
    Deque<double> queueEmpty;
    assert(queueEmpty.pop_front() == 0.0);

    //�������� �� ������ ������ ������� ����� 
    Deque<string> queueEmpty2;
    assert(queueEmpty2.pop_front() == "");
}

///���� ��� is_empty 
void test_is_empty() {

    Deque<int> queue;
    assert(queue.is_empty());

    queue.push_front(1);
    assert(!queue.is_empty());

    queue.pop_back();
    assert(queue.is_empty());
}

///����� ������� ������ ���
void test_deque() {
    test_push_back();
    test_push_front();
    test_pop_back();
    test_pop_front();
    test_is_empty();
}