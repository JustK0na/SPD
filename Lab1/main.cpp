#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#define SIZE 12
#define FILEPATH "SCHRAGE1.txt"

typedef struct {
    int id;
    int rj;
    int pj;
    int qj;
}Zadanie;

class Harmonogram{
public:
    std::vector<Zadanie> Z;
    int C=0;

    explicit Harmonogram(std::vector<Zadanie>& lista):Z(lista) {};

    void ladujZadaniaLosowe(){
        std::srand(time(NULL));
        for(int i=0; i<SIZE; i++){
            Zadanie tmp;
            tmp.id = i;
            tmp.pj = std::rand() % 20 + 1;
            tmp.rj = std::rand() % 20 + 1;
            tmp.qj = std::rand() % 20 + 1;
            Z.push_back(tmp);
        }
    }
    void ladujZadaniaZPliku(){
        std::ifstream f("/home/mikolaj/studia/SPD/Lab1/SCHRAGE1.txt");
        if(!f){
            std::cout<<"Blad otwarcia pliku";
            std::exit(1);
        }
        int n = 0;
        f >> n;
        for(int i=0; i<n; i++){
            Zadanie tmp;
            Z.push_back(tmp);
            Z.at(i).id = i;
            f>>Z.at(i).rj;
            f>>Z.at(i).pj;
            f>>Z.at(i).qj;
        }

    }
    void pokazZadania(){
        std::cout<<"\n########################\n";
        for(auto & i : Z)
            std::cout<<i.id<<". {"<<i.rj<<"}{"<<i.pj<<"}{"<<i.qj<<"}\n";
        std::cout<<"########################\n";
    };
    int liczC(){
        C = 0;
        for(int i=0; i<Z.size(); i++){
            if(i == 0){
             C = C+Z.at(i).rj+Z.at(i).pj;
            }
            else{
                C = C + std::max(C, Z.at(i).rj) + Z.at(i).pj;
            }
        }
        for(auto & i : Z){
            C += i.qj;
        }
        return C;
    }
    void HeurystyczneDostepnosc(){
        std::sort(Z.begin(), Z.end(), [](const Zadanie &a, const Zadanie &b){return a.rj < b.rj;});
    }
    void HeurystyczneStygniecie(){
        std::sort(Z.begin(), Z.end(), [](const Zadanie &a, const Zadanie &b){return a.qj > b.qj;});
    };
    void Zupelny(){
        std::vector<int> allC;
        do{
            //pokazZadania();
            allC.push_back(liczC());
        } while (std::next_permutation(Z.begin(), Z.end(), [](const Zadanie& a, const Zadanie& b){return a.id < b.id;}));
        for(auto &i: allC)
            std::cout<<"C: "<<i<<"\n";
        int bestC = *std::min_element(allC.begin(), allC.end());
        std::cout<<"Best C: "<< bestC<<"\n";
    }
};


int main() {
    std::vector<Zadanie> Z;
    Harmonogram H(Z);

    H.ladujZadaniaZPliku();
    //H.ladujZadaniaLosowe();
    H.Zupelny();
    H.pokazZadania();
    std::cout<<"C: "<<H.liczC()<<std::endl;
    H.HeurystyczneDostepnosc();
    H.pokazZadania();
    std::cout<<"C: "<<H.liczC()<<std::endl;
    H.HeurystyczneStygniecie();
    H.pokazZadania();
    std::cout<<"C: "<<H.liczC()<<std::endl;
    return 0;
}