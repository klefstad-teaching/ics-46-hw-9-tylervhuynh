#include "../src/ladder.h"
using namespace std;


void error(string word1, string word2, string msg) {
    cerr << msg << " " << word1 << ", " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > d) {return false;}
    int i = 0, j = 0, diff_count = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff_count > d) {return false;}
            if (len1 > len2) {i++;}
            else if (len1 < len2) {j++;}
            else {i++; j++;}
        } else {i++; j++;}
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> ladder;
    if (begin_word == end_word) {
        error("Word ladder could not be created: Begin and end word are equal", begin_word, end_word);
        return ladder;
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();
        for (string word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                if (word == end_word) {return new_ladder;}
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    error("No ladder found.", begin_word, end_word);
    return ladder;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream input_file(file_name);
    for (string word; input_file >> word;)
            word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder) {
    for (string word : ladder) {
        cout << word << " ";
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}