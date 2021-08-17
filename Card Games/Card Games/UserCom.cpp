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
