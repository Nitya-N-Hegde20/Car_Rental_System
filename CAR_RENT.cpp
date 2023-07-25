#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>
using namespace std;

const int MAX_CARS =100;
const int primeN=101;

struct Car {
    int carId;
    string carName;
    int dailyRent;
    bool isRented;
    string renterName;
    string phoneNumber;
    string licenseNumber;
    int numOfDays;
};

class CarRentalSystem {
private:
    Car carDatabase[MAX_CARS];
    int hashTable[MAX_CARS];

public:
    CarRentalSystem() {
        for (int i = 0; i < MAX_CARS; ++i) {
            carDatabase[i].carId = -1;
            hashTable[i] = -1;
        }
    }

    int hashFunction(int carId) {
        return carId % primeN;
    }

    int linearProbe(int index) {
        return (index + 1) % primeN;
    }

    void readCarDatabase() {
        ifstream inFile("car_rent.txt", ios::app|ios::out);
        if (!inFile) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            int carId = atoi(line.c_str());

            string carName;
            getline(inFile, carName);

            getline(inFile, line);
            int dailyRent = atoi(line.c_str());

            getline(inFile, line);
            bool isRented = (line == "1");

            string renterName;
            getline(inFile, renterName);
            
			string phoneNumber;
            getline(inFile,phoneNumber);
        
            string licenseNumber;
            getline(inFile,licenseNumber);
            
			getline(inFile, line);
            int numOfDays = atoi(line.c_str());
			

            addCarToDatabase(carId, carName, dailyRent, isRented, renterName,phoneNumber,licenseNumber,numOfDays);
        }

        inFile.close();
        system("CLS");
        cout << "Car database loaded successfully!" << endl;
        system("PAUSE");
        system("CLS");
    }

    void writeCarDatabase() {
        ofstream outFile("car_rent.txt", ios::trunc);
        if (!outFile) {
            cout << "Error opening file." << endl;
            return;
        }

        for (int i = 0; i < MAX_CARS; ++i) {
            if (carDatabase[i].carId != -1) {
                outFile << carDatabase[i].carId << endl;
                outFile << carDatabase[i].carName << endl;
                outFile << carDatabase[i].dailyRent << endl;
                outFile << carDatabase[i].isRented << endl;
                outFile << carDatabase[i].renterName << endl;
                outFile << carDatabase[i].phoneNumber<<endl;
                outFile << carDatabase[i].licenseNumber <<endl;
                outFile << carDatabase[i].numOfDays << endl;
                
            }
        }

        outFile.close();
        cout << "Car database saved successfully!" << endl;
        system("PAUSE");
        system("CLS");
    }

    void addCarToDatabase(int carId, const string& carName, int dailyRent, bool isRented = false, const string& renterName = "",const string& phoneNumber="",const string& licenseNumber="",int numOfDays=0) {
    int hashIndex = hashFunction(carId);
    int index = hashIndex;

    while (carDatabase[index].carId != -1) {
        if (carDatabase[index].carId == carId) {
            cout << "Car with the given ID already exists." << endl;
            return;
        }
        index = linearProbe(index);
        if(index == MAX_CARS)
            index=0;
        if (index == hashIndex) {
            cout << "Car database is full. Cannot add more cars." << endl;
            return;
        }
    }

    carDatabase[index].carId = carId;
    carDatabase[index].carName = carName;
    carDatabase[index].dailyRent = dailyRent;
    carDatabase[index].isRented = isRented;
    carDatabase[index].renterName = renterName;
    carDatabase[index].phoneNumber=phoneNumber;
    carDatabase[index].licenseNumber=licenseNumber;
    carDatabase[index].numOfDays=numOfDays;
    

    hashTable[index] = hashIndex;
    cout << "Car added successfully!" << endl;
}
void editCarDatabase(int carId, const string& carName, int dailyRent, bool isRented = false, const string& renterName = "",const string& phoneNumber="",const string& licenseNumber="",int numOfDays=0){
     int hashIndex = hashFunction(carId);
        if (carDatabase[hashIndex].carId != -1) {
        	if(carDatabase[hashIndex].carId ==carId){
            carDatabase[hashIndex].carName = carName;
            carDatabase[hashIndex].dailyRent = dailyRent;
            cout << "Car details updated successfully!" << endl;
        }
        else{
        int index = hashIndex;
        index = linearProbe(index);
        while (carDatabase[index].carId != carId) {
        index = linearProbe(index);
        if(index == MAX_CARS)
            index=0;
        if (index == hashIndex){
     cout << "Car with the given ID does not exist." << endl;
     return;
    }
}
            carDatabase[index].carName = carName;
            carDatabase[index].dailyRent = dailyRent;
            cout << "Car details updated successfully!" << endl;
        } 
}
else
 cout << "Car with the given ID does not exist." << endl;
}

