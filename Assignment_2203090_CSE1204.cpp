#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h> // For _getch() on Windows
using namespace std;

// Function declarations
void displayMenu();
void handleOption(int option, vector<class Operator> &operators);
void tollPlazaMenu();
void searchMenu();
void searchVehicle(const string &regNo);
void searchDateToDate(const string &startDate, const string &endDate);
void searchOperator(const string &operatorId);
void tollStatistics();
void tollSettings();

class Vehicle {
protected:
    string Date;
    string Time;
    string Operator_Id;
    double tollAmount;

public:
    string reg_No;
    Vehicle() {
        // Get current time
        time_t now = time(0);
        // Convert to tm struct for local timezone
        tm *ltm = localtime(&now);
        // Format the date as YYYY-MM-DD
        Date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + 
               "/" + to_string(1900 + ltm->tm_year);
        // Format the time as HH:MM:SS
        Time = to_string(ltm->tm_hour) + ":" + 
               to_string(ltm->tm_min) + ":" + 
               to_string(ltm->tm_sec);
    }
    virtual void getInput() {
        cout << "Enter Registration Number: ";
        cin >> reg_No;
        cout << "Enter Operator ID: ";
        cin >> Operator_Id;
    }
    virtual float tollCalculate() {
        tollAmount = 0.0; // Default toll amount
    }
    void printPassingDateAndTime() {
        cout << "Passing Date: " << Date << " Passing Time: " << Time;
    }
    string getDate() {
        return Date;
    }

    string getOperatorId() {
        return Operator_Id;
    }

    double getTollAmount() {
        return tollAmount;
    }

    void setTollAmount(double amount) {
        tollAmount = amount;
    }
};
class Truck : public Vehicle {
public:
    double weight;
    double height;

    Truck() : Vehicle() {
        tollAmount = 400.0;
    }

    void getInput() override {
        Vehicle::getInput();
        cout << "Enter weight: ";
        cin >> weight;
        cout << "Enter height: ";
        cin >> height;
    }

    float tollCalculate() override {
        float amount;
        cout<<"Enter the amount for Truck   ";
        cin>>amount;
        return amount-tollAmount;
    }

};

class Bus : public Vehicle {
protected:
    int seats;

public:
    Bus() : Vehicle() {
        tollAmount = 500.0;
    }

    void getInput() override {
        Vehicle::getInput();
        cout << "How many seats: ";
        cin >> seats;
    }

    float tollCalculate() override {
        float amount;
        cout<<"Enter the amount for Bus  ";
        cin>>amount;
        return amount-tollAmount;
    }

};
class Car : public Vehicle {
    string Owner;

public:
    Car() : Vehicle() {
        tollAmount = 150.0;
    }

    void getInput() override {
        Vehicle::getInput();
        cout << "Enter Owner: ";
        cin >> Owner;
    }

    float tollCalculate() override {
        float amount;
        cout<<"Enter the amount for Car   ";
        cin>>amount;
        return amount-tollAmount;

    }

    string getOwner() {
        return Owner;
    }

};

class Operator {
    string operator_id;
    string password;

public:
    Operator(string id, string pwd) : operator_id(id), password(pwd) {}

    static void registerOperator(vector<Operator> &operators) {
        string id, pwd;
        cout << "Enter Operator ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> pwd;
        operators.push_back(Operator(id, pwd));
        cout << "Operator registered successfully!" << endl;
    }

    static void printOperators(const vector<Operator> &operators) {
        cout << "Registered Operators:" << endl;
        for (const auto &op : operators) {
            cout << "Operator ID: " << op.operator_id << endl;
        }
    }

    static bool loginOperator(const vector<Operator> &operators) {
        string id, pwd;
        cout << "Enter Operator ID: ";
        cin >> id;
        cout << "Enter Password: ";
        pwd = maskPasswordInput();

        for (const auto &op : operators) {
            if (op.operator_id == id && op.password == pwd) {
                cout << "Login successful!" << endl;
                tollPlazaMenu();
                return true;
            }
        }
        cout << "Operator does not exist or incorrect password." << endl;
        return false;
    }

