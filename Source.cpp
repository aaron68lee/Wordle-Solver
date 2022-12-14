#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//========================== prints entire dictionary ==================================

void printDict(vector<string> const& dict)
{
    // for (int i = 0; i < dict.size(); i++)
    // {
    //     cout << dict[i] << endl;
    // }     

    cout << "\nDictionary has: " << dict.size() << " words.\n\n";
}

//========================== prints possible guesses from dictionary ==================================

vector<string> printGuess(vector<string> dict, string guess, string known, string blacks, char key, int letters)
{
    vector<string> tempDict;
    int green = 0;
    bool yellow = false;
    int numYellow = 0;
    int black = 0;
    int dynamic = 0;
    string guess0 = guess;
    string known0 = known;
    string blacks0 = blacks;

    if (letters == -1)
        dynamic = 1;

    // ============= autofill blanks once ==============

    if (guess.size() < letters)
    {
        for (int i = guess.size(); i < letters; i++)
            guess += "0";
    }

    if (known.size() < letters)
    {
        for (int i = known.size(); i < letters; i++)
            known += "0";
    }

    if (blacks.size() < letters)
    {
        for (int i = blacks.size(); i < letters; i++)
            blacks += "0";
    }

    //cout << "\n\n====\n\n" << guess << endl << known << endl << blacks << "\n\n====\n";

    // ============= Dictionary Reduction ==============

    for (int i = 0; i < dict.size(); i++) // loop through current DICT of possible words
    {
        // guess = guess0;
        // known = known0;
        // blacks = blacks0;

        if (dynamic)
        {
            // ============= autofill blanks dynamically ==============

            letters = dict[i].size();

            if (guess.size() < letters)
            {
                for (int i = guess.size(); i < letters; i++)
                    guess += "0";
            }

            if (known.size() < letters)
            {
                for (int i = known.size(); i < letters; i++)
                    known += "0";
            }

            if (blacks.size() < letters)
            {
                for (int i = blacks.size(); i < letters; i++)
                    blacks += "0";
            }
        }

        // start green analysis 

        green = 1;

        for (int j = 0; (j < letters) && green; j++) // compare GREEN
        {
            if ((guess[j] != key && dict[i].at(j) != guess[j]))
            {
                green = 0;
            }
        }

        numYellow = 0;
        yellow = true;

        for (int j = 0; (j < letters) && yellow; j++) // compare YELLOW (loop through letters in KNOWN)
        {
            numYellow = 0;

            if (known[j] != key) // skip non-KEY chars in KNOWN
            {
                for (int k = 0; k < letters; k++) // loop thru letters of dict[i]
                {
                    if (known[j] == dict[i].at(k) && k == j) // condition for GREEN
                    {
                        yellow = false;
                    }

                    if (known[j] == dict[i].at(k))
                        numYellow++;
                }

                if (numYellow == 0)
                    yellow = false;

            }
        }

        black = 1;

        for (int j = 0; (j < letters) && black; j++) // compare BLACK
        {
            if (blacks[j] != key) // && dict[i].at(j) != blacks[j]) 
            {
                for (int k = 0; k < letters; k++)
                    if (dict[i].at(k) == blacks[j]) // && dict[i].at(k) != guess[k] && known.find(blacks[j], 0) != -1) // second cluase was just modified
                        black = 0; // wordle archive test 286 fails this test
            }
        }

        if (green && yellow && black)
        {
            tempDict.push_back(dict[i]);
            cout << dict[i] << endl;
        }
    }

    cout << "\nPossible Guesses: " << tempDict.size() << " words.\n\n";
    return tempDict;
}

int main() //int argc, char* argv[]) // ================================== MAIN ======================================
{

    // load txt file of dictionary

    const char key = '0'; // black or yellow
    const char correct = '1';
    int letters = 5;
    string spacer = "";

    //string guess[] = {"00l0s", "00000"}; // first element is guess with letter, second element correct pos if 1
    string guess = ""; //"0000s"; // insert correct pos of green letters, use key char for black letters
    string known = ""; //"0t0l0"; // yellow letters in wordle
    string blacks = ""; //"0t0l0"; // black letters in wordle

    ifstream fullDict("dictionary.txt"); // database of all english words
    ifstream subDict("WordleDict.txt"); // database of all 5-letter english words
    vector<string> dict;
    string str;

    cout << "Enter number of letters (use -1 for full dict): ";
    cin >> letters;

    while (getline(fullDict, str)) // create dictionary of 5-letter words from full english dictionary
    {
        if (letters != -1)
        {
            if (str.size() == letters)
                dict.push_back(str);
        }
        else
            dict.push_back(str);
    }



    //================== RULES =================
    //string sample = ""
    cout << "\nThis Wordle program is takes 3 user inputs for the green, yellow, and black letters"\
        << "and outputs a list of remaining valid guess words. ";
    cout << "When prompted, the user input should be in format: \"" << key << "l" << key << "m" << key << "\", where " << key \
        << " denotes letters of other color and \"l\" and \"o\" denote letters of the color being prompted. If all chars are " << key\
        << " simply press enter to auto-input all \'0\'s.\n\n";

    getline(cin, spacer);

    printDict(dict);

    while (dict.size() > 1) // keep prompting user if word is not found
    {
        cout << "Enter \"green\" letters: \n";
        getline(cin, guess);
        cout << "Enter \"yellow\" letters: \n";
        getline(cin, known);
        cout << "Enter \"black\" letters: \n";
        getline(cin, blacks);

        dict = printGuess(dict, guess, known, blacks, key, letters);
    }

    return 0;
}