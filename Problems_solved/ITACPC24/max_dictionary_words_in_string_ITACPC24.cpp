#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct world_block{
    int this_counter_chars_left_behind;
    string word;

    world_block(int this_counter_chars_left_behind, string word){
        this->this_counter_chars_left_behind = this_counter_chars_left_behind;
        this->word = word;
    }
};

int main()
{
    
    unordered_map <char, vector<string>> dizionario;
    unordered_map <char, vector<world_block>> words_engine;

    string stringa;
    cin >> stringa;
    
    int n;
    cin >> n;

    while(n--){
        // Carico words in dizionario
        string word;
        cin >> word;
        dizionario[word[0]].push_back(word);
    }

    int counter_chars_left_behind = 0;
    // Start
    for(char c: stringa){

        // Salva parole correntemente nell engine
        vector<world_block> words_in_engine = words_engine[c];

        // Svuota engine
        words_engine.clear();

        // Ricarica parole nell'engine togliendo il primo carattere
        for(world_block word_block: words_in_engine)
            words_engine[word_block.word[1]].push_back(world_block(word_block.this_counter_chars_left_behind, word_block.word.substr(1)));

        // Carica parole nell'engine togliendo il primo carattere
        for(string word: dizionario[c])
            words_engine[word[1]].push_back(world_block(counter_chars_left_behind, word.substr(1)));

        // Dopo aver caricato conto il carattere come lasciato indietro
        counter_chars_left_behind++;
    
        // Completed words
        for(world_block word_completed: words_engine['\0']){
            if(counter_chars_left_behind > word_completed.this_counter_chars_left_behind)
                counter_chars_left_behind = word_completed.this_counter_chars_left_behind;
        }
    }

    cout<<counter_chars_left_behind;

    return 0;
}