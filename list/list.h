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



#endif