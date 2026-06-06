#pragma once
#include "student.h"

ICS ics;
FSC fsc;

void capitalize(string &str){
    if (str.length() == 0) return;
    if (str[0] >= 'a' && str[0] <= 'z') str[0] = str[0] - ('a' - 'A');
    for (int i = 1; i < (int)str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] = str[i] + ('a' - 'A');
    }
}

struct biodata {
    string name;
    int age;
    string education;
    string cnic;

    biodata() : name(""), age(0), education(""), cnic("") {}

    void add_data() {
        clearin();
        cout << "Enter name of Teacher: ";
        getline(cin, name);
        capitalize(name);
        clearin();
        cout << "Enter Education of " << name << ": ";
        getline(cin, education);
        capitalize(education);
        cout << "Enter Age of " << name << ": ";
        cin >> age;
        cout << "Enter CNIC Number of " << name << " (without dashes): ";
        clearin();
        getline(cin, cnic);
    }

    void see_biodata() {
        cout << "-----------------------------\n";
        cout << setw(20) << left << "Name: " << setw(20) << left << name << endl;
        cout << setw(20) << left << "Age: " << setw(20) << left << age << endl;
        cout << setw(20) << left << "CNIC: " << setw(20) << left << cnic << endl;
        cout << setw(20) << left << "Education: " << setw(20) << left << education << endl;
    }

    void save(ofstream &fout){
        size_t len;

        len = name.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(name.c_str(), len);

        len = education.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(education.c_str(), len);

        len = cnic.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(cnic.c_str(), len);

        fout.write((char*)&age, sizeof(age));
    }

    void load(ifstream &fin){
        size_t len;
        char *buffer;

        fin.read((char*)&len, sizeof(len));
        buffer = new char[len+1]; fin.read(buffer, len); buffer[len]='\0'; name=buffer; delete[] buffer;

        fin.read((char*)&len, sizeof(len));
        buffer = new char[len+1]; fin.read(buffer, len); buffer[len]='\0'; education=buffer; delete[] buffer;

        fin.read((char*)&len, sizeof(len));
        buffer = new char[len+1]; fin.read(buffer, len); buffer[len]='\0'; cnic=buffer; delete[] buffer;

        fin.read((char*)&age, sizeof(age));
    }
};

int tcount = 0;

struct teacher {
    biodata bio;
    string sub;
    bool ics;
    bool fsc;
    int attendance;

    teacher() : sub(""), ics(false), fsc(false), attendance(0) {}

    void add_teacher_data(){
        bio.add_data();
        while(true){
            cout << "Enter Subject Which this Teacher Teaches : ";
            cin >> sub;
            capitalize(sub);

            if(sub=="Physics"){ ics=fsc=true; tcount++; break; }
            else if(sub=="Urdu"){ ics=fsc=true; tcount++; break; }
            else if(sub=="English"){ ics=fsc=true; tcount++; break; }
            else if(sub=="Maths"){ ics=true; fsc=false; tcount++; break; }
            else if(sub=="Computer"){ ics=true; fsc=false; tcount++; break; }
            else if(sub=="Chemistry"){ ics=false; fsc=true; tcount++; break; }
            else if(sub=="Biology"){ ics=false; fsc=true; tcount++; break; }
            else { cout<<"No Subject exist. Enter subject again..."; getch(); }
        }
    }

    void display_teacher(){
        cout<<"\n\tTeacher's Whole Data : \n"<<endl;
        bio.see_biodata();
        cout << setw(20) << left << "Subject Teaches : " << setw(25) << left << sub ;
        cout<<" ...To ( "; if(ics)cout<<"ICS "; if(fsc)cout<<"FSC "; cout<<")"<<endl;
        cout << setw(20) << left << "Attendance : " << setw(20) << left << attendance << endl;
        cout<<"-----------------------------\n";
    }

    void only_Attendance(){
        cout<<"\nAttendance of -> "<<bio.name<<" is -> "<<attendance<<endl;
    }

    void save(ofstream &fout){
        bio.save(fout);
        size_t len = sub.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(sub.c_str(), len);
        fout.write((char*)&ics, sizeof(ics));
        fout.write((char*)&fsc, sizeof(fsc));
        fout.write((char*)&attendance, sizeof(attendance));
    }

    void load(ifstream &fin){
        bio.load(fin);
        size_t len;
        char *buffer;
        fin.read((char*)&len, sizeof(len));
        buffer = new char[len+1]; fin.read(buffer, len); buffer[len]='\0'; sub=buffer; delete[] buffer;
        fin.read((char*)&ics, sizeof(ics));
        fin.read((char*)&fsc, sizeof(fsc));
        fin.read((char*)&attendance, sizeof(attendance));
    }
};

