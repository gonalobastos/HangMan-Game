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
        double Score_Elementar = 1.0;
        double Score_Basico_Medio = 2.0;
    public:
        string nome = "empty";
        int pontuacao = 0; //por defeito
        int tentativas = 9;  //tentativas possiveis por defeito
        int gamemode = 1; //por defeito
        int dif = 1;
        int pausa = 0;
        string tema = "empty";
        string palavra = "empty";
        string tapada_aux = "empty";    //para guardar a tapada em caso de pauss
    public:
        //Metodos
        int novoJogo(Jogo tab[], int idx, int ja_jogou);//idx e o indice de memoria do jogador passado ao metodo
        void modos();
        void backup(Jogo tab[], int dim, int ja_jogou) const;
        void dificuldade();
        //modos de jogo
        int startElementar(Jogo tab[], int idx, int ja_jogou);//idx e o indice de memoria do jogador passado ao metodo
        int startMedio(Jogo tab[], int idx, int ja_jogou);
        int startBasico(Jogo tab[], int idx, int ja_jogou);
        int score();
};

class Jogador: public Jogo{
    public:
        //Metodos
        void mostraOrdenaPorPontuacao(Jogador *p, int numElem, int vi[])const;
        void ordenaInsercaoPontuacao(Jogador *p, int numElem, int vi[])const;
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
void mostraMemoria(Jogador p[] , int dim);

//Opção 5 do menu e Modo avançado- nivel2.cpp
void configTemasPalavras();
void apagarFicheiro(string fileName, string tema, string temasTab[], int numTemas);
void modifica(void);//nao precisa receber tabela de temas
bool removepalavra(string tab[],int saidasTab[], int dim);
void configTemas(string temasTab[], int &dim);
void configPalavras();

int getTemas(string temasTab[]);//to do
void putTemas(string temasTab[], int numTemas);
bool temaExiste(string tema, string tab[], int dim);

//modo de  jogo profissional
string getPalavraeSaidas(string tema, int mode);
int randomidx(int saidasTab[], int dim);

//Debug
void printTab(string tab[], int dim);


#endif // JOGO_FORCA_H
