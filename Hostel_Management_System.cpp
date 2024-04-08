#include <iostream>
#include <string>
using namespace std;


class Hostel{	
	public:
		
		int roomNo;	
		string cusName;
		string cusContact;
		string cusEmail;
		Hostel* next;
		
		Hostel(){}
		Hostel(int roomNo, string cusName, string cusContact, string cusEmail){
			this->roomNo=roomNo;
			this->cusName=cusName;
			this->cusContact=cusContact;
			this->cusEmail=cusEmail;
		}
	
};

class List{
	private:
		Hostel* head;
		
	public:
		
		List(void){
			head=NULL;
		}
		
		~List(void){
			Hostel* currHostel=head;
			Hostel* nextHostel=NULL;
			while(currHostel !=NULL){
				nextHostel=currHostel->next;
				delete currHostel;       
				currHostel=nextHostel;
			}
			head=NULL;
		}
		
		//check whether the linked list empty
		bool IsEmpty(){
			return head==NULL;
		} 
		
		//insert node, create sorted linked list
		Hostel* InsertHostel(int n, Hostel* h){
			int currIndex=0;
			Hostel* currHostel=head;
			Hostel* prevHostel=NULL;
			while(currHostel && n>currHostel->roomNo){
				prevHostel=currHostel;
				currHostel=currHostel->next;
				currIndex++;
			}
			Hostel* newHostel=new Hostel;		
			newHostel=h;
			
			if(currIndex==0){				
				newHostel->next=head;
				head=newHostel;
			}
			else{
				newHostel->next=prevHostel->next;		
				prevHostel->next=newHostel;
			}
			return newHostel;
		}
		
		//find a node (using room number)
		int FindHostel(double n){
			Hostel* currHostel=head;
			int currIndex=1;
			while(currHostel && currHostel->roomNo !=n){
				currHostel=currHostel->next;
				currIndex++;
			}
			if(currHostel)
				return currIndex;
			else 
				return 0;
		}
		
		//delete a node
		int DeleteHostel(int n){
			Hostel* prevHostel=NULL;
			Hostel* currHostel=head;
			int currIndex=1;
			while(currHostel && currHostel->roomNo !=n){
				prevHostel=currHostel;
				currHostel=currHostel->next;
				currIndex++;
			}
			if(currHostel){
				if(prevHostel){
					prevHostel->next=currHostel->next;
					delete currHostel;
				}
				else{
					head=currHostel->next;
					delete currHostel;
				}
				return currIndex;
			}
			return 0;	
		}
		
		//display the whole list
		void DisplayList(void){
			int num=0;
			Hostel* currHostel=head;
			
			while (currHostel != NULL){
				
				cout<<"Room #"<<num+1<<endl;
				cout<<"Room number\t\t\t: "<<currHostel->roomNo<<endl;
				cout<<"Resident's name\t\t\t: "<<currHostel->cusName<<endl;
				cout<<"Residents's contact number\t: "<<currHostel->cusContact<<endl;
				cout<<"Resident's email address\t: "<<currHostel->cusEmail<<endl<<endl;
				currHostel = currHostel->next;
				num++;
				
			}	
			
			//display the total number of room which is in-use
			cout << "Number of room in-use: " <<num<<endl;
		}
		
				
};

void adminMenu(){
	
	cout<<"1. Check availability of hostel room\n"<<
	      "2. Check residents' information\n"<<
	      "3. Add customer\n"<<
	      "4. Customer check out\n"<<
	      "5. Exit\n\n";
}

void customerMenu(){
	
	cout<<"1. Check availability of hostel room\n"
		<<"2. Exit\n\n";
	
}


int main(){
	
	List list;
	int role, adAction1, cusAction1;
	string name, contact, email;
	int roomNo;
	Hostel* h;
		
		cout<<"---WELCOME TO HOSTEL MANAGEMENT SYSTEM---\n";
		
	do{
	
		cout<<"\n==============================================\n"
			<<"1. Admin\n"
			<<"2. Customer\n\n"
			<<"Please choose your role => ";
		cin>>role;
		
		
		if(role==1){
				
				menu:
				
				cout<<endl;
				adminMenu();
				cout<<"Please choose an action ==> ";
				cin>>adAction1;	
				cout<<endl;
				
				//check room availability
				if(adAction1==1){
					
					cout<<"Enter the room no: ";
					cin>>roomNo;
					if(list.FindHostel(roomNo)==0)
					cout<<"No resident\n\n";
					else
					cout<<"There is resident in this room\n\n";
					
				}
				
				//check resident details (entire list)
				else if(adAction1==2){
					
					if(list.IsEmpty()==1)    //check if the list is empty
						cout<<"No customer can be displayed.\n";
					
					else
						list.DisplayList();
						
						 
				}
				
				//add customer
				else if(adAction1==3){
					
					cout<<"Enter the room no\t\t: ";
					cin>>roomNo;	
					cin.ignore();
					cout<<"Enter your name\t\t\t: ";
					getline(cin,name);
					cout<<"Enter your contact number\t: ";
					getline(cin,contact);
					cout<<"Enter your email address\t: ";
					getline(cin,email);
					cout<<endl;
					if(list.FindHostel(roomNo)==0){
					
						h=new Hostel(roomNo, name, contact, email);
						list.InsertHostel(roomNo,h);
						
					}
					else if(list.FindHostel(roomNo)!=0){
						
						cout<<"The room is not available for this moment.\n";
						
					}
					
				}
				
				//check out
				else if(adAction1==4){
					
					cout<<"Enter the room no: ";
					cin>>roomNo;
					if(list.FindHostel(roomNo)==0){
					
						cout<<"This room is empty.\n";
						
					}
					else if(list.FindHostel(roomNo)!=0){
						
						list.DeleteHostel(roomNo);
						cout<<"Successfully checked out!\n";
						
					}			
					
				}
				
				//exit
				else if(adAction1==5){
					
					cout<<"Thank you for using this system!";
				}
					
				else{
					
					cout<<"\nInvalid command\n\n";
					goto menu;
					
				}
					
		
	}
	
	else if(role==2){
		
			menu1:
				
			cout<<endl;
			customerMenu();
			cout<<"Please choose an action ==> ";
			cin>>cusAction1;	
			cout<<endl;
				
			//check room availability
			if(cusAction1==1){
					
				cout<<"Enter the room no: ";
				cin>>roomNo;
				if(list.FindHostel(roomNo)==0)
				cout<<"No resident\n\n";
				else
				cout<<"There is resident in this room\n\n";
					
			}
			
			//exit
			else if(cusAction1==2){
					
				cout<<"Thank you for using this system!";
					
			}
			
			else{
					
					cout<<"\nInvalid command\n\n";
					goto menu1;
					
			}
			
			
	}
			
	
	
	}while(adAction1!=5&&cusAction1!=2);
		
	return 0;
}







