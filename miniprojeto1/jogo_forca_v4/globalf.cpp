/*
 * Ficheiro com as funçoes usadas em todo o programa
*/

#include <iostream>
#include <string>
#include <cctype> //tolower
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "jogo_forca.h"

using namespace std;

//-----------------------------------------------------------------------------
//Globais-----------------------------------------------------------------------
//------------------------------------------------------------------------------
/**************************************************************************/
/*!
    @brief  Printa a capa do jogo
    @param  None
    @return None
*/
/**************************************************************************/
void abertura(){
    //abertura----------------------------
    char aux{};
    do{
        gotoxy(40,5);cout<< "************JOGO DA FORCA*************";
        gotoxy(40,6);cout << "*            ___________             *";
        gotoxy(40,7);cout << "*            |         |             *";
        gotoxy(40,8);cout << "*            |         O             *";
        gotoxy(40,9);cout << "*            |       \\ | /           *" ;
        gotoxy(40,10);cout << "*            |         |             *";
        gotoxy(40,11);cout << "*            |        / \\            *";
        gotoxy(40,12);cout << "*           _|______________         *";
        gotoxy(40,13);cout << "**************************************";
        gotoxy(40,14);cout << "* Criado por:                        *";
        gotoxy(40,15);cout << "*  -Goncalo Bastos, 2020238997       *";
        gotoxy(40,16);cout << "*  -Jose Nogueira, 2020233342        *";
        gotoxy(40,17);cout << "* Data: 25/04/2021                   *";
        gotoxy(40,18);cout << "**************************************";
        gotoxy(40,20);cout << "Press any key(and enter) to Start -> ";
        cin >> aux;
    }while(aux == 0);

    return;//return to main
}



