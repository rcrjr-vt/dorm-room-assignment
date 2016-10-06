#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct STUDENT
{
	string first;
	string last;
	bool gender;
};

struct ROOM
{
	STUDENT resident1;
	STUDENT	resident2;
	int vacant;
};

struct VINCENT
{
	ROOM dorm[3][20];
	int floor1;
	int floor2;
	int floor3;
	
	void Init ();
	bool RoomVacant (int roomNum);

	void AssignStudent();
	void LocateStudent();
	void RemoveStudent();
	void DisplayFloor ();
};

void VINCENT::Init()
{
	int i, j;
	floor1 = 40;
	floor2 = 40;
	floor3 = 40;
	for(i=0; i < 3; i++)
	{
		for(j = 0; j < 20; j++)
		{
			dorm[i][j].vacant = 2;
			dorm[i][j].resident1.last="Empty";
			dorm[i][j].resident1.first=" ";
			dorm[i][j].resident2.last="Empty";
			dorm[i][j].resident2.first=" ";
		}
	}
}

bool VINCENT::RoomVacant (int roomNum)
{
	int floor;
	int room;
	floor = (roomNum / 100) - 1;
	room = roomNum % 100;
	return(dorm[floor][room].vacant);			//Returns true if the room is vacant, false otherwise
}

int DisplayMenu ()//function to displaying menu
{
	int returnvalue=0;
	while (returnvalue < 1 || returnvalue > 5)
	{
		cout<<"Enter your selection (1-5)"<<endl;
		cout<<"1. Assign Student"<<endl;
		cout<<"2. Locate Student"<<endl;
		cout<<"3. Remove Student"<<endl;
		cout<<"4. Display Floor"<<endl;
		cout<<"5. EXIT"<<endl;
		cin>>returnvalue;
		if (returnvalue<1||returnvalue>5)
		{
			cout<<"Invalid selection!"<<endl;
		}
	}
	return returnvalue;
}
void VINCENT::AssignStudent()
{
	string first, last, gender, request;
	int roomNum, floor, room, i,j;
	bool sex;
	bool assigned = false;
	
	cout<<"1. Assign Student"<<endl;
	cout<<"Enter first name."<<endl;
	cin>>first;
	cout<<"Enter last name."<<endl;
	cin>>last;
	cout<<"Enter gender. (m/f)"<<endl;
	cin>>gender;
	if(gender == "m" || gender == "M")
	{
		if(floor1 == 0 && floor3 == 0)
		{
			cout<<"No more room for male students!"<<endl;
			return;
		}
		else
			sex = 1;
	}
	else if(gender == "f" || gender == "F")
	{
		if(floor2 == 0)
		{
			cout<<"No more room for female students!"<<endl;
			return;
		}
		else
			sex = 0;
	}

	cout<<"Is there a room request? (y/n)"<<endl;
	cin>>request;
	if(request == "y" || request == "Y")					//Attempt to fulfill room request
	{
		while(!assigned)
		{
			cout<<"What room number? ";
			cin>>roomNum;
			if(RoomVacant(roomNum))						//If there is a vacancy in the selected room
			{
				floor = (roomNum / 100) - 1;					//Convert the room request to array indices
				room = roomNum % 100;
				if(((gender == "m" || gender == "M") && (floor == 0 || floor == 2))||	//Make sure gender and floor match
					((gender == "f" || gender == "F") && (floor == 1))) 
				{	
					if(dorm[floor][room].vacant == 2)				//Room has two vacancies, fill first space
					{
						dorm[floor][room].resident1.first = first;
						dorm[floor][room].resident1.last = last;
						dorm[floor][room].resident1.gender = sex;
						dorm[floor][room].vacant--;
					}
					else if(dorm[floor][room].vacant == 1)			//Room has one vacancy, fill second space
					{
						dorm[floor][room].resident2.first = first;
						dorm[floor][room].resident2.last = last;
						dorm[floor][room].resident2.gender = sex;
						dorm[floor][room].vacant--;
					}
					assigned = true;
					if(floor == 0)
						floor1--;
					else if(floor == 1)
						floor2--;
					else if(floor == 2)
						floor3--;
					//Give them the room
				}
				else
				{
					cout<<"Unavailable to your gender!!"<<endl;		//Gender and floor don't match
				}
			}
			else
			{
				cout<<"Room occupied"<<endl;					//Requested room has been filled
			}
		}

	}
	else//If no request is made, or if request is invalid, assign first available room
	{
		if(gender == "m" || gender == "M")
		{
			for (i=0; i<3 && !assigned; i+=2)
			{
				for (j=0; j<20 && !assigned; j++)
				{
					if (dorm[i][j].vacant==2)
					{
						dorm[i][j].resident1.first = first;
						dorm[i][j].resident1.last = last;
						dorm[i][j].resident1.gender = sex;
						dorm[i][j].vacant--;
						assigned=true;
					}
					else if (dorm[i][j].vacant==1)
					{
						dorm[i][j].resident2.first = first;
						dorm[i][j].resident2.last = last;
						dorm[i][j].resident2.gender = sex;
						dorm[i][j].vacant--;
						assigned=true;
					}
				}
			}
		}
		else if (gender == "f" || gender == "F")
		{
			i = 1;
			for (j=0; j<20 && !assigned; j++)
			{
				if (dorm[i][j].vacant==2)
				{
					dorm[i][j].resident1.first = first;
					dorm[i][j].resident1.last = last;
					dorm[i][j].resident1.gender = sex;
					dorm[i][j].vacant--;
					assigned=true;
				}
				else if (dorm[i][j].vacant==1)
				{
					dorm[i][j].resident2.first = first;
					dorm[i][j].resident2.last = last;
					dorm[i][j].resident2.gender = sex;
					dorm[i][j].vacant--;
					assigned=true;
				}
			}
		}
		if(i == 0)
			floor1--;
		else if(i == 1)
			floor2--;
		else if(i == 2)
			floor3--;
	}
}