struct node {
    teacher data;
    node *next;
    node() : next(nullptr) {}
};

class faculty_teachers {
private:
    node *head;
    node *tail;
    node *ptr;
    const string filename = "teachers.dat";

    void save_to_file(){
        ofstream fout(filename, ios::binary | ios::trunc);
        node *temp = head;
        while(temp){
            temp->data.save(fout);
            temp = temp->next;
        }
        fout.close();
    }

    void load_from_file(){
        ifstream fin(filename, ios::binary);
        if(!fin) return;

        while(fin.peek() != EOF){
            teacher tempTeacher;
            tempTeacher.load(fin);
            node* newNode = new node;
            newNode->data = tempTeacher;

            if(!head) head=tail=newNode;
            else { tail->next=newNode; tail=newNode; }
            tcount++;
        }
        fin.close();
    }

public:
    faculty_teachers() : head(nullptr), tail(nullptr), ptr(nullptr){
        load_from_file();
    }

    void add_teacher(){
        if(tcount==7){ cout<<"Seats of Teachers is Fulled No more Addition Possible..."; getch(); return; }
        ptr = new node;
        ptr->data.add_teacher_data();

        if(head==nullptr){ head=tail=ptr; cout<<"\n TEACHER ADDED SUCCESSFULLY..."<<endl; save_to_file(); getch(); return; }

        node* temp = head;
        while(temp){
            if(temp->data.sub == ptr->data.sub){ cout<<"This Subject Teacher Already Exists ..."; delete ptr; tcount--; getch(); return; }
            temp=temp->next;
        }

        tail->next = ptr;
        tail = ptr;
        cout<<"\n TEACHER ADDED SUCCESSFULLY..."<<endl;
        save_to_file();
        getch();
    }

    void remove_teacher(){
        string s; cout<<"Enter Subject Name to Remove Teacher : "; cin>>s; capitalize(s);
        if(head==nullptr){ cout<<"\nNo Teacher Exists Returning Back .... "; getch(); return; }

        node *temp=head, *prev=nullptr; bool found=false;
        while(temp){
            if(temp->data.sub==s){
                system("cls");
                temp->data.display_teacher();
                cout<<"\n\t Press Any key to Remove This Teacher..."; getch();
                found=true;
                if(prev==nullptr){ head=head->next; if(head==nullptr) tail=nullptr; }
                else { prev->next=temp->next; if(temp==tail) tail=prev; }
                delete temp; tcount--;
                save_to_file();
                return;
            }
            prev=temp; temp=temp->next;
        }
        if(!found){ cout<<"\n Teacher Not Found Who Teaches This Subject..."; getch(); return; }
    }

    void display_attendance_Teachers(){
        node* temp=head;
        if(!head){ cout<<"No Teacher To Display Attendance..."; getch(); return; }
        while(temp){ temp->data.only_Attendance(); temp=temp->next; }
        getch();
    }

    void display_faculty(){
        node* temp=head;
        if(!head){ cout<<"No Faculty Teacher To Display Attendance..."; getch(); return; }
        while(temp){ temp->data.display_teacher(); temp=temp->next; }
        getch();
    }

    void Add_attendance_ics(string teacher_sub){
        if(teacher_sub != "Computer"){ cout << "Only the ICS class teacher (Computer) can add attendance.\n"; getch(); return; }
        ics.attendance_time();
    }

    void Add_attendance_fsc(string teacher_sub){
        if(teacher_sub != "Biology"){ cout << "Only the FSC class teacher (Biology) can add attendance.\n"; getch(); return; }
        fsc.attendance_time();
    }

    void Add_result(string sub){
        if(sub=="Physics"){ 
		cout<<"Enter Physics Numbers For ICS...\n"; 
		ics.add_result_Physics(); cout<<"\nPress any key to jump on FSC..."; getch(); 
		cout<<"Enter Physics Numbers For FSC...\n"; fsc.add_result_Physics(); cout<<"Marks is Submitted...\n"; 
		return; }
        else if(sub=="Urdu"){ 
		cout<<"Enter Urdu Numbers For ICS...\n";
		 ics.add_result_Urdu(); cout<<"\nPress any key to jump on FSC..."; getch(); 
		 cout<<"Enter Urdu Numbers For FSC...\n"; fsc.add_result_Urdu(); cout<<"Marks is Submitted...\n"; 
		 return; }
        else if(sub=="English"){ 
		cout<<"Enter English Numbers For ICS...\n";
		 ics.add_result_English(); cout<<"\nPress any key to jump on FSC..."; getch(); 
		 cout<<"Enter English Numbers For FSC...\n"; fsc.add_result_English(); cout<<"Marks is Submitted...\n";
		  return; }
        else if(sub=="Computer"){ 
		cout<<"Enter Computer Numbers For ICS...\n";
		 ics.add_result_Computer(); cout<<"\nMarks Submitted..."; getch();
		  return; }
        else if(sub=="Maths"){ cout<<"Enter Maths Numbers For ICS...\n"; 
		ics.add_result_Maths(); cout<<"\nMarks Submitted..."; getch(); return; }
        else if(sub=="Biology"){ cout<<"Enter Biology Numbers For FSC...\n"; 
		fsc.add_result_Biology(); cout<<"\nMarks Submitted..."; getch(); return; }
        else if(sub=="Chemistry"){ cout<<"Enter Chemistry Numbers For FSC...\n"; 
		fsc.add_result_Chemistry(); cout<<"\nMarks Submitted..."; getch(); return; }
    }

