/*
                                                Cloud9 SuperStore Billing System
                                            This program provides the billing services
                                            for the Cloud9 SuperStore.


        \%\ How-To
            1.  The Administrator is requested to first sign up himself using the sign up page which can be accessed by
                pressing 4 in Main menu. After signing up, he need to login into the administrator portal, which
                further can be accessed by pressing 1 in Main menu.
            2.  From thereafter, the administrator can use various functions for product and record managements. The
                detailed function usage is given in the help page.
            3.  To access the help page, the user needs to press 5 in the menu. The help page contains Information about
                the various options present in the program. Please read the help page carefully before using the program.
        ***********************************************************************************************************************

        \%\ Programmer
            This program is developed by Akash Shrivastava, studying in Air Force Golden Jubilee Institute.
            They own all rights for this program.

*/

//Header Files Included for program
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <process.h>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

//Function Prototyping

void add_product();
void modify_product();
void delete_product();
void display_all_products(int);
void search_product();
void place_order();
void main_menu();
void sales_menu();
void admin_menu();
void customer_menu();
void clear_menu();
void clear_data_product();
void signup_admin();
void signup_menu();
void signup_sales();
void Login_admin();
void Login_sales();
void records_menu();
void records_display(int);
void record_search(int);
void modify_record(int);
void delete_record(int);
void records_modify_menu(int);
bool string_compare(string, string);
int check_duplicate_product_code(int);

//Function Prototyping Ends

/* ====================================================================================================================== */
/* ====================================================================================================================== */
/* ====================================================================================================================== */

//Class Declaration for Product
class Product
{
    int product_code;
    string product_name;
    float product_cost;
    int quantity;
    float tax;

public:
    void create_product(int);
    void show_product();
    string give_product_name()
    {
        return product_name;
    }
    float give_product_cost()
    {
        return product_cost;
    }
    int give_product_code()
    {
        return product_code;
    }
};
void Product ::create_product(int code)
{
    product_code = code;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, product_name);
    cout << "Enter cost: ";
    cin >> product_cost;
}
void Product ::show_product()
{
    cout << endl
         << "\t" << left << setw(20) << product_code << setw(40) << product_name << setw(20) << product_cost;
}

//Class Declaration for Administrator
class Admin
{
    string name;
    string username;
    string password;

public:
    void create_admin()
    {
        cout << "\n\tEnter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\tEnter username: ";
        getline(cin, username);
        cout << "\tEnter password: ";
        int ch, i = 0;
        while (ch != '\n')
        {
            ch = _getch();
            if((int)ch != 8) {
                password.push_back(ch);
                cout << '*';
            }
        }
    }
    string get_username()
    {
        return username;
    }
    string get_password()
    {
        return password;
    }
    string get_name()
    {
        return name;
    }
    void show_users()
    {
        cout << endl
             << "  " << setw(20) << left << name << setw(20) << username;
    }
};

//Class Declaration for Sales
class Sales
{
    string username;
    string password;
    string name;

public:
    void create_sales()
    {
        cout << "\n\tEnter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\tEnter username: ";
        getline(cin, username);
        cout << "\tEnter password: ";
        char ch;
        int i = 0;
        while (ch != '\n')
        {
            ch = _getch();
            if((int)ch != 8) {
                password.push_back(ch);
                cout << '*';
            }
        }
    }
    string get_username()
    {
        return username;
    }
    string get_password()
    {
        return password;
    }
    string get_name()
    {
        return name;
    }
    void show_users()
    {
        cout << endl
             << "  " << setw(20) << left << name << setw(20) << username << setw(20) << password;
    }
};
//****************************************************************************************************************//

/* Class Declaration Ends */
/* *************************************************************************************************************************** */

//Global Declaration
fstream file_write;
fstream file_read;
Product product;
Admin admin;
Sales sales;
int current_position;
char current_user[30];

/* *************************************************************************************************************************** */

/*      Login System   */

/*  Sign Up Functions  */

