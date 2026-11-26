// Members and Contribution:
// 1. Lalitaa Tripurasundari A/P Tiagrajah : Add Employee, Search Employee, Department Statistics, Salary Histogram, Gender Statistics, Gender Histogram
// 2. Irine Wong Yien Hui : Display Employee Table, Delete Employee, Display Main Menu, Save Employee, Age Histogram
// 3. Foo Yian Teng :Load Employee, Update Employee, Average Salary by Department, Highest/Lowest Salary, Joined-After Statistics, Top 3 and Bottom 3 Monthly Salaries


// SECTION 1: HEADER FILES AND GLOBAL CONSTANTS USED
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


// SECTION 2: FUNCTION DECLARATIONS
    //Display Function (Member: Irine Wong Yien Hui)
    void printTableHeader();
    void printEmployeeRow(int i, const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[]);
    void displayTable(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);

    //Search Function (Member: Irine Wong Yien Hui)
    int searchEmployees(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count, int matchIndex[]);
    void searchMenu(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);

    //Delete Function (Member: Irine Wong Yien Hui)
    void removeEmployeeAt(int index, string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);
    void deleteEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);

    //Add Function (Member: Lalitaa Tripurasundari A/P Tiagrajah)
    void addEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count);

    //Update Function (Member: Foo Yian Teng)
    void updateEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[],int age[],string hireDate[],double salary[],int count);

    //Statistics Section(Member: Lalitaa Tripurasundari A/P Tiagrajah, Irine Wong Yien Hui, Foo Yian Teng)
    void statistic(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);
    bool saveStats(const string &reportContent);

    //Input validation & string helpers
    int readIntInRange(const string &prompt, int minValue, int maxValue);
    string readNonEmptyLine(const string &prompt);
    bool readYesNo(const string &prompt);
    string toLowerCase(string text);
    string readForM(const string &prompt);
    string toCapitalize(string text);

    // Error & Success Message Helpers
    void printError(const string &msg);
    void printSuccess(const string &msg);

