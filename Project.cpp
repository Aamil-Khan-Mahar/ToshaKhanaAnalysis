#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

/*
********************************IMPORTANT*****************************
-PLEASE USE THE DATASET PROVIDED AS IT HAS BEEN CLEANED
-Members: DUAA E AAMIR(25020249) X AAMIL KHAN MAHAR(25020240) X RAMEEL IMRAN(25110030)
-Head TA: Mohtashim Butt
-Assumptions/Edits to the Dataset: 

    1) There were missing cells in Retention Cost and Assessed Value columns of the data hence we used a value Rs.0 in those cells
    2) There were Multiple Variations in the dataset for the Names of the Participants for which we have cleaned it by using standerd names of all participants
    3) There were some dates missing in the dataset for which we have taken the date of the last known date in the Tosha Khana
    4) Some entries contained multiple people for which we have split the entries to individual names hence our dataset has more rows
    5) Consulted with our assinged TA(Mohtashim) about having segmentation faults when the code is compiled through the UI hence please check the TASKS by running the code again for each TASK
*/
const int N = 4233; // Header Row and 4232 Entries
// GIVEN FILE READ FUNCTION
void read_row(string *arr, FILE *input_file) 
{
    char ch;

    for (int i = 0; i < 8; i++) 
    {
        string s = "";
        while ((ch = getc(input_file)) != '\t')
            s += ch == '\n' ? ' ' : ch;
        arr[i] = s;
    }

    string s = "";
    ch = getc(input_file);
    if (ch == '"') 
    {
        while ((ch = getc(input_file)) != '"' && ch != EOF)
            s += ch == '\n' ? ' ' : ch;
        getc(input_file);
    } 
    else 
    {
        s += ch;
        while ((ch = getc(input_file)) != '\n' && ch != EOF)
            s += ch;
    }
    arr[8] = s;
}
/*

Index 0: Detail of gifts
Index 1: Item Category
Index 2: Name of Recipient 
Index 3: Affiliation
Index 4: Date
Index 5: Assessed Value
Index 6: Retention Cost
Index 7: Retained
Index 8: Remarks

*/

// GLOBAL FUNCTIONS
int unique_count(string arr[][9]) //To Find Unique Names in the Dataset
{
    string temp;
    int unique_names; //Number of unqiue names
    int temp_count;
    string temp_array[N-1]; //Stores names in a temp array
    for (int i = 0 ; i < N-1 ; i++)
    {
        temp_array[i] = arr[i+1][2];
    }
    
    for (int i = 0 ; i < N-1  ; i++)
    { 
        temp = temp_array[i];
        for (int j = i + 1 ; j < N-1 ; j++)
        {
            if (temp == temp_array[j])
            {
                temp_array[j] = "-";
            }
        }
    }

    for (int i = 0 ; i < N - 1 ; i++)
    {
        if (temp_array[i] == "-")
        temp_count++;
    }

    unique_names = N - 1 - temp_count;
    return unique_names;
}
void sort2D(string arr[][2], int unique) //Sorts a 2D Array
{   
    int temp;
    for (int i = 0; i < unique; i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < unique; j++) 
        {
            if (stoi(arr[j][1]) > stoi(arr[max_index][1])) //Checking Rows 
            {
                max_index = j;
            }
        }
        if (max_index != i) 
        {
            for (int k = 0; k < 2; k++) //Swapping Rows 
            {
                string temp = arr[i][k];
                arr[i][k] = arr[max_index][k];
                arr[max_index][k] = temp;
            }
        }
    }
}
void print_menu() //Prints the selection menu
{
    cout << endl;
    cout << "Please choose the type information you would like to know by entering the number beside it." << endl;
    cout << "   1 : Top 3 Recipients by Maximum Number of Gifts." << endl;
    cout << "   2 : Top 3 Recipients by Most Expensive Gifts." << endl;
    cout << "   3 : Total Assessed Value of all Gifts." << endl;
    cout << "   4 : Retention Cost paid by a Recipient." << endl;
    cout << "   5 : Recipients who did not Retain any Gifts." << endl;
    cout << "   6 : Recipients who did not pay any Retention Cost." << endl;
    cout << "   7 : Most Expensive Gift." << endl;
    cout << "   8 : Most Expensive Gift that was not Retained." << endl;
    cout << "   9 : Retention Cost above a Limit." << endl;
    cout << "  10 : Innovation function." << endl;
    cout << "  -1 : End the Program." << endl;
    cout << endl;
    cout << "Enter Your Choice: ";

}
string convert_amount(string amount) //Adds Commas to a number
{
    string comma_added_amount = "";
    int n = amount.length();
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (k == 3) {
            comma_added_amount = "," + comma_added_amount;
            k = 0;
        }
        comma_added_amount = amount[i] + comma_added_amount;
        k++;
    }
    return comma_added_amount;
}

