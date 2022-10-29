#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class student
{
    int id;
    char name[50];
    char a[20], b[20], c[20], d[20], e[20], f[20];

public:
    void getdata();
    void showdata() const;
    void show_tabular() const;
    int getid() const;
};

void student::getdata()
{
    cout << "\nEnter The Routinr ID: ";
    cin >> id;
    cout << "\n\nEnter day: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n9:30AM-10:20AM: ";
    cin >> a;
    cout << "\n10:30AM-11:20AM: ";
    cin >> b;
    cout << "\n11:30AM-12:20PM: ";
    cin >> c;
    cout << "\n1:00PM-2:00PM: ";
    cin >> d;
    cout << "\n2:00PM-3:00PM: ";
    cin >> e;
    cout << "\n3:00PM-4:00PM: ";
    cin >> f;
}

void student::showdata() const
{
    cout << "\nRoutinr ID: " << id;
    cout << "\nDay: " << name;
    cout << "\n9:30AM-10:20AM: " << a;
    cout << "\n10:30AM-11:20AM: " << b;
    cout << "\n11:30AM-12:20PM: " << c;
    cout << "\n1:00PM-2:00PM: " << d;
    cout << "\n2:00PM-3:00PM: " << e;
    cout << "\n3:00PM-4:00PM: " << e;
}

void student::show_tabular() const
{
    cout << id << setw(13) << name << setw(13) << a << setw(13) << b << setw(13) << c << setw(13) << d << setw(13) << e << setw(13) << f << setw(13) << endl;
}

int student::getid() const
{
    return id;
}
void SaveStudent();
void displayAll();
void Searchdisplay(int);
void modifyStudent(int);
void deleteStudent(int);
void DisplayClassResult();
void DisplayResult();

void write_student()
{
    student st;
    ofstream outFile;
    outFile.open("student.dat", ios::binary | ios::app);
    st.getdata();
    outFile.write(reinterpret_cast<char *>(&st), sizeof(student));
    outFile.close();
    cout << "\n\nRoutin Created Successful ";
    cin.ignore();
    cin.get();
}

void display_all()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL ROUTINE !!!\n\n";
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
    {
        st.showdata();
        cout << "\n\n<====================================>\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n)
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
    {
        if (st.getid() == n)
        {
            st.showdata();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nRoutine not exist";
    cin.ignore();
    cin.get();
}

void modify_student(int n)
{
    bool found = false;
    student st;
    fstream File;
    File.open("student.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!File.eof() && found == false)
    {

        File.read(reinterpret_cast<char *>(&st), sizeof(student));
        if (st.getid() == n)
        {
            st.showdata();
            cout << "\n\nPlease Enter The New Details of student: " << endl;
            st.getdata();
            int pos = (-1) * static_cast<int>(sizeof(st));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&st), sizeof(student));
            cout << "\n\n\t Routine Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Routine Not Found ";
    cin.ignore();
    cin.get();
}

void delete_student(int n)
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat", ios::out);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
    {
        if (st.getid() != n)
        {
            outFile.write(reinterpret_cast<char *>(&st), sizeof(student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRutine Deleted ..";
    cin.ignore();
    cin.get();
}

void class_result()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
    cout << "================================================================================================\n";
    cout << "seral id     day        9:30-10:20   10:30-11:20  11:30-12:20  1:00-2:00   2:00-3:00  3:00-4:00  " << endl;
    cout << "===================================================================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
    {
        st.show_tabular();
    }
    cin.ignore();
    cin.get();
    inFile.close();
}

int main()
{
    char ch;
    int num;
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);
    do
    {
        system("cls");
        cout << "\t<------------RUTINE MANAGEMENT SYSTEM----------------------->";
        cout << "\n\n\t1.CREATE CLASS ROUTINE";
        cout << "\n\n\t2.DISPLAY ALL ROUTINES IN COLUMN MODE";
        cout << "\n\n\t3.SEARCH BY ID ";
        cout << "\n\n\t4.MODIFY ROUTINE";
        cout << "\n\n\t5.DELETE ROUTINE";
        cout << "\n\n\t6.DISPLAY CLASS ROUTINE IN TABULAR MODE";
        cout << "\n\n\t7.EXIT";
        cout << "\n\n\t<------------------------------------------------------>";
        cout << "\n\n\tPlease Enter Your Choice (1-7): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_student();
            break;
        case '2':
            display_all();
            break;
        case '3':
            cout << "\n\n\tPlease Enter day serial id: ";
            cin >> num;
            display_sp(num);
            break;
        case '4':
            cout << "\n\n\tPlease EEnter day serial id: ";
            cin >> num;
            modify_student(num);
            break;
        case '5':
            cout << "\n\n\tPlease Enter day serial id: ";
            cin >> num;
            delete_student(num);
            break;
        case '6':
            class_result();
            break;
        case '7':
            exit(0);
            ;
        default:
            cout << "\a";
        }
    } while (ch != '7');

    return 0;
}

