#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
using namespace std;
void displayMenu();
void reserveRead();
void reserveWrite(int,int);
int a[5][8];

class Password{
		protected:
			string username,password;
			string newpw;
			string un,pw;
			char ch;
		public:
			void loginMenu();
			void resetPw();
			void adminLogin();
			void adminControl();
			void loginDetails();		
};

class Vehicles{
	public:
		int plateNo;
		char userName[30];
		int row;
		int column;
	public:
		void setVehicledata();
		void readVehicledata();
};

int main()
{
	Password obj;
	obj.loginMenu();
	displayMenu();
	return 0;
}

void Password::loginMenu()
{
	int choice;
	flag:
	system("cls");
	cout<<endl<<"\t\t-------------------MENU-----------------"<<endl;
	cout<<endl<<"\t\t\t\t1. Admin Control";
	cout<<endl<<"\t\t\t\t2. Login";
	cout<<endl<<endl<<"\t\t\tEnter your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			adminLogin();
			break;
		case 2:
			loginDetails();
			break;
		default:
			goto flag;
	}
}

void Password::adminLogin()
{
	ifstream adminfile;
	string adminun,adminpw;
	retry:
	system("cls");
	cout<<endl<<"\t\t************WELCOME TO ADMIN LOGIN PAGE************"<<endl;
	fflush(stdin);
	cout<<endl<<"\t\t\tEnter your username: ";
	getline(cin,adminun);
	cout<<endl<<"\t\t\tEnter your password: ";
	getline(cin,adminpw);
	adminfile.open("adminLogin.txt",ios::in);
	if(!adminfile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	
	while(adminfile>>username>>password)
	{
		if(username==adminun && password==adminpw)
		{
			adminControl();
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
				adminfile.close();
				goto retry;
			}
			else 
			{
				loginMenu();
			}
		}
	}
	adminfile.close();
}

void Password::adminControl()
{
	system("cls");
	int choice;
	flag:
	cout<<endl<<"\t\t-------------------MENU-----------------"<<endl;
	cout<<endl<<"\t\t\t\t1. Reset password ";
	cout<<endl<<"\t\t\t\t2. View Reserved Slots Details ";
	cout<<endl<<endl<<"\t\t\tEnter your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			resetPw();
			break;
		case 2:
			reserveRead();
		default:
			cout<<"\n\t\t\t\tInvalid Input!";
			sleep(1);
			goto flag;
	}
}

void Password::resetPw()
{
	call:
		system("cls");
		char ch;
		fstream file2,file3;
		cin.ignore();
		cout<<endl<<"\t\t\tVerification: ";
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
				file3<<username<<" "<<newpw;
				cout<<endl<<"\t\t\tPassword changed successfully."<<endl;
				cout<<endl<<endl<<"\t\t\t\tPlease wait....";
				sleep(1);
				file3.close();
				loginDetails();
			}
			else
			{
				int option;
				cout<<endl<<"\t\t\tUsername or password does not match.";
				cout<<endl<<"\t\t\tInvalid Username or Password! ";
				fflush(stdin);
				cout<<endl<<"\t\t\t1. Change with previous Password ";
				cout<<endl<<"\t\t\t2. Change with security key ";
				cin>>option;
				switch(option)
				{
					case 1:
						goto call;
					case 2:
						system("cls");
						string codeRetrived, codeGiven;
						fstream verify,temp,file;
						verify.open("securityKey.txt",ios::in);
						verify>>codeRetrived;
						cout<<endl<<"\t\t\tEnter the security key: ";
						cin>>codeGiven;
						if(codeRetrived==codeGiven)
						{
							cout<<endl<<"\t\t\tEnter new password: ";
							cin>>newpw;
							file.open("logindata.txt",ios::out);
							if(!file)
							{
								cout<<endl<<"\t\t\tNo such file.";
							}
							file<<username<<" "<<newpw;
							cout<<endl<<"\t\t\tPassword changed successfully."<<endl;
							cout<<endl<<endl<<"\t\t\t\tPlease wait....";
							sleep(1);
							file.close();
							verify.close();
							temp.close();
							loginDetails();
						}
						else
						{
							cout<<"\t\t\tInvalid Security Key!"<<endl;
							goto call;
						}
				}
			}
 		}
		file2.close();
}

