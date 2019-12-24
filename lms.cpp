#include <iostream>
#include<cstring>
#include<windows.h>
#include<fstream>
#include<conio.h>
#include<process.h>
#include<string>
#include<iomanip>

using namespace std;

class book{
	char bno[6];
	char bname[50];
	char aname[20];
	
	public:
		void create_book(){
			cout<<"\nNEW BOOK ENTRY....\n";
			cout<<"\nENTER THE BOOK NUMBER....";
			cin>>bno;
			cout<<"\nEnter the name of book ";
			gets(bname);
			cout<<"\nEnter the Author's name ";
			gets(aname);
			cout<<"\n\n\nBook Created..";
		}
		//the function to show the books [just show the number author and the name]
		void show_book(){
			cout<<"\nBook no. :"<<bno;
			cout<<"\nBook name :"<<bname;
			cout<<"\nBook Author. :"<<aname;
		}		
		
//this is used to modidy the book[here the name and authors name is only modified not all the book number]
		void modify_book(){
			cout<<"\nBook no. :"<<bno;
			cout<<"\n Modify book name. :";
			gets(bname);
			cout<<"\nModify Book Author. :"<<aname;
			gets(aname);
		}
		
//Here the below function is used to return the book number
		char* retbno(){
			return bno;
		}
		
//This function is used to report for the book
		void report(){
			cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
		}
};

//This is the class student Object
class student{
	char admno[6];//student admission number
	char name[20];//student name
	char stbno[6];//student book number
	int token;//number of books	
public:
	void create_student(){
		system("cls");
		cout<<"\n\nNew student Entry...\n";
		cout<<"\nEnter the adminssion number";
		cin>>admno;
		cout<<"\n\nEnter the name of student";
		gets(name);
		token = 0;
		stbno[0] = '\0';
		cout<<"\n\nstudent Record is created..";
	}
	
	void show_student(){
		cout<<"\nAdmission number :"<<admno;
		cout<<"\nName : ";
		puts(name);
		cout<<"\n\nNumber of books issued :"<<token;
		if(token == 1)
			cout<<"\n\nBook Number :"<<stbno;
	}
//this is to modify student details
	void modify_student(){
		cout<<"\nAdmission number"<<admno;
		cout<<"\nModify Student ";
		gets(name);
	}
	char* retadmno(){
		return admno;	
	}
	char* retstbno(){
		return stbno;
	}
	int rettoken(){
		return token;
	}
	void addtoken(){
		token = 1;
	}
	void resettoken(){
		token = 0;
	}
	void getstbno(char t[]){//here we have to copy the recieved string(t) into the stbno string
		strcpy(stbno,t);
	}
	void report(){
		cout<<"\t"<<admno<<setw(20)<<name<<setw(20)<<stbno<<setw(20)<<token<<endl;
	}
};

//The gotoxy() func doesn't exist in  dev c++ hence won func is defined in <windows.h>
void gotoxy(short x, short y){
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Introduction function (To introduse the user about the library management system Project)
void intro(){
	system("cls");
	gotoxy(35,11);
	cout<<"LIBRARY";
	cout<<"MANAGEMENT ";
	cout<<"SYSTEM";
	gotoxy(35,17);
	cout<<"\n\nMADE BY: Aman Pandey";
	getch();
}

//Global declaration of the stream object 
fstream fp1, fp;//fstream is used to get access to file to both read and write purpose
book bk;
student st;


//Function to write in File
void write_book(){
	char ch;
	fp.open("book.dat",ios::out|ios::app);//ios::app seek to end of file after each writes
	do{						//ios::out for output (write)
		system("cls");			//ios::in for input(read)
		bk.create_book();
		fp.write((char*)&bk, sizeof(book));
		cout<<"\n\nDo you want any other operations:yes(y/Y) or No"<<endl;
		cin>>ch;
	}while(ch == 'y' || ch == 'Y');
	fp.close();
}



//fuction to write student details
void write_student(){
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do{
		system("cls");
		st.create_student();
		fp.write((char*)&st, sizeof(student));
		cout<<"\n\nDo you want any other operations:yes(y/Y) or No"<<endl;
		cin>>ch;
	}while(ch == 'y' || ch == 'Y');
	fp.close();
}

//Function to read specific record from file
void display_spb(char n[]){
	cout<<"\nBOOK DETAILS\n";
	int flag = 0;
	fp.open("book.dat",ios::in);//ios::in for input (read)
	while(fp.read((char*)&bk,sizeof(book))){
		if(strcmpi(bk.retbno(),n) == 0){
			bk.show_book();
			flag = 1;
		}	
	}
	fp.close();
	if(flag == 0);
		cout<<"\nThis book does not exist";
	getch();
}
//function for specific student
void display_sps(char n[]){
	cout<<"\nSTUDENT DETAILS\n";
	int flag = 0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student))){
		if(strcmpi(st.retadmno(),n) ==0){
			st.show_student();
			flag = 1;
		}
	}
	fp.close();
	if(flag == 0)
		cout<<"\nstudent does not exist";
	getch();
}

