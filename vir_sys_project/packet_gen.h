

#ifndef __PACKET_GEN__
#define __PACKET_GEN__

#include "comm_def.h"
#include "comm_func.h"

class packet_gen_module: public sc_module {
  public: 
    vector<sc_fifo_out<TRANS> *> output;  //packet_gen output <TRANS> vector, which have been parameterized
    sc_in_clk clk;                        //clock input of packet_gen_module from global clock

    int m_cycle_cnt; 
    int m_packet_id;
    global_config_c *m_cfg;
    vector<comm_shape_func* > packet_shape;

    //constructor declaration 
    //instead of SC_CTOR, explicit way so it can carry argv other than the name
    //SC_HAS_PROCESS declaration must be followed instead of using SC_CTOR
    packet_gen_module(sc_module_name name, global_config_c *glb_cfg);    
    SC_HAS_PROCESS(packet_gen_module); //instead of using SC_CTOR,

    //main function of packet_gen trigered by clock.
    void packet_gen_process();

};
 

#endif