void Password::loginDetails()
{
	retry:
	system("cls");
	fstream loginFile;
	cout<<endl<<"\t\t************WELCOME TO LOGIN PAGE************"<<endl;
	fflush(stdin);
	cout<<endl<<"\t\t\tEnter your username: ";
	getline(cin,un);
	cout<<endl<<"\t\t\tEnter your password: ";
	getline(cin,pw);
	loginFile.open("logindata.txt",ios::in);
	if(!loginFile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	
	while(loginFile>>username>>password)
	{
		if(username==un && password==pw)
		{
			cout<<endl<<"\t\t\t\tLogging in......";
			cout<<endl<<"\t\t\t\tLog in successful......";
			sleep(1);
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
				loginFile.close();
				goto retry;
			}
			else 
			{
				loginMenu();
			}
		}
	}
	loginFile.close();
}

void Vehicles::setVehicledata()
{
	char ch;
	int row,column;
	cout<<endl<<"\t\t\t\t**********PARKING SLOTS**********"<<endl;
	//reserveRead();
	cout<<endl<<endl<<"\t\t\tWhere do you want to park your vehicle?";
	flow:
		cout<<endl<<"\t\t\tEnter row and column: ";
		cin>>row>>column;
		if(row>=5||column>=8)
		{
			cout<<endl<<"\t\t\tInvalid input.";
			cout<<endl<<"\t\t\tPlease enter valid input.";
			goto flow;
		}
		reserveWrite(row-1,column-1);
	Vehicles writingObject;
	cout<<endl<<"\t\t\tEnter details: ";
	cout<<endl<<"\t\t\t\tPlate number: ";
	cin>>writingObject.plateNo;
	cout<<endl<<"\t\t\t\tName: ";
	cin.ignore();
    cin.getline(writingObject.userName, 30);
	fstream dataFile;
	dataFile.open("data.txt",ios::app);
	if(!dataFile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	dataFile.write((char *) & writingObject, sizeof(writingObject));
	cout<<endl<<endl<<"\t\t\tYour vehicle has been parked successfully.";
	cout<<endl<<"\t\t\t\t\tThank You.";
	cout<<endl<<endl<<"\t\t\tDo you want to park another vehicle?";
	cout<<endl<<"\t\t\tPress 'Y' to continue or 'N' to exit : ";
	cin>>ch;
	tolower(ch);
	if(ch=='y')
	{
		dataFile.close();
		goto flow;
	}
	dataFile.close();
}

void Vehicles::readVehicledata()
{
	Vehicles readingObject;
	int detailsCheck;
	fstream dataFile;
	dataFile.open("data.txt",ios::in);
	if(!dataFile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	cout<<endl<<"\t\t\t\tEnter number of vehile you want the details of: ";
	cin>>detailsCheck;
	while(dataFile.read(reinterpret_cast<char*>(&readingObject), sizeof(readingObject)));
	{
		if(readingObject.plateNo==detailsCheck)
		{
			cout<<endl<<"\t\t\tPlate no: "<<readingObject.plateNo;
			cout<<endl<<"\t\t\tUser name: "<<readingObject.userName;
			sleep(1);
		}
	}
	dataFile.close();
}

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
		cout<<endl<<"\t\t\t\t4. Exit";
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
				//selection.reserveSlot();
				break;
			case 4:
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

void reserveRead()
{
	ifstream reservedFile;
	int num[5][8];
	reservedFile.open("reserved.txt",ios::in);
	while (!reservedFile.eof()) {
    	for (int x = 0; x < 5; x++) {
      	    for (int y = 0; y < 8; y++) {
            	if (!(reservedFile >> num[x][y])) {
                	// Handle if reading fails (e.g., end of file reached prematurely)
                	break;
            	}
            cout << "\t" << num[x][y] << "\t\t";
        	}
        cout << endl;
   		}	
	}
}

void reserveWrite(int num1,int num2)
{
	fstream reservedFile;
	reservedFile.open("reserved.txt",ios::out);
	for(int k=0;k<5;k++)
	{
		for(int l=0;l<8;l++)
		{
			if(k==num1&&l==num2)
			{
				a[k][l]==1;
			}
			reservedFile<<a[k][l]<<" ";
		}
		reservedFile<<endl;
	}
	reservedFile.close();
}
