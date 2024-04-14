#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Tree
{
    string info;
    int key;
    Tree* left, * right;
} *root;

vector<pair<int, string>> keys;
 
void List(int key, Tree** p, string info)
{
    Tree* t = new Tree; 
    t->key = key; 
    t->info = info;
    t->left = t->right = NULL; 
    *p = t; 
    keys.push_back({key, info});
}

void Add_List(Tree* root, int key, string info)
{
    Tree* prev = NULL, * t = NULL; 
    bool find = true;
    t = root;
    while (t && find)
    {
        prev = t;
        if (key == t->key) {
            find = false; 
            cout << "Повторяющийся ключ!";
        }
        else
            if (key < t->key)
                t = t->left;
            else
                t = t->right;
    }
    if (find)
    { 
        List(key, &t, info); 
        if (key < prev->key)
            prev->left = t;
        else
            prev->right = t;
    }
}

void View_Tree(Tree* p, int level)
{
    string str;
    if (p)
    {
        View_Tree(p->right, level + 1); 
        for (int i = 0; i < level; i++)
            str = str + "  ";


   
        cout << endl << str + to_string(p->key);

        View_Tree(p->left, level + 1); 
    }
}


void Del_Tree(Tree* t)
{
    if (t != NULL)
    {
        Del_Tree(t->left); 
        Del_Tree(t->right); 
        delete t;
    }
}

void Make_Blns(Tree** p, int n, int k, vector<pair<int, string>> a) {
    if (n == k)
    {
        *p = NULL;
        return;
    }
    else 
    {
        int m = (n + k) / 2;
        *p = new Tree;
        (*p)->key = a[m].first;
        (*p)->info = a[m].second;
        Make_Blns(&(*p)->left, n, m, a);
        Make_Blns(&(*p)->right, m + 1, k, a);
    }
}

void swap(int i, int j, vector<pair<int, string>>*arr)
{
    pair<int,string> buff = (*arr)[i];
    (*arr)[i] = (*arr)[j];
    (*arr)[j] = buff;
}

void Sort(vector<pair<int,string>> *arr)
{
    if (arr->size() == 0)
    {
        return;
    }

    for (int i = 0; i < ((*arr).size() - 1); i++)
    {
        for(int j = i + 1; j < ((*arr).size()); j++)
        {
            if ((*arr)[i] > (*arr)[j])
            {
                swap(i, j, arr);
            }
        }
    }
}

void FindKey(Tree* root, int key)
{
    Tree* prev = NULL, * t = NULL;
    bool find = true;
    t = root;
    while (t && find)
    {
        prev = t;
        if (key == t->key) 
        {
            cout << t->info << endl;
            return;
        }
        else
            if (key < t->key)
                t = t->left;
            else
                t = t->right;
    }
    if (t == NULL)
        cout << "Ключ не найден" << endl;
}

Tree* Del_Info(Tree* root, int key) {
    Tree* Del, * Prev_Del, * R, * Prev_R;
    Del = root;
    Prev_Del = NULL;
    
    while (Del != NULL && Del->key != key)
    {
        Prev_Del = Del;
        if (Del->key > key) Del = Del->left;
        else Del = Del->right;
    }
    if (Del == NULL) 
    { 
        cout << "Ключ не найден" << endl;
        return root;
    }
    if (Del->right == NULL) R = Del->left;
    else if (Del->left == NULL) R = Del->right;
    else
    {
        
        Prev_R = Del;
        R = Del->left;
        while (R->right != NULL) 
        {
            Prev_R = R;
            R = R->right;
        }
     
        if (Prev_R == Del) 
            R->right = Del->right;
        else {
            R->right = Del->right;
            Prev_R->right = R->left;
            R->left = Del->left;
        }
    }
    if (Del == root) 
        root = R; 
    else
        if (Del->key < Prev_Del->key)
            Prev_Del->left = R; 
        else 
            Prev_Del->right = R; 
    delete Del;
    return root;
}

void PrintTree(Tree* root, int way)
{
    static Tree* checkedNode;
    if (way == 1)
    {
        while (root != NULL && root != checkedNode)
        {
            cout << root->info << " ";
            PrintTree(root->left, 1);
            PrintTree(root->right, 1);
            checkedNode = root;
        } 
    }
    if (way == 2)
    {
        while (root != NULL && root != checkedNode)
        {
            PrintTree(root->left, 2);
            PrintTree(root->right, 2);
            cout << root->info << " ";
            checkedNode = root;
        }
    }
    if (way == 3)
    {
        while (root != NULL && root != checkedNode)
        {
            PrintTree(root->left, 3);
            cout << root->info << " ";
            PrintTree(root->right, 3);
            checkedNode = root;
        }
    }
    checkedNode = NULL;
}


int CountChars(Tree* node)
{
    static int amount = 0;
    static Tree* checkedNode;
    int number = 0;

    while (node != NULL && node != checkedNode)
    {
        CountChars(node->left);
        CountChars(node->right);
        amount += node->info.size();
        checkedNode = node;
    }
    checkedNode = NULL;
    if (node == root)
    {
        number = amount;
        amount = 0;
    }
    return number;
}


int main()
{
    setlocale(LC_ALL, "RU");
    
    int num, key;
    string info;
    
    while (true)
    {
        cout << "\nДобавить элемент в дерево - 1.\nПросмотреть дерево - 2.\nУдалить дерево - 3.\nСбалансировать дерево - 4. \nНайти и вывести значение по ключу - 5. \nУдалить узел по ключу - 6. \nВывести информацию дерева одним из обходов  - 7. \nПосчитать количество символов во всех строках дерева - 8. \nВыход - 0.\n";

        cin >> num;
        
        switch (num)
        {
        case 1:
            cout << endl << "Введите значение ключа: ";
            cin >> key;
            cout << endl << "Введите значение листа: ";
            cin >> info;
            if (root == NULL)
            {
                List(key, &root, info);
            }
            else
            {
                Add_List(root, key, info);
            }
            break;
        case 2:
            cout << "------Дерево------";
            View_Tree(root, 0);
            cout << endl;
            break;
        case 3:
            Del_Tree(root);
            keys.clear();
            root = nullptr;
            cout << endl << "Дерево удалено!" << endl;
            break;
        case 4:
            Sort(&keys);
            if(keys.size() == 0)
            {
                cout << "Дерево пустое!" << endl;
                break;
            }
            Make_Blns(&root, 0, keys.size(), keys);
            cout << endl << "Дерево сбалансировано!" << endl;
            break;
        case 5:
            cout << endl << "Введите значение ключа: ";
            cin >> key;
            FindKey(root, key);
            break;
        case 6:
            cout << endl << "Введите значение ключа: ";
            cin >> key;
            root = Del_Info(root, key);
            break;
        case 7:
            if (keys.size() == 0)
            {
                cout << "Дерево пустое!" << endl;
                break;
            }
            int way;
            cout << "\n Каким образом вывести дерево: \n1 - Прямым обходом \n2 - Обратным обходом \n3 - В порядке возрастания ключа \n";
            cin >> way;
            PrintTree(root, way);
            break;
        case 8:
            cout << "Количество символов : " << CountChars(root) << endl;
            break;
        default:
            Del_Tree(root);
            root = nullptr;
            return 0;
        }
    }
}

