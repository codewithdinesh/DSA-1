/*

Assignment 3
Title: Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given.

i) Insert new node,
ii) Findnumber of nodes in longest path from root,
iii) Minimum data value found in the tree,
iv) Change a tree so that the roles of the left and right pointers are swapped at every node,
v) Search a value
*/

#include <iostream>
#define size 20
using namespace std;

class binarytree
{
    typedef struct bst
    {
        int data;
        struct bst *left, *right;
    } node;
    node *root, *New, *temp, *parent;

public:
    node *queue[20];
    int front, rear;

    binarytree()
    {
        root = NULL;
        front = rear = -1;
    }
    void create();
    void display();
    void find();
    void insert(node *, node *);
    void inorder(node *);
    // void search(node *, int, node *);
    void long_path_node();
    int depth(node *);
    void find_min_val();
    void min_val(node *, int *);
    void mirroring();
    void mirror(node *);
    void level_wise_display(node *root);
    void enque(node *temp);
    node *deque();
    void search(node *&temp, int item, node *&parent)
    {
        while (temp != NULL && temp->data != item)
        {
            parent = temp;
            if (item < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }
};

void binarytree::create()
{

    New = new node;
    New->left = NULL;
    New->right = NULL;
    cout << "\n Enter the element" << endl;
    cin >> New->data;
    if (root == NULL)
        root = New;

    else
        insert(root, New);
}

void binarytree::insert(node *root, node *New)
{
    if (New->data < root->data)
    {
        if (root->left == NULL)
            root->left = New;
        else
            insert(root->left, New);
    }
    if (New->data > root->data)
    {
        if (root->right == NULL)
            root->right = New;
        else

            insert(root->right, New);
    }
}

void binarytree::display()
{

    if (root == NULL)
        cout << "\n The tree is not created";
    else
    {
        cout << "\n The tree is inorder : ";
        inorder(root);
    }
}
void binarytree::inorder(node *temp)
{
    if (temp != NULL)
    {
        inorder(temp->left);
        cout << " " << temp->data;
        inorder(temp->right);
    }
}

void binarytree::find_min_val()
{
    int min = root->data;
    min_val(root, &min);
    cout << "\n The minimum value node within a tree is" << min;
}

void binarytree::min_val(node *temp, int *min)
{
    if (temp != NULL)
    {
        min_val(temp->left, min);
        if (temp->data < *min)

            *min = temp->data;
        min_val(temp->right, min);
    }
}
void binarytree::find()
{
    int key;
    cout << "\n Enter the Elements that you want to search" << endl;
    cin >> key;
    temp = root;
    search(temp, key, parent);
    if (temp == NULL)
        cout << "\n The elements are not present" << endl;
    else
        cout << "\n Parent of node " << temp->data << "is" << parent->data;
}

void binarytree::long_path_node()
{
    if (root == NULL)
        cout << "\n The tree is empty!!!!" << endl;
    else
    {

        int ldepth = depth(root);
        int rdepth = depth(root);

        if (ldepth > rdepth)
        {

            cout << "\n the number of nodes in the longest path = " << ldepth + 1;
        }
        else
        {
            cout << "\n The number of nodes in the longest path = " << rdepth + 1;
        }
    }
}

int binarytree::depth(node *root)
{
    if (root == NULL)
        return 0;
    else
    {

        int ldepth = depth(root->left);
        int rdepth = depth(root->right);

        if (ldepth > rdepth)
            return ldepth;
        else
            return (rdepth + 1);
    }
}

void binarytree::enque(node *temp)
{
    if (rear == size - 1)
    {
        cout << "\n the queue is empty" << endl;
        return;
    }

    rear = rear + 1;
    queue[rear] = temp;
}

binarytree::node *binarytree::deque()
{
    node *temp;
    if (front == rear)
    {
        cout << "Queue is empty";
        return NULL;
    }
    front++;
    temp = queue[front];
    return temp;
}

void binarytree::level_wise_display(node *root)
{
    node *temp, *dummy;
    dummy = new node;
    front = rear = -1;

    if (dummy == NULL)
        cout << "\n Insufficient memory\n";
    dummy->left = root;
    dummy->right = NULL;
    dummy->data = -999;
    temp = dummy->left;
    enque(temp);
    enque(dummy);
    temp = deque();

    cout << "\n";
    while (front != rear)
    {
        if (temp != dummy)
        {
            cout << " " << temp->data;
            if (temp->left != NULL)
                enque(temp->left);
            if (temp->right != NULL)
                enque(temp->right);
        }
        else
        {
            enque(temp);
            cout << "\n"
                 << endl;
        }
        temp = deque();
    }
}

void binarytree::mirroring()
{
    cout << "\n Original Tree";
    level_wise_display(root);
    mirror(root);
    cout << "\n the tree with swapped nodes";
    level_wise_display(root);
    mirror(root);
}

void binarytree::mirror(node *root)
{
    node *temp_node;
    if (root != NULL)
    {
        mirror(root->left);
        mirror(root->right);
        temp_node = root->left;
        root->left = root->right;
        root->right = temp_node;
    }
}

int main()
{
    int choice;
    char ans = 'N';
    binarytree tr;
    cout << "\n\t Program For Binary Search tree" << endl;
    do
    {

        cout << "\n1.Create";
        cout << "\n2.Display";
        cout << "\n3.Longest Path Nodes";
        cout << "\n4.Find Minimum Value";
        cout << "\n5.Change tree by swapping nodes:";
        cout << "\n6.Search";
        cout << "\n\n Enter your choice:";
        cin >> choice;
        switch (choice)
        {

        case 1:
            do
            {
                tr.create();
                cout << " Do you want to enter more elements?(y/n)" << endl;
                cin >> ans;
            } while (ans == 'y');
            break;
        case 2:
            tr.display();
            break;
        case 3:
            tr.long_path_node();
            break;
        case 4:
            tr.find_min_val();
            break;
        case 5:
            tr.mirroring();
            break;

        case 6:
            tr.find();
            break;
        }

    } while (choice != 7);
    return 0;
}
/*
OUTPUT:

         Program For Binary Search tree

1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:1

 Enter the element
2
 Do you want to enter more elements?(y/n)
y

 Enter the element
4
 Do you want to enter more elements?(y/n)
y

 Enter the element
1
 Do you want to enter more elements?(y/n)
y

 Enter the element
10
 Do you want to enter more elements?(y/n)
y

 Enter the element
0
 Do you want to enter more elements?(y/n)
y

 Enter the element
5
 Do you want to enter more elements?(y/n)
n

1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:2

 The tree is inorder :  0 1 2 4 5 10
1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:3

 The number of nodes in the longest path = 4
1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:4

 The minimum value node within a tree is0
1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:5

 Original Tree
 2

 1 4

 0 10

 5
 the tree with swapped nodes
 2

 4 1

 10 0

 5
1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:2

 The tree is inorder :  0 1 2 4 5 10
1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:6

 Enter the Elements that you want to search
5

 Parent of node 5is10
1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:6

 Enter the Elements that you want to search
99

 The elements are not present

1.Create
2.Display
3.Longest Path Nodes
4.Find Minimum Value
5.Change tree by swapping nodes:
6.Search

 Enter your choice:

*/