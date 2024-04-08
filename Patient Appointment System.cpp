#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;


class User{
	public:
		string name;
		string id;
		string password;
	
		User *next;
	
		User(){};
		
		User(string name, string id, string password){
			this->name=name;
			this->id=id;
			this->password=password;
		}
		
};

class Admin:public User{
	private:
		int a_key;
		int key;

	public:
		string a_name;
		string a_id;
		string a_password;
	
		Admin* nextAdmin;
	
		Admin(){}
	
		Admin(string a_name, string a_id, string a_password):User(a_name, a_id, a_password){}
	
		void setKey(int a_key){
			this->a_key=a_key;
		}
	
		bool verifyKey(int key){
			if(key==a_key)
				return true;
			else 
				return false;
		}
};

class Patient:User{
	public:
		string p_name;
		string p_id;
		string p_password;
		string p_contactNo;
		string p_email;
		string apdoctor;
		
		Patient* nextPatient;
		
		Patient(){}
		Patient(string p_name, string p_id, string p_password):User(p_name, p_id, p_password){}
		Patient(string p_name, string p_id, string p_contactNo, string p_email, string apdoctor){
			this->p_name=p_name;
			this->p_id=p_id;
			this->p_contactNo=p_contactNo;
			this->p_email=p_email;
			this->apdoctor=apdoctor;
		}
			
};
class Access{
	public:
		User *backPtr, *frontPtr;
		//constructor
		Access(){
			backPtr=NULL;
			frontPtr=NULL;
		}
		
		//destructor
		~Access(){
			User *temp=frontPtr;
			while(temp){
				frontPtr=temp->next;
				delete temp;
				temp=frontPtr;
			}
		}
		//registration
		void registration(int role){
			
			ofstream outA;
			outA.open ("adminregistration.txt",ios::app);
			ofstream outP;
			outP.open ("patientregistration.txt",ios::app);
			
			string newname;
			string newid ;
			string newpassword;
			string newrole;
			
			cout<<"-REGISTRATION-\n"
				<<"Please fill in the information.\n";
			cout<<"Name: ";
			getline(cin,newname);
			cout<<"ID (Your IC Number): ";
			getline(cin,newid);
			cout<<"Password: ";
			getline(cin,newpassword);
					
			
			if(role==1){
				ifstream inp;
				inp.open("adminregistration.txt",ios::in);  //check if the id already existed in the system
				
				if (!inp.is_open()){
					cout<<"could not open file\n"; 
					system("pause");
            	}
            
            	string blankline;
            	string uid, unm, upw;
            	getline(inp,blankline);
            
            	getline(inp, uid, '\n');
           		getline(inp, unm, '\n');
				getline(inp, upw);
				User* u=new User(unm,uid, upw);
				u->next=NULL;
				frontPtr=backPtr=u;
			
            	while(!inp.eof()){
            		getline(inp, uid, '\n');
           	 		getline(inp, unm, '\n');
					getline(inp, upw);
					User* u=new User(unm, uid, upw);
					u->next=NULL;
					backPtr->next=u;
					backPtr=u;
				}
			
       			inp.close(); 
       			
       			User* currUser=frontPtr;
       			int currIndex=0;
       			
       			while(currUser&& currUser->id!=newid){
					currUser=currUser->next;
					currIndex++;
				}
				if(currUser){
					cout<<"ID existed in system. Register is not successful. \n";
				}
					
				else{
					
					
				
					if (!outA.is_open()){
            		cout<<"could not open file\n";
					system("pause"); 
        			}
        		
					outA<<"\n";
            		outA<<newid<<"\n";
            		outA<<newname<<"\n";
            		outA<<newpassword;
            		
            		cout<<"Successfully register!\n\n";
            		
            	}
			}
			
			else if(role==2){
				ifstream inp;
				inp.open("patientregistration.txt",ios::in);  //check if the id already existed in the system
				
				if (!inp.is_open()){
					cout<<"could not open file\n"; 
					system("pause");
            	}
            
            	string blankline;
            	string uid, unm, upw;
            	getline(inp,blankline);
            
            	getline(inp, uid, '\n');
           		getline(inp, unm, '\n');
				getline(inp, upw);
				User* u=new User(unm,uid, upw);
				u->next=NULL;
				frontPtr=backPtr=u;
			
            	while(!inp.eof()){
            		getline(inp, uid, '\n');
           	 		getline(inp, unm, '\n');
					getline(inp, upw);
					User* u=new User(unm, uid, upw);
					u->next=NULL;
					backPtr->next=u;
					backPtr=u;
				}
			
       			inp.close(); 
       			
       			User* currUser=frontPtr;
       			int currIndex=0;
       			
       			while(currUser&& currUser->id!=newid){
					currUser=currUser->next;
					currIndex++;
				}
				if(currUser){
					cout<<"ID existed in system. Register is not successful. \n";
				}
					
				else{
					
					if (!outP.is_open()){
            		cout<<"could not open file\n";
					system("pause"); 
        			}
        		
					outP<<"\n";
            		outP<<newid<<"\n";
            		outP<<newname<<"\n";
            		outP<<newpassword;
            		
            		cout<<"Successfully register!\n\n";
            		
           		}
			}
			
				outA.close();
				outP.close();
		}
		
