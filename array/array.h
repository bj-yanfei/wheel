#ifndef __ARRAY__
#define __ARRAY__

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class Array {
public:
    typedef T value_type;
    typedef value_type& reference ;
    typedef const value_type& const_reference;

    Array(bool can_expansion=false) : _can_expansion(can_expansion) {
        _data = new value_type[_capacity];
        if (_data)
            memset(_data, 0, _capacity*sizeof(value_type));
        else
           _capacity = 0;
    }
    Array(int n, bool can_expansion=false) :
    _capacity(n),
    _can_expansion(can_expansion) {
        _data = new value_type[_capacity];
        if (_data)
            memset(_data, 0, _capacity*sizeof(value_type));
        else
           _capacity = 0;
    }
    ~Array() {
        if (_data) delete[] _data;
    }

    size_t capacity() {return _capacity;}
    size_t size() {return _size;}

    virtual void push(const_reference data);
    void push(const_reference data, const size_t pos);

    void erase();
    virtual void dell(const_reference data);
    void dell(const size_t pos);

    reference at(const size_t pos);
    const_reference at(const size_t pos) const;

    virtual size_t where(const_reference data);

private:
    bool _can_expansion = false;

    bool expansion() {
        if (_capacity == 0) {
            value_type *data = new value_type[1];
            if (!data) {
                return false;
            }

            delete[] _data;
            _data = data;
            _capacity = 1;
        } else {
            value_type *data = new value_type[2*_capacity];
            if (data) {
                memset(data, 0, 2*_capacity*sizeof(value_type));
            } else {
                return false;
            }

            memcpy(data, _data, _capacity*sizeof(value_type));
            delete[] _data;
            _data = data;
            _capacity = _capacity*2;
        }
        return true;
    }

protected:
    value_type *_data = nullptr;
    size_t _capacity = 0;
    size_t _size = 0;
    bool is_empty() {return _size == 0;}
    bool is_full() {
        return _size >= _capacity;
    }

};

template <typename T>
void Array<T>::push(const_reference data)
{
    if (!is_full()) {
        _data[_size] = data;
        _size++;
    } else {
        if (!_can_expansion)
            return;
        else {
            if (expansion()) {
                _data[_size] = data;
                _size++;
            } else
                return;
        }
    }
}

template <typename T>
void Array<T>::push(const_reference data, const size_t pos)
{
    if ((pos > _size) || (pos < 0)) {
        return;
    } else if (pos == _size) {
        push(data);
    } else if (pos >= 0) {
        if (!is_full()) {
            for (size_t i = _size; i > pos; i--) {
                _data[i] = _data[i-1];
            }
            _data[pos] = data;
            _size++;
        } else {
            if (_can_expansion) {
                if (expansion()) {
                    for (size_t i = _size; i > pos; i--) {
                        _data[i] = _data[i-1];
                    }
                    _data[pos] = data;
                    _size++;
                } else {
                    return;
                }
            } else {
                return;
            }
        }
    }
}

template <typename T>
void Array<T>::erase()
{
    if (_data) {
        _size = 0;
    } else {
        return;
    }
}

template <typename T>
void Array<T>::dell(const_reference data)
{
    size_t pos[_size+1];
    size_t pos_index = 1;
    memset(&pos, 0, (_size+1)*sizeof(size_t));
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == data) {
            pos[0] ++;
            pos[pos_index] = i;
            pos_index ++;
        }
    }

    if (pos[0] != 0) {
        while(pos[0]) {
            if (pos[pos[0]] == _size-1) {
                _size--;
            } else {
                for (size_t j = pos[pos[0]]; j < _size-1; j++) {
                    _data[j] = _data[j+1];
                }
                _size --;
            }
            pos[0]--;
        }
    }
}

template <typename T>
void Array<T>::dell(const size_t pos)
{
    if ((pos > _size) || (pos < 0)) {
        return;
    } else if (pos == _size) {
        _size--;
    } else if (pos >= 0) {
        for (size_t i = pos; i < _size-1; i++) {
            _data[i] = _data[i+1];
        }
        _size --;
    }
}

template <typename T>
typename Array<T>::reference Array<T>::at(const size_t pos)
{
    if ((pos < _size) && (pos >=0)) {
        return _data[pos];
    }
}

template <typename T>
typename Array<T>::const_reference Array<T>::at(const size_t pos) const
{
    if ((pos < _size) && (pos >=0)) {
        return _data[pos];
    }
}

template <typename T>
size_t Array<T>::where(const_reference data){}

template <typename T>
class SortedArray : public Array<T> {
public:
    typedef T value_type;
    typedef value_type& reference ;
    typedef const value_type& const_reference;

    SortedArray(int n) : Array<T>(n) {}
    ~SortedArray() {}

    void push(const_reference data);
    void dell(const_reference data);

private:
    size_t search(const_reference value)
    {
        int low = 0;
        int high = Array<T>::_size-1;
        value_type *data = Array<T>::_data;

        while (low <= high) {
            int mid = low + (high-low)/2;

            if (low == high) {
                if (data[mid] > value) return mid;
                if (data[mid] < value) return mid+1;
            }

            if (data[mid] > value) {
                high = mid - 1;
            } else if (data[mid] < value) {
                low = mid + 1;
            } else {
                if ((mid == Array<T>::_size-1) || (data[mid+1] != value)) return mid+1;
                else low = mid + 1;
            }
        }
        if (low > high) return low;
    }
};

template <typename T>
void SortedArray<T>::push(const_reference data)
{
    if (!Array<T>::is_full()) {
        size_t pos = search(data);

        for (size_t i = Array<T>::_size; i > pos; i--) {
            Array<T>::_data[i] = Array<T>::_data[i-1];
        }
        Array<T>::_data[pos] = data;
        Array<T>::_size++;
    } else {
        return;
    }
}

template <typename T>
void SortedArray<T>::dell(const_reference data)
{
    if (Array<T>::is_empty()) return;

    size_t pos = search(data);
    if (pos <=0) {
        if (Array<T>::_data[0] == data) {
            for (size_t i = 0; i < Array<T>::_size-1; i++) {
                Array<T>::_data[i] = Array<T>::_data[i+1];
            }
            Array<T>::_size --;
            return;
        } else return;
    } else if (pos >= Array<T>::_size) {
        if (Array<T>::_data[Array<T>::_size-1] == data) {
            Array<T>::_size --;
        }
        return;
    } else {
        if (Array<T>::_data[pos-1] != data) return;
        for (size_t i = pos; i < Array<T>::_size; i++) {
            Array<T>::_data[i-1] = Array<T>::_data[i];
        }
        Array<T>::_size --;
        return dell(data);
    }
}

template <typename T>
void merge (Array<T>& ret, SortedArray<T>& A, SortedArray<T>& B)
{
    if (ret.capacity() < (A.size()+B.size())) return;

    size_t A_i = 0, B_i = 0, ret_i = 0;
    size_t A_i_e = A.size()-1, B_i_e = B.size()-1;

    while ((A_i <= A_i_e) && (B_i <= B_i_e)) {
        if (A.at(A_i) <= B.at(B_i)) {
            ret.push(A.at(A_i++), ret_i++);
        } else {
            ret.push(B.at(B_i++), ret_i++);
        }
    }

    while (A_i <= A_i_e) {
        ret.push(A.at(A_i++), ret_i++);
    }

    while (B_i <= B_i_e) {
        ret.push(B.at(B_i++), ret_i++);
    }
    return;
}

#endif