void signup(int selection)
{
    char choice;
    if (selection == 1)
        file_write.open("Admin.dat", ios::out | ios::app | ios::binary);
    else if (selection == 2)
        file_write.open("Sales.dat", ios::out | ios::app | ios::binary);
    while (1)
    {
        if (selection == 1)
        {
            admin.create_admin();
            file_write.write((char *)&admin, sizeof(Admin));
        }
        else if (selection == 2)
        {
            sales.create_sales();
            file_write.write((char *)&sales, sizeof(Sales));
        }
        cout << "\n\tAccount Created Successfully";
        cout << "\n\tDo you want to add another: ";
        cin >> choice;
        if (choice == 'n' || choice == 'N')
            break;
    }
    file_write.close();
    signup_menu();
}

/*    Login Functions   */
//Administrator Login Function
void Login_admin()
{
    system("cls");
    string check_username;
    string check_password;
    int choice;
    bool found=false;
    cout << setw(30) << "\n\t"
         << "Please Login to continue";
    cout << "\n\t"
         << "Enter username: ";
    cin.ignore();
    getline(cin, check_username);
    cout << "\tEnter password: ";
    int ch, i = 0;
    while (ch != 13)
    {
        ch = _getch();
            if((int)ch != 8) {
                check_password.push_back(ch);
                cout << '*';
            }
    }
    file_read.open("Admin.dat", ios::in | ios::binary);
    if (!file_read)
    {
        cout << "\n\tNo Administrator account available, go to Sign up Menu to create a Administrator account!"
             << "\n\tEntering Main Menu\n";
        system("PAUSE");
        main_menu();
    }
    while (file_read.read((char *)&admin, sizeof(Admin)))
    {
        if (string_compare(admin.get_username(), check_username))
        {
            if (string_compare(admin.get_password(), check_password))
            {
                cout << "\n\t\tAccount Validated"
                     << "\n\t\t\tLogin in!";
                file_read.close();
                system("PAUSE");
                admin_menu();
                found = true;
                break;
            }
        }
    }
    file_read.close();
    if (!found)
    {
        cout << "\n\tIncorrect Username or Password!";
    selection_admin_incorrect:
        cout << "\nPress 1 to re-enter details"
             << "\nPress 2 to go to Main menu"
             << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 1)
            Login_admin();
        else if (choice == 2)
            main_menu();
        else
        {
            cout << "Incorrect choice";
            goto selection_admin_incorrect;
        }
    }
}

//Sales Login Function
void Login_sales()
{
    system("cls");
    string check_username, check_password;
    int choice;
    bool found = false;
    cout << setw(30) << "\n\t"
         << "Please Login to continue";
    cout << "\n\t"
         << "Enter username: ";
    cin.ignore();
    getline(cin, check_username);
    cout << "\tEnter password: ";
    getline(cin, check_password);
    file_read.open("Sales.dat", ios::in | ios::binary);
    if (!file_read)
    {
        cout << "\n\tNo Sales account available, go to Sign up Menu to create a Sales account!"
             << "\n\tPress Enter to continue\n";
        getch();
        main_menu();
    }
    while (file_read.read((char *)&admin, sizeof(Admin)))
    {
        if (string_compare(sales.get_username(), check_username))
        {
            if (string_compare(sales.get_password(), check_password))
            {
                cout << "\n\t\tAccount Validated"
                     << "\n\t\t\tLogin in!";
                system("PAUSE");
                sales_menu();
                found = true;
            }
        }
    }
    file_read.close();
    if (!found)
    {
        cout << "\n\tIncorrect Username or Password!";
    selection_sales_incorrect:
        cout << "\nPress 1 to re-enter details"
             << "\nPress 2 to go to Main menu"
             << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 1)
            Login_sales();
        else if (choice == 2)
            main_menu();
        else
        {
            cout << "Incorrect choice";
            goto selection_sales_incorrect;
        }
    }
}
/* Login System Ends*/
/*  ************************************************************************  */

/* ====================================================================================================================== */
/* ====================================================================================================================== */
/* ====================================================================================================================== */
/* Login Records Manipulation */

