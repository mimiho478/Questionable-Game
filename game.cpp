
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


using namespace std;

/// Scores depending upon difficulty of questions.

const float DIFF_LEVEL_ONE = 1.23;
const float DIFF_LEVEL_TWO = 1.51;
const float DIFF_LEVEL_THREE = 2.02;

int main()
{
    cout << "\n______________________________\n";
    cout << "  Project 2: C++ Game Time\n";
    cout << "\n______________________________\n";

    ///step1:
    ///Declare the necessary variables, for example:
    string alias;               /// declare alias name (done)
    ofstream outFile;           ///declare output file stream variable (done)
    string date;                /// declare the date (string)
    int number_of_questions;    /// declare the number of questions (integer)
    int difficulty_level;       /// declare the difficulty level (integer)


    ///prompt for the user information (Game alias and date).
	cout << "Enter the alias name for the game: ";
	cin >> alias;
	cout << "Enter the date: ";
	cin >> date;

    ///use user's Game Name to create a new output file.
    alias = alias.append(".txt");
    outFile.open(alias.c_str(), ios::app);

    ///step4
    ///Ask the user for number of questions REPEATEDLY.
    ///Check if the number of questions is between 1-15.

	do {
		cout << "How many questions? (1 - 15): ";
		cin >> number_of_questions;
		cin.ignore(100,'\n');
	} while (number_of_questions < 1 || number_of_questions >15);


    ///ask the user to enter the difficulty level.
    /// check the difficulty level.
    /// If the difficulty level is not within the acceptable range, display the error message and exit the program.
	cout << "Enter difficulty level: (1,2,3): ";
	cin >> difficulty_level;
	if (difficulty_level < 1 || difficulty_level > 3) {
		cout << "Invalid difficulty level! Try again later" << endl;
		return 1;
	}

    /// open the correct input file
    /// use the files(questions1.txt or questions2.txt or questions3.txt) based on the level.
	string in_filename = "questions";
	in_filename.push_back('0' + difficulty_level);
	in_filename.append(".txt");
	ifstream inFile(in_filename.c_str());     ///declare and open input file


    ///for example, if the user entered the number of questions = 5, then the loop will run 5 times.
	string question, options[4];
	char right_answer, answer;
	double score = 0;			// initial player score

	for (int i = 0; i < number_of_questions; i++)
	{
        
        ///read the question, the correct answer, and the 4 options from the input file.
		getline(inFile, question);
		inFile >> right_answer;
		inFile.ignore(100, '\n');
		for (int j = 0; j<4; j++)
			getline(inFile, options[j]);

        ///step 7.2
        ///Print the question along with the options on screen.
		cout << endl << "Question (" << i + 1 << ")" << endl
			 << question << endl << endl;
		for (int j = 0; j<4; j++)
			cout << char('A' + j) << ") " << options[j] << endl;

		///step 7.3
        ///Ask the user for his choice.
		cout << " Enter your choice: ";
		cin >> answer;
		cin.ignore(100,'\n'); // clear garbage characters

		///step 7.4
        ///Convert the user choice into upper case letter. Use toupper() to convert a char to uppercase.
		answer = toupper(answer);

		///step 7.5
		///If the user choice matches the solution, Then print it as correct and calculate the score.
		if (answer == right_answer) {
			cout << endl << "Your chose: " << answer << "\t\t\tCORRECT!" << string(20,'-') << endl;
			// update score
			switch (difficulty_level)
			{
				case 1:
					score += DIFF_LEVEL_ONE;
					break;
				case 2:
					score += DIFF_LEVEL_TWO;
					break;
				case 3:
					score += DIFF_LEVEL_THREE;
					break;
				default:
					break;
			}
		} else {
			///step 7.6
			///If the user choice does not match with the solution. Then print the correct solution along with the user's choice.
			cout << endl << "Your chose: " << answer << ", but correct answer is "
				 << right_answer << "\tYOUR ARE WRONG!" << string(20,'-') << endl;
		}
	}
    ///
    /// END the loop here once ALL questions are answered.

    ///step8
    ///Print the GameName and the score to the screen
	cout << endl << "Score for " << alias << " = " << fixed << setprecision(2) << score << endl;

    ///step9
    ///print the Date, Difficulty Level, and the score to the output file.
	outFile << date << "\t" << difficulty_level << "\t" << fixed << setprecision(2) << score << endl;

    ///step10
    ///Close the input
	inFile.close();
    ///Close the output file.
	outFile.close();

    return 0;
}