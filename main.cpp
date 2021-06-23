#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct dictionary {
    string word;
    dictionary *next;
    dictionary *syn;
};

dictionary *creatWord(string name) {
    auto *word = new dictionary{std::move(name), nullptr, nullptr};
    return word;
}

void addWord(dictionary *&Head, const string &);

void addWordPrint(dictionary *&Head);

void addNode(dictionary *&Head, dictionary *);

void addSynonym(dictionary *, const string &);

void addSynonymPrint(dictionary *&Head);

void printDictionary(dictionary *&Head);

void printWord(dictionary *);

void printSyn(dictionary *);

void printMenu();

int removeWord(dictionary *&Head, const string &);

void removeWordPrint(dictionary *&Head);

void removeSynonymPrint(dictionary *&Head);

void editWordPrint(dictionary *&Head);

dictionary *searchWord(dictionary *&Head, const string &);

void searchWordPrint(dictionary *&Head);

string wordsToString(dictionary *);

int count(const string &word);

void saveInFile(dictionary *&Head);

dictionary *readFromFile(const string &address);

void exit(dictionary *&Head);

int main() {
    dictionary *Head = nullptr;

    int command;
    bool a = true;
    while (a) {
        printMenu();
        cin >> command;
        switch (command) {
            case 1:
                addWordPrint(Head);
                break;
            case 2:
                addSynonymPrint(Head);
                break;
            case 3:
                removeWordPrint(Head);
                break;
            case 4:
                removeSynonymPrint(Head);
                break;
            case 5:
                searchWordPrint(Head);
                break;
            case 6:
                editWordPrint(Head);
                break;
            case 7:
                printDictionary(Head);
                break;
            case 8:
                saveInFile(Head);
                break;
            case 10:
                exit(Head);
                break;
            default:
                a = false;
                break;
        }
    }
    return 0;
}

void addWord(dictionary *&Head, const string &word) {
    dictionary *temp;
    temp = creatWord(word);

    dictionary *find = searchWord(Head, word);
    if (find != nullptr)
        cout << "there is another word by this name in  the dictionary!" << endl;
    else
        addNode(Head, temp);
}

void addSynonym(dictionary *words, const string &synonym) {
    addWord(words->syn, synonym);
}

void addNode(dictionary *&Head, dictionary *word) {
    if (Head == nullptr)
        Head = word;
    else if (Head->word > word->word) {
        word->next = Head;
        Head = word;
    } else {
        dictionary *prev = Head;
        dictionary *curr = Head->next;

        while (curr != nullptr && curr->word < word->word) {
            prev = prev->next;
            curr = curr->next;
        }
        prev->next = word;
        word->next = curr;
    }
}

int removeWord(dictionary *&Head, const string &word) {
    dictionary *prev = nullptr;
    dictionary *curr = Head;

    if (Head == nullptr)
        return 0;
    else {
        while (curr != nullptr) {
            if (curr->word == word) {
                if (curr == Head && curr->next == nullptr)
                    Head = nullptr;
                else if (curr == Head)
                    Head = Head->next;
                else if (curr->next == nullptr)
                    prev->next = nullptr;
                else
                    prev->next = curr->next;

                delete curr;
                return 1;
            }
            prev = curr;
            curr = curr->next;
        }
        return 0;
    }
}

void removeSynonym(dictionary *word, const string &synonym) {
    removeWord(word->syn, synonym);
}

dictionary *searchWord(dictionary *&Head, const string &word) {
    dictionary *words;

    words = Head;
    while (words) {
        if (words->word == word)
            return words;
        else
            words = words->next;
    }
    return nullptr;
}

void editWord(dictionary *&Head, const string &oldWord, const string &newWord) {
    dictionary *prev, *temp;
    prev = Head;

    if (Head->word == oldWord) {
        temp = Head;
        Head = Head->next;

    } else {
        while (prev->next != nullptr && prev->next->word != oldWord) {
            prev = prev->next;
        }
        if (prev->next == nullptr) {
            cout << "we couldn't find the word : " << oldWord << endl;
            return;
        }
        temp = prev->next;
        prev->next = temp->next;
    }
    temp->word = newWord;
    addNode(Head, temp);

}

void printDictionary(dictionary *&Head) {
    dictionary *temp;
    temp = Head;

    cout << "words" << "      " << "synonyms" << endl;
    cout << "-------------------------------------" << endl;

    while (temp != nullptr) {
        printWord(temp);
        temp = temp->next;
    }
}