//Function to Display Login Data Records
void records_display(int selection)
{
    if (selection == 1)
    {
        cout << setw(50) << "Sales Users Record";
        cout << endl
             << "  " << setw(20) << left << "Name" << setw(20) << "Username" << setw(20) << "Password";
        file_read.open("Sales.dat", ios::in);
        while (file_read.read((char *)&sales, sizeof(sales)))
        {
            sales.show_users();
        }
        file_read.close();
        cout << endl
             << endl;
        system("PAUSE");
    }
    else if (selection == 2)
    {
        cout << setw(50) << "Administrator Users Record";
        cout << endl
             << "  " << setw(20) << left << "Name" << setw(20) << "Username";
        file_read.open("Admin.dat", ios::in);
        while (file_read.read((char *)&admin, sizeof(admin)))
        {
            admin.show_users();
        }
        file_read.close();
        cout << endl
             << endl;
        system("PAUSE");
    }
    records_modify_menu(selection);
}

//Function to Search Login Data Record
void record_search(int selection)
{
    string username_t;
    bool found = false;
    if (selection == 1)
    {
        cout << "\n\tEnter Sales Username: ";
        getline(cin, username_t);
        system("cls");
        cout << setw(50) << "Sales Users Record";
        cout << endl
             << "  " << setw(20) << left << "Name" << setw(20) << "Username" << setw(20) << "Password";
        file_read.open("Sales.dat", ios::in);
        while (file_read.read((char *)&sales, sizeof(sales)))
        {
            if (string_compare(sales.get_username(), username_t))
            {
                sales.show_users();
                found = true;
            }
        }
        file_read.close();
        cout << endl
             << endl;
        system("PAUSE");
    }
    else if (selection == 2)
    {
        cout << "\n\tEnter Administrator Username: ";
        cin >> username_t;
        system("cls");
        cout << setw(50) << "Administrator Users Record";
        cout << endl
             << "  " << setw(20) << left << "Name" << setw(20) << "Username";
        file_read.open("Admin.dat", ios::in);
        while (file_read.read((char *)&admin, sizeof(admin)))
        {
            if (string_compare(admin.get_username(), username_t))
            {
                admin.show_users();
                found = true;
            }
        }
        file_read.close();
        cout << endl
             << endl;
        system("PAUSE");
    }
    if (!found)
    {
        if (selection == 1)
            cout << "\n\tSales User not found!\n\n";
        else if (selection == 2)
            cout << "\n\tAdmin User not found!\n\n";
        system("PAUSE");
    }
    records_modify_menu(selection);
}

//Function to Modify Login Records
void modify_record(int selection)
{
    string username_t;
    int pos = 0;
    bool found = false;
    if (selection == 1)
    {
        file_write.open("Sales.dat", ios::in | ios::out);
        cout << "Enter Sales Username: ";
        cin.ignore();
        getline(cin, username_t);
        while (file_write.read((char *)&sales, sizeof(sales)))
        {
            if (string_compare(sales.get_username(), username_t))
            {
                sales.create_sales();
                file_write.seekg(pos, ios::beg);
                file_write.write((char *)&sales, sizeof(sales));
                cout << "\n\tRecord Updated!";
                found = true;
                break;
            }
            pos = file_write.tellg();
        }
    }
    else if (selection == 2)
    {
        file_write.open("Admin.dat", ios::in | ios::out);
        cout << "Enter Administrator Username: ";
        cin.ignore();
        getline(cin, username_t);
        while (file_write.read((char *)&admin, sizeof(admin)))
        {
            if (string_compare(admin.get_username(), username_t))
            {
                admin.create_admin();
                file_write.seekg(pos, ios::beg);
                file_write.write((char *)&admin, sizeof(admin));
                cout << "\n\tRecord Updated!";
                found = true;
                break;
            }
            pos = file_write.tellg();
        }
    }
    file_write.close();
    if (!found)
    {
        if (selection == 1)
            cout << "\n\tSales User not found!";
        else if (selection == 2)
            cout << "\n\tAdmin User not found!";
        cout << "\n\tPlease Enter Again!\n\n";
        system("PAUSE");
        modify_record(selection);
    }
    system("PAUSE");
    records_menu();
}

