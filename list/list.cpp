#include <iostream>
#include "list.h"

/**** SingleList ****/
template <typename T>
bool SingleList<T>::is_empty() const
{
    return _count == 0;
}

template <typename T>
void SingleList<T>::pop_front()
{
    if (!is_empty()) {
        ListNode<T> *p = _head->_next;
        _head->_next = p->_next;
        delete p;
        _count--;
    }
}

template <typename T>
void SingleList<T>::pop_back()
{
    if (!is_empty()) {
        ListNode<T> *p = nullptr;
        p = find_end_prev();
        if (p) {
            delete p->_next;
            p->_next = nullptr;
            _count--;
        }
    }
}

template <typename T>
void SingleList<T>::push_front(const T &data)
{
    ListNode<T> *p = new ListNode<value_type>();
    if (!p) return;
    p->_val = data;
    p->_next = _head->_next;

    _head->_next = p;
    _count++;
}

template <typename T>
void SingleList<T>::push_back(const T &data)
{
    ListNode<T> *p = new ListNode<value_type>();
    if (!p) return;
    p->_val = data;
    p->_next = nullptr;

    ListNode<T>* &q = find_end();
    if (q != nullptr) {
        q->_next = p;
        _count++;
    }
}

template <typename T>
size_t SingleList<T>::size() const
{
    return _count;
}

template <typename T>
typename SingleList<T>::reference SingleList<T>::front()
{
    if (!is_empty()) {
        return _head->_next->_val;
    }
}

template <typename T>
typename SingleList<T>::reference SingleList<T>::back()
{
    if (!is_empty()) {
        return find_end()->_val;
    }
}

template <typename T>
typename SingleList<T>::const_reference SingleList<T>::front() const
{
    if (!this->is_empty()) {
        return _head->_next->_val;
    }
}

template <typename T>
typename SingleList<T>::const_reference SingleList<T>::back() const
{
    if (!is_empty()) {
        ListNode<T> *p = _head;
        while (p->_next) {
            p = p->_next;
        }
        return p->_val;
    }
}

template <typename T>
void SingleList<T>::show() const
{
    ListNode<T> *p = _head;
    int i = 1;
    while(p->_next) {
        std::cout << "(" << i++ << "/" << size() << "): " << p->_next->_val <<std::endl;
        p = p->_next;
    }
    std::cout << std::endl;
}

/**** SingleCycleList ****/
template <typename T>
void SingleCycleList<T>::push_back(const T &data)
{
    ListNode<T> *p = new ListNode<value_type>();
    if (!p) return;
    p->_val = data;
    p->_next = SingleList<T>::_head;

    ListNode<T>* &q = find_end();
    if (q != nullptr) {
        q->_next = p;
        SingleList<T>::_count++;
    }
}

template <typename T>
void SingleCycleList<T>::pop_back()
{
    if (!SingleList<T>::is_empty()) {
        ListNode<T> *p = nullptr;
        p = find_end_prev();
        if (p) {
            delete p->_next;
            p->_next = SingleList<T>::_head;
            SingleList<T>::_count--;
        }
    }
}

template <typename T>
typename SingleCycleList<T>::reference SingleCycleList<T>::back()
{
    if (!SingleList<T>::is_empty()) {
        return find_end()->_val;
    }
}

template <typename T>
typename SingleCycleList<T>::const_reference SingleCycleList<T>::back() const
{
    if (!SingleList<T>::is_empty()) {
        ListNode<T> *p = SingleList<T>::_head;
        while (p->_next != SingleList<T>::_head) {
            p = p->_next;
        }
        return p->_val;
    }
}

template <typename T>
void SingleCycleList<T>::show() const
{
    ListNode<T> *p = SingleList<T>::_head;
    int i = 1;
    while(p->_next != SingleList<T>::_head) {
        std::cout << "(" << i++ << "/" << SingleList<T>::size() << "): " << p->_next->_val <<std::endl;
        p = p->_next;
    }
    std::cout << std::endl;
}

/**** DoublyList ****/
template <typename T>
bool DoublyList<T>::is_empty() const
{
    return _count == 0;
}

template <typename T>
void DoublyList<T>::pop_front()
{
    if (!is_empty()) {
        ListNode<T> *p = _head->_next;
        _head->_next = p->_next;
        if (size() > 1) {
            p->_next->_prev = _head;
        } else if (size() == 1) {
            _tail = _head;
        }

        delete p;
        _count--;
    }
}

template <typename T>
void DoublyList<T>::pop_back()
{
    if (!is_empty()) {
        ListNode<T> *p = _tail;
        _tail = p->_prev;
        _tail->_next = nullptr;
        delete p;
        _count--;
    }
}

template <typename T>
void DoublyList<T>::push_front(const value_type &data)
{
    ListNode<T> *p = new ListNode<value_type>();
    if (!p) return;
    p->_val = data;

    p->_next = _head->_next;
    p->_prev = _head;

    if (is_empty()) {
        _tail = p;
    } else {
         _head->_next->_prev = p;
    }
    _head->_next = p;
    _count++;
}

