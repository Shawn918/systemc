

#ifndef __TOP_H__
#define __TOP_H__

#include "comm_def.h"
#include "comm_func.h"
#include "ingress_sch.h"

class top: public sc_module {
    public:
    vector<sc_fifo_in<TRANS> *> topin_fifo;
    sc_in_clk clk;
    ingress_sch  *ing_sch_inst;

    SC_HAS_PROCESS(top);
    top (sc_module_name name, global_config_c * glb_cfg);
};

top::top(sc_module_name name, global_config_c * glb_cfg):sc_module(name),
ing_sch_inst(new ingress_sch("recv_sch",glb_cfg))
{
 //   ing_sch_inst = new ingress_sch("recv_sch", glb_cfg);
    topin_fifo.resize(g_m_inter_num);
    (*ing_sch_inst).clk(clk);
    ing_sch_inst->input_fifo=topin_fifo;
   // for(int i=0; i < g_m_inter_num; i++){
   //    ((*ing_sch_inst).input_fifo[i]) = topin_fifo[i];
   //};
};

#endif

/*
两种不同的方式应用SystemC macros:

1.传统的方式
//NAME.h
#ifndef NAME_H
#define NAME_H
#include "submodule.h"
...
SC_MODULE(NAME){
  port declerations
  channel /submodule instance
  SC_CTOR(NAME){
    connnectivity
    process registrations
  }
  process declerations
  helper declerations
};
#endif

//NAME.cpp
#include "systemc.h"
#include "NAME.h"
NAME::process {implementation}
NAME::helper {implemention}

2.建议类型

//NAME.h
#ifndef NAME_H
#define NAME_H
submodule forword class declerations
SC_MODULE(NAME){
port declerations
channel /submodule definitions
//constructors declerations
SC_CTOR(NAME);
process declerations
Helper declerations
}

//NAME.cpp
#include "NAME.h"
SC_HAS_PROCESS(NAME);
NAME::NAME(sc_module_name nm):sc_module(nm)
Initializations
{
channel allocations
submodule allocations
process registations
}

NAME::process{implementions }
NAME::Helper{implementions }


{{Macro SC_CTOR includes definitions used by the macros SC_METHOD, SC_THREAD and
SC_CTHREAD. These same definitions are introduced by the macro SC_HAS_PROCESS. If a process
macro is invoked from the constructor body of a module but macro SC_CTOR is not used within the module
class definition, macro SC_HAS_PROCESS shall be invoked within the class definition or the constructor
body of the module. If a process macro is invoked from the  before_end_of_elaboration or
end_of_elaboration callbacks of a module but macro SC_CTOR is not used within the module class
definition, macro SC_HAS_PROCESS shall be invoked within the class definition of the module or from
that same callback.
Macro SC_HAS_PROCESS shall only be used within the class definition, constructor body, or member
function body of a module. The name of the module class being constructed shall be passed as the argument
to the macro.  The macr o invocation shall be terminated with a semicolon.IE标准-1666-2011}}


————————————————
版权声明：本文为CSDN博主「ippesic」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qqyumo/article/details/9324609
*/