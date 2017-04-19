

#ifndef __TABLETENNIS_H_
#define __TABLETENNIS_H_

#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>


#define Pi 3.1415926535
#define SIZE 5120000
#define nIter 100
#define MIN(x, y) ((x < y) ? x : y)

#define tt_r 0.019
#define tt_rho 1.225
#define tt_m 0.0025

#define tt_A (Pi * tt_r * tt_r)
#define tt_B (0.5 * tt_A * tt_rho / tt_m)
#define tt_g 9.81
#define tt_dt 0.0001

#define tableL 2.74
#define tableL2 (tableL / 2.0)
#define tableW 1.525
#define netzH 0.1525

#define a1 0.422794
#define b1 2.82709
#define c1 -9.98654
#define d1 12.4086
#define e1 4.40015
#define f1 -12.7359
#define g1 18.4641

#define a2 0.0153885
#define b2 -0.643274
#define c2 1.73774
#define d2 -0.334945
#define e2 -1.47531
#define f2 3.51225
#define g2 -0.537562

#ifdef _WIN32
#define __drand() (rand() / (float)RAND_MAX)
#else
#define __drand() drand48()
#endif

#if 0
struct PosMov {
  float x[SIZE];
  float y[SIZE];
  float z[SIZE];
  float vx[SIZE];
  float vy[SIZE];
  float vz[SIZE];
};

struct Value {
  bool isStop[SIZE];
  PosMov posmov;
  float omega0[SIZE];
  float omega_x[SIZE];
  float omega_y[SIZE];
  float omega_z[SIZE];
  PosMov start;
  PosMov end;
  float vEnd[SIZE];
  int counter;
  int size;
};
#endif

struct PosMov {
  float x;
  float y;
  float z;
  float vx;
  float vy;
  float vz;
};

struct Value {
  bool isStop;
  PosMov posmov;
  float omega0;
  float omega_x;
  float omega_y;
  float omega_z;
  PosMov start;
  PosMov end;
  float vEnd;
};

//void kernel(Value* d_valueSet, int activdb, int idx);

inline float ccd(float value) {
  //	*ret = a1 + b1 * value + c1 * (value*value) + d1 * (value*value*value) /
  //		1.0 + e1 * value + f1 * (value*value) + g1 *
  //(value*value*value);
  // crfs
  return (a1 + b1 * value + c1 * (value * value) + d1 * (value * value * value)) /
      (1.0 + e1 * value + f1 * (value * value) + g1 * (value * value * value));
}

inline float ccl(float value) {
  //	*ret = a2 + b2 * value + c2 * (value*value) + d2 * (value*value*value) /
  //		1.0 + e2 * value + f2 * (value*value) + g2 *
  //(value*value*value);
  // crfs
  return (a2 + b2 * value + c2 * (value * value) + d2 * (value * value * value)) /
      (1.0 + e2 * value + f2 * (value * value) + g2 * (value * value * value));
}

