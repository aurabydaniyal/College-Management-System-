#include "admin.h"

admin ad;

const string ad_email = "admin@gmail.com";
const string ad_pass  = "admin123";
const string tc_email = "teacher@gmail.com";
const string tc_pass  = "teacher123";
const string st_email = "student@gmail.com";
const string st_pass  = "student123";
const string regist   = "registration";

string trymail = "";
string trypass = "";

void students_portal() {
    int roll;
    cout << "\nEnter Your Roll Number : ";
    roll = choice(99, 1);

    if (roll < 50)
        ics.display_All(roll);
    else
        fsc.display_All(roll);
}

void teachers_portal(){
    string sub;
    int a;
    clearin();
    while(true){
        cout<<"\nEnter Your Subject Name : ";
        getline(cin, sub);
        if(sub.empty()) continue;
        cout<<"Press 0 to confirm or 1 to write again: ";
        a=choice(1,0);
        if(a==0) break;
    }
    capitalize(sub);
    f_teach.display_teach_menu(sub);
}


void admins_portal() {
    ad.display_admin_menu();
}

string inputPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != 13) {
        if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void flashError(string message) {
    for (int i = 0; i < 3; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << message;
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << "\r" << string(message.length(), ' ') << "\r";
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void loading(string message) {
    cout << message;
    for (int i = 0; i < 5; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << endl;
}

void main_portal() {
    bool on = true;
    do {
    	system("cls");
        setColor(13);
        cout << "\t\t============================================================================";
        cout << "\n\t\t\t...........+++ WELCOME TO SCIENCE COLLEGES +++..........." << endl ;
        cout << "\t\t============================================================================\n\n";

        setColor(11);
        cout << " _"<< endl;
        cout << "/o\\" << endl;
        cout << "|+| ADMINS   Should Enter Their Email to Log in..." << endl << endl;
        setColor(6);
        cout << " _"<< endl;
        cout << "/o\\" << endl;
        cout << "|+| TEACHERS Should Enter Their Email to Log in..." << endl << endl;
        setColor(9);
        cout << " _"<< endl;
        cout << "/o\\" << endl;
        cout << "|+| STUDENTS Should Enter Their Email to Log in..." << endl << endl;
        setColor(10);
        cout << "\n\n\n |#| NOTE: For [New Registration Type (registration) in email box.]" << endl;
        clearin();
        system("cls");
        system("color F0");
        cout << "\t=================================================\n";
        cout << "\t|        LOGIN PAGE :                           |\n";
        cout << "\t=================================================\n"<<endl;
        cout << "\tEmail : ";
        cin>>trymail;

        if (trymail == regist) {
        	clearin();
            Admissions();
            cout << "Thanks For Your Registration ..." << endl;
            getch();
            continue;
        } else if (trymail == "break" || trymail == "crack" || trymail == "crash") {
            on = false;
            return;
        }

        cout << "\tPassword : ";
        trypass = inputPassword();

        if (trymail == ad_email && trypass == ad_pass) {
            loading("Logging in as Admin");
            admins_portal();
        } else if (trymail == tc_email && trypass == tc_pass) {
            loading("Logging in as Teacher");
            teachers_portal();
        } else if (trymail == st_email && trypass == st_pass) {
            loading("Logging in as Student");
            students_portal();
        } else {
            flashError("Wrong Entry! Please Try Again...");
            cout << "Press Any Key To Go Back To Landing Page...";
            getch();
            system("cls");
        }

    } while (on);
}

void greetings(){
        system("cls");

    setColor(13);
    cout << "\t\t=============================================================" << endl;
    setColor(14);
    cout << "\t\t\t     WELCOME TO SCIENCE COLLEGE PORTAL" << endl;
    setColor(13);
    cout << "\t\t=============================================================" << endl;

    setColor(12);
    cout << "\t\t\t--- ADMIN PORTAL ---" << endl;
    setColor(10);
    cout << "\t\t\t1. Add / Remove Teachers" << endl;
    cout << "\t\t\t2. View Teacher Attendance & Faculty List" << endl;
    cout << "\t\t\t3. Add / Remove Students" << endl;
    cout << "\t\t\t4. View Student Complaints" << endl;
    cout << "\t\t\t5. View All Students Data" <<endl;

    setColor(9);
    cout << "\n\t\t\t--- TEACHER PORTAL ---" << endl;
    setColor(6);
    cout << "\t\t\t1. Add Attendance for Your Class" << endl;
    cout << "\t\t\t2. Add Student Results" << endl;
    cout << "\t\t\t3. Modify Specific Student Results" << endl;

    setColor(14);
    cout << "\n\t\t\t--- STUDENT PORTAL ---" << endl;
    setColor(10);
    cout << "\t\t\t1. View Your Details" << endl;
    cout << "\t\t\t2. View Your Attendance" << endl;
    cout << "\t\t\t3. View Your Results " << endl;
    cout << "\t\t\t4. Add Complains " << endl;

    setColor(13);
    cout << "\n\t\t\t--- GENERAL FEATURES ---" << endl;
    setColor(9);
    cout << "\t\t\t1. Secure Login for ( Admin / Teacher / Student ) " << endl;
    cout << "\t\t\t2. New Student Registration Portal" << endl;
    cout << "\t\t\t3. Input Validation for All Entries" << endl;
    cout << "\t\t\t4. Data Organized by ICS & FSC Classes" << endl;
    cout << "\t\t\t5. Registration form for Students if they are New" << endl;

    setColor(13);
    cout << "\t\t=============================================================" << endl;
    setColor(14);
    cout << "\t\tPress Any Key to Continue...";
    getch();
    setColor(7);
    system("cls");
}


