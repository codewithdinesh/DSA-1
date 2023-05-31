/***********************************************************************
Program for implementing Direct Access File using the hashing technique.
Collision handling is performed using linear probing and
chaining without replacement.
[hash function=(record_id mod 10)]
************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;

class EMP_CLASS
{
    typedef struct EMPLOYEE
    {
        char name[10];
        int emp_id;
        int salary;
        int link;
        int loc;
    } Rec;
    Rec Records;

public:
    int size;
    int Chain_tab[10][10];
    EMP_CLASS();
    void Insert();
    void init();
    void Display();
    void Search();
    void set_chain();
    void Delete();
    friend int Hash(int);
};

EMP_CLASS::EMP_CLASS()
{
    strcpy(Records.name, "");
    Records.emp_id = -1;
    Records.salary = -1;
    Records.link = -1;
}

void EMP_CLASS::init()
{
    fstream seqfile;
    seqfile.open("EMP.DAT", ios::out | ios::binary);

    size = 10;

    // setting null when initialize

    for (int i = 0; i < size; i++)
    {
        cout << " value of i:" << i;
        strcpy(Records.name, "");
        Records.emp_id = -1;
        Records.salary = -1;
        Records.link = -1;
        Records.link = i;

        seqfile.write((char *)&Records, sizeof(Records));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                Chain_tab[i][j] = -1;
    }
    cout << "\n\n Hash table is initialised...";
    // cout << "\n Now, insert the records in the hash table";
    seqfile.close();
}

int Hash(int num)
{
    int key = num % 10;
    return key;
}

void EMP_CLASS::set_chain()
{
    fstream seqfile;
    int i, j, h, offset;
    seqfile.open("EMP.DAT", ios::in | ios::out | ios::binary);
    for (i = 0; i < size; i++)
    {
        h = i;
        for (j = 0; j < size; j++)
        {
            if (Chain_tab[i][j] == 1)
            {
                offset = h * sizeof(Records);
                seqfile.seekg(offset);
                seqfile.read((char *)&Records, sizeof(Records));
                seqfile.seekp(offset);
                Records.link = j;
                seqfile.write((char *)&Records, sizeof(Records));
                h = j;
            }
        }
    }
    seqfile.close();
}

void EMP_CLASS::Insert()
{
    int i, h;
    char ch = 'y';
    char new_name[10];
    int new_emp_id;
    int new_salary;
    fstream seqfile;

    init(); // initialising the hash table

    // open file by read and write mode
    seqfile.open("EMP.DAT", ios::in | ios::out | ios::binary);

    do
    {
        cout << "\n Enter Name: ";
        cin >> new_name;
        cout << "\n Enter Emp_ID: ";
        cin >> new_emp_id;
        cout << "\n Enter Salary: ";
        cin >> new_salary;

        // generate hash key
        h = Hash(new_emp_id);
        int offset;

        // getting position in file where data to be Inserted
        offset = h * sizeof(Records);

        // seeking for reading record
        seqfile.seekg(offset);
        seqfile.read((char *)&Records, sizeof(Records));

        // seeking for writing record
        seqfile.seekp(offset);

        // if there is no previous record or no collision occurs
        if (Records.emp_id == -1)
        {
            strcpy(Records.name, new_name);
            Records.emp_id = new_emp_id;
            Records.salary = new_salary;
            Records.link = -1;
            Records.loc = h; // location of hash table where data is stored

            seqfile.write((char *)&Records, sizeof(Records)) << flush;
        }
        else // collision occurs
        {
            int flag = 0;

            int prev_link = Records.loc; // previous link of that element

            // handling collision
            do
            {
                // increasing hash key
                h++; // searching down for empty loc.in the file

                // if hash key is greater than size then hashtable is full

                if (h > size + 1)
                {
                    cout << "\n The hash table is Full, Can't insert record!!!";
                    return;
                }

                // getting position of key in file
                offset = h * sizeof(Records);

                // move get pointer to that file
                seqfile.seekg(offset);

                // read file
                seqfile.read((char *)&Records, sizeof(Records));

                // if record is empty then insert new element

                if (Records.emp_id == -1) // finding empty loc. using linear probing
                {

                    seqfile.seekp(offset); // seeking the empty slot in the file

                    strcpy(Records.name, new_name); // for placing the record

                    Records.emp_id = new_emp_id;
                    Records.salary = new_salary;
                    Records.link = -1;
                    Records.loc = h; // setting the location for colliding record

                    seqfile.write((char *)&Records, sizeof(Records)) << flush;

                    // collinding record is placed in the file at proper pos.
                    // chain table is maintained for keeping track of all the colliding entries.

                    Chain_tab[prev_link][h] = 11;
                    flag = 1; // indicates colliding record is inserted
                }

            } while (flag == 0); // collision handled
        }                        // end of else
        cout << "\nDo you want to add more records? (yes-y/no-n)\t";
        cin >> ch;
        set_chain(); // setting the chain to handle collision
    } while (ch == 'y');
    seqfile.close();
}

void EMP_CLASS::Display()
{
    fstream seqfile;

    seqfile.open("EMP.DAT", ios::in | ios::out | ios::binary);

    seqfile.seekg(0, ios::beg);

    cout << "\n The Contents of file are ..." << endl;

    cout << "\nLoc.      Name         Emp_ID      Salary        Link    ";
    while (seqfile.read((char *)&Records, sizeof(Records)))
    {

        if (strcmp(Records.name, "") != 0) // not displaying empty slots
        {
            cout << "\n--------------------------------------------------------\n";
            cout << Records.loc << "       " << Records.name << flush << "      " << Records.emp_id;
            cout << "          " << Records.salary << "          " << Records.link;
        }
    }
    seqfile.close();
}

void EMP_CLASS::Search()
{
    fstream seqfile;
    int key, h, offset, flag = 0;

    cout << "\n Enter the Emp_ID for searching the record ";
    cin >> key;

    seqfile.open("EMP.DAT", ios::in | ios::binary);

    h = Hash(key); // obtaining the location of rec.using hash function
    while (seqfile.eof() == 0)
    {

        // h is a hash key
        offset = h * sizeof(Records);

        // using h for getting actual position in the file

        // hence offset is calculated
        seqfile.seekg(offset, ios::beg);                 // seeking rec.of that offset
        seqfile.read((char *)&Records, sizeof(Records)); // reading that rec.

        if (key == Records.emp_id) // checking if it is required rec.
        {
            cout << "\n The Record is present in the file and it is...";
            cout << "\n Name: " << Records.name;
            cout << "\n Emp_ID: " << Records.emp_id;
            cout << "\n Salary: " << Records.salary;
            flag = 1; // means desired reocrd is obtained
            return;
        }
        else // following link for colliding record
        {
            h = Records.link; // moving along the chain
        }
    }
    // endof while

    if (flag == 0)
        cout << "\n The Record is not present in the file";

    seqfile.close();
    return;
}

void EMP_CLASS::Delete()
{
    fstream seqfile, secondfile;
    int key, h, offset, flag = 0;

    cout << "\n Enter the Emp_ID to delete the record: ";
    cin >> key;

    seqfile.open("EMP.DAT", ios::in | ios::binary);
    secondfile.open("TEMP.DAT", ios::out | ios::binary);

    h = Hash(key); // obtaining the location of rec. using the hash function

    while (seqfile.read((char *)&Records, sizeof(Records)))
    {
        offset = h * sizeof(Records);

        if (key != Records.emp_id) // checking if it is the required record
        {
            secondfile.write((char *)&Records, sizeof(Records));
        }
        else
        {
            flag = 1; // indicates the record is found
        }
    }

    seqfile.close();
    secondfile.close();

    // Delete the original file and rename the temporary file
    if (remove("EMP.DAT") != 0)
    {
        perror("Error deleting file");
        return;
    }

    if (rename("TEMP.DAT", "EMP.DAT") != 0)
    {
        perror("Error renaming file");
        return;
    }

    if (flag == 1)
    {
        cout << "\nEmployee Deleted\n";
    }
    else
    {
        cout << "\nEmployee Not Found\n";
    }
}

int main()
{
    EMP_CLASS List;
    char ans = 'y';
    int choice, key;
    do
    {
        cout << "\nMain Menu" << endl;
        cout << "\n 1.Insert";
        cout << "\n 2.Display";
        cout << "\n 3.Search";
        cout << "\n 4.Delete";
        cout << "\n 5.Exit";
        cout << "\n Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            List.Insert();
            break;
        case 2:
            List.Display();
            break;
        case 3:
            List.Search();
            break;

        case 4:
            List.Delete();
            break;
        case 5:
            exit(0);
        }
        cout << "\n Do you want to go back to Main Menu?";
        cin >> ans;
    } while (ans == 'y');
}

/*

             Main Menu

 1.Insert
 2.Display
 3.Search
 4.Exit
 Enter your choice: 1
 value of i:0 value of i:1 value of i:2 value of i:3 value of i:4 value of i:5 value of i:6 value of i:7 value of i:8 value of i:9

 Hash table is initialised...
 Enter Name: Dinesh

 Enter Emp_ID: 6

 Enter Salary: 9000

Do you want to add more records? (yes-y/no-n)   y

 Enter Name: Omkar

 Enter Emp_ID: 5

 Enter Salary: 8922

Do you want to add more records? (yes-y/no-n)   y

 Enter Name: Sakshi

 Enter Emp_ID: 2

 Enter Salary: 8000

Do you want to add more records? (yes-y/no-n)   y

 Enter Name: Tanmay

 Enter Emp_ID: 5

 Enter Salary: 20000

Do you want to add more records? (yes-y/no-n)   y

 Enter Name: Pragati

 Enter Emp_ID: 8

 Enter Salary: 3000

Do you want to add more records? (yes-y/no-n)   n

 Do you want to go back to Main Menu?y

             Main Menu

--------------------------------------------------------
2       Sakshi      2          8000          -1
--------------------------------------------------------
5       Omkar      5          8922          7
--------------------------------------------------------
6       Dinesh      6          9000          -1
--------------------------------------------------------
7       Tanmay      5          20000          -1
--------------------------------------------------------
8       Pragati      8          3000          -1
 Do you want to go back to Main Menu?y

             Main Menu

 1.Insert
 2.Display
 3.Search
 4.Exit
 Enter your choice: 3

 Enter the Emp_ID for searching the record 7
 */