// TASK 1
void max_gifts(string arr[][9]) //Computes total number of gifts by each person
{
    int add_count = 0;
    bool add;  
    int unique_couter = 0;
    string temp;
    int unique = unique_count(arr); //Defines array size for Unique names
    string temp_array[unique][2]; //Array of Only Unique Names and second column is counter for each name
    for (int i = 1 ; i < N ;i++)
    {
        temp = arr[i][2];
        add = true;
        for (int j = add_count - 1 ; j >= 0; j--) //Checks Duplicates
        {
            if (temp == temp_array[j][0])
            add = false;
        }
        if (add)
        {
            temp_array[add_count][0] = temp; //Input Unique Name 
            add_count++;
        }
    }
    int temp_count = 0;
    for (int i = 0 ; i < unique ; i++) // Counting Frequency for each person
    {
        temp = temp_array[i][0];
        temp_count = 0;
        for (int j = 1 ; j < N ; j++)
        {
            if (temp == arr[j][2])
            {
                temp_count++;
            }
        }
        temp_array[i][1] = to_string(temp_count);
    }

    sort2D(temp_array, unique); //Sorts it from highest to lowest

    
    cout << "   1 : " << temp_array[0][0] << " received " << temp_array[0][1] << " gifts." << endl;
    cout << "   2 : " << temp_array[1][0] << " received " << temp_array[1][1] << " gifts." << endl;
    cout << "   3 : " << temp_array[2][0] << " received " << temp_array[2][1] << " gifts." << endl;
}
// TASK 1 END

// TASK 2
void expensive_gifts(string arr[][9]) //Computes total number of gifts by each person
{
    int add_count = 0;
    bool add;  
    string temp;
    int unique = unique_count(arr); //Defines array size for Unique names
    string temp_array[unique][2]; //Array of Only Unique Names and second column is counter for each name
    for (int i = 1 ; i < N ;i++)
    {
        temp = arr[i][2];
        add = true;
        for (int j = add_count - 1 ; j >= 0; j--) //Checks Duplicates
        {
            if (temp == temp_array[j][0])
            add = false;
        }
        if (add)
        {
            temp_array[add_count][0] = temp; //Input Unique Name 
            add_count++;
        }
    }
    
    int sum = 0;
    for (int i = 0 ; i < unique; i++) // Counting Frequency for each person
    {
        temp = temp_array[i][0];
        sum = 0;
        for (int j = 1 ; j < N ; j++)
        {
           if (temp == arr[j][2])
            {
                sum += stoi(arr[j][5]);
            }
        }
        temp_array[i][1] = to_string(sum);
    }

    sort2D(temp_array, unique); //Sorts it from highest to lowest
    
    cout << "   1 : " << temp_array[0][0] << " received gifts worth Rs." << convert_amount(temp_array[0][1]) << "." << endl;
    cout << "   2 : " << temp_array[1][0] << " received gifts worth Rs." << convert_amount(temp_array[1][1]) << "." << endl;
    cout << "   3 : " << temp_array[2][0] << " received gifts worth Rs." << convert_amount(temp_array[2][1]) << "." << endl;
    
}
// TASK 2 END

// TASK 3
void total_value(string arr[][9]) //Computes the Total Value of All gifts
{
    long sum = 0;
    for(int i = 1 ; i < N ; i++)
    {
        sum = sum + stoi(arr[i][5]);
    }
    cout <<  "  -> The Total Assessed Value of All Gifts in Tosha Khana is Rs." << convert_amount(to_string(sum)) << endl;
}
// TASK 3 END

// TASK 4
void retention_cost_participant(string name, string arr[][9]) //Computes Retention Cost of a certain participant
{
    bool exists = false;
    for (int i = 1 ; i < N ; i++)
    {
        if (name == arr[i][2])
        {
            exists = true; 
        }
    }

    while (exists == false)
    {
        cout << "Invalid Name Please Enter Again: " ; 
        cin.ignore();
        getline(cin,name);
        for (int i = 1 ; i < N ; i++)
        {
            if (name == arr[i][2])
            {
                exists = true;
                break; 
            }
        }
    }

    long sum_retention = 0;
    for (int j = 1 ; j < N ; j++)
    {
        if (name == arr[j][2])
        {
            sum_retention += stoi(arr[j][6]);
        }
    }
    cout <<  "\tThe Total Retention Cost of " << name << " is Rs." << convert_amount(to_string(sum_retention)) << endl;
}
// TASK 4 END

