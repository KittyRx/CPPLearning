#include <iostream>
#include <string>
using namespace std;

int main()
{
	int score = 0;

	enum QA
	{
		Question,
		AnswerA,
		AnswerB,
		AnswerC,
		AnswerD,
		COUNT
	};

	// Quiz data: 3 questions, each with 4 answers
	string data[3][COUNT] = {
		{"What is the capital of France?", "Paris", "London", "Berlin", "Madrid"},
		{"What is 2 + 2?", "3", "5", "4", "22"},
		{"What is the largest planet in our solar system?", "Earth", "Mars", "Saturn", "Jupiter"}};

	// Correct answers: by full string and by letter
	string correctAnswers[2][3] = {
		{"Paris", "4", "Jupiter"},
		{"A", "C", "D"}};

	cout << "Quiz Time!" << endl;
	cout << "Answer the following questions by entering A, B, C, or D." << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << "\n"
			 << data[i][Question] << "\n\n";
		cout << "A. " << data[i][AnswerA] << endl;
		cout << "B. " << data[i][AnswerB] << endl;
		cout << "C. " << data[i][AnswerC] << endl;
		cout << "D. " << data[i][AnswerD] << endl;

		string reply;
		cout << "\nYour answer: ";
		getline(cin, reply);

		while (reply.empty())
		{
			cout << "Please provide an answer: ";
			getline(cin, reply);
		}

		// Normalize input to uppercase
		if (reply.size() == 1)
			reply[0] = toupper(reply[0]);

		// Check if reply matches correct answer
		if (reply == correctAnswers[0][i] || reply == correctAnswers[1][i])
		{
			score += 1;
		}
		else if (reply != correctAnswers[0][i] || reply != correctAnswers[1][i])
		{
			score -= 1;
		}
	}

	cout << "\nFinal Score: " << score << "Points" << endl;
	return 0;
}
