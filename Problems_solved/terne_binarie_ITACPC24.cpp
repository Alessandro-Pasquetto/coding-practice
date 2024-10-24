#include <iostream>

/*

    Numero massimo di gruppi di terne di bit che in and danno 1

    Procedimento: conto il numero di terne e dopo sottraggo a partire dai gruppi migliori (quelli che non sprecano bit)

*/

using namespace std;

int min(int a, int b){

    if(a < b)
        return a;
    else
        return b;
}

int max(int a, int b){
    
    if(a > b)
        return a;
    else
        return b;
}

int main()
{

    int n = 0;
    cin>>n;

    int count = 0;
    int terne[7] = {0};

    while(n--){

        string n;
        cin>>n;

        int temp = stoi(n, nullptr, 2);

        if(temp == 7)
            count++;
        else
            terne[temp]++;
    }

    int k = 0;

    // 001 + 110
    k = min(terne[1], terne[6]);
    terne[1] -= k;
    terne[6] -= k;
    count += k;

    // 010 + 101
    k = min(terne[2], terne[5]);
    terne[2] -= k;
    terne[5] -= k;
    count += k;

    // 100 + 011
    k = min(terne[4], terne[3]);
    terne[4] -= k;
    terne[3] -= k;
    count += k;

    // 001 + 010 + 100
    k = min(terne[1], terne[2]);
    k = min(k, terne[4]);
    terne[1] -= k;
    terne[2] -= k;
    terne[4] -= k;
    count += k;

    while(terne[6] && terne[5] || terne[5] && terne[3] || terne[6] && terne[3]){

        // 110 + 101 / 101 + 011 / 110 + 011
        if(terne[6] == 0){
            k = min(terne[5], terne[3]);
            terne[5] -= k;
            terne[3] -= k;
            count += k;
            break;
        }
        else if(terne[5] == 0){
            k = min(terne[6], terne[3]);
            terne[6] -= k;
            terne[3] -= k;
            count += k;
            break;
        }
        else if(terne[3] == 0){
            k = min(terne[6], terne[5]);
            terne[6] -= k;
            terne[5] -= k;
            count += k;
            break;
        }else{
            k = max(terne[6], terne[5]);
            k = max(k, terne[3]);

            // Il secondo termine da sottrarre è indifferente (tanto maggiore di 0)
            if(terne[6] == k){
                terne[6]--;
                terne[5]--;
            }else if(terne[5] == k){
                terne[5]--;
                terne[6]--;
            }else{
                terne[3]--;
                terne[6]--;
            }

            count++;
        }
    }

    cout<<count;

    return 0;
}