void VINCENT::LocateStudent()
{
	string first, last;
	int i, j, roomNum;
	bool found = false;
	cout<<"2. Locate Student"<<endl;
	cout<<"Enter first name."<<endl;
	cin>>first;
	cout<<"Enter last name."<<endl;
	cin>>last;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 20; j++)
		{
			if(dorm[i][j].resident1.first == first && dorm[i][j].resident1.last == last)
			{
				roomNum = 100*(i+1) + j;
				found = true;
			}
			else if(dorm[i][j].resident2.first == first && dorm[i][j].resident2.last == last)
			{
				roomNum = 100 * (i+1) +j;
				found = true;
			}
		}
	}
	if(found)
		cout<<"Student "<<first<<" "<<last<<" was found in room "<<roomNum<<endl;
	else
		cout<<"Student not found!"<<endl;

}

void VINCENT::RemoveStudent()
{
	cout<<"3. Remove Student"<<endl;

	string first, last;
	int i, j, roomNum;
	bool found = false;

	cout<<"Enter first name."<<endl;
	cin>>first;
	cout<<"Enter last name."<<endl;
	cin>>last;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 20; j++)
		{
			if(dorm[i][j].resident1.first == first && dorm[i][j].resident1.last == last)
			{
				roomNum = 100*(i+1) + j;
				found = true;
				dorm[i][j].resident1.last = "Empty";
				dorm[i][j].resident1.first = " ";
				dorm[i][j].vacant++;
				if(i == 0)
					floor1--;
				else if(i == 1)
					floor2--;
				else if(i == 2)
					floor3--;
			}
			else if(dorm[i][j].resident2.first == first && dorm[i][j].resident2.last == last)
			{
				roomNum = 100*(i+1) + j;
				found = true;
				dorm[i][j].resident2.last = "Empty";
				dorm[i][j].resident2.first = " ";
				dorm[i][j].vacant++;
				if(i == 0)
					floor1--;
				else if(i == 1)
					floor2--;
				else if(i == 2)
					floor3--;
			}

		}
	}

	if(found)
		cout<<"Student "<<first<<" "<<last<<" was removed from room "<<roomNum<<endl;
	else
		cout<<"Student not found!"<<endl;
}

