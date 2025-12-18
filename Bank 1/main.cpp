#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>

using namespace std;

const string FileName = "Clients.txt";

void ShowMainMenue();

struct stClient
{
    string AccountNumber = " ";
    string PinCode = " ";
    string Name = " ";
    string Phone = " ";
    double AccountBalance = 0;
    bool ToBeDeleted = false;
};

enum enMainMenueOptions
{
    enShowClientList = 1,enAddNewClient = 2,enDeleteClient =3,
    enUpdateClient = 4, enFindClient = 5, enExit = 6
};

string ReadAccountNumber()
{
    string AccNumber = "";
    cout << "\nEnter Account Number? ";
    cin >> AccNumber;

    return AccNumber;
}

void ClearScreen()
{
    system("clear");
}

void GoBackToMainMenu()
{
    cout << "Press any key to go back to main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    ClearScreen();
    ShowMainMenue();
}

short ReadMainMenueOption(const short From,const short To)
{
    short Choice = 0;
    do
    {
        cout << "Please Enter Your Choice? [1 to 6]? ";
        cin >> Choice;

    } while (Choice<From || Choice > To);

    return Choice;
}

vector <string> SplitString(string S1,string Sep = "#//#")
{
    vector <string> vWords;
    string sWord;
    short Pos = 0;

    while((Pos=S1.find(Sep))!=std::string::npos) 
    {
        sWord = S1.substr(0,Pos);

        if(sWord!="")
        {
            vWords.push_back(sWord);
        }

        S1.erase(0,Pos+Sep.length());
    }

    if(S1!="")
    {
        vWords.push_back(S1);
    }
    return vWords;
}

stClient ConvertLineToRecord(string stLineData)
{
    stClient Client;
    vector <string> vLineData = SplitString(stLineData); 

    Client.AccountNumber = vLineData[0];
    Client.PinCode = vLineData[1];
    Client.Name = vLineData[2];
    Client.Phone = vLineData[3];
    Client.AccountBalance = stod(vLineData[4]);

    return Client;
}

string ConvertRecordToLine(stClient Client,string Sep = "#//#")
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
    vector <stClient> vClientData;
    fstream MyFile;
    MyFile.open(FileName,ios::in);

    if(MyFile.is_open())
    {
        string Line;
        stClient Client;

        while(getline(MyFile,Line)) //A150#//#1234#//#Mohammed Abu-Hadhoud#//#07333232#//#1000.000000
        {
            Client = ConvertLineToRecord(Line);
            vClientData.push_back(Client);
        }

        MyFile.close();
    }

    return vClientData;
}

