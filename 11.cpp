// 11

#include <iostream>
#include <fstream>
using namespace std;
class student
{
public:
    int rollno;
    char div;
    bool flag;
    char name[20];
    char addr[20];
    void getdata();
    void display_data();
    int return_rno();
};

void student::getdata()
{
    cout << "Enter roll number: ";
    cin >> rollno;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter division: ";
    cin >> div;
    cout << "Enter address: ";
    cin >> addr;
}

void student::display_data()
{
    cout << "\nRoll Number: " << rollno << endl;
    cout << "Name: " << name << endl;
    cout << "Division: " << div << endl;
    cout << "Address: " << addr << endl;
}

int student::return_rno()
{
    return rollno;
}

void write_rec()
{

    ofstream fobj;
    fobj.open("Info.txt", ios::app);
    student s1;
    s1.getdata();
    fobj.write((char *)&s1, sizeof(s1));
    fobj.close();
}
void display_rec()
{
    ifstream f1;
    f1.open("Info.txt");
    student s1;
    while (f1.read((char *)&s1, sizeof(s1)))
        s1.display_data();
    f1.close();
}
void search_rec()
{
    int rno;
    cout << "\nEnter rollno to be searched: ";
    cin >> rno;
    ifstream f1;
    f1.open("Info.txt", ios::in);
    student s1;
    while (f1.read((char *)&s1, sizeof(s1)))
    {
        if (s1.return_rno() == rno)
        {
            s1.flag = true;
            s1.display_data();
            f1.close();
            return;
        }
    }
    f1.close();
    if (s1.flag == false)
        cout << "Data not found" << endl;
}
void delete_rec()
{
    student s1;

    int r1no;
    cout << "\nEnter rollno to be deleted: ";
    cin >> r1no;
    ifstream f1;
    ofstream f2;
    f1.open("Info.txt", ios::in);
    f2.open("temp.txt", ios::out);
    f1.read((char *)&s1, sizeof(s1));
    while (!f1.eof())
    {
        if (s1.return_rno() != r1no)
            f2.write((char *)&s1, sizeof(s1));
        f1.read((char *)&s1, sizeof(s1));
    }
    cout << "\nRecord with rollno " << r1no << " has been deleted" << endl;
    f1.close();
    f2.close();
    remove("Info.txt");
    rename("temp.txt", "Info.txt");
}

int main()
{

    int option;
    bool exit = false;

    while (!exit)
    {

        cout << "\n1) Add New Student\n2) Remove Student\n3) Search Student\n4) Display\n5) Exit\nEnter option: ";
        cin >> option;

        switch (option)
        {
        case 1:

            int count;
            cout << "Enter number of records to be entered: ";
            cin >> count;
            for (int i = 0; i < count; i++)
                write_rec();
            break;
        case 2:
            delete_rec();
            break;

        case 3:
            search_rec();
            break;

        case 4:
            display_rec();
            break;

        default:
            exit = true;
            break;
        }
    }

    // cout << "\nRecords entered are: ";
    // display_rec();
    // search_rec();
    // delete_rec();
    // display_rec();
    return 0;
}

// Output
/* 1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 1
Enter number of records to be entered: 5
Enter roll number: 11
Enter name: Dinesh Rathod
Enter division: Enter address: Enter roll number: ^X
PS F:\4th Sem\DSA\Codes> ./i

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 1
Enter number of records to be entered: 5
Enter roll number: 1
Enter name: DInesh
Enter division: A
Enter address: Pune
Enter roll number: 2
Enter name: Omkar
Enter division: B
Enter address: Lonavala
Enter roll number: 74
Enter name: Pragati
Enter division: C
Enter address: Jalgav
Enter roll number: 78
Enter name: Aniket
Enter division: K
Enter address: Kolhapur
Enter roll number: 77
Enter name: Trupti
Enter division: D
Enter address: Karvenagar

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 4

Roll Number: 11
Name: Dinesh
Division: R
Address: athod

Roll Number: 1
Name: DInesh
Division: A
Address: Pune

Roll Number: 2
Name: Omkar
Division: B
Address: Lonavala

Roll Number: 74
Name: Pragati
Division: C
Address: Jalgav

Roll Number: 78
Name: Aniket
Division: K
Address: Kolhapur

Roll Number: 77
Name: Trupti
Division: D
Address: Karvenagar

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 3

Enter rollno to be searched: 1

Roll Number: 1
Name: DInesh
Division: A
Address: Pune

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 2

Enter rollno to be deleted: 0

Record with rollno 0 has been deleted

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 3

Enter rollno to be searched: 77

Roll Number: 77
Name: Trupti
Division: D
Address: Karvenagar

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 2

Enter rollno to be deleted: 77

Record with rollno 77 has been deleted

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 4

Roll Number: 11
Name: Dinesh
Division: R
Address: athod

Roll Number: 1
Name: DInesh
Division: A
Address: Pune

Roll Number: 2
Name: Omkar
Division: B
Address: Lonavala

Roll Number: 74
Name: Pragati
Division: C
Address: Jalgav

Roll Number: 78
Name: Aniket
Division: K
Address: Kolhapur

1) Add New Student
2) Remove Student
3) Search Student
4) Display
5) Exit
Enter option: 5 */