//Function to Delete Login Records
void delete_record(int selection)
{
    string username_t;
    bool found = false;
    file_write.open("temp.dat", ios::out);
    if (selection == 1)
    {
        file_read.open("Sales.dat", ios::in);
        cout << "Enter Sales Username: ";
        cin >> username_t;
        while (file_read.read((char *)&sales, sizeof(sales)))
        {
            if (string_compare(sales.get_username(), username_t))
            {
                found = true;
            }
            else
            {
                file_write.write((char *)&sales, sizeof(sales));
            }
        }
        file_write.close();
        file_read.close();
        remove("Sales.dat");
        rename("temp.dat", "Sales.dat");
    }
    else if (selection == 2)
    {
        file_read.open("Admin.dat", ios::in);
        cout << "Enter Administrator Username: ";
        cin >> username_t;
        while (file_read.read((char *)&admin, sizeof(admin)))
        {
            if (string_compare(admin.get_username(), username_t))
            {
                found = true;
            }
            else
            {
                file_write.write((char *)&admin, sizeof(admin));
            }
        }
        file_write.close();
        file_read.close();
        remove("Admin.dat");
        rename("temp.dat", "Admin.dat");
    }
    if (!found)
    {
        if (selection == 1)
            cout << "\n\tSales User not found!\n\n";
        else if (selection == 2)
            cout << "\n\tAdmin User not found!\n\n";
    }
    else
        cout << "\n\t\tRecord Deleted!!";
    system("PAUSE");
    records_menu();
}
/* Login Record Manipulation Ends */
/*  ********************************************************  */
/* ====================================================================================================================== */
/* ====================================================================================================================== */
/* ====================================================================================================================== */
/* Product Record Manipulation */

//Function to Add Product
void add_product()
{
    system("cls");
    cout << endl
         << endl;
    char choice;
    int flag = 1, code = 0;
    do
    {
        cout << endl
             << "Enter Product Code: ";
        cin >> code;
        if (check_duplicate_product_code(code))
        {
            file_write.open("Product.dat", ios::out | ios::app | ios::binary);
            product.create_product(code);
            file_write.write((char *)&product, sizeof(Product));
            file_write.close();
            cout << "\nProduct Added";
            cout << "\nDo you want to add another product? : ";
            cin >> choice;
            if (choice == 'n' || choice == 'N')
                flag = 0;
        }
        else
        {
            cout << endl
                 << "Product Code Already exists!" << endl;
            system("PAUSE");
        }
    } while (flag);

    admin_menu();
}

//Function to Modify Product
void modify_product()
{
    int code;
    bool found = false;
    system("CLS");
    display_all_products(1);
    cout << endl
         << endl;
    cout << " \n\tTo Modify ";
    cout << "\n\t Enter Product Code: ";
    cin >> code;
    file_write.open("Product.dat", ios::in | ios::out | ios::binary);
    while (file_write.read((char *)&product, sizeof(Product)) && found == 0)
    {
        if (product.give_product_code() == code)
        {
            cout << endl
                 << left << setw(20) << "Product Code" << setw(30) << "Product Name" << setw(30) << "Cost";
            product.show_product();
            cout << "\nEnter new details" << endl;
            product.create_product(code);
            size_t pos = (-1) * sizeof(class Product);
            file_write.seekp(pos, ios::cur);
            file_write.write((char *)&product, sizeof(Product));
            cout << "Record Updated!!";
            found = true;
        }
    }
    file_write.close();
    if (!found)
    {
        cout << "Product not Found!!!";
    }
    else
    {
        display_all_products(1);
    }
    getch();
    admin_menu();
}

//Function to Delete Product
void delete_product()
{
    int code;
    bool found = false;
    system("CLS");
    display_all_products(1);
    cout << endl
         << endl;
    cout << " \tTo delete"
         << "\n\t Enter product: ";
    cin >> code;
    file_read.open("Product.dat", ios::out | ios::in | ios::binary);
    file_write.open("temp.dat", ios::out | ios::binary);
    file_write.seekg(0, ios::beg);
    while (file_read.read((char *)&product, sizeof(Product)))
    {
        if (product.give_product_code() == code)
        {
            found = true;
            cout << "Product being deleted: ";
            cout << "\nCode: " << product.give_product_code()
                 << "\nName: " << product.give_product_name();
        }
        else
        {
            file_write.write((char *)&product, sizeof(Product));
        }
    }
    file_read.close();
    file_write.close();
    remove("Product.dat");
    rename("temp.dat", "Product.dat");

    if (!found)
    {
        cout << "\nProduct not Found!";
        display_all_products(1);
        delete_product();
    }
    else
        cout << "\nRecord Deleted!!!";
    getch();
    admin_menu();
}

