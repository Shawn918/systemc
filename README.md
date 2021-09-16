This project is a tutorial project for systemc Learning forked from NMadvres/systemc
Its a demo packet switch with demo testbench as below:

[pktgen]-->|----------|  |----------|-->[stat]
[pktgen]-->|INGRESS   |--|PktEditor |-->[stat]
[pktgen]-->|&Schedule |  |& Egress  |-->[stat]
[pktgen]-->|__________|  |__________|-->[stat]

[Sys Assumption]:
Port Speed: 1Gbps (GE)
Inter Clk : 100MHz
Input Port Num: 4
Output Port Num: 4

[test cases]
>>>Set1
   Pktlen: Fix 256
   Sending Ports: 1 to 4
   To Ports: 1
   Sending Speed: 1Gbps each
   Pri:  50% pri1, 50% pri2
>>>Set1
   Pktlen: Fix 256
   Sending Ports: 1 to 4
   To Ports: 1
   Sending Speed: 1Gbps each
   Pri:  50% pri1, 50% pri2
>>>Set1
   Pktlen: Fix 256
   Sending Ports: 1 to 4
   To Ports: 1
   Sending Speed: 1Gbps each
   Pri:  50% pri1, 50% pri2

[Logs/Stat]
   Loging：
       [@G_Cycle_Cnt] rcv from Port x [s:2,d:1,i:132,l:256,p:1]
       [@G_Cycle_Cnt] send to Port x [s:2,d:1,i:132,l:256,p:1]
   statistic:
       <<<TOP>>>
       [Sent]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [Rcvd]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [SDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       [DDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       <<<P1>>>
       [Sent]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [Rcvd]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [SDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       [DDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       <<<P2>>>
       [Sent]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [Rcvd]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [SDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       [DDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       <<<P3>>>
       [Sent]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [Rcvd]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [SDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       [DDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       <<<P4>>>
       [Sent]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [Rcvd]:   xxxx Pkts |xxxxx Bytes |xxx MBps
       [SDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps
       [DDrop]:  xxxx Pkts |xxxxx Bytes |xxx MBps


[Pkt info]:
S_port:  Source Port ID
D_port:  Destinaton Port ID
pkt_id:  Packet ID
pkt_len: Packet Len
pri:     Priority
Printing sample: "[s:2,d:1,i:132,l:256,p:1]"