// TASK 5
void participant_no_retention(string arr[][9]) //Finds the participant who did't retain any gift
{
    int add_count = 0;
    bool add;  
    string temp;
    int unique = unique_count(arr); //Defines array size for Unique names
    string temp_array[unique][2]; //Array of Only Unique Names and second column is counter for each name
    for (int i = 1 ; i < N ;i++)
    {
        temp = arr[i][2];
        add = true;
        for (int j = add_count - 1 ; j >= 0; j--) //Checks Duplicates
        {
            if (temp == temp_array[j][0])
            add = false;
        }
        if (add)
        {
            temp_array[add_count][0] = temp; //Input Unique Name 
            add_count++;
        }
    }

    for (int i = 0 ; i < unique ; i++) //Assigns No to all participants initially 
    {
        temp_array[i][1] = "No";
    }

    for (int i = 0 ; i < unique ; i++)
    {
        temp = temp_array[i][0];
        for (int j = 1 ; j < N ; j++)
        {
            if (temp == arr[j][2])
            {
                if ( (arr[j][7] == "Yes") || (arr[j][7] == "Auctioned") )  //Checks if participants have retained any gift 
                {
                    temp_array[i][1] = "Yes"; 
                }
            }
        }
    }
    int counter = 0;
    for (int i = 0 ; i < unique ; i++)
    {
        if (temp_array[i][1] == "No")
        {
           counter++; 
           cout << "\t"<< counter << " : " << temp_array[i][0] << " did not retain any gift." << endl;
        }
    }
}
// TASK 5 END

// TASK 6
void zero_retention_cost(string arr[][9]) //Finds names of participants who did not pay any retention cost for the gifts they retained.
{
    int add_count = 0;
    bool add;  
    string temp;
    int unique = unique_count(arr); //Defines array size for Unique names
    string temp_array[unique][3]; //Array of Only Unique Names and second column is counter for each name and third is for total retention cost
    for (int i = 1 ; i < N ;i++)
    {
        temp = arr[i][2];
        add = true;
        for (int j = add_count - 1 ; j >= 0; j--) //Checks Duplicates
        {
            if (temp == temp_array[j][0])
            add = false;
        }
        if (add)
        {
            temp_array[add_count][0] = temp; //Input Unique Name 
            add_count++;
        }
    }

    for (int i = 0 ; i < unique ; i++) //Assigns No to all participants initially 
    {
        temp_array[i][1] = "No";
    }

    for (int i = 0 ; i < unique ; i++)
    {
        temp = temp_array[i][0];
        for (int j = 1 ; j < N ; j++)
        {
            if (temp == arr[j][2])
            {
                if (arr[j][7] == "Yes")  //Checks if participants have retained any gift 
                {
                    temp_array[i][1] = "Yes"; 
                }
                else if (arr[j][7] == "Auctioned")
                {
                    temp_array[i][1] = "Auctioned";
                }
            }
        }
    }
    int sum_retention;
    for (int i = 0 ; i < unique ; i++) 
    {
        temp_array[i][2]= "0"; //Intialises total retention cost as zero
        temp = temp_array[i][0];
        sum_retention = 0;
        for (int j = 1 ; j < N ; j++)
        {
            if (temp == arr[j][2]) //Sums retention costs of all participants
            {
                sum_retention += stoi(arr[j][6]);
            }
        }
        temp_array[i][2] = to_string(sum_retention);
    }

    int counter = 0;
    for (int i = 0 ; i < unique ; i++)
    {
        if ( (temp_array[i][1] == "Yes") && (temp_array[i][2] == "0")) //Conditions for retaining a gift but not paying the cost
        {
           counter++; 
           cout << "\t" << counter << " : " << temp_array[i][0] << " did not pay retention for their retained gifts." << endl;
        }
    }
}
// TASK 6 END

// TASK 7 
void most_expensive_gift(string arr[][9]) //Finds the Highest Assessed Value Gift in the Dataset
{
    long value = stoi(arr[1][5]);
    string gift = arr[1][0];
    
    for (int i = 2 ; i < N ; i++)
    {
        if (value < stoi(arr[i][5])) //comparing the assessed values with each other
        {
            value = stoi(arr[i][5]);
            gift = arr[i][0];
        }
    }
    cout << "The Most Expensive Gift Received in Tosha Khana was " << gift << " valued at Rs." << convert_amount(to_string(value)) << endl;
}