//Function to display all products
void display_all_products(int show = 0)
{
    if (show == 0)
        system("cls");
    cout << "\n\t\t\t\t\t"
         << "Products\n\n\n";
    cout << endl
         << "\t" << setw(20) << left << "Product Code" << setw(40) << "Product Name" << setw(20) << "Cost\n";
    file_read.open("Product.dat", ios::in | ios::binary);
    while (file_read.read((char *)&product, sizeof(Product)))
    {
        product.show_product();
    }
    file_read.close();
    if (show == 0)
    {
        getch();
        if (current_position == 1)
            admin_menu();
        else if (current_position == 2)
            sales_menu();
        else if (current_position == 3)
            customer_menu();
        else
            main_menu();
    }
}

//Function to Search Product
void search_product()
{
    system("CLS");
    int flag = 0;
    int code;
    cout << "\n\n\t\tEnter product to search: ";
    cin >> code;
    file_read.open("Product.dat", ios::in | ios::binary);
    while (file_read.read((char *)&product, sizeof(Product)))
    {
        if (product.give_product_code() == code)
        {
            cout << endl
                 << "\t" << left << setw(20) << "Product Code" << setw(40) << "Product Name" << setw(20) << "Cost";
            cout << "\n";
            product.show_product();
            flag = 1;
        }
    }
    file_read.close();
    if (flag == 0)
        cout << "\nProduct Not Found! ";
    getch();
    if (current_position == 1)
        admin_menu();
    else if (current_position == 2)
        sales_menu();
    else if (current_position == 3)
        customer_menu();
    else
        main_menu();
}
/* Product Record Manipulation Ends */
/* ********************************************************************* */

