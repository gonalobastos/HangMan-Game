#include <iostream>
#include <string>
#include <cctype> //tolower
#include <windows.h>
#include <fstream>
#include <iomanip>
#include "jogo_forca.h"



/****************************************************************************************************************************************************************************
 * Menu da opcao 5
*/
void configTemasPalavras(){

    string temasTab[20]; //tabela auxiliar para usar no nivel 2
    int numTemas = getTemas(temasTab);

    //debug!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //cout << numTemas;
    //printTab(temasTab, numTemas);
    //system("pause");

    string escolha;
    int sair_flag = 0;

    do{

        do{
            system("CLS");
            gotoxy(40,5);cout<< "*****CONFIG TEMAS E PALAVRAS****";
            gotoxy(40,6);cout<< "*  0.Config. Temas             *";
            gotoxy(40,7);cout<< "*  1.Config. Palavras          *";
            gotoxy(40,8);cout<< "*  2.Sair.                     *";
            gotoxy(40,9);cout<<"********************************";
            gotoxy(40,10);cout<< " Escolha: ";
            cin>> escolha;
        }while(escolha != "0" && escolha != "1" && escolha != "2");

        switch(stoi(escolha))
        {
        case 0:
            //CONFIGURAR TEMAS
        {
            configTemas(temasTab, numTemas);
            break;
        }

        case 1:
            //CONFIGURAR PALAVRAS
        {
            modifica();
            break;
        }
        case 2:
            //SAIR
            sair_flag = 1;
            break;
        }

    }while(sair_flag != 1);

    putTemas(temasTab, numTemas);

}

/****************************************************************************************************************************************************************************
 * Configurar temas
*/
void configTemas(string temasTab[], int &numTemas) {
    string escolha;
    int sair_flag = 0;

    do{
        do{
            system("CLS");
            gotoxy(40,5);cout<< "***********CONFIG TEMAS*********";
            gotoxy(40,6);cout<< "*  0.Inserir                   *";
            gotoxy(40,7);cout<< "*  1.Apagar                    *";
            gotoxy(40,8);cout<< "*  2.Modificar                 *";
            gotoxy(40,9);cout<< "*  3.Voltar                    *";
            gotoxy(40,10);cout<<"********************************";
            gotoxy(40,11);cout<< " Escolha: ";
            cin>> escolha;
        }while(escolha != "0" && escolha != "1" && escolha != "2" && escolha != "3");

        switch(stoi(escolha))
        {
        case 0:
        {
            //INSERIR TEMAS = Criar ficheiros

            system("cls");
            //Peedir nome do tema
            string newTema1;
            gotoxy(40,5);cout << "***********************************";
            gotoxy(40,6);cout << "* Introduza o Tema.               *";
            gotoxy(40,7);cout << "* ->                              *";
            gotoxy(40,8);cout << "***********************************";
            gotoxy(44,7);cin >> newTema1;

            //criar ficheiro
            string newTema = newTema1 + ".txt"; //concatenação
            fstream tema;
            tema.open(newTema,  fstream::in | fstream::out | fstream::trunc);

            if(!tema){
                cout << "Erro ao criar o ficheiro";
                system("pause");
            }
            else{
                //!!!!!!update tab de temas
                temasTab[numTemas] = newTema1;//numTemas - 1 pois queremos indice
                numTemas++;
                putTemas(temasTab, numTemas);//update Temas file
                //verificação
                gotoxy(40,9);cout << "Tema criado com sucesso!";
                gotoxy(40,10);system("pause");
            }

            //fechar ficehrio
            tema.close();

            break;
        }
        case 1:
        {
            //APAGAR TEMAS - apagar ficheiros

            //verificar que ficam 3 temas
            if(numTemas == 3){
                system("cls");
                gotoxy(40,5);cout << "ERRO: Impossivel apagar tema. ";
            }

            system("cls");
            //Peedir nome do tema
            string newTema1;
            gotoxy(40,5);cout << "***********************************";
            gotoxy(40,6);cout << "* Introduza o tema a apagar.      *";
            gotoxy(40,7);cout << "* ->                              *";
            gotoxy(40,8);cout << "***********************************";
            gotoxy(44,7);cin >> newTema1;

            //apagar tema, apagar ficheiro e apagar no ficheiro temas
            string newTema = newTema1 + ".txt";
            apagarFicheiro(newTema, newTema1, temasTab, numTemas);
            numTemas--;

            //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //printTab(temasTab, numTemas);system("pause");

            putTemas(temasTab, numTemas);//update Temas file

            break;
        }
        case 2:
        {
            //MODIFICAR TEMAS = modificar palavaras - i.e adicionar alterar ou remover
            modifica();
            break;
        }
        case 3:
        {
            //VOLTAR

            sair_flag=1;
            break;
        }

        }

    }while(sair_flag != 1);

}


