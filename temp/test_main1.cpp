///////////////////////////////////////////////////////////
//Project: Carbon
//Description: SystemC 虚拟项目1
//Module: test_main.cpp
//Description: 测试平台 main 文件，实例化顶层 DUT 和测试台
//Group: Nebula-Matrix 预研组
//Author: Shawn
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
#include "comm_def.h"

//2.include 子模块头文件
#include "top_tb.h"    //测试台顶层
//#include "top_dut.h"   //DUT顶层

//using namespace std;   

int sc_main(int argc, char *argv[]) {

   //3.信号定义
   sc_clock gclk("clk",100,SC_NS);                  
   sc_signal<int> sig_gclk_cnt;
//   sc_signal<dut_cfg> dut_cfg_bus;  //由 tb_top 配置 DUT 的信号
   //sc_signal<pkt_desc>       pkt_stim_sig;  //sample 1个
   std::array< sc_signal<pkt_desc>, NO_PORTS > sig_pkt_stim;  //参数化激励连接信号定义
//   array< sc_signal<pkt_desc>, NO_PORTS > pkt_stat_sig;  //参数化输出连接信号定义

   //4.模块例化
//   dut_top dut_top_inst("dut_top1");
   top_tb  *top_tb_inst;
   top_tb_inst = new top_tb("top_tb_inst");

   //5.信号连接 
//   dut_top_inst.clk_cnt_in(sig_gclk_cnt);
//   dut_top_inst.cfg_in(dut_cfg_bus);
//   dut_top_inst.pkt_in(pkt_stim);
//   dut_top_inst.pkt_out(pkt_stat);

   top_tb_inst->in_clk(gclk);
//   tb_top_inst.clk_cnt_out(sig_gclk_cnt);
//   tb_top_inst.dut_cfg_out(dut_cfg_bus);
   for (int i=0;i<NO_PORTS;i++){
       top_tb_inst->out_pkt_stim[i](sig_pkt_stim[i]);
       top_tb_inst->in_pkt_stat[i](sig_pkt_stim[i]);
   }
//   tb_top_inst.pkt_stat_in(pkt_stat);

   //6.仿真启动
   sc_start(1,SC_US);

   return 0;
}