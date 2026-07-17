#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2052741168441824565) {
   out_2052741168441824565[0] = delta_x[0] + nom_x[0];
   out_2052741168441824565[1] = delta_x[1] + nom_x[1];
   out_2052741168441824565[2] = delta_x[2] + nom_x[2];
   out_2052741168441824565[3] = delta_x[3] + nom_x[3];
   out_2052741168441824565[4] = delta_x[4] + nom_x[4];
   out_2052741168441824565[5] = delta_x[5] + nom_x[5];
   out_2052741168441824565[6] = delta_x[6] + nom_x[6];
   out_2052741168441824565[7] = delta_x[7] + nom_x[7];
   out_2052741168441824565[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_832929031110274937) {
   out_832929031110274937[0] = -nom_x[0] + true_x[0];
   out_832929031110274937[1] = -nom_x[1] + true_x[1];
   out_832929031110274937[2] = -nom_x[2] + true_x[2];
   out_832929031110274937[3] = -nom_x[3] + true_x[3];
   out_832929031110274937[4] = -nom_x[4] + true_x[4];
   out_832929031110274937[5] = -nom_x[5] + true_x[5];
   out_832929031110274937[6] = -nom_x[6] + true_x[6];
   out_832929031110274937[7] = -nom_x[7] + true_x[7];
   out_832929031110274937[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7850044567525725825) {
   out_7850044567525725825[0] = 1.0;
   out_7850044567525725825[1] = 0.0;
   out_7850044567525725825[2] = 0.0;
   out_7850044567525725825[3] = 0.0;
   out_7850044567525725825[4] = 0.0;
   out_7850044567525725825[5] = 0.0;
   out_7850044567525725825[6] = 0.0;
   out_7850044567525725825[7] = 0.0;
   out_7850044567525725825[8] = 0.0;
   out_7850044567525725825[9] = 0.0;
   out_7850044567525725825[10] = 1.0;
   out_7850044567525725825[11] = 0.0;
   out_7850044567525725825[12] = 0.0;
   out_7850044567525725825[13] = 0.0;
   out_7850044567525725825[14] = 0.0;
   out_7850044567525725825[15] = 0.0;
   out_7850044567525725825[16] = 0.0;
   out_7850044567525725825[17] = 0.0;
   out_7850044567525725825[18] = 0.0;
   out_7850044567525725825[19] = 0.0;
   out_7850044567525725825[20] = 1.0;
   out_7850044567525725825[21] = 0.0;
   out_7850044567525725825[22] = 0.0;
   out_7850044567525725825[23] = 0.0;
   out_7850044567525725825[24] = 0.0;
   out_7850044567525725825[25] = 0.0;
   out_7850044567525725825[26] = 0.0;
   out_7850044567525725825[27] = 0.0;
   out_7850044567525725825[28] = 0.0;
   out_7850044567525725825[29] = 0.0;
   out_7850044567525725825[30] = 1.0;
   out_7850044567525725825[31] = 0.0;
   out_7850044567525725825[32] = 0.0;
   out_7850044567525725825[33] = 0.0;
   out_7850044567525725825[34] = 0.0;
   out_7850044567525725825[35] = 0.0;
   out_7850044567525725825[36] = 0.0;
   out_7850044567525725825[37] = 0.0;
   out_7850044567525725825[38] = 0.0;
   out_7850044567525725825[39] = 0.0;
   out_7850044567525725825[40] = 1.0;
   out_7850044567525725825[41] = 0.0;
   out_7850044567525725825[42] = 0.0;
   out_7850044567525725825[43] = 0.0;
   out_7850044567525725825[44] = 0.0;
   out_7850044567525725825[45] = 0.0;
   out_7850044567525725825[46] = 0.0;
   out_7850044567525725825[47] = 0.0;
   out_7850044567525725825[48] = 0.0;
   out_7850044567525725825[49] = 0.0;
   out_7850044567525725825[50] = 1.0;
   out_7850044567525725825[51] = 0.0;
   out_7850044567525725825[52] = 0.0;
   out_7850044567525725825[53] = 0.0;
   out_7850044567525725825[54] = 0.0;
   out_7850044567525725825[55] = 0.0;
   out_7850044567525725825[56] = 0.0;
   out_7850044567525725825[57] = 0.0;
   out_7850044567525725825[58] = 0.0;
   out_7850044567525725825[59] = 0.0;
   out_7850044567525725825[60] = 1.0;
   out_7850044567525725825[61] = 0.0;
   out_7850044567525725825[62] = 0.0;
   out_7850044567525725825[63] = 0.0;
   out_7850044567525725825[64] = 0.0;
   out_7850044567525725825[65] = 0.0;
   out_7850044567525725825[66] = 0.0;
   out_7850044567525725825[67] = 0.0;
   out_7850044567525725825[68] = 0.0;
   out_7850044567525725825[69] = 0.0;
   out_7850044567525725825[70] = 1.0;
   out_7850044567525725825[71] = 0.0;
   out_7850044567525725825[72] = 0.0;
   out_7850044567525725825[73] = 0.0;
   out_7850044567525725825[74] = 0.0;
   out_7850044567525725825[75] = 0.0;
   out_7850044567525725825[76] = 0.0;
   out_7850044567525725825[77] = 0.0;
   out_7850044567525725825[78] = 0.0;
   out_7850044567525725825[79] = 0.0;
   out_7850044567525725825[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_756315423102719430) {
   out_756315423102719430[0] = state[0];
   out_756315423102719430[1] = state[1];
   out_756315423102719430[2] = state[2];
   out_756315423102719430[3] = state[3];
   out_756315423102719430[4] = state[4];
   out_756315423102719430[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_756315423102719430[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_756315423102719430[7] = state[7];
   out_756315423102719430[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6464791029044448359) {
   out_6464791029044448359[0] = 1;
   out_6464791029044448359[1] = 0;
   out_6464791029044448359[2] = 0;
   out_6464791029044448359[3] = 0;
   out_6464791029044448359[4] = 0;
   out_6464791029044448359[5] = 0;
   out_6464791029044448359[6] = 0;
   out_6464791029044448359[7] = 0;
   out_6464791029044448359[8] = 0;
   out_6464791029044448359[9] = 0;
   out_6464791029044448359[10] = 1;
   out_6464791029044448359[11] = 0;
   out_6464791029044448359[12] = 0;
   out_6464791029044448359[13] = 0;
   out_6464791029044448359[14] = 0;
   out_6464791029044448359[15] = 0;
   out_6464791029044448359[16] = 0;
   out_6464791029044448359[17] = 0;
   out_6464791029044448359[18] = 0;
   out_6464791029044448359[19] = 0;
   out_6464791029044448359[20] = 1;
   out_6464791029044448359[21] = 0;
   out_6464791029044448359[22] = 0;
   out_6464791029044448359[23] = 0;
   out_6464791029044448359[24] = 0;
   out_6464791029044448359[25] = 0;
   out_6464791029044448359[26] = 0;
   out_6464791029044448359[27] = 0;
   out_6464791029044448359[28] = 0;
   out_6464791029044448359[29] = 0;
   out_6464791029044448359[30] = 1;
   out_6464791029044448359[31] = 0;
   out_6464791029044448359[32] = 0;
   out_6464791029044448359[33] = 0;
   out_6464791029044448359[34] = 0;
   out_6464791029044448359[35] = 0;
   out_6464791029044448359[36] = 0;
   out_6464791029044448359[37] = 0;
   out_6464791029044448359[38] = 0;
   out_6464791029044448359[39] = 0;
   out_6464791029044448359[40] = 1;
   out_6464791029044448359[41] = 0;
   out_6464791029044448359[42] = 0;
   out_6464791029044448359[43] = 0;
   out_6464791029044448359[44] = 0;
   out_6464791029044448359[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6464791029044448359[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6464791029044448359[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6464791029044448359[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6464791029044448359[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6464791029044448359[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6464791029044448359[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6464791029044448359[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6464791029044448359[53] = -9.8100000000000005*dt;
   out_6464791029044448359[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6464791029044448359[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6464791029044448359[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6464791029044448359[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6464791029044448359[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6464791029044448359[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6464791029044448359[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6464791029044448359[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6464791029044448359[62] = 0;
   out_6464791029044448359[63] = 0;
   out_6464791029044448359[64] = 0;
   out_6464791029044448359[65] = 0;
   out_6464791029044448359[66] = 0;
   out_6464791029044448359[67] = 0;
   out_6464791029044448359[68] = 0;
   out_6464791029044448359[69] = 0;
   out_6464791029044448359[70] = 1;
   out_6464791029044448359[71] = 0;
   out_6464791029044448359[72] = 0;
   out_6464791029044448359[73] = 0;
   out_6464791029044448359[74] = 0;
   out_6464791029044448359[75] = 0;
   out_6464791029044448359[76] = 0;
   out_6464791029044448359[77] = 0;
   out_6464791029044448359[78] = 0;
   out_6464791029044448359[79] = 0;
   out_6464791029044448359[80] = 1;
}
void h_25(double *state, double *unused, double *out_208023842493101327) {
   out_208023842493101327[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2675361473209965986) {
   out_2675361473209965986[0] = 0;
   out_2675361473209965986[1] = 0;
   out_2675361473209965986[2] = 0;
   out_2675361473209965986[3] = 0;
   out_2675361473209965986[4] = 0;
   out_2675361473209965986[5] = 0;
   out_2675361473209965986[6] = 1;
   out_2675361473209965986[7] = 0;
   out_2675361473209965986[8] = 0;
}
void h_24(double *state, double *unused, double *out_4630201838301252563) {
   out_4630201838301252563[0] = state[4];
   out_4630201838301252563[1] = state[5];
}
void H_24(double *state, double *unused, double *out_882564125592357150) {
   out_882564125592357150[0] = 0;
   out_882564125592357150[1] = 0;
   out_882564125592357150[2] = 0;
   out_882564125592357150[3] = 0;
   out_882564125592357150[4] = 1;
   out_882564125592357150[5] = 0;
   out_882564125592357150[6] = 0;
   out_882564125592357150[7] = 0;
   out_882564125592357150[8] = 0;
   out_882564125592357150[9] = 0;
   out_882564125592357150[10] = 0;
   out_882564125592357150[11] = 0;
   out_882564125592357150[12] = 0;
   out_882564125592357150[13] = 0;
   out_882564125592357150[14] = 1;
   out_882564125592357150[15] = 0;
   out_882564125592357150[16] = 0;
   out_882564125592357150[17] = 0;
}
void h_30(double *state, double *unused, double *out_3155749832848586288) {
   out_3155749832848586288[0] = state[4];
}
void H_30(double *state, double *unused, double *out_157028514702717359) {
   out_157028514702717359[0] = 0;
   out_157028514702717359[1] = 0;
   out_157028514702717359[2] = 0;
   out_157028514702717359[3] = 0;
   out_157028514702717359[4] = 1;
   out_157028514702717359[5] = 0;
   out_157028514702717359[6] = 0;
   out_157028514702717359[7] = 0;
   out_157028514702717359[8] = 0;
}
void h_26(double *state, double *unused, double *out_9035169518901918074) {
   out_9035169518901918074[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6416864792084022210) {
   out_6416864792084022210[0] = 0;
   out_6416864792084022210[1] = 0;
   out_6416864792084022210[2] = 0;
   out_6416864792084022210[3] = 0;
   out_6416864792084022210[4] = 0;
   out_6416864792084022210[5] = 0;
   out_6416864792084022210[6] = 0;
   out_6416864792084022210[7] = 1;
   out_6416864792084022210[8] = 0;
}
void h_27(double *state, double *unused, double *out_2604528260776752056) {
   out_2604528260776752056[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2331791826503142270) {
   out_2331791826503142270[0] = 0;
   out_2331791826503142270[1] = 0;
   out_2331791826503142270[2] = 0;
   out_2331791826503142270[3] = 1;
   out_2331791826503142270[4] = 0;
   out_2331791826503142270[5] = 0;
   out_2331791826503142270[6] = 0;
   out_2331791826503142270[7] = 0;
   out_2331791826503142270[8] = 0;
}
void h_29(double *state, double *unused, double *out_8157423100509431933) {
   out_8157423100509431933[0] = state[1];
}
void H_29(double *state, double *unused, double *out_353202829611674825) {
   out_353202829611674825[0] = 0;
   out_353202829611674825[1] = 1;
   out_353202829611674825[2] = 0;
   out_353202829611674825[3] = 0;
   out_353202829611674825[4] = 0;
   out_353202829611674825[5] = 0;
   out_353202829611674825[6] = 0;
   out_353202829611674825[7] = 0;
   out_353202829611674825[8] = 0;
}
void h_28(double *state, double *unused, double *out_2397145006884093589) {
   out_2397145006884093589[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4729196187457855749) {
   out_4729196187457855749[0] = 1;
   out_4729196187457855749[1] = 0;
   out_4729196187457855749[2] = 0;
   out_4729196187457855749[3] = 0;
   out_4729196187457855749[4] = 0;
   out_4729196187457855749[5] = 0;
   out_4729196187457855749[6] = 0;
   out_4729196187457855749[7] = 0;
   out_4729196187457855749[8] = 0;
}
void h_31(double *state, double *unused, double *out_6978859068843452263) {
   out_6978859068843452263[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7043072894317373686) {
   out_7043072894317373686[0] = 0;
   out_7043072894317373686[1] = 0;
   out_7043072894317373686[2] = 0;
   out_7043072894317373686[3] = 0;
   out_7043072894317373686[4] = 0;
   out_7043072894317373686[5] = 0;
   out_7043072894317373686[6] = 0;
   out_7043072894317373686[7] = 0;
   out_7043072894317373686[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_2052741168441824565) {
  err_fun(nom_x, delta_x, out_2052741168441824565);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_832929031110274937) {
  inv_err_fun(nom_x, true_x, out_832929031110274937);
}
void car_H_mod_fun(double *state, double *out_7850044567525725825) {
  H_mod_fun(state, out_7850044567525725825);
}
void car_f_fun(double *state, double dt, double *out_756315423102719430) {
  f_fun(state,  dt, out_756315423102719430);
}
void car_F_fun(double *state, double dt, double *out_6464791029044448359) {
  F_fun(state,  dt, out_6464791029044448359);
}
void car_h_25(double *state, double *unused, double *out_208023842493101327) {
  h_25(state, unused, out_208023842493101327);
}
void car_H_25(double *state, double *unused, double *out_2675361473209965986) {
  H_25(state, unused, out_2675361473209965986);
}
void car_h_24(double *state, double *unused, double *out_4630201838301252563) {
  h_24(state, unused, out_4630201838301252563);
}
void car_H_24(double *state, double *unused, double *out_882564125592357150) {
  H_24(state, unused, out_882564125592357150);
}
void car_h_30(double *state, double *unused, double *out_3155749832848586288) {
  h_30(state, unused, out_3155749832848586288);
}
void car_H_30(double *state, double *unused, double *out_157028514702717359) {
  H_30(state, unused, out_157028514702717359);
}
void car_h_26(double *state, double *unused, double *out_9035169518901918074) {
  h_26(state, unused, out_9035169518901918074);
}
void car_H_26(double *state, double *unused, double *out_6416864792084022210) {
  H_26(state, unused, out_6416864792084022210);
}
void car_h_27(double *state, double *unused, double *out_2604528260776752056) {
  h_27(state, unused, out_2604528260776752056);
}
void car_H_27(double *state, double *unused, double *out_2331791826503142270) {
  H_27(state, unused, out_2331791826503142270);
}
void car_h_29(double *state, double *unused, double *out_8157423100509431933) {
  h_29(state, unused, out_8157423100509431933);
}
void car_H_29(double *state, double *unused, double *out_353202829611674825) {
  H_29(state, unused, out_353202829611674825);
}
void car_h_28(double *state, double *unused, double *out_2397145006884093589) {
  h_28(state, unused, out_2397145006884093589);
}
void car_H_28(double *state, double *unused, double *out_4729196187457855749) {
  H_28(state, unused, out_4729196187457855749);
}
void car_h_31(double *state, double *unused, double *out_6978859068843452263) {
  h_31(state, unused, out_6978859068843452263);
}
void car_H_31(double *state, double *unused, double *out_7043072894317373686) {
  H_31(state, unused, out_7043072894317373686);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
