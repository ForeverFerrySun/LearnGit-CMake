/*
 * @FilePath     : \LearnGit-CMake\avlF.h
 * @Date         : 2024-05-12 19:13:08
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-12 19:31:09
 * @LastEditors  : foreverferrysun
 * @FileDescription:
 */
/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _
 * /--\ | (_| (_) |  |  |_ | | | | | _>
 *         _|
 *
 * Adelson Velskii和Landis（AVL）树
 * 特征，N是树中元素的数量：
 * 1.保证搜索时间为O（log（N））。
 * 2.动态更新/平衡的树状结构O（N）存储。
 * 3.可导出为GraphViz格式，便于可视化和验证
 *
 * @author Alejandro Fernandez (alejandro.fernandez.suarez@gmail.com)
 * @github afernandez90
 *
 ******************************************************************************/

#ifndef ALGO_AVLF_H__
#define ALGO_AVLF_H__

#include <iostream>
#include <cmath>
#include <stack>
#include <algorithm>
#include <string>

namespace alg
{

    template <typename T>
    class AVL
    {

    public:
        AVL() : tree(0), numNodes(0) {}

        T root() const;
        unsigned height() const;
        unsigned size() const;
        bool isEmpty() const;

        bool contains(const T &x) const;
        ;
        void insert(const T &x);

        void erase(const T &x);

        void toGraphViz(std::ostream &stream, std::string name) const;

     public:

        struct Node {
            Node *left, *right;
            T value;
            unsigned height;

            Node(const T &x) : left(0), right(0), value(x), height(1) {}

            bool contains(const T &x) const {
                if (value == x) return true;
                else if (x < value && left != 0) return left->contains(x);
                else if (right != 0) return right->contains(x);
                else return false;
            }

            Node *insert(const T &x) {
                if (x <= value) {
                    if (left == 0) left = new Node(x);
                    else left = left->insert(x);
                }
                else {
                    if (right == 0) right = new Node(x);
                    else right = right->insert(x);
                }

                return update();
            }

            Node *erase(const T &x, bool &found) {
                if (value == x) {
                    found = true;
                    if (left == 0 && right == 0) {
                        delete this;
                        return 0;
                    } else if (left == 0) {
                        Node *aux = right;
                        *this = *right;
                        delete aux;
                    } else if (right == 0) {
                        Node *aux = left;
                        *this = *left;
                        delete aux;
                    } else {
                        // Tracing path to rightmost leaf of the left subtree
                        std::stack<Node*> trace;

                        Node *current = left;
                        while (current != 0) {
                            trace.push(current);
                            current = current->right;
                        }

                        current = trace.top();
                        value = current->value;
                        Node *lsubtree = current->left;
                        delete current;
                        trace.pop();

                        if (trace.empty()) { left = lsubtree; }
                        else {
                            trace.top()->right = lsubtree;
                            trace.pop();
                            while (!trace.empty()) {
                                current = trace.top();
                                current->right = current->right->update();
                                trace.pop();
                            }
                        }
                    }
                    return update();
                }
                else if (x < value) {
                    if (left != 0) {
                        left = left->erase(x, found);
                        return update();
                    } else return this;
                }
                else {
                    if (right != 0) {
                        right = right->erase(x, found);
                        return update();
                    } else return this;
                }
            }

            Node *update() {
                updateHeight();

                if (getBF(this) >= 2) {
                    if (getBF(left) <= -1) LR();
                    return LL();
                } else if (getBF(this) <= -2) {
                    if (getBF(right) >= 1) RL();
                    return RR();
                } else return this;
            }

            void updateHeight() { height = std::max(getHeight(left), getHeight(right)) + 1; }

            void LR() {
                Node *lrcopy = left->right;
                left->right = lrcopy->left;
                lrcopy->left = left;
                left = lrcopy;
                left->left->updateHeight();
                left->updateHeight();
                updateHeight();
            }

            void RL() {
                Node *rlcopy = right->left;
                right->left = rlcopy->right;
                rlcopy->right = right;
                right = rlcopy;
                right->right->updateHeight();
                right->updateHeight();
                updateHeight();
            }

            Node *LL() {
                Node *lcopy = left;
                left = left->right;
                lcopy->right = this;
                lcopy->left->updateHeight();
                lcopy->right->updateHeight();
                lcopy->updateHeight();
                return lcopy;
            }

            Node *RR() {
                Node *rcopy = right;
                right = right->left;
                rcopy->left = this;
                rcopy->left->updateHeight();
                rcopy->right->updateHeight();
                rcopy->updateHeight();
                return rcopy;
            }

            static int getBF(const Node *t) {
                return getHeight(t->left) - getHeight(t->right);
            }

            static int getHeight(const Node *t) {
                return t == 0 ? 0 : t->height;
            }

            void toGraphViz(std::ostream &stream) const {
                stream << value << ";" << std::endl;
                if (left != 0) {
                    stream << left->value << ";" << std::endl;
                    stream << value << "->" << left->value << ";" << std::endl;
                    left->toGraphViz(stream);
                }
                if (right != 0) {
                    stream << right->value << ";" << std::endl;
                    stream << value << "->" << right->value << ";" << std::endl;
                    right->toGraphViz(stream);
                }
            }
        };

        Node *tree;
        unsigned numNodes;
};

}
#endif // _ALG_AVLF_HPP
