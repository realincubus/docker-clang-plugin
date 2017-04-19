
// local headers
#include "tabletennis.h"
#include "Histogram.hpp"

// system headers
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#define DEBUG_PRINT(x) printf("---: %s\n", (x))

bool initialize_one( Value& value ) {
  value.isStop = false;
  // SETUP  XYZ
  value.end.x = 0.0;
  value.end.y = 0.0;
  value.end.z = 0.0;
  value.end.vx = 0.0;
  value.end.vy = 0.0;
  value.end.vz = 0.0;
  value.vEnd = 0.0;

  value.start.x = value.posmov.x = 0.381;
  value.start.y = value.posmov.y = 0.3 - 3.3 * __drand();
  value.start.z = value.posmov.z = -0.4 + 0.8 * __drand();
  value.posmov.x = value.posmov.x;
  value.posmov.y = value.posmov.y;
  value.posmov.z = value.posmov.z;
  auto v0 = (20.0 + 180.0 * __drand()) / 3.6;
  auto phi1 = abs(atan((tableW - value.posmov.x) /
		  (tableL2 - value.posmov.y)));
  auto phi2 = -abs(
      atan(value.posmov.x / (tableL2 - value.posmov.y)));
  //	    printf("phi1,phi2 %f %f\n",phi1*180.0/Pi,phi2*180.0/Pi);
  phi1 = Pi / 2.0 + phi1;
  phi2 = Pi / 2.0 + phi2;
  //		printf("phi1,phi2 %f %f\n",phi1*180.0/Pi,phi2*180.0/Pi);
  auto phi = MIN(phi1, phi2) + abs(phi2 - phi1) * __drand();
  auto theta = Pi * (-70.0 + 140.0 * __drand()) / 180.0;
  //      printf("theta %f\n",theta*180.0/Pi);
  theta = Pi / 2 - theta;
  //		printf("phi, theta %f %f\n",phi*180.0/Pi,theta*180.0/Pi);
  // SETUP VX VY VZ
  // crfs hier war die Geschwindigkeit in die falsche Richtung gegangen
  //		valueSet.start.vx[i] = valueSet.posmov[0].vx[i] = v0 * sin(theta) *
  //cos(phi);
  value.start.vx = value.posmov.vx =
      -v0 * sin(theta) * cos(phi);
  value.start.vy = value.posmov.vy =
      v0 * sin(theta) * sin(phi);
  if (value.posmov.vy <= 0.0) {
      // do this again.
    return false;
    // valueSet.isStop[i] = true;
  }
  value.start.vz = value.posmov.vz = v0 * cos(theta);

  // crfs negative z-Geschwindigkeiten sind unsinnig, wenn die z-Koordinate
  // des Startpunkts nicht schon
  //      grösser null ist!! Am besten: nach Wahl des Startpunkts die Wahl der
  //      z-Geschwindigkeit
  //      vornehmen: wenn z>=0.0 dann kann vz>=0 oder <0 sein, wenn z<0.,dann
  //      muss vz>0.0 sein
  if ((value.posmov.z < 0.0) &&
      (value.posmov.vz <= 0.0)) {
    return false;
  }

  value.posmov.vx = value.posmov.vx;
  value.posmov.vy = value.posmov.vy;
  value.posmov.vz = value.posmov.vz;

  // SETUP OMEGA
  //		valueSet.omega0[i] 	= (-150.0 + 300.0 * __drand()) * 2 * Pi;
  // crfs das war falsch!! omega sollte nur positiv sein!!
  value.omega0 = 50.0 * __drand() * 2 * Pi;
  // crfs maximal 3000 Umdrehungen pro Minute, d.h. 50 pro sekunde
  auto thetao = Pi * __drand();
  auto phio = 2.0 * Pi * __drand();
  value.omega_x = value.omega0 * sin(thetao) * cos(phio);
  value.omega_y = value.omega0 * sin(thetao) * sin(phio);
  value.omega_z = value.omega0 * cos(thetao);
  auto omega_norm = sqrt(value.omega_x * value.omega_x +
		    value.omega_y * value.omega_y +
		    value.omega_z * value.omega_z);
  value.omega_x = value.omega_x / omega_norm;
  value.omega_y = value.omega_y / omega_norm;
  value.omega_z = value.omega_z / omega_norm;
  return true;
}

