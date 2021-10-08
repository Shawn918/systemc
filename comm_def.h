
#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include "stdio.h"
#include <memory>
#include "systemc.h"
#include "string.h"
#include <vector>

using namespace std;

const int CONST_FREQ  = 100; //100M HZ
const int CONST_NO_PORTS =4;

struct pkt_desc{
    //FROM STIM
    int sid;  //source id (0-255，255MCPU，254BCPU)  //-1 indicate not used
    int did;  //destination id (0-255 ，255MCPU，254BCPU)  //-1 indicate not used
    int fsn;  //flow pkt serial number (0-65535)  //-1 indicate not used
    int len;  //pkt length (40~9600)   //-1 indicate not used
    int pri;  //priority (0-3)   //-1 indicate not used
    int fid;  //flowid configured by PKTG  //-1 indicate not used

    //FROM ING(TAB)/PE(TAB)
    int qid;    //queue id fetched by ING,  //-1 indicate not used
    int dport;  //destination port fetched by PE  //-1 indicate not used
                //dport [0-3]：port1-port3  [4-253]reserved [254]:BCPU [255]: MCPU  //-1 indicate not used
    pkt_desc(){
        sid   = -1;  //-1 indicate not used
        did   = -1;  //-1 indicate not used
        fsn   = -1;  //-1 indicate not used
        len   = -1;  //-1 indicate not used
        pri   = -1;  //-1 indicate not used
        fid   = -1;  //-1 indicate not used
        qid   = -1;  //-1 indicate not used
        dport = -1;  //-1 indicate not used
    };

    inline bool operator == (const pkt_desc& pkt) const{
     return (pkt.sid == sid && pkt.did == did && 
             pkt.fsn == fsn && pkt.len == len && 
             pkt.pri == pri && pkt.fid == fid &&
             pkt.qid == qid && pkt.dport == dport);
   }

}

friend ostream& operator<< (ostream &out, pkt_desc &A){
    out << sc_time_stamp() << "|=> " 
        << "[ s:"<< (A.sid) 
        << ", d:"<< (A.did)
        << ", n:"<< (A.fsn)
        << ", l:"<< (A.len)
        << ", p:"<< (A.pri)
        << ", fid:"<< (A.fid)
        << ", qid:"<< (A.qid)
        << ", dport:"<< (A.dport)
        << "]" << endl;
     return out;
};

inline void
#if defined(SC_API_VERSION_STRING)
    sc_trace( sc_trace_file* tf, const pkt_desc& a, const std::string& name )
#else
    sc_trace( sc_trace_file* tf, const pkt_desc& a, const sc_string& name )
#endif
{
  sc_trace( tf, a.sid, name + ".sid" );
  sc_trace( tf, a.did, name + ".did" );
  sc_trace( tf, a.fsn, name + ".fsn" );
  sc_trace( tf, a.len, name + ".len" );
  sc_trace( tf, a.pri, name + ".pri" );
  sc_trace( tf, a.fid, name + ".fid" );
  sc_trace( tf, a.qid, name + ".qid" );
  sc_trace( tf, a.dport, name + ".dport" );
}

#endif //__COMM_DEF_H__