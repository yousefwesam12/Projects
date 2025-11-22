#include <iostream>
#include <string>
using namespace std;

enum enOpType {Add = 1 , Sub , Mul , Div , Mix};

enum enQuestionsLevel {Easy = 1 , Med , Hard , MixLevel};

struct stQuiz
{
    short QuestionsNumber = 0;
    short RightAnswers    = 0;
    short WrongAnswers    = 0;
    string QuestionsLevel = " ";
    string OperationType    = " ";
    enQuestionsLevel enQuizLevel;
    enOpType enOpreationType;
    string FinalResult = " ";
    
};

struct stQuestion
{
    short Num1 = 0;
    short Num2 = 0;
    string Opreation;
    enOpType OpType;
    short PlayerAnswer = 0;
};

short RandomNumber(int From, int To)
{
    return rand() % (To-From+1)+From;
}

short ReadHowManyQuestions(string Message)
{
    short QuestionsNumber = 0;

    cout<<Message;
    cin >> QuestionsNumber;

    return QuestionsNumber;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionsLevel = 1;

    do
    {
        cout<<"Enter Questions Level [1] Easy [2] Med [3] Hard [4] Mix ? ";
        cin >> QuestionsLevel;

    } while (QuestionsLevel<1||QuestionsLevel>4);

    return enQuestionsLevel(QuestionsLevel);
    
}

enOpType ReadOpType()
{
    short OpType = 1;

    do
    {
        cout<<"Enter Operation Type [1] Add [2] Sub [3] Mul [4] Div [5] Mix ? ";
        cin>>OpType;

    } while (OpType<1||OpType>5);
    
    cout<<endl;
    
    return enOpType(OpType);
}

short GenerateNumAccordingToLevel(enQuestionsLevel QuestionLevel)
{
    // This function returns a random number according to the level of quiz //
    switch (QuestionLevel)
    {
    case Easy:
        return RandomNumber(1,5);
    case Med:
        return RandomNumber(5,10);
    case Hard:
        return RandomNumber(10,50);
    case MixLevel:
        return RandomNumber(1,50);
    default:
        break;
    }

    // actually it will not reach here //
    return 0;
}

string GetOpTypeString(enOpType Op)
{
    // This will return + or - or / or * //

    string ArrOfOpreations[5] = {"+","-","*","/","Mix"};

    return ArrOfOpreations[Op-1];
}

string GetQuestionsLevel(enQuestionsLevel QuestionsLevel)
{
    string QuestionsLevelArray[4] = {"Easy","Med","Hard","Mix"};

    return QuestionsLevelArray[QuestionsLevel-1];
}

stQuestion GenerateQuestion(enQuestionsLevel &QuestionLevel, enOpType OpType)
{
    stQuestion Question;

    Question.Num1      = GenerateNumAccordingToLevel(QuestionLevel);
    Question.Num2      = GenerateNumAccordingToLevel(QuestionLevel);
    Question.Opreation = GetOpTypeString(OpType);
   
    
    if(OpType==Mix)
    {
        Question.OpType = enOpType(RandomNumber(1, 5));
    }
    else
    {
        Question.OpType    = OpType;
    }

    return Question;
}

string Lines(short NumOfLines)
{
    string L = "";

    for(int i = 1;i<=NumOfLines;i++)
    {
        L = L + "_";
    }
    return L;
}

void PrintQuestion(stQuestion Question,short CurrentQuestion,short AllQuestions)
{
    // This Will Print Question [1/5] for example //

    string QuestionHeader = "Question [" + to_string(CurrentQuestion) + "/" + to_string(AllQuestions) + "]\n";

    cout<<QuestionHeader;

    /*
     This Will Print
     1
     2 +
     _________
    */
    cout<<Question.Num1<<endl;
    cout<<Question.Num2<<" "<<Question.Opreation<<endl;
    cout<<Lines(20)<<endl;
    
}

short GetAnswerOfQuestion(stQuestion& Question)
{
    // This Function Gets an answer for the current question //
    switch (Question.OpType)
    {
    case Add: return Question.Num1 + Question.Num2;
    
    case Sub: return Question.Num1 - Question.Num2;
       
    case Mul: return Question.Num1 * Question.Num2;

    case Div:
            if(Question.Num1>Question.Num2)
            {
                return Question.Num1 / Question.Num2;

            }
            else
            {
                return 0;
            }
    default:
            return 0;
        break;
    }
    
}

