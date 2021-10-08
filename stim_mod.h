///////////////////////////////////////////////////////////
//Project: Carbon
//Description: SystemC 虚拟项目1
//Module: function_module.h
//Description:  底层功能模块
//Group: Nebula-Matrix 预研组
//Author: 张三
//Hierarchy：内部无嵌套模块的功能模块
////////////////////////////////////////////////////////////

//1.防重定义
#ifndef __STIM_MOD_H__
#define __STIM_MOD_H__

//2.include工具库
#include "stdio.h"
#include <iostream>
#include <memory>
#include "systemc.h"   

using namespace std;   
class stim_mod: public sc_module
{

//3.端口声明
  public: 
    sc_in<int> clk_cnt_in;
    sc_in<tb_cfg> tb_cfg_in; 
    vector<sc_out<pkt_desc> [CONST_NO_PORTS] > pkt_stim_out;  

//4.信号声明
    sc_signal<数据类型1> 信号1;  //内部信号
    sc_signal<数据类型2> 信号2;  //内部信号
    数据类型1  变量1；           //内部变量
    数据类型2  变量2；           //内部变量

//5.模块声明
    function_module(sc_module_name name); 
    SC_HAS_PROCESS(function_module);

//6.函数声明    
    void function_module_action1();
    void function_module_action2();

};

stim_mod::
stim_mod(sc_module_name name):sc_module(name),
    信号1(初始值),
    变量1(初始值)
{
    信号2=初始化()；
    变量2=初始化()；
   
    SC_METHOD(function_module_action1);
    sensitive << 报文输入口1;
    SC_THREAD(function_module_action2);
    sensitive << 全局时钟计数器1;
}

void stim_mod::
function_module_action1() {
    变量1=f(报文输入口1, 配置输入口1)
    信号1=f(报文输入口1, 配置输入口1) 
}

void stim_mod::
function_module_action2() {
    while(true){
        变量2=f(变量1,信号1，报文输入口1,配置输入口1);
        信号2=f(变量1,变量2，信号1，报文输入口1,配置输入口1);
        报文输出口1=信号2;
        wait();
    }
}


#endif   //__STIM_MOD_H__