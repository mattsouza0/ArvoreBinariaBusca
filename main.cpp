#include <QCoreApplication>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class ArvoreBinariaBusca
{
private:
    int chave;
    ArvoreBinariaBusca* pai;
    ArvoreBinariaBusca* filhoDireita;
    ArvoreBinariaBusca* filhoEsquerda;
public:
    ArvoreBinariaBusca(){
        pai = filhoEsquerda = filhoDireita = nullptr;
        chave = 0;
    }

    ArvoreBinariaBusca(int chave){
        this->chave=chave;
        pai = filhoEsquerda = filhoDireita = nullptr;
    }

    ~ArvoreBinariaBusca(){
        if(filhoEsquerda != nullptr)
            delete filhoEsquerda;
        if(filhoDireita != nullptr)
            delete filhoDireita;
        if(pai != nullptr)
            delete pai;
    }

    void setPai(ArvoreBinariaBusca* pai){
        this->pai=pai;
    }

    ArvoreBinariaBusca* getPai(){
        return pai;
    }

    void setFilhoEsquerda(ArvoreBinariaBusca* filhoEsquerda){
        this->filhoEsquerda = filhoEsquerda;
    }

    ArvoreBinariaBusca* getFilhoEsquerda(){
        return filhoEsquerda;
    }

    void setFilhoDireita(ArvoreBinariaBusca* filhoDireita){
        this->filhoDireita = filhoDireita;
    }

    ArvoreBinariaBusca* getFilhoDireita(){
        return filhoDireita;
    }

    void setChave(int chave){
        this->chave = chave;
    }

    int getChave(){
        return chave;
    }

    void inserir(ArvoreBinariaBusca* novo){
        if(novo->getChave() < this->chave){
            if(filhoEsquerda == nullptr){
                filhoEsquerda = novo;
            }else{
                filhoEsquerda->inserir(novo);
            }
        }else{
            if(filhoDireita == nullptr){
                filhoDireita = novo;
            }else{
                filhoDireita->inserir(novo);
            }
        }
    } 

    void remover(ArvoreBinariaBusca* chv){
        ArvoreBinariaBusca* y = nullptr;
        if(chv->filhoEsquerda == nullptr){
            transplant(chv,chv->filhoDireita);
        }else if (chv->filhoDireita == nullptr) {
            transplant(chv,chv->filhoEsquerda);
        }else{
            y = minimo(chv->filhoDireita);
        }
        if(y->pai != chv){
            transplant(y,y->filhoDireita);
            y->filhoDireita = chv->filhoDireita;
            y->filhoDireita->pai = y;
        }
        transplant(chv,y);
        y->filhoEsquerda = chv->filhoEsquerda;
        y->filhoEsquerda->pai = y;
    }

    void transplant(ArvoreBinariaBusca* no1,ArvoreBinariaBusca* no2){//substituir a subarvore no no1 pela subarvore no no2
        if(no1 == no1->pai->filhoEsquerda){
            no1->pai->filhoEsquerda = no2;
        }else{
            no1->pai->filhoDireita = no2;
        }
        if(no2 != nullptr){
            no2->pai = no1->pai;
        }
    }

    bool busca(ArvoreBinariaBusca* no, int ch){
        while(no != nullptr && ch != no->chave){
            if(ch < no->chave){
                no = no->filhoEsquerda;
            }else{
                no = no->filhoDireita;
            }
        }
        if(no == nullptr)
            return false;
        return true;
    }

    ArvoreBinariaBusca* minimo(ArvoreBinariaBusca* no){//consulta na arvore q retorna um ponteiro para o elemento no com a menor chave
        while (no->filhoEsquerda != nullptr) {
            no = no->filhoEsquerda;
        }
        return no;
    }

    ArvoreBinariaBusca* maximo(ArvoreBinariaBusca* no){//consulta na arvore q retorna um ponteiro para o elemento no com a maior chave
        while (no->filhoDireita != nullptr) {
            no = no->filhoDireita;
        }
        return no;
    }

    ArvoreBinariaBusca* sucessor(ArvoreBinariaBusca* x){//consulta q retorna um ponteiro para o maior elemento
        ArvoreBinariaBusca* y;
        if(x->filhoDireita != nullptr){
            return minimo(x->filhoDireita);
        }
        y = x->pai;
        while (y != nullptr && x == y->filhoDireita) {
            x = y;
            y = y->pai;
        }
        return y;
    }

    ArvoreBinariaBusca* predecessor(ArvoreBinariaBusca* x){
        ArvoreBinariaBusca* y;
        if(x->filhoEsquerda != nullptr){
            return maximo(x->filhoEsquerda);
        }
        y = x->pai;
        while (y != nullptr && x == y->filhoEsquerda) {
            x = y;
            y = y->pai;
        }
        return y;
    }

    /*
    string inOrdem(){
        std::stringstream co;
        if(filhoEsquerda != nullptr)
            co<<filhoEsquerda->inOrdem();
        co<<chave<<" | ";
        if(filhoDireita != nullptr)
            co<<filhoDireita->inOrdem();
        return co.str();
    }
    */

    void inOrdem(ArvoreBinariaBusca* no){//esquerda - raiz - direita
        if(no->filhoEsquerda != nullptr){
            inOrdem(no->filhoEsquerda);
        }
        cout<<no->getChave()<<" | ";
        if(no->filhoDireita != nullptr){
            inOrdem(no->filhoDireita);
        }
    }

    void preOrdem(ArvoreBinariaBusca* no){//raiz - esquerda - direita
        cout<<no->getChave()<<" | ";
        if(no->filhoEsquerda != nullptr){
            preOrdem(no->filhoEsquerda);
        }
        if(no->filhoDireita != nullptr){
            preOrdem(no->filhoDireita);
        }
    }

    void posOrdem(ArvoreBinariaBusca* no){//esquerda - direita - raiz
        if(no->filhoEsquerda != nullptr){
            posOrdem(no->filhoEsquerda);
        }
        if(no->filhoDireita != nullptr){
            posOrdem(no->filhoDireita);
        }
        cout<<no->getChave()<<" | ";
    }
};

