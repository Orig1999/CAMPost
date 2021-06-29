#pragma once
#include <QString>

//catia
const QString catia_apt = "aptsource";
const QString catia_prog_start = "Start generation of";
const QString catia_coodnitate_sys = "CATMAT/";
const QString catia_tool_change_begin = "TOOLCHANGEBEGINNING";
const QString catia_tool_change_end = "TOOLCHANGEEND";
const QString catia_tool_num = "LOADTL/";
const QString catia_tool_comp = "TLCOMP";
const QString catia_spindle_speed = "SPINDL/";
const QString catia_path_type = "TOOLPATH_TYPE/";
const QString catia_path_type_3axis = "3AXIS";
const QString catia_spindle_off = "SPINDL/OFF";
const QString catia_fedrat = "FEDRAT/";
const QString catia_tool_adjust = "ADJUST";
const QString catia_path_start = "START_OP/";
const QString catia_apt_apid ="RAPID";
const QString catia_apt_circle_dir = "INDIRV/";//圆弧起点切线矢量
const QString catia_apt_circle = "TLON,GOFWD/";//圆弧开始
const QString catia_apt_circle_c_r = "CIRCLE/";//圆心和半径
const QString catia_apt_circle_full = "INTOF";//整圆
const QString catia_apt_circle_c_e = "LINE/";//圆心和终点
const QString catia_apt_move ="GOTO/";
const QString catia_path_end = "END_OP/";
const QString catia_program_end = "$$ END";

//const QString catia_drill_on="CYCLE/";
const QString catia_drill_off = "CYCLE/OFF";
//钻孔
const QString catia_cycle_99="G99";//G99
const QString catia_cycle_98="G98";//G98

const QString catia_cycle_tap="CYCLE/TAP";//G84
const QString catia_cycle_drill = "CYCLE/DRILL";//G81

//nx
const QString nx_cls = "cls";//CLSF_ADVANCED

//程序头
const QString jd50_prog_header ="%\nO0001\nG91 G28 Z0\nG90 G40 G98 G80 G49\nG54 G21 G17 G00";
const QString jd50_prog_end ="M05 M09\nG91 G28 Z0\nM30\n%";
const QString jd50_path_header ="G90 G40 G49 G54 G17";
const QString jd50_adjust = "G53.1";
const QString jd50_Tool_length_adjust_on = "G43";
const QString jd50_Tool_length_adjust_off = "G49";
const QString jd50_local_sys_off = "G69";
