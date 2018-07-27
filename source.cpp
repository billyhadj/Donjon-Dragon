#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include "header.hpp"

using namespace std ;

#define RESET "\033[0m"
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

Position Entity::getPosition() const{
  return position;
}
void Entity::setPosition(const int x, const int y, const int level){
  position.x = x;
  position.y = y;
  position.level = level;
}

void Entity::setRepresentation(const char c){
  representation = c;
}

char Entity::getRepresentation() const{
  return representation;
}

Player::Player(Donjon & d) {
  Potion pot1(2);
  Potion pot2(1);
  visibility = 5;
  inventory_Potion.push_back(pot1);
  inventory_Potion.push_back(pot2);
  int random = rand()%4;
  switch (random){
  case 1 :
    representation = '^';
    break;
  case 2 :
    representation = 'V';
    break;
  case 3 :
    representation = '<';
    break;
  case 0 :
    representation = '>';
    break;
  default:
    cout << "erreur lors de la création du personnage" << endl;
  }
  position.x = 5;
  position.y = 5;
  position.level = 0;
  d.setLevel(position.x, position.y, position.level, representation);
}

void Player::move(const Donjon donj, Donjon &ddonj){
  char d;
  char _reach;
  int x = getPosition().x;
  int y = getPosition().y;
  int z = getPosition().level;
  int n = 0;
  Position pos;
  int quit = 0 - 48;
  do{
    system("stty raw");
    d = getchar();
    system("stty cooked");
    n = d - 48;
  }while(n > 9 || n < 0);
  switch(n){
  case 7 :
    _reach = ddonj.getLevel(x-1,y-1,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x-1, y-1, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 4 :
    _reach = ddonj.getLevel(x,y-1,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x, y-1, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 1 :
    _reach = ddonj.getLevel(x+1,y-1,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x+1, y-1, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 8 :
    _reach = ddonj.getLevel(x-1,y,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x-1, y, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 2 :
    _reach = ddonj.getLevel(x+1,y,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x+1, y, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 9 :
    _reach = ddonj.getLevel(x-1,y+1,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x-1, y+1, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 6 :
    _reach = ddonj.getLevel(x,y+1,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x, y+1, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 3 :
    _reach = ddonj.getLevel(x+1,y+1,z);
    if(_reach != '/' && _reach != '-' && _reach != '\\' && _reach != ' ' && _reach != '|' && _reach != CHAR_MONSTER){
      setPosition(x+1, y+1, z);
    }else{
      if(_reach == CHAR_MONSTER){
	//attaque
      }else
	move(donj, ddonj);
    }
    break;
  case 5 :
    char c;
    c = getRepresentation();
    do{
      system("stty raw");
      d = getchar();
      system("stty cooked");
      n = d - 48;
    }while((n != 4 || c == '<') && (n != 8 || c == '^') && (n != 6 || c == '>') && (n != 2 || c == 'V'));
    switch (n){
    case 4 :
      setRepresentation('<');
      break;
    case 8 :
      setRepresentation('^');
      break;
    case 6 :
      setRepresentation('>');
      break;
    case 2 :
      setRepresentation('V');
      break;
    default:
      break;
    }
  case 0 :
    //return quit();
    break;
  default:
    break;
  }
  if(_reach == ESCALIER_DOWN && getPosition().level != 0){
    pos = ddonj.getEscalier(2*z-1);
    setPosition(pos.x, pos.y, pos.level);
  }else{
    if(_reach == ESCALIER_UP && getPosition().level != 3){
      pos = ddonj.getEscalier(2*(z+1));
      setPosition(pos.x, pos.y, pos.level);
    }
  }
  ddonj.setLevel(x, y, z, donj.getLevel(x,y,z));
  ddonj.setLevel(getPosition().x, getPosition().y, getPosition().level, getRepresentation());
}

Floor :: Floor(const string file_name) {
  ifstream file(file_name.c_str(), ios::in); //ouverture du fichier
  int taille = 0;
  file.seekg(file.beg, file.end);//déplacement à la fin du ficher
  int sizeFile = file.tellg();//mémorise la longueur du fichier
  file.seekg(file.beg);//retourne au début
  int sizeRow = 0 ;
  int sizeCol = 0 ; 
  if(file){
    //Lecture des paramètres pour créer une matrice du niveau
    while(taille != sizeFile){
      sizeCol++;
      string contenu;
      getline(file, contenu);
      if (contenu.length()> sizeRow)
	sizeRow = contenu.length() ;
      taille = taille + contenu.length() + 1;
      file.seekg(taille);
    }
    file.seekg(file.beg);
    taille = 0 ;
    int i = 0 ;
    char Buffer[sizeCol][sizeRow];
    //Création de la matrice
    while(taille != sizeFile){
      string contenu;
      getline(file, contenu);
      for (int j = 0 ; j<sizeRow  ; j++){
	if(j < contenu.length()){
	  Buffer[i][j]=contenu[j];
	}
	else{
	  Buffer[i][j]=' ';
	}
      }
      taille = taille + contenu.length() + 1;
      file.seekg(taille);
      i++ ;
    }
    for(int i = 0 ; i < sizeCol ; i++){
      vector<char> tmp ; 
      for ( int j = 0 ; j < sizeRow ; j++){
	tmp.push_back(Buffer[i][j]);
      }
      level.push_back(tmp);      
      }
    file.close();
}
 else
   cerr << "Impossible d'ouvrir le fichier" << endl;

} ;

Floor::Floor(const Floor &fl){
  for (int i = 0 ; i < fl.level.size() ; i++){
    level.push_back(fl.level[i]);
  }
}
        
void Floor::setEtage(const int i, const int j, const char c){
  level[i][j] = c;
}

char Floor::getEtage(const int i, const int j) const {
  return level[i][j];
}

void Donjon::setLevel(const int i, const int j, const int k, const char c){
  donjon[k].setEtage(i,j,c);
}

char Donjon::getLevel(const int i, const int j, const int k) const {
  return donjon[k].getEtage(i,j);
}

Position Donjon::getEscalier(const int i){
  return escalier[i];
}

int Floor::getSize(){
  return level.size();
}

int Floor::getSize(const int i){
  return level[i].size();
}

void Donjon::affichage(const int etage, vector<Monster> vm, vector<Potion> vp, Player p, Donjon &ddd){
  for (int i = 0 ; i < donjon[etage].getSize() ; i++) {
    for (int j = 0 ; j < donjon[etage].getSize(i) ; j++) {
      if( abs(p.getPosition().y - j) <= p.getVisibility() && abs(p.getPosition().x - i) <= p.getVisibility()){
	ddd.setLevel(i,j,etage,getLevel(i,j,etage));
	bool is = false;
	int tmp;
	for (int k = 0 ; k < vm.size() ; k++){
	  if (vm[k].getPosition().x == i && vm[k].getPosition().y == j && vm[k].getPosition().level == etage){
	    tmp = k;
	    is = true;
	  }
	}
	if ( is ){
	  switch(vm[tmp].getIA()){
	  case 0 :
	    cout << GREEN;
	    break;
	  case 1 :
	    cout << YELLOW;
	    break;
	  case 2 :
	    cout << MAGENTA;
	    break;
	  case 3 :
	    cout << RED;
	  default :
	    break;
	  }
	}
	is = false;
	for (int k = 0 ; k < vp.size() ; k++){
	  if (vp[k].getPosition().x == i && vp[k].getPosition().y == j && vp[k].getPosition().level == etage)
	    is = true;
	}
	if ( is ){
	  cout << RED;
	}
	cout << ddd.getLevel(i,j,etage) << WHITE;
      }
      else{
	cout << RESET << ddd.getLevel(i,j,etage) << WHITE;
      }
    }
    cout << endl;
  }
}

Floor::~Floor(){
}

Donjon::Donjon(){
  bool i1 = true;
  bool i2 = true;
  bool i3 = true;
  bool i4 = true;
  int cpt = 0;
  do{
    int n;
    do{
    n = rand()%4 + 1;
    }while(i1 == false && n == 1 || i2 == false && n == 2 || i3 == false && n == 3 || i4 == false && n == 4);
    switch(n){
    case 1 :
      donjon.push_back(Floor("carte.txt"));
      i1 = false;
      break;
    case 2 :
      donjon.push_back(Floor("carte2.txt"));
      i2 = false;
      break;
    case 3 :
      donjon.push_back(Floor("carte3.txt"));
      i3 = false;
      break;
    case 4 :
      donjon.push_back(Floor("carte4.txt"));
      i4 = false;
      break;
    default:
      break;
    }
    int i = 0;
    int j = 0;
    char c = ESCALIER_DOWN;
    Position pos;
    do{
      if(j == getSize(cpt, i)){
	i++;
	j = 0;
      }else{
	j++;
      }
    }while(donjon[cpt].getEtage(i, j) != c);
    pos.x = i;
    i = 0;
    pos.y = j;
    j = 0;
    pos.level = cpt;
    escalier.push_back(pos);
    c = ESCALIER_UP;
    do{
      if(j == getSize(cpt, i)){
	i++;
	j = 0;
      }else{
	j++;
      }
    }while(donjon[cpt].getEtage(i, j) != c);
    pos.x = i;
    i = 0;
    pos.y = j;
    j = 0;
    pos.level = cpt;
    escalier.push_back(pos);
    cpt++;
  }while(cpt != 4);
}

Donjon::Donjon(const Donjon &donj){
  for (int i = 0 ; i < donj.donjon.size(); i++){
      donjon.push_back(donj.donjon[i]);
  }
  for (int i = 0 ; i < donj.escalier.size() ; i++){
    escalier.push_back(donj.escalier[i]);
  }
}

int Donjon::getSize(const int i){
  return donjon[i].getSize();
}

int Donjon::getSize(const int i, const int j){
  return donjon[i].getSize(j);
}

Stuff::Stuff(Donjon &d){
  int x;
  int y;
  int z;
  name = " ";
  duration = -1;
  representation = ' ';
  z = rand()%4;
  do{
    x = rand()%(d.getSize(z));
    y = rand()%(d.getSize(z,x));
  }while(d.getLevel(x,y,z) != '.');
  pos.x = x;
  pos.y = y;
  pos.level = z;
}

Stuff::Stuff(const Stuff &){
}

Stuff::Stuff(int i){
}

string Stuff::getName(){
  return name;
}

int Stuff::getDuration(){
  return duration;
}

void Stuff::lessDuration(){
  duration--;
}

char Stuff::getRepresentation(){
  return representation;
}

void Stuff::setPosition(const int x, const int y, const int z){
  pos.x = x;
  pos.y = y;
  pos.level = z;
}

Position Stuff::getPosition(){
  return pos;
}

Potion::Potion(Donjon &d) : Stuff(d){
  name = "Potion";
  representation = CHAR_POTION;
  actif = false;
  effect = rand()%3;
  d.setLevel(pos.x,pos.y,pos.level,representation);
}

Potion::Potion(int i) : Stuff(i){
  effect = i;
  name = "Potion";
  representation = CHAR_POTION;
  actif = false;
}

Potion::Potion(const Potion & pot) : Stuff(pot){
  name = pot.name;
  representation = CHAR_POTION;
  actif = pot.actif;
  effect = pot.effect;
}

void Potion::setActif(){
  actif = true;
}

bool Potion::getActif(){
  return actif;
}

Monster::Monster(Donjon &d, int floor){
  representation = CHAR_MONSTER;
  IA = rand()%4;
  if( IA == 3 )
    visibility = 5;
  else
    visibility = 1;
  int x;
  int y;
  do{
    x = rand()%(d.getSize(floor));
    y = rand()%(d.getSize(floor,x));
  }while(d.getLevel(x,y,floor) != '.');
  position.x = x;
  position.y = y;
  position.level = floor;
  d.setLevel(x,y,floor,representation);
}

Monster::~Monster(){
}

int Monster::getIA(){
  return IA;
}

void Player::take(vector<Potion> &vp, vector<Weapon> &vw){
  int j = 0;
  bool b = false;
  for( int i = 0 ; i < vp.size() ; i++){
    if(position.x == vp[i].getPosition().x && position.y == vp[i].getPosition().y && position.level == vp[i].getPosition().level){
      Potion pot(vp[i]);
      vp.erase(vp.begin() + i);
      inventory_Potion.push_back(pot);
      b = true;
    }
  }
  j += 1;
  if( !b ){
    for( int i = 0 ; i < vw.size() ; i++){
      if(position.x == vw[i].getPosition().x && position.y == vw[i].getPosition().y && position.level == vw[i].getPosition().level){
	Weapon w(vw[i]);
	vw.erase(vw.begin() + i);
	inventory_Weapon.push_back(w);
	b = true;
      }
    }
  }
}

void Player::erase_Potion(int i){
  inventory_Potion.erase(inventory_Potion.begin() + i);
}

void Player::erase_Weapon(int i){
  inventory_Weapon.erase(inventory_Weapon.begin() + i);
}

Weapon::Weapon(Donjon &d) : Stuff(d){
}

Weapon::Weapon(const Weapon &w) : Stuff(w){
}

Shield::Shield(Donjon &d) : Stuff(d){
}

void Monster::move(Donjon d, Donjon & dd, Player p, int nbr_tour){
  int i;
  int j;
  char _reach;
  switch(IA){
  case 0 : //random
    if(abs(p.getPosition().x - position.x) <= visibility && abs(p.getPosition().y - position.y) <= visibility){
      //combat
    }else{
      do{
	do{
	  i = rand()%3 - 1;
	  j = rand()%3 - 1;
      }while(i == 0 && j == 0);
	_reach = dd.getLevel(position.x + i, position.y + j, position.level);
      }while(_reach != '.' && _reach != '#' && _reach != p.getRepresentation());
      dd.setLevel(position.x, position.y, position.level, d.getLevel(position.x, position.y, position.level));
      position.x += i;
      position.y += j;
    }
    break;
  case 1 : //random sans couloirs
    if(abs(p.getPosition().x - position.x) <= visibility && abs(p.getPosition().y - position.y) <= visibility){
      //combat
    }else{
      do{
	do{
	  i = rand()%3 - 1;
	  j = rand()%3 - 1;
	}while(i == 0 && j == 0);
	_reach = dd.getLevel(position.x + i, position.y + j, position.level);
      }while(_reach != '.' && _reach != p.getRepresentation());
      dd.setLevel(position.x, position.y, position.level, d.getLevel(position.x, position.y, position.level));
      position.x += i;
      position.y += j;
    }
    break;
  case 2 : //random téléportation
    if(abs(p.getPosition().x - position.x) <= visibility && abs(p.getPosition().y - position.y) <= visibility){
      //combat
    }else{
      if(nbr_tour%10 == 0){
	do{
	  i = rand()%(d.getSize(position.level));
	  j = rand()%(d.getSize(position.level,i));
	}while(dd.getLevel(i,j,position.level) != '.' && dd.getLevel(i,j,position.level) != '#' && dd.getLevel(i,j,position.level) != CHAR_MONSTER);
	dd.setLevel(position.x, position.y, position.level, d.getLevel(position.x, position.y, position.level));
	position.x = i;
	position.y = j;
      }
    }
    break;
  case 3 : //qui suit le joueur
    {
    int distanceX = abs(p.getPosition().x - position.x);
    int distanceY = abs(p.getPosition().y - position.y);
    char _reach;
    int newX = 0;
    int newY = 0;
    vector<bool> access;
    int deplX = 0;
    int deplY = 0;
    int distanceMin = visibility + 1;
    if( distanceX <= visibility && distanceY <= visibility && p.getPosition().level == position.level){
      for(int cpt1 = 0 ; cpt1 <= 2 ; cpt1++){
	for(int cpt2 = 0 ; cpt2 <= 2 ; cpt2++){
	  _reach = dd.getLevel(position.x + cpt1-1, position.y + cpt2-1, position.level);
	  if(_reach == '.' || _reach == '#' || _reach == p.getRepresentation()){
	    access.push_back(true);
	  }
	  else{
	    access.push_back(false);
	  }
	}
      }
      dd.setLevel(position.x, position.y, position.level, d.getLevel(position.x, position.y, position.level));
      for(int i = 0 ; i < 9 ; i++){
	if(access[i]){
	  newX = i/3 - 1;
	  newY = i%3 - 1;
	  distanceX = abs(p.getPosition().x - position.x - newX);
	  distanceY = abs(p.getPosition().y - position.y - newY);
	  if( distanceX < distanceMin && distanceY < distanceMin){
	    distanceMin = max(distanceX, distanceY);
	    deplX = newX;
	    deplY = newY;
	  }
	}
      }
      cout << deplX << " et " << deplY << endl;
      if(position.x + deplX == p.getPosition().x && position.y + deplY == p.getPosition().y){
	//attaque
      }else{
	position.x += deplX;
	position.y += deplY;
      }
    }else{
      do{
	do{
	  i = rand()%3 - 1;
	  j = rand()%3 - 1;
	}while(i == 0 && j == 0);
	_reach = dd.getLevel(position.x + i, position.y + j, position.level);
      }while(_reach != '.' && _reach != '#');
      dd.setLevel(position.x,position.y,position.level, d.getLevel(position.x,position.y,position.level));
      position.x += i;
      position.y += j;
    }
    }
    break;
  default :
    break;
  }
  dd.setLevel(position.x, position.y, position.level, representation);
}

int Entity::getVisibility() const{
  return visibility;
}

/*int Entity::getHealthPoint()const {
  return healthPoint ;
}
void Entity::setHealthPoint(int i) {
  healthPoint = i ;
}

void Entity::attack(Entity & e) {
  if (e.getResistance() < strength){
    e.setHealthPoint(e.getHealthPoint() - (strength-e.getResistance()));
}

int Entity::getStrength() const  {
  return strength ;
}

void Entity :: setStrength(const int i){
  strength = i ;
}

 
int Entity :: getShield() const {
  return shield ;
}

void Entity :: setShiled(const int i){
  shield = i ;
}

int Entity :: getResistance() const {
  return resistance ;
}

void Entity :: setResistance (const int i){
  resistancee = i ;
  }*/
