

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
   sc_clock clk("clk",100,SC_NS);  //100ns 对应10MHZ 

   //init the I/O between [pkt_gen_mod] [ing_sch_mod]
   vector< sc_fifo<TRANS> * > tmp_fifo;  
   tmp_fifo.resize(g_m_inter_num);
   for(int i=0; i < g_m_inter_num; i++){
      tmp_fifo[i] =new sc_fifo<TRANS>();
   }
    
   //init module
   global_config_c   
   *glb_cfg = new global_config_c();

   packet_gen_module 
   pkt_gen_mod("pkt_gen", glb_cfg);
   pkt_gen_mod.clk(clk);
 
   ingress_sch 
   ing_sch_mod("recv_sch", glb_cfg);
   ing_sch_mod.clk(clk);

   //blind
   for(int i =0; i < g_m_inter_num; i++){
      pkt_gen_mod.output[i]->bind(*tmp_fifo[i]);
      ing_sch_mod.input_fifo[i]->bind(*tmp_fifo[i]);
      //(pkt_gen_mod.output[i])(tmp_fifo[i]);
      //(ing_sch_mod.input_fifo[i])(tmp_fifo[i]);
   }
   //char

   sc_start(100,SC_US);

   return 0;
}