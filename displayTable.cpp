#include<iostream>
#include <cctype>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;

    const int MAX_EMPLOYEES = 100;
    const int NUM_FIELDS = 8;
    const string EMPLOYEE_FILE = "employee.txt";
    const string STATS_FILE = "statistics.txt";
    const int TABLE_WIDTH = 114;

    bool loadEmployees(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);
    bool saveEmployees(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);

    //Display
    void printTableHeader();
    void printEmployeeRow(int i, const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[]);
    void displayTable(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);

    //Search
    int searchEmployees(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count, int matchIndex[]);
    void searchMenu(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);

    //Delete
    void removeEmployeeAt(int index, string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);
    void deleteEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);

    // Add
    void addEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);

    // Statistics
    void statistic(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);
    
    //Input validation helpers
    int readIntInRange(const string &prompt, int minValue, int maxValue);
    string readNonEmptyLine(const string &prompt);
    bool readYesNo(const string &prompt);
    string toLowerCase(string text);
    string readForM(const string &prompt);
    string toCapitalize(string text);

    // Error handling
    void printError(const string &msg);
    void printSuccess(const string &msg);

    bool loadEmployees(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count)

    {
        ifstream inFile(EMPLOYEE_FILE);
        if (!inFile) {
            cout<<"Error: cannot open "<<EMPLOYEE_FILE<<endl;
            return false;
        }

        string line;
        count = 0;
        getline(inFile, line);

        while (getline(inFile, line) && count <MAX_EMPLOYEES) {
            if (!line.empty() && line[line.length() -1] == '\r')
            line.erase(line.length() - 1);

            string fields[NUM_FIELDS];
            int fieldCount = 0;
            stringstream ss(line);
            string piece;
            while (getline(ss, piece, '\t')) {
                if (!piece.empty() && fieldCount < NUM_FIELDS)
                    fields[fieldCount++] = piece;
            }

            if (fieldCount != NUM_FIELDS)
            continue;

            employeeID[count]   = fields[0];
            name[count]         = fields[1];
            jobTitle[count]     = fields[2];
            department[count]   = fields[3];
            gender[count]       = fields[4];
            age[count]          = stoi(fields[5]);
            hireDate[count]     = fields[6];
            salary[count]       = stod(fields[7]);
            count++;
        }

        inFile.close();
        return true;
    }

    bool saveEmployees(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count)
    {
        ofstream outFile(EMPLOYEE_FILE);
        if (!outFile) {
            cout<<"Error: cannot write to "<<EMPLOYEE_FILE<<endl;
            return false;
        }

        outFile<<"ID\tFull Name\tJob Title\tDepartment\tGender\tAge\tHire Date\tMonthly Salary\n";

        for(int i =0; i<count; i++) {
            outFile<<employeeID[i]<<'\t'
                   <<name[i]<<'\t'
                   <<jobTitle[i]<<'\t'
                   <<department[i]<<'\t'
                   <<gender[i]<<'\t'
                   <<age[i]<<'\t'
                   <<hireDate[i]<<'\t'
                   <<setprecision(10)<<salary[i]<<'\n';
        }
        outFile.close();
        return true;
    }

    bool saveStats(const string &reportContent)
    {
        ofstream outFile(STATS_FILE);
        if (!outFile)
        {
            cout << "\nError: Could not open " << STATS_FILE << " for writing\n" << endl;
            return false;
        }
        outFile << reportContent;
        outFile.close();
        return true;
    }

    void printTableHeader() {
        cout<< left
            << setw(4)  <<"No."
            << setw(13)  <<"Employee ID"
            << setw(18)  <<"Full Name"
            << setw(27)  <<"Job Title"
            << setw(17)  <<"Department"
            << setw(8)  <<"Gender"
            << setw(5)  <<"Age"
            << setw(12)  <<"Hire Date"
            << right << setw(10) << "Salary(RM)" << endl;
        cout<< string(TABLE_WIDTH, '-')<< endl;
    }

    void printEmployeeRow(int i, const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[])
    {
        cout<< left
            << setw(4)  << (i + 1)
            << setw(13)  << employeeID[i]
            << setw(18)  << name [i]
            << setw(27)  << jobTitle [i]
            << setw(17)  << department [i]
            << setw(8)  << gender [i]
            << setw(5)  << age [i]
            << setw(12)  << hireDate[i]
            << right << setw(10) << fixed << setprecision(2) << salary[i] << endl;
    }

    void displayTable(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count)
    {
        cout<<"\n======================================== EMPLOYEE TABLE ===================================================\n";
        if (count == 0) {
            cout<<"No employee records found.\n";
            return;
        }

        printTableHeader();
        for (int i=0; i<count; i++)
            printEmployeeRow(i, employeeID, name, jobTitle, department, gender, age, hireDate, salary);
        cout<<string(TABLE_WIDTH, '-') << endl;
        cout<< "Total employees: "<<count<<endl;
    }

    int searchEmployees(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count, int matchIndex[])
    {
        cout<<"\nSearch by:\n"
            <<" 1. Employee ID\n"
            <<" 2. Full Name\n"
            <<" 3. Job Title\n"
            <<" 4. Department\n"
            <<" 5. Gender\n"
            <<" 6. Age\n"
            <<" 7. Hire Date (YYYY-MM-DD)\n"
            <<" 8. Monthly Salary\n";
            int choice = readIntInRange("Enter your choice (1-8): ", 1, 8);

            int matches = 0;

            if (choice == 6) {
                int targetAge = readIntInRange("Enter age to search(18-100): ",18, 100);
                for (int i = 0; i<count; i++)
                    if (age[i] == targetAge)
                        matchIndex[matches++] = i;
            }
            else if (choice == 8) {
                int targetSalary = readIntInRange("Enter monthly salary to search (RM): ", 1, 1000000);
                for (int i = 0; i<count; i++)
                    if (salary[i] == targetSalary)
                        matchIndex[matches++] = i;
            }
            else {
                string keyword = toLowerCase(readNonEmptyLine("Enter search keyword: "));
                for (int i = 0; i<count; i++) {
                    string value;
                    switch (choice) {
                        case 1: value = employeeID[i];  break;
                        case 2: value = name[i];        break;
                        case 3: value = jobTitle[i];    break;
                        case 4: value = department[i];  break;
                        case 5: value = gender[i];      break;
                        case 7: value = hireDate[i];    break;
                    }
                    value = toLowerCase(value);

                    bool found = (choice == 5) ? (value == keyword)
                                               : (value.find(keyword) != string::npos);
                    if (found)
                        matchIndex[matches++] = i;
                }
            }
            return matches;
    }

    //Menu option: search and display the matching employees
    void searchMenu(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count)
    {
        cout<<"\n=========================SEARCH EMPLOYEE===============================\n";
        if (count == 0) {
            cout<<"No employee records to search.\n";
            return;
        }

        int matchIndex[MAX_EMPLOYEES];
        int matches = searchEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count, matchIndex);

        if (matches == 0) {
            cout<<"No matching employee found.\n";
            return;
        }

        cout<<"\n"<<matches<<" matching employee(s) found:\n";
        printTableHeader();
        for (int m = 0; m < matches; m++)
            printEmployeeRow(matchIndex[m], employeeID, name, jobTitle, department, gender, age, hireDate, salary);
            cout<<string(TABLE_WIDTH, '-')<<endl;
    }

    // ==================DELETE====================
    void removeEmployeeAt(int index, string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count) 
    {
        for (int i = index; i < count - 1; i++) {
            employeeID[i] = employeeID[i + 1];
            name[i]       = name[i + 1];
            jobTitle[i]   = jobTitle[i + 1];
            department[i] = department[i + 1];
            gender[i]     = gender[i + 1];
            age[i]        = age[i + 1];
            hireDate[i]   = hireDate[i + 1];
            salary[i]     = salary[i + 1];
        }
        count--;
    }

    void deleteEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count)
    {
        cout<<"\n=========================DELETE EMPLOYEE============================\n";
        if (count == 0) {
            cout<<"No employee records to delete.\n";
            return;
        }

        // Find employee(s) with the Search function
        int matchIndex[MAX_EMPLOYEES];
        int matches = searchEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count, matchIndex);

        if (matches == 0) {
            cout<<"No matching employee found. Noting deleted.\n";
            return;
        }

        cout<<"\n"<<matches<<" matching employee(s) found:\n";
        cout<<left<<setw(6)<<"Pick";
        printTableHeader();
        for (int m=0; m<matches; m++){
            cout<<left<<setw(6)<<(m+1);
            printEmployeeRow(matchIndex[m], employeeID, name, jobTitle, department, gender, age, hireDate, salary);
        }
        cout<<string(TABLE_WIDTH, '-')<<endl;

        int pick;
        if (matches == 1) {
            pick = 1;
        }else{
            cout<<"Enter the Pick number to delete one employee, "<<(matches + 1)<<" to delete ALL "<<matches<<" matches, or 0 to cancel.\n";
            pick = readIntInRange("Your choice: ", 0, matches + 1);
            if (pick == 0) {
                cout<<"Delete cancelled.\n";
                return;
            }
        }
        
        //Confirm before delete
        string question;
        if (pick == matches + 1)
            question = "Delete ALL " + to_string(matches) + " employees listed above? (Y/N): ";
        else
            question = "Delete " + employeeID[matchIndex[pick - 1]] + "("+ name[matchIndex[pick - 1]] + ")? (Y/N): ";

            if (!readYesNo(question)) {
                cout<<"Delete cancelled.\n";
                return;
            }

            if (pick == matches + 1) {
                for (int m = matches - 1; m>= 0; m--)
                    removeEmployeeAt(matchIndex[m], employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                    cout<<matches<<" employee(s) deleted.\n";
            } else {
                removeEmployeeAt(matchIndex[pick - 1], employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                cout<<"Employee deleted.\n";
            }

            // Save the updated list back to employee.txt
            if (saveEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count))
                cout<<EMPLOYEE_FILE<<" updated. "<<count<<" employee(s) remaining.\n";
    }

    // Lalitaa'a part

    // Add
    void addEmployee(string employeeID[], string name[], string jobTitle[], string department[],
                     string gender[], int age[], string hireDate[], double salary[], int &count)
    {
        cout << "\n=========================ADD EMPLOYEE============================\n\n";

        if (count >= MAX_EMPLOYEES)
        {
            cout << "Employee list is full! Cannot enter a new employee.\n\n";
            return;
        }

        cout << "Please enter the following details for the new employee:\n";

        // 1. Validate unique Employee ID (Format: EMP001)
        string newID;
        while (true)
        {
            newID = readNonEmptyLine("Employee ID (e.g., EMP001): ");
            for (int i = 0; i < 3 && i < (int)newID.length(); i++)
            {
                newID[i] = toupper(newID[i]);
            }

            bool exists = false;
            for (int i = 0; i < count; i++)
            {
                if (toLowerCase(employeeID[i]) == toLowerCase(newID))
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
            {
                cout << newID << " already exists! Please enter a different ID.\n";
            }
            else if (newID.length() != 6 || newID.substr(0, 3) != "EMP" ||
                     !isdigit(newID[3]) || !isdigit(newID[4]) || !isdigit(newID[5]))
            {
                cout << "Invalid ID format! Please enter a valid ID (e.g., EMP001).\n";
            }
            else
            {
                break;
            }
        }

        // 2. Read and validate remaining fields
        string newName = readNonEmptyLine("Full Name (e.g., Adam Doe): ");
        string newJobTitle = readNonEmptyLine("Job Title (e.g., Data Analyst): ");
        string newDepartment = readNonEmptyLine("Department (e.g., Analytics): ");
        string newGender = readForM("Gender (F/M): ");
        int newAge = readIntInRange("Age (e.g., 73): ", 18, 100);

        int year = readIntInRange("Hire Year (2000-2026): ", 2000, 2026);
        int month = readIntInRange("Hire Month (1-12): ", 1, 12);
        int day = readIntInRange("Hire Day (1-31): ", 1, 31);
        string newHireDate = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-" + (day < 10 ? "0" : "") + to_string(day);

        double newMonthlySalary = readIntInRange("Monthly Salary (e.g., 5000): ", 1, 1000000);

        // 3. Add the new employee to the arrays
        employeeID[count] = newID;
        name[count] = toCapitalize(newName);
        jobTitle[count] = toCapitalize(newJobTitle);
        department[count] = toCapitalize(newDepartment);
        gender[count] = newGender;
        age[count] = newAge;
        hireDate[count] = newHireDate;
        salary[count] = newMonthlySalary;
        count++;

        // 4. Save the updated list back to employee.txt
        if (saveEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count))
        {
            printSuccess("Employee added successfully!");
        }
    }

    // Statistics
    void statistic(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count){
        


        int maleCount = 0, femaleCount = 0;
        for (int i = 0; i < count; i++) {
            if (gender[i] == "Male") maleCount++;
            else if (gender[i] == "Female") femaleCount++;
        }
        double malePct = (maleCount/count)/100;
        double femalePct = (femaleCount/count)/100;
    }
    

    // Input validation helpers
    int readIntInRange(const string &prompt, int minValue, int maxValue)
    {
        while (true) {
            cout<<prompt;
            string input;
            getline(cin, input);

            stringstream ss(input);
            int value;
            char extra;
            if (ss >> value && !(ss >> extra) && value >= minValue && value <= maxValue)
                return value;

            cout<<"Invalid input. Please enter a whole number from "<<minValue<<" to "<<maxValue<<".\n";
        }
    }

    string readNonEmptyLine(const string &prompt) {
        while (true) {
            cout<<prompt;
            string input;
            getline(cin, input);

            if (input.find_first_not_of(" \t") != string::npos)
                return input.substr(input.find_first_not_of(" \t"));

            cout<<"Input cannot be empty. Please try again.\n";
        }
    }

    bool readYesNo(const string &prompt) {
        while (true) {
            cout<<prompt;
            string input;
            getline(cin, input);

            if (input == "Y" || input == "y") return true;
            if (input == "N" || input == "n") return false;

            cout<<"Invalid input. Please enter Y or N.\n";
        }
    }

    string toLowerCase(string text) {
        for (int i = 0; i < (int)text.length(); i++)
            text[i] = tolower(text[i]);
        return text;
    }

    string readForM(const string &prompt) {
        while (true) {
            cout<<prompt;
            string input;
            getline(cin, input);

            if (input == "F" || input == "f") return "Female";
            if (input == "M" || input == "m") return "Male";

            cout<<"Invalid input. Please enter F or M.\n";
        }
    }

    // Extra: toCapitalize function (capitalize the first letter of the string) - use to capitalize in the add function
    string toCapitalize(string text) {
        text[0] = toupper(text[0]);
        return text;
    }

    void printError(const string &msg) {
        cerr << "[ERROR] " << msg << endl;
    }

    void printSuccess(const string &msg) {
        cout << "[SUCCESS] " << msg << endl;
    }

    // ======================MAIN========================

    int main () {
        string employeeID[MAX_EMPLOYEES], name[MAX_EMPLOYEES], jobTitle[MAX_EMPLOYEES];
        string department[MAX_EMPLOYEES], gender[MAX_EMPLOYEES], hireDate[MAX_EMPLOYEES];
        int age[MAX_EMPLOYEES];
        double salary[MAX_EMPLOYEES];
        int count = 0;

        if (!loadEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count))
        return 1;

        int choice;
        do {
            cout << "\n========================MAIN MENU==========================\n"
                 << " 1. Display Table\n"
                 << " 2. Search Employee\n"
                 << " 3. Add Employee\n"
                 << " 4. Delete Employee\n"
                 << " 5. Employee Statistics\n"
                 << " 6. Exit\n";
            choice = readIntInRange("Please enter your choice: ", 1, 6);

            switch (choice)
            {
            case 1:
                displayTable(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 2:
                searchMenu(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 3:
                addEmployee(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 4:
                deleteEmployee(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 5:
                statistic(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 6:
                cout << "Goodbye!\n";
                break;
            }
        } while (choice != 6);
         
        return 0;
    }

