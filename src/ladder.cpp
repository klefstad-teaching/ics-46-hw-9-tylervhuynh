#include "../src/ladder.h"
using namespace std;


void error(string word1, string word2, string msg) {
    cerr << msg << " " << word1 << ", " << word2 << endl;
}

bool my_assert(bool condition) {
    if (condition == true) {cout << "PASSED" << endl;}
    else {cout << "FAILED" << endl;}
    return condition;
}

void to_lowercase(string &word) {transform(word.begin(), word.end(), word.begin(), ::tolower);}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) {return false;}
    int i = 0;
    int j = 0;
    int counter = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            counter++;
            if (counter > d) {return false;}
            if (len1 > len2) {i++;}
            else if (len1 < len2) {j++;}
            else {i++; j++;}
        } else {i++; j++;}
    }
    return counter + (len1 - i) + (len2 - j) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string start = begin_word;
    string end = end_word;
    to_lowercase(start);
    to_lowercase(end);
    vector<string> ladder;
    if (start == end) {
        error(start, end, "No word ladder found.");
        return ladder;
    }
    if (word_list.find(end) == word_list.end()) {
        error(start, end, "No word ladder found.");
        return ladder;
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({start});
    set<string> visited;
    visited.insert(start);
    while (!ladder_queue.empty()) {
        int level = ladder_queue.size();
        set<string> level_visited;
        for (int i = 0; i < level; ++i) {
            vector<string> current_ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = current_ladder.back();
            for (const string& word : word_list) {
                if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(word);
                    if (word == end) {return new_ladder;}
                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
        visited.insert(level_visited.begin(), level_visited.end());
    }
    error(start, end, "No word ladder found.");
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream input_file(file_name);
    for (string word; input_file >> word;) {
        to_lowercase(word);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}