/**************************************************************************/
/*!
    @brief  Printa o menu
    @param  None
    @return None
*/
/**************************************************************************/
void menu(){
    //menu

    //memory allocation
    Jogador *Jogadores = new Jogador[MAX_JOGADORES]; //tabela de jogadores //Jogadores funciona como uma tabela normal
    int idx_jdr = 0;//tem sempre o indice do jogador atual

    //open backup file stream OBS!!IMPORTANTE TEM DE TER PELO MENOS 1 JOGADOR NO FICHEIRO PORQUE ELE NAO ESTA A VERIFICAR BBEM SE O FILE ESTA VAZIO E CRIA UM JOGADOR A 0
    ifstream backupfile;
    backupfile.open("backup.txt");//ios::in|ios::out|ios::trunc
    if ( !backupfile.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    //Recover data from backup-> se houver conteudo no backup
    if(backupfile.peek() != EOF){
        while(backupfile.peek() != EOF){
            backupfile >> Jogadores[idx_jdr].nome >> Jogadores[idx_jdr].pontuacao >> Jogadores[idx_jdr].gamemode >> Jogadores[idx_jdr].dif >> Jogadores[idx_jdr].pausa;
            idx_jdr++ ;//atualizar o jogador atual
        }
    }

    //close file
    backupfile.close();

    //assegurar que o utilizador introduz uma das opcoes
    int escolha;
    int sair_flag = 0;

    //variaveis auxiliares para a opcao 0 do menu
    string nome_aux;
    int i_aux;
    int pontuacao_ant = 0;

    //variaveis auxiliares para a opcao 2 do menu
    int num_jogadores = 0;
    int iPorPontuacao[num_jogadores];//tabela de indices

    do{
        //entro neste loop com o indice de memoria vazio
        //DEBUG
        //cout << "idx_jdr = " << idx_jdr << endl;
        //Jogadores->mostraMemoria(Jogadores , idx_jdr);
        //system("pause");
        do{
            system("CLS");
            gotoxy(40,5);cout<< "**************MENU**************";
            gotoxy(40,6);cout<< "*  0.Iniciar novo jogo.        *";
            gotoxy(40,7);cout<< "*  1.Modo de Funcionamento.    *";
            gotoxy(40,8);cout<< "*  2.Mostrar Pontuacoes.       *";
            gotoxy(40,9);cout<< "*  3.Sair.                     *";
            gotoxy(40,10);cout<<"********************************";
            gotoxy(40,12);cout<< " Escolha: ";
            cin >> escolha;
        }while(escolha != 0 && escolha!=1 && escolha!=2 && escolha!=3);

        switch(escolha)
        {
            case 0:
                //Antes de comecar a jogar
                //Pedir para introduzir o nome de jogador=escolher o save
                system("cls");
                gotoxy(40,5);cout << "********************************";
                gotoxy(40,6);cout << "* Introduza o seu nome se pre- *";
                gotoxy(40,7);cout << "* tende continuar a jogar ou   *";
                gotoxy(40,8);cout << "* um novo nome e comecar outro *";
                gotoxy(40,9);cout << "* jogo.                        *";
                gotoxy(40,10);cout << "********************************";
                gotoxy(40,11);cout << "Nome: ";

                cin >> nome_aux;cout << endl;

                //verificar se ja existe na memoria um jogador com este nome
                i_aux = Jogadores->procuraNome(nome_aux, Jogadores, idx_jdr); //i_aux recebe o indice de memoria do save do jogador
                if (i_aux >= 0){
                    char answer{};
                    do{
                        system("cls");
                        gotoxy(40,5);cout << "***********************************";
                        gotoxy(40,6);cout << "*Ja existe um save com esse nome  *";
                        gotoxy(40,7);cout << "*Deseja continuar a jogar?        *";
                        gotoxy(40,8);cout << "*                                 *";
                        gotoxy(40,9);cout << "***********************************";
                        gotoxy(40,10);cout << "*Escolha [S/N]: ";

                        cin >> answer;
                        if(answer == 'S' || answer =='s'){

                            //antes de tudo verificar se tem um jog em pausa - Se SIM saltar logo para novo jogo
                            if(Jogadores[i_aux].pausa == 1){
                                Jogadores[i_aux].novoJogo();
                                break;
                            }

                            //reset da pontuacao
                            pontuacao_ant = Jogadores[i_aux].pontuacao;
                            Jogadores[i_aux].pontuacao = 0;

                            //perguntar se pretende alterar o modo- so se nao tiver um jogo suspenso
                            char ans{};
                            while(ans == 0){
                                system("cls");
                                gotoxy(40,5);cout << "***********************************";
                                gotoxy(40,6);cout << "*Alterar o modo Selecionado antes?*";
                                gotoxy(40,7);cout << "*                                 *";
                                gotoxy(40,8);cout << "***********************************";
                                gotoxy(40,9);cout << "*Escolha [S/N]: ";
                                cin >> answer;
                                if(answer == 'S' || answer =='s'){
                                    Jogadores[i_aux].modos();
                                    if(Jogadores[i_aux].gamemode != 1){
                                        //Dificuldade
                                        Jogadores[i_aux].dificuldade();
                                    }
                                    break;
                                }else if(answer == 'N' || answer =='n'){
                                    break;
                                }
                            }

                            //iniciar o jogo com esse save (ou jogador)
                            Jogadores[i_aux].novoJogo();

                            //Se a pontuacao conseguida for menor que a anterior, manter a maior
                            if(Jogadores[i_aux].pontuacao < pontuacao_ant){
                                Jogadores[i_aux].pontuacao = pontuacao_ant;
                            }

                            //save to backup
                            Jogadores[idx_jdr].backup(Jogadores, idx_jdr);

                        }
                        else if(answer == 'N' || answer =='n'){
                            system("cls");

                            //pedir um novo nome e criar um jogador novo no topo da lista -ASSUMINDO QUE introduz um nome que nao esta na memoria
                            gotoxy(40,5);cout << "***********************************";
                            gotoxy(40,6);cout << "* Introduza o nome.               *";
                            gotoxy(40,7);cout << "* ->                              *";
                            gotoxy(40,8);cout << "***********************************";
                            gotoxy(45,7);cin >> Jogadores[idx_jdr].nome;//save to mem

                            //perguntar se pretende alterar o modo
                            char ans{};
                            do{
                                system("cls");
                                gotoxy(40,5);cout << "***********************************";
                                gotoxy(40,6);cout << "*Alterar o modo Selecionado antes?*";
                                gotoxy(40,7);cout << "*                                 *";
                                gotoxy(40,8);cout << "***********************************";
                                gotoxy(40,9);cout << "*Escolha [S/N]: ";
                                cin >> answer;
                                if(answer == 'S' || answer =='s'){
                                    Jogadores[idx_jdr].modos();
                                    if(Jogadores[idx_jdr].gamemode != 1){
                                        //Dificuldade
                                        Jogadores[idx_jdr].dificuldade();
                                    }
                                    break;
                                }else if(answer == 'N' || answer =='n'){
                                    break;
                                }
                            }while(ans == 0);

                            //chamar menu com esse novo jogador
                            Jogadores[idx_jdr].novoJogo();

                            //save to backup
                            Jogadores[idx_jdr].backup(Jogadores, idx_jdr);

                            //novo jogador
                            idx_jdr++;
                        }
                        else{
                            gotoxy(40,5);cout << "Invalido, introduza[S/N]: ";
                        }
                    }while(answer == 0);
                }
                //Se nao existir na memoria
                else{

                    //se nao existir este jogador com o nome- save to memoria
                    Jogadores[idx_jdr].nome = nome_aux;

                    //apresentar o menu PARA O JOGADOR[i](= iniciar o jogo em si)
                    Jogadores[idx_jdr].novoJogo();

                    //no fim da partida deste jogador -save to backup
                    Jogadores[idx_jdr].backup(Jogadores, idx_jdr);     

                    //novo jogador
                    idx_jdr++;
                }
                break;

            case 1:
                //Modos
                Jogadores[idx_jdr].modos();
                if(Jogadores[idx_jdr].gamemode != 1){
                    //Dificuldade
                    Jogadores[idx_jdr].dificuldade();
                }
                //save to backup
                Jogadores[idx_jdr].backup(Jogadores, idx_jdr);
             break;

            case 2:
                //Score board
                num_jogadores = idx_jdr + 1;
                Jogadores->mostraOrdenaPorPontuacao(Jogadores, num_jogadores, iPorPontuacao);
                break;

            case 3:
                //Sair
                sair_flag = 1;
                return;

            default:
            break;
        }
    }while(sair_flag == 0);

    //memory desallocation
    delete[] Jogadores;

    return;
}


/**************************************************************************/
/*!
    @brief  Desenha a Forca dependendo da tentativa
    @param  tentativa atual
    @return void
*/
/**************************************************************************/

void desenha(int tentativas)
{
    //desenho depende da tentativa

    switch(tentativas)
         {
         case 9:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "*                  *"<<endl;
             gotoxy(40,6);cout << "*                  *"<<endl;
             gotoxy(40,7);cout << "*                  *"<<endl;
             gotoxy(40,8);cout << "*                  *" <<endl;
             gotoxy(40,9);cout << "*                  *"<<endl;
             gotoxy(40,10);cout << "*                  *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 8:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "*                  *"<<endl;
             gotoxy(40,6);cout << "*                  *"<<endl;
             gotoxy(40,7);cout << "*                  *"<<endl;
             gotoxy(40,8);cout << "*                  *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 7:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "*                  *"<<endl;
             gotoxy(40,6);cout << "*                  *"<<endl;
             gotoxy(40,7);cout << "* |                *"<<endl;
             gotoxy(40,8);cout << "* |                *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 6:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "*                  *"<<endl;
             gotoxy(40,6);cout << "* |                *"<<endl;
             gotoxy(40,7);cout << "* |                *"<<endl;
             gotoxy(40,8);cout << "* |                *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 5:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "* ___________      *"<<endl;
             gotoxy(40,6);cout << "* |         |      *"<<endl;
             gotoxy(40,7);cout << "* |                *"<<endl;
             gotoxy(40,8);cout << "* |                *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 4:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "* ___________      *"<<endl;
             gotoxy(40,6);cout << "* |         |      *"<<endl;
             gotoxy(40,7);cout << "* |         O      *"<<endl;
             gotoxy(40,8);cout << "* |                *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 3:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "* ___________      *"<<endl;
             gotoxy(40,6);cout << "* |         |      *"<<endl;
             gotoxy(40,7);cout << "* |         O      *"<<endl;
             gotoxy(40,8); cout << "* |         |      *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 2:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "* ___________      *"<<endl;
             gotoxy(40,6);cout << "* |         |      *"<<endl;
             gotoxy(40,7);cout << "* |         O      *"<<endl;
             gotoxy(40,8);cout << "* |       \\ | /    *" <<endl;
             gotoxy(40,9);cout << "* |                *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 1:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "* ___________      *"<<endl;
             gotoxy(40,6);cout << "* |         |      *"<<endl;
             gotoxy(40,7);cout << "* |         O      *"<<endl;
             gotoxy(40,8);cout << "* |       \\ | /    *" <<endl;
             gotoxy(40,9);cout << "* |         |      *"<<endl;
             gotoxy(40,10);cout << "* |                *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
         break;
         case 0:
             gotoxy(40,4);cout << "********************"<<endl;
             gotoxy(40,5);cout << "* ___________      *"<<endl;
             gotoxy(40,6);cout << "* |         |      *"<<endl;
             gotoxy(40,7);cout << "* |         O      *"<<endl;
             gotoxy(40,8);cout << "* |       \\ | /    *" <<endl;
             gotoxy(40,9);cout << "* |         |      *"<<endl;
             gotoxy(40,10);cout << "* |        / \\     *"<<endl;
             gotoxy(40,11);cout << "*_|________________*"<<endl;
             gotoxy(40,13);cout << "-----VOCE MORREU----"<<endl;
         }
         return;
};

/**************************************************************************/
/*!
    @brief  posiciona o cursor onde é necessario
*/
/**************************************************************************/
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

/**************************************************************************/
/*!
    @brief  Funçao que devolve a posiçao na memoria, *p, do jogador que contem
    o mesmo nome que o nome inserido(nome), como sabemos que so havera
    saves de  jogadores entre 0 e idx_jgdr, basta procurar nesse intervalo
    @param  string nome - nome introduzido
            Jogador *p - ponteiro para a tabela de jogadores
            idx_jdr - dimensao da tabela de jogadores
   @return indice

*/
/**************************************************************************/
int Jogador::procuraNome(string nome_aux, Jogador p[], int idx_jdr)const
{
    int dim = idx_jdr + 1;

    //pesquisa Sequencial pois a tabela nao precisa esatr ordenada
    for(int i = 0; i<dim; i++){
        if(p[i].nome.compare(nome_aux) == 0){
            return i;
        }
    }
    return -1;
}
/**************************************************************************/
/*!
    @brief  gera uma palavra aleatoria
    @param  recebe o tema
    @return retorna a palavra
*/
/**************************************************************************/
string getPalavra(string tema){
    srand (time(NULL));

    //open file
    string escolha = tema + ".txt";
    ifstream palavras;
    palavras.open(escolha); //escolha - tema.txt
    if (!palavras.is_open()) {
        cout << "Error opening file"<< endl;
    }
    //Sabemos que temos 8 palavras em tema.txt
    string listapalavras[8]; //strigs ja sao alocadas na memoria dinamica
    string palavra;
    //ler as palavras do ficheiro
    for(int i = 0; i<48; i++){
        palavras >> listapalavras[i];
    }

    //escolher um elemnto da tabela de strings ao calhas
    int random = rand() %8;//0-8
    palavra = listapalavras[random];//TEMOS A PALAVRA

    //close file
    palavras.close();

    return(palavra);
}

/**************************************************************************/
/*!
    @brief  printa as instrucoes do mod elementar
*/
/**************************************************************************/
void instrucoes_elementar(){
    system("CLS");
    gotoxy(40,5);cout<< "***********INSTRUCOES*************";
    gotoxy(40,6);cout<< "*->Adivinhar a palavra, sabendo  *";
    gotoxy(40,7);cout<< "* o tema e o num de letras, se   *";
    gotoxy(40,8);cout<< "* vencer vai ser apresentada ou- *";
    gotoxy(40,9);cout<< "* tra palavra para continuar.    *";
    gotoxy(40,10);cout<< "**********************************";
    gotoxy(40,12);system("pause");
}


/**************************************************************************/
/*!
    @brief  printa as instrucoes do modo basico
*/
/**************************************************************************/
void instrucoes_basico_medio(int diff){
    if(diff == 1){
        system("CLS");
        gotoxy(40,5);cout<< "***********INSTRUCOES*************";
        gotoxy(40,6);cout<< "*->Adivinhar a palavra, sabendo  *";
        gotoxy(40,7);cout<< "* o tema e o num de letras, se   *";
        gotoxy(40,8);cout<< "* vencer vai ser apresentada ou- *";
        gotoxy(40,9);cout<< "* tra palavra para continuar.    *";
        gotoxy(40,10);cout<< "* ATENCAO: Tens 20 seg para adi- *";
        gotoxy(40,11);cout<< "* vinhar cada letra              *";
        gotoxy(40,12);cout<< "**********************************";
        gotoxy(40,13);system("pause");
    }
    else if(diff == 2){
        system("CLS");
        gotoxy(40,5);cout<< "***********INSTRUCOES*************";
        gotoxy(40,6);cout<< "*->Adivinhar a palavra, sabendo  *";
        gotoxy(40,7);cout<< "* o tema e o num de letras, se   *";
        gotoxy(40,8);cout<< "* vencer vai ser apresentada ou- *";
        gotoxy(40,9);cout<< "* tra palavra para continuar.    *";
        gotoxy(40,10);cout<< "* ATENCAO: Tens 15 seg para adi- *";
        gotoxy(40,11);cout<< "* vinhar cada letra              *";
        gotoxy(40,12);cout<< "**********************************";
        gotoxy(40,13);system("pause");
    }
    else if(diff == 3){
        system("CLS");
        gotoxy(40,5);cout<< "***********INSTRUCOES*************";
        gotoxy(40,6);cout<< "*->Adivinhar a palavra, sabendo  *";
        gotoxy(40,7);cout<< "* o tema e o num de letras, se   *";
        gotoxy(40,8);cout<< "* vencer vai ser apresentada ou- *";
        gotoxy(40,9);cout<< "* tra palavra para continuar.    *";
        gotoxy(40,10);cout<< "* ATENCAO: Tens 10 seg para adi- *";
        gotoxy(40,11);cout<< "* vinhar cada letra              *";
        gotoxy(40,12);cout<< "**********************************";
        gotoxy(40,13);system("pause");
    }

}


/**************************************************************************/
/*!
    @brief  Escolher aleatoriamente o tema e a palavra apartir de um .txt
    @param  None
    @return retorna como referencia o tema e a plavra
*/
/**************************************************************************/

void geraPalavraeTema(string& tema, string& palavra){
    // inicializa uma semente random
    srand (time(NULL));

    //open file
    ifstream palavras;
    palavras.open("palavras.txt");

    if (!palavras.is_open()) {
        cout << "Error opening file"<< endl;
    }

    //Sabemos que temos 24 palavras em palavras.txt em formato tema:palavra
    string listapalavras[24]; //strigs ja sao alocadas na memoria dinamica
    string palavraetema;
    //ler as palavras do ficheiro
    for(int i = 0; i<24; i++){
        palavras >> listapalavras[i];
    }
    //escolher um elemnto da tabela de strings ao calhas
    int random = rand() % 24;
    palavraetema = listapalavras[random];

    //separar palavra e tema e retornar como referencia(tema:palavra)
        int delim = palavraetema.find(":");
        //copiar a string apos delim para palavra
        palavra = palavraetema.substr(delim+1);
        //copiar a string ate delim para tema
        tema = palavraetema.substr(0,delim);

    //close file
    palavras.close();

    return;

}

//----------------------------------------------------------------------------
//METODOS---------------------------------------------------------------------
//-------------------------------------------------------------------------------

/**************************************************************************/
/*!
    @brief  Vai verificar o modo em que vai iniciar o jogo e inicia o jogo
    @param  None
    @return None
*/
/**************************************************************************/
int Jogo:: novoJogo(){
    //verficação do modo de jogo
    if(gamemode == 1){
        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startElementar(palavra_aux,tema_aux);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação:
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,5);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            }return pontuacao;
        }

        //escolher o tema , assegurando que o utilizador escolhe um tema correto
        string tema;
        tema.clear();
        do{
            system("CLS");
            gotoxy(40,5);cout<< "**************TEMA**************";
            gotoxy(40,6);cout<< "*  Animais                     *";
            gotoxy(40,7);cout<< "*  Cores                       *";
            gotoxy(40,8);cout<< "*  Frutas                      *";
            gotoxy(40,9);cout<< "********************************";
            gotoxy(40,11);cout<< "Introduza o tema: ";
            cin >> tema;
            //passar tudo para minusculas
            int n = tema.size();
            for(int i = 0; i < n; i++){
                tema[i] = tolower(tema[i]);
            }
        }while(tema != "animais" && tema != "cores" && tema != "frutas");

        //ir buscar a palavra
        string palavra = getPalavra(tema);

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startElementar(palavra, tema); //retorna a pontuacao

        //basta verificar o valor da pontuação: DEBUG
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            //gotoxy(40,9);system("pause");
        }

        //return pontuacao para guardar no backup
        return pontuacao;
    }

    else if(gamemode == 2){
        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startBasico(palavra_aux,tema_aux);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação: DEBUG
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
                //gotoxy(40,9);system("pause");
            }return pontuacao;
        }

        //gerar o tema e palavra aleatoriamente
        string palavra;
        string tema;
        geraPalavraeTema(tema, palavra);

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startBasico(palavra, tema); //retorna a pontuacao

        //basta verificar o valor da pontuação:debug
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,5);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            //gotoxy(40,7);system("pause");
        }

    }

    else if(gamemode == 3){
        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startMedio(palavra_aux,tema_aux);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação:
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,5);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            }return pontuacao;
        }

        //gerar o tema e palavra aleatoriamente
        string palavra;
        string tema;
        geraPalavraeTema(tema, palavra);

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startMedio(palavra, tema); //retorna a pontuacao

        //basta verificar o valor da pontuação:
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,5);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            //gotoxy(40,7);system("pause");
        }
    }
    return 0;//nunca vai acontecer
}



