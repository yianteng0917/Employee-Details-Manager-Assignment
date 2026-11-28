// Members and Contribution:
// 1. Lalitaa Tripurasundari A/P Tiagrajah : Add Employee, Search Employee, Department Statistics, Salary Histogram, Gender Statistics, Gender Histogram
// 2. Irine Wong Yien Hui : Display Employee Table, Delete Employee, Display Main Menu, Save Employee, Age Histogram, Sort Employee
// 3. Foo Yian Teng :Load Employee, Update Employee, Average Salary by Department, Highest/Lowest Salary, Joined-After Statistics, Top 3 and Bottom 3 Monthly Salaries


// SECTION 1: HEADER FILES AND GLOBAL CONSTANTS USED
#include<iostream>
#include <cctype>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<ctime>
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

    //Sort Function (Member: Irine Wong Yien Hui)
    void swapEmployees(int a, int b, string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[]);
    bool comesBefore(int a, int b, int field, bool ascending, const string name[], const int age[], const string hireDate[], const double salary[]);
    void sortMenu(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count);

    //Input validation & string helpers
    int readIntInRange(const string &prompt, int minValue, int maxValue);
    string readNonEmptyLine(const string &prompt);
    bool readYesNo(const string &prompt);
    string toLowerCase(string text);
    string readForM(const string &prompt);
    string toCapitalize(string text);
    bool isLeapYear(int year);
    string shortenText(const string &text, int width);
    int daysInMonth(int year, int month);
    void getToday(int &year, int &month, int &day);
    string readTextField(const string &prompt, const string &fieldName, const string &allowedSymbols, int maxLength);

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

        // Turn every field into text first: 8 columns, row 0 is the header
        const string header[NUM_FIELDS] = {"ID", "Full Name", "Job Title", "Department", "Gender", "Age", "Hire Date", "Monthly Salary"};
        string cell[MAX_EMPLOYEES + 1][NUM_FIELDS];
        for (int f = 0; f < NUM_FIELDS; f++)
            cell[0][f] = header[f];
        for (int i = 0; i < count; i++) {
            stringstream sal;
            sal << setprecision(10) << salary[i];
            cell[i + 1][0] = employeeID[i];
            cell[i + 1][1] = name[i];
            cell[i + 1][2] = jobTitle[i];
            cell[i + 1][3] = department[i];
            cell[i + 1][4] = gender[i];
            cell[i + 1][5] = to_string(age[i]);
            cell[i + 1][6] = hireDate[i];
            cell[i + 1][7] = sal.str();
        }

        // Find how many tab stops (8 characters each) each column needs to fit its longest value
        const int TAB_SIZE = 8;
        int columnTabs[NUM_FIELDS];
        for (int f = 0; f < NUM_FIELDS; f++) {
            int longest = 0;
            for (int r = 0; r <= count; r++)
                if ((int)cell[r][f].length() > longest)
                    longest = cell[r][f].length();
            columnTabs[f] = (longest + 2 + TAB_SIZE - 1) / TAB_SIZE;   // at least 2 spaces gap between columns
        }

        // Write each row, adding enough tabs after each field so the columns line up.
        // The file is still tab-separated, so loadEmployees() reads it normally.
        for (int r = 0; r <= count; r++) {
            for (int f = 0; f < NUM_FIELDS; f++) {
                outFile << cell[r][f];
                if (f < NUM_FIELDS - 1) {
                    int tabsNeeded = columnTabs[f] - (int)cell[r][f].length() / TAB_SIZE;
                    outFile << string(tabsNeeded, '\t');
                }
            }
            outFile << '\n';
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
            << setw(18)  << shortenText(name[i], 18)
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

    // Search Menu (Member: Lalitaa Tripurasundari A/P Tiagrajah)
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
                readTextField("Enter new Job Title: ", "Job Title", "&-/", 26);
            break;

        case 2:
            // Update department
            department[selected] =
                readTextField("Enter new Department: ", "Department", "&-/", 16);
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
        string newName = readTextField("Full Name (e.g., Adam Doe): ", "Full Name", "'-.", 100);
        string newJobTitle = readTextField("Job Title (e.g., Data Analyst): ", "Job Title", "&-/", 26);
        string newDepartment = readTextField("Department (e.g., Analytics): ", "Department", "&-/", 16);
        string newGender = readForM("Gender (F/M): ");
        int newAge = readIntInRange("Age (e.g., 73): ", 18, 100);

        // Hire date validation: real calendar dates only (no 31 Feb, 29 Feb only in leap years)
        // and no dates in the future
        int todayYear, todayMonth, todayDay;
        getToday(todayYear, todayMonth, todayDay);

        int year = readIntInRange("Hire Year (2000-" + to_string(todayYear) + "): ", 2000, todayYear);

        int maxMonth = (year == todayYear) ? todayMonth : 12;   // cannot be a future month
        int month = readIntInRange("Hire Month (1-" + to_string(maxMonth) + "): ", 1, maxMonth);

        int maxDay = daysInMonth(year, month);                    // 28, 29, 30 or 31
        if (year == todayYear && month == todayMonth)
            maxDay = todayDay;                                   // cannot be a future day
        int day = readIntInRange("Hire Day (1-" + to_string(maxDay) + "): ", 1, maxDay);
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

    //SAVE IN "statistics.txt" FILE
    bool saveStats(const string &reportContent) // save all content stored in reportContent file stream
    { 
        ofstream outFile(STATS_FILE);
        if (!outFile) // error msg if file fail to open
        {
            printError("Could not open " + STATS_FILE + " for writing.");
            return false;
        }
        outFile << reportContent;
        outFile.close();
        return true;
    }

    void statistic(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count){
        stringstream report; // string.s object that saves all outputs/input in a temp place to be used in one go (Sends text into a string variable in RAM instead of the screen or a file.)
        report << fixed << setprecision(2); // all number outputs in 2 sf

        cout << endl; 
        report << "=========================================================\n "
            << setw(41) << "COMPANY EMPLOYEE STATISTICS" << "\n"
            "=========================================================\n\n";
        if (count == 0) 
        {
            printError("No employee records available.");
            return;
        }
    // DECLERATION OF VARIABLE IN STATS FUNC
        // Gender
        int maleCount = 0,
            femaleCount = 0;
        int highest[3] = {0}, lowest[3] = {0}; // array to keep the position of highest and lowest ppl 

        // Department
        string deptNames[MAX_EMPLOYEES]; 
        int deptCounts[MAX_EMPLOYEES] = {0};
        int uniqueDepts = 0; //number of different departments

        // Employees joined after 1st Jan 2022
        int countJoinedAfter2022 = 0;

        // Sallary and Age category counting
        int sal5000_7500 = 0, sal7501_9500 = 0, sal9501_10000 = 0, salAbove10000 = 0;
        int age20_30 = 0, age31_40 = 0, ageAbove40 = 0;

    // MAIN LOOP - skims through every employee
        for (int i = 0; i < count; i++) { 

    // GENDER PERCENTAGE - LOGIC
            if (gender[i] == "Male") maleCount++;
            else if (gender[i] == "Female") femaleCount++;

    // DEPARTMENT DISTRIBUTION HISTOGRAM - LOGIC
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
            
    // SALARY DISTRIBUTION HISTOGRAM - LOGIC
            if (salary[i] >= 5000 && salary[i] <= 7500) sal5000_7500++;
            else if (salary[i] > 7500 && salary[i] <= 9500) sal7501_9500++;
            else if (salary[i] > 9500 && salary[i] <= 10000) sal9501_10000++;
            else if (salary[i] > 10000) salAbove10000++;

    // AGE DISTRIBUTION HISTOGRAM - LOGIC
            if (age[i] >= 20 && age[i] <= 30) age20_30++;
            else if (age[i] >= 31 && age[i] <= 40) age31_40++;
            else if (age[i] > 40) ageAbove40++;    
        }
    // T0P 3 EMPLOYEES -LOGIC
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
    // BOTTOM 3 EMPLOYEES - LOGIC
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
        
    // TOTAL MALE AND FEMALE PERCENTAGE - LOGIC
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
               << setw(18) << shortenText(name[highest[0]], 18) << " | "
               << setw(26) << jobTitle[highest[0]] << " | "
               << setw(7) << gender[highest[0]] << " | RM "
               << right << setw(8) << salary[highest[0]] << "\n";

        report << left << setw(32) << " Employee with Lowest Salary:"
               << setw(7) << employeeID[lowest[0]] << " | "
               << setw(18) << shortenText(name[lowest[0]], 18) << " | "
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
                   << setw(18) << shortenText(name[highest[i]], 18) << " | "
                   << setw(26) << jobTitle[highest[i]] << " | "
                   << setw(7) << gender[highest[i]] << " | RM "
                   << right << setw(8) << salary[highest[i]] << "\n";
        }
        report << "\n  Bottom 3:\n";
        for (int i = 0; i < 3 && i < count; i++)
        {
            report << "  " << left << i + 1 << setw(3) << "."
                   << setw(7) << employeeID[lowest[i]] << " | "
                   << setw(18) << shortenText(name[lowest[i]], 18) << " | "
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
    
    

    // SECTION 6: SORT FUNCTION (Member: Irine Wong Yien Hui)
    // Swaps two employees (all 8 parallel arrays) at positions a and b
    void swapEmployees(int a, int b, string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[])
    {
        swap(employeeID[a], employeeID[b]);
        swap(name[a],       name[b]);
        swap(jobTitle[a],   jobTitle[b]);
        swap(department[a], department[b]);
        swap(gender[a],     gender[b]);
        swap(age[a],        age[b]);
        swap(hireDate[a],   hireDate[b]);
        swap(salary[a],     salary[b]);
    }

    // Returns true if employee a should come before employee b
    // field: 1 = Salary, 2 = Age, 3 = Hire Date, 4 = Full Name
    bool comesBefore(int a, int b, int field, bool ascending, const string name[], const int age[], const string hireDate[], const double salary[])
    {
        bool less, greater;
        switch (field) {
            case 1:  less = salary[a] < salary[b];      greater = salary[a] > salary[b];      break;
            case 2:  less = age[a] < age[b];            greater = age[a] > age[b];            break;
            case 3:  less = hireDate[a] < hireDate[b];  greater = hireDate[a] > hireDate[b];  break; // YYYY-MM-DD sorts correctly as text
            default: less = toLowerCase(name[a]) < toLowerCase(name[b]);
                     greater = toLowerCase(name[a]) > toLowerCase(name[b]);                   break;
        }
        return ascending ? less : greater;
    }

    // Menu option: display the table sorted by a chosen field.
    // Sorts a COPY of the arrays, so the original order and employee.txt are not changed.
    void sortMenu(const string employeeID[], const string name[], const string jobTitle[], const string department[], const string gender[], const int age[], const string hireDate[], const double salary[], int count)
    {
        cout<<"\n=========================SORT EMPLOYEES=============================\n";
        if (count == 0) {
            printError("No employee records to sort.");
            return;
        }

        cout<<"Sort by:\n"
            <<" 1. Monthly Salary\n"
            <<" 2. Age\n"
            <<" 3. Hire Date\n"
            <<" 4. Full Name\n";
        int field = readIntInRange("Enter your choice (1-4): ", 1, 4);

        cout<<"Order:\n"
            <<" 1. Ascending (low to high / A to Z / oldest first)\n"
            <<" 2. Descending (high to low / Z to A / newest first)\n";
        bool ascending = (readIntInRange("Enter your choice (1-2): ", 1, 2) == 1);

        // Copy the data into local arrays
        string sID[MAX_EMPLOYEES], sName[MAX_EMPLOYEES], sJob[MAX_EMPLOYEES], sDept[MAX_EMPLOYEES];
        string sGender[MAX_EMPLOYEES], sHire[MAX_EMPLOYEES];
        int sAge[MAX_EMPLOYEES];
        double sSalary[MAX_EMPLOYEES];
        for (int i = 0; i < count; i++) {
            sID[i]     = employeeID[i];
            sName[i]   = name[i];
            sJob[i]    = jobTitle[i];
            sDept[i]   = department[i];
            sGender[i] = gender[i];
            sAge[i]    = age[i];
            sHire[i]   = hireDate[i];
            sSalary[i] = salary[i];
        }

        // Selection sort on the copy
        for (int i = 0; i < count - 1; i++) {
            int best = i;
            for (int j = i + 1; j < count; j++)
                if (comesBefore(j, best, field, ascending, sName, sAge, sHire, sSalary))
                    best = j;
            if (best != i)
                swapEmployees(i, best, sID, sName, sJob, sDept, sGender, sAge, sHire, sSalary);
        }

        // Reuse the existing display function to print the sorted copy
        displayTable(sID, sName, sJob, sDept, sGender, sAge, sHire, sSalary, count);
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


    // Text field validation (Full Name, Job Title, Department)
    // - cannot be empty (uses readNonEmptyLine)
    // - only letters, spaces and the symbols in allowedSymbols (e.g. ' in O'Connor, & in R&D)
    // - must contain at least one letter
    // - maximum length so the employee table columns stay aligned
    string readTextField(const string &prompt, const string &fieldName, const string &allowedSymbols, int maxLength)
    {
        while (true) {
            string input = readNonEmptyLine(prompt);

            // Remove spaces at the end
            while (!input.empty() && (input[input.length() - 1] == ' ' || input[input.length() - 1] == '\t'))
                input.erase(input.length() - 1);

            bool validChars = true, hasLetter = false;
            for (int i = 0; i < (int)input.length(); i++) {
                char c = input[i];
                if (isalpha(c))
                    hasLetter = true;
                else if (c != ' ' && allowedSymbols.find(c) == string::npos)
                    validChars = false;
            }

            if (!validChars)
                printError(fieldName + " can only contain letters, spaces and " + allowedSymbols + " (no numbers).");
            else if (!hasLetter)
                printError(fieldName + " must contain at least one letter.");
            else if ((int)input.length() > maxLength)
                printError(fieldName + " is too long. Maximum " + to_string(maxLength) + " characters.");
            else
                return input;
        }
    }

    // Shortens long text for table display so the columns stay aligned.
    // The full text is still saved in employee.txt; only the display is shortened.
    // e.g. "Alexandra Christina Williamson" -> "Alexandra Chris..." (width 18)
    string shortenText(const string &text, int width) {
        if ((int)text.length() < width)
            return text;
        return text.substr(0, width - 4) + "...";
    }

    // Date helpers (used by Add Employee hire date validation)
    // A leap year is divisible by 4, except century years, which must be divisible by 400
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Returns the number of days in the given month (February depends on leap year)
    int daysInMonth(int year, int month) {
        if (month == 2)
            return isLeapYear(year) ? 29 : 28;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;
        return 31;
    }

    // Gets today's date from the computer clock
    void getToday(int &year, int &month, int &day) {
        time_t now = time(0);
        tm *local = localtime(&now);
        year  = local->tm_year + 1900;
        month = local->tm_mon + 1;
        day   = local->tm_mday;
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

//SECTION 7: DISPLAY MAIN MENU (Member: Irine Wong Yien Hui) 
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
                 << " 7. Sort Employees\n"
                 << " 8. Exit\n\e[0m";
            choice = readIntInRange("\033[34mPlease enter your choice: \033[0m", 1, 8);

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
                sortMenu(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count);
                break;
            case 8:
                cout << "\033[32mGoodbye!\033[0m\n"; //the random letters and numbers is to make the text green
                break;
            }
        } while (choice != 8);
         
        return 0;
    }
