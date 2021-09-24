#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include "stdio.h"
#include <memory>
#include "systemc.h"
#include "tlm"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include "tlm_utils/multi_passthrough_target_socket.h"
#include "string.h"
#include <vector>
#include <assert.h>

using namespace std;
using namespace tlm_utils;
using namespace tlm;


const int g_m_freq  = 100; //100M HZ
const int g_m_inter_num =4;

typedef struct trans_type
{
   int  sport_id;
   int  dport_id;
   int  pkt_id;
   int  pkt_len;
   int  pri_id;

   trans_type(){
      sport_id  = 0;
      dport_id  = 0;
      pkt_id    = 0;
      pkt_len   = 0;
      pri_id    = 0;
   }

/*
   friend ostream& operator<< (ostream &out, trans_type &A){
       out << "[sport_id:" << (A.sport_id) 
           << ", dport_id:"<< (A.dport_id)
           << ", pkt_id:"<< (A.pkt_id)
           << ", pkt_len:"<< (A.pkt_len)
           << ", pri_id:"<< (A.pri_id)
           << "]" << endl;
       return out;
   }
*/
   friend ostream& operator<< (ostream &out, trans_type &A){
       out << sc_time_stamp() << "|=> " 
           << "[s:" << (A.sport_id) 
           << ", d:"<< (A.dport_id)
           << ", i:"<< (A.pkt_id)
           << ", l:"<< (A.pkt_len)
           << ", p:"<< (A.pri_id)
           << "]" << endl;
       return out;
   }

} TRANS_STR; 


// 全局配置数据结构
struct para{
   int  m_freq;           //主频,单位MHZ
   int  m_inter_num;      //接口数
   int  m_sch_sel;        //调度器选择 0:SP 1:RR  2:WRR
   int  shape_value;      //限速值 单位Mbps
};

// 全局配置
class global_config_c : public sc_module
{
   public:
      para para_init;      //初始化全局配置
      int  glb_clk_cnt;    //全局时钟计数
      SC_HAS_PROCESS(global_config_c);
      global_config_c(sc_module_name name): public sc_module(name),
      //初始化全局配置
      para_init.m_freq(g_m_freq),
      para_init.m_inter_num(g_m_inter_num), 
      para_init.m_sch_sel(1),
      para_init.shape_value(1000),
      //初始化全局时钟计数
      glb_clk_cnt(0)
     {
           SC_METHOD(clock_cnt){glb_clk_cnt++};
           sensitive << clk.pos();
     }
}; 

#define  ASSERT(A)  (assert(A))



#endif