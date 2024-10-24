#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct world_block{
    int this_counter_past_chars_left;
    string word;

    world_block(int this_counter_past_chars_left, string word){
        this->this_counter_past_chars_left = this_counter_past_chars_left;
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

    int counter_past_chars_left = 0;
    // Start
    for(char c: stringa){

        // Salva parole correntemente nell engine
        vector<world_block> worlds_in_engine = words_engine[c];

        // Svuota engine
        words_engine.clear();

        // Ricarica parole nell'engine togliendo il primo carattere
        for(world_block word_block: worlds_in_engine)
            words_engine[word_block.word[1]].push_back(world_block(word_block.this_counter_past_chars_left, word_block.word.substr(1)));

        // Carica parole nell'engine togliendo il primo carattere
        for(string word: dizionario[c])
            words_engine[word[1]].push_back(world_block(counter_past_chars_left, word.substr(1)));

        // Dopo aver caricato conto il carattere come lasciato indietro
        counter_past_chars_left++;
    
        // Completed words
        for(world_block word_completed: words_engine['\0']){
            if(counter_past_chars_left > word_completed.this_counter_past_chars_left)
                counter_past_chars_left = word_completed.this_counter_past_chars_left;
        }
    }

    cout<<counter_past_chars_left;

    return 0;
}