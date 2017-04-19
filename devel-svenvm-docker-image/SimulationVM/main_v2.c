#include <complex.h>
#include <errno.h>
#include <math.h>
//#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define v_0 1                        // velocity of the particles
#define N 100                        // number of particles
#define L 50                         // length of the square
#define R 1                          // radius of interaction
#define T 40000                      // number of time steps
#define c 100                        // time resolution
#define d_min 1                      // minimum number of strength
#define d_max 2001                   // maxmimum number of strength
#define resolution_of_strength 0.025 // resolution of strength parameter
#define wavevectorx 1                // wave number in x-direction
#define wavevectory 1                // wave number in y-direction
#define waitingtime 10000
#define m_max 100

double rrand();
double scan_to_number();
double randm(double m, double strength);
double radius(double x_1, double x_2, double y_1, double y_2);

// Save input as number
double scan_to_number() {
  double value;
  scanf("%lf", &value);
  return value;
}

// Generate a random number between 0 and 1
double rrand() {
  double random_number1 = (double)rand() / RAND_MAX;
  return random_number1;
}

// Generate a random number between -m/2 and m/2
double randm(double m, double strength) {
  double random_number2 = rrand();
  random_number2 -= 0.5;
  random_number2 *= strength * m;
  return random_number2;
}

void initiate(double x[], double y[], double nx_old[],
              double ny_old[], double nx_new[], double ny_new[],
              double sumnx[], double sumny[], double r[],
              double nx_temp[], double ny_temp[], double v[],
              double complex Ax[], double complex Ay[],
              double complex A1[], double complex Wk[],
              double complex Ax_complex[], double complex Ay_complex[],
              double complex A1_complex[],
              double complex Wk_complex[]) {
  
  for (int i = 0; i < N; i++) {
    double phi = rrand() * 2 * M_PI;
    nx_old[i] = cos(phi);
    ny_old[i] = sin(phi);
    x[i] = rrand() * L;
    y[i] = rrand() * L;
    nx_new[i] = nx_old[i];
    ny_new[i] = ny_old[i];
    sumnx[i] = 0;
    sumny[i] = 0;
    r[i] = 0;
    nx_temp[i] = 0;
    ny_temp[i] = 0;
  }
  for (int i = 0; i < T; i++) {
    v[i] = 0;
    A1[i] = 0;
    Ax[i] = 0;
    Ay[i] = 0;
    Wk[i] = 0;
    A1_complex[i] = 0;
    Ax_complex[i] = 0;
    Ay_complex[i] = 0;
    Wk_complex[i] = 0;
  }
}

void renew(double complex G[3][3], double complex omega[3][3],
           double complex Flux[3][T]) {
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      G[i][j] = 0;
      omega[i][j] = 0;
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < T; j++) {
      Flux[i][j] = 0;
    }
  }
}

void renew2(double complex (*WK_m)[m_max]) {
  int i;
  for (i = 0; i < m_max; i++) {
    (*WK_m)[i] = 0;
  }
}

double radius(double x_1, double x_2, double y_1, double y_2) {
  double absolute_x = fabs(x_1 - x_2);
  double absolute_y = fabs(y_1 - y_2);
  double x_temp;
  double y_temp;
  double r;
  if (x_1 <= x_2) {
    if (y_1 <= y_2) {
      if (absolute_x < L / 2) {
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 - L;
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_temp), 2));
        }
      }
      if (absolute_x > L / 2) {
        x_temp = x_2 - L;
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 - L;
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_temp), 2));
        }
      }
    }
    if (y_1 > y_2) {
      if (absolute_x < L / 2) {
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 + L;
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_temp), 2));
        }
      }
      if (absolute_x > L / 2) {
        x_temp = x_2 - L;
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 + L;
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_temp), 2));
        }
      }
    }
  }
  if (x_1 > x_2) {
    if (y_1 <= y_2) {
      if (absolute_x < L / 2) {
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 - L;
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_temp), 2));
        }
      }
      if (absolute_x > L / 2) {
        x_temp = x_2 + L;
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 - L;
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_temp), 2));
        }
      }
    }
    if (y_1 > y_2) {
      if (absolute_x < L / 2) {
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 + L;
          r = fabs(pow((x_1 - x_2), 2) + pow((y_1 - y_temp), 2));
        }
      }
      if (absolute_x > L / 2) {
        x_temp = x_2 + L;
        if (absolute_y < L / 2) {
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_2), 2));
        }
        if (absolute_y > L / 2) {
          y_temp = y_2 + L;
          r = fabs(pow((x_1 - x_temp), 2) + pow((y_1 - y_temp), 2));
        }
      }
    }
  }
  return r;
}

