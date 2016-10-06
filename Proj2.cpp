//CS 1044 - Period 4
//May 1st, 2006
//Program File: Proj2.cpp
//Program to store, retrieve and display dormatory resident information

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct ROOM
{
	string first1;
	string last1;
	string first2;
	string last2;
	int number;
	void Set(string fir1, string sec1, string fir2, string sec2, int num);
	friend std::ostream& operator<<(std::ostream&, const ROOM &);
};

void assign_student(ROOM x[2][10],ROOM y[2][10],ROOM z[2][10]);
void locate_student(ROOM x[2][10],ROOM y[2][10],ROOM z[2][10]);
void remove_student(ROOM x[2][10],ROOM y[2][10],ROOM z[2][10]);
void display_array(ROOM x[2][10], int floorNum);

void main()
{
ROOM floor1[2][10];
ROOM floor2[2][10];
ROOM floor3[2][10];
int floorNum;

for(int i = 0; i < 2; i++) //Initial Setting of Room Assignment
	for(int j = 0; j < 10; j++)
	{	
		floor1[i][j].Set("Blank", "Blank", "Blank", "Blank", 0);	
	}

for(int i = 0; i < 2; i++)//Initial Setting of Room Assignment
	for(int j = 0; j < 10; j++)
	{	
		floor2[i][j].Set("Blank", "Blank", "Blank", "Blank", 0 );	
	}

for(int i = 0; i < 2; i++)//Initial Setting of Room Assignment
	for(int j = 0; j < 10; j++)
	{	
		floor3[i][j].Set("Blank", "Blank", "Blank", "Blank", 0);	
	}

int select = 0;

	while (select != 5)
	{
	cout<<endl;
	cout << "Welcome to Lupoli University" << endl;//Menu
	cout << "Vincent Hall Selection System" << endl;
	cout << " " << endl;
	cout << "1 - Assign a Student to a Room" << endl;
	cout << "2 - Locate a Student" << endl;
	cout << "3 - Remove a Student" << endl;
	cout << "4 - Display floor" << endl;
	cout << "5 - Quit Program" << endl;

	cin >> select;

	if (select == 1)//Determines Menu Selection
	{	assign_student(floor1, floor2, floor3);	}
	else if (select == 2)
	{	locate_student(floor1, floor2, floor3);	}
	else if (select == 3)
	{	remove_student(floor1, floor2, floor3);	}
	else if (select == 4) 
	{	
		cout<<"Which floor do you want to display?"<<endl;
		cin>>floorNum;
		if(floorNum == 1)
			display_array(floor1, floorNum);	
		else if(floorNum == 2)
			display_array(floor2, floorNum);	
		else if(floorNum == 3)
			display_array(floor3, floorNum);	
		else
			cout<<"Invalid floor selection!"<<endl;
	}

	}
}

