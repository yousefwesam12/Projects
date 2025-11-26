#include <iostream>
#include <cctype>
#include <fstream>
#include <stdlib.h>

using namespace std;

const string FileName = "clientss.txt";

string ReadAccountNumber()
{
    string AccountNumber = " ";

    cout << "Please Enter Account Number? ";
    cin >> AccountNumber;

    return AccountNumber;
}

void ClearScreen()
{
    system("clear");
}

struct stClient
{
    string AccountNumber = " ";
    string PinCode = " ";
    string Name = " ";
    string Phone = " ";
    double AccountBalance = 0;
    bool ToBeDeleted = false;
    bool DoDeposit = false;
};

enum enMenuChoices {ShowList = 1, AddClient, DelClient,UpdateInfo,FindClient,Transactions,Exit};

enum enTransChoices {Deposit = 1, Withdraw , TotalBalances , MainMenue};

enMenuChoices ReadChoice(int From,int To)
{
    short Choice = 0;

    do
    {
        cout << "Choose what do you want to do? ["<<From<<" to "<<To<<"]? ";
        cin >> Choice;

        while (cin.fail())
        {
            // user didn't input a number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << endl;
            cin >> Choice;
        }

    } while (Choice < From || Choice > To);

    return enMenuChoices(Choice);
}

enTransChoices ReadTransChoice(int From,int To)
{
    short Choice = 0;

    do
    {
        cout << "Choose what do you want to do? ["<<From<<" to "<<To<<"]? ";
        cin >> Choice;

        while (cin.fail())
        {
            // user didn't input a number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << endl;
            cin >> Choice;
        }

    } while (Choice < From || Choice > To);

    return enTransChoices(Choice);
}

double ReadDepositAmount(int From,int To)
{
    double DepositAmount = 0;

    do
    {
        cout<<"Please Enter Deposit Amount? ";
        cin >> DepositAmount;

    } while (DepositAmount<From || DepositAmount > To);

    return DepositAmount;
}

double ReadWithdrawAmount(int From,int To)
{
    double Withdraw = 0;

    do
    {
        cout<<"Please Enter Withdraw Amount? ";
        cin >> Withdraw;

    } while (Withdraw<From || Withdraw > To);

    return Withdraw;
}

void PrintMainMenuScreen()
{
    cout<<"==============================================================================================\n";
    cout<<"\t\t\t\t\tMain Menue Screen\n";
    cout<<"==============================================================================================\n";
    cout<<"\t\t\t[1] Show Client List.\n";
    cout<<"\t\t\t[2] Add New Client.\n";
    cout<<"\t\t\t[3] Delete Client.\n";
    cout<<"\t\t\t[4] Update Client Info.\n";
    cout<<"\t\t\t[5] Find Client.\n";
    cout<<"\t\t\t[6] Transactions.\n";
    cout<<"\t\t\t[7] Exit.\n";
    cout<<"==============================================================================================\n";
}

vector <string> SplitString(string S1,string Sep = "#//#")
{
    vector <string> vWords;
    string sWord;
    short Pos;

    while ((Pos=S1.find(Sep))!= -1)
    {
        sWord = S1.substr(0,Pos);
        if (sWord!="")
        {
            vWords.push_back(sWord);
        }

        S1.erase(0,Pos+Sep.length());
    }
    if (S1!="")
    {
        vWords.push_back(S1);
    }

    return vWords;
}

stClient ConvertLineToRecord(string Line,string Sep="#//#")
{
    stClient Client;

    vector <string> vClientInfo = SplitString(Line);

    Client.AccountNumber = vClientInfo[0];
    Client.PinCode = vClientInfo[1];
    Client.Name = vClientInfo[2];
    Client.Phone = vClientInfo[3];
    Client.AccountBalance = stod(vClientInfo[4]);

    return Client;
}

string ConvertRecordToLine(stClient Client,string Sep ="#//#")
{
    string Line = Client.AccountNumber + Sep;
    Line += Client.PinCode + Sep;
    Line += Client.Name + Sep;
    Line += Client.Phone + Sep;
    Line += to_string(Client.AccountBalance);

    return Line;
}

