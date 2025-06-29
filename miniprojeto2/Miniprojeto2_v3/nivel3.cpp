#include <iostream>
#include <string>
#include <cctype> //tolower
#include <windows.h>
#include <fstream>
#include <iomanip>
#include "jogo_forca.h"


/*******************************************************************************************
 *
*/
string getPalavraeSaidas(string tema, int mode){
    srand (time(NULL));

    //open file para leitura
    string escolha = tema + ".txt";
    ifstream palavras;
    palavras.open(escolha); //escolha - tema.txt
    if (!palavras.is_open()) {
        cout << "Error opening file"<< endl;
        system("pause");
    }


    //escolha da Palvara
    int saidasTab[25];
    string tabPalavras[25];
    int i= 0;
    while(palavras.peek() != EOF){
        palavras >> tabPalavras[i] >> saidasTab[i];
        i++;
    }
    int numPalavras = i;

    //close file
    palavras.close();

    //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //cout<<"num_palavras " << numPalavras;
    //printTabTemaSaidas(tabPalavras, saidasTab, numPalavras);
    //system("pause");

    //escolher o indice da palavra
    int random = rand() %numPalavras;//0-num_palavras
    int seed = randomidx(saidasTab, numPalavras);

    //tabela ja vem atualizada

    //open file para escrita
    ofstream palavras2;
    palavras2.open(escolha, ios::trunc); //escolha - tema.txt
    if (!palavras2.is_open()) {
        cout << "Error opening file"<< endl;
        system("pause");
    }

    //atualizar file
    for(int i = 0; i<numPalavras; i++){
        palavras2 << tabPalavras[i] << " " << saidasTab[i];
        //IMPORTANATE- So damos \n se nao for a ultima linha
        if(i != numPalavras-1){
            palavras2 << endl;
        }
    }

    //close file
    palavras2.close();

    if(mode == 1 || mode == 2 || mode == 3|| mode == 4){
        return (tabPalavras[random]);
    }
    else{
        return(tabPalavras[seed]);
    }
}


int randomidx(int saidasTab[], int dim){
    srand (time(NULL));
    int random;
    bool certo = false;
    bool saidasIguais = true;

    //verificar se saidas iguuais
    for(int i = 0; i<dim; i++){
        for(int j = 0; j<dim; j++){
            if(saidasTab[i] != saidasTab[j]){
                saidasIguais = false;
            }
        }
    }

    //resolver bug se todos estiverem igual saidas
    if(saidasIguais == true){
        //atualizar tab
        saidasTab[0]++;
        return 0;//retorna um indice qualquer, é indiferente
    }

    //encontrar o maior numero da tabela
    int maior = saidasTab[0];
    for(int i = 0; i < dim; i++){
        if(saidasTab[i] > maior)
        {
            maior = saidasTab[i];
        }
    }

    while(!certo){
        //gerar indice aleatorio
        random = rand() %dim;//0-num_palavras
        //verifcar se nesse indice o elemento e diferente de maior
        if(saidasTab[random] != maior){
            //se for - certo = true;
            saidasTab[random] = maior;//alterar a Tab de saidas para deois alterar ficheiro
            certo = true;
        }
    }
    return(random);
}
