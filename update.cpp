
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

extern string employeeID[];
extern string name[];
extern string jobTitle[];
extern string department[];
extern string gender[];
extern int age[];
extern string hireDate[];
extern double salary[];
extern int employeeCount;

int searchEmployeeByID(string searchID) {
    for (int i = 0; i < employeeCount; i++) {
        if (employeeID[i] == searchID) {
            return i;
        }
    }
    return -1;
}

bool saveEmployees() {
    ofstream outFile("Employee.txt");

    if (!outFile) {
        cout << "Error opening Employee.txt!" << endl;
        return false;
    }

    for (int i = 0; i < employeeCount; i++) {
        outFile << employeeID[i] << '\t'
                << name[i] << '\t'
                << jobTitle[i] << '\t'
                << department[i] << '\t'
                << gender[i] << '\t'
                << age[i] << '\t'
                << hireDate[i] << '\t'
                << salary[i] << '\n';
    }

    outFile.close();

    if (outFile.fail()) {
        cout << "Error saving employee information!" << endl;
        return false;
    }

    return true;
}

void updateEmployee() {
    string searchID;
    int index = -1;
    int choice;

    cout << "Enter Employee ID to update: ";
    cin >> searchID;

    index = searchEmployeeByID(searchID);

    if (index == -1) {
        cout << "Employee not found." << endl;
        return;
    }

    cout << "\n===== UPDATE EMPLOYEE =====" << endl;
    cout << "1. Update Job Title" << endl;
    cout << "2. Update Department" << endl;
    cout << "3. Update Monthly Salary" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
        cout << "Invalid choice!" << endl;
        cin.clear();
        cin.ignore(100000, '\n');
        return;
    }

    switch (choice) {
        case 1:
            cout << "Enter new Job Title: ";
            getline(cin >> ws, jobTitle[index]);
            break;

        case 2:
            cout << "Enter new Department: ";
            getline(cin >> ws, department[index]);
            break;

        case 3: {
            double newSalary;

            cout << "Enter new Monthly Salary: ";
            cin >> newSalary;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(100000, '\n');
                return;
            }

            if (newSalary < 200) {
                cout << "Invalid salary! Salary must be at least 200." << endl;
                return;
            }

            salary[index] = newSalary;
            break;
        }

        case 4:
            cout << "Exiting Update Menu..." << endl;
            return;

        default:
            cout << "Invalid choice." << endl;
            return;
    }

    if (saveEmployees()) {
        cout << "Employee updated successfully!" << endl;
    }
    else {
        cout << "Failed to save employee information." << endl;
    }
}
