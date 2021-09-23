

#ifndef __PACKET_GEN__
#define __PACKET_GEN__

#include "comm_def.h"
#include "comm_func.h"

class packet_gen_module: public sc_module {
  public: 
    vector<sc_fifo_out<TRANS> *> output;
    sc_in_clk clk;

    int m_cycle_cnt;
    int m_packet_id;
    global_config_c *m_cfg;
    vector<comm_shape_func *> packet_shape;
    
    SC_HAS_PROCESS(packet_gen_module);
    packet_gen_module(string name, global_config_c *glb_cfg);
    void packet_gen_process();

};
 

#endif