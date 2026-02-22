#include <iostream>

using namespace std;

/*

Vedere https://it.wikipedia.org/wiki/Permutazione
Le rotazioni permesse sono composte da 3 letterali (abc) ed è equivalente a due trasposizini da 2 letterali (ab)*(bc)
Si può dimostrare che se una stessa permutazione p può essere scritta sia come prodotto di h trasposizioni, sia come prodotto di trasposizioni, allora h e k hanno la stessa parità, cioè sono entrambi pari o entrambi dispari.

Essendo quindi che si parte/deve arrivare ad un ordinamento, nello stato di ordinamento ci sono 0 (pari) trasposizioni ed essendo che con le rotazioni di 3 letterali mi muovo di 2 trasposizioni alla volta è possibile arrivare solo
in permutazioni/stati generati da un numero pari di trasposizioni.
-> se ho una permutazione generata da un numero dispari di trasposizioni significa che con le rotazioni da 3 non è possibile arrivare a ordinamento

Nella pratica posso controllare se il numero di swap del bubble sort è pari o dispari...

*/


int main()
{

    int n;
    cin >> n;

    int input_nums[n];
    cin >> input_nums[0];

    int counter = 0;

    for (int i = 1; i < n; i++)
    {
        int n_input;
        cin >> n_input;

        input_nums[i] = n_input;

        // Bubble sort
        int k = 0;
        while(i - k > 0 && input_nums[i - k] < input_nums[i - k - 1]){

            int c = input_nums[i - k - 1];
            input_nums[i - k - 1] = input_nums[i - k];
            input_nums[i - k] = c;

            k++;
        }

        counter += k;
    }

    if(counter % 2 == 0)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}