//function to modify book
void modify_book(){
	char n[6];
	int found = 0;
	cout<<"\n\nMODIFY BOOK RECORD......";
	cout<<"\n\nEnter the book no";
	cin>>n;
	fp.open("book.dat", ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book))&&found == 0){
		if(strcmpi(bk.retbno(),n)){
			bk.show_book();
			cout<<"\n\nEnter the details of book to be modified"<<endl;
			bk.modify_book();
			int pos = -1*sizeof(bk);
			fp.seekp(pos,ios::cur);//seekp(bytes,refernce_position) to take the pointer to desired position 
			fp.write((char*)&bk,sizeof(book));
			cout<<"record updated"<<endl;
			found = 1;
		}
	}
	fp.close();
	if(found == 0)
		cout<<"\n\nbook not found";
	getch();
}
//function to modify student
void modify_student(){
	char n[6];
	int found = 0;
	cout<<"\n\nEnter the student admition number:"<<endl;
	cin>>n;
	fp.open("student.dat",ios::in | ios::out);
	while(fp.read((char*)&st, sizeof(student))&&found == 0){
		if(strcmpi(st.retadmno(), n) == 0){
			st.show_student();
			cout<<"\nEnter the details of student to modify it"<<endl;
			st.modify_student();
			int pos = -1*sizeof(student);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\nRecord updated"<<endl;
			found = 1;
		}
	}
	fp.close();
	if(found == 0)
		cout<<"\n\nThe student doesnot exists"<<endl;
	getch();
}
//******************************************************************************************
//			funtion to delete the content
//******************************************************************************************
void delete_book(){
	char n[6];
	system("cls");
	cout<<"\n\nDELETE THE BOOK";
	cout<<"Enter the book number you wanna delete";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book))){
		if(strcmp(bk.retbno(),n) != 0){
			fp2.write((char*)&bk,sizeof(book));
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");//this is to remove the given file
	rename("Temp.dat","book.dat");//rename(old_name,new_name)// we have given the tem.dat as book.dat where book.dat is not previous but its new to temp.dat
	cout<<"\n\n\tRecord deleted"<<endl;
	getch();
}
//#########################################################################################
//				Delete Student Details
//#########################################################################################
void delete_student(){
	char n[6];
	int flag = 0;
	system("cls");
	cout<<"\n\nSTudent Delete"<<endl;
	cout<<"Enter the admition number"<<endl;
	cin>>n;
	fp.open("student.dat", ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat", ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student))){
		if(strcmpi(st.retadmno(),n) !=0){
			fp2.write((char*)&st,sizeof(student));
		}else{
			flag = 1;
		}
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag == 1)
		cout<<"Record deleted"<<endl;
	else
		cout<<"Record not found"<<endl;
	getch();
}

//to siaplay all students
void display_alls(){
	system("cls");
	fp.open("student.dat",ios::in);
	if(!fp){
		cout<<"\n\nError!!! FIle couldn't be open";
		getch();
		return;
	}
	cout<<"\n\n	student list "<<endl;
	cout<<"\n\n============================================================"<<endl;
	cout<<"\n\nAdmission no."<<setw(10)<<"Name"<<setw(20)<<"book issued"<<endl;
	cout<<"===================================================================="<<endl;
	while(fp.read((char*)&st,sizeof(student))){
		st.report();
	}
	fp.close();
	getch();
}

//function to display all books
void display_allb(){
	system("cls");
	fp.open("book.dat",ios::in);
	if(!fp){
		cout<<"Error !!File cann't be opened";
		getch();
		return;
	}
	cout<<"\n\nBook List"<<endl;
	cout<<"\n\n======================================================="<<endl;
	cout<<"\n\nBook name"<<setw(10)<<"Book number"<<setw(20)<<"Book Author"<<endl;
	cout<<"\n\n============================================================"<<endl;
	while(fp.read((char*)&bk,sizeof(book))){
		bk.report();	
	}
	fp.close();
	getch();
}

//Function to issue book
void book_issue(){
	char sn[6],bn[6];
	int found = 0,flag = 0;
	system("cls");
	cout<<"\n\nBOOK ISSUE"<<endl;
	cout<<"\n\nEnter the student admission number"<<endl;
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))){
		if(strcmpi(st.retadmno(),sn) == 0){
			found = 1;
			if(st.rettoken() == 0){
				cout<<"\n\nt Enter the book Number. ";
				cin>>bn;
				while(fp1.read((char*)&bk, sizeof(book))&&found == 0){
					if(strcmpi(bk.retbno(), bn) == 0){
						bk.show_book();
						flag = 1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos = -1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\tBook issued succesfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
					}	
				}
				if(flag == 0) 
					cout<<"\n\nBook No. does not exist";
			}else{
				cout<<"\nYou have not returned the last book ";
			}
		}
	}
	if(found == 0)
		cout<<"Student record does not exist......";
	getch();
	fp.close();
	fp1.close();
}

