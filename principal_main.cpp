#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include "header.hpp"

using namespace std ;


int main (int argc, char * argv[]){
  Donjon d;
  Donjon dd(d);
  Donjon ddd(d);
  for (int i = 0 ; i < 4 ; i++){
    for(int j = 0 ; j < ddd.getSize(i) ; j++){
      for(int k = 0 ; k < ddd.getSize(i,j) ; k++){
	ddd.setLevel(j,k,i,' ');
      }
    }
  }
  Player p(dd);
  int nbr_tour = 1;
  vector<Potion> tableauPotion;
  vector<Monster> tableauMonster;
  int nb_potions = rand()%20 + 20;
  for (int i = 0 ; i < nb_potions ; i++){
    Potion pot(dd);
    tableauPotion.push_back(pot);
  }
  int cpt;
  for (int i = 0 ; i < 4 ; i++){
    cpt = 0;
    while(cpt < 5){
      Monster M(dd, i);
      tableauMonster.push_back(M);
      cpt++;
    }
  }
  dd.affichage(p.getPosition().level, tableauMonster, tableauPotion, p, ddd);
  //début jeu
  while(p.getPosition().level != 3){
    p.move(d, dd);
    for( int i = 0 ; i < tableauMonster.size(); i++){
      tableauMonster[i].move(d, dd, p, nbr_tour);
    }
    nbr_tour ++;
    system("clear");
    dd.affichage(p.getPosition().level, tableauMonster, tableauPotion, p,ddd);
  }
  return 0;
}