vector <stClient> LoadDataFromFileToVector(string FileName)
{
    vector <stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName,ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile,Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();
    }
    return vClients;
}

void PrintClientRecord(stClient Client)
{
    cout<<"| "<<setw(15)<<left<<Client.AccountNumber;
    cout<<"| "<<setw(10)<<left<<Client.PinCode;
    cout<<"| "<<setw(40)<<left<<Client.Name;
    cout<<"| "<<setw(12)<<left<<Client.Phone;
    cout<<"| "<<setw(12)<<left<<Client.AccountBalance;
}

void PrintAllClientsData(vector <stClient> vCLients)
{
    vCLients = LoadDataFromFileToVector(FileName);

    cout<<"\t\t\t\tClient List ("<<vCLients.size()<<") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClient &Client : vCLients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    char AnyKey = ' ' ;

    cout<<"Press any key to go back to Main Menue...";
    cin >> AnyKey;
    system("pause");

}

bool IsAccountNumberUsed(string AccountNumber)
{
    vector <stClient> vClients = LoadDataFromFileToVector(FileName);

    for (stClient &Client : vClients)
    {
        if (Client.AccountNumber==AccountNumber)
        {
            return true;
        }
    }

    return false;

}

bool FindClientByAccountNumber(string AccountNumber,vector<stClient>vClients,stClient &Client)
{
    for (stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector<stClient> &vClients)
{
    for (stClient &C : vClients)
    {
        if (C.AccountNumber==AccountNumber)
        {
            C.ToBeDeleted = true;
            return true;
        }
    }

    return false;
}

void PrintClientCard(stClient Client)
{
    cout<<"The Following are the client details:\n";
    cout<<"---------------------------------\n";
    cout<<"Account Number: "<<Client.AccountNumber<<endl;
    cout<<"Pin Code      : "<<Client.PinCode<<endl;
    cout<<"Name          : "<<Client.Name<<endl;
    cout<<"Phone         : "<<Client.Phone<<endl;
    cout<<"Account Balance: "<<Client.AccountBalance<<endl;
    cout<<"---------------------------------\n";

}

void SaveClientsDataToFile(string FileName,vector <stClient> vClients)
{
    fstream MyFile;

    MyFile.open(FileName,ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.ToBeDeleted == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }
}

void PrintDeleteHeader()
{
    cout<<"---------------------------------\n";
    cout<<"\tDelete Client Screen\n";
    cout<<"---------------------------------\n";
}

bool DeleteClientByAccountNumber(string AccountNumber,vector<stClient> &vClients)
{
    stClient Client;
    vClients = LoadDataFromFileToVector(FileName);

    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        cout<<"\n\n";
        PrintClientCard(Client);

        cout<<"\n\nAre you sure you want delete this client? Y/N? ";
        cin >> Answer;

        if (tolower(Answer)=='y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber,vClients);

            SaveClientsDataToFile(FileName,vClients);


            vClients = LoadDataFromFileToVector(FileName);

            cout << "\n\nClient Deleted Successfully ✅\n";

            return true;
        }
    }
    else
    {
        cout<<"Client With Account Number ("<<AccountNumber<<") is Not Found!\n";
        return false;
    }

}