//function to deposit books
void book_deposit(){
	char sn[6],bn[6];
	int found = 0,flag = 0,day,fine;
		system("cls");
	cout<<"\n\nBook Deposit";
	cout<<"\n\nEnter the student admission number : ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(st))&&found == 0){
		if(strcmpi(st.retadmno(),sn) == 0){
			found = 1;
			if(st.rettoken() == 1){
				while(fp1.read((char*)&bk,sizeof(bk))&&flag == 0){
					if(strcmpi(bk.retbno(),st.retstbno()) == 0){
						bk.show_book();
						flag = 1;
						cout<<"\n\nBook deposited in no. of days?";
						cin>>day;
						if(day>15){
							fine = (day-15)*1;
							cout<<"\n\nThe finen have to deposited is"<<fine;
						}
						st.resettoken();
						int pos = -1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\nBook Deposited Successfully";
					}
				}
				if(flag == 0)
					cout<<"\n\nBook doesn't exist";
			}else{
				cout<<"\n\nNo book issued..please check";
			}
		}
	}
	if(found == 0)
		cout<<"\n\nstudent record doesn' exist";
	getch();
	fp.close();
	fp1.close();
}

//function fopr admin_menu
void admin_menu(){
	system("cls");
	int ch2;
	cout<<"\n\n\tAdministrator menu";
	cout<<"\n\n\t1,Create student record";
	cout<<"\n\n\t2.Display all student record";
	cout<<"\n\n\t3.Display specific student record";
	cout<<"\n\n\t4.modify student record";
	cout<<"\n\n\t5.delete student record";
	cout<<"\n\n\t6.create book";
	cout<<"\n\n\t7.display all books";
	cout<<"\n\n\t8.display specific book";
	cout<<"\n\n\t9.modify book";
	cout<<"\n\n\t10.delete book";
	cout<<"\n\n\t11.back to main menu";
	cout<<"\n\n\tPlease enter your choice(1-11)";
	cin>>ch2;
	switch(ch2){
		case 1:	system("cls");
				write_student();
				break;
		case 2:	display_alls();
				break;
		case 3:	char n[6];
				system("cls");
				cout<<"\nPlease enter the student admission number";
				cin>>n;
				display_sps(n);
				break;
		case 4:	modify_student();
				break;
		case 5:	delete_student();
				break;
		case 6:	system("cls");
				write_book();
				break;
		case 7:	display_allb();
				break;	
		case 8:	char s[6];
				system("cls");
				cout<<"\nPlease enter book number";
				cin>>s;
				display_spb(s);
				break;
		case 9:	modify_book();
				break;
		case 10:	delete_book();
				break;
		case 11:	exit(0);
	}
}

//This is the program Driver function or main function
int main(int argc, char** argv) {
	char ch;
	intro();//Intoduction Function

	//make it menu driven
	do{//ask for different types of operations to be performed
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
		cout<<"\n\n\t04. ADMINISTRATOR MENU";
		cout<<"\n\n\t05. EXIT";
		cout<<"\n\n\tPlease select your option(1-4)";
		ch = getch();
		switch(ch){//according to the choosen input from user perform the operation
			case '1': system("cls");
					book_issue();
					break;
			case '2': book_deposit();
					break;
			case '3': admin_menu();
					break;
			case '4': exit(0);
			default: cout<<"\a";
		}
	}while(ch!='4');
	return 0;
}
