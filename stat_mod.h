///////////////////////////////////////////////////////////
//Project: Carbon
//Description: SystemC 虚拟项目1
//Module: stat_mod.h
//Description:  收包模块
//Group: Nebula-Matrix 预研组
//Author: Shawn
//Hierarchy：内部无嵌套模块的功能模块
////////////////////////////////////////////////////////////

//1.防重定义
#ifndef __STAT_MOD_H__
#define __STAT_MOD_H__

//2.include工具库
#include "stdio.h"
#include <iostream>
#include <memory>
#include "systemc.h"   

//using namespace std;   
class stat_mod: public sc_module
{

//3.端口声明
  public: 
    sc_in<int> clk_cnt_in;
    //sc_in<tb_cfg> tb_cfg_in; 
    sc_in<pkt_desc> pkt_stat_in;  //sample 1
    //array< sc_in<pkt_desc>, NO_PORTS > pkt_stat_in;  

//4.信号声明


//5.模块声明
    stat_mod(sc_module_name name); 
    SC_HAS_PROCESS(stat_mod);

//6.函数声明    
    void pkt_dump();

};

stat_mod::
stat_mod(sc_module_name name):sc_module(name){
    SC_METHOD(pkt_dump);
    sensitive<< pkt_stat_in;
}

void stat_mod::
pkt_dump() {
    cout <<  pkt_stat_in;
}

#endif //__STAT_MOD_H__