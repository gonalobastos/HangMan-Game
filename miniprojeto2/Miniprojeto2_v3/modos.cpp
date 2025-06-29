#include "jogo_forca.h"
#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <ctype.h>

using namespace std;

//Escolher modo
void Jogo:: modos(){
    string escolha;
    do{
      system("CLS");
      gotoxy(40,5);cout<< "***********MENU-MODOS***********";
      gotoxy(40,6);cout<< "*  1.Elementar                 *";
      gotoxy(40,7);cout<< "*  2.Basico                    *";
      gotoxy(40,8);cout<< "*  3.Medio                     *";
      gotoxy(40,9);cout<< "*  4.Avancado                  *";
      gotoxy(40,10);cout<< "*  5.Profissional              *";
      gotoxy(40,11);cout<< "********************************";
      gotoxy(40,12);cout<< "Escolha: ";
      cin >> escolha;
    }while(escolha != "0" && escolha != "1" && escolha != "2" && escolha != "3" && escolha != "4" && escolha != "5");
    gamemode = stoi(escolha);
}


//ELEMENTAR-------------------------------------------------------------------------------------
int Jogo:: startElementar(Jogo tab[], int idx, int ja_jogou){
    //Variaveis de jogo
    char palpite;
    bool correto = false;
    string aux;

    //plaavra misterio
    int tam = palavra.size();//cout << "Tema->"<< tema << "Palavra->" << palavra << endl;//DEBUG
    string tapada(tam, '*');
    if(pausa == 1){
        tapada = tapada_aux;
    }
    else{
        //Não acontece nada
    }

    //Apresentar as Regras
    instrucoes_elementar();

    //GAME LOOP
    do{
        //save to backup
        backup(tab,idx,ja_jogou);

        //reset flags
        correto = false;
        pausa = 1;

        //desenhar a forca
        system("CLS");
        //mas antes verifica se é a ultima tentativa- se sim faz break do loop
        if(tentativas==0){
            desenha(tentativas);
            gotoxy(40,15);system("pause");
            break;
        }
        desenha(tentativas);
        cout << endl;

        //printar info sobre a palavra a descobrir
        gotoxy(40,14);cout << "Tema: " << tema << endl;
        gotoxy(40,15);cout << "Palavra a descobrir:" << tapada << endl;
        gotoxy(40,16);cout << "Tentativas restantes: " << tentativas << endl;

        //pedir palpite
        gotoxy(40,18);cout << "Palpite('0'para Menu-Pausa): ";
        cin >> palpite;cout << endl;

        //verificar se quer aceder o menu de pausa
        if (palpite == '0'){
            //open mini menu
            do{
                system("CLS");
                gotoxy(40,5);cout<< "***********MENU-PAUSA***********";
                gotoxy(40,6);cout<< "*  0.Sair                      *";
                gotoxy(40,7);cout<< "*  1.Pausar(Suspender)         *";
                gotoxy(40,8);cout<< "*  2.Continuar                 *";
                gotoxy(40,9);cout<< "********************************";
                gotoxy(40,11);cout<< "Escolha: ";
                cin >> aux;
            }while(aux != "0" && aux != "1" && aux !="2");
            switch(stoi(aux)){
                case 0:
                    //Sair
                    //reset das tentativas
                    tentativas = 9;
                    return pontuacao;
                break;
                case 1:
                    //set da flag
                    pausa = 1;
                    //guardar a palavra e o tema a tapada
                    tapada_aux = tapada;
                    //palavra e tema ja estao guardados pois sao elementos da classe
                    // e as tentativas? Nao fazemos reset para continuar com as mesmas
                    return pontuacao; //a pontuaçao tambem se mantem
                break;
                case 2:
                    //nao faz nada so volta
                break;
            default:
                    return 0;
            }
        }

        //verificar se palpite esta correto
        for(int i = 0; i<tam; i++){
            if(palavra[i] == palpite){
                //mostrar letra da palavra
                tapada[i] = palpite;
                tapada_aux = tapada;
                correto = true;
            }
        }
        if(correto == false && palpite != '0'){
            //decrementar tentativas
            tentativas-- ;
        }
        //verificar se venceu
        if(palavra == tapada){
            //limpar o ecra
            system("cls");
            gotoxy(40,5);cout<< "Acertou!\n";
            gotoxy(40,7);system("pause");

            //calculo da pontuaçao - esta classe tem acesso a pontuacao de jogador
            pontuacao = pontuacao + score();

            //reset das tentativas
            tentativas = 9;

            //escolher outra palavra
            palavra = getPalavra(tema);
            tam = palavra.size();//cout << "Tema->"<< tema << "Palavra->" << palavra << endl;//DEBUG

            //tapar a palavra
            tapada.clear();
            string tapada_aux1(tam, '*');
            tapada.insert(0,tapada_aux1);

            //voltar a jogar - volta ao loop (pois fizemos reset nas tentativas)
        }

    }while(tentativas >= 0);

    pausa = 0; //fica a 1 durante o jogo para caso o progrma encerre desta forma garante que nao perde o progresso

    //Quando ficar sem tentativas significa que perdeu o jogo
    //vai retornar para novoJogo
    //mas antes fazer reset das tentativas, para jogos futuros
    tentativas = 9;

    //save to backup
    backup(tab,idx,ja_jogou);

    return pontuacao;
}

