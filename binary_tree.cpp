//Tasks A-H. I and J not solved.

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class tree_elem {
public:
    int m_data;  //число, которое хранится в этой вершине
    tree_elem* m_left;  //указатель на левого потомка данной вершины
    tree_elem* m_right;  //указатель на правого потомка данной вершины
    int balance;  //баланс вершины
    int freq;  //частота встречи в последовательности

    //констурктор класса записывает в вершину полученное число, а потомки инициализирует нуль-указателями
    tree_elem(int val) {
        m_data = val;
        m_left = nullptr;
        m_right = nullptr;
        balance = 0;
        freq = 1;
    }
};


class binary_tree {
private:
    tree_elem* m_root;  //указатель на корень дерева
    int m_size;  //количество элементов в дереве
    int m_height;  //высота дерева

    //рекурсивная процедура для метода print(): сначала зайдём в левое, а затем в правое поддерево
    void print_tree(tree_elem* curr) {
        //проверка на ненулевой указатель
        if (curr) {
            print_tree(curr->m_left);
            cout << curr->m_data << " ";
            print_tree(curr->m_right);
        }
    }

    //рекурсивная процедура для деструктора, удаляющая элементы левого и правого поддерева, а затем и сам элемент
    void delete_tree(tree_elem* curr) {
        if (curr) {
            delete_tree(curr->m_left);
            delete_tree(curr->m_right);
            delete curr;
        }
    }

    //рекурсивная процедура для поиска высоты заданной вершины
    int search_height(tree_elem* curr) {
        if (curr == nullptr) {
            return 0;
        }
        int lefth = search_height(curr->m_left);
        int righth = search_height(curr->m_right);
        if (lefth > righth) {
            return lefth + 1;
        }
        else {
            return righth + 1;
        }
    }

    //рекурсивная процедура для вывода всех листьев дерева
    void search_tree_leaves(tree_elem* curr) {
        if (curr) {
            if (curr->m_left == nullptr and curr->m_right == nullptr) {
                cout << curr->m_data << " ";
            }
            search_tree_leaves(curr->m_left);
            search_tree_leaves(curr->m_right);
        }
    }

    //рекурсивная процедура для вывода всех вершин дерева, имеющих по два предка
    void search_tree_forks(tree_elem* curr) {
        if (curr) {
            search_tree_forks(curr->m_left);
            if (curr->m_left != nullptr and curr->m_right != nullptr) {
                cout << curr->m_data << " ";
            }
            search_tree_forks(curr->m_right);
        }
    }

    //рекурсивная процедура для вывода всех вершин дерева, имеющих по одному предку
    void search_tree_branches(tree_elem* curr) {
        if (curr) {
            search_tree_branches(curr->m_left);
            if (curr->m_left == nullptr and curr->m_right != nullptr) {
                cout << curr->m_data << " ";
            }
            if (curr->m_left != nullptr and curr->m_right == nullptr) {
                cout << curr->m_data << " ";
            }
            search_tree_branches(curr->m_right);
        }
    }

    //рекурсивная процедура обхода поддеревьев для сравнения их высоты
    int avl_traversal(tree_elem* curr) {
        if (curr == nullptr)
            return 1;
        int lh = avl_traversal(curr->m_left);
        int rh = avl_traversal(curr->m_right);
        if (lh == 0 or rh == 0 or abs(lh - rh) > 1)
            return 0;
        else
            return std::max(lh, rh) + 1;
    }

    //рекурсивная процедура обхода дерева для вывода элемента и его частоты в последовательности
    void frequency_traversal(tree_elem* curr) {
        if (curr) {
            frequency_traversal(curr->m_left);
            cout << curr->m_data << " " << curr->freq << endl;
            frequency_traversal(curr->m_right);
        }
    }

    //рекурсивная процедура поиска высоты элемента
    int get_size(tree_elem* curr) {
        int size = 1;
        if (curr->m_left != 0) {
            size += get_size(curr->m_left);
        }
        if (curr->m_right != 0) {
            size += get_size(curr->m_right);
        }
        return size;
    }

    //рекурсивная процедура поиска максимума в дереве
    int first_max(tree_elem* curr) {
        if (curr->m_right == 0) {
            return curr->m_data;
        }
        return first_max(curr->m_right);
    }

    //рекурсивная процедура поиска второго максимума в дереве
    int second_max(tree_elem* curr) {
        if (curr->m_right == 0) {
            return first_max(curr->m_left);
        }
        int x = get_size(curr->m_right);
        if (x == 1) {
            return curr->m_data;
        }
        return second_max(curr->m_right);
    }

public:
    //конструктор; для корректной работы в дереве всегда должен быть хотя бы один элемент
    binary_tree(int key) {
        m_root = new tree_elem(key);
        m_size = 1;
        m_height = 1;
    }

    //деструктор
    ~binary_tree() {
        delete_tree(m_root);
    }

    //метод рекурсивно обходит всё дерево и выводит все его элементы в порядке возрастания
    void print() {
        print_tree(m_root);
        cout << endl;
    }

    //метод проверяет, содержится ли в дереве элемент со значением key; поиск идёт от корня
    bool find(int key) {
        tree_elem* curr = m_root;
        while (curr and curr->m_data != key) {
            if (curr->m_data > key) 
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }
        return curr != nullptr;
    }

    //метод добавления элемента в дерево
    void insert(int key) {
        tree_elem* curr = m_root;
        if (curr->m_data == key) {
            curr->freq += 1;
        }
        while (curr and curr->m_data != key) {
            if (curr->m_data > key and curr->m_left == nullptr) {
                curr->m_left = new tree_elem(key);
                ++m_size;
                return;
            }
            if (curr->m_data < key and curr->m_right == nullptr) {
                curr->m_right = new tree_elem(key);
                ++m_size;
                return;
            }
            if (curr->m_data > key) {
                curr = curr->m_left;
            }
            else {
                curr = curr->m_right;
            }
            if (curr->m_data == key) {
                curr->freq += 1;
            }
        }
    }

    //поиск высоты дерева
    int height() {
        return search_height(m_root);
    }

    //вывод всех листов дерева
    void tree_leaves() {
        search_tree_leaves(m_root);
        cout << endl;
    }

    //вывод всех вершин дерева, имеющих по два предка
    void tree_forks() {
        search_tree_forks(m_root);
        cout << endl;
    }

    //вывод всех вершин дерева, имеющих по одному предку
    void tree_branches() {
        search_tree_branches(m_root);
        cout << endl;
    }

    //проверка дерева на АВЛ-сбланасированность
    bool avl_balance() {
        return avl_traversal(m_root);
    }

    //частота элемента в последовательности, которую вводят для построения бинарного дерева
    void frequency_elem_in_array() {
        frequency_traversal(m_root);
    }

    //поиск максимального элемента в дереве
    int max() {
        return first_max(m_root);
    }

    //поиск второго максимума в дереве
    int s_max() {
        return second_max(m_root);
    }
};


int main() {
    return 0;
}