/* To Place Order, Create Invoice and Save Invoice */
//Function to Place Order
void place_order()
{
    system("cls");
    int product_list[50], product_quantity[50];
    int product_count = 0, quantity_count = 0;
    float cost = 0, total_cost = 0, total_amount = 0;
    const float tax = 18;
    int choice_bill;
    cout << endl;
    for (int i = 0; i < 120; i++)
        cout << "*";
    cout << "\n"
         << setw(50) << "Welcome To SuperStore"
         << "\n"
         << setw(35) << "Item List";
    display_all_products(1);
    for (int i = 0; i < 120; i++)
        cout << "*";
    cout << "\n\n****************************************Note: Enter 0 when no more orders to be placed!*********************************"
         << " \n Place your Order ";
    do
    {
        cout << "\n Enter Product code: ";
        cin >> product_list[product_count];
        if (product_list[product_count] == 0)
            break;
        product_count++;
        cout << "\n Enter quantity: ";
        cin >> product_quantity[quantity_count];
        quantity_count++;
    } while (1);
    cout << "        Thank you for placing your order! Press Enter to continue.";
    getch();

    /*                 ***********************Invoice***********************************************            */
    //To Display Invoice

    system("CLS");
    cout << setw(50) << "ORDER INVOICE\n";
    cout << endl
         << left << setw(20) << "S.No." << setw(20) << "Product Code" << setw(30) << "Product Name" << setw(20) << "Cost"
         << setw(10) << "Quantity" << setw(10) << "Total Cost";
    for (int count_order = 0; count_order <= product_count; count_order++)
    {
        file_read.open("Product.dat", ios::in | ios::binary);
        file_read.seekp(0, ios::beg);
        while (file_read.read((char *)&product, sizeof(Product)))
        {
            if (product.give_product_code() == product_list[count_order])
            {
                cost = product.give_product_cost();
                total_cost = cost * product_quantity[count_order];
                cout << "\n"
                     << left << setw(20) << count_order + 1 << setw(20) << product_list[count_order] << setw(30) << product.give_product_name()
                     << setw(20) << cost << setw(10) << product_quantity[count_order] << setw(10) << total_cost;
                total_amount += total_cost;
            }
        }
        file_read.close();
    }
    cout << "\n\n"
         << left << setw(40) << "Total Amount: " << total_amount;
    total_amount = total_amount + (tax / 100) * total_amount;
    cout << "\n"
         << left << setw(40) << "Tax : " << tax << " %";
    cout << "\n"
         << left << setw(40) << "Total Amount(tax incl.) : " << total_amount;
    /*  Invoice Ends  */

    cout << "\n\n\n";
    cout << left << setw(20) << "Press 1 to Save\n"
         << left << setw(20) << "Press 2 for Sales Menu\n"
         << left << setw(20) << "Selection: ";
    cin >> choice_bill;

    /* To save bill */
    if (choice_bill == 1)
    {
        total_amount = 0;
        file_write.open("bill.txt", ios::out | ios::app);
        file_write << setw(50) << "Order Bill\n"
                   << endl
                   << left << setw(20) << "S.No." << setw(20) << "Product Code" << setw(30)
                   << "Product Name" << setw(20) << "Cost" << setw(10) << "Quantity" << setw(10) << "Total Cost";
        for (int count_order = 0; count_order <= product_count; count_order++)
        {
            file_read.open("Product.dat", ios::in | ios::binary);
            file_read.seekp(0, ios::beg);
            while (file_read.read((char *)&product, sizeof(product)))
            {
                if (product.give_product_code() == product_list[count_order])
                {
                    cost = product.give_product_cost();
                    total_cost = cost * product_quantity[count_order];
                    total_amount += total_cost;
                    file_write << endl
                               << left << setw(20) << count_order + 1 << setw(20) << product_list[count_order]
                               << setw(30) << product.give_product_name()
                               << setw(20) << cost << setw(10) << product_quantity[count_order] << setw(10) << total_cost;
                }
            }
            file_read.close();
        }
        file_write << "\n\n"
                   << left << setw(40) << "Total Amount: " << total_amount;
        total_amount = total_amount + (tax / 100) * total_amount;
        file_write << "\n"
                   << left << setw(40) << "Tax : " << tax << " %"
                   << "\n"
                   << left << setw(40) << "Total Amount(tax incl.) : " << total_amount << endl;
        for (int i = 0; i < 55; i++)
            file_write << "*";
        file_write << "Bill  Ends";
        for (int i = 0; i < 55; i++)
            file_write << "*";
        file_write << "\n\n\n";
        file_write.close();
        cout << "\nBill Saved"
             << "\nPress Enter to go back to Sales Menu\n";
        cin.ignore();
        cin.get();
        sales_menu();
    }
    else if (choice_bill == 2)
    {
        sales_menu();
    }
}

/* Invoice Creation and Saving Ends */
/* ****************************************************** */

/* Functions to Provide services to other functions */

// Function to Compare Strings
bool string_compare(const string old_string, const string new_string)
{
    if (old_string.length() != new_string.length())
        return false;
    for (int i = 0; i <= new_string.length(); i++)
    {
        if (old_string[i] != new_string[i])
            return false;
    }
    return true;
}

int check_duplicate_product_code(int code)
{
    file_read.open("Product.dat", ios::in | ios::binary);
    while (file_read.read((char *)&product, sizeof(product)))
    {
        if (code == product.give_product_code())
        {
            file_read.close();
            return 0;
        }
    }
    file_read.close();
    return 1;
}

/*  Functions to Clear Data  */
void clear_data_product()
{
    remove("Product.dat");
    clear_menu();
}

void clear_data_admin()
{
    remove("Admin.dat");
    clear_menu();
}
void clear_data_sales()
{
    remove("Sales.dat");
    clear_menu();
}

//Function For Help Page
void help_page()
{
    system("cls");
    char data[200];
    file_read.open("help.txt", ios::in);
    while (file_read)
    {
        file_read.getline(data, 200, '$');
        cout << data;
    }
    file_read.close();
    getch();
    main_menu();
}