    static string maskPasswordInput() {
        string password;
        char ch;
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        return password;
    }
};

// Global data structures to store vehicles and operators
vector<Vehicle*> vehicles;
vector<Operator> operators;


void searchVehicle(const string &regNo) {
    for (const auto &vehicle : vehicles) {
        if (vehicle->reg_No == regNo) {
            vehicle->printPassingDateAndTime();
            cout << "Toll Amount: " << vehicle->getTollAmount();
            cout << "  Operator ID: " << vehicle->getOperatorId();
            if (dynamic_cast<Bus*>(vehicle)) {
                cout << "  Vehicle Type: Bus" << endl;
            } else if (dynamic_cast<Truck*>(vehicle)) {
                cout << "  Vehicle Type: Truck" << endl;
            } else if (dynamic_cast<Car*>(vehicle)) {
                cout << "  Vehicle Type: Car" << endl;
            }
        }
    }
}
void searchDateToDate(const string &startDate, const string &endDate) {
    for (const auto &vehicle : vehicles) {
        if (vehicle->getDate() >= startDate && vehicle->getDate() <= endDate) {
            vehicle->printPassingDateAndTime();
            cout << " Toll Amount: " << vehicle->getTollAmount();
            cout << " Operator ID: " << vehicle->getOperatorId();
            if (dynamic_cast<Bus*>(vehicle)) {
                cout << "  Vehicle Type: Bus" << endl;
            } else if (dynamic_cast<Truck*>(vehicle)) {
                cout << "  Vehicle Type: Truck" << endl;
            } else if (dynamic_cast<Car*>(vehicle)) {
                cout << "  Vehicle Type: Car" << endl;
            }
        }
    }
}

void searchOperator(const string &operatorId) {
    for (const auto &vehicle : vehicles) {
        if (vehicle->getOperatorId() == operatorId) {
            vehicle->printPassingDateAndTime();
            cout << " Toll Amount: " << vehicle->getTollAmount();
            cout << " Operator ID: " << vehicle->getOperatorId();
            if (dynamic_cast<Bus*>(vehicle)) {
                cout << "  Vehicle Type: Bus" << endl;
            } else if (dynamic_cast<Truck*>(vehicle)) {
                cout << "  Vehicle Type: Truck" << endl;
            } else if (dynamic_cast<Car*>(vehicle)) {
                cout << "  Vehicle Type: Car" << endl;
            }
        }
    }
}

void tollStatistics() {
    cout << "Showing statistics" << endl;
    int busCount = 0, truckCount = 0, carCount = 0;
    double busIncome = 0.0, truckIncome = 0.0, carIncome = 0.0;

    for (const auto &v : vehicles) {
        if (Bus *bus = dynamic_cast<Bus*>(v)) {
            busCount++;
            busIncome += bus->getTollAmount();
        } else if (Truck *truck = dynamic_cast<Truck*>(v)) {
            truckCount++;
            truckIncome += truck->getTollAmount();
        } else if (Car *car = dynamic_cast<Car*>(v)) {
            carCount++;
            carIncome += car->getTollAmount();
        }
    }
    cout << "Total Buses: " << busCount << ", Total Income from Buses: " << busIncome << endl;
    cout << "Total Trucks: " << truckCount << ", Total Income from Trucks: " << truckIncome << endl;
    cout << "Total Cars: " << carCount << ", Total Income from Cars: " << carIncome << endl;
}

