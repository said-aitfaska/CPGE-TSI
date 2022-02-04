/*

Le robot suiveur de couleur


FORMATION DIPFABLAB AVANCE 02/2019

MEMBRES: 
  Sarah
  Yasmina
  Véronique
  Justin

*/
   
#include <SPI.h>  
#include <Pixy.h>


Pixy pixy; //ouverture de la Pixy
int s;

void setup()
{
  
  Serial.begin(9600);
  Serial.print("Starting...\n");    //On utilise le port série pour débugger
  pinMode(5, OUTPUT);               //Emetteur ultrasons
  pinMode(6, INPUT);                //Récepteur ultrasons
  

  pinMode(9, OUTPUT);               //Sortie Relais pilotage des moteurs gauches
  pinMode(3, OUTPUT);               //Sortie Relais pilotage des moteurs droits
 

  pixy.init();                      //Initialisation de la Pixy
}


/* Fonction pour allumer les moteurs gauches*/

void avd(){

 
  digitalWrite(3,HIGH);


  
}


/* Fonction pour allumer les moteurs droits*/

void avg(){

   digitalWrite(9, HIGH);

 
}



/*Fonction pour arreter les moteurs gauches*/ 

void stop_droite(){

  digitalWrite(3, LOW);
  
}


/*Fonction pour arreter les moteurs droits*/

void stop_gauche(){

  digitalWrite(9, LOW);
  
}



void loop()
{ 



  
/*Analyse de la distance avec les obstacles par ultrasons*/
  
  
  delay(10);
  long duration;
  long distance;
  digitalWrite(5, LOW);  
  delayMicroseconds(10); 
  digitalWrite(5, HIGH);

  delayMicroseconds(30); 
  digitalWrite(5, LOW);
  duration = pulseIn(6, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);  //On obtient la distance
  
  
  /*Tant que les obstacles sont à + de 30cm du robot*/
  

  while(distance >= 30){

    
/*Détection des codes couleurs / objets programmés sur la Pixy*/


 static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 

 blocks = pixy.getBlocks();
    
/*Si on trouve des objets, on affcihe leur coordonnées dans le port série*/


  if (blocks)
  {
    
    
    i++;
    
    if (i%50==0) //On affiche les objets toutes les 50 mesures pour ne pas spammer l'Arduino
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print(); //affcihage des coordonnées des objets détectés

        //La pixy a une résolution de 640x240 mais affiche des coordonnées de 320 (en x) par 200 (en y)
        
        //on établit une condition sur la coordonnée en x de l'objet
        //si l'objet est tel que 120<x<200, alors on avance tout droit
        //si x<120 alors on avance vers la gauche en allumant les moteurs droits
        //si 200<x alors on avance vers la droite en allumant les moteurs gauches


       if(pixy.blocks[0].x > 200){

        avg();
        stop_droite();
        
      }
      
      else if (pixy.blocks[0].x < 120) {
      
        avd();
        stop_gauche();
        
      }

      else {
        avg();
        avd();
        
        
      }

        
      }
    }
  }
  
  //Si la distance est inférieure à 30cm, on stoppe tous les moteurs

  Serial.println("STOP");
  stop_droite();
  stop_gauche();
 
  

}
