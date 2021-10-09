


#include "packet_gen.h"
//激励包长应从顶层获取，先配置固定256B，稍后再改
packet_gen_module::
packet_gen_module(sc_module_name name, global_config_c *glb_cfg):sc_module(name),
    m_cycle_cnt(0),
    m_packet_id(0),
    m_cfg(glb_cfg)
{
    output.resize(g_m_inter_num);
    for(int i=0; i < g_m_inter_num; i++) {
        output[i] =new sc_fifo_out<TRANS>;
    }
    //init shape
    packet_shape.resize(g_m_inter_num);
    for(int i=0; i < g_m_inter_num; i++) {
       packet_shape[i] = new comm_shape_func(1000, 9620, 13, 10);
    }
   
    SC_METHOD(packet_gen_process);
    sensitive << clk.pos();
}

void packet_gen_module::
packet_gen_process() {
   m_cycle_cnt++;   
   //填桶
    if((m_cycle_cnt !=0) &&(m_cycle_cnt % 10 ==0)) {
        for(int i=0; i < g_m_inter_num; i++) {
            packet_shape[i]->add_token(13);  //10cc填充13个
        }    
    }
    
   //4端口轮询
   for(int i=0; i < g_m_inter_num; i++){
        if(packet_shape[i]->shape_status(256)) { //包长是否够
            m_packet_id++;  
            TRANS new_trans(new trans_type);
            new_trans->sport_id = i;
            new_trans->dport_id = i;
            new_trans->pkt_id   = m_packet_id;
            new_trans->pkt_len  = 256;
            new_trans->pri_id   = 0;
            output[i]->nb_write(new_trans);
            cout << "send to port " << i << " pktid " << m_packet_id <<endl;
            cout << * new_trans << endl ;
        }
   }   
}