void deleteCarFromDatabase(int carId) {
        int hashIndex = hashFunction(carId);
        if (carDatabase[hashIndex].carId != -1) {
        	if(carDatabase[hashIndex].carId ==carId){
            carDatabase[hashIndex].carId = -1;
            carDatabase[hashIndex].carName = "";
            carDatabase[hashIndex].dailyRent = 0;
            carDatabase[hashIndex].isRented = false;
            carDatabase[hashIndex].renterName = "";
            carDatabase[hashIndex].phoneNumber="";
            carDatabase[hashIndex].licenseNumber="";
            carDatabase[hashIndex].numOfDays=0;
            hashTable[hashIndex] = -1;
            cout << "Car deleted successfully!" << endl;
        }
        else{
        int index = hashIndex;
        index = linearProbe(index);
        while (carDatabase[index].carId != carId) {
        index = linearProbe(index);
        if(index == MAX_CARS)
            index=0;
        if (index == hashIndex){
     cout << "Car with the given ID does not exist." << endl;
     return;
    }
}
            carDatabase[index].carId = -1;
            carDatabase[index].carName = "";
            carDatabase[index].dailyRent = 0;
            carDatabase[index].isRented = false;
            carDatabase[index].renterName = "";
            carDatabase[index].phoneNumber="";
            carDatabase[index].licenseNumber="";
            carDatabase[index].numOfDays=0;
            hashTable[index] = -1;
            cout << "Car deleted successfully!" << endl;
        } 
}
else
 cout << "Car with the given ID does not exist." << endl;
}

    void rentCar(int carId, const string& renterName, int numOfDays,const string& phoneNumber,const string& licenseNumber) {
    int hashIndex = hashFunction(carId);
    if (carDatabase[hashIndex].carId != -1) {
    	if(carDatabase[hashIndex].carId == carId){
        if (!carDatabase[hashIndex].isRented) {
            carDatabase[hashIndex].isRented = true;
            carDatabase[hashIndex].renterName = renterName;
            carDatabase[hashIndex].phoneNumber=phoneNumber;
            carDatabase[hashIndex].licenseNumber=licenseNumber;
            carDatabase[hashIndex].numOfDays=numOfDays;
            int totalRent = carDatabase[hashIndex].numOfDays * carDatabase[hashIndex].dailyRent;
            cout << "Car rented successfully!" << endl;
            cout << "Total rent: $" << totalRent << endl;
            writeCarDatabase(); // Call the member function of the same object to write the database
            showInvoice(carId,renterName,numOfDays,totalRent,phoneNumber,licenseNumber,carDatabase[hashIndex].carName,carDatabase[hashIndex].dailyRent);
        } else {
            cout << "Car is already rented." << endl;
        }
    }
    else{
        int index = hashIndex;
        index = linearProbe(index);
        while (carDatabase[index].carId != carId) {
        index = linearProbe(index);
        if(index == MAX_CARS)
            index=0;
        if (index == hashIndex){
     cout << "Car with the given ID does not exist." << endl;
     return;
    }
    
    }
	if (!carDatabase[index].isRented) {
            carDatabase[index].isRented = true;
            carDatabase[index].renterName = renterName;
            carDatabase[index].phoneNumber=phoneNumber;
            carDatabase[index].licenseNumber=licenseNumber;
            carDatabase[index].numOfDays=numOfDays;
            int totalRent = numOfDays * carDatabase[index].dailyRent;
            cout << "Car rented successfully!" << endl;
            cout << "Total rent: $" << totalRent << endl;
            writeCarDatabase(); 
            showInvoice(carId,renterName,numOfDays,totalRent,phoneNumber,licenseNumber,carDatabase[index].carName,carDatabase[index].dailyRent);
        } else {
            cout << "Car is already rented." << endl;
        } 
    }
}
else
cout << "Car with the given ID does not exist." << endl;
     return;
}
void showInvoice(int carId, const string& renterName, int numOfDays,int totalRent,const string& phoneNumber,const string& licenseNumber,const string& carName,int dailyRent){
    	 cout << "\n\t\t                       Car Rental - Customer Invoice                  "<<endl;
    cout << "\t\t	///////////////////////////////////////////////////////////"<<endl;
    cout << "\t\t	| Customer Name:"<<"-----------------|"<<setw(10)<<renterName<<" |"<<endl;
    cout << "\t\t	| Phone Number :"<<"-----------------|"<<setw(10)<<phoneNumber<<" |"<<endl;
    cout << "\t\t	| License Number:"<<"----------------|"<<setw(10)<<licenseNumber<<" |"<<endl;
    cout << "\t\t	| Car No. :"<<"----------------------|"<<setw(10)<<carId<<" |"<<endl;
    cout << "\t\t	| Car Name :"<<"---------------------|"<<setw(10)<<carName<<" |"<<endl;
    cout << "\t\t	| Daily Rent :"<<"-------------------|"<<setw(10)<<dailyRent<<" |"<<endl;
	cout << "\t\t	| Number of days :"<<"---------------|"<<setw(10)<<numOfDays<<" |"<<endl;
    cout << "\t\t	| Your Rental Amount is :"<<"--------|"<<setw(10)<<totalRent<<" |"<<endl;
    cout << "\t\t	| Caution Money :"<<"----------------|"<<setw(10)<<"0"<<" |"<<endl;
    cout << "\t\t	 ________________________________________________________"<<endl;
    cout <<"\n";
    cout << "\t\t	| Total Rental Amount is :"<<"-------|"<<setw(10)<<totalRent<<" |"<<endl;
    cout << "\t\t	 ________________________________________________________"<<endl;
    cout << "\t\t	 # This is a computer generated invoce and it does not"<<endl;
    cout << "\t\t	 require an authorised signture #"<<endl;
    cout <<" "<<endl;
    cout << "\t\t	///////////////////////////////////////////////////////////"<<endl;
    cout << "\t\t	You are advised to pay up the amount before due date."<<endl;
    cout << "\t\t	Otherwise penelty fee will be applied"<<endl;
    cout << "\t\t	///////////////////////////////////////////////////////////"<<endl;
    
	}

    void displayCarDatabase() {
    	cout<<"\t\t\t\t\t<<<<<<~~~~~~~~~~   CAR DATABASE   ~~~~~~~~~>>>>>> \n\n";
        for (int i = 0; i < MAX_CARS; ++i) {
            if (carDatabase[i].carId != -1) {
            	cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
                cout <<"Car ID: " << carDatabase[i].carId <<endl;
                cout << "Car Name: " << carDatabase[i].carName << endl;
                cout << "Daily Rent: $" << carDatabase[i].dailyRent << endl;
                cout << "Status: " << (carDatabase[i].isRented ? "Rented" : "Available") << endl;
                if (carDatabase[i].isRented){
                    cout << "Rented by: " << carDatabase[i].renterName << endl;
                    cout << "License Number: " << carDatabase[i].licenseNumber <<endl;
                    cout << "Phone number: " << carDatabase[i].phoneNumber <<endl;
                    cout << "Number of days :" << carDatabase[i].numOfDays << endl;
                }
                cout << endl;
            }
        }
        system("PAUSE");
        system ("CLS");
    }
     void displayAvailable() {
     	cout<<"\t\t\t\t\t <<<<<<~~~~~~~~~~   AVAILABLE CARS  ~~~~~~~~~>>>>>> \n\n";
        for (int i = 0; i < MAX_CARS; ++i) {
            if (carDatabase[i].carId != -1) {
            	if(carDatabase[i].isRented==0){
            	cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                cout << "Car ID: " << carDatabase[i].carId << endl;
                cout << "Car Name: " << carDatabase[i].carName << endl;
                cout << "Daily Rent: $" << carDatabase[i].dailyRent << endl;
                cout << endl;
                
            }
        }
    }
        system("PAUSE");
        system ("CLS");
}
};