void printWord(dictionary *word) {
    cout << word->word << "    ";
    printSyn(word);
    cout << endl;
}

void printSyn(dictionary *word) {
    dictionary *temp;
    temp = word->syn;

    while (temp) {
        cout << "   " << temp->word;
        temp = temp->next;
    }
}

void addWordPrint(dictionary *&Head) {
    cout << "how many words do you want to add?" << endl;
    int n;
    cin >> n;

    string word;
    for (int i = 0; i < n; ++i) {
        cout << "enter your word: " << endl;
        cin >> word;
        addWord(Head, word);
    }
    cout << "your words were successfully added!" << endl;
    cout << endl;
}

void addSynonymPrint(dictionary *&Head) {
    cout << "to which word do you want to add synonym? " << endl;
    string word;
    cin >> word;

    dictionary *find = searchWord(Head, word);

    if (find == nullptr) {
        cout << "we couldn't find the word!" << endl;
        cout << endl;
    } else {
        cout << "how many synonyms do you want to add?" << endl;
        int n;
        cin >> n;

        string synonym;
        for (int i = 0; i < n; ++i) {
            cout << "enter the synonym: " << endl;
            cin >> synonym;
            addSynonym(find, synonym);
        }
        cout << "your synonyms were successfully added!" << endl;
        cout << endl;
    }
}

void editWordPrint(dictionary *&Head) {
    string word, newWord;

    cout << "enter the word you want to edit:" << endl;
    cin >> word;

    cout << "enter the new word" << endl;
    cin >> newWord;

    editWord(Head, word, newWord);
    cout << "your word was successfully edited!" << endl;
    cout << endl;
}

void removeWordPrint(dictionary *&Head) {
    cout << "enter the word you want to remove: " << endl;
    string word;
    cin >> word;

    removeWord(Head, word);
    cout << "your word was successfully removed!" << endl;
    cout << endl;
}

void removeSynonymPrint(dictionary *&Head) {
    cout << "which word's synonyms do you want to remove: " << endl;
    string word, synonym;
    cin >> word;

    dictionary *find = searchWord(Head, word);

    if (find == nullptr) {
        cout << "we couldn't find the word!" << endl;
        cout << endl;
    } else {
        printWord(find);
        cout << "enter the synonym you want to remove: " << endl;
        cin >> synonym;
        removeSynonym(find, synonym);
        cout << "your synonym was successfully removed!" << endl;
        cout << endl;
    }
}

void searchWordPrint(dictionary *&Head) {
    cout << "enter the word: " << endl;
    string word;
    cin >> word;

    dictionary *find = searchWord(Head, word);

    if (find == nullptr) {
        cout << "we couldn't find the word!" << endl;
        cout << endl;
    } else {
        printWord(find);
    }
}

int count(const string &word) {
    int answer = 0;
    for (char ch : word) {
        if (ch == ' ')
            answer++;
    }
    return answer;
}

string wordsToString(dictionary *word) {
    string answer = word->word + " ";
    auto temp = word->syn;

    while (temp != nullptr) {
        answer += temp->word + " ";
        temp = temp->next;
    }
    return answer;
}

void saveInFile(dictionary *&Head) {
    ofstream save("dictionary.txt");

    dictionary *temp = Head;

    while (temp != nullptr) {
        save << wordsToString(temp) << endl;
        temp = temp->next;
    }
    cout << "words successfully added to file!" << endl;
    save.close();
}

dictionary *readFromFile(const string &address) {
    dictionary *Head = nullptr;
    string line;
    ifstream read(address);
    getline(read, line);
    int size = count(line);
    while (!read.eof()) {
        string word[size];
        getline(read, line);
    }
    return Head;
}

void exit(dictionary *&Head) {
    cout << "do you want to save changes? " << endl;
    cout << "yes or no " << endl;

    string command;
    cin >> command;

    if (command == "yes") {
        saveInFile(Head);
        exit(1);
    } else if (command == "no")
        exit(1);
}

void printMenu() {
    cout << "1. add word" << endl;
    cout << "2. add synonym" << endl;
    cout << "3. remove word" << endl;
    cout << "4. remove synonym" << endl;
    cout << "5. search word" << endl;
    cout << "6. edit word" << endl;
    cout << "7. print dictionary" << endl;
    cout << "8. save on file" << endl;
    cout << "9. read from file" << endl;
    cout << "10. exit" << endl;
}