/****************************************************************************************************************************************************************************
 * Modifica palavras no tema = modifciar o tema
*/
void modifica(){


    system("cls");
    //Peedir nome do tema
    string newTema1;
    gotoxy(40,5);cout << "***********************************";
    gotoxy(40,6);cout << "* Introduza o Tema.               *";
    gotoxy(40,7);cout << "* ->                              *";
    gotoxy(40,8);cout << "***********************************";
    gotoxy(44,7);cin >> newTema1;

    //abrir ficheiro
    string newTema = newTema1 + ".txt"; //concatenação
    fstream tema;
    tema.open(newTema);

    //vweficação de tema existente
    while(!tema.is_open()){
        system("cls");
        gotoxy(40,7);cout << "ERRO: Tema nao Existente.";
        gotoxy(40,8);system("pause");

        //Peedir nome do tema
        system("cls");
        newTema1.clear();
        gotoxy(40,5);cout << "***********************************";
        gotoxy(40,6);cout << "* Introduza o Tema.               *";
        gotoxy(40,7);cout << "* ->                              *";
        gotoxy(40,8);cout << "***********************************";
        gotoxy(44,7);cin >> newTema1;

        //abrir ficheiro
        newTema = newTema1 + ".txt"; //concatenação
        tema.open(newTema);
    }

    //passar tema para uma tabela
    string temaTab[20];
    int saidasTab[20];
    int i = 0;
    int num_palavras = 0;
    while(tema.peek() != EOF){
        tema >> temaTab[i] >> saidasTab[i] ;
        i++;
        num_palavras++;
    }//if(num_palavras != 0)num_palavras--;
    //FECHAR
    tema.close();

    //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //cout<<num_palavras;system("pause");

    //alteracoes sao feitas na tabela
    string escolha;
    int terminar = 0;
    while(terminar != 1)
    {


        system("CLS");
        //printar conteudo do tema
        gotoxy(40,4);cout<< "**************TEMA**************";
        for(int j = 0; j < num_palavras; j++){
            gotoxy(40,5+j);cout << newTema1 << "[" << j << "]: " << temaTab[j];;
        }
        gotoxy(40, 5+num_palavras);cout<< "********************************";

        //minimenu - pedir o que fazer
        do{
            gotoxy(40,5+num_palavras+2);cout<< "*********CONFIG PALAVRAS********";
            gotoxy(40,5+num_palavras+3);cout<< "*  0.Alterar Palavra           *";
            gotoxy(40,5+num_palavras+4);cout<< "*  1.Apagar Palavra            *";
            gotoxy(40,5+num_palavras+5);cout<< "*  2.Acrescentar Palavra       *";
            gotoxy(40,5+num_palavras+6);cout<< "*  3.Terminar                  *";
            gotoxy(40,5+num_palavras+7);cout<<"********************************";
            gotoxy(40,5+num_palavras+8);cout<< " Escolha: ";
            cin>> escolha;
        }while(escolha != "0" && escolha != "1" && escolha != "2" && escolha != "3");

        switch(stoi(escolha))
        {
        case 0 :
        {
            //pedir linha
            int linha;
            do{
                system("cls");
                gotoxy(40,5);cout << "***********************************";
                gotoxy(40,6);cout << "* Introduza o Indice .            *";
                gotoxy(40,7);cout << "* ->                              *";
                gotoxy(40,8);cout << "***********************************";
                gotoxy(44,7);cin >> linha;
            }while(linha < 0 || linha > num_palavras-1);

            //pedir palavra
            string palavraNova;
            gotoxy(40,5);cout << "***********************************";
            gotoxy(40,6);cout << "* Introduza a nova Palavra.       *";
            gotoxy(40,7);cout << "* ->                              *";
            gotoxy(40,8);cout << "***********************************";
            gotoxy(44,7);cin >> palavraNova;

            //alterar palavras
            temaTab[linha].clear();
            temaTab[linha].insert(0,palavraNova);

            //atualizar saidas
            saidasTab[linha] = 0;

            //verif
            system("cls");
            gotoxy(40,5);cout << "Palavra alterada com sucesso! ";
            gotoxy(40,6);system("pause");

            break;

        }
        case 1 :
        {
            system("cls");
            //verificar se ficam no minimo 8 palavras no ficheiro
            if(removepalavra(temaTab, saidasTab, num_palavras)){
                gotoxy(40,5);cout << "Palavra removida com sucesso";
                num_palavras--;
                gotoxy(40,6);system("pause");
            }else{
                gotoxy(40,5);cout << "Impossivel remover. Minimo 8 palavras necessario";
                gotoxy(40,6);system("pause");
            }

            break;
        }
        case 2 :
        {
            //pedir palavra
            system("cls");
            string palavraNova;
            gotoxy(40,5);cout << "***********************************";
            gotoxy(40,6);cout << "* Introduza a nova Palavra.       *";
            gotoxy(40,7);cout << "* ->                              *";
            gotoxy(40,8);cout << "***********************************";
            gotoxy(44,7);cin >> palavraNova;
            //adicionar a tabela de palavras
            temaTab[num_palavras] = palavraNova;
            //adicionar uma linha a 0 as saidas
            saidasTab[num_palavras] = 0;
            //incrementar o numero de palavras
            num_palavras++;
            //verif
            system("cls");
            gotoxy(40,5);cout << "Palavra adicionada com sucesso! ";
            gotoxy(40,6);system("pause");
            break;
        }

        case 3 :
        {
            terminar = 1;
            break;
        }
        }

        //DEPOIS DE SAIR DO SWITCH
        //passar a tabela para o ficheiro
        ofstream tema2;
        tema2.open(newTema, ios::trunc);
        if(!tema2.is_open()){
            cout << "erro ao abrir ficheiro";
            system("pause");
        }
        for(int k = 0; k<num_palavras; k++){
            tema2 << temaTab[k] << " " << saidasTab[k];
            if(k != num_palavras-1){
                tema2<<endl;
            }
        }
        tema2.close();
    }
}