stClient AddNewClient()
{
    stClient Client;

    cout<<"---------------------------------------\n";
    cout<<"\tAdd New Clients Screen\n";
    cout<<"---------------------------------------\n";

    cout<<"Adding New Client:\n\n";

    cout << "Enter Account Number? ";
    getline(cin>>ws,Client.AccountNumber);

    while (IsAccountNumberUsed(Client.AccountNumber))
    {
        cout <<"Client with ["<<Client.AccountNumber<<"] already exists, Enter Another Number? ";
        getline(cin>>ws,Client.AccountNumber);
    }

    cout << "Enter Pin Code? ";
    getline(cin,Client.PinCode);

    cout<<"Enter Name? ";
    getline(cin,Client.Name);

    cout<<"Enter Phone? ";
    getline(cin,Client.Phone);

    cout<<"Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddDataLineToTheFile(string FileName,string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName,ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddClients()
{
    char AddMore = 'Y';

    do
    {
        stClient Client = AddNewClient();
        AddDataLineToTheFile(FileName,ConvertRecordToLine(Client));
        cout<<"Client Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (AddMore=='Y' || AddMore == 'y');
}

void PrintUpdateHeader()
{
    cout<<"--------------------------------------\n";
    cout<<"\tUpdate Client Info Screen\n";
    cout<<"--------------------------------------\n";
}

void PrintTransactionsMenu()
{
    cout<<"============================================\n";
    cout<<"\tTransactions Menu Screen\n";
    cout<<"============================================\n";
    cout<<"\t[1] Deposit.\n";
    cout<<"\t[2] Withdraw.\n";
    cout<<"\t[3] Total Balances.\n";
    cout<<"\t[4] Main Menue.\n";
    cout<<"============================================\n";

}

void PrintFindClientHeader()
{
    cout<<"--------------------------------------\n";
    cout<<"\tFind Client Screen\n";
    cout<<"--------------------------------------\n";
}

void PrintDepositHeader()
{
    cout<<"--------------------------------------\n";
    cout<<"\tDeposit Screen\n";
    cout<<"--------------------------------------\n";
}

stClient UpdateClientUsingAccountNumber(string AccountNumber,vector<stClient> &vClients)
{

    for (stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountNumber = AccountNumber;

            cout << "Enter PinCode? ";
            cin >> C.PinCode;

            cout << "Enter Name? ";
            getline(cin>>ws,C.Name);

            cout <<"Enter Phone? ";
            getline(cin,C.Phone);

            cout<<"Enter AccountBalance? ";
            cin >> C.AccountBalance;

            return C;
        }
    }
}

void AddUpdatedClientToFile(string AccountNumber,vector<stClient> &vClient)
{
    stClient Client;
    char Answer = 'n';
    vClient = LoadDataFromFileToVector(FileName);

    if (FindClientByAccountNumber(AccountNumber,vClient,Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to update this client? y/n? ";
        cin >> Answer;

        if (tolower(Answer)=='y')
        {
            Client = UpdateClientUsingAccountNumber(AccountNumber,vClient);

            SaveClientsDataToFile(FileName,vClient);

            cout<<"\n\nClient Updated Successfully.\n";
        }
    }
    else
    {
        cout<<"Client With Account Number("<<AccountNumber<<") is not found.\n";
    }
}

void FindClientScreen(string AccountNumber,vector<stClient> vClient)
{
    vClient = LoadDataFromFileToVector(FileName);

    stClient Client;

    if (FindClientByAccountNumber(AccountNumber,vClient,Client))
    {
        cout << "\n\n";
        PrintClientCard(Client);

        char AnyKey = ' ';

        cout<<"\n\nPress any key to go back to Main Menue...";
        cin >> AnyKey;
    }
    else
    {
       cout<<"Client With Account Number ("<<AccountNumber<<") is not found!\n";
    }

}

void DepositScreen(vector<stClient> &vClient)
{
        PrintDepositHeader();
        string AccountNumber = ReadAccountNumber();
        vClient = LoadDataFromFileToVector(FileName);
        char Answer = 'n';

        stClient Client;

        while (!FindClientByAccountNumber(AccountNumber,vClient,Client))
        {
                cout << "Client with ["<<AccountNumber<<"] does not exist.\n";
                AccountNumber = ReadAccountNumber();
        }

        if (FindClientByAccountNumber(AccountNumber,vClient,Client))
        {
            PrintClientCard(Client);
            double DepositAmount = 0;
            DepositAmount = ReadDepositAmount(1,100000);

            cout << "\n\nAre you sure you want to perform this transaction? y/n? ";
            cin >>  Answer;

            if (tolower(Answer) == 'y')
            {
                for (stClient &C : vClient)
                {
                    if (C.AccountNumber == Client.AccountNumber)
                    {
                        C.AccountBalance += DepositAmount;
                        break;
                    }
                }
                SaveClientsDataToFile(FileName,vClient);
            }
        }
}

void PrintAllClientsData(stClient Client,bool IsForBalance)
{
    cout<<"| "<<setw(15)<<left<<Client.AccountNumber;
    cout<<"| "<<setw(40)<<left<<Client.Name;
    cout<<"| "<<setw(12)<<left<<Client.AccountBalance;
    cout<<endl;

}

void TotalBalancesScreen(vector<stClient> vClient)
{
    vClient = LoadDataFromFileToVector(FileName);

    cout<<"\t\t\t\tBalances List ("<<vClient.size()<<") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    long long TotalBalances = 0;

    for (stClient &Client : vClient)
    {
        PrintAllClientsData(Client,true);
        TotalBalances += Client.AccountBalance;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout<<"\t\t\t\tTotal Balances = "<<TotalBalances<<endl;

}

void PrintWithdrawHeader()
{
    cout<<"-----------------------------\n";
    cout<< "\tWithdraw Screen\n";
    cout<<"-----------------------------\n";
}

void WithdrawScreen(vector<stClient> vClient)
{
    PrintWithdrawHeader();
    vClient = LoadDataFromFileToVector(FileName);
    string AccountNumber = ReadAccountNumber();

    stClient Client;

    if (FindClientByAccountNumber(AccountNumber,vClient,Client))
    {
        PrintClientCard(Client);

        double WithdrawAmount = 0;
        WithdrawAmount = ReadWithdrawAmount(1,100000);

        for (stClient &C : vClient)
        {
            if (C.AccountNumber == Client.AccountNumber)
            {

                while (WithdrawAmount>C.AccountBalance)
                {
                    cout<<"\nAmount Exceeds the balance, you can withdraw up to : "<<C.AccountBalance<<endl;
                    cout<< "Please Enter Another Amount? ";
                    cin>> WithdrawAmount;
                }

                if (C.AccountBalance>WithdrawAmount)
                {
                    C.AccountBalance -= WithdrawAmount;
                    SaveClientsDataToFile(FileName,vClient);
                    break;
                }
            }
        }
    }
}

void TransactionScreen(vector<stClient> vClient)
{
    PrintTransactionsMenu();
    enTransChoices enTransactionChoice = ReadTransChoice(1,4);

    switch (enTransactionChoice)
    {
        case Deposit:
            ClearScreen();
            DepositScreen(vClient);
            break;

        case Withdraw:
            ClearScreen();
            WithdrawScreen(vClient);
            break;

        case TotalBalances:
            ClearScreen();
            TotalBalancesScreen(vClient);
            break;

        case MainMenue:
            ClearScreen();
            PrintMainMenuScreen();
            break;
    }
}

void ExitScreen()
{
    cout<<"--------------------------------------\n";
    cout<<"\tProgram Ends :-)\n";
    cout<<"--------------------------------------\n";
}

void StartBankSystem()
{
    enMenuChoices MenuChoices;
    stClient Client;

    PrintMainMenuScreen();
    MenuChoices = ReadChoice(1,7);

    enTransChoices TransChoice;
    vector<stClient> vClients;

    switch (MenuChoices)
    {

        case ShowList:
            ClearScreen();
            PrintAllClientsData(vClients);
            break;

        case AddClient:
            ClearScreen();
            AddClients();
            break;

        case DelClient:
            ClearScreen();
            PrintDeleteHeader();
            DeleteClientByAccountNumber(ReadAccountNumber(),vClients);
            break;

        case UpdateInfo:
            ClearScreen();
            PrintUpdateHeader();
            AddUpdatedClientToFile(ReadAccountNumber(),vClients);
            break;


        case FindClient:
            ClearScreen();
            PrintFindClientHeader();
            FindClientScreen(ReadAccountNumber(),vClients);
            break;

        case Transactions:
            ClearScreen();
            TransactionScreen(vClients);
            break;

        case Exit:
            ClearScreen();
            ExitScreen();
            break;
    }
}

int main()
{
   StartBankSystem();
}