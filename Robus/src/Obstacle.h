#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <Arduino.h>
#include <ArduinoNunchuk.h>
#include <Wire.h>
#include "Base.h"

int checkZ();
int IsForward();
void UpdateNun();
void SuivreLigne();

//Transforme le chiffre retourné par l'infrarouge en distance en cm
float distance_cm(float dist){
  return (float)(85.624 * pow(2.7182,-0.006*dist));
}

float doublecheck_dist(int analog_input){
  float dist = 0;
  float nbr = 10;
  for(int i = 0; i < nbr; i++)
    {
      dist += distance_cm(analogRead(analog_input));    
      }
      return (dist / nbr) ;
}

void allo(){
  
  checkSpeed(0,0.3);
  if (doublecheck_dist(9) < 20){

      Stop();
      
      TournerSurLui(2010, 1);
      ENCODER_Reset(0);
      int distance_mur = distance_cm(analogRead(8));
      do{
       checkSpeed(0,0.3);
      }while(doublecheck_dist(8) < distance_mur + 15);
      int distance_1er_essai = ENCODER_Read(0);
      
      Stop();
      delay(1000);
      avance(2000);
      TournerSurLui(2010,0);
      avance(5000);
      delay(1000);

      distance_mur = doublecheck_dist(8);
      do{
       checkSpeed(0,0.3);
      }while(distance_cm(analogRead(8)) < distance_mur + 15);

      avance(2000);
      TournerSurLui(1900,0);
      Stop();
      while(analogRead(4) < 500){
        checkSpeed(0,0.3);
      }
      TournerSurLui(2010,1);
      delay(5000);
      avance(10000);

    
  } 
}

void vibration(int fois,int delayOn, int delayOff);

void obstacle_guide_simple(){
  
  
  if (doublecheck_dist(9) < 20 && IsForward() == 1){

/*
      Stop();
      
      TournerSurLui(2010, 1);
      ENCODER_Reset(0);
      int distance_mur = distance_cm(analogRead(8));
      if(distance_mur > 40){
        //Tourne tout de suite
      }else{ 
        do{
        checkSpeed(0,0.3);
        }while(doublecheck_dist(8) < distance_mur + 15);
      }
      int distance_1er_essai = ENCODER_Read(0);
      
      Stop();
      delay(1000);
      avance(2000);
      TournerSurLui(2010,0); */
      MOTOR_SetSpeed(0,0); MOTOR_SetSpeed(1,0);
      vibration(2,1250,250);
  } 
}

int obstacle_libre_simple(){
  
  if(checkZ() == 1){

  if (doublecheck_dist(9) < 20){

      Stop();
  UpdateNun();
  if(checkZ() == 1){SuivreLigne();}
      TournerSurLui(2010, 1);
  UpdateNun();
  if(checkZ() == 1){SuivreLigne();}
      ENCODER_Reset(0);
      int distance_mur = distance_cm(analogRead(8));
      if(distance_mur > 40){
        //Tourne tout de suite
      }else{  
        do{
  UpdateNun();   
  if(checkZ() == 1){SuivreLigne();}
        checkSpeed(0,0.3);
        }while(doublecheck_dist(8) < distance_mur + 15);
      }
      int distance_1er_essai = ENCODER_Read(0);
       UpdateNun();
       if(checkZ() == 1){SuivreLigne();}
      Stop();
     
      avance(2000);
         UpdateNun();
         if(checkZ() == 1){SuivreLigne();}
      TournerSurLui(2010,0);
         UpdateNun();
         if(checkZ() == 1){SuivreLigne();}
      avance(4000);
      
   UpdateNun();
   if(checkZ() == 1){SuivreLigne();}
      distance_mur = doublecheck_dist(8);
      do{
       checkSpeed(0,0.3);
      }while(distance_cm(analogRead(8)) < distance_mur + 15);
   UpdateNun();
   if(checkZ() == 1){SuivreLigne();}
      avance(2000);
  UpdateNun();
  if(checkZ() == 1){SuivreLigne();}
      TournerSurLui(2010,0);
      // while(analogRead(4) < 500){
      //   checkSpeed(0,0.3);
      // }
      MOTOR_SetSpeed(0,0.2);
      MOTOR_SetSpeed(0,0.2);

      // avance(distance_1er_essai+2000);
      // TournerSurLui(2010,1);
      
  
    return 3;
  }
  } 
  return 0;
}