//BASICO----------------------------------------------------------------------------------------
int Jogo:: startBasico(Jogo tab[], int idx, int ja_jogou){

    //Variaveis de jogo
    char palpite;
    bool correto = false;
    int aux;
    bool letraInserida = false;

    //defenir o tempo para adivinhar cada letra
    int endTime;
    switch(dif){
    case 1:
        //Facil
        endTime = clock()+20000;//20 seg
        break;
    case 2:
        //Facil
        endTime = clock()+15000;//15 seg
        break;
    case 3:
        //Facil
        endTime = clock()+10000;//10 seg
        break;
    }

    //plaavra misterio
    int tam = palavra.size();//cout << "Tema->"<< tema << "Palavra->" << palavra << endl;//DEBUG
    string tapada(tam, '*');
    if(pausa == 1){
        tapada = tapada_aux;
    }
    else{
        //Não acontece nada
    }

    //Apresentar as Regras
    instrucoes_basico_medio(dif);

    //GAME LOOP
    do{
        //save to backup
        backup(tab,idx,ja_jogou);

        //reset flags
        correto = false;
        letraInserida = false;
        pausa = 1;

        //repor o tempo para adivinhar a proxima letra
        switch(dif){
        case 1:
            //Facil
            endTime = clock()+20000;//20 seg
            break;
        case 2:
            //Facil
            endTime = clock()+15000;//15 seg
            break;
        case 3:
            //Facil
            endTime = clock()+10000;//10 seg
            break;
        }

        //desenhar a forca
        system("CLS");
        //mas antes verifica se é a ultima tentativa- se sim faz break do loop
        if(tentativas==0){
            desenha(tentativas);
            gotoxy(40,15);system("pause");
            break;
        }
        desenha(tentativas);
        cout << endl;

        //printar info sobre a palavra a descobrir
        gotoxy(40,14);cout << "Tema: " << tema << endl;
        gotoxy(40,15);cout << "Palavra a descobrir:" << tapada << endl;
        gotoxy(40,16);cout << "Tentativas restantes: " << tentativas << endl;

        //pedir palpite
        gotoxy(40,18);cout << "Palpite('0'para Menu-Pausa): ";
        while( !letraInserida && clock() < endTime){
            //printar info sobre a palavra a descobrir
            //system("cls");  - nao posso usar
            gotoxy(40,14);cout << "Tema: " << tema << endl;
            gotoxy(40,15);cout << "Palavra a descobrir:" << tapada << endl;
            gotoxy(40,16);cout << "Tentativas restantes: " << tentativas << endl;

            //pedir palpite
            gotoxy(40,18);cout << "Palpite('0'para Menu-Pausa): ";
            cin >> palpite;
            //verificar se quer aceder o menu de pausa
            if (palpite == '0'){
                //open mini menu
                do{
                    system("CLS");
                    gotoxy(40,5);cout<< "***********MENU-PAUSA***********";
                    gotoxy(40,6);cout<< "*  0.Sair                      *";
                    gotoxy(40,7);cout<< "*  1.Pausar(Suspender)         *";
                    gotoxy(40,8);cout<< "*  2.Continuar                 *";
                    gotoxy(40,9);cout<< "********************************";
                    gotoxy(40,11);cout<< "Escolha: ";
                    cin >> aux;
                }while(aux != 0 && aux != 1 && aux != 2);
                switch(aux){
                    case 0:
                        //Sair
                        //reset das tentativas
                        tentativas = 9;
                        return pontuacao;
                    break;
                    case 1:
                        //set da flag
                        pausa = 1;
                        //guardar a palavra e o tema a tapada
                        tapada_aux = tapada;
                        // e as tentativas? Nao fazemos reset para continuar com as mesmas
                        return pontuacao; //a pontuaçao tambem se mantem
                    break;
                    case 2:
                        //nao faz nada so volta
                    break;
                default:
                        return 0;
                }
            }
            if( clock() < endTime && isalpha((int)palpite))
                letraInserida = true;
        }

        //verificar que introduzio o palpite a tempo
        if(!letraInserida && palpite != '0'){
            system("cls");
            gotoxy(49,14);cout << "-> ACABOU O TEMPO <-";
            tentativas = 0;
            desenha(tentativas);
            gotoxy(40,15);system("pause");
            return pontuacao;
        }

        //verificar se palpite esta correto
        for(int i = 0; i<tam; i++){
            if(palavra[i] == palpite){
                //mostrar letra da palavra
                tapada[i] = palpite;
                correto = true;
            }
        }
        if(correto == false && palpite != '0'){
            //decrementar tentativas
            tentativas-- ;
        }

        //verificar se venceu
        if(palavra == tapada){
            //limpar o ecra
            system("cls");
            gotoxy(40,5);cout<< "Acertou!\n";
            gotoxy(40,7);system("pause");

            //calculo da pontuaçao - esta classe tem acesso a pontuacao de jogador
            pontuacao = pontuacao + score();

            //reset das tentativas
            tentativas = 9;

            //escolher outra palavra
            palavra = getPalavra(tema);
            tam = palavra.size();//cout << "Tema->"<< tema << "Palavra->" << palavra << endl;//DEBUG

            //tapar a palavra
            tapada.clear();
            string tapada_aux(tam, '*');
            tapada.insert(0,tapada_aux);

            //voltar a jogar - volta ao loop (pois fizemos reset nas tentativas)
        }

    }while(tentativas >= 0);

    pausa = 0; //fica a 1 durante o jogo para caso o progrma encerre desta forma garante que nao perde o progresso

    //Quando ficar sem tentativas significa que perdeu o jogo
    //vai retornar para novoJogo
    //mas antes fazer reset das tentativas, para jogos futuros
    tentativas = 9;

    //save to backup
    backup(tab,idx,ja_jogou);

    return pontuacao;
}

