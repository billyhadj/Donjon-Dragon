#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>

//constantes
#define CHAR_MONSTER 'M'
#define CHAR_POTION 'o'
#define CHAR_WEAPON 'X'
#define CHAR_SHIELD 'H'
#define ESCALIER_UP '@'
#define ESCALIER_DOWN 'd'


using namespace std ;

struct Position {
  int x;
  int y;
  int level;
};

class Potion;
class Monster;
class Player;


class Floor {
private :
  vector<vector<char> > level ; 
public :
  Floor(const string);
  Floor(const Floor &);
  ~Floor();
  void setEtage(const int i, const int j, const char k);
  char getEtage(const int i, const int j) const;
  int getSize();
  int getSize(const int i);
};

class Donjon{
private :
  vector<Floor> donjon ;
  vector<Position> escalier;
public:
  Donjon(); //done
  Donjon(const Donjon&); //done
  void setLevel(const int i, const int j, const int k, const char c); //done
  char getLevel(const int i, const int j, const int k) const; //done
  Position getEscalier(const int); //done
  void affichage(const int, vector<Monster>, vector<Potion>, Player, Donjon &); //done
  int getSize(const int); //done
  int getSize(const int, const int); //done
};

class Stuff {
protected:
  Position pos;
  string name;
  int duration;
  char representation;
public :
  Stuff();
  Stuff(Donjon &);
  Stuff(const Stuff &);
  Stuff(int i);
  string getName();
  int getDuration();
  void lessDuration();
  char getRepresentation();
  void setPosition(const int, const int, const int);
  Position getPosition();
  
};



class Potion : public Stuff {
private:
  bool actif;
  int effect;
public:
  Potion(Donjon &);
  Potion(const Potion &);
  Potion(int);
  void setActif();
  bool getActif();
};
class Weapon : public Stuff {
private:
  int damage;
  int scope;
public:
  Weapon(Donjon &);
  Weapon(const Weapon &);
};

class Shield : public Stuff {
public:
  Shield(Donjon &);
};


class Entity {
  //statistics
protected:
  int visibility;
  int strength;
  int healthPoint;
  int shield;
  int resistance;
  Position position;
  char representation;
public:
  void setVisibility(const int);
  int getVisibility() const;
  void setStrength(const int);
  int getStrength() const;
  void sethealthPoint(const int);
  int getHealthPoint() const;
  void setShield(const int);
  int getShield() const;
  void setResistance(const int);
  int getResistance() const;
  void setRepresentation(const char); //done
  char getRepresentation() const; //done
  virtual void setPosition(const int x, const int y, const int z); //done
  virtual Position getPosition() const; //done
  void drop(); //perd tout son inventaire si healthPoint = 0
  //virtual void attack();
public:
  //Entity();
  //~Entity();
};

class Player : virtual  public Entity{
private:
  vector<Potion> inventory_Potion;
  vector<Weapon> inventory_Weapon;
public:
  Player(Donjon &d); //done
  //~Player();
  void take(vector<Potion> &, vector<Weapon> &);//prendre un objet et l'ajouter à son inventaire
  void erase_Potion(int);//supprimer une potion
  void erase_Weapon(int);//supprimer une arme
  void drop();//jeter un objet
  void move(const Donjon donj, Donjon &ddonj);
};


class Monster : public Entity {
private:
  int IA;
public:
  Monster(Donjon &, int);
  ~Monster();
  int getIA();
  void move(Donjon, Donjon &, Player, int);
};

