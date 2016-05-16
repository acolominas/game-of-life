#include<iostream>
#include<vector>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#define NF 50
#define NC 50
using namespace std;

typedef vector<bool> Fila;
typedef vector<Fila> Matriu;

void crear_mon(Matriu& A) {
    cout << "### JOC DE LA VIDA ###" << endl;    
    cout << "1. Aleatori" << endl;
    cout << "2. Introduir mon" << endl;
    int opc;
    cin >> opc;
    if (opc == 1) { 
        srand(time(NULL));
        for (int i = 0; i < A.size(); ++i)
	    for (int j = 0; j < A[0].size(); ++j) A[i][j] = (rand()%2 == 0);        
    }
    else {  
        int a;
        for (int i = 0; i < A.size(); ++i)
            for (int j = 0; j < A[0].size(); ++j) {
	        cin >> a;
                if (a == 0) A[i][j] = false;
                else A[i][j] = true; 
            }
    }
}

void escriure_mon(const Matriu& A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j) {
	    if(A[i][j]) cout << "*";
            else cout << " ";
            cout << " ";
        }
        cout << endl;
    }
}

int calcular_veins_vius(const Matriu& A, int i, int j) {
    int vius = 0;
    if (i != 0) {
        if (j != 0 and A[i-1][j-1]) ++vius;
        if (A[i-1][j]) ++vius;
        if (j < A[0].size() - 1 and A[i-1][j+1]) ++vius;
    }
    if (j != 0 and A[i][j-1])  ++vius;
    if (j < A[0].size() - 1 and A[i][j+1])  ++vius;

    if (i < A.size() - 1) {
        if (j != 0 and A[i+1][j-1]) ++vius;
        if (A[i+1][j]) ++vius;
        if (j < A[0].size() -1 and A[i+1][j+1]) ++vius;
    }
    return vius;
}

void iniciar_vida(Matriu& est_actual, Matriu& est_seguent) {
    escriure_mon(est_actual);
    sleep(1);
    system("clear");       
    est_seguent = est_actual;
    while (1) {
        int vius;
        for(int i = 0; i < est_actual.size(); ++i) {
	    for (int j = 0; j < est_actual[0].size(); ++j) {
	        //calculem numero de veins vius
	        vius = calcular_veins_vius(est_actual,i,j);                
		//i modifiquem estat seguent, si cal
		if(not est_actual[i][j] and vius == 3) est_seguent[i][j] = true;
		if(est_actual[i][j] and (vius < 2 or vius > 3)) est_seguent[i][j] = false; 
            }
        }
        escriure_mon(est_seguent);
        usleep(75000);
        system("clear");        
        est_actual = est_seguent;
    }
}

int main() {
    Matriu est_actual(NF,Fila(NC));
    Matriu est_seguent(NF,Fila(NC));
    crear_mon(est_actual);
    escriure_mon(est_actual);   
    iniciar_vida(est_actual,est_seguent);
}
