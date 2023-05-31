// Experiment No. 8

#include <iostream>
using namespace std;
#define SIZE 10
class OBST
{
    int p[SIZE];       // Successful
    int q[SIZE];       // Unsuccessful
    int node[SIZE];    // Nodes
    int w[SIZE][SIZE]; // Weight
    int c[SIZE][SIZE]; // Cost
    int r[SIZE][SIZE]; // Root
    int n;

public:
    void get_data();
    int Min_Value(int i, int j);
    void calc_OBST();
    void build_tree();
};
void OBST::get_data()
{
    int i;
    cout << "\nOptimal Binary Search Tree Calculations\n";
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the data as…\n";
    for (i = 1; i <= n; i++)
    {
        cout << " node[" << i << "] = ";
        cin >> node[i];
    }
    cout << "Enter values of p(1:" << n << ")" << endl;
    for (i = 1; i <= n; i++)
    {
        cout << " p[" << i << "] = ";
        cin >> p[i];
    }
    cout << "Enter values of q(0:" << n << ")" << endl;
    for (i = 0; i <= n; i++)
    {
        cout << " q[" << i << "] = ";
        cin >> q[i];
    }
    cout << endl;
}
int OBST::Min_Value(int i, int j)
{
    int a, k;
    int minimum = 16000; // Any large arbitrary value
    for (a = i + 1; a <= j; a++)
    {
        if ((c[i][a - 1] + c[a][j]) < minimum)
        {
            minimum = c[i][a - 1] + c[a][j];
            k = a;
        }
    }
    return k;
}
void OBST::calc_OBST()
{
    int i, j, k, m;
    for (i = 0; i < n; i++)
    {
        // initialize
        w[i][i] = q[i];
        r[i][i] = c[i][i] = 0;
        // Optimal trees with one node
        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        r[i][i + 1] = i + 1;
        c[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
    }
    w[n][n] = q[n];
    r[n][n] = c[n][n] = 0;
    // Find optimal trees with ‘m’ nodes
    for (m = 2; m <= n; m++)
    {
        for (i = 0; i <= n - m; i++)
        {
            // increasing j based on the number of nodes to consider like 0->2(2nodes), 2->4(2
            j = i + m;
            // Calculation of w,c,r in the OBST matrix
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            k = Min_Value(i, j); // Value of 'a' for which c(i,a-1)+c(a,j)
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }
}
void OBST::build_tree()
{
    int i, j, k;
    // Max 20 elements assumed so queue is made of 20
    int queue[20], front = -1, rear = -1;
    cout << "The Optimal Binary Search Tree for the given node is ";
    // r[0][n] will be root since it be will the last OBST calc from 0->n(n nodes)
    cout << "\nThe Root of this OBST is -> " << r[0][n];
    // c[0][n] will be the final cost of that tree from 0->n
    cout << "\nThe Cost of this OBST is -> " << c[0][n];
    cout << "\n NODE \t LEFT CHILD \tRIGHT CHILD ";
    cout << "\n";
    queue[++rear] = 0;
    queue[++rear] = n;
    while (front != rear)
    {
        i = queue[++front]; // 0
        j = queue[++front]; // n
        k = r[i][j];        // Main root 1st time
        cout << "\n " << k; // Printing Node
        if (r[i][k - 1] != 0)
        {
            cout << "\t\t " << r[i][k - 1]; // Printing Left Child
            queue[++rear] = i;
            queue[++rear] = k - 1;
        }
        else
            cout << "\t\t"
                 << "[X]";
        if (r[k][j] != 0)
        {
            cout << "\t " << r[k][j]; // Printing Right Child
            queue[++rear] = k;
            queue[++rear] = j;
        }
        else
            cout << "\t"
                 << "[X]";
    } // end of while
    cout << "\n";
}
int main()
{
    OBST obj;
    obj.get_data();
    obj.calc_OBST();
    obj.build_tree();
    cout << "\n[X] indicates NULL/no child";
    return 0;
}

/*

Optimal Binary Search Tree Calculations
Enter the number of nodes: 4
Enter the data asΓÇª
 node[1] = 2
 node[2] = 5
 node[3] = 7
 node[4] = 1
Enter values of p(1:4)
 p[1] = 7
 p[2] = 2
[X] indicates NULL/no child

 */