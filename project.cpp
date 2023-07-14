/*
Tested on Ubuntu 20.04
Compiler: gcc version 9.3.0 (Ubuntu 9.3.0-10ubuntu2) 
The code needs ‘-std=c++17’ or ‘-std=gnu++17’  as it makes use of structured bindings  

****** ! IMPORTANT !
You have to add compiler flag (/stdc++17) when compiling with Visual studio 
Project properties -> Config Properties -> C/C++ -> Command Line, and then add compiler flag to the bottom section "Additional Options"
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <tuple>
using namespace std;

struct date{
    int day;
    int month;
    int year;
};
struct fine
{
    int value;
    string street_name;
    date fine_date;
    bool paid = false ;
};
struct car
{
    int plate_number;
    string model;
    int production_year;
    // bool registered = false;
    vector<fine> fines;
};
struct driver
{
    int license_number;
    string name ;
    date birthdate;
    // int numCars = 0; // doesn't exceed 3 **  Deprecated -> used std::vector.size() to reduce redundacy
    vector<car> cars; 
};
/// Global Definitions
vector<driver> drivers;
string br = "//***************************\\\\ \n";
char esc_char =27;
// Global Functions
tuple<int, int, int>  getBirthDate()
{
    int current_year = 2020;
    int minValidYear = current_year -18;
    int m,d,y;
    cout<<"Driver Birth Date"<<endl;
    cout<<"Enter Day: ";
    cin>> d;
    cout<<"Enter Month: ";
    cin>> m;
    cout<<"Enter Year: ";
    cin>> y;
    while( (y >= minValidYear)  || (m < 1 || m > 12)  || (d < 1 || d > 31) )
    {
        cout<<"Invalid Birth Date Entered. Please try to re-enter"<<endl;
        cout<<"Enter Day: ";
        cin>> d;
        cout<<"Enter Month: ";
        cin>> m;
        cout<<"Enter Year: ";
        cin>> y;
    }
    return  {d, m, y};
}
tuple<int, int, int>  getDate()
{
    int m,d,y;
    cout<<"Enter Date"<<endl;
    cout<<"Enter Day: ";
    cin>> d;
    cout<<"Enter Month: ";
    cin>> m;
    cout<<"Enter Year: ";
    cin>> y;
    while(  (m < 1 || m > 12)  || (d < 1 || d > 31) )
    {
        cout<<"Invalid Birth Date Entered. Please try to re-enter"<<endl;
        cout<<"Enter Day: ";
        cin>> d;
        cout<<"Enter Month: ";
        cin>> m;
        cout<<"Enter Year: ";
        cin>> y;
    }
    return  {d, m, y};
}
int searchDrivers(string msg, bool suppress)
{
    string dName;  // dName short for Driver Name
    int dIndex = -1;
    cout<<msg;
    cin.ignore();
    getline(cin,dName);
    for(int k=0; k < drivers.size(); k++)
    {
        
        if(dName.compare(drivers[k].name) == 0)
        {
            dIndex = k;
            break;
        }
    }
    if(!suppress)
    {
        string ans;
        if (dIndex== -1)
        {
            cout<<br;
            cout<<"Driver not Found. Check for spelling "<<endl;
            cout<<"Do you want to search again for another driver? ";
            cin>> ans;
            while(ans == "y" || ans == "Y" || ans == "yes"){
                dIndex = searchDrivers(msg,true);
                if(dIndex > -1)
                {
                    ans = "N";
                }else{
                    cout<<"Driver not Found. Check for spelling "<<endl;
                    cout<<"Do you want to search again for another driver? ";
                    cin>> ans;
                }
            }
        }
    }

    return dIndex;
}
int searchCars(int dIndex)
{
    int choice;
    cout<<br;
    cout<<"Search Options: "<<endl;
    cout<<"Option 1: With plate Number"<<endl;
    cout<<"Option 2: With model"<<endl;
    cin>>choice;
    int cIndex = -1;
    if(choice ==1)
    {
        int cNum;  
        cout<<"Enter Car Plate Number: ";
        //cin.ignore();
        //getline(cin,dName);
        cin>>cNum;
        for(int k=0; k < drivers[dIndex].cars.size(); k++)
        {   
            if(drivers[dIndex].cars[k].plate_number == cNum)
            {
                cIndex = k;
                break;
            }
        }
    }else if (choice == 2){
        string cModel;  
        cout<<"Enter Car Model: ";
        cin.ignore();
        getline(cin,cModel);
        for(int k=0; k < drivers[dIndex].cars.size(); k++)
        {   
            if(drivers[dIndex].cars[k].model.compare(cModel) == 0)
            {
                cIndex = k;
                break;
            }
        }
    }else{
        cout<<"Operation aborted. Invalid choice/option"<<endl;
        return searchCars(dIndex);
    }

    string ans;
    if (cIndex== -1)
    {
        cout<<br;
        cout<<"Car not Found. Check that inserted data is correct. "<<endl;
        cout<<"Do you want to search again for another car?";
        cin>> ans;
        while(ans == "y" || ans == "Y" || ans == "yes"){
            cIndex = searchCars(dIndex);
            if(cIndex > -1)
            {
                ans = "N";
            }else{
                cout<<"Car not Found. Check that inserted data is correct. "<<endl;
                cout<<"Do you want to search again for another car?";
                cin>> ans;
            }
        }
    }
    return cIndex;
}
void showDriver(int dIndex)
{
    cout<<"Driver's Name: " << drivers[dIndex].name<<endl;
    cout<<"Driver's License number: " <<drivers[dIndex].license_number <<endl;
    cout<< "Driver's Birth Date: " <<drivers[dIndex].birthdate.day<< "/"<< drivers[dIndex].birthdate.month<< "/"<< drivers[dIndex].birthdate.year<<endl;
}
void showCar(int dIndex, int cIndex)
{
    cout<<"Car's Plate Number" << drivers[dIndex].cars[cIndex].plate_number <<endl;
    cout<<"Car's model: " << drivers[dIndex].cars[cIndex].model <<endl;
    cout<<"Car's production year: " << drivers[dIndex].cars[cIndex].production_year<<endl;
}
void showCars(int dIndex)
{
    cout<<br;
    cout<<"Cars owned by Driver are listed: " << drivers[dIndex].name<<endl;
    for(int m=0; m < drivers[dIndex].cars.size() ; m++)
    {
        cout<<"Car No. " << m <<endl;
        showCar(dIndex, m);
    }
}
void showFine(int dIndex, int cIndex, int fIndex)
{
    cout<<"Fine Value: "<<drivers[dIndex].cars[cIndex].fines[fIndex].value <<endl;
    cout<<"Street name where Fine is incurred: "<< drivers[dIndex].cars[cIndex].fines[fIndex].street_name <<endl;
    cout<< "Date when Fine is incurred: " <<drivers[dIndex].cars[cIndex].fines[fIndex].fine_date.day<< "/"<< drivers[dIndex].cars[cIndex].fines[fIndex].fine_date.month<< "/"<< drivers[dIndex].cars[cIndex].fines[fIndex].fine_date.year<<endl;
}
int sumFines(int dIndex, int cIndex)
{
    int sum = 0;
    for(int m=0; m < drivers[dIndex].cars[cIndex].fines.size() ; m++)
    {
        if(drivers[dIndex].cars[cIndex].fines[m].paid == false)
        {
            sum += drivers[dIndex].cars[cIndex].fines[m].value;
        }
    }
    return sum;
}
void showAllDriverData(int dIndex)
{
    showDriver(dIndex);
    for(int y=0; y < drivers[dIndex].cars.size() ; y++ ){
        cout<<br;
        showCar(dIndex, y);
        cout<<"Fines Attached to Car: "<<endl;
        for (int b = 0; b < drivers[dIndex].cars[y].fines.size(); b++)
        {
            showFine(dIndex,y,b);
        }   
    }
}
//
void mainLoop()
{
    string option;
    cout<<br;
    cout<< esc_char << "[1m" << "Welcome to TrafficGo(R) The most advanced traffic system in the entire world"<<esc_char << "[0m" <<endl;
    cout<<br;
    cout<<"Choose one of the following options so that the system can assit you better"<<endl;
    cout<<"Reply with the option number"<<endl;
    cout<<"Option 1: Driver License Registration"<<endl;
    cout<<"Option 2: Car License Registration"<<endl;
    cout<<"Option 3: Fine Addition - Issue a fine"<<endl;
    cout<<"Option 4: Fine payment"<<endl;
    cout<<"Option 5: Search Database (Drivers-Cars-Fines)"<<endl;
    cin>>option;
    if(option == "1"){
        int numDrivers = drivers.size();
        // intiatiing driver struct into the drivers vector
        drivers.push_back(driver());
        // fetching data from the driver
        cout<<"Enter Driver's name: ";
        cin.ignore();
        getline(cin,drivers[numDrivers].name);
        cout<<drivers[numDrivers].name<<endl;
        // Generating Driver License number
        drivers[numDrivers].license_number = rand();
        // Entering Driver Birth Date
        auto [day, month, year] = getBirthDate();
        drivers[numDrivers].birthdate.day = day ;
        drivers[numDrivers].birthdate.month = month;
        drivers[numDrivers].birthdate.year = year;
        // Ask if driver owns car
        cout<<"Does Driver own one or more car?"<<endl;
        cout<<"Reply with Y/y if Driver owns or N/n if not: ";
        char ans;
        cin>> ans;
        if(ans == 'Y' || ans == 'y')
        {
            int carVectorIndex = drivers[numDrivers].cars.size();
            drivers[numDrivers].cars.push_back(car());
            // generating Car plate number
            drivers[numDrivers].cars[carVectorIndex].plate_number = rand();
            // fetching Car model
            cout<<"Enter Car's model: ";
            cin.ignore();
            getline(cin,drivers[numDrivers].cars[carVectorIndex].model);
            // fetching Car production year
            cout<<"Enter Car's production year: ";
            cin>>drivers[numDrivers].cars[carVectorIndex].production_year;

        }
        //// Display Driver Details after registration 

        cout<<"Driver's Name: " << drivers[numDrivers].name<<endl;
        cout<<"Driver's License number: " <<drivers[numDrivers].license_number <<endl;
        cout<< "Driver's Birth Date: " <<drivers[numDrivers].birthdate.day<< "/"<< drivers[numDrivers].birthdate.month<< "/"<< drivers[numDrivers].birthdate.year<<endl;
        cout<<"Regsitered Cars Info for Driver With License Number " << drivers[numDrivers].license_number << ": " <<endl;
        for(int j = 0 ; j < drivers[numDrivers].cars.size(); j++){
            cout<<"Car's Plate Number: " << drivers[numDrivers].cars[j].plate_number <<endl;
            cout<<"Car's model: " << drivers[numDrivers].cars[j].model <<endl;
            cout<<"Car's production year: " << drivers[numDrivers].cars[j].production_year<<endl;
        }
        
            
    }else if(option == "2")
    {
        string dName;  // dName short for Driver Name
        int dIndex = -1;
        cout<<"Enter Driver Name For whom the car will be registered: ";
        cin.ignore();
        getline(cin,dName);
        for(int k=0; k < drivers.size(); k++)
        { 
            if(dName.compare(drivers[k].name) == 0)
            {
                dIndex = k;
                break;
            }
        }
        if(dIndex > -1)
        {
            if(drivers[dIndex].cars.size() < 3)
            {
                int carVectorIndex = drivers[dIndex].cars.size();
                drivers[dIndex].cars.push_back(car());
                // generating Car plate number
                drivers[dIndex].cars[carVectorIndex].plate_number = rand();
                // fetching Car model
                cout<<"Enter Car's model: ";
                cin.ignore();
                getline(cin,drivers[dIndex].cars[carVectorIndex].model);
                // fetching Car production year
                cout<<"Enter Car's production year: ";
                cin>>drivers[dIndex].cars[carVectorIndex].production_year;
                //increasing number of cars that driver own by one
                // drivers[dIndex].numCars ++; (deprecated)
                ///Confirmation and Display info
                cout<<"*** Infor of Driver for whom the car was added ***"<<endl;
                cout<<"Driver's Name: " << drivers[dIndex].name<<endl;
                cout<<"Driver's License number: " <<drivers[dIndex].license_number <<endl;
                cout<< "Driver's Birth Date: " <<drivers[dIndex].birthdate.day<< "/"<< drivers[dIndex].birthdate.month<< "/"<< drivers[dIndex].birthdate.year<<endl;
                cout<<"Regsitered Cars Info for Driver With License Number " << drivers[dIndex].license_number << ": " <<endl;
                for(int j = 0 ; j < drivers[dIndex].cars.size(); j++){
                    cout<< br;
                    cout<<"Car's Plate Number" << drivers[dIndex].cars[j].plate_number <<endl;
                    cout<<"Car's model: " << drivers[dIndex].cars[j].model <<endl;
                    cout<<"Car's production year: " << drivers[dIndex].cars[j].production_year<<endl;
                }
            }else
            {
                cout<<"Operation Aborted. Driver " << dName << " already has three cars. He/She needs to remove one first before registering new car" <<endl;
            }
            
        }else
        {
            cout<<"Driver not found. Driver " << dName << " has to register first" <<endl;
        }
    }else if(option  == "3")
    {
        int dIndex = searchDrivers("Enter Driver Name For whom the fine will be issued: ", false);
        int cIndex;
        if(dIndex > -1)
        {
            cIndex = searchCars(dIndex);
            if(cIndex >-1)
            {
                int fineVectorIndex = drivers[dIndex].cars[cIndex].fines.size();
                drivers[dIndex].cars[cIndex].fines.push_back(fine());
                cout<<"Enter Fine Value: ";
                cin>>drivers[dIndex].cars[cIndex].fines[fineVectorIndex].value;
                cout<<"Enter Street name where Fine is incurred: ";
                cin.ignore();
                getline(cin,drivers[dIndex].cars[cIndex].fines[fineVectorIndex].street_name);

                auto [day, month, year] = getDate();
                drivers[dIndex].cars[cIndex].fines[fineVectorIndex].fine_date.day = day ;
                drivers[dIndex].cars[cIndex].fines[fineVectorIndex].fine_date.month = month;
                drivers[dIndex].cars[cIndex].fines[fineVectorIndex].fine_date.year = year;

                //Confirmation and showing data
                cout<<"Fine Issued succesfully to: "<<endl;
                showDriver(dIndex);
                cout<<"Whose Car is: " <<endl;
                showCar(dIndex,cIndex);
                cout<<"Fine Details: "<<endl;
                showFine(dIndex, cIndex, fineVectorIndex);
        

            }
        }else{
            cout<<br;
            cout<<"Operation Aborted -> No fine Issued as no driver was selected"<<endl;
        }   
    }else if(option == "4")
    {
        int dIndex = searchDrivers("Enter Driver Name For whom the fine will be paid : ", false);
        int cIndex;
        if(dIndex > -1)
        {
            showCars(dIndex);
            cIndex = searchCars(dIndex);
            if(cIndex >-1)
            {
                cout<<br<<"Please wait while the system is calculating the sum of fines. ";
                int finesValue = sumFines(dIndex,cIndex);
                if(finesValue >0)
                {
                    cout<<"The total amount that should be paid is " <<finesValue << "$" <<endl;
                    string confirm;
                    cout<<"Press y to confirm payment of a total sum " << finesValue <<"$";
                    cin.ignore();
                    getline(cin,confirm);
                    if (confirm  == "y")
                    {
                        for(int m=0; m < drivers[dIndex].cars[cIndex].fines.size() ; m++)
                        {
                            drivers[dIndex].cars[cIndex].fines[m].paid = true;
                        }
                        cout<<"Fine of amount "<<finesValue <<"$ Paid succesfully for: "<<endl;
                        showDriver(dIndex);
                        cout<<"Whose Car is: " <<endl;
                        showCar(dIndex,cIndex);
                    }
                }

            }
        }else{
            cout<<br;
            cout<<"Operation Aborted -> No fine Paid as no driver was selected"<<endl;
        } 
         
    }else if(option == "5")
    {
        //Search portion
        string searchOption;
        bool valid = true;
        cout<<br;
        cout<<"Select one the options below to search Database:"<<endl;
        cout<<"Option 1: Search Drivers"<<endl;
        cout<<"Option 2: Search Cars"<<endl;
        cout<<"Option 3: Search Fines"<<endl;
        cin>>searchOption;
        while(searchOption != "1" && searchOption != "2" && searchOption != "3" )
        {
            cout<<br;
            cout<<"Invalid Search Option Selected."<<endl;
            string response;
            cout<<"Press e to exit or any other key to retry.";
            cin>>response;
            if(response != "e")
            {
                cout<<"Select one the options below to search Database:"<<endl;
                cout<<"Option 1: Search Drivers"<<endl;
                cout<<"Option 2: Search Cars"<<endl;
                cout<<"Option 3: Search Fines"<<endl;
                cin>>searchOption;
            }else
            { 
                valid = false;
                break;
            }
        }
        if(valid)
        {
            if(searchOption == "1")
            {
                cout<<br;
                int dIndex = searchDrivers("Enter Driver Name to show Details: ", false);
                showDriver(dIndex);
            }else if(searchOption == "2")
            {
                cout<<br;
                int dIndex = searchDrivers("Enter Driver Name to show His/Her Cars Details: ", false);
                showCars(dIndex);

            }else if(searchOption == "3")
            {
                cout<<br;
                int dIndex = searchDrivers("Enter Driver Name to show All His/Her Fines: ", false);
                showAllDriverData(dIndex);
            }
        }
    }else{
        cout<<"**** Invalid Option Selected **** "<<endl;
        cout<<br;
        string reply;
        cout<<"Press e to exit or y to display options menu again."<<endl;
        cin.ignore();
        getline(cin, reply);
        if(reply == "y")
        {
            mainLoop();
        }

    }

}


 int main()
 {
 
    string connector;
    mainLoop();
    cout<<"Press y/Y to display menu options again or any key to terminate. ";
    cin>> connector;
    while(connector == "y" || connector == "Y" || connector == "yes" )
    {
        mainLoop();
        cout<<"Press y/Y to display menu options again or any key to terminate. ";
        cin>> connector;  
    }

}