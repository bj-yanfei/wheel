#include <iostream>
#include "array.h"

void test_array_push()
{
    Array<int> array(4, true);
    array.push(2,0);
    array.push(1,0);
    array.push(1,0);
    array.push(3,0);

    for (int i = 0; i<array.size(); i++) {
        std::cout << i << ": " << array.at(i) << " " << array.size() << " " << array.capacity() << std::endl;
    }
    std::cout << '\n';
    array.dell(1);
    for (int i = 0; i<array.size(); i++) {
        std::cout << i << ": " << array.at(i) << " " << array.size() << " " << array.capacity() << std::endl;
    }
}

void test_sortarray_merge()
{
    SortedArray<int> arraya = SortedArray<int> (7);
    SortedArray<int> arrayb = SortedArray<int> (5);
    Array<int> arrayc = Array<int> (12);
    arraya.push(12);
    arraya.push(10);
    arraya.push(8);
    arraya.push(6);
    arraya.push(4);
    arraya.push(2);
    arraya.push(0);

    arrayb.push(1);
    arrayb.push(3);
    arrayb.push(5);
    arrayb.push(7);
    arrayb.push(9);


    for (int i = 0; i<arraya.size(); i++) {
        std::cout << i << ": " << arraya.at(i) << " " << arraya.size() << " " << arraya.capacity() << std::endl;
    }
    std::cout << '\n';

    for (int i = 0; i<arrayb.size(); i++) {
        std::cout << i << ": " << arrayb.at(i) << " " << arrayb.size() << " " << arrayb.capacity() << std::endl;
    }
    std::cout << '\n';

    merge(arrayc, arraya, arrayb);

    for (int i = 0; i<arrayc.size(); i++) {
        std::cout << i << ": " << arrayc.at(i) << " " << arrayc.size() << " " << arrayc.capacity() << std::endl;
    }
    std::cout << '\n';

}
void test_sortarray_push()
{
    SortedArray<int> *arraya = new SortedArray<int> (5);
    SortedArray<int> *arrayb = new SortedArray<int> (5);
    arraya->push(0);
    arraya->push(2);
    arraya->push(4);
    arraya->push(6);
    arraya->push(8);

    for (int i = 0; i<arraya->size(); i++) {
        std::cout << i << ": " << arraya->at(i) << " " << arraya->size() << " " << arraya->capacity() << std::endl;
    }
    std::cout << '\n';

    arrayb->push(1);
    arrayb->push(3);
    arrayb->push(5);
    arrayb->push(7);
    arrayb->push(9);


    for (int i = 0; i<arrayb->size(); i++) {
        std::cout << i << ": " << arrayb->at(i) << " " << arrayb->size() << " " << arrayb->capacity() << std::endl;
    }
    std::cout << '\n';

    delete arraya;
    delete arrayb;
}

void test_sortedarray_dell()
{
    Array<int> *parray = new SortedArray<int> (6);
    parray->push(5);

    for (int i = 0; i<parray->size(); i++) {
        std::cout << i << ": " << parray->at(i) << " " << parray->size() << " " << parray->capacity() << std::endl;
    }
    std::cout << '\n';

    parray->dell(2);
    for (int i = 0; i<parray->size(); i++) {
        std::cout << i << ": " << parray->at(i) << " " << parray->size() << " " << parray->capacity() << std::endl;
    }
    std::cout << '\n';

    std::cout << "************" << '\n';

    Array<int> *pparray = new Array<int> (5);
    pparray->push(1);
    pparray->push(2);
    pparray->push(3);
    pparray->push(4);
    pparray->push(5);


    for (int i = 0; i<pparray->size(); i++) {
        std::cout << i << ": " << pparray->at(i) << " " << pparray->size() << " " << pparray->capacity() << std::endl;
    }
    std::cout << '\n';
    pparray->at(2) = 5;

    for (int i = 0; i<pparray->size(); i++) {
        std::cout << i << ": " << pparray->at(i) << " " << pparray->size() << " " << pparray->capacity() << std::endl;
    }

    delete parray;
    delete pparray;
}

int main()
{
    //test_array_push();
    // test_sortarray_push();
    //test_sortedarray_dell();
    test_sortarray_merge();

    return 0 ;
}