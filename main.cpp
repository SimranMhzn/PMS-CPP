#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
using namespace std;

//password verification part
class Password{
		protected:
			string username,password;
			string newpw;
			string un,pw;
			char ch;
		public:
			void login_menu();
			void login_details();		
};

//vehicle data entry section
class Vehicles{
	protected:
		int plate_no;
		int entry_time_hr;
		int entry_time_min;
		int exit_time;
		char slotArray[5][8];
		string username,password;
		string newpw;
		string un,pw;
	public:
		void setVehicledata();
		void readVehicledata();
		void reserveSlot();
		void changepw();
};

//main function definition
void displayMenu()
{
	//object of vehicle class 
	Vehicles selection;
	int option;
	char ch;
	flag:
		system("cls"); //clears console
		//main menu 
		cout<<endl<<"\t\t\t\t1. Vehicle entry ";
		cout<<endl<<"\t\t\t\t2. Vehicle exit ";
		cout<<endl<<"\t\t\t\t3. Show reserved slots ";
		cout<<endl<<"\t\t\t\t4. Change password ";
		cout<<endl<<"\t\t\t\t5. Exit";
		cout<<endl<<"\n\n\t\t\t\t   Enter your choice:  ";
		cin>>option;
		switch(option)
		{
			case 1:
				selection.setVehicledata();
				displayMenu();
			case 2:
				selection.readVehicledata();
				displayMenu();
			case 3:
				selection.reserveSlot();
				break;
			/*case 4:
				selectionTemp.changepw();
				break;*/
			case 5:
				exit(0);
				break;
			default:
				cout<<endl<<"\t\t\t\tInvalid selection";
				cout<<endl<<endl<<"\t\t\tDo you want to try again?";
				cout<<endl<<"\t\t\tPress 'Y' to continue or 'N' to exit : ";
				cin>>ch;
				tolower(ch);
				if(ch=='y')
				{
					goto flag;
				}
				else
				{
					exit(0);
				}
		}
}

int main()
{
	Password obj;
	obj.login_menu();
	displayMenu();
	return 0;
}

//login menu showing function
void Password::login_menu()
{
	int choice;
	char ch;
	flag:
	system("cls");
	cout<<endl<<"\t\t-------------------MENU-----------------"<<endl;
	cout<<endl<<"\t\t\t\t1. Login";
	cout<<endl<<"\t\t\t\t2. Exit";
	cout<<endl<<endl<<"\t\t\tEnter your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			login_details();
			break;
		case 2:
			exit(0);
		default:
			cout<<"\n\t\t\t\tInvalid Input!";
			sleep(3);
			goto flag;
	}
}

//login details taking function
void Password::login_details()
{
	retry:
	system("cls");
	fstream login_file;
	cout<<endl<<"\t\t************WELCOME TO LOGIN PAGE************"<<endl;
	fflush(stdin);
	cout<<endl<<"\t\t\tEnter your username: ";
	getline(cin,un);
	cout<<endl<<"\t\t\tEnter your password: ";
	getline(cin,pw);
	login_file.open("logindata.txt",ios::in);
	if(!login_file)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	
	while(login_file>>username>>password)
	{
		if(username==un && password==pw)
		{
			cout<<endl<<"\t\t\t\tLogging in......";
			sleep(3);
			system("cls");
		}
		else
		{
			cout<<endl<<"\t\t\tInvalid Username or Password! ";
			fflush(stdin);
			cout<<endl<<"\t\t\tDo you want to try again (Y/N)? ";
			cin>>ch;
			tolower(ch);
			if(ch=='y')
			{
				system("cls");
				goto retry;
				login_file.close();
			}
			else if(ch=='n')
			{
				login_menu();
			}
			else
			{
				cout<<endl<<"\t\t\t\tInvalid Input!";
				exit(0);
			}
		}
	}
	login_file.close();
}