int menu(){
    int op;
    cout<<"Escolha uma das opcoes abaixo: "<<endl;
    cout<<"1 - Inserir"<<endl;
    cout<<"2 - Remover"<<endl;
    cout<<"3 - Consulta Ordem"<<endl;
    cout<<"4 - Consulta Pre Ordem"<<endl;
    cout<<"5 - Consulta Pos Ordem"<<endl;
    cout<<"6 - Buscar Chave"<<endl;
    cout<<"0 - Sair"<<endl;
    cout<<"--> ";
    cin>>op;
    return op;
}

int main(){
    ArvoreBinariaBusca *arvore=nullptr, *novo, print;
    int chave,op=menu();
    while(op!=0){
        switch (op)
        {
        case 1:
            try {
            cout<<"\nDigite um numero para inserir na arvore: "<<endl;
            cin>>chave;
            cout<<endl;
            novo = new ArvoreBinariaBusca(chave);
            if(arvore == nullptr){
                arvore = novo;
            }else{
                arvore->inserir(novo);
            }
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 2:
            try {
            cout<<"\nInforme um numero para remover da arvore: ";
            cin>>chave;
            cout<<endl;
            //
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 3:
            try {
            cout<<"Percurso In Ordem: ";
            print.inOrdem(arvore);
            cout<<"\n"<<endl;
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 4:
            try {
            cout<<"Percurso Pre Ordem: ";
            print.preOrdem(arvore);
            cout<<"\n"<<endl;
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 5:
            try {
            cout<<"Percurso Pos Ordem: ";
            print.posOrdem(arvore);
            cout<<"\n"<<endl;
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 6:
            try {
            cout<<"\nInforme o numero para ser buscado: ";
            cin>>chave;
            if(arvore->busca(arvore,chave)){
                cout<<"\n Numero Encontrado\n"<<endl;
            }else{
                cout<<"\n Numero Nao Encontrado\n"<<endl;
            }
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        default:
        cout<<"\nOpcao invalida.\n"<<endl;
            break;
        }
        op = menu();
    }
    cout << "\n       PROGRAMA FINALIZADO\n" << endl;
    return 0;
}