		//admin login
		int adminlogin(){
			ifstream inp;
			inp.open ("adminregistration.txt",ios::in); 
			if (!inp.is_open()){
				cout<<"could not open file\n"; 
				system("pause");
            }
            
            string blankline;
            string uid, unm, upw;
            getline(inp,blankline);
            
            getline(inp, uid, '\n');
           	getline(inp, unm, '\n');
			getline(inp, upw);
			User* u=new User(unm,uid, upw);
			u->next=NULL;
			frontPtr=backPtr=u;
			
            while(!inp.eof()){
            	getline(inp, uid, '\n');
           	 	getline(inp, unm, '\n');
				getline(inp, upw);
				User* u=new User(unm, uid, upw);
				u->next=NULL;
				backPtr->next=u;
				backPtr=u;
			}
			
       		inp.close(); 
       		
       		string inId, inName, inPassword;
       		cout<<"-ADMIN LOGIN-\n"
				<<"Please fill in the information.\n";
			cout<<"Enter ID (Your I/c No): ";
			getline(cin, inId);
			cout<<"Enter Username: ";
            getline(cin, inName);
            cout<<"Enter Password: ";
            getline(cin, inPassword);
            
            User* input=new User(inName, inId, inPassword);
            
            User* currUser=frontPtr;
			int currIndex=1;
			while(currUser && currUser->id!=inId){
				currUser=currUser->next;
				currIndex++;
			}
			if(currUser){
				if(currUser->name==inName&&currUser->password==inPassword){
					return 1;
				}
				else if(currUser->name!=inName||currUser->password!=inPassword){
					return 2;
				}
			}
				
			else{
				return 3;
			}
		}
		
		//patient login
		int patientlogin(){
			ifstream inp;
			inp.open ("patientregistration.txt",ios::in); 
			if (!inp.is_open()){
				cout<<"could not open file\n"; 
				system("pause");
            }
            string blankline;
            string uid, unm, upw;
            getline(inp,blankline);
            
            getline(inp, uid, '\n');
           	getline(inp, unm, '\n');
			getline(inp, upw);
			User* u=new User(unm,uid, upw);
			u->next=NULL;
			frontPtr=backPtr=u;
			
            while(!inp.eof()){
            	getline(inp, uid, '\n');
           	 	getline(inp, unm, '\n');
				getline(inp, upw);
				User* u=new User(unm, uid, upw);
				u->next=NULL;
				backPtr->next=u;
				backPtr=u;
			}
			
       		inp.close(); 
       		
       		string inId, inName, inPassword;
       		
       		cout<<"-PATIENT LOGIN-\n"
				<<"Please fill in the information.\n";
			cout<<"Enter ID (Your I/c No): ";
			getline(cin, inId);
			cout<<"Enter Username: ";
            getline(cin, inName);
            cout<<"Enter Password: ";
            getline(cin, inPassword);
            
            User* input=new User(inName, inId, inPassword);
            
            User* currUser=frontPtr;
			int currIndex=1;
			while(currUser && currUser->id!=inId){
				currUser=currUser->next;
				currIndex++;
			}
			if(currUser){
				if(currUser->name==inName&&currUser->password==inPassword){
					return 1;
				}
				else if(currUser->name!=inName||currUser->password!=inPassword){
					return 2;
				}
			}
				
			else{
				return 3;
			}
		}
		
};