inline void kernel(std::vector<Value>& d_valueSet, int idx) {
  // activpos is the new value and should just be used for write operations

  auto& value = d_valueSet[idx];

  if (value.isStop) {
    // nichts zu tun
    return;
  }

#ifdef COMPUTE_COMPLETE_TRAJECTORY
  // this is better for cpu code gpu code will hate this
  while( value.isStop == false ) {
#endif

    // store last positions speed information into register
    // crfs warum sind denn jetzt hier die alten Werte in dem inactivdb Array??
    float vxlast = value.posmov.vx;
    float vylast = value.posmov.vy;
    float vzlast = value.posmov.vz;

    float mod_v = sqrt(vxlast * vxlast + vylast * vylast + vzlast * vzlast);

    float omega0 = value.omega0;
    float inval = omega0 * tt_r / mod_v;
    auto valccd = ccd(inval);
    auto valccl = ccl(inval);

    float omega_x = value.omega_x;
    float omega_y = value.omega_y;
    float omega_z = value.omega_z;

    float multiplier = tt_B * mod_v;

    auto dydx_vx = -(multiplier * valccd * vxlast) +
	      multiplier * valccl * (omega_y * vzlast - omega_z * vylast);
    auto dydx_vy = -(multiplier * valccd * vylast) +
	      multiplier * valccl * (omega_z * vxlast - omega_x * vzlast);
    auto dydx_vz = -(multiplier * valccd * vzlast) +
	      multiplier * valccl * (omega_x * vylast - omega_y * vxlast) - tt_g;

    float zlast = value.posmov.z;
    float xlast = value.posmov.x;
    float ylast = value.posmov.y;

    float xnow,ynow,znow;
    float vxnow,vynow,vznow;
    // calculate new speed and position
    value.posmov.x = xnow = xlast + vxlast * tt_dt;
    value.posmov.y = ynow = ylast + vylast * tt_dt;
    value.posmov.z = znow = zlast + vzlast * tt_dt;
    value.posmov.vx = vxnow = vxlast + dydx_vx * tt_dt;
    value.posmov.vy = vynow = vylast + dydx_vy * tt_dt;
    value.posmov.vz = vznow = vzlast + dydx_vz * tt_dt;
    //    printf("positions new, old, omega, ccd, ccl, %f %f %f %f %f %f %f %f
    //    %f\n",xlast,ylast,zlast,xnow,ynow,znow,omega0,valccd,valccl);
    // TODO : kill unneccesary ifs
    // abort if ball crosses the surface and hits the table
    if ((zlast > 0.0) && (znow < 0.0)) {
      float t = -zlast / (znow - zlast);
      float xs = xlast + t * (xnow - xlast);
      float ys = ylast + t * (ynow - ylast);
      float zs = zlast + t * (znow - zlast);
      value.end.x = xs;
      value.end.y = ys;
      value.end.z = zs;
      if ((ys >= tableL2) && (xs < tableW) && (ys <= tableL) && (xs >= 0.0)) {
	float vxs,vys,vzs;
	value.end.vx = vxs = vxlast + t * (vxnow - vxlast);
	value.end.vy = vys = vylast + t * (vynow - vylast);
	value.end.vz = vzs = vzlast + t * (vznow - vzlast);
	value.vEnd = sqrt(vxs * vxs + vys * vys + vzs * vzs);
	// printf("erfolgreicher Schlag \n");
      } else {
	// tisch verfehlt
      }
      value.isStop = true;

      // printf("Fehler - Tisch verfehlt \n");
      return;
      // 	printf("isStop %d \n",d_valueSet.isStop[pos]);
    }
    // abort if ball crosses the surface from beneath and is under the table (is
    // not if it is in front of the table)
    if ((zlast < 0.0) && (znow > 0.0) && (xnow > 0.0) && (ynow > 0.0)) {
      float t = -zlast / (znow - zlast);
      float xs = xlast + t * (xnow - xlast);
      float ys = ylast + t * (ynow - ylast);
      float zs = zlast + t * (znow - zlast);
      if ((ys > tableL2) && (xs < tableW)) {
	// von unten getroffen
	// printf("Ball trifft Tisch von unten \n");
      }
      value.isStop = true;

      return;
    }

    // abort if ball hits the net or passes to high
    if ((ynow > tableL2) && (ylast < tableL2)) {
      if (znow < netzH) {
	value.isStop = true;  // im netz
					 // printf("Ball im Netz \n");
	return;
      }
      if (znow > netzH + 0.3) {
	value.isStop = true;  // zu hoch
					 // printf("Ball zu hoch \n");
	return;
      }
    }
#ifdef COMPUTE_COMPLETE_TRAJECTORY
  }
#endif
}

#if 0
#define cpyE( name ) vd.name[id_d] = vs.name[id_s]
#define cpyP( name ) \
  vd.name.x[id_d] = vs.name.x[id_s]; \
  vd.name.y[id_d] = vs.name.y[id_s]; \
  vd.name.z[id_d] = vs.name.z[id_s]; \
  vd.name.vx[id_d] = vs.name.vx[id_s]; \
  vd.name.vy[id_d] = vs.name.vy[id_s]; \
  vd.name.vz[id_d] = vs.name.vz[id_s] 

inline void move( Value& vs, Value& vd, int id_s, int id_d ){
  cpyE( isStop );
  cpyP( posmov );
  cpyE( omega0 );
  cpyE( omega_x );
  cpyE( omega_y );
  cpyE( omega_z );
  cpyP( start );
  cpyP( end );
  cpyE( vEnd );
}

#endif


#endif
