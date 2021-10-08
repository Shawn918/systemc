///////////////////////////////////////////////////////////
//Project: Carbon
//Description: SystemC 虚拟项目1
//Module: test_main.cpp
//Description: 测试平台 main 文件，实例化顶层 DUT 和测试台
//Group: Nebula-Matrix 预研组
//Author: 张三
//Hierarchy：
//test_main__:tb_top ___:stim
//         |          |_:stat
//         |          |_:test_ctrl
//         |_:dut_top__:L1_mod1
//                   |_:L1_mod2             
//                   |_:L1_mod3             
//                   |_:L1_mod4             
////////////////////////////////////////////////////////////

//1.include 工具库
#include "stdio.h"
#include <iostream>
#include <memory>
#include "systemc.h"   

//2.include 子模块头文件
#include "tb_top.h"    //测试台顶层
#include "dut_top.h"   //DUT顶层
#include "comm_def.h"  //通用定义

using namespace std;   

int sc_main(int argc, char *argv[]) {

   //3.信号定义
   sc_clock gclk("clk",100,SC_NS);                  
   sc_signal<int> gclk_cnt;
   sc_signal<dut_cfg> dut_cfg_bus;  //由 tb_top 配置 DUT 的信号
   vector< sc_signal<pkt_desc> [4] > pkt_stim;  //参数化激励连接信号定义
   vector< sc_signal<pkt_desc> [4] > pkt_stat;  //参数化输出连接信号定义

   //4.模块例化
   dut_top dut_top_inst("dut_top1");
   tb_top  tb_top_inst("tb_top1");

   //5.信号连接 
   dut_top_inst.clk_cnt_in(gclk_cnt);
   dut_top_inst.cfg_in(dut_cfg_bus);
   dut_top_inst.pkt_in(pkt_stim);
   dut_top_inst.pkt_out(pkt_stat);

   tb_top_inst.clk_in(gclk);
   tb_top_inst.clk_cnt_out(gclk_cnt);
   tb_top_inst.dut_cfg_out(dut_cfg_bus);
   tb_top_inst.pkt_stim_out(pkt_stim);
   tb_top_inst.pkt_stat_in(pkt_stat);
   
   //6.仿真启动
   sc_start(100,SC_US);

   return 0;
}