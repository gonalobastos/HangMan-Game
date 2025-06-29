#ifndef JOGO_FORCA_H
#define JOGO_FORCA_H

#include <iostream>
#include <string>
#include <ctime>

#define MAX_JOGADORES 100


using namespace std;

//classe com os objetos
class Jogo{
    //ESTES MEMBROS SAO VISIVEIS PELAS CLASSES DERIVADAS
    private:
        double Score_Elementar = 1.5;
        double Score_Basico_Medio = 3.5;
        string palavra_aux; //para guardar a palavra em caso de pausa
        string tema_aux;    //para guardar o tema em caso de paussa
        string tapada_aux;    //para guardar a tapada em caso de paussa
    public:
        string nome;
        int pontuacao = 0; //por defeito
        int tentativas = 9;  //tentativas possiveis por defeito
        int gamemode = 1; //por defeito
        int dif;
        int pausa = 0;
    public:
        //Metodos
        int novoJogo();
        void modos();
        void backup(Jogo tab[], int dim) const;
        void dificuldade();
        //modos de jogo
        int startElementar(string palavra, string tema);
        int startMedio(string palavra, string tema);
        int startBasico(string palavra, string tema);
        int score();
};

class Jogador: public Jogo{
    public:
        //Metodos
        void mostraOrdenaPorPontuacao(Jogador *p, int numElem, int vi[])const;
        void ordenaInsercaoPontuacao(Jogador *p, int numElem, int vi[])const;
        void mostraMemoria(Jogador p[] , int dim)const;
        int procuraNome(string nome, Jogador p[], int idx_jdr)const;

};


//Global Functions
void gotoxy(int x, int y);
void abertura();
void menu();
void desenha(int tentativas);
string getPalavra(string tema);
void geraPalavraeTema(string& tema, string& palavra);
void instrucoes_elementar(void);
void instrucoes_basico_medio(int diff);


#endif // JOGO_FORCA_H
