// Add
    void addEmployee(string employeeID[], string name[], string jobTitle[], string department[], string gender[], int age[], string hireDate[], double salary[], int &count){

        cout << "\n=========================ADD EMPLOYEE============================\n\n";

        if (count >= MAX_EMPLOYEES){
            cout << "Employee list is full! Can not enter a new employee in\n" << endl;
            return;
        }

        string newID, newName, newJobTitle, newDepartment, newGender, newHireDate;
        int newAge;
        double newMonthlySalary;
        cout << "Please enter the following details for the new employee:\n";
        while (true)
        {
            newID = readNonEmptyLine("Employee ID (e.g., EMP001): "); // Prints prompt & reads non-empty text
            

            bool exists = false; // Flag assumes ID is brand-new
            for (int i = 0; i < count; i++)
            { // Loops through all loaded employees
                if (toLowerCase(employeeID[i]) == toLowerCase(newID))
                {                 
                    exists = true; // Marks duplicate found
                    break;         // Stops searching early
                }
            }

            if (exists)
            {
                cout << newID << " already exists! Please enter a different ID.\n";
            }
            else if (newID.length() != 6)
            {
                cout << "Invalid ID format!: More or less than 6 characters. Please enter a valid ID (e.g., EMP001).\n";
            }
            else if (newID.substr(0, 3) != "EMP")
            {
                cout << "Invalid ID format!: incorrect prefix. Please enter a valid ID (e.g., EMP001).\n";
            }
            else if (!isdigit(newID[3]) || !isdigit(newID[4]) || !isdigit(newID[5]))
            {
                cout << "Invalid ID format!: invalid characters. Please enter a valid ID (e.g., EMP001).\n";
            }
            else
            {
                break; //ID is unique -> exits while loop!
            }
        }
            newName = readNonEmptyLine("Full Name (e.g., Adam Doe): ");
            newJobTitle = readNonEmptyLine("Job Title (e.g., Data Analyst): ");
            newDepartment = readNonEmptyLine("Department (e.g., Analytics): ");
            newGender = readNonEmptyLine("Gender ('F' for female and 'M' for male): ");
            newAge = readIntInRange("Age (e.g., 73): ", 18, 100);
            newHireDate = readNonEmptyLine("Hire Date (e.g., YYYY-MM-DD): ");
            newMonthlySalary = readIntInRange("Monthly Salary (e.g., 5000): ", 1, 1000000);


        // Add the new employee to the arrays
        employeeID[count] = newID;
        name[count] = newName;
        jobTitle[count] = newJobTitle;
        department[count] = newDepartment;
        gender[count] = newGender;
        age[count] = newAge;
        hireDate[count] = newHireDate;
        salary[count] = newMonthlySalary;
        count++;

        // Save the updated list back to employee.txt
        if (saveEmployees(employeeID, name, jobTitle, department, gender, age, hireDate, salary, count))
        {
            cout << "\nEmployee added successfully!\n";
        }
    }