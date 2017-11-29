#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

class Funcoes{
    public:
        string ler;
        string escrever;
        string mover;
        string proxEstado;
};


class Estado{
    public:
        string nome;
        Funcoes funcao[50];
};


void SMT(Estado estado[50], int cabecote, string fita, string estadoAtual, string estadoFinal){
    int i, j;
    string aux, aux2, aux3;
    
    i = 0;
        
    while(i < 50){
        if(estadoAtual == estado[i].nome){
            j = 0;
            while(j < 50){
                aux = estado[i].funcao[j].ler;
                aux2 = fita[cabecote];
                
                if(j == 49 && (strcmp(aux2.c_str(), aux.c_str()))){
                    if(estadoAtual == estadoFinal){
                        cout << "ACEITO" << endl;
                        exit(0);
                    }
                    else{
                        cout << "REJEITA" << endl;
                        exit(0);
                    }
                }
               
                
                if(!(strcmp(aux2.c_str(), aux.c_str()))){
                   
                   // cout << j << endl;
                    fita[cabecote] = estado[i].funcao[j].escrever[0];           // <<<< ESCREVER ANTES DE MOVER
                    
                    
                    if(estado[i].funcao[j].mover.c_str()[0] == 'E'){
                        cabecote--;
                    }
                    else if(estado[i].funcao[j].mover.c_str()[0] == 'D'){
                        cabecote++;
                    }
                    
                    estadoAtual = estado[i].funcao[j].proxEstado;
                    cout << fita << endl;
                    SMT(estado, cabecote, fita, estadoAtual, estadoFinal);
                   
                }
                
                j++;
            }
            
        }
        i++;
    }
}


int main(){
    string aux;
    string fita;
    string estados[50][50];
    string estadoInicial;
    string estadoFinal;
    int numEstados = 0;
    int numFunc = 0;
    int i = 0, j =0;
    fstream arq;
    string estadoAtual;
    int cabecote;
    
    arq.open("entrada.txt", ios::in | ios::out | ios::app);
        
    getline(arq, fita);
    arq.close();
    
    
    Estado estado[50];
  
    arq.open("funcao.txt", ios::in | ios::out | ios::app);
    
    string line[256];

    for(int i = 0; !(arq.eof()); i++)    {
        getline(arq, line[i]);
    }
    
    arq.close();
    
    
    estadoInicial = line[0];
    estadoFinal = line[1];
    
    numEstados = stoi(line[2]);
   
    int k = 3;
    
    for(i = 0; i < numEstados; i++){
        estado[i].nome = line[k]; k++;
        numFunc = stoi(line[k]); k++;
        for(j = 0; j < numFunc; j++){
            estado[i].funcao[j].ler = line[k]; k++;
            estado[i].funcao[j].escrever = line[k]; k++;
            estado[i].funcao[j].mover = line[k]; k++;
            estado[i].funcao[j].proxEstado = line[k]; k++;
        }
        
    }
   
   
    estadoAtual = estadoInicial;
    cabecote = 0;

    
    SMT(estado, cabecote, fita, estadoInicial, estadoFinal);
    
   
    return 0;
    
}