void assign_student(ROOM x[2][10],ROOM y[2][10],ROOM z[2][10])
{
	int i, j, roomNum;
	int floor, num;
	char req;
	bool assigned = false;
	bool request = false;
	string fname, lname, sex;
cout << "Please enter the First Name of the Student ";
cin >> fname;
cout << "Please enter the Last Name of the Student ";
cin >> lname;
cout << "Please enter the sex of the student (M or F) ";
cin >> sex;
if(sex == "m" || sex == "M" || sex == "F" || sex == "f")//Determines if sex entered is actually M or F
{
cout << "Is there a room request? (Y/N) ";
cin >> req;
if(req == 'Y' || req == 'y')
	request = true;
	if(!request)
	{
		if (sex == "M" || sex == "m")
		{
			for(i = 0; i < 2 && !assigned; i++)//To assign to first available room
				for(j = 0; j < 10 && !assigned; j ++)//1st Floor (Male) Assignments
				{
					if(x[i][j].first1 == "Blank")
					{
						x[i][j].first1 = fname;
						x[i][j].last1 = lname;
						assigned = true;
					}
					else if(x[i][j].first2 == "Blank")
					{
						x[i][j].first2 = fname;
						x[i][j].last2 = lname;
						assigned = true;
					}
				}
			for(i = 0; i < 2 && !assigned; i++)//3rd Floor (Male) Assignments
				for(j = 0; j < 10 && !assigned; j ++)
				{
					if(z[i][j].first1 == "Blank")
					{
						z[i][j].first1 = fname;
						z[i][j].last1 = lname;
						assigned = true;
					}
					else if(z[i][j].first2 == "Blank")
					{
						z[i][j].first2 = fname;
						z[i][j].last2 = lname;
						assigned = true;
					}
				}
		}
		else if(sex == "F" || sex == "f")
		{
			for(i = 0; i < 2 && !assigned; i++)//2nd Floor (Female) Assignments
				for(j = 0; j < 10 && !assigned; j ++)
				{
					if(y[i][j].first1 == "Blank")
					{
						y[i][j].first1 = fname;
						y[i][j].last1 = lname;
						assigned = true;
					}
					else if(y[i][j].first2 == "Blank")
					{
						y[i][j].first2 = fname;
						y[i][j].last2 = lname;
						assigned = true;
					}
				}
		}
	}
	else
	{
		cout<<"What room would you like? ";
		cin>>roomNum;
		floor = roomNum/100;//Breaks room number to determine floor in matrix
		num = roomNum % 100;//Breaks room number to determine number on floor
		if(floor == 1 && (sex == "M" || sex == "m"))
		{
			if(x[num%2][num/2].first1 == "Blank")
			{
				x[num%2][num/2].first1 = fname;
				x[num%2][num/2].last1 = lname;
			}
			else if(x[num%2][num/2].first2 == "Blank")
			{
				x[num%2][num/2].first2 = fname;
				x[num%2][num/2].last2 = lname;
			}
			else
				cout<<"Sorry, room is already full";
		}

		else if(floor == 2 && (sex == "F" || sex == "f"))//Make sure gender is female
		{
			if(y[num%2][num/2].first1 == "Blank")
			{
				y[num%2][num/2].first1 = fname;
				y[num%2][num/2].last1 = lname;
			}
			else if(y[num%2][num/2].first2 == "Blank")
			{
				y[num%2][num/2].first2 = fname;
				y[num%2][num/2].last2 = lname;
			}
			else
				cout<<"Sorry, room is already full";
		}
		else if(floor == 3 && (sex == "M" || sex == "m"))
		{
			if(z[num%2][num/2].first1 == "Blank")
			{
				z[num%2][num/2].first1 = fname;
				z[num%2][num/2].last1 = lname;
			}
			else if(z[num%2][num/2].first2 == "Blank")
			{
				z[num%2][num/2].first2 = fname;
				z[num%2][num/2].last2 = lname;
			}
			else
				cout<<"Sorry, room is already full";
		}
		else if(((floor == 1 || floor == 3)&& (sex == "F" || sex == "f"))||(floor == 2 && (sex == "M" || sex == "m")))
		{
			cout<<"Sorry, that floor is unavailable to your gender"<<endl;
		}
	}
	}

else
	cout << "You did not enter a valid sex, please try again" << endl;//If user does not enter valid sex
}

void locate_student(ROOM x[2][10],ROOM y[2][10],ROOM z[2][10])
{
	string who1;
	string who2;
	bool found = false;
	cout << "Enter the First Name of who you are searching for ";
	cin >> who1;
	cout << "Enter the Last Name of who you are searching for ";
	cin >> who2;

	for(int i = 0; i < 2; i++)
	     for(int j = 0; j < 10; j++)
         {  
			 if (who1 == x[i][j].first1 && who2 == x[i][j].last1)
			 {
				 cout << "Found the Student!" << endl;
				 cout << " " << endl;
				 cout << "Located in:" << endl;
				 cout << "Floor: 1" << endl;
				 cout << "Room: " << 100+i+2*j << endl;
				 found = true;
			 }
			 else if (who1 == x[i][j].first2 && who2 == x[i][j].last2)
			 {
				 cout << "Found the Student!" << endl;
				 cout << " " << endl;
				 cout << "Located in:" << endl;
				 cout << "Floor: 1" << endl;
				 cout << "Room: " << 100+i+2*j << endl;
				 found = true;
			 }
			 else if (who1 == y[i][j].first1 && who2 == y[i][j].last1)
			 {
				 cout << "Found the Student!" << endl;
				 cout << " " << endl;
				 cout << "Located in:" << endl;
				 cout << "Floor: 2" << endl;
				 cout << "Room: " << 200+i+2*j << endl;
				 found = true;
			 }
			 else if (who1 == y[i][j].first2 && who2 == y[i][j].last2)
			 {
				 cout << "Found the Student!" << endl;
				 cout << " " << endl;
				 cout << "Located in:" << endl;
				 cout << "Floor: 2" << endl;
				 cout << "Room: " << 200+i+2*j << endl;
				 found = true;
			 }
			 else if (who1 == z[i][j].first1 && who2 == z[i][j].last1)
			 {
				 cout << "Found the Student!" << endl;
				 cout << " " << endl;
				 cout << "Located in:" << endl;
				 cout << "Floor: 3" << endl;
				 cout << "Room: " << 300+i+2*j << endl;
				 found = true;
			 }
			 else if (who1 == z[i][j].first2 && who2 == z[i][j].last2)
			 {
				 cout << "Found the Student!" << endl;
				 cout << " " << endl;
				 cout << "Located in:" << endl;
				 cout << "Floor: 3" << endl;
				 cout << "Room: " << 300+i+2*j << endl;
				 found = true;
			 }

		 }
	if(!found)
		cout<<"Student not found!"<<endl;
}

