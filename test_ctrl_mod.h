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
#ifndef __TEST_CTRL_MOD_H__
#define __TEST_CTRL_MOD_H__

//2.include工具库
#include "stdio.h"
#include <iostream>
#include <memory>
#include "systemc.h"   

using namespace std;   
class test_ctrl_mod: public sc_module
{

//3.端口声明
  public: 
    sc_in_clk             clk_in;
    sc_out<int>      clk_cnt_out;
    sc_out<dut_cfg>  dut_cfg_out;  
    sc_out< tb_cfg>   tb_cfg_out;  

//4.信号声明
    sc_signal<int>      clk_cnt_sig;  
    sc_signal<dut_cfg>  dut_cfg_sig;  
    sc_signal< tb_cfg>   tb_cfg_sig;  

//5.模块声明
    test_ctrl_mod(sc_module_name name); 
    SC_HAS_PROCESS(test_ctrl_mod);

//6.函数声明    
    void clk_count();    

};

test_ctrl_mod::
test_ctrl_mod(sc_module_name name):sc_module(name)
{
    //    dut_cfg_sig = f(配置文件)；
    //    tb_cfg_sig  = f(配置文件)；
    //    dut_cfg_out = dut_cfg_sig；
    //    tb_cfg_out  = tb_cfg_sig；
    cout<<"读取文件预留位置.\n";

    SC_THREAD(clk_count);
    sensitive << clk_in;
}


void test_ctrl_mod::
clk_count() {
    clk_cnt_sig=0;
    while(true){
        clk_cnt_sig++;
        clk_cnt_out=clk_cnt_sig;
        wait();
    }
}


#endif  //__TEST_CTRL_MOD_H__