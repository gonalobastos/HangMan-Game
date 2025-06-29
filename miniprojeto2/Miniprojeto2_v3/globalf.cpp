
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
//#include <stdio.h>

using namespace std;


//Globais-----------------------------------------------------------------------



/****************************************************************************************************************************************************************************
 * Apresenta o menu e é o ponto de partida para todo o jogo
*/
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
            backupfile >> Jogadores[idx_jdr].nome >> Jogadores[idx_jdr].pontuacao >> Jogadores[idx_jdr].gamemode >> Jogadores[idx_jdr].dif >> Jogadores[idx_jdr].pausa >> Jogadores[idx_jdr].tentativas >> Jogadores[idx_jdr].palavra >> Jogadores[idx_jdr].tema >> Jogadores[idx_jdr].tapada_aux;
            idx_jdr++ ;//atualizar o jogador atual
        }
    }

    //close file
    backupfile.close();

    //assegurar que o utilizador introduz uma das opcoes
    string escolha;
    int sair_flag = 0;

    //variaveis auxiliares para a opcao 0 do menu
    string nome_aux;
    int i_aux;

    //variaveis auxiliares para a opcao 2 do menu
    int num_jogadores = 0;
    int iPorPontuacao[num_jogadores];//tabela de indices

    do{
        //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(idx_jdr != 0){
            cout << "idx_jdr = " <<idx_jdr << endl;
            mostraMemoria(Jogadores,idx_jdr);//com ficheiro vazio isto mostra um vazio
            system("pause");
        }
        //-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        do{
            system("CLS");
            gotoxy(40,5);cout<< "**************MENU**************";
            gotoxy(40,6);cout<< "*  0.Iniciar novo jogo.        *";
            gotoxy(40,7);cout<< "*  1.Modo de Funcionamento.    *";
            gotoxy(40,8);cout<< "*  2.Mostrar Pontuacoes.       *";
            gotoxy(40,9);cout<< "*  3.Sair.                     *";
            gotoxy(40,10);cout<< "*  4.Config Temas e Palavras.  *";
            gotoxy(40,11);cout<< "*  5.Suspender                 *";
            gotoxy(40,12);cout<< "*  6.Continuar                 *";
            gotoxy(40,13);cout<< "********************************";
            gotoxy(40,15);cout<< " Escolha: ";
            cin>> escolha;

        }while(escolha != "0" && escolha != "1" && escolha != "2" && escolha != "3" && escolha != "4" && escolha != "5" && escolha != "6");

        switch(stoi(escolha))
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
            gotoxy(40,10);cout << "* No caso de introduzir sobre- *";
            gotoxy(40,11);cout << "* nome separe com '_'          *";
            gotoxy(40,12);cout << "********************************";
            gotoxy(40,13);cout << "Nome: ";
            //Aceitar nome e sobrenome
            while(1){
                getline(cin, nome_aux);
                if(!nome_aux.empty()){
                    break;
                }
            }

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

                        //antes de tudo verificar se tem um jog em pausa(OU POR ACABR) - Se SIM saltar logo para novo jogo
                        if(Jogadores[i_aux].pausa == 1){
                            Jogadores[i_aux].novoJogo(Jogadores,idx_jdr,i_aux);
                            break;//voltar a apresentar o menu
                        }

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
                        Jogadores[i_aux].novoJogo(Jogadores,idx_jdr,i_aux);//VOUALTERAR AQUI 1


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
                        Jogadores[idx_jdr].novoJogo(Jogadores,idx_jdr,0);

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
                Jogadores[idx_jdr].novoJogo(Jogadores,idx_jdr,0);

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
            Jogadores[idx_jdr].backup(Jogadores,idx_jdr,idx_jdr); //passo idx_jdr no parametro ja jogou para guardar no save de novojogador
            break;

        case 2:
            //Score board
            num_jogadores = idx_jdr + 1;
            Jogadores->mostraOrdenaPorPontuacao(Jogadores, num_jogadores, iPorPontuacao);
            break;

        case 3:
        {
            //Sair
            //Suspender
            string nome_aux2;

            //Pedir para introduzir o nome de jogador=escolher o save
            system("cls");
            gotoxy(40,5);cout << "********************************";
            gotoxy(40,6);cout << "* Tem a certeza que deseja     *";
            gotoxy(40,7);cout << "* sair? Se ira deixar um jogo a*";
            gotoxy(40,8);cout << "* a meio introduza o seu nome. *";
            gotoxy(40,9);cout << "* No caso de introduzir sobre- *";
            gotoxy(40,10);cout << "* nome separe com '_'          *";
            gotoxy(40,11);cout << "********************************";
            gotoxy(40,12);cout << "Nome(0 para sair): ";
            //Aceitar nome e sobrenome
            while(1){
                getline(cin, nome_aux2);
                if(!nome_aux2.empty()){
                    break;
                }
            }
            if(nome_aux2.compare("0")==0){
                //sair
                sair_flag = 1;
                break;
            }
            else{
                //backup
                Jogadores[idx_jdr].nome = nome_aux2;
                Jogadores[idx_jdr].backup(Jogadores, idx_jdr, idx_jdr);
                //sair
                sair_flag = 1;
                break;
            }
        }

        case 4:
            configTemasPalavras();
            break;

        case 5:
        {
            //Suspender
            string nome_aux2;

            //Pedir para introduzir o nome de jogador=escolher o save
            system("cls");
            gotoxy(40,5);cout << "********************************";
            gotoxy(40,6);cout << "* Introduza o seu nome se pre- *";
            gotoxy(40,7);cout << "* tende Suspender.             *";
            gotoxy(40,8);cout << "* No caso de introduzir sobre- *";
            gotoxy(40,9);cout << "* nome separe com '_'          *";
            gotoxy(40,10);cout << "********************************";
            gotoxy(40,11);cout << "Nome(0 para cancelar): ";
            //Aceitar nome e sobrenome
            while(1){
                getline(cin, nome_aux2);
                if(!nome_aux2.empty()){
                    break;
                }
            }
            if(nome_aux2.compare("0")==0){
                //cancelar
                break;
            }
            else{
                Jogadores[idx_jdr].nome = nome_aux2;
                Jogadores[idx_jdr].backup(Jogadores, idx_jdr, idx_jdr);
                sair_flag = 1;
                break;
            }
        }


        case 6:
        {
            //continuar jogo

            string nome_aux2;

            //Pedir para introduzir o nome de jogador=escolher o save
            system("cls");
            gotoxy(40,5);cout << "********************************";
            gotoxy(40,6);cout << "* Introduza o seu nome se pre- *";
            gotoxy(40,7);cout << "* para continuar a jogar ou   *";
            gotoxy(40,8);cout << "* No caso de introduzir sobre- *";
            gotoxy(40,9);cout << "* nome separe com '_'          *";
            gotoxy(40,10);cout << "********************************";
            gotoxy(40,11);cout << "Nome: ";
            //Aceitar nome e sobrenome
            while(1){
                getline(cin, nome_aux2);
                if(!nome_aux2.empty()){
                    break;
                }
            }

            //verificar se ja existe na memoria um jogador com este nome
            i_aux = Jogadores->procuraNome(nome_aux2, Jogadores, idx_jdr); //i_aux recebe o indice de memoria do save do jogador
            if (i_aux >= 0)
            {
                //antes de tudo verificar se tem um jog em pausa(OU POR ACABR) - Se SIM saltar logo para novo jogo
                if(Jogadores[i_aux].pausa == 1){
                    Jogadores[i_aux].novoJogo(Jogadores,idx_jdr,i_aux);
                    break;//voltar a apresentar o menu
                }

                //perguntar se pretende alterar o modo
                char answer{};
                while(answer == 0){
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

                //perguntar se pretende configurar palavras e temas?
                char ans{};
                while(ans == 0)
                {
                    system("cls");
                    gotoxy(40,5);cout << "***********************************";
                    gotoxy(40,6);cout << "*Config Palavras e Temas?         *";
                    gotoxy(40,7);cout << "*                                 *";
                    gotoxy(40,8);cout << "***********************************";
                    gotoxy(40,9);cout << "*Escolha [S/N]: ";
                    cin >> ans;
                    if(ans == 'S' || ans =='s'){
                        configTemasPalavras();
                        break;
                    }else if(ans == 'N' || ans =='n'){
                        break;
                    }
                    else{
                        ans = 0;
                        system("cls");
                        gotoxy(40,5);cout << "Introduza uma opção valida! ";
                        continue;
                    }

                }

                //iniciar o jogo com esse save (ou jogador)
                Jogadores[i_aux].novoJogo(Jogadores,idx_jdr,i_aux);

            }
            //Se nao existir na memoria
            else{
                system("cls");
                gotoxy(40,5);cout << "Erro: Jogador não existente na memoria.";
                gotoxy(40,6);system("pause");
            }

            break;
        }
        default:
            break;
        }
    }while(sair_flag == 0);

    //memory desallocation
    delete[] Jogadores;

    return;
}

