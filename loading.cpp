
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
using namespace std;
void loading ();
int main()
{
	loading();
	return 0;
}
 void loading(){
    int load;
    int loadingTime = 100000; 
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t";
    cout<<"Loading";
    for (load = 0; load < 10; load++) 
	{
        cout<<".";
        fflush(stdout); 
		usleep(loadingTime); 
    }
    system("cls");
}