#include <iostream>
#include <iomanip>
using namespace std;

/* Helper function to centre the data in our output table*/
string centreData(const string& data, int width){
    int padding = width - data.length();
    int paddingLeft = padding/2;
    int paddingRight = padding - paddingLeft;
    return string(paddingLeft, ' ') + data + string(paddingRight, ' ');
}

int main(){

    const int CANDIDATE_NUM = 5; 
    string name[CANDIDATE_NUM];
    int votes[CANDIDATE_NUM];
    int totalVote = 0; 

    for (int i = 0; i < CANDIDATE_NUM; i++){
        cout << "Please enter the name of candidate " << i+1 << ": ";
        cin >> name[i];
        cout << "Please enter the number of votes for this candidate: "; 
        cin >> votes[i];
        totalVote += votes[i];
    }

    cout << left << setw(15) << "Candidate" << setw(20) << centreData("Votes Received", 20) << setw(20) << centreData("% of Total Votes",20) << endl << endl; 

    int winner = 0; 
    for (int i = 0; i < CANDIDATE_NUM; i++){
        double percentage = static_cast<double>(votes[i]) / totalVote * 100; 
        cout << left << setw(15) << name[i] << setw(20) << centreData(to_string(votes[i]), 20) << setw(20) << fixed << setprecision(2) << centreData(to_string(percentage), 20) << endl;

        if (votes[i] > votes[winner]){
            winner = i; 
        }
    }

    cout << left << setw(15) << "Total" << setw(20) << centreData(to_string(totalVote), 20) << endl << endl; 
    cout << "The winner of the Election is " << name[winner] << "." << endl;

    return 0;
}