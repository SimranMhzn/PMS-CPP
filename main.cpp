#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sstream>
int num[5][8];

using namespace std;
void displayMenu();
void reserveRead();
void reserveWrite(int,int);

class Password{
		protected:
			string username,password;
			string newpw;
			string un,pw;
			char ch;
		public:
			void resetPw();
			int resetOption();
			void adminLogin();
			void adminControl();
			void loginDetails();
			void loginMenu();	
};

class Vehicles{
	public:
		int plateNo;
		string userName;
		int hr,min;
		int row,column;
	public:
		void setVehicledata();
		int checkReserved(int,int);
		void generateData();
		int checkPlateno(int);
		void calculateTime(int,int);
		void removeData(int);
		void removeSlot(int);
};

int main()
{
	Password obj;
	obj.loginMenu();
	displayMenu();
	return 0;
}

void Password::loginMenu()//main menu
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
		ifstream file2;
		ofstream file3;
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
				cout<<endl<<"\t\t\tUsername or password does not match.";
				cout<<endl<<"\t\t\tInvalid Username or Password! ";
				int result=resetOption();
				if(result==1)
				{
					goto call;
				}
			}
 		}
		file2.close();
}

int Password::resetOption()
{
	int option;
	int flag=0;
	fflush(stdin);
	cout<<endl<<"\t\t\t1. Try again ";
	cout<<endl<<"\t\t\t2. Change with security key ";
	cout<<endl<<endl<<"\t\t\tPlease enter your choice: ";
	cin>>option;
	switch(option)
	{
		case 1:
			flag=1;
			return flag;
		case 2:
			system("cls");
			string codeRetrived, codeGiven;
			ifstream verify;
			ofstream file;
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
				adminLogin();
			}
			else
			{
				cout<<"\t\t\tInvalid Security Key!"<<endl;
				flag==1;
				return flag;
			}
	}
}

