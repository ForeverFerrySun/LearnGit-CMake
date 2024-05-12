#include "avlF.h"

template <typename T>
T alg::AVL<T>::root() const
{
    return tree->value;
}

template <typename T>
unsigned int alg::AVL<T>::height() const
{
    return Node::getHeight(tree);
}

template <typename T>
unsigned int alg::AVL<T>::size() const
{
    return numNodes;
}

template <typename T>
bool alg::AVL<T>::isEmpty() const
{
    return numNodes == 0;
}

template <typename T>
bool alg::AVL<T>::contains(const T &x) const
{
    if (!isEmpty())
    {
        return tree->contains(x);
    }
    else
        return false;
}

template <typename T>
void alg::AVL<T>::insert(const T &x)
{
    if (isEmpty())
        tree = new Node(x);
    else
        tree = tree->insert(x);
    numNodes++;
}

template <typename T>
void alg::AVL<T>::erase(const T &x)
{
    if (!isEmpty())
    {
        bool found = false;
        tree = tree->erase(x, found);
        if (found)
            numNodes--;
    }
}

template <typename T>
void alg::AVL<T>::toGraphViz(std::ostream &stream, std::string name) const
{
    if (!isEmpty())
    {
        stream << "digraph " << name << " {" << std::endl;
        tree->toGraphViz(stream);
        stream << "}" << std::endl;
    }
}