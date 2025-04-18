
template <typename E>

struct Node{
    E e;
    std::vector Node<E> children;
};

template <typename e> 

struct Tree<E e>{
    Node<E> root; 
};