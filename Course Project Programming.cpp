#include "prints.h"
#include "functions.h"
using namespace std;


int main()
{
    setlocale(LC_CTYPE, "");
    string fname;
    cout << "Hello, users, welcome to ToDoList created by Veronika Soldatyenkova." << endl;
    char choice;
    do
    {
        // display menu
        printMenu();

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (toupper(choice))
        {
        case 'A':
            choiceA();
            break;
        case 'P':
            choiceP();
            break;
        case 'W':
            cout << "You selected: Write data out." << endl;
            cout << "Enter filename: ";

            std::cin.clear();
            std::cin.ignore();
            getline(cin, fname);
            if (fname.empty()) {
                cout << "Filename cannot be empty. Please try again." << endl;
                break;
            }
            write_txs(fname);
            break;
        case 'R':
            cout << "You selected: Read data in." << endl;
            cout << "Enter the name of the file to read from: ";
            std::cin.clear();
            std::cin.ignore();
            getline(cin, fname);
            if (fname.empty()) {
                cout << "Filename cannot be empty. Please try again." << endl;
                break;
            }
            read_txs(fname);
            break;
        case 'D':
            deleteTab();
            break;
        case 'Q':
            cout << "Quitting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (toupper(choice) != 'Q');

    return 0;
}