void remove_student(ROOM x[2][10],ROOM y[2][10],ROOM z[2][10])
{
	string who1;
	string who2;
	bool found = false;
	cout << "Enter the First Name of who you are searching for ";
	cin >> who1;
	cout << "Enter the Last Name of who you are searching for ";
	cin >> who2;

	for(int i = 0; i < 2; i++)
	     for(int j = 0; j < 10; j++)
         {  
			 if (who1 == x[i][j].first1 && who2 == x[i][j].last1)
			 {
				 cout << "Removed student "<<x[i][j].first1<<" "<<x[i][j].last1<<" from room "<<100+i+2*j<<endl;
				 x[i][j].first1 = x[i][j].first2;
				 x[i][j].last1 = x[i][j].last2;
				 x[i][j].first2 = "Blank";
				 x[i][j].last2 = "Blank";
				 found = true;
			 }
			 else if (who1 == x[i][j].first2 && who2 == x[i][j].last2)
			 {
				 cout << "Removed student "<<x[i][j].first2<<" "<<x[i][j].last2<<" from room "<<100+i+2*j<<endl;
				 x[i][j].first2 = "Blank";
				 x[i][j].last2 = "Blank";
				 found = true;
			 }
			 else if (who1 == y[i][j].first1 && who2 == y[i][j].last1)
			 {
				 cout << "Removed student "<<y[i][j].first1<<" "<<y[i][j].last1<<" from room "<<100+i+2*j<<endl;
				 y[i][j].first1 = y[i][j].first2;
				 y[i][j].last1 = y[i][j].last2;
				 y[i][j].first2 = "Blank";
				 y[i][j].last2 = "Blank";
				 found = true;
			 }
			 else if (who1 == y[i][j].first2 && who2 == y[i][j].last2)
			 {
				 cout << "Removed student "<<y[i][j].first2<<" "<<y[i][j].last2<<" from room "<<100+i+2*j<<endl;
				 y[i][j].first2 = "Blank";
				 y[i][j].last2 = "Blank";
				 found = true;
			 }
			 else if (who1 == z[i][j].first1 && who2 == z[i][j].last1)
			 {
				 cout << "Removed student "<<z[i][j].first1<<" "<<z[i][j].last1<<" from room "<<100+i+2*j<<endl;
				 z[i][j].first1 = z[i][j].first2;
				 z[i][j].last1 = z[i][j].last2;
				 z[i][j].first2 = "Blank";
				 z[i][j].last2 = "Blank";
				 found = true;
			 }
			 else if (who1 == z[i][j].first2 && who2 == z[i][j].last2)
			 {
				 cout << "Removed student "<<z[i][j].first2<<" "<<z[i][j].last2<<" from room "<<100+i+2*j<<endl;
				 z[i][j].first2 = "Blank";
				 z[i][j].last2 = "Blank";
				 found = true;
			 }

		 }
	if(!found)
		cout<<"Student not found!"<<endl;
}

void display_array(ROOM x[2][10], int floorNum)//Displays floor
{
	int count = 0;
	cout << "Floor "<<floorNum<< endl;
	for(int i = 0; i < 2; i++)
	{
		 cout<<"|";
	     for(int j = 0; j < 10; j++)
         {  
			 cout << setw(6)<<(floorNum*100)+count<<"|";
			 count+=2;
		 }
		 cout<<endl;
		 cout<<"|";
		 for(int j = 0; j < 10; j++)
         {  
			 cout << setw(6)<<x[i][j].first1.substr(0,6)<<"|";
		 }
		 cout<<endl;
		 cout<<"|";
		 for(int j = 0; j < 10; j++)
         {  
			 cout << setw(6)<<x[i][j].last1.substr(0,6)<<"|";
		 }
		 cout<<endl;
		 cout<<"|";
		 for(int j = 0; j < 10; j++)
         {  
			 cout << setw(6)<<x[i][j].first2.substr(0,6)<<"|";
		 }
		 cout<<endl;
		 cout<<"|";
		 for(int j = 0; j < 10; j++)
         {  
			 cout << setw(6)<<x[i][j].last2.substr(0,6)<<"|";
		 }
		 cout<<endl;
		 cout<<endl;
		 count = 1;
	}
	cout<<endl;
}

ostream& operator<<(std::ostream&out, const ROOM &obj)
{
	unsigned int i;





    return out;
}

void ROOM::Set(string fir1, string sec1, string fir2, string sec2, int num)
{
	first1 = fir1;
	last1 = sec1;
	first2 = fir2;
	last2 = sec2;
	number = num;
}
