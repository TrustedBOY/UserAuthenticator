#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

class UserAuth
{
    string userName, Email, password;
    fstream file;

public:
    string loginDataPath = "../data/loginData.dat";
    bool login();
    bool signUp();
    bool forget();
} userAuth;

string toLower(string str);
string encryptString(string str);
string decryptString(string str);
void ensureFileExists(string path);

int main()
{
    ensureFileExists(userAuth.loginDataPath);
    string choice;
    do
    {
        cout << "\n1- Login";
        cout << "\n2- Sign-Up";
        // cout<<"\n3- Forgot Password";
        cout << "\n4- Exit";
        cout << "\nEnter Your Choice :: ";
        getline(cin, choice);

        switch (choice[0])
        {
        case '1':
            userAuth.login();
            break;
        case '2':
            userAuth.signUp();
            break;
        // case '3':
        //     userAuth.forgot();
        // break;
        case '4':
            return 0;
        default:
            cout << "Invalid Selection...!";
        }
    } while (true);
}

bool UserAuth ::signUp()
{
    file.open(loginDataPath, ios ::app | ios::out | ios ::binary);
    if (!file.is_open())
    {
        cout << "failed to open the file!\n";
        return false;
    }

    cout << "----------------SignUp----------------";
    cout << "\nEnter Your User Name :: ";
    getline(cin, userName);

    cout << "\nEnter Your E-Mail :: ";
    getline(cin, Email);

    string passwordCheck;
    do
    {
        cout << "\nEnter Your Password   :: ";
        getline(cin, password);

        if (password.length() < 8 || password.length() > 16)
        {
            cout << "Passwords must contain between 8 and 16 character ..." << endl;
            continue;
        }

        cout << "Confirm Your password :: ";
        getline(cin, passwordCheck);

        if (password.compare(passwordCheck) != 0)
            cout << "\nPasswords Do Not Match!!\tRetry...";

    } while (passwordCheck.compare(password) != 0);

    Email = toLower(Email);
    userName = toLower(userName);

    string record = "" + userName + "*" + Email + "*" + password;
    record = encryptString(record);
    file << record << '\n';
    file.close();

    cout << "\nSuccessfully Signed Up ! " << endl
         << "Returning to Menu ...\n";

    return true;
}

bool UserAuth ::login()
{
    file.open(loginDataPath, ios ::in | ios ::out | ios ::binary);

    if (!file.is_open())
    {
        cout << "failed to open the file!\n";
        return false;
    }

    file.seekg(0, ios::end);
    if (file.tellg() == 0)
    {
        cout << "No accounts registered yet!\n";
        file.close();
        return false;
    }
    file.seekg(0, ios::beg);

    string search_UserName, search_Email, search_Password;

    enum class LC
    {
        MAIL,
        USERNAME
    } loginChoice;

    string input;

    cout << endl
         << "----------------Login----------------";

    // choose login method via Username(0) or Email(1)
    do
    {
        cout << "\nLogin with User Name -> 0" << endl
             << "Login with Email     -> 1" << endl;
        getline(cin, input);

        if (input.length() == 1 && (input[0] == '0' || input[0] == '1'))
        {
            loginChoice = input[0] == '0' ? LC::USERNAME : LC::MAIL;
            break;
        }
        else
        {
            cout << "Try Again ...\n\n";
        }
    } while (true);

    if (loginChoice == LC::USERNAME)
    {
        cout << "\nEnter Your Username :: ";
        getline(cin, search_UserName);
        search_UserName = toLower(search_UserName);
    }
    else
    {
        cout << "\nEnter Your Email :: ";
        getline(cin, search_Email);
        search_Email = toLower(search_Email);
    }

    cout << "\nEnter Your Password :: ";
    getline(cin, search_Password);

    string record;

    while (getline(file, record, '\n'))
    {
        record = decryptString(record);

        stringstream ss(record);

        getline(ss, userName, '*');
        getline(ss, Email, '*');
        getline(ss, password, '\n');

        if (loginChoice == LC::USERNAME)
        {
            if (userName.compare(search_UserName) == 0 && password.compare(search_Password) == 0)
            {
                cout << "\nAccount Login Successful...!";
                cout << "\nUsername :: " << userName;
                cout << "\nEmail :: " << Email;
                file.close();
                return true;
            }
        }
        else if (loginChoice == LC::MAIL)
        {
            if (Email.compare(search_Email) == 0 && password.compare(search_Password) == 0)
            {
                cout << "\nAccount Login Successful...!" << endl;
                cout << "\nUsername :: " << userName;
                cout << "\nEmail :: " << Email;
                file.close();
                return true;
            }
        }
    }
    cout << "\nLogin Credentials Do Not Match ...!" << endl;

    file.close();
    return false;
}

string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = (char)tolower(str[i]);
    }

    return str;
}

string encryptString(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = (char)(str[i] + 44);
    }

    return str;
}

string decryptString(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = (char)(str[i] - 44);
    }

    return str;
}

void ensureFileExists(string path)
{
    fstream file(path, ios::app | ios::binary);
    file.close();
}