class Queue{
	public:
		Patient *backPtr, *frontPtr, *sorted;
		
		//constructor
		Queue(){
			backPtr=NULL;
			frontPtr=NULL;
		}
		
		//destructor
		~Queue(){
			Patient *temp=frontPtr;
			while(temp){
				frontPtr=temp->nextPatient;
				delete temp;
				temp=frontPtr;
			}
		}
		
		//check queue (if it is empty)
		bool isEmpty(){
			if(backPtr==NULL&&frontPtr==NULL){
				return true;
			}
			else
			return false;
		}
		
		//insert a patient
		void insertPatient(Patient *p){
			
			Patient* newPatient=new Patient;		
			newPatient=p;
			
			if(isEmpty()){
				newPatient->nextPatient=NULL;
				frontPtr=backPtr=newPatient;
			}
			else{
				newPatient->nextPatient=NULL;
				backPtr->nextPatient=newPatient;
				backPtr=newPatient;
			}
		}
			
		//delete first patient
		void completePatient(){
			
			Patient* currPatient=frontPtr;
				cout<<"Delete Customer Queue #1"<<"\n"
					<<"Patient name: "<<currPatient->p_name<<"\n"
					<<"Patient id: "<<currPatient->p_id<<"\n"
					<<"Patient contact number: "<<currPatient->p_contactNo<<"\n"
					<<"Patient email address: "<<currPatient->p_email<<"\n"
					<<"Patient appointment doctor: "<<currPatient->apdoctor<<"\n\n";
				
			Patient* tempPtr=NULL;
			tempPtr=frontPtr;
			frontPtr=frontPtr->nextPatient;
			tempPtr->nextPatient=NULL;
			delete tempPtr;
	
		}
		
		//delete patient in middle queue
		void cancelPatient(){
			
			Patient* currPatient = frontPtr;
			Patient* prevPatient = NULL;
			
			int currIndex = 1;
			string pIC;
			cout<<"Please enter your IC number:";
			getline(cin, pIC);
			
			while(currPatient && currPatient->p_id!=pIC){
				prevPatient = currPatient;
				currPatient=currPatient->nextPatient;
				currIndex++;
			}
			
			if(currPatient){
				if(prevPatient){
					prevPatient->nextPatient=currPatient->nextPatient;
					delete currPatient;
				}
				else{
					frontPtr = currPatient->nextPatient;
					delete currPatient;
				}
				
				cout<<"Successfully cancel your appoitment!\n\n";
			}
			
			else
			{
				cout<<"Your appoitment is not found.\n\n";
			}
		}
		
		//display the queue
		void display(void){
			if(isEmpty()){
				cout<<"No patient in the queue.\n";
			}
			
			else{
			int num=0;
			Patient* currPatient=frontPtr;
			while(currPatient!=NULL){
				cout<<"Queue #"<<num+1<<"\n"
					<<"Patient name: "<<currPatient->p_name<<"\n"
					<<"Patient id: "<<currPatient->p_id<<"\n"
					<<"Patient contact number: "<<currPatient->p_contactNo<<"\n"
					<<"Patient email address: "<<currPatient->p_email<<"\n"
					<<"Patient appointment doctor: "<<currPatient->apdoctor<<"\n\n";
				currPatient=currPatient->nextPatient;
				num++;
				}
			}
		}
		
