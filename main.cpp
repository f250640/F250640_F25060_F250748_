/*
Group_Members:
1. Moazzam Ali - ID: 25F-0640
2. Asfand Haroon - ID: 25F-0606
3. Mati ur Rehman - ID: 25F-0748*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Global Initializations
const int MAX_QUESTIONS = 50;
const int QUIZ_SIZE = 10;
int currentDifficulty = 1;

// --- Function Prototypes ---
void HomeDIsplay();
void saving_score(string name, int score);
void logSession(string name, int score, int correct, int wrong);
void HighScoreReview();
int loadingOfQuestions(string filename, string question[], string QuestionOptions[][4], int CorrectAnswers[], int difficulty[]);
void MainBody();

//Menu Display Function

void HomeDIsplay() 
{
    cout << "========================================" << endl;
    cout << "           WELCOME TO QUIZGAME        " << endl;
    cout << "========================================" << endl;
    cout << "1. Start Quiz" << endl;
    cout << "2. View High Scores" << endl;
    cout << "3. Exit Game" << endl;
    cout << "========================================" << endl;
    cout << "Please select an option (1-3): ";
}

// Save High Score Function

void saving_score(string name, int score) 
{
    ofstream file("high_scores.txt", ios::app);
    if (file.is_open()) 
    {
        file << name << " " << score << endl;
        file.close();
    }
}

// Log Session Function

void logSession(string name, int score, int correct, int wrong) 
{
    ofstream file("quiz_logs.txt", ios::app);
    if (file.is_open()) 
    {
        file << "Player: " << name << " | Score: " << score
            << " | Correct: " << correct << " | Wrong: " << wrong << endl;
        file.close();
    }
}

// Showing High Scores Function

void HighScoreReview() 
{
    system("CLS");
    cout << "--- TOP HIGH SCORES ---" << endl;
    ifstream file("high_scores.txt");
    string line;
    if (file.is_open()) 
    {
        while (getline(file, line)) cout << line << endl;
        file.close();
    }
    else 
    {
        cout << "No high scores yet." << endl;
    }
}

// Loading of Questions Function

int loadingOfQuestions(string filename, string qText[], string qOptions[][4], int qCorrect[], int qDifficulty[]) 
{
    ifstream file(filename.c_str());
    if (!file.is_open()) 
    {
        cout << "Error: Could not open " << filename << endl;
        cout << "Check if the file exists in the folder!" << endl;
        return 0;
    }

    int count = 0;
    string tempText, tempOptions[4];
    int tempCorrect = 0, tempDiff = 0;

    while (count < MAX_QUESTIONS && getline(file, tempText)) 
    {
        if (tempText.empty()) continue;

        for (int i = 0; i < 4; i++) getline(file, tempOptions[i]);
        file >> tempCorrect;
        file >> tempDiff;
        file.ignore();

		// Store in arrays
        qText[count] = tempText;
        for (int k = 0; k < 4; k++) 
            qOptions[count][k] = tempOptions[k];
		//switch to 0-based index
        qCorrect[count] = tempCorrect;
        qDifficulty[count] = tempDiff;
        count++;
    }
    file.close();
    return count;
}

// Main Body Function

void MainBody() 
{
    system("CLS");
    string playerName;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, playerName);
int catChoice;
int currentDifficulty;
string filename;

// --- CATEGORY SELECTION WITH VALIDATION ---
while (true)
{
    cout << "\nSelect Category:\n"
         << "1. Science\n2. Computer\n3. Sports\n4. History\n5. IQ/Logic\n"
         << "Choice: ";

    if (!(cin >> catChoice))
    {
        cin.clear();                
        cin.ignore(1000, '\n');      
        cout << "Invalid input! Please enter a number between 1 and 5.\n";
        continue;
    }

    if (catChoice < 1 || catChoice > 5)
    {
        cout << "Invalid choice! Please select a number between 1 and 5.\n";
        continue;
    }

    break; 
}

// --- DIFFICULTY SELECTION WITH VALIDATION ---
while (true)
{
    cout << "\nSelect Difficulty:\n"
         << "1. Easy\n2. Medium\n3. Hard\n"
         << "Choice: ";

    if (!(cin >> currentDifficulty))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number between 1 and 3.\n";
        continue;
    }

    if (currentDifficulty < 1 || currentDifficulty > 3)
    {
        cout << "Invalid choice! Please select 1, 2, or 3.\n";
        continue;
    }

    break; 
}

// --- SELECT FILE BASED ON CATEGORY AND DIFFICULTY ---
if (catChoice == 1) // Science
{
    if (currentDifficulty == 1) filename = "science.txt";
    else if (currentDifficulty == 2) filename = "sciencem_medium.txt";
    else filename = "science_hard.txt";
}
else if (catChoice == 2) // Computer
{
    if (currentDifficulty == 1) filename = "computer.txt";
    else if (currentDifficulty == 2) filename = "computerm_medium.txt";
    else filename = "computer_hard.txt";
}
else if (catChoice == 3) // Sports
{
    if (currentDifficulty == 1) filename = "sports.txt";
    else if (currentDifficulty == 2) filename = "sportsm_medium.txt";
    else filename = "sports_hard.txt";
}
else if (catChoice == 4) // History
{
    if (currentDifficulty == 1) filename = "history.txt";
    else if (currentDifficulty == 2) filename = "Historym_medium.txt";
    else filename = "history_hard.txt";
}
else // IQ / Logic
{
    if (currentDifficulty == 1) filename = "iq.txt";
    else if (currentDifficulty == 2) filename = "IQm_medium.txt";
    else filename = "iq_hard.txt";
}
	// Arrays for questions
    string qText[MAX_QUESTIONS];
    string qOptions[MAX_QUESTIONS][4];
    int qCorrect[MAX_QUESTIONS];
    int qDifficulty[MAX_QUESTIONS];

    int totalLoaded = loadingOfQuestions(filename, qText, qOptions, qCorrect, qDifficulty);

    if (totalLoaded == 0) 
    {
        cout << "\nNo questions loaded. File might be empty." << endl;
        return;
    }
	// Shuffle questions randomly
    for (int k = 0; k < 30; k++) 
    {
        int idx1 = rand() % totalLoaded;
        int idx2 = rand() % totalLoaded;

        string tStr = qText[idx1]; 
        qText[idx1] = qText[idx2]; 
        qText[idx2] = tStr;
        int tInt = qCorrect[idx1]; 
        qCorrect[idx1] = qCorrect[idx2]; 
        qCorrect[idx2] = tInt;
        tInt = qDifficulty[idx1]; 
        qDifficulty[idx1] = qDifficulty[idx2]; 
        qDifficulty[idx2] = tInt;
        for (int m = 0; m < 4; m++) 
        {
            tStr = qOptions[idx1][m]; 
            qOptions[idx1][m] = qOptions[idx2][m]; 
            qOptions[idx2][m] = tStr;
        }
    }

	// Limit to QUIZ_SIZE = 10
    int limit = (totalLoaded < QUIZ_SIZE) ? totalLoaded : QUIZ_SIZE;

    int score = 0, correctCount = 0, wrongCount = 0, streak = 0;
    int life5050 = 1, lifeSkip = 1, lifeReplace = 1, lifeTime = 1;

	// Quiz Loop
    for (int i = 0; i < limit; i++) 
    {
        int maxTime = 10;

        system("CLS");
        cout << "Question " << (i + 1) << "/" << limit << endl;
        cout << "Score: " << score << " | Streak: " << streak << endl;
        cout << "----------------------------------------" << endl;
        cout << qText[i] << endl;
        cout << "----------------------------------------" << endl;

        for (int j = 0; j < 4; j++) cout << (j + 1) << ". " << qOptions[i][j] << endl;

        cout << "\n[Lifelines]: 5. 50/50 | 6. Skip | 7. Replace | 8. +Time" << endl;
        cout << "Time Limit: " << maxTime << " seconds." << endl;
        cout << "Enter answer (1-4): ";

        time_t start = time(0);
        int userAns = 0;
        cin >> userAns;
        time_t end = time(0);

        double taken = difftime(end, start);

        // Lifelines Logic
        bool skipped = false;
        bool replaced = false;

        if (userAns == 5) 
        { // 50/50
            if (life5050) 
            {
                life5050 = 0;
                cout << "\n[LIFELINE USED]: 50/50" << endl;
                cout << "Hint: The answer is " << qOptions[i][qCorrect[i] - 1]
                    << " or " << qOptions[i][(qCorrect[i] % 4)] << endl;
                cout << "Enter answer again: ";
                cin >> userAns;
            }
            else cout << "\nLifeline already used!" << endl;
        }
        else if (userAns == 6) 
        { // Skip
            if (lifeSkip) 
            {
                lifeSkip = 0;
                cout << "\n[LIFELINE USED]: Question Skipped!" << endl;
                skipped = true;
            }
            else cout << "\nLifeline already used!" << endl;
        }
        else if (userAns == 7) 
        { // Replace
            if (lifeReplace) 
            {
                lifeReplace = 0;
                cout << "\n[LIFELINE USED]: Question Replaced!" << endl;
                replaced = true;
            }
            else cout << "\nLifeline already used!" << endl;
        }
        else if (userAns == 8) 
        { // Extra Time
            if (lifeTime) 
            {
                lifeTime = 0;
                maxTime += 10;
                cout << "\n[LIFELINE USED]: +10 Seconds added!" << endl;
                cout << "Enter answer: ";
                cin >> userAns;
                taken = 0; // Reset timer penalty
            }
            else cout << "\nLifeline already used!" << endl;
        }

		//Results Evaluation
        if (skipped) 
        {
            // Do nothing
        }
        else if (replaced) 
        {
            i--; // Repeat loop with new index
        }
        else if (taken > maxTime) 
        {
            cout << "\n========================================" << endl;
            cout << "              TIME UP!                  " << endl;
            cout << "========================================" << endl;
            cout << "Correct Answer was: " << qOptions[i][qCorrect[i] - 1] << endl;
            streak = 0;
            wrongCount++;
        }
        else if (userAns == qCorrect[i]) 
        {
            cout << "\n========================================" << endl;
            cout << "              CORRECT!                  " << endl;
            cout << "========================================" << endl;
            correctCount++;
            streak++;
            int pts = 10;
            if (streak == 3) 
            { 
                cout << "Streak Bonus! +5 pts" << endl; pts += 5; 
            }
            if (streak == 5) 
            { 
                cout << "Super Streak! +15 pts" << endl; pts += 15; 
            }
            score += pts;
        }
        else 
        {
            cout << "\n========================================" << endl;
            cout << "             INCORRECT!                 " << endl;
            cout << "========================================" << endl;
            cout << "The correct answer was: " << qOptions[i][qCorrect[i] - 1] << endl;
            streak = 0;
            wrongCount++;
            int pen = (currentDifficulty == 1) ? 2 : (currentDifficulty == 2 ? 3 : 5);
            score -= pen;
            cout << "Penalty applied: -" << pen << " points." << endl;
        }

        cout << "\n";
        system("pause");
    }

	//Quiz Summary
    system("CLS");
    cout << "========================================" << endl;
    cout << "           QUIZ COMPLETED               " << endl;
    cout << "========================================" << endl;
    cout << "Player Name   : " << playerName << endl;
    cout << "Final Score   : " << score << endl;
    cout << "Correct       : " << correctCount << endl;
    cout << "Incorrect     : " << wrongCount << endl;
    cout << "========================================" << endl;

    saving_score(playerName, score);
    logSession(playerName, score, correctCount, wrongCount);
}




// Main Function
int main() 
{
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    int choice = 0;
    string playerName; 

    do 
    {
        HomeDIsplay();

        if (!(cin >> choice)) 
        {
            cin.clear();
            cin.ignore(1000, '\n'); 
            choice = 0;
        }

        cin.ignore(); 

        switch (choice) 
        {
        case 1: 
            
             MainBody(); 
             cout << "\nEnter your name for review: ";
             cin.ignore();
            getline(cin, playerName);
            break;
        case 2: 
            
            HighScoreReview(); 
            
            cout << "\nEnter your name for review: ";
            getline(cin, playerName);
            break;
        case 3: 
            cout << "Exiting... Goodbye!" << endl 
                 << "Thank you for playing QuizMaster!" << endl;
            
            cout << "\nEnter your name for review: ";
            getline(cin, playerName);
            break;
        default: 
            cout << "Invalid choice." << endl;
            continue; 
        }

           
        // --- Review Section ---
        string review;
        cout << "\n--- Leave a Review ---" << endl;
        cout << "Player: " << playerName << endl;
        cout << "Enter your comment about the game: ";
        getline(cin, review);

        
        ofstream reviewFile("review.txt", ios::app);
        if (reviewFile.is_open())
        {
            reviewFile << "Player: " << playerName << endl;
            reviewFile << "Comment: " << review << endl;
            reviewFile << "-------------------------------" << endl;
            reviewFile.close();
            cout << "Thank you for your feedback!" << endl;
        }
        else
        {
            cout << "Error: Could not open review file." << endl;
        }

        if (choice != 3) 
        {
            cout << "\n";
            system("pause");
            system("CLS");
        }

    } while (choice != 3);

    return 0;
}

