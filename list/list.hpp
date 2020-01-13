#ifndef __LIST__
#define __LIST__

template <typename T>
class ListNode {
public:
    T _val;
    ListNode *_prev = nullptr;
    ListNode *_next = nullptr;
};

template <typename T>
class LinkedList {
public:
    LinkedList() {}
    virtual ~LinkedList() {}

    virtual bool is_empty() const = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual void push_front(const T &data) = 0;
    virtual void push_back(const T &data) = 0;
    virtual size_t size() const = 0;
    virtual T & front() = 0;
    virtual const T & front() const = 0;
    virtual T & back() = 0;
    virtual const T & back() const = 0;
    virtual void show() const = 0;
};

template <typename T>
class SingleList : public LinkedList<T>{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    SingleList() {
        _head = new ListNode<value_type>();
        _count = 0;
    }

    ~SingleList() {
        if (!is_empty()) {
            pop_back();
        }
        delete _head;
        _head = nullptr;
        _count = 0;
    }

    bool is_empty() const override;
    void pop_front() override;
    void pop_back() override;
    void push_front(const value_type &data) override;
    void push_back(const value_type &data) override;
    size_t size() const override;
    reference front() override;
    const_reference front() const override;
    reference back() override;
    const_reference back() const override;
    virtual void show() const override;


protected:
    ListNode<T> *_head = nullptr;
    ListNode<T> *_tail = nullptr;
    size_t _count = 0;


    ListNode<value_type>* & find_end_prev()
    {
        if (!is_empty()) {
            ListNode<value_type> *p = _head;
            while (p->_next->_next != nullptr) {
                p = p->_next;
            }
            return p;
        }
    }

    ListNode<value_type>* & find_end()
    {
        ListNode<value_type> *p = _head;
        while (p->_next != nullptr) {
            p = p->_next;
        }
        return p;
    }
};


template <typename T>
class SingleCycleList : public SingleList<T> {
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    SingleCycleList() : SingleList<T>() {
        SingleList<T>::_head->_next = SingleList<T>::_head;
    }

    ~SingleCycleList()
    {
        if (!SingleList<T>::is_empty()) {
            pop_back();
        }
        delete SingleList<T>::_head;
        SingleList<T>::_head = nullptr;
        SingleList<T>::_count = 0;
    }

    void push_back(const value_type &data) override;
    void pop_back() override;
    reference back() override;
    const_reference back() const override;
    void show() const override;

private:
    ListNode<value_type>* & find_end_prev()
    {
        if (!SingleList<T>::is_empty()) {
            ListNode<value_type> *p = SingleList<T>::_head;
            while (p->_next->_next != SingleList<T>::_head) {
                p = p->_next;
            }
            return p;
        }
    }

    ListNode<value_type>* & find_end()
    {
        ListNode<value_type> *p = SingleList<T>::_head;
        while (p->_next != SingleList<T>::_head) {
            p = p->_next;
        }
        return p;
    }
};


template <typename T>
class DoublyList : public LinkedList<T>{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    DoublyList() {
        _head = new ListNode<value_type>();
        _tail = _head;
        _count = 0;
    }

    ~DoublyList() {
        if (!is_empty()) {
            pop_back();
        }
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count = 0;
    }

    bool is_empty() const override;
    void pop_front() override;
    void pop_back() override;
    void push_front(const value_type &data) override;
    void push_back(const value_type &data) override;
    size_t size() const override;
    reference front() override;
    const_reference front() const override;
    reference back() override;
    const_reference back() const override;
    virtual void show() const override;


protected:
    ListNode<T> *_head = nullptr;
    ListNode<T> *_tail = nullptr;
    size_t _count = 0;
};

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



#endif