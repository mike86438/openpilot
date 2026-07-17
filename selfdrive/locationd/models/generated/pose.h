#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2062215461122009820);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1674122598517831978);
void pose_H_mod_fun(double *state, double *out_2615016230612845443);
void pose_f_fun(double *state, double dt, double *out_2589489788835022049);
void pose_F_fun(double *state, double dt, double *out_8716816819534034926);
void pose_h_4(double *state, double *unused, double *out_4969538978811489115);
void pose_H_4(double *state, double *unused, double *out_5889238309403794696);
void pose_h_10(double *state, double *unused, double *out_2007694217068845080);
void pose_H_10(double *state, double *unused, double *out_1823393631919099076);
void pose_h_13(double *state, double *unused, double *out_6769157992845548257);
void pose_H_13(double *state, double *unused, double *out_2676964484071461895);
void pose_h_14(double *state, double *unused, double *out_9071104771947762329);
void pose_H_14(double *state, double *unused, double *out_1925997453064310167);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}