void get_new_direction(double (*nx_new)[N], double (*ny_new)[N],
                       double (*nx_temp)[N], double (*ny_temp)[N],
                       double (*sumnx)[N], double (*sumny)[N],
                       int first_particle, double m, double strength) {
  double norm = 1 / sqrt(pow((*sumnx)[first_particle], 2) +
                         pow((*sumny)[first_particle], 2));
  double s = randm(m, strength); // random noise
  (*nx_new)[first_particle] =
      (*sumnx)[first_particle] * norm; // standardization of the velocity
  (*ny_new)[first_particle] = (*sumny)[first_particle] * norm;
  (*nx_temp)[first_particle] = (*nx_new)[first_particle];
  (*ny_temp)[first_particle] = (*ny_new)[first_particle];
  (*nx_new)[first_particle] =
      (*nx_temp)[first_particle] * cos(s) - (*ny_temp)[first_particle] * sin(s);
  (*ny_new)[first_particle] =
      (*nx_temp)[first_particle] * sin(s) + (*ny_temp)[first_particle] * cos(s);
}

void get_new_position(double (*nx_new)[N], double (*ny_new)[N],
                      double (*nx_old)[N], double (*ny_old)[N], double (*x)[N],
                      double (*y)[N], double tau) {
  int i;
  for (i = 0; i < N; i++) {
    (*nx_old)[i] = (*nx_new)[i];
    (*ny_old)[i] = (*ny_new)[i];
  }
  for (i = 0; i < N; i++) {
    (*x)[i] = (*x)[i] + v_0 * (*nx_old)[i] * tau;
    (*y)[i] = (*y)[i] + v_0 * (*ny_old)[i] * tau;
  }
}

void put_back_to_domain(double (*x)[N], double (*y)[N]) {
  int i;
  for (i = 0; i < N; i++) {
    while ((*x)[i] < 0) {
      (*x)[i] = (*x)[i] + L;
    }
    while ((*y)[i] < 0) {
      (*y)[i] = (*y)[i] + L;
    }
    while ((*x)[i] >= L) {
      (*x)[i] = fmod((*x)[i], L);
    }
    while ((*y)[i] >= L) {
      (*y)[i] = fmod((*y)[i], L);
    }
  }
}

// calculates the total velocity during time step "time"
void get_total_velocity(double nx_old[], double ny_old[], double v[],
                        int time) {
  int i = 0;
  double nxsum = 0;
  double nysum = 0;
  for (i = 0; i < N; i++) {
    nxsum += nx_old[i];
    nysum += ny_old[i];
  }
  v[time] = sqrt(pow(nxsum, 2) + pow(nysum, 2)) / N;
}

