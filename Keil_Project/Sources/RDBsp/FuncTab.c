#include "FuncTab.h"


/*
版本号改成o3 2023.10.30号
*/
STLingMin  gstLingMinConfig[6] =
{
{1, LING_MIN_DU},
{2, LING_MIN_DU},
{4, LING_MIN_DU},
{8, LING_MIN_DU},
{16,LING_MIN_DU},
{32,LING_MIN_DU},
};

const volatile STSetVaue  ImageTemprertureTab[] = 
{
   {0xe1, 0},
	 {0xe2, 15},
	 {0xe3, 38},
	 {0xe4, 55},
	 {0xe5, 2},
	 {0xe6, 0},
	 {0xe7, -7},
	 {0xe8, -7},
	 {0xe9, -7},
	 {0xea, 5},//表示 EH
	 {0xeb, 1}, //表示 Eb
	 {0xec, 3}, //表示 软件版本号
};

volatile STSetVaue  TemprertureTab[] = 
{
   {0xe1, 0},
	 {0xe2, 15},
	 {0xe3, 38},
	 {0xe4, 55},
	 {0xe5, 2},
	 {0xe6, 0},
	 {0xe7, -7},
	 {0xe8, -7},
	 {0xe9, -7},
	 {0xea, 5},//表示 EH
	 {0xeb, 1}, //表示 Eb
	 {0xec, 3}, //表示 软件版本号
};


 //u8 dgg[2];










