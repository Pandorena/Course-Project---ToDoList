#include "prints.h"
#include "functions.h"
using namespace std;


int main()
{
    string fname;
    string quit_answer;
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
        case 'C':
            choiceC();
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
            cout << "Do you want to save your data?" << endl;
            std::cin.clear();
            std::cin.ignore();
            while (true) {
                cout << "Enter Y,y or N,n: ";
                getline(cin, quit_answer);
                if (quit_answer == "Y" || quit_answer == "y") {
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
                }
                else if (quit_answer == "N" || quit_answer == "n") {
                    cout << "Quitting program." << endl;
                    break;
                }
                else {
                    cout << "Wrong answer. Try again" << endl;
                }
            }
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (toupper(choice) != 'Q');

    return 0;
}