    void change_result_ics(string s){ capitalize(s); int roll; while(true){ 
	cout<<"Enter Roll-No : "; cin>>roll; if(cin.fail() || roll<1 || roll>49){ cin.clear(); cin.ignore(1000,'\n');
	 cout<<"Invalid input! Enter a number between (1-49).\n"; } else break; } ics.modify_subject_result(roll,s); }

    void change_result_fsc(string s){ capitalize(s); int roll; while(true){ 
	cout<<"Enter Roll-No : "; cin>>roll; if(cin.fail() || roll<51 || roll>99){ cin.clear(); cin.ignore(1000,'\n'); 
	cout<<"Invalid input! Enter a number between (51-99).\n"; } else break; } fsc.modify_subject_result(roll,s); }

    void change_result(string str){
        capitalize(str);
        if(str=="Physics" || str=="Urdu" || str=="English"){
            cout<<"Press 1 if you want to Update in ICS \n OR \nPress 2 if you want to update in FSC\n";
            int n; while(true){ cout<<"Enter Choice : "; cin>>n; if(cin.fail() || n<1 || n>2){ 
			cin.clear(); cin.ignore(1000,'\n'); cout<<"Invalid input! Enter a number (1 or 2).\n"; } 
			else break; }
            if(n==1) change_result_ics(str); else change_result_fsc(str); return;
        }
        else if(str=="Computer" || str=="Maths"){ change_result_ics(str); return; }
        else if(str=="Chemistry" || str=="Biology"){ change_result_fsc(str); return; }
        else{ cout<<endl<<"No subject with this name in FSC or ICS"<<endl; getch(); return; }
    }

    void display_teach_menu(string str){
        node *temp=head; int choice; bool found=false;
        while(temp){
            if(temp->data.sub==str){
                system("color F0");
                cout<<"\n\tWelcome Dear Teacher .....\n";
                cout<<"\tName :"<<temp->data.bio.name<<endl;
                cout<<"\tCNIC :"<<temp->data.bio.cnic<<endl;
                cout<<"\tTeaches :"<<temp->data.sub<<endl;
                string subject=temp->data.sub;
                temp->data.attendance++;
                save_to_file(); // update file when attendance changes
                cout<<"\n\n\tPress any key to Continue..."; getch();
                found=true;
                while(true){
                    system("cls");
                    cout<<"\nTeacher's Portal.....\n\n";
                    cout<<"Press 0 to Terminate."<<endl;
                    cout<<"Press 1 to Add Attendance."<<endl;
                    cout<<"Press 2 to Add Result."<<endl;
                    cout<<"Press 3 to Change Specific Result."<<endl;
                    cout<<"\nEnter your Choice Here :";
                    while(true){ cin>>choice; 
					if(cin.fail() || choice<0 || choice>3){ 
					cin.clear(); cin.ignore(1000,'\n'); 
					cout<<"Invalid choice! Enter 0-3: ";
					 } else break; }

                    if(choice==0) break;
                    else if(choice==1){ 
					if(subject=="Computer") Add_attendance_ics(subject);
					else if(subject=="Biology") Add_attendance_fsc(subject); 
					else cout<<"Only class teachers can add attendance.\n"; getch(); 
					}
                    else if(choice==2){ 
					Add_result(subject); getch(); }
                    else if(choice==3){ 
					change_result(subject); getch(); }
                }
                return;
            }
            temp=temp->next;
        }
        cout<<"Teacher Not Found..."; getch();
    }

    void show_tcount(){ cout<<"\nCurrent number of teachers: "<<tcount<<endl; }

    ~faculty_teachers(){
        node *current=head;
        while(current){ 
		node* nextNode=current->next;
		 delete current; 
		 current=nextNode; }
        head=tail=ptr=nullptr; 
		tcount=0;
    }
};
