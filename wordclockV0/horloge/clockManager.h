#define il {2,0,0}      // {Nombre de lettres, Numéro de sa ligne de 0 à 9, numéro de colonne de sa première lettre de 0 à 10}
#define rien {0,0,0}
#define est {3,0,3}
#define une {3,2,4}
#define deux {4,0,7}
#define trois {5,1,6}
#define quatre {6,1,0}
#define cinqH {4,3,7}
#define six {3,3,4}
#define sept {4,2,7}
#define huit {4,3,0}
#define neuf {4,2,0}
#define dixH {3,4,2}
#define onze {4,5,0}
#define midi {4,4,0}
#define minuit {6,4,5}
#define heure {5,5,5}
#define heures {6,5,5}
#define moins {5,6,0}
#define le  {2,6,6}
#define dixM {3,6,8}
#define et1 {2,7,0}
#define quart {5,7,3}
#define vingt {5,8,0}
#define vingtcinq {10,8,0}
#define tiret {1,8,5}
#define cinqM {4,8,6}
#define et2 {2,9,0}
#define demie {5,9,3}
#define flo {3,9,8}

const int ledW = 11, ledH = 10; //Nombre de leds en ligne et en colonne
int hoursArray[24][2][3] = {{minuit, rien}, {une, heure}, {deux, heures}, {trois, heures}, {quatre, heures}, {cinqH, heures}, {six, heures}, {sept, heures}, {huit, heures}, {neuf, heures}, {dixH, heures}, {onze, heures}, {midi, rien}, {une, heure}, {deux, heures}, {trois, heures}, {quatre, heures}, {cinqH, heures}, {six, heures}, {sept, heures}, {huit, heures}, {neuf, heures}, {dixH, heures}, {onze, heures}};
int minutesArray[12][3][3] = {{rien, rien, rien}, {cinqM, rien, rien}, {dixM, rien, rien}, {et1, quart, rien}, {vingt, rien, rien}, {vingtcinq, rien, rien}, {et2, demie, rien}, {moins, vingtcinq, rien}, {moins, vingt, rien}, {moins, le, quart},{moins, dixM, rien}, {moins, cinqM, rien}};
byte octet1, octet2, octet3; //Octets que l'on envoit au 3 Registres à décalages
int matrix[ledH][ledW];

void selectionLigne(int ligneP) {
    octet1 = ((1<<7)>>ligneP)&255; //1000 0000 -> 0100 0000 -> ... -> 0000 0000 -> 0000 0000
    octet2 = 0; 
    switch(ligneP) {
      case 8:
        octet2 = 128;
        break;
      case 9:
        octet2 = 64;
        break;
    }
    octet3 = 0;
}

void gestionLigne(int ligneP) {
    for (int i = 0; i<6; i++) {
     octet2 = octet2+((matrix[ligneP][i])<<(5-i));  
    }
    for (int i = 6; i<11; i++) {
      octet3 = octet3+(matrix[ligneP][i]<<(13-i));  
    }
    
}

void matrixUpdate() {
  int minutesH = floor(minutes/5);
  int hoursH = hours;
    if (minutesH > 6 && hours <= 23) 
    {
      hoursH = hours+1;
    } else if (minutesH > 6 && hours == 23)
    {
      hours = 0;
    }
    for (int i = 0; i < ledH; i++) {
      for (int j = 0; j < ledW; j++) {
        matrix[i][j] = 1;
      }
    }
    for (int i = 0; i < 2; i++) { //il
        matrix[0][i] = 0;
    }
    for (int i = 0; i < 3; i++) { //est
        matrix[0][i+3] = 0;
    }
    for (int j = 0 ; j < 2 ; j++) {
      for (int i = 0; i < hoursArray[hoursH][j][0]; i++) {
          matrix[hoursArray[hoursH][j][1]][i+hoursArray[hoursH][j][2]] =0;
      }
    }
    for (int j = 0 ; j < 3 ; j++) {
      for (int i = 0; i < minutesArray[minutesH][j][0]; i++) {
          matrix[minutesArray[minutesH][j][1]][i+minutesArray[minutesH][j][2]] = 0;
      }
    }
}