/****************************************************************************************************************************************************************************
 * remove um elemento de uma tabela verificando se ficam 8 elementos
*/
bool removepalavra(string tab[], int saidasTab[], int dim){

    //verifcar se deppoois de apagar ficam 8 palavras
    if(dim < 9) return false;

    //pedir indice
    int linha;
    do{
        system("cls");
        gotoxy(40,5);cout << "***********************************";
        gotoxy(40,6);cout << "* Introduza o Indice .            *";
        gotoxy(40,7);cout << "* ->                              *";
        gotoxy(40,8);cout << "***********************************";
        gotoxy(44,7);cin >> linha;
    }while(linha < 0 || linha > dim-1);

    //remove palavras
    string tab_aux[dim];
    int j = 0;
    for(int i = 0; i<dim ; i++){
        if(i != linha){
            tab_aux[j] = tab[i];
            j++;
        }
    }
    tab = tab_aux;

    //remove numero de saidas da palavra
    int tab_aux2[dim];
    int k = 0;
    for(int i = 0; i<dim ; i++){
        if(i != linha){
            tab_aux[k] = tab[i];
            k++;
        }
    }
    saidasTab = tab_aux2;

    return true;
}


/****************************************************************************************************************************************************************************
 * Apaga tema = apagar ficheiro
*/
void apagarFicheiro(string fileName, string tema, string temasTab[], int numTemas){

    //apagar da tabela de temas para deois pagar do ficheiro de temas
    string tab_aux[numTemas];
    int j = 0;

    for(int i = 0; i<numTemas ; i++){
        if(temasTab[i].compare(tema) != 0){
            tab_aux[j] = temasTab[i];
            j++;
        }
    }
    temasTab = tab_aux;

    //apagar ficheiro
    int status;
    const char *filename = fileName.c_str();
    status = remove(filename);
    if(status==0)
    {
        system("cls");
        gotoxy(40,5);cout<<"Tema apagado com sucesso!";
        gotoxy(40,6);system("pause");
    }
    else
    {
        system("cls");
        gotoxy(40,5);cout<<"Erro!!";
        gotoxy(40,6);system("pause");
    }
}

/****************************************************************************************************************************************************************************
 * Vai buscar os temas e coloca em uma tabela, retorna o numero de temas
*/
int getTemas(string temasTab[]){

    int contTemas = 0;

    ifstream filetemas;
    filetemas.open("Temas.txt");//ios::in|ios::out|ios::trunc
    if ( !filetemas.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    //Recover data from backup-> se houver conteudo no backup
    while(filetemas.peek() != EOF){
        filetemas >> temasTab[contTemas];
        contTemas++ ;//atualizar o jogador atual
    }

    //close file
    filetemas.close();

    return contTemas;
}

/****************************************************************************************************************************************************************************
 * Passa a tabela de temas para o ficheiro de temas
*/
void putTemas(string temasTab[], int numTemas){
    //Dbug!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //cout<<"Em putTemas."<<endl;
    //printTab(temasTab, numTemas);

    //open file
    ofstream filetemas;
    filetemas.open("Temas.txt", ios::trunc);
    if ( !filetemas.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    //save
    for(int i = 0; i < numTemas; i++){
        filetemas << temasTab[i];
        //so meto endl se nao for a ultima linha
        if(i != numTemas-1){
            filetemas << endl;
        }
    }

    //close file
    filetemas.close();
}


/****************************************************************************************************************************************************************************
 * Verifica se o tema existe
*/
bool temaExiste(string tema, string tab[], int dim){
    for(int i=0; i<dim; i++){
        if(tab[i].compare(tema) == 0){
            return true;
        }
    }
    return false;
}
