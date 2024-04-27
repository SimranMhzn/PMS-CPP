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
		string plateNo;
		char userName[30];
		int hr,min;
		int row,column;
	public:
		void setVehicledata();
		void readVehicledata();
		void calculateTime(int,int);
		void removeData(string);
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
	char key;
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
			cout<<"\t\t\tEnter any key to exit: ";
			cin>>key;
			if(key!=0)
			{
				break;
			}
		default:
			cout<<"\n\t\t\t\tInvalid Input!";
			sleep(1);
			goto flag;
	}
	system("cls");
	adminControl();
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
		file2.open("adminLogin.txt",ios::in);
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
				file3.open("adminLogin.txt",ios::out);
				if(!file3)
				{
					cout<<endl<<"\t\t\tNo such file.";
				}
				file3<<username<<" "<<newpw;
				cout<<endl<<"\t\t\tPassword changed successfully."<<endl;
				cout<<endl<<endl<<"\t\t\t\tPlease wait....";
				sleep(1);
				file3.close();
				adminLogin();
			}
			else
			{
				int option;
				cout<<endl<<"\t\t\tUsername or password does not match.";
				cout<<endl<<"\t\t\tInvalid Username or Password! ";
				fflush(stdin);
				cout<<endl<<"\t\t\t1. Try again ";
				cout<<endl<<"\t\t\t2. Change with security key ";
				cout<<endl<<endl<<"\t\t\tPlease enter your choice: ";
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
							file.open("adminLogin.txt",ios::out);
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
							adminLogin();
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
	reserveRead();
	cout<<endl<<endl<<"\t\t\tWhere do you want to park your vehicle?";
	flow:
		cout<<endl<<"\t\t\tEnter row and column: ";
		cin>>row>>column;
		if(row>5||column>8)
		{
			cout<<endl<<"\t\t\tInvalid input.";
			cout<<endl<<"\t\t\tPlease enter valid input.";
			goto flow;
		}
		fstream read;
		int num[5][8];
		read.open("reserved.txt",ios::in);
		while (!read.eof()) {
    		for (int x = 0; x < 5; x++) {
      	    	for (int y = 0; y < 8; y++) {
            		if (!(read >> num[x][y])) {
                		break;
            		}
            		if(num[x][y]==1)
            		{
            			if(row==x&&column==y)
            			{
            				cout<<endl<<"\t\t\t The selected slot is already reserved. Please try again!";
            				goto flow;
						}
					}
        		}
   			}	
		}
		read.close();
		reserveWrite(row-1,column-1);
	Vehicles writingObject,readingObject;
	cout<<endl<<"\t\t\tEnter details: ";
	again:
	cout<<endl<<"\t\t\t\tPlate number: ";
	cin>>writingObject.plateNo;
	fstream dataFile;
	dataFile.open("data.txt",ios::in);
	if(!dataFile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	while(dataFile.read(reinterpret_cast<char*>(&readingObject), sizeof(readingObject)));
	{
		if(readingObject.plateNo==writingObject.plateNo)
		{
			cout<<endl<<"\t\t\tThe vehicle with same plate no already exist. Please enter carefully!";
			goto again;
		}
	}
	dataFile.close();
	cout<<endl<<"\t\t\t\tName: ";
	cin.ignore();
    cin.getline(writingObject.userName, 30);
    cout<<endl<<"\t\t\t\tPresent time: ";
    cout<<endl<<"\t\t\t\tHour: ";
	cin>>writingObject.hr;
	cout<<endl<<"\t\t\t\tMinute: ";
	cin>>writingObject.min;
	fstream data;
	data.open("data.txt",ios::app);
	if(!data)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	data.write((char *) & writingObject, sizeof(writingObject));
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
	data.close();
}

void Vehicles::readVehicledata()
{
	Vehicles readingObject;
	char ch=0;
	string detailsCheck;
	re:
	cout<<endl<<"\t\t\t\tEnter number of vehile you want the details of: ";
	cin>>detailsCheck;
	fstream dataFile;
	dataFile.open("data.txt",ios::in);
	if(!dataFile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	while(dataFile.read(reinterpret_cast<char*>(&readingObject), sizeof(readingObject)))
	{
		if(readingObject.plateNo==detailsCheck)
		{
			calculateTime(readingObject.hr,readingObject.min);
			cout<<endl<<"\t\t\tPlate no: "<<readingObject.plateNo;
			cout<<endl<<"\t\t\tUser name: "<<readingObject.userName;
			cout<<endl<<endl<<"\t\t\tHappy Parking!";
			cout<<endl<<"\t\tPlease enter any key to exit the page!";
			cin>>ch;
			if(ch!=0)
			{
				exit(0);
			}
		}
		else
		{
			cout<<endl<<"\t\t\t Error finding the details! Please enter valid number plate! ";
			dataFile.close();
			goto re;
		}
	}
	readingObject.removeData(detailsCheck);
	dataFile.close();
}

void Vehicles::calculateTime(int x,int y)
{
	int h,m;
	cout<<endl<<"\t\t\tEnter the present time: ";
	cout<<endl<<"\t\t\tHours: ";
	cin>>h;
	cout<<endl<<"\t\t\tMinutes: ";
	cin>>m;
	int totalMin1=(x*60)+y;
	int totalMin2=(h*60)+m;
	int diff=totalMin2-totalMin1;
	int hour=diff/60;
	int min=diff%60;
	float price=hour*50+min*0.8;
	cout<<endl<<endl<<"\t\t\tTotal price: "<<abs(price);
	cout<<endl<<"\t\t\tTotal hour parked: "<<hour;
	cout<<endl<<"\t\t\tTotal minutes parked: "<<min;
	cout<<endl<<endl<<"\t\t\tNote: Price per hour= Rs 50";
}

void Vehicles::removeData(string option) {
    const int ROWS = 5;
    const int COLS = 8;
    Vehicles temp;
    int x,y;
    int num[ROWS][COLS] = {};
    ofstream writing;
	writing.open("reserved.txt",ios::out);
    ifstream reading;
	reading.open("data.txt", ios::in);
    if (!reading.is_open()) {
        cout << "Error: Failed to open file 'reserved.txt' for reading." << endl;
        exit(1);
    }
    else {
        while(reading.read(reinterpret_cast<char*>(&temp), sizeof(temp)))
		{
			if(temp.plateNo!=option)
			{
    			writing.write(reinterpret_cast<char*>(&temp), sizeof(temp));
			}
		}
		writing.close();
    	reading.close();
    	if (remove("data.txt") != 0) {
        	cout << endl << "\t\t\tError: Failed to remove file 'data.txt'." << endl;
    	}
    	if (rename("tempo.txt", "data.txt") != 0) {
        	cout << endl << "\t\t\tError: Failed to rename file 'tempo.txt' to 'data.txt'." << endl;
    	}
    }
}

void displayMenu()
{
	//object of vehicle class 
	Vehicles selection;
	int option;
	char ch=0;
	flag:
		system("cls"); 
		cout<<endl<<"\t\t\t\t1. Vehicle entry ";
		cout<<endl<<"\t\t\t\t2. Bill generation ";
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
				cout<<endl<<"\t\t\t\t\t\t\t\tDetails:"<<endl<<endl;
				reserveRead();
				cout<<endl<<"\t\t\tEnter any key to exit: ";
				cin>>ch;
				if(ch!=0)
				{
					displayMenu();
				}
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
	fstream reservedFile;
	int num[5][8];
	reservedFile.open("reserved.txt",ios::in);
	while (!reservedFile.eof()) {
    	for (int x = 0; x < 5; x++) {
      	    for (int y = 0; y < 8; y++) {
            	if (!(reservedFile >> num[x][y])) {
                	break;
            	}
            	cout<<"\t\t"<< num[x][y];
        	}
        cout << endl;
   		}	
	}
}

void reserveWrite(int num1, int num2) {
    const int ROWS = 5;
    const int COLS = 8;
    int num[ROWS][COLS] = {};

    ifstream read("reserved.txt", ios::in);
    if (!read.is_open()) {
        cout << "Error: Failed to open file 'reserved.txt' for reading." << endl;
        exit(1);
    }
    else {
        for (int x = 0; x < ROWS; x++) {
            for (int y = 0; y < COLS; y++) {
                if (!(read >> num[x][y])) {
                    break;
                }
            }
        }
    }
    read.close();

    if (num1 >= 0 && num1 < ROWS && num2 >= 0 && num2 < COLS) {
        num[num1][num2] = 1;
    }
    else {
        cout << endl << "\t\t\tError: Invalid array indices provided." << endl;
        return;
    }

    ofstream reservedFile("reserved.txt");
    if (!reservedFile.is_open()) {
        cout << endl << "\t\t\tError: Failed to open file 'reserved.txt' for writing." << endl;
        return;
    }

    for (int k = 0; k < ROWS; k++) {
        for (int l = 0; l < COLS; l++) {
            reservedFile << num[k][l] << " ";
        }
        reservedFile << endl;
    }

    reservedFile.close();
    cout << endl << "\t\t\tData written to file successfully." << endl;
}