template <typename T>
void DoublyList<T>::push_back(const value_type &data)
{
    ListNode<T> *p = new ListNode<value_type>();
    if (!p) return;
    p->_val = data;
    p->_next = nullptr;
    p->_prev = _tail;

    _tail->_next = p;
    _tail = p;
    _count++;
}

template <typename T>
size_t DoublyList<T>::size() const
{
    return _count;
}

template <typename T>
typename DoublyList<T>::reference DoublyList<T>::front()
{
    if (!is_empty()) {
        return _head->_next->_val;
    }
}

template <typename T>
typename DoublyList<T>::reference DoublyList<T>::back()
{
    if (!is_empty()) {
        return _tail->_val;
    }
}

template <typename T>
typename DoublyList<T>::const_reference DoublyList<T>::front() const
{
    if (!this->is_empty()) {
        return _head->_next->_val;
    }
}

template <typename T>
typename DoublyList<T>::const_reference DoublyList<T>::back() const
{
    if (!is_empty()) {
        return _tail->_val;
    }
}

template <typename T>
void DoublyList<T>::show() const
{
    ListNode<T> *p = _head;
    int i = 1;
    while(p->_next) {
        std::cout << "(" << i++ << "/" << size() << "): " << p->_next->_val <<std::endl;
        p = p->_next;
    }
    std::cout << std::endl;
}

void test_single_list()
{
    LinkedList<int> *list = new SingleList<int> ();
    list->push_front(5);
    list->push_front(4);
    list->push_front(3);
    list->push_front(2);
    list->push_front(1);

    list->push_back(5);
    list->push_back(4);
    list->push_back(3);
    list->push_back(2);
    list->push_back(1);
    
    list->show();

    std::cout << "front: " << list->front() << std::endl;
    std::cout << "back: " << list->back() << std::endl;
    list->back() = 10;

    list->show();
    delete list;
}

void test_single_cycle_list()
{
    LinkedList<int> *list = new SingleCycleList<int> ();
    list->push_front(5);
    list->push_front(4);
    list->push_front(3);
    list->push_front(2);
    list->push_front(1);

    list->push_back(5);
    list->push_back(4);
    list->push_back(3);
    list->push_back(2);
    list->push_back(1);
    
    list->show();

    std::cout << "front: " << list->front() << std::endl;
    std::cout << "back: " << list->back() << std::endl;
    list->back() = 10;

    list->show();
    delete list;
}

void test_doubly_list()
{
    LinkedList<int> *list = new DoublyList<int> ();
    list->push_front(5);
    list->push_front(4);
    list->push_front(3);
    list->push_front(2);
    list->push_front(1);

    list->push_back(5);
    list->push_back(4);
    list->push_back(3);
    list->push_back(2);
    list->push_back(1);
    
    list->show();

    std::cout << "front: " << list->front() << std::endl;
    std::cout << "back: " << list->back() << std::endl;
    list->back() = 10;

    list->show();
    delete list;
}


void reverse_single_list()
{
    LinkedList<int> *list = new SingleList<int> ();
    list->push_front(5);
    list->push_front(4);
    list->push_front(3);
    list->push_front(2);
    list->push_front(1);
    list->show();

    LinkedList<int> *nlist = new SingleList<int> ();
    while(!list->is_empty()) {
        nlist->push_front(list->front());
        list->pop_front();
    }
    nlist->show();

    delete list;
    delete nlist;
}

void merge_2_sorted_list()
{
    LinkedList<int> *list1 = new SingleList<int> ();
    list1->push_front(15);
    list1->push_front(10);
    list1->push_front(8);
    list1->push_front(6);
    list1->push_front(4);
    list1->push_front(2);
    list1->show();

    LinkedList<int> *list2 = new SingleList<int> ();
    list2->push_front(9);
    list2->push_front(7);
    list2->push_front(3);
    list2->push_front(3);
    list2->push_front(1);
    list2->show();

    LinkedList<int> *list3 = new SingleList<int> ();

    while(!list1->is_empty() && !list2->is_empty()) {
        if (list1->front() <= list2->front()) {
            list3->push_back(list1->front());
            list1->pop_front();
        } else {
            list3->push_back(list2->front());
            list2->pop_front();
        }
    }

    while(!list1->is_empty()) {
        list3->push_back(list1->front());
        list1->pop_front();
    }

    while(!list2->is_empty()) {
        list3->push_back(list2->front());
        list2->pop_front();
    }

    list1->show();
    list2->show();
    list3->show();

    delete list1;
    delete list2;
    delete list3;
}

int main()
{
    //test_single_list();
    //test_single_cycle_list();
    //test_doubly_list();
    //reverse_single_list();
    merge_2_sorted_list();

    return 0;
}