///////////////////////////////////////////////////////////
//Project: Carbon
//Description: SystemC 虚拟项目1
//Module: stim_mod.h
//Description:  发包模块
//Group: Nebula-Matrix 预研组
//Author: Shawn
//Hierarchy：内部无嵌套模块的功能模块
////////////////////////////////////////////////////////////

//1.防重定义
#ifndef __STIM_MOD_H__
#define __STIM_MOD_H__

//2.include工具库
#include "comm_def.h"

//using namespace std;   
class stim_mod: public sc_module
{

//3.端口声明
  public: 
    sc_in<int> clk_cnt_in;
//    sc_in<tb_cfg> tb_cfg_in; 
    sc_out<pkt_desc> pkt_stim_out;  //sample 1个
//    array<sc_out<pkt_desc>, NO_PORTS > pkt_stim_out;  
    
//4.信号声明
     pkt_desc pkt_desc_tmp;  
//    array< pkt_desc, NO_PORTS > pkt_desc_tmp;  
    
//5.模块声明
    stim_mod(sc_module_name name); 
    SC_HAS_PROCESS(stim_mod);

//6.函数声明 
    void pkt_gen();
    //void function_module_action2();

};

stim_mod::
stim_mod(sc_module_name name):sc_module(name)
{
/*    for(int i=0; i < NO_PORTS; i++)
    {
        pkt_desc_tmp[i].sid = i;
        pkt_desc_tmp[i].did = NO_PORTS-1-i;
        pkt_desc_tmp[i].fsn = 0;
        pkt_desc_tmp[i].len = 64;
        pkt_desc_tmp[i].pri = 0;
        pkt_desc_tmp[i].fid = i;
    }*/
        pkt_desc_tmp.sid = 0;//sample 1
        pkt_desc_tmp.did = NO_PORTS-1;//sample 1
        pkt_desc_tmp.fsn = 0;//sample 1
        pkt_desc_tmp.len = 64;//sample 1
        pkt_desc_tmp.pri = 0;//sample 1
        pkt_desc_tmp.fid = 0; //sample 1

    SC_METHOD(pkt_gen);
    sensitive << clk_cnt_in;
 //   SC_THREAD(function_module_action2);
 //   sensitive << 全局时钟计数器1;
}

void stim_mod::
pkt_gen() {
    //pkt_desc_tmp[clk_cnt_in % NO_PORTS].fsn++;
    pkt_desc_tmp.fsn++; //sample 1
    pkt_stim_out = pkt_desc_tmp;
}
/*
void stim_mod::
function_module_action2() {
    while(true){
        变量2=f(变量1,信号1，报文输入口1,配置输入口1);
        信号2=f(变量1,变量2，信号1，报文输入口1,配置输入口1);
        报文输出口1=信号2;
        wait();
    }
}*/


#endif   //__STIM_MOD_H__