//MEDIO-------------------------------------------------------------------------------------------------
int Jogo:: startMedio(Jogo tab[], int idx, int ja_jogou){

    //Variaveis de jogo
    char palpite;
    bool correto = false;
    int aux;
    bool letraInserida = false;
    string erradas;

    //defenir o tempo para adivinhar cada letra
    int endTime;
    switch(dif){
    case 1:
        //Facil
        endTime = clock()+20000;//20 seg
        break;
    case 2:
        //Facil
        endTime = clock()+15000;//15 seg
        break;
    case 3:
        //Facil
        endTime = clock()+10000;//10 seg
        break;
    }

    //plaavra misterio
    int tam = palavra.size();//cout << "Tema->"<< tema << "Palavra->" << palavra << endl;//DEBUG
    string tapada(tam, '*');
    if(pausa == 1){
        tapada = tapada_aux;
    }
    else{
        //Não acontece nada
    }

    //Apresentar as Regras
    instrucoes_basico_medio(dif);

    //GAME LOOP
    do{
        //save to backup
        backup(tab,idx,ja_jogou);

        //reset flags
        correto = false;
        letraInserida = false;
        pausa=1;

        //repor o tempo para adivinhar a proxima letra
        switch(dif){
        case 1:
            //Facil
            endTime = clock()+20000;//20 seg
            break;
        case 2:
            //Facil
            endTime = clock()+15000;//15 seg
            break;
        case 3:
            //Facil
            endTime = clock()+10000;//10 seg
            break;
        }

        //desenhar a forca
        system("CLS");
        //mas antes verifica se é a ultima tentativa- se sim faz break do loop
        if(tentativas==0){
            desenha(tentativas);
            gotoxy(40,15);system("pause");
            break;
        }
        desenha(tentativas);
        cout << endl;

        //printar info sobre a palavra a descobrir
        gotoxy(40,14);cout << "Tema: " << tema << endl;
        gotoxy(40,15);cout << "Palavra a descobrir:" << tapada << endl;
        gotoxy(40,16);cout << "Tentativas restantes: " << tentativas << endl;
        gotoxy(40,17);cout << "Letras erradas: " << erradas << endl;

        //pedir palpite
        gotoxy(40,19);cout << "Palpite('0'para Menu-Pausa): ";
        while( !letraInserida && clock() < endTime){
            //printar info sobre a palavra a descobrir
            //system("cls");
            gotoxy(40,14);cout << "Tema: " << tema << endl;
            gotoxy(40,15);cout << "Palavra a descobrir:" << tapada << endl;
            gotoxy(40,16);cout << "Tentativas restantes: " << tentativas << endl;
            gotoxy(40,17);cout << "Letras erradas: " << erradas << endl;

            //pedir palpite
            gotoxy(40,19);cout << "Palpite('0'para Menu-Pausa): ";
            cin >> palpite;
            //verificar se quer aceder o menu de pausa
            if (palpite == '0'){
                //open mini menu
                do{
                    system("CLS");
                    gotoxy(40,5);cout<< "***********MENU-PAUSA***********";
                    gotoxy(40,6);cout<< "*  0.Sair                      *";
                    gotoxy(40,7);cout<< "*  1.Pausar(Suspender)         *";
                    gotoxy(40,8);cout<< "*  2.Continuar                 *";
                    gotoxy(40,9);cout<< "********************************";
                    gotoxy(40,11);cout<< "Escolha: ";
                    cin >> aux;
                }while(aux != 0 && aux != 1 && aux != 2);
                switch(aux){
                    case 0:
                        //Sair
                        //reset das tentativas
                        tentativas = 9;
                        return pontuacao;
                    break;
                    case 1:
                        //set da flag
                        pausa = 1;
                        //guardar a palavra e o tema a tapada
                        tapada_aux = tapada;
                        // e as tentativas? Nao fazemos reset para continuar com as mesmas
                        return pontuacao; //a pontuaçao tambem se mantem
                    break;
                    case 2:
                        //nao faz nada so volta
                    break;
                default:
                        return 0;
                }
            }
            if( clock() < endTime && isalpha((int)palpite))
                letraInserida = true;
        }
        cout << endl;

        //verificar que introduzio o palpite a tempo
        if(!letraInserida && palpite != '0'){
            system("cls");
            gotoxy(49,14);cout << "-> ACABOU O TEMPO <-";
            tentativas = 0;
            desenha(tentativas);
            gotoxy(40,15);system("pause");
            return pontuacao;
        }

        //verificar se palpite esta correto
        for(int i = 0; i<tam; i++){
            if(palavra[i] == palpite){
                //mostrar letra da palavra
                tapada[i] = palpite;
                correto = true;
            }
        }
        if(correto == false && palpite != '0'){
            //decrementar tentativas
            tentativas-- ;
            //Se nao for repetido alterar a string de tentativas erradas
            if(erradas.find(palpite) != std::string::npos){
                //do nothing
            }else{
                erradas = erradas + palpite;
            }
        }

        //verificar se venceu
        if(palavra == tapada){
            //limpar o ecra
            system("cls");
            gotoxy(40,5);cout<< "Acertou!\n";
            gotoxy(40,7);system("pause");

            //calculo da pontuaçao - esta classe tem acesso a pontuacao de jogador
            pontuacao = pontuacao + score();

            //reset das tentativas
            tentativas = 9;

            //reset de erradas
            erradas.clear();

            //escolher outra palavra
            palavra = getPalavra(tema);
            tam = palavra.size();//cout << "Tema->"<< tema << "Palavra->" << palavra << endl;//DEBUG

            //tapar a palavra
            tapada.clear();
            string tapada_aux(tam, '*');
            tapada.insert(0,tapada_aux);

            //voltar a jogar - volta ao loop (pois fizemos reset nas tentativas)
        }

    }while(tentativas >= 0);
    pausa = 0; //fica a 1 durante o jogo para caso o progrma encerre desta forma garante que nao perde o progresso

    //Quando ficar sem tentativas significa que perdeu o jogo
    //vai retornar para novoJogo
    //mas antes fazer reset das tentativas, para jogos futuros
    tentativas = 9;

    //save to backup
    backup(tab,idx,ja_jogou);

    return pontuacao;
}

//-----------------------------------------------------------------------------------
int Jogo:: score(){
    double pontos = 0;

    if(tentativas != 0)
    {
        switch(gamemode)
        {
        case 1:
            pontos = Score_Elementar*tentativas;
            break;
        case 2:
            pontos = Score_Basico_Medio*tentativas*dif;
            break;
        case 3:
            pontos = Score_Basico_Medio*tentativas*dif;
            break;
        case 4:
            pontos = Score_Basico_Medio*tentativas*dif;
            break;
        case 5:
            pontos = Score_Basico_Medio*tentativas*dif;
            break;
        }
    }

    pontuacao = pontuacao + pontos;
    return pontuacao;
}