int main() {
  // Initiate the random numbers generator
  srand(1);
  // Initiate variables
  int i, j, l, t, p, h; // indices
  int time;
  int first_particle;
  int other_particle;
  double nx_old[N];
  double ny_old[N];
  double x[N];
  double y[N];
  double nx_new[N];
  double ny_new[N];
  double sumnx[N];
  double sumny[N];
  double nx_temp[N];
  double ny_temp[N];
  double r[N];
  double v[T];
  double complex Ax[T], Ay[T], A1[T], Wk[T];
  double complex Ax_complex[T], Ay_complex[T], A1_complex[T],
      Wk_complex[T];                   // konjugiert komplex
  double complex G[3][3], omega[3][3]; // ueberpruebfbare Matrizen
  double complex Flux[3][T];           // Flux Matrix
  double nxsum;
  double nysum;
  double tau;      // time step
  double area;     // area
  double m;        // maximum noise
  double s;        // noise
  double phi;      // angle of norm vector
  double strength; // strength of the noise
  double norm;
  double v_total;
  double complex A1_average, Ax_average, Ay_average;
  double complex A1_average_complex, Ax_average_complex, Ay_average_complex;
  double kx = wavevectorx * 2 * M_PI / L, ky = wavevectory * 2 * M_PI / L;
  double complex WK_m[m_max];
  double k = sqrt(pow(kx, 2) + pow(ky, 2));
  char str[10];
  FILE *fp, *fp2, *fp3, *fp4;
  // Functions

  fp = fopen("controllparameter.csv", "w");
  fp3 = fopen("suszeptibility.csv", "w");
  fp4 = fopen("flux.csv", "w");

  // get the maximum of the noise
  area = L * L;
  m = M_PI * R * R * N / area;
  printf("m=%f\n", m);
  printf("kx=%f	", kx);
  printf("ky=%f\n", ky);
  // get the value of the time steps
  printf("Enter time step tau\n");
  tau = scan_to_number();
  for (l = d_min; l < d_max; l++) {
    // initiate the arrays with random values
    initiate(x, y, nx_old, ny_old, nx_new, ny_new, sumnx, sumny, r,
             nx_temp, ny_temp, v, Ax, Ay, A1,Wk, Ax_complex,
             Ay_complex, A1_complex, Wk_complex);
    strength = l * resolution_of_strength;
    v_total = 0;
    A1_average = 0;
    Ax_average = 0;
    Ay_average = 0;
    A1_average_complex = 0;
    Ax_average_complex = 0;
    Ay_average_complex = 0;
    renew(G, omega, Flux);
    renew2(&WK_m);
    sprintf(str, "vorticity%03f,%d,%d.csv", strength * m, wavevectorx,
            wavevectory);
    fp2 = fopen(str, "w");
    for (time = 0; time < T; time++) {
      for (first_particle = 0; first_particle < N; first_particle++) {
        sumnx[first_particle] = nx_old[first_particle];
        sumny[first_particle] = ny_old[first_particle];
        // loop over all particles to get the distance from each one to other
        // particle
        for (other_particle = 0; other_particle < N; other_particle++) {
          if (other_particle != first_particle) {
            r[other_particle] = radius(x[first_particle], x[other_particle],
                                       y[first_particle], y[other_particle]);
            r[other_particle] = sqrt(r[other_particle]);
            // if the other particle is in reach of the first particle add its
            // velocity to sumnx/sumny
            if (r[other_particle] <= R) {
              sumnx[first_particle] += nx_old[other_particle];
              sumny[first_particle] += ny_old[other_particle];
            }
          }
        }
        get_new_direction(
            &nx_new, &ny_new, &nx_temp, &ny_temp, &sumnx, &sumny,
            first_particle, m,
            strength); // calculates new directory with random interference
      }
      get_new_position(
          &nx_new, &ny_new, &nx_old, &ny_old, &x, &y,
          tau); // calculates new position of each particle based on v_0 and tau
      put_back_to_domain(
          &x, &y); // applies periodic boundary conditions for all particles
      if (time >= waitingtime) {
        if (fmod(time, 1) == 0) {
          get_total_velocity(nx_old, ny_old, v, time);
        }
      }
      for (j = 0; j < N; j++) {
        A1[time] +=
            (cos(kx * x[j] + ky * y[j]) + I * sin(kx * x[j] + ky * y[j]));
        Ax[time] +=
            (cos(kx * x[j] + ky * y[j]) + I * sin(kx * x[j] + ky * y[j])) *
            nx_old[j] * v_0;
        Ay[time] +=
            (cos(kx * x[j] + ky * y[j]) + I * sin(kx * x[j] + ky * y[j])) *
            ny_old[j] * v_0;
        A1_complex[time] +=
            (cos(kx * x[j] + ky * y[j]) - I * sin(kx * x[j] + ky * y[j]));
        Ax_complex[time] +=
            (cos(kx * x[j] + ky * y[j]) - I * sin(kx * x[j] + ky * y[j])) *
            nx_old[j] * v_0;
        Ay_complex[time] +=
            (cos(kx * x[j] + ky * y[j]) - I * sin(kx * x[j] + ky * y[j])) *
            ny_old[j] * v_0;
      }
      Wk[time] = kx * Ay[time] - ky * Ax[time];
      Wk_complex[time] = kx * Ay_complex[time] - ky * Ax_complex[time];
    }

    for (t = 0; t < T; t++) {
      v_total += v[t];
      A1_average += A1[t];
      Ax_average += Ax[t];
      Ay_average += Ay[t];
      A1_average_complex += A1_complex[t];
      Ax_average_complex += Ax_complex[t];
      Ay_average_complex += Ay_complex[t];
    }
    for (t = waitingtime; t < T - 1; t++) {
      Flux[0][t] = -1 / tau * I * (A1_complex[t] - A1_complex[t + 1]);
      Flux[1][t] = -1 / tau * I * (Ax_complex[t] - Ax_complex[t + 1]);
      Flux[2][t] = -1 / tau * I * (Ay_complex[t] - Ay_complex[t + 1]);
    }
    A1_average /= T;
    Ax_average /= T;
    Ay_average /= T;
    A1_average_complex /= T;
    Ax_average_complex /= T;
    Ay_average_complex /= T;
    // printf("A1_average= %f %+fi\n", creal(A1_average), cimag(A1_average));
    // printf("Ax_average= %f %+fi\n", creal(Ax_average), cimag(Ax_average));
    // printf("Ay_average= %f %+fi\n", creal(Ay_average), cimag(Ay_average));
    v_total /= (T - waitingtime);
    printf("noise = [%10.4f,%10.4f]", -strength * m / 2, strength * m / 2);
    printf("v_total= %f strength= %d\n", v_total, l);
    fprintf(fp, "%f;%f\n", v_total, strength * m);

    for (j = 0; j < m_max; j += 1) {

      p = 0;
      for (i = waitingtime; i < T - j; i++) {
        WK_m[j] += Wk[i] * Wk_complex[i + j];
        p += 1;
      }
      WK_m[j] /= p;
      fprintf(fp2, "%d;%f;%f;%f;%f\n", j, creal(WK_m[j]), cimag(WK_m[j]),
              log(creal(WK_m[j])), log(cimag(WK_m[j])));
    }

    p = 0;
    for (t = waitingtime; t < T; t++) {
      G[0][0] += 1 / pow(L, 2) * (A1_complex[t] - A1_average_complex) *
                 (A1[t] - A1_average);
      G[1][1] += 1 / pow(L, 2) * (Ax_complex[t] - Ax_average_complex) *
                 (Ax[t] - Ax_average);
      G[2][2] += 1 / pow(L, 2) * (Ay_complex[t] - Ay_average_complex) *
                 (Ay[t] - Ay_average);
      G[0][1] += 1 / pow(L, 2) * (A1_complex[t] - A1_average_complex) *
                 (Ax[t] - Ax_average);
      G[1][0] += 1 / pow(L, 2) * (Ax_complex[t] - Ax_average_complex) *
                 (A1[t] - A1_average);
      G[0][2] += 1 / pow(L, 2) * (A1_complex[t] - A1_average_complex) *
                 (Ay[t] - Ay_average);
      G[2][0] += 1 / pow(L, 2) * (Ay_complex[t] - Ay_average_complex) *
                 (A1[t] - A1_average);
      G[1][2] += 1 / pow(L, 2) * (Ax_complex[t] - Ax_average_complex) *
                 (Ay[t] - Ay_average);
      G[2][1] += 1 / pow(L, 2) * (Ay_complex[t] - Ay_average_complex) *
                 (Ax[t] - Ax_average);

      p += 1;
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        G[i][j] /= p;
      }
    }
    // for(i=0;i<3;i++){
    // for(j=0;j<3;j++){
    // printf("G[%d][%d]=%f %+fi, p= %d\n",i,j,creal(G[i][j]),
    // cimag(G[i][j]),p);

    //}
    //}

    p = 0;
    for (t = waitingtime; t < T; t++) {
      omega[0][0] += 1 / (pow(L, 2) * k) * Flux[0][t] * A1[t];
      omega[1][1] += 1 / (pow(L, 2) * k) * Flux[1][t] * Ax[t];
      omega[2][2] += 1 / (pow(L, 2) * k) * Flux[2][t] * Ay[t];
      omega[0][1] += 1 / (pow(L, 2) * k) * Flux[0][t] * Ax[t];
      omega[1][0] += 1 / (pow(L, 2) * k) * Flux[1][t] * A1[t];
      omega[0][2] += 1 / (pow(L, 2) * k) * Flux[0][t] * Ay[t];
      omega[2][0] += 1 / (pow(L, 2) * k) * Flux[2][t] * A1[t];
      omega[1][2] += 1 / (pow(L, 2) * k) * Flux[1][t] * Ay[t];
      omega[2][1] += 1 / (pow(L, 2) * k) * Flux[2][t] * Ax[t];
      p += 1;
    }

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        omega[i][j] /= p;
      }
    }

    // for(i=0;i<3;i++){
    // for(j=0;j<3;j++){
    // printf("omega[%d][%d]=%f %+fi, p= %d\n",i,j,creal(omega[i][j]),
    // cimag(omega[i][j]),p);

    //}
    //}

    fprintf(fp3, "%f;%f;%f;", strength * m, creal(G[0][0]), cimag(G[0][0]));
    fprintf(fp3, "%f;%f;%f;%f;", creal(G[0][1]), cimag(G[0][1]), creal(G[1][0]),
            cimag(G[1][0]));
    fprintf(fp3, "%f;%f;%f;%f;", creal(G[0][2]), cimag(G[0][2]), creal(G[2][0]),
            cimag(G[2][0]));
    fprintf(fp3, "%f;%f;%f;%f;", creal(G[2][1]), cimag(G[2][1]), creal(G[1][2]),
            cimag(G[1][2]));
    fprintf(fp3, "%f;%f;%f;%f\n", creal(G[1][1]), cimag(G[1][1]),
            creal(G[2][2]), cimag(G[2][2]));

    fprintf(fp4, "%f;%f;%f;", strength * m, creal(omega[0][0]),
            cimag(omega[0][0]));
    fprintf(fp4, "%f;%f;%f;%f;", creal(omega[0][1]), cimag(omega[0][1]),
            creal(omega[1][0]), cimag(omega[1][0]));
    fprintf(fp4, "%f;%f;%f;%f;", creal(omega[0][2]), cimag(omega[0][2]),
            creal(omega[2][0]), cimag(omega[2][0]));
    fprintf(fp4, "%f;%f;%f;%f;", creal(omega[2][1]), cimag(omega[2][1]),
            creal(omega[1][2]), cimag(omega[1][2]));
    fprintf(fp4, "%f;%f;%f;%f\n", creal(omega[1][1]), cimag(omega[1][1]),
            creal(omega[2][2]), cimag(omega[2][2]));

    fclose(fp2);
  }
  fclose(fp);
  fclose(fp3);
  fclose(fp4);
}