bool PrintQuestionResults(short PlayerAnswer,short RightAnswer)
{
    if(PlayerAnswer==RightAnswer)
    {
        cout<<"Right Answer :)\n";
        return true;
    }
    else
    {
        cout<<"Wrong Answer (:\n";
        cout<<"The Right Answer is "<<RightAnswer<<endl;
        return false;
    }
}

string GetFinalResult(short RightAnswers,short WrongAnswers)
{
    
    if(RightAnswers>WrongAnswers)
    {
        return "PASS :)";
    }
    else
    {
        return "FAIL ):";
    }
}

stQuiz FillGame(short RightAnswers,short WrongAnswers,string OpType,string QuestionsLevel,short NumOfQuestions,string FinalResult)
{
    stQuiz Quiz;

    Quiz.QuestionsNumber = NumOfQuestions;
    Quiz.QuestionsLevel  = QuestionsLevel;
    Quiz.OperationType   = OpType;
    Quiz.RightAnswers    = RightAnswers;
    Quiz.WrongAnswers    = WrongAnswers;
    Quiz.FinalResult     = FinalResult;

    return Quiz;
}

stQuiz StartGame(stQuestion Question)
{
    // Frist we need to read how many questions //
    
    stQuiz Quiz;
    short RightAnswers = 0;
    short WrongAnswers = 0;

    Quiz.QuestionsNumber = ReadHowManyQuestions("How Many Questions You Want To Answer?  ");

    // Then We need to read questions level //

    Quiz.enQuizLevel = ReadQuestionsLevel();

    // Then we need to read op type //

    Quiz.enOpreationType        = ReadOpType();
    
    Quiz.OperationType          = GetOpTypeString(Quiz.enOpreationType);

    //Then we need to generate Questions and print it //

    for(short CurrentQuestion = 1;CurrentQuestion<=Quiz.QuestionsNumber;CurrentQuestion++)
    {
            Question = GenerateQuestion(Quiz.enQuizLevel,Quiz.enOpreationType);

            PrintQuestion(Question,CurrentQuestion,Quiz.QuestionsNumber);

            // We need to read player answer //

            cin >> Question.PlayerAnswer;

            // Print Right or false //

            bool Answer = 0;
            Answer = PrintQuestionResults(Question.PlayerAnswer,GetAnswerOfQuestion(Question));

            // Counters for right answers//

            if(Answer==true)
            {
                RightAnswers++;
            }
            else
            {
                WrongAnswers++;
            }
    }
    
    

    return FillGame(RightAnswers,WrongAnswers,GetOpTypeString(Quiz.enOpreationType),GetQuestionsLevel(Quiz.enQuizLevel),Quiz.QuestionsNumber,GetFinalResult(RightAnswers, WrongAnswers));
}

void PrintFinalScreen(stQuiz Quiz)
{
    cout<<Lines(35)<<endl<<endl;
    cout<<"\tFinal Result is "<<Quiz.FinalResult<<"\n";
    cout<<Lines(35)<<endl<<endl;

    cout<<"Number Of Questions : "<<Quiz.QuestionsNumber<<endl;
    cout<<"Questions Level     : "<<Quiz.QuestionsLevel<<endl;
    cout<<"Operation Type      : "<<Quiz.OperationType<<endl;
    cout<<"Right Answers       : "<<Quiz.RightAnswers<<endl;
    cout<<"Wrong Answers       : "<<Quiz.WrongAnswers<<endl;
}



int main()
{
    srand((unsigned)time(NULL));
    stQuiz Quiz;
    stQuestion Question;
    
    char PlayAgain = 'Y';
    
    do
    {
        Quiz = StartGame(Question);

        PrintFinalScreen(Quiz);
        
        cout<<"\nDo You Want To Play Again? Y/N?  ";
        cin >>PlayAgain;
        
        cout<<endl<<endl;
        
    } while (PlayAgain=='Y'||PlayAgain == 'y');



}