		void checkTurn(){
			Patient* currPatient=frontPtr;
		
			int turn=1;
			string inIc;
			cout<<"Please enter your IC number:";
			getline(cin, inIc);
			
			while(currPatient && currPatient->p_id!=inIc){
				currPatient=currPatient->nextPatient;
				turn++;
			}
			if(currPatient)
				cout<<"There are "<<turn-1<<" patient(s) before your turn.\n\n";
			else 
				cout<<"Data not found. Please make an appointment.\n\n";
		}
		
		//search patient
		void searchPatient() {
			Patient* currPatient = frontPtr;
			string inIc;
			
			cout << "Please enter IC number of patient:";
			cin.ignore();
			getline(cin, inIc);
			cout << endl;
	
			while (currPatient && currPatient->p_id != inIc) {
				currPatient = currPatient->nextPatient;
			}
	
			if (currPatient) {
				cout << "-----Patient Info-----" << "\n"
					<< "Patient name: " << currPatient->p_name << "\n"
					<< "Patient id: " << currPatient->p_id << "\n"
					<< "Patient contact number: " << currPatient->p_contactNo << "\n"
					<< "Patient email address: " << currPatient->p_email << "\n"
					<< "Patient appointment doctor: " << currPatient->apdoctor << "\n\n";
			}
			else
				cout << "Data not found. Please make an appointment.\n\n";
		}
		
		void displaySorted(void){
			
			if(isEmpty()){
				cout<<"No patient in the queue.\n";
			}
			
			else{
			int num=0;
			Patient* currPatient=sorted;
			while(currPatient!=NULL){
				cout<<"Sorted #"<<num+1<<"\n"
					<<"Patient appointment doctor: "<<currPatient->apdoctor<<"\n"
					<<"Patient name: "<<currPatient->p_name<<"\n"
					<<"Patient id: "<<currPatient->p_id<<"\n"
					<<"Patient contact number: "<<currPatient->p_contactNo<<"\n"
					<<"Patient email address: "<<currPatient->p_email<<"\n"
					<<"\n\n";
				currPatient=currPatient->nextPatient;
				num++;
				}
			}
		}
		
		void insertionSort()
		{
			sorted = NULL;
			
			Patient* current = frontPtr;
			
			while (current != NULL) {
				
				Patient* next = current->nextPatient;
				sortedInsert(current);
				current = next;
			}
		}

		void sortedInsert(Patient* newnode)
		{
			Patient* temp = new Patient;
			temp->p_name = newnode->p_name;
			temp->p_id = newnode->p_id;
			temp->p_contactNo = newnode->p_contactNo;
			temp->p_email = newnode->p_email;
			temp->apdoctor = newnode->apdoctor;

			if (sorted == NULL || sorted->apdoctor >= temp->apdoctor) {
				temp->nextPatient = sorted;
				sorted = temp;
			}
			else {
				Patient* current = sorted;
				while (current->nextPatient != NULL
					&& current->nextPatient->apdoctor < temp->apdoctor) {
					current = current->nextPatient;
				}
				temp->nextPatient = current->nextPatient;
				current->nextPatient = temp;
			}
		}
};

void menu1(){
	cout<<"Choose Your Role\n"
		<<"1. Admin\n"
		<<"2. Patient\n"
		<<"3. Exit System\n"
		<<"Enter role: ";
}

void menu2(){
	cout<<"Choose Action\n"
		<<"1. Register\n"
		<<"2. Login\n"
		<<"Enter action: ";
}

void adminMenu(){
	cout<<"Choose Action\n"
		<<"1. Check Patient Queue List\n"
		<<"2. Complete Patient\n"  //when the first customer in the queue has done the appointment
		<<"3. Search Patient \n"
		<<"4. Sort by Doctor's name\n"
		<<"5. Exit\n"
		<<"Enter action: "; 
}

