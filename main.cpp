#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

void perskaitymas(int Men_nuo[], int Diena_nuo[], int Men_iki[], int Diena_iki[], string Zuv[], int n){
    ifstream F("duom.txt");
    for(int i = 0; i < n; i++)
        F >> Zuv[i] >> Men_nuo[i] >> Diena_nuo[i] >> Men_iki[i] >> Diena_iki[i];
    F.close();
}
void sprendimas(int Men_nuo[], int Diena_nuo[], int Men_iki[], int Diena_iki[], string Zuv[], int n){
    time_t t = time(0);
    tm* now = localtime(&t);
    int k = 0;
    ofstream R("rez.txt");
    for(int i = 0; i < n; i++){
        if(((now->tm_mon + 1) >= Men_nuo[i]) && ((now->tm_mon + 1) <= Men_iki[i])){ // jei dabartinis menesis ieina i tam tikros zuvies zvejojimo draudimo menesius
            if(((now->tm_mon + 1) == Men_nuo[i]) && (now->tm_mday >= Diena_nuo[i]) && (Men_nuo[i] != Men_iki[i])){ // jei dabartinis menesis yra zvejojimo draudimo pirmas menesis, ir dabartine diena yra nemazesne uz draudimo isigaliojimo diena, ir draudimo pradzios ir pabaigos menesiai yra skirtingi
                if(k == 0){
                    R << "Dabar galiojantys draudimai:" << endl;
                    k++;
                }
                R << Zuv[i] << " - nuo " << setw(2) << setfill('0') << Men_nuo[i] << "-" << setw(2) << setfill('0') << Diena_nuo[i] << " iki " << setw(2) << setfill('0') << Men_iki[i] << "-" << setw(2) << setfill('0') << Diena_iki[i] << endl;
            }
            if((Men_nuo[i] < (now->tm_mon + 1)) && ((now->tm_mon + 1) < Men_iki[i])){ // jei dabartinis menesis yra tarp zvejybos draudimo menesiu
                if(k == 0){
                    R << "Dabar galiojantys draudimai:" << endl;
                    k++;
                }
                R << Zuv[i] << " - nuo " << setw(2) << setfill('0') << Men_nuo[i] << "-" << setw(2) << setfill('0') << Diena_nuo[i] << " iki " << setw(2) << setfill('0') << Men_iki[i] << "-" << setw(2) << setfill('0') << Diena_iki[i] << endl;
            }
            if(((now->tm_mon + 1) == Men_iki[i]) && (now->tm_mday <= Diena_iki[i])){ // jei dabartinis menesis yra paskutinis zvejybos draudimo menesis, ir dabartine diena yra ne didesne uz draudimo galiojimo pabaigos diena
                if(k == 0){
                    R << "Dabar galiojantys draudimai:" << endl;
                    k++;
                }
                R << Zuv[i] << " - nuo " << setw(2) << setfill('0') << Men_nuo[i] << "-" << setw(2) << setfill('0') << Diena_nuo[i] << " iki " << setw(2) << setfill('0') << Men_iki[i] << "-" << setw(2) << setfill('0') << Diena_iki[i] << endl;
            }
        }
        if((now->tm_mon + 1 < Men_iki[i]) && (Men_nuo[i] > Men_iki[i])){ // jei dabartinis menesis yra mazesnis uz draudimo pabaigos menesi, ir draudimo pradzios menesis yra didesnis (yra veliau) uz draudimo pasibaigimo menesi
            if(k == 0){
                    R << "Dabar galiojantys draudimai:" << endl;
                    k++;
                }
                R << Zuv[i] << " - nuo " << setw(2) << setfill('0') << Men_nuo[i] << "-" << setw(2) << setfill('0') << Diena_nuo[i] << " iki " << setw(2) << setfill('0') << Men_iki[i] << "-" << setw(2) << setfill('0') << Diena_iki[i] << endl;
            }
        if((now->tm_mon + 1 == Men_iki[i]) && (Men_nuo[i] > Men_iki[i]) && (now->tm_mday <= Diena_iki[i])){
            if(k == 0){
                    R << "Dabar galiojantys draudimai:" << endl;
                    k++;
                }
                R << Zuv[i] << " - nuo " << setw(2) << setfill('0') << Men_nuo[i] << "-" << setw(2) << setfill('0') << Diena_nuo[i] << " iki " << setw(2) << setfill('0') << Men_iki[i] << "-" << setw(2) << setfill('0') << Diena_iki[i] << endl;
            }
        if((now->tm_mon + 1 == Men_nuo[i]) && (Men_nuo[i] > Men_iki[i]) && (now->tm_mday >= Diena_nuo[i])){
            if(k == 0){
                    R << "Dabar galiojantys draudimai:" << endl;
                    k++;
                }
                R << Zuv[i] << " - nuo " << setw(2) << setfill('0') << Men_nuo[i] << "-" << setw(2) << setfill('0') << Diena_nuo[i] << " iki " << setw(2) << setfill('0') << Men_iki[i] << "-" << setw(2) << setfill('0') << Diena_iki[i] << endl;
            }
    }
    if(k == 0){
        R << "Dabar galiojanciu draudimu nera." << endl;
    }
    R.close();
}
int main()
{
    int n = 11; //n - kiek yra zuvu, kurioms taikomi draudimai
    int Men_nuo[n], Diena_nuo[n], Men_iki[n], Diena_iki[n]; // datos nuo kada iki kada galioja draudimai
    string Zuv[n]; // zuvu pavadinimai
    perskaitymas(Men_nuo, Diena_nuo, Men_iki, Diena_iki, Zuv, n);
    sprendimas(Men_nuo, Diena_nuo, Men_iki, Diena_iki, Zuv, n);
    return 0;
}
