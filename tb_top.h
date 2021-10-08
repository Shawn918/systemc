///////////////////////////////////////////////////////////
//Project: Carbon
//Description: SystemC 虚拟项目1
//Module: tb_top.h
//Description: 测试台 top 文件，实例化各测试模块
//Group: Nebula-Matrix 预研组
//Author: 张三
//Hierarchy：
//             tb_top __:stim
//                    |_:stat
//                    |_:test_ctrl
////////////////////////////////////////////////////////////

//1.防重定义
#ifndef __TB_TOP_H__
#define __TB_TOP_H__

//2.include工具库
#include "stdio.h"
#include <iostream>
#include <memory>
#include "systemc.h"   

//3.include子模块库
#include "stim_mod.h"      //激励模块
#include "stat_mod.h"      //统计模块
#include "test_ctrl_mod.h" //测试控制模块
#include "comm_def.h"  //通用定义

using namespace std;   
class tb_top: public sc_module
{

//4.端口声明
  public: 
    sc_in_clk clk_in;                  //全局时钟输入
    sc_out<int> clk_cnt_out;           //全局时钟计数输出，由test_ctrl根据全局时钟输入产生
    sc_out<dut_cfg> dut_cfg_out;       //由test_ctrl读取文件产生
    vector<  sc_in<pkt_desc> [CONST_NO_PORTS] > pkt_stat_in;   //由stat模块接收的报文
    vector< sc_out<pkt_desc> [CONST_NO_PORTS] > pkt_stim_out;  //由stim产生的激励报文

//5.信号声明
    sc_signal<int> gclk_cnt;           //由test_ctrl产生，需要输出给外部和tb_top内部其他子模块
    sc_signal<tb_cfg> tb_cfg_sig;      //由test_ctrl读取文件产生，输送给其他的testbench内部模块

//5.模块声明
    tb_top(sc_module_name name); 
    SC_HAS_PROCESS(tb_top);
//6.函数声明
//    void tb_top_process()

//7.子模块声明
    stim_mod *stim_inst;
    stat_mod *stat_inst;
    test_ctrl_mod *test_ctrl_inst;

    SC_CTOR(tb_top){
    //8.子模块例化    
        stim_inst = new stim_mod("stim_inst")；
        stat_inst = new stat_mod("stat_inst");
        test_ctrl_inst = new test_ctrl_inst("test_ctrl_inst");
     
    //9.信号连接 
        stim_inst->clk_cnt_in(gclk_cnt);
        stim_inst->tb_cfg(tb_cfg_sig);
        stim_inst->pkt_stim_out(pkt_stim_out);
    
        stat_inst->clk_cnt_in(gclk_cnt);
        stat_inst->tb_cfg(tb_cfg_sig);
        stat_inst->pkt_stat_in(pkt_stat_in);
    
        test_ctrl_inst->clk_in(clk_in);
        test_ctrl_inst->clk_cnt_out(gclk_cnt);
        test_ctrl_inst->dut_cfg_out(dut_cfg_out);
        test_ctrl_inst->tb_cfg_out(tb_cfg_sig);
        clk_cnt_out = gclk_cnt
   };
};

#endif  //__TB_TOP_H__