void VINCENT::DisplayFloor()
{
	int floor, i;
	cout<<"4. Display Floor"<<endl;
	cout<<"Pick a floor for display 1-3."<<endl;
	cin>>floor;
	floor--;
	for (i=0; i<71; i++)//adds top line for table
	{
		cout<<"_";
	}
	cout<<endl;
	cout<<"|";
	for (i=0; i<20; i+=2)//displays even floor numbers
	{
		cout<<setw(6)<<(floor+1)*100+i<<"|";
	}
	cout<<endl;
	cout<<"|";
	for (i=0; i<20; i+=2)//display resident1s last name within the even rooms
	{
		cout<<setw(5)<<dorm[floor][i].resident1.last.substr(0,5)<<","; 
		cout<<"|";
	}
	cout<<endl;
	cout<<"|";
	for (i=0; i<20; i+=2)//display resident1s first name within the even rooms
	{
		cout<<setw(6)<<dorm[floor][i].resident1.first.substr(0,6); 
		cout<<"|";
	}
	cout<<endl;
		cout<<"|";
	for (i=0; i<20; i+=2)//display resident2s last name within the even rooms
	{
		cout<<setw(5)<<dorm[floor][i].resident2.last.substr(0,5)<<","; 
		cout<<"|";
	}
	cout<<endl;
	cout<<"|";
	for (i=0; i<20; i+=2)//display resident2s first name within the even rooms
	{
		cout<<setw(6)<<dorm[floor][i].resident2.first.substr(0,6); 
		cout<<"|";
	}
	cout<<endl;
	for (i=0; i<71; i++)//displays divider between rooms
	{
		cout<<"_";
	}
	cout<<endl;
	cout<<"|";
	for (i=1; i<20; i+=2)//displays odd room numbers
	{
		cout<<setw(6)<<(floor+1)*100+i<<"|";
	}
	cout<<endl;
	cout<<"|";

	for (i=1; i<20; i+=2)//display resident1s last name within the odd rooms
	{
		cout<<setw(5)<<dorm[floor][i].resident1.last.substr(0,5)<<","; 
		cout<<"|";
	}
	cout<<endl;
	cout<<"|";
	for (i=1; i<20; i+=2)//display resident1s first name within the odd rooms
	{
		cout<<setw(6)<<dorm[floor][i].resident1.first.substr(0,6); 
		cout<<"|";
	}
	cout<<endl;
	cout<<"|";
	for (i=1; i<20; i+=2)//display resident2s last name within the odd rooms
	{
		cout<<setw(5)<<dorm[floor][i].resident2.last.substr(0,5)<<","; 
		cout<<"|";
	}
	cout<<endl;
	cout<<"|";
	for (i=1; i<20; i+=2)//display resident2s first name within the odd rooms
	{
		cout<<setw(6)<<dorm[floor][i].resident2.first.substr(0,6); 
		cout<<"|";
	}
	cout<<endl;
	for (i=0; i<71; i++)//displays bottom line of table
	{
		cout<<"_";
	}
	cout<<endl;
}
int main()
{
	int choice; 
	VINCENT Hall;
	Hall.Init();

	choice = DisplayMenu();

	while (choice != 5)
	{
		switch (choice)
		{
		case 1:
			Hall.AssignStudent();
			break;
		case 2:
			Hall.LocateStudent();
			break;
		case 3:
			Hall.RemoveStudent();
			break;
		case 4:
			Hall.DisplayFloor();
			break;
		case 5:
			exit(0);
			break;
		}
		cout<<endl;
		choice=DisplayMenu();
	}
	return 0;
}