//Function for Start Program Display
void start_program()
{
    char data[200];
    file_read.open("start.txt", ios::in);
    while (file_read)
    {
        file_read.getline(data, 100, '$');
        cout << data;
    }
    file_read.close();
    getch();
    main_menu();
}
/* Service Functions Ends */
/* ************************************************* */

/* Menu Functions */

//Function for Main menu
void main_menu()
{
    system("cls");
    int choice;
    cout << "\n\n\t\t\t\t"
         << "Welcome to  Cloud9 SuperStore";
    cout << "\n\n\t\t"
         << "Main Menu"
         << "\n\t"
         << "1. Administrator"
         << "\n\t"
         << "2. Sales"
         << "\n\t"
         << "3. Customer"
         << "\n\t"
         << "4. Sign up"
         << "\n\t"
         << "5. Help Page"
         << "\n\t"
         << "6. Exit";
selection_main:
    cout << "\n\t"
         << "Enter your choice: ";
    cin >> choice;
    current_position = choice;
    if (choice == 623)
        admin_menu();
    if (choice == 101)
        sales_menu();
    switch (choice)
    {
    case 1:
        system("cls");
        Login_admin();
        break;
    case 2:
        system("cls");
        Login_sales();
        break;
    case 3:
        system("cls");
        customer_menu();
        break;
    case 4:
        system("cls");
        signup_menu();
        break;
    case 5:
        help_page();
        break;
    case 6:
        exit(0);
        break;
    default:
        cout << "Incorrect input!";
        goto selection_main;
        break;
    }
}

//Function for Administrator menu
void admin_menu()
{
    system("cls");
    int choice;
    cout << "\n\n\t\t\t\t"
         << "Welcome to  Cloud9 SuperStore";
    cout << "\n\n\t\t"
         << "Administrator Menu";
    cout << "\n\t\t"
         << "1. Add Product"
         << "\n\t\t"
         << "2. Modify Product"
         << "\n\t\t"
         << "3. Delete Product"
         << "\n\t\t"
         << "4. Display Product"
         << "\n\t\t"
         << "5. Search Product"
         << "\n\t\t"
         << "6. Records Menu"
         << "\n\t\t"
         << "7. Clear Data Menu"
         << "\n\t\t"
         << "8. Sales Menu"
         << "\n\t\t"
         << "9. Main Menu"
         << "\n\t\t"
         << "10. Exit";
selection_admin:
    cout << "\n\t\t"
         << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        add_product();
        break;
    case 2:
        modify_product();
        break;
    case 3:
        delete_product();
        break;
    case 4:
        display_all_products();
        break;
    case 5:
        search_product();
        break;
    case 6:
        records_menu();
        break;
    case 7:
        clear_menu();
        break;
    case 8:
        sales_menu();
        break;
    case 9:
        main_menu();
        break;
    case 10:
        exit(0);
        break;
    default:
        cout << "Incorrect choice!";
        goto selection_admin;
        break;
    }
}

//Function for Sales menu
void sales_menu()
{
    current_position = 2;
    system("cls");
    int choice;
    cout << "\n\n\t\t\t\t"
         << "Welcome to  Cloud9 SuperStore";
    cout << "\n\n\t\t"
         << "Sales Menu"
         << "\n\t\t"
         << "1. Start Billing"
         << "\n\t\t"
         << "2. Display Products"
         << "\n\t\t"
         << "3. Search Product"
         << "\n\t\t"
         << "4. Main Menu"
         << "\n\t\t"
         << "5. Exit";
selection_sales:
    cout << "\n\t\t"
         << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        place_order();
        break;
    case 2:
        display_all_products();
        break;
    case 3:
        search_product();
        break;
    case 4:
        main_menu();
        break;
    case 5:
        exit(0);
        break;
    default:
        cout << "Incorrect choice!";
        goto selection_sales;
        break;
    }
}