void initialize_all(std::vector<Value>& value_set, int size) {
  DEBUG_PRINT("Initialising host values");
  value_set.resize( size );
#if 0
  for (int i = 0; i < size; i++) {
    auto& value = value_set[i];
    if( initialize_one( value ) == false ) {
      --i;
    }
  }
#endif
}

void print_to_file( std::vector<Value>& value_set, std::string filename, bool filter = true);

void filter_stopped( std::vector<Value>& value_set, std::vector<Value>& value_set_result );

int main(int argc, char** argv) {

  int nGes = SIZE;

  // crfs nSteps anpassen: maximale Schritte sind bestimmt durch längste Distanz
  // startpunkte-tischkante
  //                      und minmale Geschwindigkeit, sowie Zeitschrit
  // crfs  minimale Geschwindigkeit 20 km/h *3.6 -> m/s
  //      maximaler Abstand x=0.381;y=-3.0;z=0.4; bis x=1.525;y=2.74; z=0.0;
  //      schiefer wurf berechnen mit anfangsgeschw. wie oben, start- und
  //      endpunkte wie oben
  //      daraus dann anzahl der schritte abschätzen
  int nSteps = 32000;

  auto seed = time(NULL);
#ifdef _WIN32
  srand((unsigned)seed);
  printf("Windows version\n");
#else
  srand(seed);
  printf("Linux version\n");
#endif

  std::vector<Value> value_set;
  std::vector<Value> value_set_result;
  printf("size of value is %d MiB\n", sizeof(Value) / (1024 * 1024));

  // Produktionsschleife über das Hauptprogramm
  //for (int index = 0; index < nIter; index++) {
    initialize_all(value_set, nGes);

    DEBUG_PRINT("Calling kernel");
    int test = nSteps;
    do {
      int size = value_set.size();
      for (int idx=0;idx < size;++idx) {
    	Value& value = value_set[idx];
	if  ( value.isStop ) {
	  continue;
	}
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
    	float xnow;
    	float ynow;
    	float znow;
    	float vxnow;
    	float vynow;
    	float vznow;
    	value.posmov.x = xnow = xlast + vxlast * tt_dt;
    	value.posmov.y = ynow = ylast + vylast * tt_dt;
    	value.posmov.z = znow = zlast + vzlast * tt_dt;
    	value.posmov.vx = vxnow = vxlast + dydx_vx * tt_dt;
    	value.posmov.vy = vynow = vylast + dydx_vy * tt_dt;
    	value.posmov.vz = vznow = vzlast + dydx_vz * tt_dt;
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
	    value.isStop = 1;

	  }
	}
	else if ((zlast < 0.0) && (znow > 0.0) && (xnow > 0.0) && (ynow > 0.0)) {
	  // abort if ball crosses the surface from beneath and is under the table (is
	  // not if it is in front of the table)
	  float t = -zlast / (znow - zlast);
	  float xs = xlast + t * (xnow - xlast);
	  float ys = ylast + t * (ynow - ylast);
	  float zs = zlast + t * (znow - zlast);
#if 1
	  if ((ys > tableL2) && (xs < tableW)) {
	    // von unten getroffen
	    // printf("Ball trifft Tisch von unten \n");
	  }
#endif
	  value.isStop = 1;
	}

       	else if ((ynow > tableL2) && (ylast < tableL2)) {
	  // abort if ball hits the net or passes to high
	  if (znow < netzH) {
	    value.isStop = 1;  // im netz
	  }
	  if (znow > netzH + 0.3) {
	    value.isStop = 1;  // zu hoch
	  }
	}
      }


      if ( !(test % 100 ) ) {
	filter_stopped( value_set, value_set_result );
	
	printf("steps left %d sr %d\n", test, value_set.size() );
      }

      --test;
    } while (test && value_set.size());
    DEBUG_PRINT("done\n");


#if 1
    string prefix = "Results.";
    string index_number = to_string( 0 );
    string postfix = ".txt";
    string filename = prefix + index_number + postfix;
    print_to_file( value_set_result, filename );
    value_set_result.clear();
    print_to_file( value_set, filename + ".remaining", false );
#endif
    //diagnostics.collect_information( value_set_result );
    
  //}
  // Ende Produktionsschleife
  return 0;
}