void patientMenu(){
	cout<<"Choose Action\n"
		<<"1. Make an Appointment\n"
		<<"2. Check Your Turn\n"
		<<"3. Cancel Appointment\n"
		<<"4. Exit\n"
		<<"Enter action: ";
}

int main(){
	Access a;
	Queue q;
	Admin ad;
	Patient *p;
	int role, adminKey, ad1, ad2, pa1, pa2;
	int aStatus; //admin login status 
	int pStatus; //patient login status
	string pnm, pid, pcontact, pmail, pdoctor;
	
	ChooseRole:
		menu1();
		cin>>role;
		cout<<endl;
	
	//admin login/register
	if(role==1){
		ad.setKey(123456);
		cout<<"Please enter the admin key: ";
		cin>>adminKey;
		
		//verify the admin key
		if(ad.verifyKey(adminKey)==1){
			cout<<"Admin key is verified.\n\n"
				<<"Press <enter> to continue"<<endl;
				cin.get();
				cin.get();
				system("CLS");
			
			Admin:
			cout<<"-ADMIN INTERFACE-\n";
			menu2();
			cin>>ad1;
			cin.ignore();
			cout<<endl;
			
			//registration
			if(ad1==1){
				a.registration(role);
				cout<<"Press <enter> to continue"<<endl;
				cin.get();
				system("CLS");
				goto Admin;
				
			}//end register
			
			else if(ad1==2){
				
				aStatus=a.adminlogin();
				
				//successfully login
				if(aStatus==1){
					cout<<"Successfully login!\n\n"
						<<"Press <enter> to continue"<<endl;
					cin.get();
					system("CLS");
					
					//start performing action
					do{
						adminMenu();
						cin>>ad2;
						cout<<endl;
					
						//display customer queue list
						if(ad2==1){
							q.display();
							cout<<endl;
							cout<<"Press <enter> to continue"<<endl;
							cin.get();
							cin.get();
							system("CLS");
						}
					
						//delete the patient
						else if(ad2==2){
							if(q.isEmpty()){
								cout<<"No patient in the queue to be deleted.\n";
								cout<<endl;
								cout<<"Press <enter> to continue"<<endl;
								cin.get();
								cin.get();
								system("CLS");
							}
							
							else{
								q.completePatient();
								cout<<"The first patient has completed the appoinment. The queue list is updated.\n";
								cout<<endl;
								cout<<"Press <enter> to continue"<<endl;
								cin.get();
								cin.get();
								system("CLS");
							}
						
						}
						
						//search patient
						else if (ad2 == 3) {
							q.searchPatient();
							cout << endl;
							cout << "Press <enter> to continue" << endl;
							cin.get();
							system("CLS");
						}
						
						//sort by doctor's name
						else if (ad2 == 4) {
							q.insertionSort();
							q.displaySorted();
							cout<<endl;
							cout << "Press <enter> to continue" << endl;
							cin.get();
							cin.get();
							system("CLS");
						}
						
						//change the role
						else if (ad2 == 5) {
							cout << "Thank you for using this system.\n";
							cout << endl;
							cout << "Press <enter> to continue" << endl;
							cin.get();
							cin.get();
							system("CLS");
							goto ChooseRole;
						}

						//invalid input
						else {
							cout << "Invalid input. Please choose a valid action.\n\n"
								<< "Press <enter> to continue" << endl;
							cin.get();
							system("CLS");
							goto Admin;

						}

					} while (ad2 != 5);
						
				}//end for success login
				
				//wrong username or password
				else if(aStatus==2){
					cout<<"Incorrect username or password.\n\n"
						<<"Press <enter> to continue"<<endl;
						cin.get();
						system("CLS");
						goto Admin;
				}
				
				//wrong id or not register yet
				else if(aStatus==3){
					cout<<"Incorrect ID or not register yet.\n\n"
						<<"Press <enter> to continue"<<endl;
					cin.get();
					system("CLS");
					goto Admin;
				}
				
			}
			
			else{
				cout<<"Invalid input. Please choose a valid action.\n\n"
					<<"Press <enter> to continue"<<endl;
				cin.get();
				system("CLS");
				goto Admin;
		
			}
			
		}//end verified admin key
		
		else{
			cout<<"Incorrect admin key. Please choose your role again.\n\n"
				<<"Press <enter> to continue"<<endl;
			cin.get();
			cin.get();
			system("CLS");
			goto ChooseRole;
			
		}//wrong admin key
		
	}//end admin
	
	else if(role==2){
		
		Patient:
			cout<<"-PATIENT INTERFACE-\n";
			menu2();
			cin>>pa1;
			cin.ignore();
			cout<<endl;
			
			//registration
			if(pa1==1){
				a.registration(role);
				cout<<"Press <enter> to continue"<<endl;
				cin.get();
				system("CLS");
				goto Patient;
				
			}//end register
			
			else if(pa1==2){
				
				pStatus=a.patientlogin();
				
				//successfully login
				if(pStatus==1){
					cout<<"Successfully login!\n\n"
						<<"Press <enter> to continue"<<endl;
					cin.get();
					system("CLS");
					
					//start performing action
					do{
						patientMenu();
						cin>>pa2;
						cout<<endl;
						cin.ignore();
							
						//make an appointment
						if(pa2==1){
							cout<<"-MAKE APPOINTMENT_\n"
								<<"Please enter you information\n";
							cout<<"Name: ";
							getline(cin,pnm);
							cout<<"ID (IC number): ";
							getline(cin,pid);
							cout<<"Contact number: ";
							getline(cin,pcontact);
							cout<<"Email address: ";
							getline(cin,pmail);
							cout<<"Doctor's name': ";
							getline(cin,pdoctor);
						
							p=new Patient(pnm, pid, pcontact, pmail, pdoctor);
							q.insertPatient(p);
							cout<<"Successfully making appointment!\n\n";
						
							cout<<"Press <enter> to continue"<<endl;
							cin.get();
							system("CLS");
						
						}
					
						//check your turn in the queue
						else if(pa2==2){
							cout<<"-CHECK YOUR TURN-\n";
							q.checkTurn();
							cout<<"Press <enter> to continue"<<endl;
							cin.get();
							system("CLS");
						}
						
						//cancel appointment -  delete the patient from the queue
						else if(pa2==3){
							cout<<"-CANCEL APPOINTMENT-\n";
							q.cancelPatient();
							cout<<"Press <enter> to continue"<<endl;
							cin.get();
							system("CLS");
						}
					
						//exit the system
						else if(pa2==4){
							cout<<"Thank you for using this system.\n\n";
							cout<<"Press <enter> to continue"<<endl;
							cin.get();
							system("CLS");
							goto ChooseRole;
						}
					
						//invalid input
						else{
							cout<<"Invalid input. Please choose a valid action.\n\n"
								<<"Press <enter> to continue"<<endl;
							cin.get();
							system("CLS");
						}
					
					}while(pa2!=4);
						
				}//end for success login
				
				//wrong username or password
				else if(pStatus==2){
					cout<<"Incorrect username or password.\n\n"
						<<"Press <enter> to continue"<<endl;
						cin.get();
						system("CLS");
						goto Patient;
				}
				
				//wrong id or not register yet
				else if(pStatus==3){
					cout<<"Incorrect ID or not register yet.\n\n"
						<<"Press <enter> to continue"<<endl;
					cin.get();
					system("CLS");
					goto Patient;
				}
				
			}
			
			else{
				cout<<"Invalid input. Please choose a valid action.\n\n"
					<<"Press <enter> to continue"<<endl;
				cin.get();
				system("CLS");
				goto Patient;
		
			}
		
	}//end patient
	
	else if(role==3){
		cout<<"Exiting the system....\n";
		return 0;
	}
	
	else{
		cout<<"Invalid input. Please choose a valid role.\n\n"
			<<"Press <enter> to continue"<<endl;
		cin.get();
		cin.get();
		system("CLS");
		goto ChooseRole;
		
	}
		
}
