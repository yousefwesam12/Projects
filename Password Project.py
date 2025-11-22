def ReadPassword():
   Password = input("Enter Password: ")
   return Password

def CountDigits(Password):
    Counter = 0

    Digits = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0']

    for char in Password:
        if char in Digits:
            Counter += 1

    return Counter

def CountLetters(Password):
    Counter = 0
    for char in Password:
        if(char.isalpha()):
            Counter += 1

    return Counter

def CountSpecialChar(Password):
    Counter = 0
    SpecialChar = ['!','@','#','$','%','&','*']
    for char in Password:
        if(char in SpecialChar):
            Counter += 1
    return Counter

def IsStrongPassword(Password):

    IsStrong = (CountDigits(Password)>=4) and (CountLetters(Password)>=4) and ( CountSpecialChar(Password)>=4)
    return IsStrong


Password = ReadPassword()

if (IsStrongPassword(Password)):
    print("Password is strong")
else:
    print("Password is weak")
