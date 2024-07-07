#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class University
{
private:
    string Name, Rollno, Phoneno, Branch;

public:
    University() : Name(""), Rollno(""), Phoneno(""), Branch("") {}

    void setName(string name)
    {
        Name = name;
    }
    void setRollno(string rollno)
    {
        Rollno = rollno;
    }
    void setPhone(string number)
    {
        Phoneno = number;
    }
    void setBranch(string branch)
    {
        Branch = branch;
    }
    string getName() const
    {
        return Name;
    }
    string getRollno() const
    {
        return Rollno;
    }
    string getPhone() const
    {
        return Phoneno;
    }
    string getBranch() const
    {
        return Branch;
    }

    // Checking if the entered phone number is valid or not
    bool validPhone(string str)
    {
        if (str.size() != 10)
        {
            return false;
        }
        for (char it : str)
        {
            if (!isdigit(it))
            {
                return false;
            }
        }
        return true;
    }

    // Taking information of the student to add
    void addStudent()
    {
        string name, rollno, phonenumber, branch;
        cin.ignore();
        cout << "Enter the rollno of student: ";
        cin >> rollno;
        if (isRollnoPresent(rollno))
        {
            cout << "Entered Roll-No already present in record" << endl;
            cout << "---------------------------------" << endl;
            return;
        }
        setRollno(rollno);
        cin.ignore();
        cout << "Enter the name of student: ";
        getline(cin, name);
        setName(name);
        cout << "Enter the contact number of student: ";
        cin >> phonenumber;
        while (validPhone(phonenumber) == false)
        {
            cout << "Invalid input, enter a valid phone number: ";
            cin >> phonenumber;
        }
        setPhone(phonenumber);
        cin.ignore();
        cout << "Enter the branch of student: ";
        getline(cin, branch);
        setBranch(branch);
        addStudentToFile();
    }

    // Adding collected info of student to university record file
    void addStudentToFile()
    {
        ofstream out("record.txt", ios::app);
        if (out.is_open())
        {
            out << "Roll-No:" << Rollno << endl;
            out << "Name:" << Name << endl;
            out << "Phone number:" << Phoneno << endl;
            out << "Branch:" << Branch << endl;
            out << "-----------------------------" << endl;
            cout << "Student added successfully!" << endl;
            cout << "---------------------------------" << endl;
        }
        else
        {
            cout << "Unable to add student" << endl;
            cout << "---------------------------------" << endl;
        }
        out.close();
    }

    // Checking if roll number is already present
    bool isRollnoPresent(string rollno)
    {
        ifstream in("record.txt");
        if (!in.is_open())
        {
            return false;
        }
        string line;
        while (getline(in, line))
        {
            if (line.find("Roll-No:" + rollno) != string::npos)
            {
                in.close();
                return true;
            }
        }
        in.close();
        return false;
    }

    // Searching the student in university record file
    void searchStudent(string rollno)
    {
        ifstream in("record.txt");
        bool found = false;
        if (!in.is_open())
        {
            cout << "Student searching failed!" << endl;
            cout << "---------------------------------" << endl;
            return;
        }
        string line;
        while (getline(in, line))
        {
            if (line.find("Roll-No:" + rollno) != string::npos)
            {
                found = true;
                cout << "Student details found!" << endl;
                cout << "---------------------------------" << endl;
                cout << line << endl;
                for (int i = 0; i < 3; i++)
                {
                    getline(in, line);
                    cout << line << endl;
                }
                cout << "---------------------------------" << endl;
            }
        }
        if (!found)
        {
            cout << "Entered student details not found!" << endl;
            cout << "---------------------------------" << endl;
        }
        in.close();
    }

    // Updating the details of student
    void update(string rollno)
    {
        ifstream in("record.txt");
        bool found = false;
        int choice;
        vector<vector<string>> record;
        vector<string> student;
        string line;
        int counter = 0;

        if (!in.is_open())
        {
            cout << "Updation cannot be performed" << endl;
            cout << "---------------------------------" << endl;
            return;
        }

        while (getline(in, line))
        {
            student.push_back(line);
            counter++;
            if (line == "-----------------------------")
            {
                record.push_back(student);
                student.clear();
                counter = 0;
            }
        }
        in.close();

        for (auto &students : record)
        {
            if (students.size() > 0 && students[0].find("Roll-No:" + rollno) != string::npos)
            {
                found = true;
                cout << "Student found" << endl;
                cout << "---------------------------------" << endl;
                cout << "What do you want to update?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Phone number" << endl;
                cout << "3. Branch" << endl;
                cout << "4. Update all" << endl;
                cout << "5. Exit" << endl;
                cout << "---------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1 || choice == 4)
                {
                    string name;
                    cout << "Enter the new name of the student: ";
                    cin.ignore();
                    getline(cin, name);
                    students[1] = "Name:" + name;
                }
                if (choice == 2 || choice == 4)
                {
                    string number;
                    cout << "Enter new phone number: ";
                    cin >> number;
                    if (validPhone(number))
                    {
                        students[2] = "Phone number:" + number;
                    }
                    else
                    {
                        cout << "Could not update phone number, the input is invalid" << endl;
                        cout << "---------------------------------" << endl;
                        return;
                    }
                }
                if (choice == 3 || choice == 4)
                {
                    string branch;
                    cout << "Enter branch of student: ";
                    cin.ignore();
                    getline(cin, branch);
                    students[3] = "Branch:" + branch;
                }
            }
        }

        if (!found)
        {
            cout << "Student not found!" << endl;
            cout << "---------------------------------" << endl;
            return;
        }

        ofstream out("record.txt");
        if (!out.is_open())
        {
            cout << "Cannot retrieve data from file" << endl;
            cout << "---------------------------------" << endl;
            return;
        }
        for (const auto &students : record)
        {
            for (const auto &line : students)
            {
                out << line << endl;
            }
        }
        out.close();
        cout << "Student details updated successfully!" << endl;
        cout << "---------------------------------" << endl;
    }
};

int main()
{
    University data;
    int choice;
    cout<<"*********************************************"<<endl;
    cout<<"Welcome to University Management System"<<endl;
    cout<<"*********************************************"<<endl;
    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1. Add new student" << endl;
        cout << "2. Search student details" << endl;
        cout << "3. Update student details" << endl;
        cout << "4. Exit" << endl;
        cout << "---------------------------------" << endl;
        cout << "Enter: ";
        cin >> choice;
        if (choice == 1)
        {
            data.addStudent();
        }
        else if (choice == 2)
        {
            string rollno;
            cout << "Enter roll no: ";
            cin >> rollno;
            data.searchStudent(rollno);
        }
        else if (choice == 3)
        {
            string rollno;
            cout << "Enter roll no: ";
            cin >> rollno;
            data.update(rollno);
        }
        else if(choice==4)
        {
            cout<<"Thankyou for using the UMS";
            break;
        }
    }
    return 0;
}