void Password::loginDetails()
{
	retry:
	system("cls");
	ifstream loginFile;
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

void displayMenu()//display menu after login
{
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
				selection.generateData();
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

void Vehicles:: setVehicledata()
{
	flow:
	char ch;
	system("cls");
	cout<<endl<<endl<<endl<<"\t\t\t\t\t\t\t**********PARKING SLOTS**********"<<endl<<endl;
	reserveRead();
			
		cout<<endl<<"\t\t\tWhere do you want to park your vehicle?";
		cout<<endl<<"\t\t\tEnter row and column(row<5 and column<8): ";
		cin>>row>>column;
		
		int result=checkReserved(row-1,column-1);
		if(result==1)
		{
			goto flow;
		}
		
	cout<<endl<<"\t\t\tEnter details: ";
	again:
		cout<<endl<<"\t\t\t\tPlate number: ";
		cin>>plateNo;
		int check=checkPlateno(plateNo);
		if(check==1)
		{
			goto again;
		}
		cout<<endl<<"\t\t\t\tName: ";
		cin.ignore();
    	getline(cin,userName );
    	cout<<endl<<"\t\t\t\tPresent time: ";
    	cout<<endl<<"\t\t\t\tHour: ";
		cin>>hr;
		cout<<endl<<"\t\t\t\tMinute: ";
		cin>>min;
		
	ofstream data;
	data.open("data.txt",ios::app);
	if(!data)
	{
		cout<<endl<<"\t\t\tNo such file";
		exit(0);
	}
	data << userName << ',' << " " << plateNo << " " << hr << " " << min <<" " << row << " "<< column <<endl;
	if(data.fail())
	{
		cout<<endl<<"\t\t\t Error writing to the file!";
		exit(0);
	}
	reserveWrite(row-1,column-1);
	data.close();
	cout<<endl<<"\t\t\t Data added successfully.";
	cout<<endl<<endl;
	
	cout<<"\t\t\t Do you want to add another movie?[Y/N] : ";
	cin>>ch;
	tolower(ch);
	if (ch=='y')
	{
		system("cls");
		goto flow;
	}
}

int Vehicles::checkReserved(int a,int b)
{
	bool exitLoop = false;
	int flag;
	ifstream read;
	read.open("reserved.txt",ios::in);
	while (!read.eof() && !exitLoop) {
    	for (int x = 0; x < 5; x++) {
        	for (int y = 0; y < 8; y++) {
            	if (!(read >> num[x][y])) {
                	exitLoop = true;
                	break;
            	}
            	if (num[x][y] == 1) {
                	if (a == x && b == y) {
                    	flag = 1;
                    	cout << endl << "\t\t\t The selected slot is already reserved. Please try again!";
                    	sleep(2);
                    	exitLoop = true; 
                    	break;
                	} 
					else {
                    	flag = 0;
                	}
            	}
        	}
        	if (exitLoop)
			{
				break; // Exit outer loop if flag is set
			}	
    	}
	return flag;
	read.close();
	}
}

int Vehicles::checkPlateno(int temp1)
{
	ifstream dataFile;
	int flag=0;
	dataFile.open("data.txt",ios::in);
	if(!dataFile)
	{
		cout<<endl<<"\t\t\tNo such file";
	}
	string line;
	while (getline(dataFile,line))
	{
		istringstream iss(line);
		if (getline(iss,userName,','))
		{
			if (iss>>plateNo>>hr>>min>>row>>column)
			{
				if(plateNo==temp1)
				{
					cout<<endl<<"\t\t\t The plate no "<<plateNo<<" is already in database.";
					flag=1;
				}
			}
		}
	}
	dataFile.close();
	return flag;
}

void reserveRead()
{
	ifstream reservedFile;
	reservedFile.open("reserved.txt",ios::in);
	while (!reservedFile.eof()) {
    	for (int x = 0; x < 5; x++) {
      	    for (int y = 0; y < 8; y++) {
            	if (!(reservedFile >> num[x][y])) {
                	break;
            	}
            	cout<<"\t\t"<< num[x][y];
        	}
        cout<<endl<<endl;
   		}	
	}
	reservedFile.close();
}

void reserveWrite(int num1, int num2) {
	int ROWS =5;
	int COLS =8;
	
	//reading the reserved slots
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

    if (num1 >= 0 && num1 < ROWS && num2 >= 0 && num2 < COLS) {
        num[num1][num2] = 1;
    }
    
	//writing the reserved slot with addition
    ofstream reservedFile("reserved.txt",ios::out);
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
    read.close();
    reservedFile.close();
}

void Vehicles::generateData() 
{
    Vehicles readingObject;
    char ch=0;
    int detailsCheck,found=0;
    cout << endl << "\t\t\t\tEnter number of vehicle you want the details of: ";
    cin >> detailsCheck;

	//reading the data of vehicles
    ifstream dataFile;
	dataFile.open("data.txt",ios::in);
    if (!dataFile) {
        cout << endl << "\t\t\tNo such file";
        exit(0);
    }
    string line;
	while (getline(dataFile,line))
	{
		istringstream iss(line);
		if (getline(iss,userName,','))
		{
			if (iss>>plateNo>>hr>>min>>row>>column)
			{
				if(plateNo==detailsCheck)
				{
					cout << endl << "\t\t\tPlate no: " <<plateNo;
            		cout << endl << "\t\t\tUser name: " <<userName;
            		calculateTime(hr,min);
            		cout << endl << endl << "\t\t\tHappy Parking!";
            		found=1;
            		break;
				}
			}
		}
	}
    dataFile.close();

	if(found==1)
	{
		removeSlot(detailsCheck);
		removeData(detailsCheck);
		cout<<endl<<"\t\t\tEnter any key to exit: ";
		cin>>ch;
		if(ch!=0)
		{
			displayMenu();
		}
	}
	else
	{
		cout<<endl<<"\t\t\t\tNo record found!";
	}
    
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
	float price=hour*30+min*0.5;
	cout<<endl<<endl<<"\t\t\tTotal price: "<<abs(price);
	cout<<endl<<"\t\t\tTotal hour parked: "<<hour;
	cout<<endl<<"\t\t\tTotal minutes parked: "<<min;
	cout<<endl<<endl<<"\t\t\tNote: Price per hour= Rs 30";
}

void Vehicles::removeSlot(int details)
{
	int a,b;
	ifstream rData;
	rData.open("data.txt",ios::in);
	if (!rData) {
        cout << endl << "\t\t\tNo such file";
        exit(0);
    }
    string line;
	while (getline(rData,line))
	{
		istringstream iss(line);
		if (getline(iss,userName,','))
		{
			if (iss>>plateNo>>hr>>min>>row>>column)
			{
				if (plateNo= details) 
				{
            		a=row;
            		b=column;
            		break;
        		}
			}
		}
	}

	cout<<endl<<endl<<"\t\t\tThe vehicle is parked in row: "<<a <<" and column: "<<b;
	ifstream temp1;
	ofstream temp2;
	
	temp1.open("reserved.txt",ios::in);
	if (!temp1.is_open()) {
        cout << "\t\t\tError: Failed to open file 'reserved.txt' for reading." << endl;
        exit(1);
    }
    else {
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 8; y++) {
                if (!(temp1 >> num[x][y])) {
                    break;
                }
            }
        }
    }
    for (int x = 0; x < 5; x++) 
	{
        for (int y = 0; y < 8; y++) 
		{
            if(a==x&&b==y)
            {
                num[a][b]=0;
			}
        }
    }
    
    temp2.open("temp.txt",ios::out);
    for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 8; l++) {
            temp2 << num[k][l] << " ";
        }
        temp2<< endl;
    }
    
    temp2.close();
    temp1.close();
    rData.close();
    remove("reserved.txt");
    rename("temp.txt", "reserved.txt");
}

void Vehicles::removeData(int option) 
{
    int check = 0;
    ofstream writing;
	writing.open("delete.txt", ios::out);
    ifstream reading;
	reading.open("data.txt", ios::in);

    if (!writing || !reading) {
        cout << "Error: Unable to open files." << endl;
        exit(0);
    }
	reading.seekg(0, ios::beg);
	string line;
	while (getline(reading,line))
	{
		istringstream iss(line);
		if (getline(iss,userName,','))
		{
			if (iss>>plateNo>>hr>>min>>row>>column)
			{
				if (plateNo==option) 
				{
            		check = 1;
        		}
        		else
        		{
					writing<< userName << ',' << " " << plateNo << " " << hr << " " << min <<" " << row << " "<< column <<endl;
				}
			}
		}
	}
    writing.close();
    reading.close();
    remove("data.txt");
    rename("delete.txt", "data.txt");

    if (check == 1) {
        cout << "\n\t\t\tRecord Deleted Successfully.";
    } 
	else {
        cout <<endl<<"t\t\t Record not found!!";
    }
    sleep(3);
}
