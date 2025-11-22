def IsNumInRange(From,To,Num):
    return Num >=From and Num <= To

def ReadHowManyTasks():
    NumOfTasks = 0
    NumOfTasks = int(input("How many tasks do you want to create? 1️⃣ to 🔟?\n"))

    while (not IsNumInRange(1,10,NumOfTasks)):
        NumOfTasks = int(input("Please Enter a valid Range: \n"))

    return NumOfTasks

def ReadTaskName():
    TaskName = ""
    TaskName = input("What is your task name? ")
    return TaskName

def MakeTasks(NumOfTasks):
    Tasks = []
    for i in range(1,NumOfTasks+1):
        Tasks.append(ReadTaskName())
    return Tasks

def DisplayTasks(Tasks):
    print("\n----------------------Tasks 📝 ----------------------")
    Counter = 1
    for Task in Tasks:
        print(f"- Task No. {Counter} : {Task}")
        Counter += 1
    print("-----------------------------------------------------")

Tasks = []

print("Hi There, happy to see you!!!")

while(True):
    Tasks += MakeTasks(ReadHowManyTasks())
    DisplayTasks(Tasks)
    AddMore = input("Do You Want To Add More Tasks? Y/N\n")

    if(AddMore != "Y" and AddMore != "y"):
        print("Good Bye! 👋")
        break