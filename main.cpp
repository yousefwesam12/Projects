#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice {Rock=1,Paper=2,Scissors=3};

enum enWinner {Player1=1,Computer=2,Draw=3};

struct stRoundInfo
{
    short RoundNumber;
    enWinner WinnerOfRound;
    string WinnerNameOfRound;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;

};

struct stGameInfo
{
    short NumOfRounds;
    short Player1WinTimes;
    short ComputerWinTimes;
    short DrawTimes;
    enWinner GameWinner;
    string WinnerName;
};

int RandomNumber(int From, int To)
{
    return rand() % (To-From+1) + From;
}

enGameChoice GetComputerChoice()
{
    return enGameChoice(RandomNumber(1,3));
}

enGameChoice ReadPlayerChoice()
{
    short Choice = 0;

    do
    {
        cout<<"\nYour Choice: [1]:Stone,[2]:Paper,[3]:Scissors ? ";
        cin>>Choice;
        
    } while (Choice<1||Choice>3);
    
    return enGameChoice(Choice);
}


string Tabs(short TabsNumber)
{
    string T = " ";

    for (int i = 1; i <= TabsNumber; i++)
    {
        T = T +"\t";
    }

    return T;
}

short ReadHowManyRounds()
{
    short Rounds = 0;

    do
    {
        cout<<"How Many Rounds 1 to 10 ?\n";
        cin>>Rounds;
        
    } while (Rounds<1||Rounds>10);
    
    return Rounds;
}

string GetWinnerName(enWinner Winner)
{
    string ArrOfWinners[3] = {"Player1","Computer","No Winner"};

    return ArrOfWinners[Winner-1];
}

string GetChoiceName(enGameChoice GameChoice)
{
    string ArrOfChoices[3] = {"Rock","Paper","Scissors"};

    return ArrOfChoices[GameChoice-1];
}

enWinner WhoWonTheGame(short Player1WinTimes,short ComputerWinTimes)
{
    if(Player1WinTimes>ComputerWinTimes)
    {
        return Player1;
    }
    else if(Player1WinTimes<ComputerWinTimes)
    {
        return Computer;
    }
    else
    {
        return Draw;
    }
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if(RoundInfo.Player1Choice==RoundInfo.ComputerChoice)
    {
        return Draw;
    }

    switch (RoundInfo.Player1Choice)
    {
    case Rock:
        if(RoundInfo.ComputerChoice==Paper)
        return Computer;
        
    case Scissors:
        if(RoundInfo.ComputerChoice==Rock)
        return Computer;

    case Paper:
        if(RoundInfo.ComputerChoice==Scissors)
        return Computer;
    }

    // Here the winner is Player 1

    return Player1;

}

stGameInfo FillGameResults(short GameRounds,short Player1WinTimes,short ComputerWinTimes,short DrawTimes)
{
    stGameInfo GameInfo;

    GameInfo.NumOfRounds = GameRounds;
    GameInfo.Player1WinTimes = Player1WinTimes;
    GameInfo.ComputerWinTimes = ComputerWinTimes;
    GameInfo.DrawTimes = DrawTimes;
    GameInfo.GameWinner = WhoWonTheGame(Player1WinTimes,ComputerWinTimes);
    GameInfo.WinnerName = GetWinnerName(GameInfo.GameWinner);
    
    return GameInfo;

}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout<<"\n_________________Round["<<RoundInfo.RoundNumber<<"]_________________\n\n";
    cout<<"Player 1 Choice : "<<GetChoiceName(RoundInfo.Player1Choice)<<"\n";
    cout<<"Computer Chocie : "<<GetChoiceName(RoundInfo.ComputerChoice)<<endl;
    cout<<"Round Winner    : "<<GetWinnerName(RoundInfo.WinnerOfRound)<<endl;
    cout<<"__________________________________________\n";
}

stGameInfo PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0,ComputerWinTimes = 0,DrawTimes =0;

    for(short GameRound=1;GameRound<=HowManyRounds;GameRound++)
    {
        cout<<"\nRound ["<<GameRound<<"] begins: \n";

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.WinnerOfRound = WhoWonTheRound(RoundInfo);
        
        if(RoundInfo.WinnerOfRound==Computer)
        {
            ComputerWinTimes++;
        }
        else if(RoundInfo.WinnerOfRound==Player1)
        {
            Player1WinTimes++;
        }
        else
        {
            DrawTimes++;
        }

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(RoundInfo.RoundNumber,Player1WinTimes,ComputerWinTimes,DrawTimes);

}

void ShowGameOverScreen()
{
    cout<<Tabs(2)<<"_______________________________________________________________________\n\n";
    
    cout<<Tabs(2)<<"                        +++ G a m e  O v e r +++                \n\n";
    
    cout<<Tabs(2)<<"_______________________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameInfo GameInfo)
{
    cout<<Tabs(2)<<"Rounds Played      : "<<GameInfo.NumOfRounds<<endl;
    cout<<Tabs(2)<<"Player 1 win times : "<<GameInfo.Player1WinTimes<<endl;
    cout<<Tabs(2)<<"Computer win times : "<<GameInfo.ComputerWinTimes<<endl;
    cout<<Tabs(2)<<"Draw times         : "<<GameInfo.DrawTimes<<endl;
    cout<<Tabs(2)<<"Winner Name        : "<<GameInfo.WinnerName<<endl;

}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        stGameInfo GameInfo = PlayGame(ReadHowManyRounds());

        ShowGameOverScreen();

        ShowFinalGameResults(GameInfo);

        cout<<"\nDo You Want To Play Again? Y/N? \n";
        cin>>PlayAgain;

    } while (PlayAgain=='Y'||PlayAgain=='y');
    
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