/**************************************************************************/
/*!
    @brief  SCORE BOARD
*/
/**************************************************************************/
void Jogador:: mostraOrdenaPorPontuacao(Jogador *p, int numElem, int vi[])const{
    // inicializa vetor de indices IMPORTANTE!
    for(int i=0; i<numElem; i++) vi[i]=i;

    // ordena vetor de índices por preco
    ordenaInsercaoPontuacao(p, numElem, vi);


    // mostra tabela pess (de Pessoas) ordenada por idade
    system("cls");
    char aux{};
    int i;
    do{
        gotoxy(40,5);cout<< "***********SCORE-BOARD**********";
        for(i=0; i<numElem-1; i++){
            gotoxy(40,6+i);cout <<"Nome: " << p[vi[i]].nome;
            cout <<"| Pontuacao: " << p[vi[i]].pontuacao << endl;
        }
        gotoxy(40,8+i);cout << "Press any key(and enter) to Exit -> ";
        cin >> aux;
    }while(aux==0);
}

/**************************************************************************/
/*!
    @brief  ordena o vetor de indices por ordem crescente de
    pontuacoes da tabela de jogadores
*/
/**************************************************************************/
void Jogador:: ordenaInsercaoPontuacao(Jogador *p, int numElem, int vi[])const{
    for(int i = 1; i < numElem; i++){
        int aux = vi[i]; // indice auxiliar
        int j;
        for(j = i; (j > 0) && (p[aux].pontuacao > p[vi[j-1]].pontuacao); j--){
            vi[j] = vi[j-1];
        }
        vi[j] = aux;
    }
}