// TASK 8 
void most_expensive_not_retained(string arr[][9]) //Finds the Highest Assessed Value Gift in the dataset that was not retained
{
    long value = 0;
    string gift = " ";
    
    
    for (int i = 1 ; i < N ; i++)
    {
        if ( (value < stoi(arr[i][5])) && (arr[i][7] == "No")) //Retained show be No
        {
            value = stoi(arr[i][5]);
            gift = arr[i][0];
        }
    }
    cout << "The Most Expensive Gift Received in Tosha Khana was " << gift << " valued at Rs." << convert_amount(to_string(value)) << endl;
}
// TASK 8 END 

// TASK 9
void retention_cost_over_limit(string arr[][9], long limit) //we pass the limit through the function
{
    int counter = 0;
    for (int i = 1 ; i < N ; i++)
    {
        if (limit < stoi(arr[i][6])) //comparing the dataset values with the input limit.
        {
            counter++;
            cout << "\t" << counter << " : " << arr[i][0] << " has an assessed value of Rs." << convert_amount(arr[i][6]) << endl;
        }
    }
} 
// TASK 9 END 

// TASK 10
void Corruption_analysis(string arr[][9]) //Analyses two kinds of affliation statistics from the dataset 
{
    //finding out number of affiliations
    string temp;
    int unique_affiliations = 0; //Number of unqiue affiliations
    int temp_count;
    string temp_array[N-1]; //Stores names in a temp array
    for (int i = 0 ; i < N-1 ; i++)
    {
        temp_array[i] = arr[i+1][3];
    }
    
    for (int i = 0 ; i < N - 1  ; i++)
    { 
        temp = temp_array[i];
        for (int j = i + 1 ; j < N - 1 ; j++)
        {
            if (temp == temp_array[j])
            {
                temp_array[j] = "-";
            }
        }
    }

    for (int i = 0 ; i < N - 1 ; i++)
    {
        if (temp_array[i] == "-")
        temp_count++;
    }

    unique_affiliations = N - 1 - temp_count;

    //Creating an array filled with names of affiliations
    int add_count = 0;
    bool add;  
    int unique_couter = 0;
    string affiliations[unique_affiliations][2];
    for (int i = 1 ; i < N ;i++)
    {
        temp = arr[i][3];
        add = true;
        for (int j = add_count - 1 ; j >= 0; j--) //Checks Duplicates
        {
            if (temp == affiliations[j][0])
            add = false;
        }
        if (add)
        {
            affiliations[add_count][0]= temp; //Input Unique Affiliation Names 
            add_count++;
        }
    }
    
    //Making an array with Years, Affiliations, and corruption coloumns
    int years = 21;
    string corruption_array[unique_affiliations * years][3];
    int row_counter = 0; // stores the row number to input the Array
    for (int i = 0; i < unique_affiliations; i++ )
    {       
        for(int k = 2002 ; k < 2023 ; k++)    // 
        {
            corruption_array[row_counter][0] = to_string(k); // Adds Years
            corruption_array[row_counter][1] = affiliations[i][0]; // Adds affiliation
            row_counter++; 
        }

    }
    
    // Computes Assessed-Retention values to the array
    string temp1;
    long total = 0;

    for (int i = 0 ; i < unique_affiliations * years ; i++)
    {   
        
        total = 0;
        for (int j = 1 ; j < N ; j++)
        {
            temp1 = arr[j][4].substr(arr[j][4].length()-4,4); //finds year of each entry 
            
            if ( (corruption_array[i][0] == temp1 ) && (corruption_array[i][1] == arr[j][3]) )
            {
                total += (stol(arr[j][5]) - stol(arr[j][6]));
                        
            }
        }
        corruption_array[i][2] = to_string(total);    
    }
    //Assigns Non-Affiliated Status to people with an empty affiliation cell in the data
    for (int i = 0 ; i < unique_affiliations * years ; i++)
    {
        if (corruption_array[i][1] == "")
            corruption_array[i][1] = "Non-Affiliated";
    }
 
    //Prints the data summary.
    cout << "The following tells us unpaid value of gifts paid by people of a certain affiliation by Years (there is no printing if the amount is zero)" << endl << endl;
    for (int i = 0 ; i < unique_affiliations * years ; i++)
    {
        if (corruption_array[i][0] =="2002")
            cout << "AFFILIATION: " << corruption_array[i][1] << endl; 
        if (corruption_array[i][2] != "0")
            cout << "\tYear: " << corruption_array[i][0] << " : Rs." << convert_amount(corruption_array[i][2]) << endl;
        if (corruption_array[i][0] == "2022")
            cout << endl;
    }

    //The Following Code computes percentage of all affiliation's total unpaid payments
    long total_temp;
    total = 0;
    for (int i = 0 ; i < unique_affiliations ; i++)
    {
        total_temp = 0;
        for (int j = 1 ; j < N ; j++)
        {
            if (affiliations[i][0] == arr[j][3])
            {
                total_temp += (stoi(arr[j][5]) - stoi(arr[j][6]));
                total += (stoi(arr[j][5]) - stoi(arr[j][6]));
            } 
            
        }
        affiliations[i][1] = to_string(total_temp);
    }
    
    //Printing The Percentages
    cout << endl << endl << "Unpaid Value of the Gifts sorted by affiliations:" << endl << endl;
    for (int i = 0 ; i < unique_affiliations ; i++)
    {   
        if (affiliations[i][0]=="")
            affiliations[i][0] = "Non-affiliated";
        cout << i+1 << " : "<< affiliations[i][0] << endl;
        cout << "    Amount: Rs." << convert_amount(affiliations[i][1]) << endl;
        cout << "    Percentage: " << (stof(affiliations[i][1])/total) * 100 << "%" << endl << endl;
    }
}
// TASK 10 END 