//Function for Customer Menu
void customer_menu()
{
    system("cls");
    int choice;
    cout << "\n\n\t\t\t\t"
         << "Welcome to  Cloud9 SuperStore";
    cout << "\n\n\t\t"
         << "Customer Menu"
         << "\n\t\t"
         << "1. Display Products"
         << "\n\t\t"
         << "2. Search Product"
         << "\n\t\t"
         << "3. Main Menu"
         << "\n\t\t"
         << "4. Exit";
selection_customer:
    cout << "\n\t\t"
         << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        display_all_products();
        break;
    case 2:
        search_product();
        break;
    case 3:
        main_menu();
        break;
    case 4:
        exit(0);
        break;
    default:
        cout << "Incorrect choice!";
        goto selection_customer;
        break;
    }
}

//Function for Sign up Menu
void signup_menu()
{
    system("cls");
    int choice;
    cout << setw(25) << "\n\t\t\t"
         << "Welcome to Sign up Menu";
    cout << setw(15) << "\n\tSign up for...";
    cout << "\n\t\t"
         << "1. Administrator"
         << "\n\t\t"
         << "2. Sales"
         << "\n\t\t"
         << "3. Main Menu"
         << "\n\t\t"
         << "Enter your choice: ";
    cin >> choice;
    if (choice == 3)
        main_menu();
    signup(choice);
    if (choice > 3 || choice < 1)
    {
        cout << "Incorrect Choice! ";
        getch();
        signup_menu();
    }
}

//Function For Records Menu
void records_menu()
{
    system("cls");
    int choice;
    cout << "\n"
         << setw(50) << "Records Menu"
         << "\n\t1. Sales Records"
         << "\n\t2. Administrator Records"
         << "\n\t3. Administrator Menu"
         << "\n\t4. Main Menu"
         << "\n\tSelection: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    case 2:
        records_modify_menu(choice);
        break;
    case 3:
        admin_menu();
        break;
    case 4:
        main_menu();
        break;
    default:
        cout << "Incorrect choice!";
        system("PAUSE");
        records_menu();
    }
}

//Function for Record Modification Menu
void records_modify_menu(int selection)
{
    system("cls");
    int choice;
    cout << "\n"
         << setw(80) << "Records Modification Menu"
         << "\n\t\t"
         << "1. Display"
         << "\n\t\t"
         << "2. Search"
         << "\n\t\t"
         << "3. Modify"
         << "\n\t\t"
         << "4. Delete"
         << "\n\t\t"
         << "5. Records Menu"
         << "\n\t\t"
         << "6. Administrator Menu"
         << "\n\t\t"
         << "7. Main Menu";
selection_customer:
    cout << "\n\t\t"
         << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        system("cls");
        records_display(selection);
        break;
    case 2:
        system("cls");
        record_search(selection);
        break;
    case 3:
        system("cls");
        modify_record(selection);
        break;
    case 4:
        system("cls");
        delete_record(selection);
        break;
    case 5:
        records_menu();
        break;
    case 6:
        admin_menu();
        break;
    case 7:
        main_menu();
        break;
    default:
        cout << "Incorrect choice!";
        goto selection_customer;
    }
}

//Function for Clear Data Menu
void clear_menu()
{
    system("cls");
    int choice;
    cout << "\n\t\t\t"
         << "Clear Data Menu";
    cout << "\n\t"
         << "1. Clear All! "
         << "\n\t"
         << "2. Product File"
         << "\n\t"
         << "3. Administrator Login Data"
         << "\n\t"
         << "4. Sales Login Data"
         << "\n\t"
         << "5. Adminstrator Menu";
    cout << "\nEnter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        clear_data_admin();
        clear_data_product();
        clear_data_sales();
        break;
    case 2:
        clear_data_product();
        break;
    case 3:
        clear_data_admin();
        break;
    case 4:
        clear_data_sales();
        break;
    case 5:
        admin_menu();
        break;
    default:
        cout << "Incorrect choice";
        clear_menu();
        break;
    }
}
/* Menu Functions Ends */
/* *********************************************** */

/* Main Function */
int main()
{
    start_program();
    return 0;
}

/* Main Function Ends */

/* ************************** The Program Ends here! A Program by Akash Shrivastava ***************  */
/*                                      End of Program                                            */