#if 1
void print_to_file( std::vector<Value>& value_set, std::string filename, bool filter ){
  ofstream myfile(filename);
  int k = 0;
  for (int i = 0; i < value_set.size(); i++) {
    if ((value_set[i].vEnd != 0.0) && (value_set[i].end.vx != 0.0) &&
	(value_set[i].end.vy != 0.0)) {
      k = k + 1;
    }
  }
  myfile << k << endl;
  printf("k %d\n", k);
  for (int i = 0; i < value_set.size(); i++) {
    if ( filter ) {
      if (!(
	  (value_set[i].vEnd != 0.0) && (value_set[i].end.vx != 0.0) &&
	  (value_set[i].end.vy != 0.0))
	) {
	continue;
      }
    }
    //		printf("Anfangsposition %f %f
    //%f\n",value_set.start.x[i],value_set.start.y[i],value_set.start.z[i]);
    auto vAnfang = sqrt(value_set[i].start.vx * value_set[i].start.vx +
		   value_set[i].start.vy * value_set[i].start.vy +
		   value_set[i].start.vz * value_set[i].start.vz);
    //		printf("Anfangsgeschwindigkeit %f %f
    //%f\n",value_set.start.vx[i],value_set.start.vy[i],value_set.start.vz[i]);
    //		printf("Endposition %f %f
    //%f\n",value_set.end.x[i],value_set.end.y[i],value_set.end.z[i]);
    //		printf("Endgeschwindigkeit %f %f %f
    //%f\n",value_set.vEnd[i],value_set.end.vx[i],value_set.end.vy[i],value_set.end.vz[i]);
    //		printf("Rotation %f %f %f
    //%f\n",value_set.omega0[i],value_set.omega_x[i],value_set.omega_y[i],value_set.omega_z[i]);
    auto Ekinstart = 0.5 * tt_m * (vAnfang * vAnfang);
    auto Ekinend = 0.5 * tt_m * (value_set[i].vEnd * value_set[i].vEnd);
    auto Erot = 1.0 / 3.0 * tt_m * tt_r * tt_r *
	   (value_set[i].omega0 * value_set[i].omega0);
    //		printf("Kinetische Energie Anfang, Kinetische Energie
    //Ende, Rotationsenergie %f %f\n",Ekinstart,Ekinend,Erot);
    myfile << value_set[i].start.x << " " << value_set[i].start.y << " "
	   << value_set[i].start.z << " " << vAnfang << " "
	   << value_set[i].start.vx << " " << value_set[i].start.vy
	   << " " << value_set[i].start.vz << " " << value_set[i].end.x
	   << " " << value_set[i].end.y << " " << value_set[i].end.z
	   << " " << value_set[i].vEnd << " " << value_set[i].end.vx
	   << " " << value_set[i].end.vy << " " << value_set[i].end.vz
	   << " " << value_set[i].omega0 << " " << value_set[i].omega_x
	   << " " << value_set[i].omega_y << " " << value_set[i].omega_z
	   << " " << Ekinstart << " " << Ekinend << " " << Erot << endl;
  }
}
#endif

void filter_stopped( std::vector<Value>& value_set, 
    std::vector<Value>& value_set_result ){

  auto partition_point = std::partition(value_set.begin(), value_set.end(), 
      [](auto& value)
      {
	return !value.isStop;
      }
  );

  cout << "isStop front" << value_set.front().isStop << endl;
  cout << "isStop pp " << partition_point->isStop << endl;

  auto d = std::distance(value_set.begin(), partition_point);
  cout << "d pp " << d << endl;

  for( auto it = partition_point; it != value_set.end() ; it++ ) {
    value_set_result.push_back( *it );
  }

  if ( false ) {
    // reinitialize
    for( auto it = partition_point; it != value_set.end() ; it++ ) {
      initialize_one( *it );
    }
  }else{
    value_set.resize( d );
  }

  cout << "results " << value_set_result.size() << endl;
}

#if 0
struct Diagnostics {
  Histogram<double> end_vx(-20, 100, 10);
  void collect_information( Value& value_set ) {
    for( int i = 0; i < value_set.size; i++ ) {
      end_vx.collect( value_set.end.vx[i] );
    }
    end_vx.print();
  }
};
#endif

