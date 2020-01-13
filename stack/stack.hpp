#ifndef __STACK__
#define __STACK__

#include "../array/array.hpp"
#include "../list/list.hpp"

template <typename T>
class Stack {
public:
    Stack() {}
    virtual ~Stack() {}

    virtual void pop() = 0;
    virtual T& top() = 0;
    virtual const T & top() const = 0;
    virtual void push(const T &data) = 0;
    virtual int size() const = 0;
    virtual int capacity() const = 0;
    virtual void show() const = 0;
protected:
    virtual bool is_empty() const =0;
};

template <typename T>
class ArrayStack : public Stack<T> {
public:
    ArrayStack() : Stack<T>() {
        _capacity = 10;
        _data = new Array<T> (_capacity, false);
    }
     
    ArrayStack(size_t n) :
        _capacity(n),
        Stack<T>() {
        _data = new Array<T> (_capacity, false);
    }

    ~ArrayStack() {
        delete _data;
    }

    virtual void pop();
    virtual T& top();
    virtual const T & top() const;
    virtual void push(const T &data);
    virtual int size() const {return _size;}
    virtual int capacity() const {return _capacity;}
    virtual void show() const;

private:
    Array<T> *_data;
    size_t _capacity = 0;
    size_t _size = 0;
    bool is_empty() const {return _size == 0;}
};

template <typename T>
class LinkedStack : public Stack<T> {
public:
    LinkedStack() : Stack<T>() {
        _data = new SingleList<T> ();
    }

    ~LinkedStack() {
        delete _data;
    }

    virtual void pop();
    virtual T& top();
    virtual const T & top() const;
    virtual void push(const T &data);
    virtual int size() const {return _size;}
    virtual void show() const;

private:
    SingleList<T> *_data;
    size_t _size = 0;
    bool is_empty() const {return _size == 0;}
    int capacity() const {}
};

/**** ArrayStack ****/
template <typename T>
void ArrayStack<T>::pop()
{
    if (!is_empty()) {
        _size--;
    }
}

template <typename T>
T & ArrayStack<T>::top()
{
    if (!is_empty()) {
        return _data->at(_size-1);
    }
}

template <typename T>
const T & ArrayStack<T>::top() const
{
    if (!is_empty()) {
        return _data->at(_size-1);
    }
}

template <typename T>
void ArrayStack<T>::push(const T &data)
{
    if (_size < _capacity) {
        _data->push(data);
        _size++;
    } else {
        Array<T> *temp_data = new Array<T>[2*_capacity];
        memcpy(temp_data, _data, _size*sizeof(_data[0]));
        delete[] _data;
        _data = temp_data;
        _capacity *=2;

        _data->push(data);
        _size++;
    }
}

template <typename T>
void ArrayStack<T>::show() const
{
    if (!is_empty()) {
        for (int i=0; i< size(); i++)
            cout << "(" << i+1 << "/" << size() << "): " << _data->at(i) <<endl;
    }
    cout << endl;
}

/**** LinkedStack ****/
template <typename T>
void LinkedStack<T>::pop()
{
    if (!is_empty()) {
        _data->pop_back();
        _size--;
    }
}

template <typename T>
T & LinkedStack<T>::top()
{
    if (!is_empty()) {
        return _data->back();
    }
}

template <typename T>
const T & LinkedStack<T>::top() const
{
    if (!is_empty()) {
        return _data->back();
    }
}

template <typename T>
void LinkedStack<T>::push(const T &data)
{
    _data->push_back(data);
    _size++;
}

template <typename T>
void LinkedStack<T>::show() const
{
    if (!is_empty()) {
        _data->show();
    }
}

#endif