//getting the data 
void Vehicles::setVehicledata()
{
	system("cls");
	char ch;
	cout<<endl<<"\t\t\t\t**********PARKING SLOTS**********"<<endl<<endl;
	/*char arr[5][8] ={{'0','0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0','0'}};
	int position,i,j;
	cout<<endl<<"\t\t\t_______________________________________________";
	cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
	cout<<endl<<"\t\t\t  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  |  "<<arr[0][3]<<"  |  "<<arr[0][4]<<"  |  "<<arr[0][5]<<"  |  "<<arr[0][6]<<"  |  "<<arr[0][7]<<"  ";
	cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
	cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
	cout<<endl<<"\t\t\t  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  |  "<<arr[0][3]<<"  |  "<<arr[0][4]<<"  |  "<<arr[0][5]<<"  |  "<<arr[0][6]<<"  |  "<<arr[0][7]<<"  ";
	cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
	cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
	cout<<endl<<"\t\t\t  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  |  "<<arr[0][3]<<"  |  "<<arr[0][4]<<"  |  "<<arr[0][5]<<"  |  "<<arr[0][6]<<"  |  "<<arr[0][7]<<"  ";
	cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
	cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
	cout<<endl<<"\t\t\t  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  |  "<<arr[0][3]<<"  |  "<<arr[0][4]<<"  |  "<<arr[0][5]<<"  |  "<<arr[0][6]<<"  |  "<<arr[0][7]<<"  ";
	cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
	cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
	cout<<endl<<"\t\t\t  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  |  "<<arr[0][3]<<"  |  "<<arr[0][4]<<"  |  "<<arr[0][5]<<"  |  "<<arr[0][6]<<"  |  "<<arr[0][7]<<"  ";
	cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";*/

	cout<<endl<<endl<<"\t\t\tWhere do you want to park your vehicle?";
	flow:
		cout<<endl<<"\t\t\tEnter row: ";
		cin>>i;
		cout<<endl<<"\t\t\tEnter column: ";
		cin>>j;
		if(i>=5||j>=8)
		{
			cout<<endl<<"\t\t\tInvalid input.";
			cout<<endl<<"\t\t\tPlease enter row between 0-4 and column between 0-7.";
			goto flow;
		}
	Vehicles writingObject;
	cout<<endl<<"\t\t\tEnter details: ";
	cout<<endl<<"\t\t\t\tPlate number: ";
	cin>>writingObject.plate_no;
	cout<<endl<<"\t\t\t\tTime: ";
	cout<<endl<<"\t\t\t\t\tHour: ";
	cin>>writingObject.entry_time_hr;
	cout<<endl<<"\t\t\t\t\tMinute: ";
	cin>>writingObject.entry_time_min;
	fstream data_file;
	data_file.open("data.txt",ios::out);
	if(!data_file)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	data_file.write((char*)&writingObject,sizeof(writingObject));
	data_file.close();
		arr[i-1][j-1]='X';
		system("cls");
		cout<<endl<<"\t\t\t_______________________________________________";
		cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
		cout<<endl<<"\t\t\t  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  |  "<<arr[0][3]<<"  |  "<<arr[0][4]<<"  |  "<<arr[0][5]<<"  |  "<<arr[0][6]<<"  |  "<<arr[0][7]<<"  ";
		cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
		cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
		cout<<endl<<"\t\t\t  "<<arr[1][0]<<"  |  "<<arr[1][1]<<"  |  "<<arr[1][2]<<"  |  "<<arr[1][3]<<"  |  "<<arr[1][4]<<"  |  "<<arr[1][5]<<"  |  "<<arr[1][6]<<"  |  "<<arr[1][7]<<"  ";
		cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
		cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
		cout<<endl<<"\t\t\t  "<<arr[2][0]<<"  |  "<<arr[2][1]<<"  |  "<<arr[2][2]<<"  |  "<<arr[2][3]<<"  |  "<<arr[2][4]<<"  |  "<<arr[2][5]<<"  |  "<<arr[2][6]<<"  |  "<<arr[2][7]<<"  ";
		cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
		cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
		cout<<endl<<"\t\t\t  "<<arr[3][0]<<"  |  "<<arr[3][1]<<"  |  "<<arr[3][2]<<"  |  "<<arr[3][3]<<"  |  "<<arr[3][4]<<"  |  "<<arr[3][5]<<"  |  "<<arr[3][6]<<"  |  "<<arr[3][7]<<"  ";
		cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
		cout<<endl<<"\t\t\t     |     |     |     |     |     |     |     ";
		cout<<endl<<"\t\t\t  "<<arr[4][0]<<"  |  "<<arr[4][1]<<"  |  "<<arr[4][2]<<"  |  "<<arr[4][3]<<"  |  "<<arr[4][4]<<"  |  "<<arr[4][5]<<"  |  "<<arr[4][6]<<"  |  "<<arr[4][7]<<"  ";
		cout<<endl<<"\t\t\t_____|_____|_____|_____|_____|_____|_____|_____";
		cout<<endl<<endl<<"\t\t\tYour vehicle has been parked successfully.";
		cout<<endl<<"\t\t\t\t\tThank You.";
		cout<<endl<<endl<<"\t\t\tDo you want to park another vehicle?";
		cout<<endl<<"\t\t\tPress 'Y' to continue or 'N' to exit : ";
		cin>>ch;
		tolower(ch);
		if(ch=='y')
		{
			goto flow;
		}
		else
		{
			exit(0);
		}
}

void Vehicles::readVehicledata()
{
	Vehicles readingObject;
	int detailsCheck;
	fstream data_file;
	data_file.open("data.txt",ios::in);
	if(!data_file)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	cout<<endl<<"\t\t\t\tEnter number of vehile you want the details of: ";
	cin>>detailsCheck;
	while(data_file.read((char*)&readingObject,sizeof(readingObject)))
	{
		if(readingObject.plate_no==detailsCheck)
		{
			cout<<endl<<"\t\t\tTime parked";
			cout<<endl<<"\t\t\tHour: "<<readingObject.entry_time_hr;
			cout<<endl<<"\t\t\tMinute: "<<readingObject.entry_time_min;
		}
	}
	data_file.close();
}
/*void Vehicles::changepw()
{
	call:
		system("cls");
		char ch;
		fstream file2,file3;
		cin.ignore();
		cout<<endl<<"\t\t\tEnter your username: ";
		cin>>un;
		cout<<endl<<"\t\t\tEnter your current password: ";
		cin>>pw;
		file2.open("logindata.txt",ios::in);
		if(!file2)
		{
			cout<<endl<<"\t\t\tNo such file.";
		}
		while(file2>>username>>password)
		{
			if(password==pw)
			{
				cout<<endl<<"\t\t\tEnter new password: ";
				cin>>newpw;
				file3.open("logindata.txt",ios::out);
				if(!file3)
				{
					cout<<endl<<"\t\t\tNo such file.";
				}
				file3<<un<<" "<<newpw;
				cout<<endl<<"\t\t\tPassword changed successfully."<<endl;
				cout<<endl<<endl<<"\t\t\t\tPlease wait....";
				sleep(3);
				file3.close();
				login_details();
			}
			else
			{
				cout<<endl<<"\t\t\tUsername or password does not match.";
				cout<<endl<<endl<<"\t\t\tDo you want to try again?";
				cout<<endl<<"\t\t\tPress 'Y' to continue or 'N' to exit : ";
				cin>>ch;
				tolower(ch);
				if(ch=='y')
				{
					goto call;
				}
				else
				{
					exit(0);
				}
			}
 		}
		file2.close();
}*/
