#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2062215461122009820) {
   out_2062215461122009820[0] = delta_x[0] + nom_x[0];
   out_2062215461122009820[1] = delta_x[1] + nom_x[1];
   out_2062215461122009820[2] = delta_x[2] + nom_x[2];
   out_2062215461122009820[3] = delta_x[3] + nom_x[3];
   out_2062215461122009820[4] = delta_x[4] + nom_x[4];
   out_2062215461122009820[5] = delta_x[5] + nom_x[5];
   out_2062215461122009820[6] = delta_x[6] + nom_x[6];
   out_2062215461122009820[7] = delta_x[7] + nom_x[7];
   out_2062215461122009820[8] = delta_x[8] + nom_x[8];
   out_2062215461122009820[9] = delta_x[9] + nom_x[9];
   out_2062215461122009820[10] = delta_x[10] + nom_x[10];
   out_2062215461122009820[11] = delta_x[11] + nom_x[11];
   out_2062215461122009820[12] = delta_x[12] + nom_x[12];
   out_2062215461122009820[13] = delta_x[13] + nom_x[13];
   out_2062215461122009820[14] = delta_x[14] + nom_x[14];
   out_2062215461122009820[15] = delta_x[15] + nom_x[15];
   out_2062215461122009820[16] = delta_x[16] + nom_x[16];
   out_2062215461122009820[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1674122598517831978) {
   out_1674122598517831978[0] = -nom_x[0] + true_x[0];
   out_1674122598517831978[1] = -nom_x[1] + true_x[1];
   out_1674122598517831978[2] = -nom_x[2] + true_x[2];
   out_1674122598517831978[3] = -nom_x[3] + true_x[3];
   out_1674122598517831978[4] = -nom_x[4] + true_x[4];
   out_1674122598517831978[5] = -nom_x[5] + true_x[5];
   out_1674122598517831978[6] = -nom_x[6] + true_x[6];
   out_1674122598517831978[7] = -nom_x[7] + true_x[7];
   out_1674122598517831978[8] = -nom_x[8] + true_x[8];
   out_1674122598517831978[9] = -nom_x[9] + true_x[9];
   out_1674122598517831978[10] = -nom_x[10] + true_x[10];
   out_1674122598517831978[11] = -nom_x[11] + true_x[11];
   out_1674122598517831978[12] = -nom_x[12] + true_x[12];
   out_1674122598517831978[13] = -nom_x[13] + true_x[13];
   out_1674122598517831978[14] = -nom_x[14] + true_x[14];
   out_1674122598517831978[15] = -nom_x[15] + true_x[15];
   out_1674122598517831978[16] = -nom_x[16] + true_x[16];
   out_1674122598517831978[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2615016230612845443) {
   out_2615016230612845443[0] = 1.0;
   out_2615016230612845443[1] = 0.0;
   out_2615016230612845443[2] = 0.0;
   out_2615016230612845443[3] = 0.0;
   out_2615016230612845443[4] = 0.0;
   out_2615016230612845443[5] = 0.0;
   out_2615016230612845443[6] = 0.0;
   out_2615016230612845443[7] = 0.0;
   out_2615016230612845443[8] = 0.0;
   out_2615016230612845443[9] = 0.0;
   out_2615016230612845443[10] = 0.0;
   out_2615016230612845443[11] = 0.0;
   out_2615016230612845443[12] = 0.0;
   out_2615016230612845443[13] = 0.0;
   out_2615016230612845443[14] = 0.0;
   out_2615016230612845443[15] = 0.0;
   out_2615016230612845443[16] = 0.0;
   out_2615016230612845443[17] = 0.0;
   out_2615016230612845443[18] = 0.0;
   out_2615016230612845443[19] = 1.0;
   out_2615016230612845443[20] = 0.0;
   out_2615016230612845443[21] = 0.0;
   out_2615016230612845443[22] = 0.0;
   out_2615016230612845443[23] = 0.0;
   out_2615016230612845443[24] = 0.0;
   out_2615016230612845443[25] = 0.0;
   out_2615016230612845443[26] = 0.0;
   out_2615016230612845443[27] = 0.0;
   out_2615016230612845443[28] = 0.0;
   out_2615016230612845443[29] = 0.0;
   out_2615016230612845443[30] = 0.0;
   out_2615016230612845443[31] = 0.0;
   out_2615016230612845443[32] = 0.0;
   out_2615016230612845443[33] = 0.0;
   out_2615016230612845443[34] = 0.0;
   out_2615016230612845443[35] = 0.0;
   out_2615016230612845443[36] = 0.0;
   out_2615016230612845443[37] = 0.0;
   out_2615016230612845443[38] = 1.0;
   out_2615016230612845443[39] = 0.0;
   out_2615016230612845443[40] = 0.0;
   out_2615016230612845443[41] = 0.0;
   out_2615016230612845443[42] = 0.0;
   out_2615016230612845443[43] = 0.0;
   out_2615016230612845443[44] = 0.0;
   out_2615016230612845443[45] = 0.0;
   out_2615016230612845443[46] = 0.0;
   out_2615016230612845443[47] = 0.0;
   out_2615016230612845443[48] = 0.0;
   out_2615016230612845443[49] = 0.0;
   out_2615016230612845443[50] = 0.0;
   out_2615016230612845443[51] = 0.0;
   out_2615016230612845443[52] = 0.0;
   out_2615016230612845443[53] = 0.0;
   out_2615016230612845443[54] = 0.0;
   out_2615016230612845443[55] = 0.0;
   out_2615016230612845443[56] = 0.0;
   out_2615016230612845443[57] = 1.0;
   out_2615016230612845443[58] = 0.0;
   out_2615016230612845443[59] = 0.0;
   out_2615016230612845443[60] = 0.0;
   out_2615016230612845443[61] = 0.0;
   out_2615016230612845443[62] = 0.0;
   out_2615016230612845443[63] = 0.0;
   out_2615016230612845443[64] = 0.0;
   out_2615016230612845443[65] = 0.0;
   out_2615016230612845443[66] = 0.0;
   out_2615016230612845443[67] = 0.0;
   out_2615016230612845443[68] = 0.0;
   out_2615016230612845443[69] = 0.0;
   out_2615016230612845443[70] = 0.0;
   out_2615016230612845443[71] = 0.0;
   out_2615016230612845443[72] = 0.0;
   out_2615016230612845443[73] = 0.0;
   out_2615016230612845443[74] = 0.0;
   out_2615016230612845443[75] = 0.0;
   out_2615016230612845443[76] = 1.0;
   out_2615016230612845443[77] = 0.0;
   out_2615016230612845443[78] = 0.0;
   out_2615016230612845443[79] = 0.0;
   out_2615016230612845443[80] = 0.0;
   out_2615016230612845443[81] = 0.0;
   out_2615016230612845443[82] = 0.0;
   out_2615016230612845443[83] = 0.0;
   out_2615016230612845443[84] = 0.0;
   out_2615016230612845443[85] = 0.0;
   out_2615016230612845443[86] = 0.0;
   out_2615016230612845443[87] = 0.0;
   out_2615016230612845443[88] = 0.0;
   out_2615016230612845443[89] = 0.0;
   out_2615016230612845443[90] = 0.0;
   out_2615016230612845443[91] = 0.0;
   out_2615016230612845443[92] = 0.0;
   out_2615016230612845443[93] = 0.0;
   out_2615016230612845443[94] = 0.0;
   out_2615016230612845443[95] = 1.0;
   out_2615016230612845443[96] = 0.0;
   out_2615016230612845443[97] = 0.0;
   out_2615016230612845443[98] = 0.0;
   out_2615016230612845443[99] = 0.0;
   out_2615016230612845443[100] = 0.0;
   out_2615016230612845443[101] = 0.0;
   out_2615016230612845443[102] = 0.0;
   out_2615016230612845443[103] = 0.0;
   out_2615016230612845443[104] = 0.0;
   out_2615016230612845443[105] = 0.0;
   out_2615016230612845443[106] = 0.0;
   out_2615016230612845443[107] = 0.0;
   out_2615016230612845443[108] = 0.0;
   out_2615016230612845443[109] = 0.0;
   out_2615016230612845443[110] = 0.0;
   out_2615016230612845443[111] = 0.0;
   out_2615016230612845443[112] = 0.0;
   out_2615016230612845443[113] = 0.0;
   out_2615016230612845443[114] = 1.0;
   out_2615016230612845443[115] = 0.0;
   out_2615016230612845443[116] = 0.0;
   out_2615016230612845443[117] = 0.0;
   out_2615016230612845443[118] = 0.0;
   out_2615016230612845443[119] = 0.0;
   out_2615016230612845443[120] = 0.0;
   out_2615016230612845443[121] = 0.0;
   out_2615016230612845443[122] = 0.0;
   out_2615016230612845443[123] = 0.0;
   out_2615016230612845443[124] = 0.0;
   out_2615016230612845443[125] = 0.0;
   out_2615016230612845443[126] = 0.0;
   out_2615016230612845443[127] = 0.0;
   out_2615016230612845443[128] = 0.0;
   out_2615016230612845443[129] = 0.0;
   out_2615016230612845443[130] = 0.0;
   out_2615016230612845443[131] = 0.0;
   out_2615016230612845443[132] = 0.0;
   out_2615016230612845443[133] = 1.0;
   out_2615016230612845443[134] = 0.0;
   out_2615016230612845443[135] = 0.0;
   out_2615016230612845443[136] = 0.0;
   out_2615016230612845443[137] = 0.0;
   out_2615016230612845443[138] = 0.0;
   out_2615016230612845443[139] = 0.0;
   out_2615016230612845443[140] = 0.0;
   out_2615016230612845443[141] = 0.0;
   out_2615016230612845443[142] = 0.0;
   out_2615016230612845443[143] = 0.0;
   out_2615016230612845443[144] = 0.0;
   out_2615016230612845443[145] = 0.0;
   out_2615016230612845443[146] = 0.0;
   out_2615016230612845443[147] = 0.0;
   out_2615016230612845443[148] = 0.0;
   out_2615016230612845443[149] = 0.0;
   out_2615016230612845443[150] = 0.0;
   out_2615016230612845443[151] = 0.0;
   out_2615016230612845443[152] = 1.0;
   out_2615016230612845443[153] = 0.0;
   out_2615016230612845443[154] = 0.0;
   out_2615016230612845443[155] = 0.0;
   out_2615016230612845443[156] = 0.0;
   out_2615016230612845443[157] = 0.0;
   out_2615016230612845443[158] = 0.0;
   out_2615016230612845443[159] = 0.0;
   out_2615016230612845443[160] = 0.0;
   out_2615016230612845443[161] = 0.0;
   out_2615016230612845443[162] = 0.0;
   out_2615016230612845443[163] = 0.0;
   out_2615016230612845443[164] = 0.0;
   out_2615016230612845443[165] = 0.0;
   out_2615016230612845443[166] = 0.0;
   out_2615016230612845443[167] = 0.0;
   out_2615016230612845443[168] = 0.0;
   out_2615016230612845443[169] = 0.0;
   out_2615016230612845443[170] = 0.0;
   out_2615016230612845443[171] = 1.0;
   out_2615016230612845443[172] = 0.0;
   out_2615016230612845443[173] = 0.0;
   out_2615016230612845443[174] = 0.0;
   out_2615016230612845443[175] = 0.0;
   out_2615016230612845443[176] = 0.0;
   out_2615016230612845443[177] = 0.0;
   out_2615016230612845443[178] = 0.0;
   out_2615016230612845443[179] = 0.0;
   out_2615016230612845443[180] = 0.0;
   out_2615016230612845443[181] = 0.0;
   out_2615016230612845443[182] = 0.0;
   out_2615016230612845443[183] = 0.0;
   out_2615016230612845443[184] = 0.0;
   out_2615016230612845443[185] = 0.0;
   out_2615016230612845443[186] = 0.0;
   out_2615016230612845443[187] = 0.0;
   out_2615016230612845443[188] = 0.0;
   out_2615016230612845443[189] = 0.0;
   out_2615016230612845443[190] = 1.0;
   out_2615016230612845443[191] = 0.0;
   out_2615016230612845443[192] = 0.0;
   out_2615016230612845443[193] = 0.0;
   out_2615016230612845443[194] = 0.0;
   out_2615016230612845443[195] = 0.0;
   out_2615016230612845443[196] = 0.0;
   out_2615016230612845443[197] = 0.0;
   out_2615016230612845443[198] = 0.0;
   out_2615016230612845443[199] = 0.0;
   out_2615016230612845443[200] = 0.0;
   out_2615016230612845443[201] = 0.0;
   out_2615016230612845443[202] = 0.0;
   out_2615016230612845443[203] = 0.0;
   out_2615016230612845443[204] = 0.0;
   out_2615016230612845443[205] = 0.0;
   out_2615016230612845443[206] = 0.0;
   out_2615016230612845443[207] = 0.0;
   out_2615016230612845443[208] = 0.0;
   out_2615016230612845443[209] = 1.0;
   out_2615016230612845443[210] = 0.0;
   out_2615016230612845443[211] = 0.0;
   out_2615016230612845443[212] = 0.0;
   out_2615016230612845443[213] = 0.0;
   out_2615016230612845443[214] = 0.0;
   out_2615016230612845443[215] = 0.0;
   out_2615016230612845443[216] = 0.0;
   out_2615016230612845443[217] = 0.0;
   out_2615016230612845443[218] = 0.0;
   out_2615016230612845443[219] = 0.0;
   out_2615016230612845443[220] = 0.0;
   out_2615016230612845443[221] = 0.0;
   out_2615016230612845443[222] = 0.0;
   out_2615016230612845443[223] = 0.0;
   out_2615016230612845443[224] = 0.0;
   out_2615016230612845443[225] = 0.0;
   out_2615016230612845443[226] = 0.0;
   out_2615016230612845443[227] = 0.0;
   out_2615016230612845443[228] = 1.0;
   out_2615016230612845443[229] = 0.0;
   out_2615016230612845443[230] = 0.0;
   out_2615016230612845443[231] = 0.0;
   out_2615016230612845443[232] = 0.0;
   out_2615016230612845443[233] = 0.0;
   out_2615016230612845443[234] = 0.0;
   out_2615016230612845443[235] = 0.0;
   out_2615016230612845443[236] = 0.0;
   out_2615016230612845443[237] = 0.0;
   out_2615016230612845443[238] = 0.0;
   out_2615016230612845443[239] = 0.0;
   out_2615016230612845443[240] = 0.0;
   out_2615016230612845443[241] = 0.0;
   out_2615016230612845443[242] = 0.0;
   out_2615016230612845443[243] = 0.0;
   out_2615016230612845443[244] = 0.0;
   out_2615016230612845443[245] = 0.0;
   out_2615016230612845443[246] = 0.0;
   out_2615016230612845443[247] = 1.0;
   out_2615016230612845443[248] = 0.0;
   out_2615016230612845443[249] = 0.0;
   out_2615016230612845443[250] = 0.0;
   out_2615016230612845443[251] = 0.0;
   out_2615016230612845443[252] = 0.0;
   out_2615016230612845443[253] = 0.0;
   out_2615016230612845443[254] = 0.0;
   out_2615016230612845443[255] = 0.0;
   out_2615016230612845443[256] = 0.0;
   out_2615016230612845443[257] = 0.0;
   out_2615016230612845443[258] = 0.0;
   out_2615016230612845443[259] = 0.0;
   out_2615016230612845443[260] = 0.0;
   out_2615016230612845443[261] = 0.0;
   out_2615016230612845443[262] = 0.0;
   out_2615016230612845443[263] = 0.0;
   out_2615016230612845443[264] = 0.0;
   out_2615016230612845443[265] = 0.0;
   out_2615016230612845443[266] = 1.0;
   out_2615016230612845443[267] = 0.0;
   out_2615016230612845443[268] = 0.0;
   out_2615016230612845443[269] = 0.0;
   out_2615016230612845443[270] = 0.0;
   out_2615016230612845443[271] = 0.0;
   out_2615016230612845443[272] = 0.0;
   out_2615016230612845443[273] = 0.0;
   out_2615016230612845443[274] = 0.0;
   out_2615016230612845443[275] = 0.0;
   out_2615016230612845443[276] = 0.0;
   out_2615016230612845443[277] = 0.0;
   out_2615016230612845443[278] = 0.0;
   out_2615016230612845443[279] = 0.0;
   out_2615016230612845443[280] = 0.0;
   out_2615016230612845443[281] = 0.0;
   out_2615016230612845443[282] = 0.0;
   out_2615016230612845443[283] = 0.0;
   out_2615016230612845443[284] = 0.0;
   out_2615016230612845443[285] = 1.0;
   out_2615016230612845443[286] = 0.0;
   out_2615016230612845443[287] = 0.0;
   out_2615016230612845443[288] = 0.0;
   out_2615016230612845443[289] = 0.0;
   out_2615016230612845443[290] = 0.0;
   out_2615016230612845443[291] = 0.0;
   out_2615016230612845443[292] = 0.0;
   out_2615016230612845443[293] = 0.0;
   out_2615016230612845443[294] = 0.0;
   out_2615016230612845443[295] = 0.0;
   out_2615016230612845443[296] = 0.0;
   out_2615016230612845443[297] = 0.0;
   out_2615016230612845443[298] = 0.0;
   out_2615016230612845443[299] = 0.0;
   out_2615016230612845443[300] = 0.0;
   out_2615016230612845443[301] = 0.0;
   out_2615016230612845443[302] = 0.0;
   out_2615016230612845443[303] = 0.0;
   out_2615016230612845443[304] = 1.0;
   out_2615016230612845443[305] = 0.0;
   out_2615016230612845443[306] = 0.0;
   out_2615016230612845443[307] = 0.0;
   out_2615016230612845443[308] = 0.0;
   out_2615016230612845443[309] = 0.0;
   out_2615016230612845443[310] = 0.0;
   out_2615016230612845443[311] = 0.0;
   out_2615016230612845443[312] = 0.0;
   out_2615016230612845443[313] = 0.0;
   out_2615016230612845443[314] = 0.0;
   out_2615016230612845443[315] = 0.0;
   out_2615016230612845443[316] = 0.0;
   out_2615016230612845443[317] = 0.0;
   out_2615016230612845443[318] = 0.0;
   out_2615016230612845443[319] = 0.0;
   out_2615016230612845443[320] = 0.0;
   out_2615016230612845443[321] = 0.0;
   out_2615016230612845443[322] = 0.0;
   out_2615016230612845443[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2589489788835022049) {
   out_2589489788835022049[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2589489788835022049[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2589489788835022049[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2589489788835022049[3] = dt*state[12] + state[3];
   out_2589489788835022049[4] = dt*state[13] + state[4];
   out_2589489788835022049[5] = dt*state[14] + state[5];
   out_2589489788835022049[6] = state[6];
   out_2589489788835022049[7] = state[7];
   out_2589489788835022049[8] = state[8];
   out_2589489788835022049[9] = state[9];
   out_2589489788835022049[10] = state[10];
   out_2589489788835022049[11] = state[11];
   out_2589489788835022049[12] = state[12];
   out_2589489788835022049[13] = state[13];
   out_2589489788835022049[14] = state[14];
   out_2589489788835022049[15] = state[15];
   out_2589489788835022049[16] = state[16];
   out_2589489788835022049[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8716816819534034926) {
   out_8716816819534034926[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8716816819534034926[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8716816819534034926[2] = 0;
   out_8716816819534034926[3] = 0;
   out_8716816819534034926[4] = 0;
   out_8716816819534034926[5] = 0;
   out_8716816819534034926[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8716816819534034926[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8716816819534034926[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8716816819534034926[9] = 0;
   out_8716816819534034926[10] = 0;
   out_8716816819534034926[11] = 0;
   out_8716816819534034926[12] = 0;
   out_8716816819534034926[13] = 0;
   out_8716816819534034926[14] = 0;
   out_8716816819534034926[15] = 0;
   out_8716816819534034926[16] = 0;
   out_8716816819534034926[17] = 0;
   out_8716816819534034926[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8716816819534034926[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8716816819534034926[20] = 0;
   out_8716816819534034926[21] = 0;
   out_8716816819534034926[22] = 0;
   out_8716816819534034926[23] = 0;
   out_8716816819534034926[24] = 0;
   out_8716816819534034926[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8716816819534034926[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8716816819534034926[27] = 0;
   out_8716816819534034926[28] = 0;
   out_8716816819534034926[29] = 0;
   out_8716816819534034926[30] = 0;
   out_8716816819534034926[31] = 0;
   out_8716816819534034926[32] = 0;
   out_8716816819534034926[33] = 0;
   out_8716816819534034926[34] = 0;
   out_8716816819534034926[35] = 0;
   out_8716816819534034926[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8716816819534034926[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8716816819534034926[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8716816819534034926[39] = 0;
   out_8716816819534034926[40] = 0;
   out_8716816819534034926[41] = 0;
   out_8716816819534034926[42] = 0;
   out_8716816819534034926[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8716816819534034926[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8716816819534034926[45] = 0;
   out_8716816819534034926[46] = 0;
   out_8716816819534034926[47] = 0;
   out_8716816819534034926[48] = 0;
   out_8716816819534034926[49] = 0;
   out_8716816819534034926[50] = 0;
   out_8716816819534034926[51] = 0;
   out_8716816819534034926[52] = 0;
   out_8716816819534034926[53] = 0;
   out_8716816819534034926[54] = 0;
   out_8716816819534034926[55] = 0;
   out_8716816819534034926[56] = 0;
   out_8716816819534034926[57] = 1;
   out_8716816819534034926[58] = 0;
   out_8716816819534034926[59] = 0;
   out_8716816819534034926[60] = 0;
   out_8716816819534034926[61] = 0;
   out_8716816819534034926[62] = 0;
   out_8716816819534034926[63] = 0;
   out_8716816819534034926[64] = 0;
   out_8716816819534034926[65] = 0;
   out_8716816819534034926[66] = dt;
   out_8716816819534034926[67] = 0;
   out_8716816819534034926[68] = 0;
   out_8716816819534034926[69] = 0;
   out_8716816819534034926[70] = 0;
   out_8716816819534034926[71] = 0;
   out_8716816819534034926[72] = 0;
   out_8716816819534034926[73] = 0;
   out_8716816819534034926[74] = 0;
   out_8716816819534034926[75] = 0;
   out_8716816819534034926[76] = 1;
   out_8716816819534034926[77] = 0;
   out_8716816819534034926[78] = 0;
   out_8716816819534034926[79] = 0;
   out_8716816819534034926[80] = 0;
   out_8716816819534034926[81] = 0;
   out_8716816819534034926[82] = 0;
   out_8716816819534034926[83] = 0;
   out_8716816819534034926[84] = 0;
   out_8716816819534034926[85] = dt;
   out_8716816819534034926[86] = 0;
   out_8716816819534034926[87] = 0;
   out_8716816819534034926[88] = 0;
   out_8716816819534034926[89] = 0;
   out_8716816819534034926[90] = 0;
   out_8716816819534034926[91] = 0;
   out_8716816819534034926[92] = 0;
   out_8716816819534034926[93] = 0;
   out_8716816819534034926[94] = 0;
   out_8716816819534034926[95] = 1;
   out_8716816819534034926[96] = 0;
   out_8716816819534034926[97] = 0;
   out_8716816819534034926[98] = 0;
   out_8716816819534034926[99] = 0;
   out_8716816819534034926[100] = 0;
   out_8716816819534034926[101] = 0;
   out_8716816819534034926[102] = 0;
   out_8716816819534034926[103] = 0;
   out_8716816819534034926[104] = dt;
   out_8716816819534034926[105] = 0;
   out_8716816819534034926[106] = 0;
   out_8716816819534034926[107] = 0;
   out_8716816819534034926[108] = 0;
   out_8716816819534034926[109] = 0;
   out_8716816819534034926[110] = 0;
   out_8716816819534034926[111] = 0;
   out_8716816819534034926[112] = 0;
   out_8716816819534034926[113] = 0;
   out_8716816819534034926[114] = 1;
   out_8716816819534034926[115] = 0;
   out_8716816819534034926[116] = 0;
   out_8716816819534034926[117] = 0;
   out_8716816819534034926[118] = 0;
   out_8716816819534034926[119] = 0;
   out_8716816819534034926[120] = 0;
   out_8716816819534034926[121] = 0;
   out_8716816819534034926[122] = 0;
   out_8716816819534034926[123] = 0;
   out_8716816819534034926[124] = 0;
   out_8716816819534034926[125] = 0;
   out_8716816819534034926[126] = 0;
   out_8716816819534034926[127] = 0;
   out_8716816819534034926[128] = 0;
   out_8716816819534034926[129] = 0;
   out_8716816819534034926[130] = 0;
   out_8716816819534034926[131] = 0;
   out_8716816819534034926[132] = 0;
   out_8716816819534034926[133] = 1;
   out_8716816819534034926[134] = 0;
   out_8716816819534034926[135] = 0;
   out_8716816819534034926[136] = 0;
   out_8716816819534034926[137] = 0;
   out_8716816819534034926[138] = 0;
   out_8716816819534034926[139] = 0;
   out_8716816819534034926[140] = 0;
   out_8716816819534034926[141] = 0;
   out_8716816819534034926[142] = 0;
   out_8716816819534034926[143] = 0;
   out_8716816819534034926[144] = 0;
   out_8716816819534034926[145] = 0;
   out_8716816819534034926[146] = 0;
   out_8716816819534034926[147] = 0;
   out_8716816819534034926[148] = 0;
   out_8716816819534034926[149] = 0;
   out_8716816819534034926[150] = 0;
   out_8716816819534034926[151] = 0;
   out_8716816819534034926[152] = 1;
   out_8716816819534034926[153] = 0;
   out_8716816819534034926[154] = 0;
   out_8716816819534034926[155] = 0;
   out_8716816819534034926[156] = 0;
   out_8716816819534034926[157] = 0;
   out_8716816819534034926[158] = 0;
   out_8716816819534034926[159] = 0;
   out_8716816819534034926[160] = 0;
   out_8716816819534034926[161] = 0;
   out_8716816819534034926[162] = 0;
   out_8716816819534034926[163] = 0;
   out_8716816819534034926[164] = 0;
   out_8716816819534034926[165] = 0;
   out_8716816819534034926[166] = 0;
   out_8716816819534034926[167] = 0;
   out_8716816819534034926[168] = 0;
   out_8716816819534034926[169] = 0;
   out_8716816819534034926[170] = 0;
   out_8716816819534034926[171] = 1;
   out_8716816819534034926[172] = 0;
   out_8716816819534034926[173] = 0;
   out_8716816819534034926[174] = 0;
   out_8716816819534034926[175] = 0;
   out_8716816819534034926[176] = 0;
   out_8716816819534034926[177] = 0;
   out_8716816819534034926[178] = 0;
   out_8716816819534034926[179] = 0;
   out_8716816819534034926[180] = 0;
   out_8716816819534034926[181] = 0;
   out_8716816819534034926[182] = 0;
   out_8716816819534034926[183] = 0;
   out_8716816819534034926[184] = 0;
   out_8716816819534034926[185] = 0;
   out_8716816819534034926[186] = 0;
   out_8716816819534034926[187] = 0;
   out_8716816819534034926[188] = 0;
   out_8716816819534034926[189] = 0;
   out_8716816819534034926[190] = 1;
   out_8716816819534034926[191] = 0;
   out_8716816819534034926[192] = 0;
   out_8716816819534034926[193] = 0;
   out_8716816819534034926[194] = 0;
   out_8716816819534034926[195] = 0;
   out_8716816819534034926[196] = 0;
   out_8716816819534034926[197] = 0;
   out_8716816819534034926[198] = 0;
   out_8716816819534034926[199] = 0;
   out_8716816819534034926[200] = 0;
   out_8716816819534034926[201] = 0;
   out_8716816819534034926[202] = 0;
   out_8716816819534034926[203] = 0;
   out_8716816819534034926[204] = 0;
   out_8716816819534034926[205] = 0;
   out_8716816819534034926[206] = 0;
   out_8716816819534034926[207] = 0;
   out_8716816819534034926[208] = 0;
   out_8716816819534034926[209] = 1;
   out_8716816819534034926[210] = 0;
   out_8716816819534034926[211] = 0;
   out_8716816819534034926[212] = 0;
   out_8716816819534034926[213] = 0;
   out_8716816819534034926[214] = 0;
   out_8716816819534034926[215] = 0;
   out_8716816819534034926[216] = 0;
   out_8716816819534034926[217] = 0;
   out_8716816819534034926[218] = 0;
   out_8716816819534034926[219] = 0;
   out_8716816819534034926[220] = 0;
   out_8716816819534034926[221] = 0;
   out_8716816819534034926[222] = 0;
   out_8716816819534034926[223] = 0;
   out_8716816819534034926[224] = 0;
   out_8716816819534034926[225] = 0;
   out_8716816819534034926[226] = 0;
   out_8716816819534034926[227] = 0;
   out_8716816819534034926[228] = 1;
   out_8716816819534034926[229] = 0;
   out_8716816819534034926[230] = 0;
   out_8716816819534034926[231] = 0;
   out_8716816819534034926[232] = 0;
   out_8716816819534034926[233] = 0;
   out_8716816819534034926[234] = 0;
   out_8716816819534034926[235] = 0;
   out_8716816819534034926[236] = 0;
   out_8716816819534034926[237] = 0;
   out_8716816819534034926[238] = 0;
   out_8716816819534034926[239] = 0;
   out_8716816819534034926[240] = 0;
   out_8716816819534034926[241] = 0;
   out_8716816819534034926[242] = 0;
   out_8716816819534034926[243] = 0;
   out_8716816819534034926[244] = 0;
   out_8716816819534034926[245] = 0;
   out_8716816819534034926[246] = 0;
   out_8716816819534034926[247] = 1;
   out_8716816819534034926[248] = 0;
   out_8716816819534034926[249] = 0;
   out_8716816819534034926[250] = 0;
   out_8716816819534034926[251] = 0;
   out_8716816819534034926[252] = 0;
   out_8716816819534034926[253] = 0;
   out_8716816819534034926[254] = 0;
   out_8716816819534034926[255] = 0;
   out_8716816819534034926[256] = 0;
   out_8716816819534034926[257] = 0;
   out_8716816819534034926[258] = 0;
   out_8716816819534034926[259] = 0;
   out_8716816819534034926[260] = 0;
   out_8716816819534034926[261] = 0;
   out_8716816819534034926[262] = 0;
   out_8716816819534034926[263] = 0;
   out_8716816819534034926[264] = 0;
   out_8716816819534034926[265] = 0;
   out_8716816819534034926[266] = 1;
   out_8716816819534034926[267] = 0;
   out_8716816819534034926[268] = 0;
   out_8716816819534034926[269] = 0;
   out_8716816819534034926[270] = 0;
   out_8716816819534034926[271] = 0;
   out_8716816819534034926[272] = 0;
   out_8716816819534034926[273] = 0;
   out_8716816819534034926[274] = 0;
   out_8716816819534034926[275] = 0;
   out_8716816819534034926[276] = 0;
   out_8716816819534034926[277] = 0;
   out_8716816819534034926[278] = 0;
   out_8716816819534034926[279] = 0;
   out_8716816819534034926[280] = 0;
   out_8716816819534034926[281] = 0;
   out_8716816819534034926[282] = 0;
   out_8716816819534034926[283] = 0;
   out_8716816819534034926[284] = 0;
   out_8716816819534034926[285] = 1;
   out_8716816819534034926[286] = 0;
   out_8716816819534034926[287] = 0;
   out_8716816819534034926[288] = 0;
   out_8716816819534034926[289] = 0;
   out_8716816819534034926[290] = 0;
   out_8716816819534034926[291] = 0;
   out_8716816819534034926[292] = 0;
   out_8716816819534034926[293] = 0;
   out_8716816819534034926[294] = 0;
   out_8716816819534034926[295] = 0;
   out_8716816819534034926[296] = 0;
   out_8716816819534034926[297] = 0;
   out_8716816819534034926[298] = 0;
   out_8716816819534034926[299] = 0;
   out_8716816819534034926[300] = 0;
   out_8716816819534034926[301] = 0;
   out_8716816819534034926[302] = 0;
   out_8716816819534034926[303] = 0;
   out_8716816819534034926[304] = 1;
   out_8716816819534034926[305] = 0;
   out_8716816819534034926[306] = 0;
   out_8716816819534034926[307] = 0;
   out_8716816819534034926[308] = 0;
   out_8716816819534034926[309] = 0;
   out_8716816819534034926[310] = 0;
   out_8716816819534034926[311] = 0;
   out_8716816819534034926[312] = 0;
   out_8716816819534034926[313] = 0;
   out_8716816819534034926[314] = 0;
   out_8716816819534034926[315] = 0;
   out_8716816819534034926[316] = 0;
   out_8716816819534034926[317] = 0;
   out_8716816819534034926[318] = 0;
   out_8716816819534034926[319] = 0;
   out_8716816819534034926[320] = 0;
   out_8716816819534034926[321] = 0;
   out_8716816819534034926[322] = 0;
   out_8716816819534034926[323] = 1;
}
void h_4(double *state, double *unused, double *out_4969538978811489115) {
   out_4969538978811489115[0] = state[6] + state[9];
   out_4969538978811489115[1] = state[7] + state[10];
   out_4969538978811489115[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5889238309403794696) {
   out_5889238309403794696[0] = 0;
   out_5889238309403794696[1] = 0;
   out_5889238309403794696[2] = 0;
   out_5889238309403794696[3] = 0;
   out_5889238309403794696[4] = 0;
   out_5889238309403794696[5] = 0;
   out_5889238309403794696[6] = 1;
   out_5889238309403794696[7] = 0;
   out_5889238309403794696[8] = 0;
   out_5889238309403794696[9] = 1;
   out_5889238309403794696[10] = 0;
   out_5889238309403794696[11] = 0;
   out_5889238309403794696[12] = 0;
   out_5889238309403794696[13] = 0;
   out_5889238309403794696[14] = 0;
   out_5889238309403794696[15] = 0;
   out_5889238309403794696[16] = 0;
   out_5889238309403794696[17] = 0;
   out_5889238309403794696[18] = 0;
   out_5889238309403794696[19] = 0;
   out_5889238309403794696[20] = 0;
   out_5889238309403794696[21] = 0;
   out_5889238309403794696[22] = 0;
   out_5889238309403794696[23] = 0;
   out_5889238309403794696[24] = 0;
   out_5889238309403794696[25] = 1;
   out_5889238309403794696[26] = 0;
   out_5889238309403794696[27] = 0;
   out_5889238309403794696[28] = 1;
   out_5889238309403794696[29] = 0;
   out_5889238309403794696[30] = 0;
   out_5889238309403794696[31] = 0;
   out_5889238309403794696[32] = 0;
   out_5889238309403794696[33] = 0;
   out_5889238309403794696[34] = 0;
   out_5889238309403794696[35] = 0;
   out_5889238309403794696[36] = 0;
   out_5889238309403794696[37] = 0;
   out_5889238309403794696[38] = 0;
   out_5889238309403794696[39] = 0;
   out_5889238309403794696[40] = 0;
   out_5889238309403794696[41] = 0;
   out_5889238309403794696[42] = 0;
   out_5889238309403794696[43] = 0;
   out_5889238309403794696[44] = 1;
   out_5889238309403794696[45] = 0;
   out_5889238309403794696[46] = 0;
   out_5889238309403794696[47] = 1;
   out_5889238309403794696[48] = 0;
   out_5889238309403794696[49] = 0;
   out_5889238309403794696[50] = 0;
   out_5889238309403794696[51] = 0;
   out_5889238309403794696[52] = 0;
   out_5889238309403794696[53] = 0;
}
void h_10(double *state, double *unused, double *out_2007694217068845080) {
   out_2007694217068845080[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2007694217068845080[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2007694217068845080[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1823393631919099076) {
   out_1823393631919099076[0] = 0;
   out_1823393631919099076[1] = 9.8100000000000005*cos(state[1]);
   out_1823393631919099076[2] = 0;
   out_1823393631919099076[3] = 0;
   out_1823393631919099076[4] = -state[8];
   out_1823393631919099076[5] = state[7];
   out_1823393631919099076[6] = 0;
   out_1823393631919099076[7] = state[5];
   out_1823393631919099076[8] = -state[4];
   out_1823393631919099076[9] = 0;
   out_1823393631919099076[10] = 0;
   out_1823393631919099076[11] = 0;
   out_1823393631919099076[12] = 1;
   out_1823393631919099076[13] = 0;
   out_1823393631919099076[14] = 0;
   out_1823393631919099076[15] = 1;
   out_1823393631919099076[16] = 0;
   out_1823393631919099076[17] = 0;
   out_1823393631919099076[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1823393631919099076[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1823393631919099076[20] = 0;
   out_1823393631919099076[21] = state[8];
   out_1823393631919099076[22] = 0;
   out_1823393631919099076[23] = -state[6];
   out_1823393631919099076[24] = -state[5];
   out_1823393631919099076[25] = 0;
   out_1823393631919099076[26] = state[3];
   out_1823393631919099076[27] = 0;
   out_1823393631919099076[28] = 0;
   out_1823393631919099076[29] = 0;
   out_1823393631919099076[30] = 0;
   out_1823393631919099076[31] = 1;
   out_1823393631919099076[32] = 0;
   out_1823393631919099076[33] = 0;
   out_1823393631919099076[34] = 1;
   out_1823393631919099076[35] = 0;
   out_1823393631919099076[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1823393631919099076[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1823393631919099076[38] = 0;
   out_1823393631919099076[39] = -state[7];
   out_1823393631919099076[40] = state[6];
   out_1823393631919099076[41] = 0;
   out_1823393631919099076[42] = state[4];
   out_1823393631919099076[43] = -state[3];
   out_1823393631919099076[44] = 0;
   out_1823393631919099076[45] = 0;
   out_1823393631919099076[46] = 0;
   out_1823393631919099076[47] = 0;
   out_1823393631919099076[48] = 0;
   out_1823393631919099076[49] = 0;
   out_1823393631919099076[50] = 1;
   out_1823393631919099076[51] = 0;
   out_1823393631919099076[52] = 0;
   out_1823393631919099076[53] = 1;
}
void h_13(double *state, double *unused, double *out_6769157992845548257) {
   out_6769157992845548257[0] = state[3];
   out_6769157992845548257[1] = state[4];
   out_6769157992845548257[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2676964484071461895) {
   out_2676964484071461895[0] = 0;
   out_2676964484071461895[1] = 0;
   out_2676964484071461895[2] = 0;
   out_2676964484071461895[3] = 1;
   out_2676964484071461895[4] = 0;
   out_2676964484071461895[5] = 0;
   out_2676964484071461895[6] = 0;
   out_2676964484071461895[7] = 0;
   out_2676964484071461895[8] = 0;
   out_2676964484071461895[9] = 0;
   out_2676964484071461895[10] = 0;
   out_2676964484071461895[11] = 0;
   out_2676964484071461895[12] = 0;
   out_2676964484071461895[13] = 0;
   out_2676964484071461895[14] = 0;
   out_2676964484071461895[15] = 0;
   out_2676964484071461895[16] = 0;
   out_2676964484071461895[17] = 0;
   out_2676964484071461895[18] = 0;
   out_2676964484071461895[19] = 0;
   out_2676964484071461895[20] = 0;
   out_2676964484071461895[21] = 0;
   out_2676964484071461895[22] = 1;
   out_2676964484071461895[23] = 0;
   out_2676964484071461895[24] = 0;
   out_2676964484071461895[25] = 0;
   out_2676964484071461895[26] = 0;
   out_2676964484071461895[27] = 0;
   out_2676964484071461895[28] = 0;
   out_2676964484071461895[29] = 0;
   out_2676964484071461895[30] = 0;
   out_2676964484071461895[31] = 0;
   out_2676964484071461895[32] = 0;
   out_2676964484071461895[33] = 0;
   out_2676964484071461895[34] = 0;
   out_2676964484071461895[35] = 0;
   out_2676964484071461895[36] = 0;
   out_2676964484071461895[37] = 0;
   out_2676964484071461895[38] = 0;
   out_2676964484071461895[39] = 0;
   out_2676964484071461895[40] = 0;
   out_2676964484071461895[41] = 1;
   out_2676964484071461895[42] = 0;
   out_2676964484071461895[43] = 0;
   out_2676964484071461895[44] = 0;
   out_2676964484071461895[45] = 0;
   out_2676964484071461895[46] = 0;
   out_2676964484071461895[47] = 0;
   out_2676964484071461895[48] = 0;
   out_2676964484071461895[49] = 0;
   out_2676964484071461895[50] = 0;
   out_2676964484071461895[51] = 0;
   out_2676964484071461895[52] = 0;
   out_2676964484071461895[53] = 0;
}
void h_14(double *state, double *unused, double *out_9071104771947762329) {
   out_9071104771947762329[0] = state[6];
   out_9071104771947762329[1] = state[7];
   out_9071104771947762329[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1925997453064310167) {
   out_1925997453064310167[0] = 0;
   out_1925997453064310167[1] = 0;
   out_1925997453064310167[2] = 0;
   out_1925997453064310167[3] = 0;
   out_1925997453064310167[4] = 0;
   out_1925997453064310167[5] = 0;
   out_1925997453064310167[6] = 1;
   out_1925997453064310167[7] = 0;
   out_1925997453064310167[8] = 0;
   out_1925997453064310167[9] = 0;
   out_1925997453064310167[10] = 0;
   out_1925997453064310167[11] = 0;
   out_1925997453064310167[12] = 0;
   out_1925997453064310167[13] = 0;
   out_1925997453064310167[14] = 0;
   out_1925997453064310167[15] = 0;
   out_1925997453064310167[16] = 0;
   out_1925997453064310167[17] = 0;
   out_1925997453064310167[18] = 0;
   out_1925997453064310167[19] = 0;
   out_1925997453064310167[20] = 0;
   out_1925997453064310167[21] = 0;
   out_1925997453064310167[22] = 0;
   out_1925997453064310167[23] = 0;
   out_1925997453064310167[24] = 0;
   out_1925997453064310167[25] = 1;
   out_1925997453064310167[26] = 0;
   out_1925997453064310167[27] = 0;
   out_1925997453064310167[28] = 0;
   out_1925997453064310167[29] = 0;
   out_1925997453064310167[30] = 0;
   out_1925997453064310167[31] = 0;
   out_1925997453064310167[32] = 0;
   out_1925997453064310167[33] = 0;
   out_1925997453064310167[34] = 0;
   out_1925997453064310167[35] = 0;
   out_1925997453064310167[36] = 0;
   out_1925997453064310167[37] = 0;
   out_1925997453064310167[38] = 0;
   out_1925997453064310167[39] = 0;
   out_1925997453064310167[40] = 0;
   out_1925997453064310167[41] = 0;
   out_1925997453064310167[42] = 0;
   out_1925997453064310167[43] = 0;
   out_1925997453064310167[44] = 1;
   out_1925997453064310167[45] = 0;
   out_1925997453064310167[46] = 0;
   out_1925997453064310167[47] = 0;
   out_1925997453064310167[48] = 0;
   out_1925997453064310167[49] = 0;
   out_1925997453064310167[50] = 0;
   out_1925997453064310167[51] = 0;
   out_1925997453064310167[52] = 0;
   out_1925997453064310167[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2062215461122009820) {
  err_fun(nom_x, delta_x, out_2062215461122009820);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1674122598517831978) {
  inv_err_fun(nom_x, true_x, out_1674122598517831978);
}
void pose_H_mod_fun(double *state, double *out_2615016230612845443) {
  H_mod_fun(state, out_2615016230612845443);
}
void pose_f_fun(double *state, double dt, double *out_2589489788835022049) {
  f_fun(state,  dt, out_2589489788835022049);
}
void pose_F_fun(double *state, double dt, double *out_8716816819534034926) {
  F_fun(state,  dt, out_8716816819534034926);
}
void pose_h_4(double *state, double *unused, double *out_4969538978811489115) {
  h_4(state, unused, out_4969538978811489115);
}
void pose_H_4(double *state, double *unused, double *out_5889238309403794696) {
  H_4(state, unused, out_5889238309403794696);
}
void pose_h_10(double *state, double *unused, double *out_2007694217068845080) {
  h_10(state, unused, out_2007694217068845080);
}
void pose_H_10(double *state, double *unused, double *out_1823393631919099076) {
  H_10(state, unused, out_1823393631919099076);
}
void pose_h_13(double *state, double *unused, double *out_6769157992845548257) {
  h_13(state, unused, out_6769157992845548257);
}
void pose_H_13(double *state, double *unused, double *out_2676964484071461895) {
  H_13(state, unused, out_2676964484071461895);
}
void pose_h_14(double *state, double *unused, double *out_9071104771947762329) {
  h_14(state, unused, out_9071104771947762329);
}
void pose_H_14(double *state, double *unused, double *out_1925997453064310167) {
  H_14(state, unused, out_1925997453064310167);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