// SECTION 3: OPENING EMPLOYEE FILE AND READING DATA INTO ARRAYS
    // Load Employee (Member: Foo Yian Teng)
    // Returns true if successful, false if file cannot be opened
    bool loadEmployees(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count)
    {
        ifstream inFile(EMPLOYEE_FILE);
        if (!inFile) {
            printError("Cannot open " + EMPLOYEE_FILE);
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

    // Save Employee (Member: Irine Wong Yien Hui)
    // Returns true if successful, false if file cannot be opened
    bool saveEmployees(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count)
    {
        ofstream outFile(EMPLOYEE_FILE);
        if (!outFile) {
            printError("Cannot write to " + EMPLOYEE_FILE);
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

// SECTION 4: DISPLAY MENU AND FUNCTIONS
    //Employee Table Display (Member: Irine Wong Yien Hui)
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
        cout<<"\n=========================================== EMPLOYEE TABLE ======================================================\n";
        if (count == 0) {
            printError("No employee records found.");
            return;
        }

        printTableHeader();
        for (int i=0; i<count; i++)
            printEmployeeRow(i, employeeID, name, jobTitle, department, gender, age, hireDate, salary);
        cout<<string(TABLE_WIDTH, '-') << endl;
        cout<< "Total employees: "<<count<<endl;
    }

     //Search Menu (Member: Lalitaa Tripurasundari A/P Tiagrajah)
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
            <<" 8. Monthly Salary\n"
            <<" 9. Cancel (Return to main menu)\n";

            int choice = readIntInRange("Enter your choice (1-9): ", 1, 9);

            int matches = 0;
            if (choice == 9)
            {
                return -1;
            }

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

    //Search Function - Menu
    void searchMenu(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count)
    {
        cout<<"\n=========================SEARCH EMPLOYEE===============================\n";
        if (count == 0) {
            printError("No employee records to search.");
            return;
        }

        int matchIndex[MAX_EMPLOYEES];
        int matches = searchEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count, matchIndex);

    // User selected Cancel from the search menu
    if (matches == -1)
    {
    return;
    }
    // If no matches found 
        if (matches == 0) {
            printError("No matching employee found.");
            return;
        }
    // Display the matching employees
        printSuccess(to_string(matches) + " matching employee(s) found.");
        cout<<"\n"<<matches<<" matching employee(s) found:\n";
        printTableHeader();
        for (int m = 0; m < matches; m++)
            printEmployeeRow(matchIndex[m], employeeID, name, jobTitle, department, gender, age, hireDate, salary);
            cout<<string(TABLE_WIDTH, '-')<<endl;
    }

    // Delete Function (Member: Irine Wong Yien Hui)
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
            printError("No employee records to delete.");
            return;
        }

        // Find employee(s) with the Search function
        int matchIndex[MAX_EMPLOYEES];
        int matches = searchEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count, matchIndex);

        // User selected Cancel from the search menu
        if (matches == -1){
            return;
        }
        if (matches == 0) {
            printError("No matching employee found. Nothing deleted.");
            return;
        }

        printSuccess(to_string(matches) + " matching employee(s) found.");
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
                printError("Delete cancelled.");
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
                printError("Delete cancelled.");
                return;
            }

            if (pick == matches + 1) {
                for (int m = matches - 1; m>= 0; m--)
                    removeEmployeeAt(matchIndex[m], employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                    printSuccess(to_string(matches) + " employee(s) deleted.");
            } else {
                removeEmployeeAt(matchIndex[pick - 1], employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                printSuccess("Employee deleted.");
            }

            // Save the updated list back to employee.txt
            if (saveEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count))
                printSuccess(string(EMPLOYEE_FILE) + " updated. " + to_string(count) + " employee(s) remaining.");
    }
   
    // Update Function (Member: Foo Yian Teng)
        void updateEmployee(
        string employeeID[], string name[], string jobTitle[], string department[], string gender[],int age[],string hireDate[], double salary[],int count)
{
    cout << "\n=========================UPDATE EMPLOYEE============================\n";
        //Checks if there are any employee records to update
         if (count == 0)
        {
            printError("No employee records to update.");
            return;
        }
        //Search for matching employees
        int matchIndex[MAX_EMPLOYEES];

        int matches = searchEmployees(
            employeeID,
            name,
            jobTitle,
            department,
            gender,
            age,
            hireDate,
            salary,
            count,
            matchIndex
            );

        //User selected Cancel from the search menu
        if (matches == -1)
         {
            return;
            }
        //Exit if no matching employees are found
        if (matches == 0)
        {
            printError("No matching employee found.");
            return;
        }

    
        //Display the matching employees 
        printSuccess(to_string(matches) + " matching employee(s) found.");
        cout << "\n" << matches << " matching employee(s) found:\n";

        cout << left << setw(6) << "Pick";
        printTableHeader();

        //Display the matching employees and employee details
        for (int m = 0; m < matches; m++)
        {
        cout << left << setw(6) << (m + 1);
        printEmployeeRow(
        matchIndex[m],
        employeeID,
        name,
        jobTitle,
        department,
        gender,
        age,
        hireDate,
        salary
        );
        }

cout << string(TABLE_WIDTH, '-') << endl;

// User selects employee to update
int pick;

if (matches == 1)
{ pick = 1;
}
else{
    pick = readIntInRange(
        "Select employee to update: ",
        1,
        matches
    );
}

int selected = matchIndex[pick - 1];

// Display update options
    cout << "\n===== UPDATE EMPLOYEE =====\n"
         << "1. Update Job Title\n"
         << "2. Update Department\n"
         << "3. Update Monthly Salary\n"
         << "4. Cancel\n";

    int choice = readIntInRange("Enter your choice: ", 1, 4);

    switch (choice)
    {
        case 1:
            // Update job title
            jobTitle[selected] =
                readNonEmptyLine("Enter new Job Title: ");
            break;

        case 2:
            // Update department
            department[selected] =
                readNonEmptyLine("Enter new Department: ");
            break;

        case 3:
            // Update monthly salary
            salary[selected] =
                readIntInRange(
                    "Enter new Monthly Salary: ",
                    1,
                    1000000
                );
            break;

        case 4:
            // Cancel update operation
            printError("Update cancelled.");
            return;
    }
//Save the updated employee information back to employee.txt
    if (saveEmployees(
            employeeID,
            name,
            jobTitle,
            department,
            gender,
            age,
            hireDate,
            salary,
            count))
    {
        printSuccess("Employee updated successfully!");
    }
}

    // Add Function (Member: Lalitaa Tripurasundari A/P Tiagrajah)
    void addEmployee(string employeeID[], string name[], string jobTitle[], string department[],
                     string gender[], int age[], string hireDate[], double salary[], int &count)
    {
        cout << "\n=========================ADD EMPLOYEE============================\n\n";

        if (count >= MAX_EMPLOYEES)
        {
            printError("Employee list is full! Cannot enter a new employee.");
            return;
        }

        cout << "Please enter the following details for the new employee:\n";

        //Validate unique Employee ID 
        //Format: EMP001; inputs that don't match the format will be rejected with a Error message
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
                printError(newID + " already exists! Please enter a different ID.");
            }
            else if (newID.length() != 6 || newID.substr(0, 3) != "EMP" ||
                     !isdigit(newID[3]) || !isdigit(newID[4]) || !isdigit(newID[5]))
            {
                printError("Invalid ID format! Please enter a valid ID (e.g., EMP001).");
            }
            else
            {
                break;
            }
        }

        //Read and validate remaining fields
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

        //Add the new employee to the arrays
        employeeID[count] = newID;
        name[count] = toCapitalize(newName);
        jobTitle[count] = toCapitalize(newJobTitle);
        department[count] = toCapitalize(newDepartment);
        gender[count] = newGender;
        age[count] = newAge;
        hireDate[count] = newHireDate;
        salary[count] = newMonthlySalary;
        count++;

        //Save the updated list back to employee.txt
        if (saveEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count))
        {
            printSuccess("Employee added successfully!");
        }
    }

    // SECTION 5: STATISTICS FUNCTIONS
    bool saveStats(const string &reportContent)
    {
        ofstream outFile(STATS_FILE);
        if (!outFile)
        {
            printError("Could not open " + STATS_FILE + " for writing.");
            return false;
        }
        outFile << reportContent;
        outFile.close();
        return true;
    }

    void statistic(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count){
        stringstream report; // string.s object that saves all outputs/input in a temp place to be used in one go
        report << fixed << setprecision(2);
        // Sends text into a string variable in RAM instead of the screen or a file.
        cout << endl; // for looks
        report << "=========================================================\n "
            << setw(41) << "COMPANY EMPLOYEE STATISTICS" << "\n"
            "=========================================================\n\n";
        if (count == 0)
        {
            printError("No employee records available.");
            return;
        }

        int maleCount = 0,
            femaleCount = 0;
        int highest[3] = {0}, lowest[3] = {0}; // array to keep the position of highest and lowest ppl 

        string deptNames[MAX_EMPLOYEES]; 
        int deptCounts[MAX_EMPLOYEES] = {0};
        int uniqueDepts = 0; //number of different departments

        int countJoinedAfter2022 = 0;

        int sal5000_7500 = 0, sal7501_9500 = 0, sal9501_10000 = 0, salAbove10000 = 0;
        int age20_30 = 0, age31_40 = 0, ageAbove40 = 0;

        for (int i = 0; i < count; i++)
        { // skims through every employee in the file file
            // GENDER PERCENTAGE
            if (gender[i] == "Male") maleCount++;
            else if (gender[i] == "Female") femaleCount++;

            int foundIndex = -1; // -1 means "not on our sheet yet"
            //Check existing departments on our attendance sheet
            for (int d = 0; d < uniqueDepts; d++){
                if (toLowerCase(deptNames[d]) == toLowerCase(department[i])){
                    foundIndex = d; // Found it at row d!
                    break;
                }
            }
            // Update count or add a new department row
            if (foundIndex != -1){
                deptCounts[foundIndex]++; // Already exists -> add 1 to its count
            }
            else{
                deptNames[uniqueDepts] = department[i]; // New -> write it down
                deptCounts[uniqueDepts] = 1;            // Start its count at 1
                uniqueDepts++;                          // Total unique departments + 1
            }
            if (hireDate[i] > "2022-01-01")
            {
                countJoinedAfter2022++;
            }
    
            if (salary[i] >= 5000 && salary[i] <= 7500) sal5000_7500++;
            else if (salary[i] > 7500 && salary[i] <= 9500) sal7501_9500++;
            else if (salary[i] > 9500 && salary[i] <= 10000) sal9501_10000++;
            else if (salary[i] > 10000) salAbove10000++;

            if (age[i] >= 20 && age[i] <= 30) age20_30++;
            else if (age[i] >= 31 && age[i] <= 40) age31_40++;
            else if (age[i] > 40) ageAbove40++;
            
        }
   
        bool picked[MAX_EMPLOYEES] = {false};
        for (int k = 0; k < 3 && k < count; k++)
        {
            int bestIdx = -1;
            for (int i = 0; i < count; i++){
                if (picked[i])
                    continue;
                if (bestIdx == -1 || salary[i] > salary[bestIdx]){
                    bestIdx = i;
                }
            }
            highest[k] = bestIdx;
            picked[bestIdx] = true;
        }
    
        for (int i = 0; i < count; i++)
            picked[i] = false; // Reset checklist!
        for (int k = 0; k < 3 && k < count; k++)
        {
            int lowIdx = -1;
            for (int i = 0; i < count; i++)
            {
                if (picked[i])
                    continue;
                if (lowIdx == -1 || salary[i] < salary[lowIdx])
                {
                    lowIdx = i;
                }
            }
            lowest[k] = lowIdx;
            picked[lowIdx] = true;
        }
        
        // calculations
        double malePct = ((double)maleCount/count)*100.0;
        double femalePct = ((double)femaleCount/count)*100.0;

    // FINAL OUTPUT FORMATTING 
        report << "---------------------------------------------------------\n"
               << "  [1] GENDER BREAKDOWN\n"
               << "---------------------------------------------------------\n";
        report << left << setw(12) << "  Male:" << maleCount << " (" << malePct << "%)\n";
        report << left << setw(12) << "  Female:" << femaleCount << " (" << femalePct << "%)\n\n";

        report << "---------------------------------------------------------\n"
               << "  [2] HIGHEST & LOWEST MONTHLY SALARY\n"
               << "---------------------------------------------------------\n";
        report << left << setw(32) << " Employee with Highest Salary:"
               << setw(7) << employeeID[highest[0]] << " | "
               << setw(18) << name[highest[0]] << " | "
               << setw(26) << jobTitle[highest[0]] << " | "
               << setw(7) << gender[highest[0]] << " | RM "
               << right << setw(8) << salary[highest[0]] << "\n";

        report << left << setw(32) << " Employee with Lowest Salary:"
               << setw(7) << employeeID[lowest[0]] << " | "
               << setw(18) << name[lowest[0]] << " | "
               << setw(26) << jobTitle[lowest[0]] << " | "
               << setw(7) << gender[lowest[0]] << " | RM "
               << right << setw(8) << salary[lowest[0]] << "\n\n";

        report << "---------------------------------------------------------\n"
               << "  [3] TOP 3 AND BOTTOM 3 MONTHLY SALARIES\n"
               << "---------------------------------------------------------\n";
        report << "  Top 3:\n";
        for (int i = 0; i < 3 && i < count; i++)
        {
            report << "  " << left << i + 1 << setw(3) << "."
                   << setw(7) << employeeID[highest[i]] << " | "
                   << setw(18) << name[highest[i]] << " | "
                   << setw(26) << jobTitle[highest[i]] << " | "
                   << setw(7) << gender[highest[i]] << " | RM "
                   << right << setw(8) << salary[highest[i]] << "\n";
        }
        report << "\n  Bottom 3:\n";
        for (int i = 0; i < 3 && i < count; i++)
        {
            report << "  " << left << i + 1 << setw(3) << "."
                   << setw(7) << employeeID[lowest[i]] << " | "
                   << setw(18) << name[lowest[i]] << " | "
                   << setw(26) << jobTitle[lowest[i]] << " | "
                   << setw(7) << gender[lowest[i]] << " | RM "
                   << right << setw(8) << salary[lowest[i]] << "\n";
        }
        report << "\n";

        report << "---------------------------------------------------------\n"
               << "  [4] EMPLOYEES BY DEPARTMENT\n"
               << "---------------------------------------------------------\n";
        report << "  " << left << setw(20) << "Department"
               << right << setw(16) << "No of Employees"
               << setw(14) << "Percentage" << "\n";
        report << "  ---------------------------------------------------\n";
        for (int i = 0; i < uniqueDepts; i++)
        {
            report << "  " << left << setw(20) << deptNames[i]
                   << right << setw(16) << deptCounts[i]
                   << setw(13) << ((double)deptCounts[i] / count) * 100.0 << "%\n";
        }
        report << "  ---------------------------------------------------\n";
        report << "  " << left << setw(20) << "TOTAL"
               << right << setw(16) << count
               << setw(13) << 100.00 << "%\n\n";

        report << "---------------------------------------------------------\n"
               << "  [5] EMPLOYEES JOINED AFTER 1ST JAN 2022\n"
               << "---------------------------------------------------------\n";
        report << left << setw(25) << "  Number of Employees:" << countJoinedAfter2022 << "\n";
        report << left << setw(25) << "  Percentage (%):" << ((double)countJoinedAfter2022 / count) * 100.0 << "%\n\n";

        report << "---------------------------------------------------------\n"
               << "  [6] HISTOGRAMS\n"
               << "---------------------------------------------------------\n";
        report << "  Note: Each '*' represents 1 employee.\n\n";
        report << "  1. Monthly Salary Distribution\n";
        report << right << setw(24) << "RM 5,000 - RM 7,500" << " | " << left << string(sal5000_7500, '*') << " (" << sal5000_7500 << ")\n";
        report << right << setw(24) << "RM 7,501 - RM 9,500" << " | " << left << string(sal7501_9500, '*') << " (" << sal7501_9500 << ")\n";
        report << right << setw(24) << "Above RM 10,000" << " | " << left << string(salAbove10000, '*') << " (" << salAbove10000 << ")\n\n";

        report << "  2. Gender Distribution\n";
        report << right << setw(24) << "Male" << " | " << left << string(maleCount, '*') << " (" << maleCount << ")\n";
        report << right << setw(24) << "Female" << " | " << left << string(femaleCount, '*') << " (" << femaleCount << ")\n\n";

        report << "  3. Age Distribution\n";
        report << right << setw(24) << "20 - 30" << " | " << left << string(age20_30, '*') << " (" << age20_30 << ")\n";
        report << right << setw(24) << "31 - 40" << " | " << left << string(age31_40, '*') << " (" << age31_40 << ")\n";
        report << right << setw(24) << "Above 40" << " | " << left << string(ageAbove40, '*') << " (" << ageAbove40 << ")\n";

        report << "\n=========================================================\n\n";
        cout << report.str();    // Prints to terminal
        if (saveStats(report.str()))
            printSuccess("Statistics report saved to " + STATS_FILE);
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

            printError("Invalid input. Please enter a whole number from " + to_string(minValue) + " to " + to_string(maxValue) + ".");
        }
    }

    string readNonEmptyLine(const string &prompt) {
        while (true) {
            cout<<prompt;
            string input;
            getline(cin, input);

            if (input.find_first_not_of(" \t") != string::npos)
                return input.substr(input.find_first_not_of(" \t"));

            printError("Input cannot be empty. Please try again.");
        }
    }

    bool readYesNo(const string &prompt) {
        while (true) {
            cout<<prompt;
            string input;
            getline(cin, input);

            if (input == "Y" || input == "y") return true;
            if (input == "N" || input == "n") return false;

            printError("Invalid input. Please enter Y or N.");
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

            printError("Invalid input. Please enter F or M.");
        }
    }

    // Extra: toCapitalize function (capitalize the first letter of the string) - use to capitalize in the add function
    string toCapitalize(string text) {
        text[0] = toupper(text[0]);
        return text;
    }

    void printError(const string &msg) {
        cerr << "\033[31m[ERROR] " << msg << "\033[0m" << endl;
    }

    void printSuccess(const string &msg) {
        cout << "\033[32m[SUCCESS] " << msg << "\033[0m" << endl;
    }

//SECTION 6: DISPLAY MAIN MENU (Member: Irine Wong Yien Hui) 
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
            cout << "\e[1m\n========================MAIN MENU==========================\n"
                 << " 1. Display Table\n"
                 << " 2. Search Employee\n"
                 << " 3. Add Employee\n"
                 << " 4. Delete Employee\n"
                 << " 5. Update Employee\n"
                 << " 6. Employee Statistics\n"
                 << " 7. Exit\n\e[0m";
            choice = readIntInRange("\033[34mPlease enter your choice: \033[0m", 1, 7);

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
                updateEmployee(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 6:
                statistic(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 7:
                cout << "\033[32mGoodbye!\033[0m\n"; //the random letters and numbers is to make the text green
                break;
            }
        } while (choice != 7);
         
        return 0;
    }