int main() {
    CarRentalSystem rentalSystem;
    rentalSystem.readCarDatabase();
    char ch;
    string password="admin",pass;
    int choice;
    int carId;
    int a;
    string carName;
    int dailyRent;
    string renterName;
    string phoneNumber;
    string licenseNumber;
    int numOfDays;
   ifstream in("welcome.txt"); //displaying welcome ASCII image text on output screen fn1353

  if(!in) {
    cout << "Cannot open input file.\n";
  }
  char str2[1000];
  while(in) {
    in.getline(str2, 1000);  // delim defaults to '\n' cp
    if(in) cout << str2 << endl;
  }
  in.close();
  sleep(1);
  cout<<"\nStarting the program please wait....."<<endl;
  sleep(1);
  cout<<"\nloading up files....."<<endl;
  sleep(1); //function which waits for (n) seconds
  system ("CLS"); //cleares screen 
    while (true) {
    	label:
        cout<<"\n\n\n\n\n\n\t\t\t\t\t ~~~~~CAR RENTAL SYSTEM~~~~ \n\n";
   cout<<"\t\t\t\t\t------------------------------";
   cout<<"\n\t\t\t\t\t\t     1.Customer \n";	
   cout<<"\n\t\t\t\t\t\t     2.Admin \n";
   cout<<"\n\t\t\t\t\t\t     3.Exit \n";
   	 cout<<"\t\t\t\t\t------------------------------\n\n";
        cout << "\t\t\t\t\tEnter your choice: ";
        cin >> choice;
   system("PAUSE");
      system ("CLS");
        switch (choice) {
        	case 1:{
        		 cout<<"\n\n\n\n\n\n\t\t\t\t\t ~~~~~~~~~~   CUSTOMER  ~~~~~~~~~ \n\n";
   cout<<"\t\t\t\t\t------------------------------";
   cout<<"\n\t\t\t\t\t\t     a.Rent a car \n";	
   cout<<"\n\t\t\t\t\t\t     b.Display  \n";
   cout<<"\n\t\t\t\t\t\t     c.Exit \n";
   	 cout<<"\t\t\t\t\t------------------------------\n\n";
        cout << "\t\t\t\t\tEnter your choice: ";
        cin >> ch;
				switch(ch){
					case 'a':system ("CLS");
					rentalSystem.displayAvailable();
					cout<<"--------------------------------------------------------------------------"<<endl;
    cout << "Please provide following information: "<<endl; 
    cout<<"Please select a Car No. : ";
    cin >> carId;
    cout << "Renter name : ";                           
    cin.ignore();
    getline(cin, renterName);
    cout << "Phone number :";
    getline(cin, phoneNumber);
    cout << "License Number :";
    getline(cin, licenseNumber);
    cout<<"Number of days you wish to rent the car : ";
    cin >> numOfDays;
    cout<<endl;
                rentalSystem.rentCar(carId, renterName, numOfDays,phoneNumber,licenseNumber);  
				system("PAUSE"); 
                goto label;
                case 'b':system("PAUSE");
				system ("CLS");
				rentalSystem.displayAvailable();
				system("PAUSE");
                goto label;
                case 'c':{
					system ("CLS");
				cout << "Exiting program..." << endl;
				system ("CLS");
				ifstream inFil("thanks.txt");
				 char str1[300];

  while(inFil) {
    inFil.getline(str1, 300);
    if(inFil) cout << str1 << endl;
  }
  inFil.close();
  return 0;
}
                 default:cout << "Invalid choice! Please try again." << endl;
                system ("CLS");
                goto label;
                
				}
			}
			case 2:{system ("CLS");
				cout<<"Enter the password: ";
			cin>>pass;
			if(pass==password){
				system ("CLS");
				cout<<"\n\n\n\n\n\n\t\t\t\t\t ~~~~~~~~~~   ADMIN   ~~~~~~~~~ \n\n";
				 cout<<"\t\t\t\t\t------------------------------";
   cout<<"\n\t\t\t\t\t\t     1.ADD CAR \n";	
   cout<<"\n\t\t\t\t\t\t     2.DELETE CAR \n";
   cout<<"\n\t\t\t\t\t\t     3.DISPLAY \n";
   cout<<"\n\t\t\t\t\t\t     4.EDIT CAR DETAILS \n";
   cout<<"\n\t\t\t\t\t\t     5.EXIT \n";
   cout<<"\t\t\t\t\t------------------------------\n\n";
        cout << "\t\t\t\t\tEnter your choice: ";
        cin >> a;
        switch(a){
        	case 1:{system ("CLS");
				cout << "Please provide following information: "<<endl; 
                cout<<"Enter a Car ID : ";
                cin >> carId;
                cout << "Enter car name: ";
                cin.ignore();
                getline(cin, carName);
                cout << "Enter daily rent: ";
                cin >> dailyRent;
                rentalSystem.addCarToDatabase(carId, carName, dailyRent);
                system("PAUSE");
                rentalSystem.writeCarDatabase();
                goto label;
            }
            case 2: {system ("CLS");
				cout << "Enter car ID: ";
                cin >> carId;
                rentalSystem.deleteCarFromDatabase(carId);
                system("PAUSE");
                rentalSystem.writeCarDatabase();
                goto label;
            }
            case 4: {
			    system("CLS"); 
			    cout<<"Enter a Car ID whose name or rent needs to be changed : ";
                cin >> carId;
                cout << "Enter car name: ";
                cin.ignore();
                getline(cin, carName);
                cout << "Enter daily rent: ";
                cin >> dailyRent;
                rentalSystem.editCarDatabase(carId, carName, dailyRent);
                system("PAUSE");
                rentalSystem.writeCarDatabase();
                goto label;
            	
				break;
			}
            case 3:{
			system ("CLS");
			rentalSystem.displayCarDatabase();
			system("PAUSE");
                goto label;
            }
            case 5:{
                system ("CLS");
				cout << "Exiting program..." << endl;
				system ("CLS");
				ifstream inF("thanks.txt");
				 char str12[300];

  while(inF) {
    inF.getline(str12, 300);
    if(inF) 
	cout << str12 << endl;
  }
  inF.close();
                return 0;
            }
            default:cout << "Invalid choice! Please try again." << endl;
                goto label;
		}
			}
			else{
				cout<<"Invalid password\n";
				goto label;
			}
		}
          case 3:{
			system ("CLS");
				cout << "Exiting program..." << endl;
				system ("CLS");
				ifstream inFi("thanks.txt");
				 char str13[300];

  while(inFi) {
    inFi.getline(str13, 300);
    if(inFi) 
	cout << str13 << endl;
  }
  inFi.close();
                return 0;
            }
			default:cout << "Invalid choice! Please try again." << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}