void perpendiculaire(){
  float dist_temp;
  float dist_avant = 0;
  float dist_1 = 0;
  float temp = 0;
  int j = 0;
  
      

      j = 0;
  do{

    MOTOR_SetSpeed(0,0);
    MOTOR_SetSpeed(1,0.3);

    if(j == 0){
      dist_temp = doublecheck_dist(8);
    }else{
      dist_temp = dist_avant;
    }
    delay(75);

    Serial.print("1");
    Serial.print("\t");
    Serial.print(distance_cm(analogRead(8)));
    Serial.print(" < ");
    Serial.println(dist_temp);

    j++;
    dist_avant = doublecheck_dist(8);
  }while(dist_avant < dist_temp);
    j = 0;
    dist_1 = dist_avant;
    temp = dist_avant;
    dist_avant = 5;
    dist_temp = 10;

  while(dist_avant < dist_temp && dist_avant < dist_1){

    MOTOR_SetSpeed(0,0.3);
    MOTOR_SetSpeed(1,0);

    if(j == 0){
      dist_temp = doublecheck_dist(8);
    }else{
      dist_temp = dist_avant;
    }
    delay(75);

    Serial.print("2");
    Serial.print("\t");
    Serial.print(distance_cm(analogRead(8)));
    Serial.print(" < ");
    Serial.println(dist_temp);

    j++;
    dist_avant = doublecheck_dist(8);
  }
  
  
  //LAFLEUR
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  Serial.println("DONE");
}

//0 = proche   1 = loin
int changerDistanceMur(float side, float diff){

  float nbrTic = ((143.0/3.0)*(acos((9.0-(abs(diff)))/9.0)));

  Serial.print("=============== NBR = "); Serial.print(nbrTic); Serial.println(" ===============");

  if (side == 0){
    //À REMPLIR PLUS TARD
  }
  if (side == 1){
    Stop();
    if (diff > 0){
      
      while(ENCODER_Read(1) < nbrTic){
        MOTOR_SetSpeed(0,0);
        MOTOR_SetSpeed(1,0.3);
        Serial.print("1\t0\t"); Serial.println(ENCODER_Read(1));
      }
      Stop();
      while(ENCODER_Read(0) < nbrTic){
        MOTOR_SetSpeed(0,0.3);
        MOTOR_SetSpeed(1,0);
        Serial.print("1\t1\t"); Serial.println(ENCODER_Read(0));
      }
    }

    // if (diff < 0){
      
    //   while(ENCODER_Read(0) < nbrTic){
    //     MOTOR_SetSpeed(0,0.3);
    //     MOTOR_SetSpeed(1,0);
    //     Serial.print("0\t1\t"); Serial.println(ENCODER_Read(0));
    //   }
    //   Stop();
    //   while(ENCODER_Read(1) < nbrTic){
    //     MOTOR_SetSpeed(0,0);
    //     MOTOR_SetSpeed(1,0.3);
    //     Serial.print("0\t0\t"); Serial.println(ENCODER_Read(1));
    //   }
    // }
    Stop();
  }

    
    Stop();
    
   

}
    
void SuivreMur(){

  
  float change = 0.1;
  float vit = 0.3;
  int dist_T = 0;
  int dist_temp = 0;
  int diff = 0;

  perpendiculaire();

  dist_T = doublecheck_dist(8); //Distance T du mur
  
  while(doublecheck_dist(8) < dist_T + 15){

    if (doublecheck_dist(8) > dist_T + 2  || doublecheck_dist(8) < dist_T - 2 ){
      
      perpendiculaire();

      dist_temp = doublecheck_dist(8);
      diff = dist_temp - dist_T;

      if (diff < -5 || diff > 5){
        changerDistanceMur(1,diff);
      }else{
        checkSpeed(0,0.3);
      }
    }else{
      checkSpeed(0,0.3);
    }
  }
  Stop();
  delay(3000);
  //HAHA MOI CEST JACOB
}

#endif