// MAIN PROECT
int main() 
{
    FILE *input_file = fopen("project_data.txt", "r");

    string dataset[N][9];
    for (int i = 0; i < N; i++)
    {
        read_row(dataset[i], input_file);
    }
    
    // Creating a case function to call the respective functions 
    int selection,end;
    long limit;
    string name;

    cout << endl;
    cout << "                                                                           ------------------------------                                                       " << endl;
    cout << "                                                                           X TOSHA KHANA ANALYSIS BOARD X                                                       " << endl;
    cout << "                                                                           ------------------------------                                                       " << endl;

    
    do // Runs the program fully until the User exits the program
    {
        cout << endl;
        cout << "X - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - X" << endl;
        cout << endl;
        cout << "Enter 1 For MENU or -1 to End program! : "; //Asks to enter the Menu
        cin >> end;
        while ((end != 1) && (end != -1)) 
        {
            cout << "Invalid Choice!!! Enter 1 For MENU or -1 to End program! : "; //Asks to enter the Menu
            cin >> end;
        }
        if (end == 1) 
        { 
            print_menu(); //Shows the Menu and Options 
            cin >> selection;
            while ( (selection > 10) || (selection < -1) || (selection == 0))
            {
                cout << "Invalid Choice!!! Choose again : ";
                cin >> selection;
            }
            cout << endl;
            if(selection == 1)
            {
                cout << "Top 3 Recipients by Maximum Number of gifts are: " << endl;
                max_gifts(dataset);
            }
            else if(selection == 2)
            {
                cout << "Top 3 Recipients by Most Expensive Gifts." << endl;
                expensive_gifts(dataset);
            }
            else if(selection == 3)
            {
                cout << "Total Assessed Value of all Gifts:" << endl;
                total_value(dataset);
            }
            else if(selection == 4)
            {
                cout << "Retention Cost paid by a Recipient:" <<endl;
                cout << "Enter Recipient's Name: ";
                cin.ignore();
                getline(cin,name);
                retention_cost_participant(name,dataset);  
            }
            else if(selection == 5)
            {
                cout << "Recipients who did not retain any Gifts:" << endl;
                participant_no_retention(dataset);
            }
            else if(selection == 6)
            {
                cout << "Recipients who did not pay any Retention Cost:" << endl;
                zero_retention_cost(dataset);
            }
            else if(selection == 7)
            {
                cout << "Most Expensive Gift:" << endl;
                most_expensive_gift(dataset);
            }
            else if(selection == 8)
            {
                cout << "Most Expensive Gift that was not Retained:" << endl;
                most_expensive_not_retained(dataset);
            }
            else if(selection == 9)
            {
                cout << "Gifts with Retention Cost Above a certain Limit:" << endl;
                cout << "Enter the Limit: ";
                cin >> limit;
                retention_cost_over_limit(dataset,limit);
            }
            else if(selection == 10)
            {
                Corruption_analysis(dataset);
            }
            else if(selection == -1)
            {
                end = -1;
            }
        }
        else if (end == -1)
            break;
    } while (end != -1 );
    
    
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X                      THANK YOU                      X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X            Instructor: Malik Jahan Khan             X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X               Head TA : Shaban Ahmad                X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X                 TA : Mohtashim Butt                 X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X                    GROUP MEMBERS                    X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X  Duaa-e-Aamir  X  Aamil Khan Mahar  X  Rameel Imran X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "                                                               X    25020249    X      25020240      X    25110030   X    " << endl;
    cout << "                                                               -------------------------------------------------------    " << endl;
    cout << "X - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - X" << endl;

}