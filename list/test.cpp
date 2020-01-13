#include <iostream>
#include "list.h"

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
    LinkedList<int> *list = new SingleList<int> ();
    //test_single_list();
    //test_single_cycle_list();
    //test_doubly_list();
    //reverse_single_list();
    //merge_2_sorted_list();

    return 0;
}