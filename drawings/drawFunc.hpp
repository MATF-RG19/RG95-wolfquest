#ifndef DRAWFUNC_HPP
#define DRAWFUNC_HPP

void drawAxes(float len);

void setNormalAndVertex();

/*
ovo je doktorski odradjen model Balta ako to mogu
sam za sebe reci, svaka tacka unapred definisana u prostoru
ostalo je crtanje trouglova (poly izgled)
*/
void drawBalto(int baltoPosition);

// jelka od valjka i 6 piramida(kupe sa malo slices/stacks)
void drawChristmasTree(float x, float y, float z);

// jedna jelka pomerena na traku(position)
void drawChristmasTreeObstacle(int position);

/*
crn Balto bez pomeranja nogu, kasnije rotiran i transliran
inace u crtacu jako arogantan i egocentrican haski
"The only way Steele notices anyon
is if they're wearing a mirror"
Balto(1995) pogledaj crtani..
*/
void drawSteel(void);

// steel pomeren na jednu od 3 trake(position) i rotiran licem ka Baltu
void drawSteelObstacle(int position);

// iscrtava sve prepreke pozivajuci se na ostale funkcije
// drawObstacle-> drawChristmasTreeObstacle/drawSteelObstacle
void drawObstacles(void);

/*
 u zavisnosti od tipa(Steel/Jelka) crta prepreku na udaljenosti x
 i na traci position
*/
void drawObstacle(float x, int type, int position);

// razvucena kocka
void drawTrack(void);

/*
2 razvucene kocke translirane levo/desno
i rotirane pod uglom 30* i na njih dodate jelke
*/
void drawTerrain(void);

#endif