/****************************************************************************************************************************************************************************
 * Inicia o Jogo para um certo jogador(objeto) cujo indice na tabela de jogadores e na mem é passado como argumeto
*/

int Jogo:: novoJogo(Jogo tab[], int idx, int ja_jogou){
    int pontuacao_ant;

    //verficação do modo de jogo
    if(gamemode == 1){

        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startElementar(tab,idx,ja_jogou);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação:
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,5);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            }return pontuacao;
        }
        //se nao tiver jogo em pausa

        //guardar pontuacao anterior em variavel auxiliar
        pontuacao_ant = pontuacao;
        pontuacao = 0; //reset da pontuaco


        //escolher o tema , assegurando que o utilizador escolhe um tema correto
        //string tema;
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
        backup(tab,idx,ja_jogou); //backup tema

        //ir buscar a palavra
        palavra = getPalavraeSaidas(tema, gamemode);
        backup(tab,idx,ja_jogou);//backup palavra

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startElementar(tab,idx,ja_jogou); //retorna a pontuacao

        //Se a pontuacao conseguida for menor que a anterior, manter a maior
        if(pontuacao < pontuacao_ant){
            pontuacao = pontuacao_ant;
        }

        backup(tab,idx,ja_jogou);//backup pontuacao

        //basta verificar o valor da pontuação: DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            gotoxy(40,9);system("pause");
        }

        //return pontuacao para guardar no backup
        return pontuacao;
    }

    else if(gamemode == 2){

        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startBasico(tab,idx,ja_jogou);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação: DEBUG
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
                gotoxy(40,9);system("pause");
            }return pontuacao;
        }
        //se nao tiver jogo em pausa

        //guardar pontuacao anterior em variavel auxiliar
        pontuacao_ant = pontuacao;
        pontuacao = 0; //reset da pontuaco

        //gerar o tema e palavra aleatoriamente
        geraPalavraeTema(tema, palavra);
        backup(tab,idx,ja_jogou);//backup palavra e tema

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startBasico(tab,idx,ja_jogou); //retorna a pontuacao

        //Se a pontuacao conseguida for menor que a anterior, manter a maior
        if(pontuacao < pontuacao_ant){
            pontuacao = pontuacao_ant;
        }

        backup(tab,idx,ja_jogou);//backup pontuacao

        //basta verificar o valor da pontuação:debug
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            gotoxy(40,9);system("pause");
        }

        return pontuacao;

    }

    else if(gamemode == 3){
        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startMedio(tab,idx,ja_jogou);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação:
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
                gotoxy(40,9);system("pause");
            }return pontuacao;
        }

        //guardar pontuacao anterior em variavel auxiliar
        pontuacao_ant = pontuacao;
        pontuacao = 0; //reset da pontuaco

        //gerar o tema e palavra aleatoriamente
        geraPalavraeTema(tema, palavra);
        backup(tab,idx,ja_jogou);//backup palavra e tema

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startMedio(tab,idx,ja_jogou); //retorna a pontuacao

        //Se a pontuacao conseguida for menor que a anterior, manter a maior
        if(pontuacao < pontuacao_ant){
            pontuacao = pontuacao_ant;
        }
        backup(tab,idx,ja_jogou);//backup pontuacao

        //basta verificar o valor da pontuação:
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            gotoxy(40,9);system("pause");
        }
    }

    else if(gamemode == 4){
        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startMedio(tab,idx,ja_jogou);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação:
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
                gotoxy(40,9);system("pause");
            }return pontuacao;
        }

        //guardar pontuacao anterior em variavel auxiliar
        pontuacao_ant = pontuacao;
        pontuacao = 0; //reset da pontuaco

        //Escolher o tema entre os predefenidos e os configurados-TO DO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        string temasTab[20];
        int numTemas = getTemas(temasTab);
        tema.clear();
        do{
            system("CLS");
            gotoxy(40,5);cout<< "**************TEMA**************";
            for(int i = 0; i < numTemas ; i++){
                gotoxy(42,6+i);cout << i << "." << temasTab[i];
            }
            gotoxy(40,5+numTemas+1);cout<< "********************************";
            gotoxy(40,5+numTemas+2);cout<< "Introduza o tema: ";
            cin >> tema;
            //passar tudo para minusculas
            int n = tema.size();
            for(int i = 0; i < n; i++){
                tema[i] = tolower(tema[i]);
            }
        }while(!temaExiste(tema, temasTab, numTemas));//tema != "animais" && tema != "cores" && tema != "frutas"
        backup(tab,idx,ja_jogou); //backup tema


        //Gerar palavra aleatoriamente
        palavra = getPalavraeSaidas(tema, gamemode);
        backup(tab,idx,ja_jogou);//backup palavra

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startMedio(tab,idx,ja_jogou); //retorna a pontuacao

        //Se a pontuacao conseguida for menor que a anterior, manter a maior
        if(pontuacao < pontuacao_ant){
            pontuacao = pontuacao_ant;
        }
        backup(tab,idx,ja_jogou);//backup pontuacao

        //basta verificar o valor da pontuação:
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            gotoxy(40,9);system("pause");
        }
    }

    else if(gamemode == 5){
        //antes de tudo verificar se tem um jogo a meio
        if(pausa == 1){
            //Acabar/Continuar o jogo e sair
            pontuacao = startMedio(tab,idx,ja_jogou);
            //reset da flag - so depois de sair do jogo pois precisamos de la
            pausa = 0;
            //basta verificar o valor da pontuação:
            if(pontuacao > 0){
                system("cls");
                //guardar o score do jogador na memoria - ja esta automaticamente
                gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
                gotoxy(40,9);system("pause");
            }return pontuacao;
        }

        //guardar pontuacao anterior em variavel auxiliar
        pontuacao_ant = pontuacao;
        pontuacao = 0; //reset da pontuaco

        //Escolher o tema entre os predefenidos e os configurados-TO DO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        string temasTab[20];
        int numTemas = getTemas(temasTab);
        tema.clear();
        do{
            system("CLS");
            gotoxy(40,5);cout<< "**************TEMA**************";
            for(int i = 0; i < numTemas ; i++){
                gotoxy(42,6+i);cout << i << "." << temasTab[i];
            }
            gotoxy(40,5+numTemas+1);cout<< "********************************";
            gotoxy(40,5+numTemas+2);cout<< "Introduza o tema: ";
            cin >> tema;
            //passar tudo para minusculas
            int n = tema.size();
            for(int i = 0; i < n; i++){
                tema[i] = tolower(tema[i]);
            }
        }while(!temaExiste(tema, temasTab, numTemas));//tema != "animais" && tema != "cores" && tema != "frutas"
        backup(tab,idx,ja_jogou); //backup tema


        //Gerar palavra com Base nas especificacoes do modo 5
        palavra = getPalavraeSaidas(tema, gamemode);
        backup(tab,idx,ja_jogou);//backup palavra

        //iniciar o jogo com aquela palavra e tema
        pontuacao = startMedio(tab,idx,ja_jogou); //retorna a pontuacao

        //Se a pontuacao conseguida for menor que a anterior, manter a maior
        if(pontuacao < pontuacao_ant){
            pontuacao = pontuacao_ant;
        }
        backup(tab,idx,ja_jogou);//backup pontuacao

        //basta verificar o valor da pontuação:
        if(pontuacao > 0){
            system("cls");
            //guardar o score do jogador na memoria - ja esta automaticamente
            gotoxy(40,7);cout<< "Acomulou um SCORE: "<<pontuacao <<endl;
            gotoxy(40,9);system("pause");
        }
    }

    return 0;//nunca vai acontecer
}


