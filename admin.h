#pragma once
#include "teacher.h"

new_admissions entry;
faculty_teachers f_teach;

class admin {

public:

    void manage_teachers() {
        int c;
        while (true) {
            system("cls");
            system("color F5");

            cout << "Teacher's Management Module...\n";
            cout << "Press 0 to Terminate.\n"
                 << "Press 1 to Add New Teacher.\n"
                 << "Press 2 to Remove Any Teacher.\n"
                 << "Press 3 to See Teacher's Attendance.\n"
                 << "Press 4 to See Your Teacher's Faculty.\n";

            c = choice(4, 0);

                 if (c == 0) break;
            else if (c == 1) f_teach.add_teacher();
            else if (c == 2) f_teach.remove_teacher();
            else if (c == 3) f_teach.display_attendance_Teachers();
            else if (c == 4) f_teach.display_faculty();
        }
    }


    void manage_students() {
        int c;
        while (true) {
            system("cls");
            system("color F5");

            cout << "Student's Management Module...\n";
            cout << "Press 0 to Terminate.\n"
                 << "Press 1 to Add New Admissions.\n"
                 << "Press 2 to Remove Any Student.\n"
                 << "Press 3 to See Student Complaints.\n"
                 << "Press 4 to Check Students Data."<<endl;

            c = choice(4, 0);

            if (c == 0) break;

            else if (c == 1) {
                int x = entry.display_newAdmission();
                node_newAdmit* ptr;

                switch (x) {
                case 1:
                    ptr = entry.return_node();
                    ics.add_student_ics(ptr);
                    cout << "Student Added to ICS Successfully...";
                    getch();
                    break;

                case 2:
                    ptr = entry.return_node();
                    fsc.add_student_fsc(ptr);
                    cout << "Student Added to FSC Successfully...";
                    getch();
                    break;

                case 3:
                    entry.remove_head();
                    cout << "Student Discarded Successfully...";
                    getch();
                    break;
                }
            }

            else if (c == 2) {
                cout << "Enter Roll Number of Student to Delete: ";
                int roll = choice(99, 1);

                if (roll < 50) ics.delete_st(roll);
                else fsc.delete_st(roll);
            }

            else if (c == 3) {
                cout << "Press 1 for ICS Complaints.\n"
                     << "Press 2 for FSC Complaints.\n";

                int opt = choice(2, 1);
                if (opt == 1) ics.complain("admin");
                else fsc.complain("admin");
            }
            
            else if (c == 4){
            	cout << "Press 1 for ICS Class Details.\n"
                     << "Press 2 for FSC Class Details.\n";
                int opt = choice(2, 1);
                if (opt == 1) ics.display_ics_class();
                else if (opt == 2) fsc.display_fsc_class();
			}
            
        }
    }


    void display_admin_menu() {
        int c;
        while (true) {
            system("cls");
            system("color 80");

            cout << "\t\t.... Welcome Dear Admin ....\n\n";
            cout << "Press 0 to Terminate.\n"
                 << "Press 1 to Enter Teacher Module.\n"
                 << "Press 2 to Enter Student Module.\n";

            c = choice(2, 0);

            if (c == 0) break;
            else if (c == 1) manage_teachers();
            else if (c == 2) manage_students();
        }
    }
};

void Admissions() {
    string name, degree;
    long long int cnic;
    int age;

    system("cls");
    system("color F4");
    cout << "Registration Portal...\n";

    for (int i = 5; i > 0; i--) {

        if (i == 1) cout << "Last Try left...." << endl;

        while (true) {
            cout << "Name (As per CNIC): ";
            if (!getline(cin, name)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (!name.empty() && all_of(name.begin(), name.end(), 
                [](char ch){ return isalpha(ch) || isspace(ch); })) {
                break;
            }
        }

        while (true) {
            cout << "Age (15-30): ";
            if (cin >> age && age >= 15 && age <= 30) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "CNIC (13 digits): ";
            if (cin >> cnic && cnic >= 1000000000000LL && cnic <= 9999999999999LL) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Previous Degree (comp/bio): ";
            if (!getline(cin, degree)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (!degree.empty() && all_of(degree.begin(), degree.end(),
                [](char ch){ return isalpha(ch) || isspace(ch); })) {
                break;
            }
        }

        cout << "Enter 1 to save data or 0 to re-enter: ";
        int c = choice(1, 0);
        if (c == 1) break;
    }

    capitalize(name);
    capitalize(degree);

    entry.add_newAddmision(name, age, cnic, degree);

    cout << "Data Saved Successfully...\n";
}