/**************************************************************************/
/*!
    @brief  Funcao para ddebug
    @param  None
    @return None
*/
/**************************************************************************/

void Jogador:: mostraMemoria(Jogador p[] , int dim) const{
    //ccaso em que a memoria esta vazia
    if(dim == 0){
        cout << "Memoria vazia";
        return;
    }

    for (int i = 0; i < dim; i++){
        cout << "Jogadores[" << i << "] -> " << "nome: " <<  p[i].nome ;
        cout << "|pontuacao: " << p[i].pontuacao << "|gamemode: " << p[i].gamemode << "|dif: " << p[i].dif << "|pause: " << p[i].pausa;
        cout << endl;
    }
}


/**************************************************************************/
/*!
    @brief  Funçao que recebe um jogador_aux e guarda a informaçao
    pertinente no backup file assumimos que estamos numa linha vazia do file
    @param  None
    @return None
*/
/**************************************************************************/

void Jogo:: backup(Jogo tab[], int dim) const{

    //open ackup file stream
    ofstream backupfile;
    backupfile.open("backup.txt",ios::trunc);
    if ( !backupfile.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    //save info
    for(int i = 0; i<dim; i++){
        backupfile << tab[i].nome << " " << tab[i].pontuacao << " " << tab[i].gamemode<< " " << tab[i].dif << " " << tab[i].pausa;
        backupfile << "\n";
    }

    //close file
    backupfile.close();

    return;
}


/**************************************************************************/
/*!
    @brief  Funçao que pede ao jogador qual a dificuldade em que pretende jogar
    @param  None
    @return None
*/
/**************************************************************************/

void Jogo:: dificuldade(){
        int aux;
        do{
          system("CLS");
          gotoxy(40,5);cout<< "***********DIFICULDADE**********";
          gotoxy(40,6);cout<< "*  1.Facil                     *";
          gotoxy(40,7);cout<< "*  2.Media                     *";
          gotoxy(40,8);cout<< "*  3.Dificil                   *";
          gotoxy(40,9);cout<< "********************************";
          gotoxy(40,11);cout<< "Escolha: ";
          cin >> aux;
        }while(aux != 1 && aux != 2 && aux != 3);
        dif = aux;
}