/****************************************************************************************************************************************************************************
 * guarda a tabela dejogadores no ficheiro
*/
void Jogo:: backup(Jogo tab[], int idx, int ja_jogou) const{
    int dim = idx+1;

    //update tab
    if(ja_jogou == 0){
        tab[idx].nome = nome;
        tab[idx].pontuacao = pontuacao;
        tab[idx].gamemode = gamemode;
        tab[idx].dif = dif;
        tab[idx].pausa = pausa;
        tab[idx].tentativas = tentativas;
        tab[idx].palavra = palavra;
        tab[idx].tema = tema;
        tab[idx].tapada_aux = tapada_aux;
    }
    else{
        tab[ja_jogou].nome = nome;
        tab[ja_jogou].pontuacao = pontuacao;
        tab[ja_jogou].gamemode = gamemode;
        tab[ja_jogou].dif = dif;
        tab[ja_jogou].pausa = pausa;
        tab[ja_jogou].tentativas = tentativas;
        tab[ja_jogou].palavra = palavra;
        tab[ja_jogou].tema = tema;
        tab[ja_jogou].tapada_aux = tapada_aux;
    }

    //open ackup file stream
    ofstream backupfile;
    backupfile.open("backup.txt",ios::trunc);
    if ( !backupfile.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    //save info
    for(int i = 0; i<dim; i++){
        backupfile << tab[i].nome << " " << tab[i].pontuacao << " " << tab[i].gamemode<< " " << tab[i].dif << " " << tab[i].pausa<< " " << tab[i].tentativas << " ";
        backupfile << tab[i].palavra << " " << tab[i].tema << " " << tab[i].tapada_aux;
        //so meto \n se nao for o ultima linha que passo para o file
        if(i != dim-1)
            backupfile << "\n";
    }

    //close file
    backupfile.close();

    return;
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

    //por causa do modo 5 - temo de ignorar as vezes saidas da palavra
    int tabsaidas[30];


    //open file
    string escolha = tema + ".txt";
    ifstream palavras;
    palavras.open(escolha); //escolha - tema.txt
    if (!palavras.is_open()) {
        cout << "Error opening file"<< endl;
        system("pause");
    }

    //Sabemos que temos 8 palavras em tema.txt
    string listapalavras[30]; //max num de palavras = 30
    string palavra;
    //ler as palavras do ficheiro
    int i = 0;
    while(palavras.peek() != EOF){
        palavras >> listapalavras[i] >> tabsaidas[i];
        i++;
        //cout << listapalavras[i]; system("pause");
    }

    //escolher um elemnto da tabela de strings ao calhas
    int random = rand() %i;//0-i
    palavra = listapalavras[random];//TEMOS A PALAVRA

    //close file
    palavras.close();

    return(palavra);
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

void mostraMemoria(Jogador p[] , int dim){
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


/****************************************************************************************************************************************************************************
 * Posiciona o cursor onde e necessario
*/
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

/****************************************************************************************************************************************************************************
 * Printa a capa do jogo
*/
void abertura(){
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
        gotoxy(40,17);cout << "* Universidade de Coimbra            *";
        gotoxy(40,18);cout << "* Data: 25/04/2021                   *";
        gotoxy(40,19);cout << "**************************************";
        gotoxy(40,21);cout << "Press any key(and enter) to Start -> ";
        cin >> aux;
    }while(aux == 0);

    return;//return to main
}


/*****************************************************************************************************************************************************************************
 *  @brief  Desenha a Forca dependendo da tentativa
*/

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



/*****************************************************************************************************************************************************************************
 * printa as instrucoes do mod basico e medio
 */
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

/******************************************************************************************************************************************************************************
 * printa as instrucoes do mod elementar
 */

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

void printTab(string tab[], int dim){
    for(int i = 0; i<dim; i++)
        cout << "tab[" << i << "] : " << tab[i] << endl;
}

