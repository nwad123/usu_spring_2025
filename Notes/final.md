---
geometry: margin=1in
fontsize: 10pt
---

```
  Point                                                   Incr       Path
  --------------------------------------------------------------------------
  clock processor_clk (rise edge)                         0.00       0.00
  clock network delay (ideal)                             0.00       0.00
  decode_r_block_r_addr_2_reg_reg_2_/CK (QDFFX1)          0.00 #     0.00 r
  decode_r_block_r_addr_2_reg_reg_2_/Q (QDFFX1)           0.12       0.12 r
  U5002/O (INVXLP)                                        0.03       0.15 f
  U5003/O (ND2XLP)                                        0.09       0.24 r
  U5045/O (OR2B1XLP)                                      0.45       0.69 r
  U5046/O (INVXLP)                                        0.12       0.81 f
  U5047/O (INVXLP)                                        0.48       1.30 r
  U5097/O (OAI22XLP)                                      0.04       1.33 f
  U5098/O (AOI12XLP)                                      0.08       1.42 r
  U5099/O (OAI112XLP)                                     0.05       1.46 f
  U5100/O (AOI112XLP)                                     0.10       1.57 r
  U5101/O (AOI22XLP)                                      0.05       1.62 f
  U5102/O (AOI22XLP)                                      0.09       1.70 r
  U5103/O (OA112XLP)                                      0.37       2.08 r
  U5104/O (INVX1)                                         0.36       2.43 f
  execute_alu_inst_add_29_U1_2/CO (FA1X1)                 0.14       2.58 f
  ...                                  (steadily rises from 2.58 to 4.80 f)
  execute_alu_inst_add_29_U1_30/CO (FA1X1)                0.07       4.80 f
  execute_alu_inst_add_29_U1_31/O (XOR3XLP)               0.06       4.86 f
  U6392/O (AOI22XLP)                                      0.07       4.92 r
  U6395/O (OAI112XLP)                                     0.05       4.97 f
  U6414/O (AOI112XLP)                                     0.14       5.11 r
  U6418/O (AOI23XLP)                                      0.08       5.19 f
  U6421/O (AO12XLP)                                       0.10       5.29 f
  execute_alu_fwd_data_1_reg_31_/D (DFFX1)                0.00       5.29 f
  data arrival time                                                  5.29

  clock processor_clk (rise edge)                        20.00      20.00
  clock network delay (ideal)                             0.00      20.00
  execute_alu_fwd_data_1_reg_31_/CK (DFFX1)               0.00      20.00 r
  library setup time                                     -0.08      19.92
  data required time                                                19.92
  --------------------------------------------------------------------------
  data required time                                                19.92
  data arrival time                                                 -5.29
  --------------------------------------------------------------------------
  slack (MET)                                                       14.63
```

\newpage 

```
Number of ports:                          163
Number of nets:                          5715
Number of cells:                         5431
Number of combinational cells:           4025
Number of sequential cells:              1406
Number of macros/black boxes:               0
Number of buf/inv:                        327
Number of references:                      61

Combinational area:              21803.039893
Buf/Inv area:                      811.439995
Noncombinational area:           22083.712491
Macro/Black Box area:                0.000000
Net Interconnect area:      undefined  (Wire load has zero net area)

Total cell area:                 43886.752384
```

\newpage 

```
                 Internal         Switching           Leakage            Total
Power Group      Power            Power               Power              Power   (   %    )  Attrs
--------------------------------------------------------------------------------------------------
io_pad             0.0000            0.0000            0.0000            0.0000  (   0.00%)
memory             0.0000            0.0000            0.0000            0.0000  (   0.00%)
black_box          0.0000            0.0000            0.0000            0.0000  (   0.00%)
clock_network      0.6687            0.0000            0.0000            0.0000  (   0.00%)  i
register       2.7861e-02        8.7349e-03        3.5547e+07            0.7408  (  88.75%)
sequential         0.0000            0.0000            0.0000            0.0000  (   0.00%)
combinational  2.1906e-02        4.8686e-02        2.3322e+07        9.3914e-02  (  11.25%)
--------------------------------------------------------------------------------------------------
Total              0.7185 mW     5.7420e-02 mW     5.8869e+07 pW         0.8348 mW
```

\newpage 

```
Total Power
-----------------------------------------------------------------
Total Internal Power:        1.29150088 mW            69.8622%
Total Switching Power:       0.49402142 mW            26.7235%
Total Leakage Power:         0.06311753 mW             3.4143%
Total Power:                 1.84863983 mW
-----------------------------------------------------------------
```

\newpage

```
Total number of nets with non-default rule or having extra spacing = 17
Total wire length = 169682 um.
Total half perimeter of net bounding box = 127211 um.
Total wire length on LAYER metal1 = 1463 um.
Total wire length on LAYER metal2 = 53253 um.
Total wire length on LAYER metal3 = 64386 um.
Total wire length on LAYER metal4 = 34363 um.
Total wire length on LAYER metal5 = 14178 um.
Total wire length on LAYER metal6 = 2039 um.
Total wire length on LAYER metal7 = 0 um.
Total wire length on LAYER metal8 = 0 um.
Total number of vias = 48891
Up-Via Summary (total 48891):

-----------------------
 metal1          21883
 metal2          21042
 metal3           4892
 metal4            972
 metal5            102
-----------------------
                 48891

Total number of DRC violations = 0
```

\newpage 

```
+--------------------+---------+---------+---------+
|     Setup mode     |   all   | reg2reg | default |
+--------------------+---------+---------+---------+
|           WNS (ns):| 14.998  | 14.998  | 16.425  |
|           TNS (ns):|  0.000  |  0.000  |  0.000  |
|    Violating Paths:|    0    |    0    |    0    |
|          All Paths:|  1968   |  1850   |  1955   |
+--------------------+---------+---------+---------+

Density: 70.678%
Routing Overflow: 0.00% H and 0.00% V
```
