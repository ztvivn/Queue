#include <iostream>

template<class Type>
struct Node;

template<class Type>
struct Queue
{
    Node<Type> *first = nullptr;//первый элемент
    Node<Type> *last = nullptr;//последний элемент

    void come(Type value);//поместить в очередь
    Type get();//получить из очереди
    ~Queue();
};

template<class Type>
struct Node
{
    Node<Type> *next = nullptr;//указатель на следующий элемент
    Node<Type> *prev = nullptr;//указатель на предыдущий элемент
    Type value;

    Node(Type value) : value(value) {}
};

template<class Type>
Queue<Type>::~Queue()
{
    while (first)
    {
        Node<Type> *node = first;
        first = first->next;
        delete  node;
    }
    
}

template<class Type>
void Queue<Type>::come(Type value)
{
    Node<Type> *node = new Node<Type>{value};

    if(first == nullptr)
    {
        last = first = node;
        return;
    }

    node->next = first;//указатель на след элем
    first->prev = node;//указатель на предыдущий элем
    first = node;//переставляем указатель на первый элемент
}

template<class Type>
Type Queue<Type>::get()
{
    if(first == nullptr)
    {
        throw std::out_of_range("Очередь пустая");
    }

    Type value = last->value;
    Node<Type> *node = last;

    if(last == first)//случай, когда остается один элемент
    {
        first = last = nullptr;
    }
    else
    {
        last = last->prev;
        last->next->prev = nullptr;
    }

    delete node;
    return value;
}

int main() 
{
    Queue<int> queue;

    queue.come(1);
    queue.come(45);
    queue.come(34);

    try
    {
        std::cout << queue.get() << " - " << queue.get() << " - "
                  << queue.get() << " - " << queue.get() << '\n';
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}