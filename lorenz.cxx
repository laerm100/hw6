#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

struct Vektor { // Vektor definieren

  double x; 
  double y;
  double z;
} ;

struct Vektor k_berechnen ( struct Vektor r, double a, double b, double c ) ;

int main(void) {
  
  struct Vektor k[4]; // 4 Vektoren
  struct Vektor r,r_temp;
  double a= 10.0;
  double b= 28.0;
  double c= 8.0/3.0;
  
  double dt= 0.0001; // dt=0.01, dt=0.001
  
  double t= 0.0; //t von 0-100 variieren
  
  ofstream Datei("lorenz.dat");
  
  r.x= 1.0; // Anfangsbedingungen
  r.y= 1.0;
  r.z= 1.0;
  
  Datei <<t<< "\t" <<r.x<< "\t" <<r.y<< "\t" <<r.z<< endl;
  
  for(t=0.0; t<=100.0; t+= dt) {
    
    r_temp = r;
    
    k[0] = k_berechnen (r,a,b,c); 
    
    r_temp.x += 0.5*dt*k[0].x;   // aus Runge Kutta Scheme
    r_temp.y += 0.5*dt*k[0].y;
    r_temp.z += 0.5*dt*k[0].z;
    k[1] = k_berechnen(r_temp, a, b, c);
    
    r_temp = r; 
    r_temp.x += 0.5*dt*k[1].x;
    r_temp.y += 0.5*dt*k[1].y;
    r_temp.z += 0.5*dt*k[1].z;
    k[2] = k_berechnen(r_temp, a, b, c);
    
    r_temp = r;
    r_temp.x += dt*k[2].x;
    r_temp.y += dt*k[2].y;
    r_temp.z += dt*k[2].z;
    k[3] = k_berechnen(r_temp,a,b,c);
    
    r.x += dt*(1.0/6.0*k[0].x + 1.0/3.0*k[1].x + 1.0/3.0*k[2].x+ 1.0/6.0*k[3].x);
    r.y += dt*(1.0/6.0*k[0].y + 1.0/3.0*k[1].y + 1.0/3.0*k[2].y+ 1.0/6.0*k[3].y);
    r.z += dt*(1.0/6.0*k[0].z + 1.0/3.0*k[1].z + 1.0/3.0*k[2].z+ 1.0/6.0*k[3].z);
    
    Datei << t << "\t" << r.x << "\t" << r.y << "\t" << r.z << endl;
    
  }
  
  Datei.close();
  exit(0);
}

struct Vektor k_berechnen(struct Vektor r,double a, double b, double c) {
 
    struct Vektor k; // Ableitungen vom Übungszettel
    k.x = a*(r.y - r.x);
    k.y = r.x*(b - r.z) - r.y;
    k.z = r.x*r.y - c*r.z;
    
    return k;    
}
    