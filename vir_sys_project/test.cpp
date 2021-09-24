

#include "stdio.h"
#include <iostream>
#include <memory>

#include "packet_gen.h"
#include "ingress_sch.h"
#include "systemc.h"
#include "comm_def.h"
#include "comm_func.h"

using namespace std;


int sc_main(int argc, char *argv[]) {

   int glb_clk_cnt = 0;

   sc_clock clk("clk",100,SC_NS);  //100ns 对应10MHZ 
   SC_METHOD(clkcnt){
      glb_clk_cnt++
   };
   sensitive << clk.pos();

   //init the I/O between [pkt_gen_mod] [ing_sch_mod]
   vector< sc_fifo<TRANS> * > tmp_fifo;  
   tmp_fifo.resize(g_m_inter_num);
   for(int i=0; i < g_m_inter_num; i++){
      tmp_fifo[i] =new sc_fifo<TRANS>();
   }
    
   //init module
   global_config_c* glb_cfg;  
   glb_cfg = new global_config_c();

   packet_gen_module pkt_gen_inst("pkt_gen", glb_cfg);
   pkt_gen_inst.clk(clk);
 
   ingress_sch ing_sch_inst("recv_sch", glb_cfg);
   ing_sch_inst.clk(clk);

   //blind
   for(int i =0; i < g_m_inter_num; i++){
      pkt_gen_inst.output[i]->bind(*tmp_fifo[i]);
      ing_sch_inst.input_fifo[i]->bind(*tmp_fifo[i]);
      //(pkt_gen_mod.output[i])(tmp_fifo[i]);
      //(ing_sch_mod.input_fifo[i])(tmp_fifo[i]);
   }
   //char

   sc_start(100,SC_US);

   return 0;
}