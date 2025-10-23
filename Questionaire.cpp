#include <iostream>
#include <string>
using namespace std;

void Questionaire()
{

	int score = 0;

	// First we define questions.
	string questions[] = {
		"What is the capital of France?",
		"What is 2 + 2?",
		"What is the largest planet in our solar system?"};

	// Define the size of questions array.
	int questionsCount = sizeof(questions) / sizeof(string);

	// Define the correct answers.
	string answers[] = {
		"Paris",
		"4",
		"Jupiter"};

	// Then we define options for answers.
	string answerOptions[3][4] = {
		{"Paris", "London", "Berlin", "Madrid"},
		{"3", "5", "4", "22"},
		{"Earth", "Mars", "Saturn", "Jupiter"}};

	int answersSize = sizeof(answerOptions) / sizeof(string);

	// We create a simple display for the quizz.
	cout << "Quizz Time!" << endl;
	cout << "Answer the following questions by entering the number corresponding to your answer." << endl;

	// Loop to display all questions.
	for (int i = 0; i < questionsCount; i++)
	{
		cout << questions[i] << endl;

		// And all answers for each question.
		for (string answer : answerOptions[i])
		{
			cout << " - " << answer << endl;
		};

		// Get user answer for each question.
		string reply;
		cout << "Your answer:" << endl;
		getline(cin, reply);

		// Empty answers loop.
		while (reply.empty())
		{
			// Create a skip for those who don't want to answer.
			cout << "Would you like to skip this question(yes/y | no/n) ?" << endl;
			cout << "Your choice:" << endl;
			getline(cin >> ws, reply);
			// If yes next question.
			if (reply == "yes" || reply == "y")
			{	string skipconfirm = "skipped";
				cout << "Question skipped." << endl;
				reply = skipconfirm;
				break;
			}
			// If no ask the question again.
			else
			{
				cout << questions[i] << endl;
				cout << "Your answer:" << endl;
				getline(cin >> ws, reply);
			};
		};

		// Then check if the answers are correct.
		if (reply != answers[i] && reply != "skipped")
		{
			score -= 1;
		}
		else
		{
			score += 1;
		};
	};

	// Output results:
	cout << "Your score is : " << score << " out of " << questionsCount << endl;

};
