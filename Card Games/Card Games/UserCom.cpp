#include "UserCom.h"
#include<iostream>

string UserCom::GetString(string preface)
{
    string result;
    cout << preface << " : ";
    cin >> result;
    cout << "\n\n";
    return result;
}

int UserCom::GetNumber(string preface)
{
    int num;
    cout << preface << " : ";
    cin >> num;
    cout << "\n\n";
    return num;
}

bool UserCom::YesNo(string preface)
{
    string input;
    bool result;
    bool match = false;

    while (!match) {
        cout << preface << " - Yes or No" << " : ";
        cin >> input;

        for (auto yesVariant : yesAnswers) {
            if (input == yesVariant) {
                result = true;
                match = true;
            }
        }
        for (auto noVariant : noAnswers) {
            if (input == noVariant) {
                result = false;
                match = true;
            }
        }
    }

    cout << "\n\n";
    return result;
}

int UserCom::PokerDecision(int minRaise, int playersMaxRaise)
{
    int input;
    int result;
    bool match = false;
    bool reachedMin = false;

    while (!match) {
        cout << "1.Call 2.Raise 3.Fold : ";
        cin >> input;

        switch (input)
        {
        case(1):
            result = 0;
            match = true;
            break;

        case(2):
            while (!reachedMin) {
                cout << "Enter raise must exceed " << minRaise << ". 0 to cancel : ";
                cin >> result;
                if (result == 0) {
                    reachedMin = true;
                }
                else if (result > playersMaxRaise) {
                    cout << "Not enough cash\n";
                }
                else if (result <= minRaise) {
                    cout << "Not high enough\n";
                }
                else {
                    reachedMin = true;
                    match = true;
                }
            }
            break;

        case(3):
            result = -1;
            match = true;
            break;

        }
        
    }

    return result;
}