void PrintClientRecord(stClient Client)
{
    cout<<"| "<<setw(15)<<left<<Client.AccountNumber;
    cout<<"| "<<setw(10)<<left<<Client.PinCode;
    cout<<"| "<<setw(40)<<left<<Client.Name;
    cout<<"| "<<setw(12)<<left<<Client.Phone;
    cout<<"| "<<setw(12)<<left<<Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector <stClient> vClientData = LoadDataFromFileToVector(FileName);

    cout<<"\t\t\t\tClient List ("<<vClientData.size()<<") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if(vClientData.size()==0)
    {
        cout << "\t\t\t\tNo Clients Available To Show.\n";
    }
    else
    {
        for(stClient &C : vClientData)
        {
        PrintClientRecord(C);
        cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

bool FindClientByAccountNumber(string AccountNumber,vector<stClient>vClient,stClient &Client)
{
    for (stClient C : vClient)
    {
        if(C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

bool ClientExistByAccountNumber(string AccountNumber,string FileName)
{
    fstream MyFile;

    MyFile.open(FileName,ios::in);

    if(MyFile.is_open())
    {
        string Line;
        stClient Client;

        while(getline(MyFile,Line))
        {
            Client = ConvertLineToRecord(Line);

            if(Client.AccountNumber==AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();
    }
}

stClient ReadNewClient()
{
    stClient Client;

    cout << "Enter Account Number? ";
    getline(cin>>ws,Client.AccountNumber);

    while(ClientExistByAccountNumber(Client.AccountNumber,FileName))
    {
        cout << "\nClient with ["<<Client.AccountNumber<<"] already exists, Enter Another Account Number? ";
        getline(cin>>ws,Client.AccountNumber);
    }

    cout << "\nEnter PinCode? ";
    getline(cin,Client.PinCode);

    cout << "\nEnter Name? ";
    getline(cin,Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin,Client.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector <stClient> SaveClientsDataToFile(string FileName,vector<stClient>vClient)
{
    fstream MyFile;
    MyFile.open(FileName,ios::out);

    string DataLine;

    if(MyFile.is_open())
    {

        for(stClient C : vClient)
        {
            if(!C.ToBeDeleted)
            {
                DataLine = ConvertRecordToLine(C);

                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClient;

}

void AddDataLineToFile(string FileName,string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName,ios::out|ios::app);

    if(MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        
        MyFile.close();
    }
}

void AddNewClient()
{
    stClient Client = ReadNewClient();
    
    AddDataLineToFile(FileName,ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char Answer = 'Y';

    do
    {
        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> Answer;  
      
    } while (Answer=='y'||Answer=='Y');
    
}

void ShowAddNewClientsScreen()
{
    cout << "-----------------------------------\n";
    cout << "\tAdd New Clients Screen\n";
    cout << "-----------------------------------\n";

    AddNewClients();

   
}

void PrintClientCard(stClient Client)
{
    cout << "\n" << "The following are the client details:\n";
    cout << "-----------------------------------\n";
    cout << "Account Number: " << Client.AccountNumber << endl;
    cout << "Pin Code: " << Client.PinCode << endl;
    cout << "Name: " << Client.Name << endl;
    cout << "Phone: " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
    cout << "-----------------------------------\n";
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <stClient> &vClient)
{
    for (stClient &C : vClient)
    {
        if(C.AccountNumber == AccountNumber)
        {
            C.ToBeDeleted = true;
            return true;
        }
    }
    return false;
}

void DeleteClientByAccountNumber(string AccountNumber,vector <stClient>vClient)
{
    stClient Client;
    char Answer = 'y';

    if(FindClientByAccountNumber(AccountNumber,vClient,Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to delete this client? y/n? ";
        cin >> Answer;

        if(toupper(Answer)=='Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber,vClient);
            SaveClientsDataToFile(FileName,vClient);
            cout << "\n Client Deleted Successfully.\n";
        }
    }
    else
    {
        cout << "\n" << "Client with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient C;
    C.AccountNumber = AccountNumber;

    cout << "\nEnter PinCode? ";
    getline(cin>>ws,C.PinCode);

    cout << "\nEnter Name? ";
    getline(cin,C.Name);

    cout << "\nEnter Phone? ";
    getline(cin,C.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> C.AccountBalance;

    return C;
}

bool UpdateClientByAccountNumber(string AccountNumber,vector <stClient> &vClient)
{
    stClient Client;
    char Answer = 'y';

    if(FindClientByAccountNumber(AccountNumber,vClient,Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to delete this client? y/n? ";
        cin >> Answer;

        if(toupper(Answer)=='Y')
        {
            for(stClient &C : vClient)
            {
                if(C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(FileName,vClient);
            cout << "\n Client Updated Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\n" << "Client with Account Number (" << AccountNumber << ") is NOT Found!\n";
        return false;
    }
}

void ShowDeleteClientsScreen()
{
    cout << "-----------------------------------\n";
    cout << "\tDelete Clients Screen\n";
    cout << "-----------------------------------\n";

    vector <stClient> vClients = LoadDataFromFileToVector(FileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber,vClients);

}

void ShowUpdateClientsScreen()
{
    cout << "-----------------------------------\n";
    cout << "\tUpdate Clients Screen\n";
    cout << "-----------------------------------\n";
    vector <stClient> vClients = LoadDataFromFileToVector(FileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber,vClients);
}

void ShowFindClientsScreen()
{
    stClient Client;
    cout << "-----------------------------------\n";
    cout << "\tFind Clients Screen\n";
    cout << "-----------------------------------\n";
    vector <stClient> vClients = LoadDataFromFileToVector(FileName);
    string AccountNumber = ReadAccountNumber();

    if(FindClientByAccountNumber(AccountNumber,vClients,Client))
        PrintClientCard(Client);
    else
        cout << "\nClient With Account Number (" << AccountNumber << ") is NOT Found!\n";
}

void ShowExitScreen()
{
    cout << "-----------------------------------\n";
    cout << "\tProgram Ends :-)\n";
    cout << "-----------------------------------\n";
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
        case enShowClientList:
            ClearScreen();
            ShowAllClientsScreen();
            GoBackToMainMenu();
            break;

        case enAddNewClient:
            ClearScreen();
            ShowAddNewClientsScreen();
            GoBackToMainMenu();
            break;

        case enDeleteClient:
            ClearScreen();
            ShowDeleteClientsScreen();
            GoBackToMainMenu();
            break;

        case enUpdateClient:
            ClearScreen();
            ShowUpdateClientsScreen();
            GoBackToMainMenu();
            break;

        case enFindClient:
            ClearScreen();
            ShowFindClientsScreen();
            GoBackToMainMenu();
            break;

        case enExit:
            ClearScreen();
            ShowExitScreen();
            break;
    }
}

void ShowMainMenue()
{
    cout << "\n=========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "=========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "=========================================\n";
    PerformMainMenueOption(enMainMenueOptions(ReadMainMenueOption(1,6)));
}

int main()
{
    ShowMainMenue();
}