void tollSettings() {
    string userneme;
    cout << "Enter Admin Username: ";
    cin >> userneme;
    string password="najmul";
    string pass;
    cout << "Enter Admin Password: ";
    pass = Operator::maskPasswordInput();
    if (pass != password) {
        cout << "Invalid password. Access denied." << endl;
        return;
    }
    int choice;
    cout << "1. Change Bus Toll Amount" << endl;
    cout << "2. Change Truck Toll Amount" << endl;
    cout << "3. Change Car Toll Amount" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
        case 1: {
            double newBusToll;
            cout << "Enter new toll amount for Bus: ";
            cin >> newBusToll;
            for (auto &v : vehicles) {
                if (Bus *bus = dynamic_cast<Bus*>(v)) {
                   bus->setTollAmount(newBusToll);
                }
            }
            cout << "Bus toll amount updated successfully." << endl;
            break;
        }
        case 2: {
            double newTruckToll;
            cout << "Enter new toll amount for Truck: ";
            cin >> newTruckToll;
            for (auto &v : vehicles) {
                if (Truck *truck = dynamic_cast<Truck*>(v)) {
                 truck->setTollAmount(newTruckToll);
                }
            }
            cout << "Truck toll amount updated successfully." << endl;
            break;
        }
        case 3: {
            double newCarToll;
            cout << "Enter new toll amount for Car: ";
            cin >> newCarToll;
            for (auto &v : vehicles) {
                if (Car *car = dynamic_cast<Car*>(v)) {
                    car->setTollAmount(newCarToll);
                }
            }
            cout << "Car toll amount updated successfully." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

int main() {
    while (true) {
        displayMenu();
        int option;
        cin >> option;
        handleOption(option, operators);
    }
}

void displayMenu() {
    cout << "* Toll Plaza: Operator *" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter Your Option: ";
}

void handleOption(int option, vector<Operator> &operators) {
    switch (option) {
        case 1:
            cout << "Logging in:" << endl;
            Operator::loginOperator(operators);
            break;
        case 2:
            cout << "Registering :" << endl;
            Operator::registerOperator(operators);
            break;
        case 3:
            cout << "Thank You" << endl;
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }
}

void tollPlazaMenu() {
    while (true) {
        cout << "******* Toll Plaza Menu ******" << endl;
        cout << "1. Bus" << endl;
        cout << "2. Truck" << endl;
        cout << "3. Car" << endl;
        cout << "4. Search" << endl;
        cout << "5. Statistics" << endl;
        cout << "6. Toll Settings (admin)" << endl;
        cout << "7. Save and Logout" << endl;
        cout << "Enter Your Option (1-7): ";
        int option;
        cin >> option;
        switch (option) {
            case 1:
                cout << "Bus toll processing " << endl;
            {   float changes;
                Bus *bus = new Bus();
                bus->getInput();
                changes=bus->tollCalculate();
                vehicles.push_back(bus);
                cout << "Return "<<changes<<" Taka" << endl;
            }
                break;
            case 2:
                cout << "Truck toll processing" << endl;
            
                {
                    float changes;
                    Truck *truck = new Truck();
                    truck->getInput();
                   changes= truck->tollCalculate();
                    vehicles.push_back(truck);
                    cout << "Return "<<changes<<" Taka" << endl;
                }
                break;
            case 3:
                cout << "Car toll processing" << endl;
                {
                    float changes;
                    Car *car = new Car();
                    car->getInput();
                   changes= car->tollCalculate();
                    vehicles.push_back(car);
                    cout << "Return "<<changes<<" Taka" << endl;
                }
                break;
            case 4:
              searchMenu();
                break;
            case 5:
              tollStatistics();
                break;
            case 6:
                cout << "Toll Settings (admin) " << endl;
                tollSettings();
                break;
            case 7:
                cout << "Saving and logging out" << endl;
                // Handle Save and Logout option
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
    
}
void searchMenu() {
    cout << "Search Menu" << endl;
    cout << "1. Vehicle" << endl;
    cout << "2. Date to Date" << endl;
    cout << "3. Operator" << endl;
    cout << "Enter Your Option (1-3): ";
    int searchOption;
    cin >> searchOption;
    if (searchOption == 1) {
       string regNo;
        cout << "Enter Registration Number: ";
        cin >> regNo;
        searchVehicle(regNo);
    } else if (searchOption == 2) {
        string startDate, endDate;
        cout << "Enter Start Date (DD/MM/YYYY): ";
        cin >> startDate;
        cout << "Enter End Date (DD/MM/YYYY): ";
        cin >> endDate;
        searchDateToDate(startDate, endDate);
    } else if (searchOption == 3) {
        string operatorId;
        cout << "Enter Operator ID: ";
        cin >> operatorId;
        searchOperator(operatorId);
    } else {
        cout << "Invalid option. Please try again." << endl;
    }
}
