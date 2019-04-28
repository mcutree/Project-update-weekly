 
;标号==============指令================================地址===机器码=======
;==========================================================================
Q0000:             LJMP  Q05A7                        ;0000   02 05 A7
;==========================================================================
Q0003:		 DB  00H, DBH, 00H, 00H, 00H, 00H, 00H, 00H	;........
Q000B:		 DB  02H, DBH, 52H	;..R
;==========================================================================
Q000E:             MOV   A,3MOV                       ;000E   E5 3D
                   XRL   A,#0AH                       ;0010   64 0A
                   JZ    Q00JZ                        ;0012   60 03
                   LJMP  Q01C7                        ;0014   02 01 C7
;==========================================================================
Q0017:             MOV   3DHMOV                       ;0017   F5 3D
                   INC   3AHINC                       ;0019   05 3A
                   MOV   A,3MOV                       ;001B   E5 3A
                   XRL   A,#06H                       ;001D   64 06
                   JZ    Q00JZ                        ;001F   60 03
                   LJMP  Q01C7                        ;0021   02 01 C7
;==========================================================================
Q0024:             MOV   3AHMOV                       ;0024   F5 3A
                   INC   49HINC                       ;0026   05 49
                   MOV   A,4MOV                       ;0028   E5 49
                   XRL   A,#0AH                       ;002A   64 0A
                   JZ    Q00JZ                        ;002C   60 03
                   LJMP  Q01C7                        ;002E   02 01 C7
;==========================================================================
Q0031:             MOV   49HMOV                       ;0031   F5 49
                   INC   44HINC                       ;0033   05 44
                   MOV   A,4MOV                       ;0035   E5 44
                   XRL   A,#06H                       ;0037   64 06
                   JZ    Q00JZ                        ;0039   60 03
                   LJMP  Q01C7                        ;003B   02 01 C7
;==========================================================================
Q003E:             MOV   44HMOV                       ;003E   F5 44
                   DEC   52HDEC                       ;0040   15 52
                   MOV   A,5MOV                       ;0042   E5 52
                   JZ    Q00JZ                        ;0044   60 10
                   INC   50HINC                       ;0046   05 50
                   MOV   A,5MOV                       ;0048   E5 50
                   XRL   A,#0AH                       ;004A   64 0A
                   JZ    Q00JZ                        ;004C   60 03
                   LJMP  Q01C7                        ;004E   02 01 C7
;==========================================================================
Q0051:             MOV   50HMOV                       ;0051   F5 50
                   INC   4AHINC                       ;0053   05 4A
                   RET      RET                       ;0055   22
;==========================================================================
Q0056:             MOV   A,5MOV                       ;0056   E5 52
                   JZ    Q00JZ                        ;0058   60 03
                   LJMP  Q01C7                        ;005A   02 01 C7
;==========================================================================
Q005D:             MOV   52HMOV8H                     ;005D   75 52 18
                   MOV   50HMOV                       ;0060   F5 50
                   MOV   4AHMOV                       ;0062   F5 4A
                   MOV   A,3MOV                       ;0064   E5 37
                   JNZ   Q00JNZ                       ;0066   70 04
                   MOV   R7,MOVH                      ;0068   7F 01
                   SJMP  Q006E                        ;006A   80 02
Q006C:             MOV   R7,MOVH                      ;006C   7F 00
Q006E:             MOV   A,3MOV                       ;006E   E5 32
                   JNZ   Q00JNZ                       ;0070   70 04
                   MOV   R6,MOVH                      ;0072   7E 01
                   SJMP  Q0078                        ;0074   80 02
Q0076:             MOV   R6,MOVH                      ;0076   7E 00
Q0078:             MOV   A,RMOV                       ;0078   EE
                   ANL   A,R7                         ;0079   5F
                   MOV   R7,MOV                       ;007A   FF
                   MOV   A,4MOV                       ;007B   E5 40
                   JNZ   Q00JNZ                       ;007D   70 04
                   MOV   R6,MOVH                      ;007F   7E 01
                   SJMP  Q0085                        ;0081   80 02
Q0083:             MOV   R6,MOVH                      ;0083   7E 00
Q0085:             MOV   A,RMOV                       ;0085   EE
                   ANL   A,R7                         ;0086   5F
                   MOV   R7,MOV                       ;0087   FF
                   MOV   A,3MOV                       ;0088   E5 3E
                   JNZ   Q00JNZ                       ;008A   70 04
                   MOV   R6,MOVH                      ;008C   7E 01
                   SJMP  Q0092                        ;008E   80 02
Q0090:             MOV   R6,MOVH                      ;0090   7E 00
Q0092:             MOV   A,RMOV                       ;0092   EE
                   ANL   A,R7                         ;0093   5F
                   JNZ   Q00JNZ                       ;0094   70 28
                   DEC   32HDEC                       ;0096   15 32
                   MOV   A,3MOV                       ;0098   E5 32
                   CJNE  A,#0AH,Q00BE                 ;009A   B4 0A 21
                   CLR   A                            ;009D   E4
                   MOV   32HMOV                       ;009E   F5 32
                   DEC   37HDEC                       ;00A0   15 37
                   MOV   A,3MOV                       ;00A2   E5 37
                   CJNE  A,#0AH,Q00BE                 ;00A4   B4 0A 17
                   CLR   A                            ;00A7   E4
                   MOV   37HMOV                       ;00A8   F5 37
                   DEC   40HDEC                       ;00AA   15 40
                   MOV   A,4MOV                       ;00AC   E5 40
                   CJNE  A,#0AH,Q00BE                 ;00AE   B4 0A 0D
                   CLR   A                            ;00B1   E4
                   MOV   40HMOV                       ;00B2   F5 40
                   DEC   3EHDEC                       ;00B4   15 3E
                   MOV   A,3MOV                       ;00B6   E5 3E
                   CJNE  A,#0AH,Q00BE                 ;00B8   B4 0A 03
                   CLR   A                            ;00BB   E4
                   MOV   3EHMOV                       ;00BC   F5 3E
Q00BE:             MOV   A,3MOV                       ;00BE   E5 39
                   ORL   A,#0FEH                      ;00C0   44 FE
                   MOV   R7,MOV                       ;00C2   FF
                   CPL   A                            ;00C3   F4
                   JNZ   Q01JNZ                       ;00C4   70 7A
                   DEC   42HDEC                       ;00C6   15 42
                   MOV   A,4MOV                       ;00C8   E5 42
                   JZ    Q00JZ                        ;00CA   60 0D
                   INC   46HINC                       ;00CC   05 46
                   MOV   A,4MOV                       ;00CE   E5 46
                   XRL   A,#0AH                       ;00D0   64 0A
                   JZ    Q00JZ                        ;00D2   60 03
                   LJMP  Q01C7                        ;00D4   02 01 C7
;==========================================================================
Q00D7:             SJMP  Q0155                        ;00D7   80 7C
Q00D9:             MOV   A,4MOV                       ;00D9   E5 42
                   JZ    Q00JZ                        ;00DB   60 03
                   LJMP  Q01C7                        ;00DD   02 01 C7
;==========================================================================
Q00E0:             MOV   42HMOVFH                     ;00E0   75 42 1F
                   MOV   46HMOV1H                     ;00E3   75 46 01
                   MOV   53HMOV                       ;00E6   F5 53
                   DEC   41HDEC                       ;00E8   15 41
                   MOV   A,4MOV                       ;00EA   E5 41
                   JZ    Q00JZ                        ;00EC   60 0E
                   INC   39HINC                       ;00EE   05 39
                   MOV   A,3MOV                       ;00F0   E5 39
                   XRL   A,#0AH                       ;00F2   64 0A
                   JZ    Q00JZ                        ;00F4   60 03
                   LJMP  Q01C7                        ;00F6   02 01 C7
;==========================================================================
Q00F9:             LJMP  Q018E                        ;00F9   02 01 8E
;==========================================================================
Q00FC:             MOV   A,4MOV                       ;00FC   E5 41
                   JZ    Q01JZ                        ;00FE   60 03
                   LJMP  Q01C7                        ;0100   02 01 C7
;==========================================================================
Q0103:             MOV   41HMOVCH                     ;0103   75 41 0C
                   MOV   39HMOV1H                     ;0106   75 39 01
                   MOV   47HMOV                       ;0109   F5 47
                   INC   3FHINC                       ;010B   05 3F
                   MOV   A,3MOV                       ;010D   E5 3F
                   XRL   A,#0AH                       ;010F   64 0A
                   JZ    Q01JZ                        ;0111   60 03
                   LJMP  Q01C7                        ;0113   02 01 C7
;==========================================================================
Q0116:             MOV   3FHMOV                       ;0116   F5 3F
                   INC   4BHINC                       ;0118   05 4B
                   MOV   A,4MOV                       ;011A   E5 4B
                   XRL   A,#0AH                       ;011C   64 0A
                   JZ    Q01JZ                        ;011E   60 03
                   LJMP  Q01C7                        ;0120   02 01 C7
;==========================================================================
Q0123:             MOV   4BHMOV                       ;0123   F5 4B
                   INC   23HINC                       ;0125   05 23
                   MOV   A,2MOV                       ;0127   E5 23
                   XRL   A,#0AH                       ;0129   64 0A
                   JZ    Q01JZ                        ;012B   60 03
                   LJMP  Q01C7                        ;012D   02 01 C7
;==========================================================================
Q0130:             MOV   23HMOV                       ;0130   F5 23
                   INC   22HINC                       ;0132   05 22
                   MOV   A,2MOV                       ;0134   E5 22
                   XRL   A,#0AH                       ;0136   64 0A
                   JZ    Q01JZ                        ;0138   60 03
                   LJMP  Q01C7                        ;013A   02 01 C7
;==========================================================================
Q013D:             MOV   22HMOV                       ;013D   F5 22
                   RET      RET                       ;013F   22
;==========================================================================
Q0140:             MOV   A,RMOV                       ;0140   EF
                   CPL   A                            ;0141   F4
                   JNZ   Q01JNZ                       ;0142   70 03
                   LJMP  Q01C7                        ;0144   02 01 C7
;==========================================================================
Q0147:             DEC   45HDEC                       ;0147   15 45
                   MOV   A,4MOV                       ;0149   E5 45
                   JZ    Q01JZ                        ;014B   60 0D
                   INC   46HINC                       ;014D   05 46
                   MOV   A,4MOV                       ;014F   E5 46
                   XRL   A,#0AH                       ;0151   64 0A
                   JNZ   Q01JNZ                       ;0153   70 72
Q0155:             MOV   46HMOV                       ;0155   F5 46
                   INC   53HINC                       ;0157   05 53
                   RET      RET                       ;0159   22
;==========================================================================
Q015A:             MOV   A,4MOV                       ;015A   E5 45
                   JNZ   Q01JNZ                       ;015C   70 69
                   MOV   A,3MOV                       ;015E   E5 39
                   CJNE  A,#02H,Q0177                 ;0160   B4 02 14
                   MOV   A,3MOV                       ;0163   E5 3B
                   CJNE  A,#1CH,Q016D                 ;0165   B4 1C 05
                   MOV   45HMOVCH                     ;0168   75 45 1C
                   SJMP  Q017A                        ;016B   80 0D
Q016D:             MOV   A,3MOV                       ;016D   E5 3B
                   CJNE  A,#1DH,Q0180                 ;016F   B4 1D 0E
                   MOV   45HMOVDH                     ;0172   75 45 1D
                   SJMP  Q017A                        ;0175   80 03
Q0177:             MOV   42HMOVEH                     ;0177   75 42 1E
Q017A:             MOV   46HMOV1H                     ;017A   75 46 01
                   CLR   A                            ;017D   E4
                   MOV   53HMOV                       ;017E   F5 53
Q0180:             DEC   41HDEC                       ;0180   15 41
                   MOV   A,4MOV                       ;0182   E5 41
                   JZ    Q01JZ                        ;0184   60 0D
                   INC   39HINC                       ;0186   05 39
                   MOV   A,3MOV                       ;0188   E5 39
                   XRL   A,#0AH                       ;018A   64 0A
                   JNZ   Q01JNZ                       ;018C   70 39
Q018E:             MOV   39HMOV                       ;018E   F5 39
                   INC   47HINC                       ;0190   05 47
                   RET      RET                       ;0192   22
;==========================================================================
Q0193:             MOV   A,4MOV                       ;0193   E5 41
                   JNZ   Q01JNZ                       ;0195   70 30
                   MOV   41HMOVCH                     ;0197   75 41 0C
                   MOV   39HMOV1H                     ;019A   75 39 01
                   MOV   47HMOV                       ;019D   F5 47
                   INC   3FHINC                       ;019F   05 3F
                   MOV   A,3MOV                       ;01A1   E5 3F
                   CJNE  A,#0AH,Q01C7                 ;01A3   B4 0A 21
                   CLR   A                            ;01A6   E4
                   MOV   3FHMOV                       ;01A7   F5 3F
                   INC   4BHINC                       ;01A9   05 4B
                   MOV   A,4MOV                       ;01AB   E5 4B
                   CJNE  A,#0AH,Q01C7                 ;01AD   B4 0A 17
                   CLR   A                            ;01B0   E4
                   MOV   4BHMOV                       ;01B1   F5 4B
                   INC   23HINC                       ;01B3   05 23
                   MOV   A,2MOV                       ;01B5   E5 23
                   CJNE  A,#0AH,Q01C7                 ;01B7   B4 0A 0D
                   CLR   A                            ;01BA   E4
                   MOV   23HMOV                       ;01BB   F5 23
                   INC   22HINC                       ;01BD   05 22
                   MOV   A,2MOV                       ;01BF   E5 22
                   CJNE  A,#0AH,Q01C7                 ;01C1   B4 0A 03
                   CLR   A                            ;01C4   E4
                   MOV   22HMOV                       ;01C5   F5 22
Q01C7:             RET      RET                       ;01C7   22
;==========================================================================
Q01C8:             MOV   50HMOVH                      ;01C8   85 30 50
                   MOV   4AHMOVH                      ;01CB   85 2F 4A
Q01CE:             MOV   DPTMOV7FFFH                  ;01CE   90 7F FF
                   MOV   A,#MOVH                      ;01D1   74 DF
                   MOVX  @DPTR,A                      ;01D3   F0
                   MOV   A,3MOV                       ;01D4   E5 3D
                   ADD   A,AADD                       ;01D6   25 E0
                   ADD   A,#ADD                       ;01D8   24 6D
                   MOV   DPLMOV                       ;01DA   F5 82
                   CLR   A                            ;01DC   E4
                   ADDC  A,#0AH                       ;01DD   34 0A
                   MOV   DPHMOV                       ;01DF   F5 83
                   MOV   A,#MOV                       ;01E1   74 01
                   MOVC  A,@A+DPTR                    ;01E3   93
                   MOV   DPTMOV0BFFFH                 ;01E4   90 BF FF
                   LCALL Q0A03                        ;01E7   12 0A 03
                   MOV   DPTMOV7FFFH                  ;01EA   90 7F FF
                   MOV   A,#MOVH                      ;01ED   74 EF
                   MOVX  @DPTR,A                      ;01EF   F0
                   MOV   A,3MOV                       ;01F0   E5 3A
                   ADD   A,AADD                       ;01F2   25 E0
                   ADD   A,#ADD                       ;01F4   24 6D
                   MOV   DPLMOV                       ;01F6   F5 82
                   CLR   A                            ;01F8   E4
                   ADDC  A,#0AH                       ;01F9   34 0A
                   MOV   DPHMOV                       ;01FB   F5 83
                   MOV   A,#MOV                       ;01FD   74 01
                   MOVC  A,@A+DPTR                    ;01FF   93
                   MOV   DPTMOV0BFFFH                 ;0200   90 BF FF
                   LCALL Q0A03                        ;0203   12 0A 03
                   MOV   DPTMOV7FFFH                  ;0206   90 7F FF
                   MOV   A,#MOVH                      ;0209   74 F7
                   MOVX  @DPTR,A                      ;020B   F0
                   MOV   A,4MOV                       ;020C   E5 49
                   ADD   A,AADD                       ;020E   25 E0
                   ADD   A,#ADD                       ;0210   24 6D
                   MOV   DPLMOV                       ;0212   F5 82
                   CLR   A                            ;0214   E4
                   ADDC  A,#0AH                       ;0215   34 0A
                   MOV   DPHMOV                       ;0217   F5 83
                   MOV   A,#MOV                       ;0219   74 01
                   MOVC  A,@A+DPTR                    ;021B   93
                   ORL   A,#80H                       ;021C   44 80
                   MOV   DPTMOV0BFFFH                 ;021E   90 BF FF
                   LCALL Q0A03                        ;0221   12 0A 03
                   MOV   DPTMOV7FFFH                  ;0224   90 7F FF
                   MOV   A,#MOVH                      ;0227   74 FB
                   MOVX  @DPTR,A                      ;0229   F0
                   MOV   A,4MOV                       ;022A   E5 44
                   ADD   A,AADD                       ;022C   25 E0
                   ADD   A,#ADD                       ;022E   24 6D
                   MOV   DPLMOV                       ;0230   F5 82
                   CLR   A                            ;0232   E4
                   ADDC  A,#0AH                       ;0233   34 0A
                   MOV   DPHMOV                       ;0235   F5 83
                   MOV   A,#MOV                       ;0237   74 01
                   MOVC  A,@A+DPTR                    ;0239   93
                   MOV   DPTMOV0BFFFH                 ;023A   90 BF FF
                   LCALL Q0A03                        ;023D   12 0A 03
                   MOV   DPTMOV7FFFH                  ;0240   90 7F FF
                   MOV   A,#MOVH                      ;0243   74 FD
                   MOVX  @DPTR,A                      ;0245   F0
                   MOV   A,5MOV                       ;0246   E5 50
                   ADD   A,AADD                       ;0248   25 E0
                   ADD   A,#ADD                       ;024A   24 6D
                   MOV   DPLMOV                       ;024C   F5 82
                   CLR   A                            ;024E   E4
                   ADDC  A,#0AH                       ;024F   34 0A
                   MOV   DPHMOV                       ;0251   F5 83
                   MOV   A,#MOV                       ;0253   74 01
                   MOVC  A,@A+DPTR                    ;0255   93
                   ORL   A,#80H                       ;0256   44 80
                   MOV   DPTMOV0BFFFH                 ;0258   90 BF FF
                   LCALL Q0A03                        ;025B   12 0A 03
                   MOV   DPTMOV7FFFH                  ;025E   90 7F FF
                   MOV   A,#MOVH                      ;0261   74 FE
                   MOVX  @DPTR,A                      ;0263   F0
                   MOV   A,4MOV                       ;0264   E5 4A
                   ADD   A,AADD                       ;0266   25 E0
                   ADD   A,#ADD                       ;0268   24 6D
                   MOV   DPLMOV                       ;026A   F5 82
                   CLR   A                            ;026C   E4
                   ADDC  A,#0AH                       ;026D   34 0A
                   MOV   DPHMOV                       ;026F   F5 83
                   MOV   A,#MOV                       ;0271   74 01
                   MOVC  A,@A+DPTR                    ;0273   93
                   MOV   DPTMOV0BFFFH                 ;0274   90 BF FF
                   LCALL Q0A03                        ;0277   12 0A 03
                   MOV   DPTMOV0DFFFH                 ;027A   90 DF FF
                   MOV   A,#MOV                       ;027D   74 7F
                   MOVX  @DPTR,A                      ;027F   F0
                   MOV   A,4MOV                       ;0280   E5 46
                   LCALL Q09F2                        ;0282   12 09 F2
                   MOV   DPTMOV0DFFFH                 ;0285   90 DF FF
                   MOV   A,#MOVH                      ;0288   74 BF
                   MOVX  @DPTR,A                      ;028A   F0
                   MOV   A,5MOV                       ;028B   E5 53
                   LCALL Q09F2                        ;028D   12 09 F2
                   MOV   DPTMOV0DFFFH                 ;0290   90 DF FF
                   MOV   A,#MOVH                      ;0293   74 DF
                   MOVX  @DPTR,A                      ;0295   F0
                   MOV   A,3MOV                       ;0296   E5 39
                   ADD   A,AADD                       ;0298   25 E0
                   ADD   A,#ADD                       ;029A   24 6D
                   MOV   DPLMOV                       ;029C   F5 82
                   CLR   A                            ;029E   E4
                   ADDC  A,#0AH                       ;029F   34 0A
                   MOV   DPHMOV                       ;02A1   F5 83
                   MOV   A,#MOV                       ;02A3   74 01
                   MOVC  A,@A+DPTR                    ;02A5   93
                   ORL   A,#80H                       ;02A6   44 80
                   LCALL Q0A00                        ;02A8   12 0A 00
                   MOV   DPTMOV0DFFFH                 ;02AB   90 DF FF
                   MOV   A,#MOVH                      ;02AE   74 EF
                   MOVX  @DPTR,A                      ;02B0   F0
                   MOV   A,4MOV                       ;02B1   E5 47
                   LCALL Q09F2                        ;02B3   12 09 F2
                   MOV   DPTMOV0DFFFH                 ;02B6   90 DF FF
                   MOV   A,#MOVH                      ;02B9   74 F7
                   MOVX  @DPTR,A                      ;02BB   F0
                   MOV   A,3MOV                       ;02BC   E5 3F
                   ADD   A,AADD                       ;02BE   25 E0
                   ADD   A,#ADD                       ;02C0   24 6D
                   MOV   DPLMOV                       ;02C2   F5 82
                   CLR   A                            ;02C4   E4
                   ADDC  A,#0AH                       ;02C5   34 0A
                   MOV   DPHMOV                       ;02C7   F5 83
                   MOV   A,#MOV                       ;02C9   74 01
                   MOVC  A,@A+DPTR                    ;02CB   93
                   ORL   A,#80H                       ;02CC   44 80
                   LCALL Q0A00                        ;02CE   12 0A 00
                   MOV   DPTMOV0DFFFH                 ;02D1   90 DF FF
                   MOV   A,#MOVH                      ;02D4   74 FB
                   MOVX  @DPTR,A                      ;02D6   F0
                   MOV   A,4MOV                       ;02D7   E5 4B
                   LCALL Q09F2                        ;02D9   12 09 F2
                   MOV   DPTMOV0DFFFH                 ;02DC   90 DF FF
                   MOV   A,#MOVH                      ;02DF   74 FD
                   MOVX  @DPTR,A                      ;02E1   F0
                   MOV   A,2MOV                       ;02E2   E5 23
                   LCALL Q09F2                        ;02E4   12 09 F2
                   MOV   DPTMOV0DFFFH                 ;02E7   90 DF FF
                   MOV   A,#MOVH                      ;02EA   74 FE
                   MOVX  @DPTR,A                      ;02EC   F0
                   MOV   A,2MOV                       ;02ED   E5 22
                   LCALL Q09F2                        ;02EF   12 09 F2
                   MOV   DPTMOV0F7FFH                 ;02F2   90 F7 FF
                   MOV   A,#MOVH                      ;02F5   74 F7
                   MOVX  @DPTR,A                      ;02F7   F0
                   MOV   A,3MOV                       ;02F8   E5 32
                   ADD   A,AADD                       ;02FA   25 E0
                   ADD   A,#ADD                       ;02FC   24 6D
                   MOV   DPLMOV                       ;02FE   F5 82
                   CLR   A                            ;0300   E4
                   ADDC  A,#0AH                       ;0301   34 0A
                   MOV   DPHMOV                       ;0303   F5 83
                   MOV   A,#MOV                       ;0305   74 01
                   MOVC  A,@A+DPTR                    ;0307   93
                   MOV   DPTMOV0FBFFH                 ;0308   90 FB FF
                   LCALL Q0A03                        ;030B   12 0A 03
                   MOV   DPTMOV0F7FFH                 ;030E   90 F7 FF
                   MOV   A,#MOVH                      ;0311   74 FB
                   MOVX  @DPTR,A                      ;0313   F0
                   MOV   A,3MOV                       ;0314   E5 37
                   ADD   A,AADD                       ;0316   25 E0
                   ADD   A,#ADD                       ;0318   24 6D
                   MOV   DPLMOV                       ;031A   F5 82
                   CLR   A                            ;031C   E4
                   ADDC  A,#0AH                       ;031D   34 0A
                   MOV   DPHMOV                       ;031F   F5 83
                   MOV   A,#MOV                       ;0321   74 01
                   MOVC  A,@A+DPTR                    ;0323   93
                   MOV   DPTMOV0FBFFH                 ;0324   90 FB FF
                   LCALL Q0A03                        ;0327   12 0A 03
                   MOV   DPTMOV0F7FFH                 ;032A   90 F7 FF
                   MOV   A,#MOVH                      ;032D   74 FD
                   MOVX  @DPTR,A                      ;032F   F0
                   MOV   A,4MOV                       ;0330   E5 40
                   ADD   A,AADD                       ;0332   25 E0
                   ADD   A,#ADD                       ;0334   24 6D
                   MOV   DPLMOV                       ;0336   F5 82
                   CLR   A                            ;0338   E4
                   ADDC  A,#0AH                       ;0339   34 0A
                   MOV   DPHMOV                       ;033B   F5 83
                   MOV   A,#MOV                       ;033D   74 01
                   MOVC  A,@A+DPTR                    ;033F   93
                   MOV   DPTMOV0FBFFH                 ;0340   90 FB FF
                   LCALL Q0A03                        ;0343   12 0A 03
                   MOV   DPTMOV0F7FFH                 ;0346   90 F7 FF
                   MOV   A,#MOVH                      ;0349   74 FE
                   MOVX  @DPTR,A                      ;034B   F0
                   MOV   A,3MOV                       ;034C   E5 3E
                   ADD   A,AADD                       ;034E   25 E0
                   ADD   A,#ADD                       ;0350   24 6D
                   MOV   DPLMOV                       ;0352   F5 82
                   CLR   A                            ;0354   E4
                   ADDC  A,#0AH                       ;0355   34 0A
                   MOV   DPHMOV                       ;0357   F5 83
                   MOV   A,#MOV                       ;0359   74 01
                   MOVC  A,@A+DPTR                    ;035B   93
                   MOV   DPTMOV0FBFFH                 ;035C   90 FB FF
                   MOVX  @DPTR,A                      ;035F   F0
                   MOV   R7,MOVH                      ;0360   7F 03
                   MOV   R6,MOVH                      ;0362   7E 00
                   LJMP  Q0A08                        ;0364   02 0A 08
;==========================================================================
Q0367:             JNB   20HJNBQ03A3                  ;0367   30 05 39
                   MOV   A,5MOV                       ;036A   E5 52
                   XRL   A,#18H                       ;036C   64 18
                   JZ    Q03JZ                        ;036E   60 20
                   INC   52HINC                       ;0370   05 52
                   DEC   30HDEC                       ;0372   15 30
                   MOV   A,3MOV                       ;0374   E5 30
                   CPL   A                            ;0376   F4
                   JZ    Q03JZ                        ;0377   60 03
                   LJMP  Q0500                        ;0379   02 05 00
;==========================================================================
Q037C:             MOV   30HMOV9H                     ;037C   75 30 09
                   DEC   2FHDEC                       ;037F   15 2F
                   MOV   A,2MOV                       ;0381   E5 2F
                   CPL   A                            ;0383   F4
                   JZ    Q03JZ                        ;0384   60 03
                   LJMP  Q0500                        ;0386   02 05 00
;==========================================================================
Q0389:             MOV   2FHMOV2H                     ;0389   75 2F 02
                   MOV   30HMOV3H                     ;038C   75 30 03
                   RET      RET                       ;038F   22
;==========================================================================
Q0390:             MOV   A,5MOV                       ;0390   E5 52
                   XRL   A,#18H                       ;0392   64 18
                   JZ    Q03JZ                        ;0394   60 03
                   LJMP  Q0500                        ;0396   02 05 00
;==========================================================================
Q0399:             MOV   52HMOV1H                     ;0399   75 52 01
                   MOV   30HMOV3H                     ;039C   75 30 03
                   MOV   2FHMOV2H                     ;039F   75 2F 02
                   RET      RET                       ;03A2   22
;==========================================================================
Q03A3:             JNB   20HJNBQ03C1                  ;03A3   30 00 1B
                   DEC   2DHDEC                       ;03A6   15 2D
                   MOV   A,2MOV                       ;03A8   E5 2D
                   CPL   A                            ;03AA   F4
                   JZ    Q03JZ                        ;03AB   60 03
                   LJMP  Q0500                        ;03AD   02 05 00
;==========================================================================
Q03B0:             MOV   2DHMOV9H                     ;03B0   75 2D 09
                   DEC   2AHDEC                       ;03B3   15 2A
                   MOV   A,2MOV                       ;03B5   E5 2A
                   CPL   A                            ;03B7   F4
                   JZ    Q03JZ                        ;03B8   60 03
                   LJMP  Q0500                        ;03BA   02 05 00
;==========================================================================
Q03BD:             MOV   2AHMOV5H                     ;03BD   75 2A 05
                   RET      RET                       ;03C0   22
;==========================================================================
Q03C1:             JNB   20HJNBQ03F9                  ;03C1   30 04 35
                   DEC   28HDEC                       ;03C4   15 28
                   MOV   A,2MOV                       ;03C6   E5 28
                   CPL   A                            ;03C8   F4
                   JZ    Q03JZ                        ;03C9   60 03
                   LJMP  Q0500                        ;03CB   02 05 00
;==========================================================================
Q03CE:             MOV   28HMOV9H                     ;03CE   75 28 09
                   DEC   3CHDEC                       ;03D1   15 3C
                   MOV   A,3MOV                       ;03D3   E5 3C
                   CPL   A                            ;03D5   F4
                   JZ    Q03JZ                        ;03D6   60 03
                   LJMP  Q0500                        ;03D8   02 05 00
;==========================================================================
Q03DB:             MOV   3CHMOV9H                     ;03DB   75 3C 09
                   DEC   51HDEC                       ;03DE   15 51
                   MOV   A,5MOV                       ;03E0   E5 51
                   CPL   A                            ;03E2   F4
                   JZ    Q03JZ                        ;03E3   60 03
                   LJMP  Q0500                        ;03E5   02 05 00
;==========================================================================
Q03E8:             MOV   51HMOV9H                     ;03E8   75 51 09
                   DEC   29HDEC                       ;03EB   15 29
                   MOV   A,2MOV                       ;03ED   E5 29
                   CPL   A                            ;03EF   F4
                   JZ    Q03JZ                        ;03F0   60 03
                   LJMP  Q0500                        ;03F2   02 05 00
;==========================================================================
Q03F5:             MOV   29HMOV9H                     ;03F5   75 29 09
                   RET      RET                       ;03F8   22
;==========================================================================
Q03F9:             JNB   20HJNBQ0427                  ;03F9   30 03 2B
                   MOV   A,4MOV                       ;03FC   E5 41
                   XRL   A,#0CH                       ;03FE   64 0C
                   JZ    Q04JZ                        ;0400   60 12
                   INC   41HINC                       ;0402   05 41
                   DEC   54HDEC                       ;0404   15 54
                   MOV   A,5MOV                       ;0406   E5 54
                   CPL   A                            ;0408   F4
                   JZ    Q04JZ                        ;0409   60 03
                   LJMP  Q0500                        ;040B   02 05 00
;==========================================================================
Q040E:             MOV   54HMOV9H                     ;040E   75 54 09
                   DEC   38HDEC                       ;0411   15 38
                   RET      RET                       ;0413   22
;==========================================================================
Q0414:             MOV   A,4MOV                       ;0414   E5 41
                   XRL   A,#0CH                       ;0416   64 0C
                   JZ    Q04JZ                        ;0418   60 03
                   LJMP  Q0500                        ;041A   02 05 00
;==========================================================================
Q041D:             MOV   41HMOV1H                     ;041D   75 41 01
                   MOV   54HMOV2H                     ;0420   75 54 02
                   MOV   38HMOV1H                     ;0423   75 38 01
                   RET      RET                       ;0426   22
;==========================================================================
Q0427:             JB    20HJB,Q042D                  ;0427   20 02 03
                   LJMP  Q04D5                        ;042A   02 04 D5
;==========================================================================
Q042D:             MOV   A,5MOV                       ;042D   E5 54
                   ORL   A,#0FEH                      ;042F   44 FE
                   MOV   R7,MOV                       ;0431   FF
                   CPL   A                            ;0432   F4
                   JNZ   Q04JNZ                       ;0433   70 27
                   MOV   A,4MOV                       ;0435   E5 42
                   XRL   A,#1FH                       ;0437   64 1F
                   JZ    Q04JZ                        ;0439   60 0E
                   INC   42HINC                       ;043B   05 42
                   DEC   2EHDEC                       ;043D   15 2E
                   MOV   A,2MOV                       ;043F   E5 2E
                   CPL   A                            ;0441   F4
                   JZ    Q04JZ                        ;0442   60 03
                   LJMP  Q0500                        ;0444   02 05 00
;==========================================================================
Q0447:             SJMP  Q047B                        ;0447   80 32
Q0449:             MOV   A,4MOV                       ;0449   E5 42
                   XRL   A,#1FH                       ;044B   64 1F
                   JZ    Q04JZ                        ;044D   60 03
                   LJMP  Q0500                        ;044F   02 05 00
;==========================================================================
Q0452:             MOV   42HMOV1H                     ;0452   75 42 01
                   MOV   2EHMOV1H                     ;0455   75 2E 01
                   MOV   43HMOV3H                     ;0458   75 43 03
                   RET      RET                       ;045B   22
;==========================================================================
Q045C:             MOV   A,RMOV                       ;045C   EF
                   CPL   A                            ;045D   F4
                   JNZ   Q04JNZ                       ;045E   70 03
                   LJMP  Q0500                        ;0460   02 05 00
;==========================================================================
Q0463:             MOV   A,5MOV                       ;0463   E5 54
                   XRL   A,#02H                       ;0465   64 02
                   JNZ   Q04JNZ                       ;0467   70 3B
                   MOV   A,4MOV                       ;0469   E5 45
                   XRL   A,3BH                        ;046B   65 3B
                   JZ    Q04JZ                        ;046D   60 12
                   INC   45HINC                       ;046F   05 45
                   DEC   2EHDEC                       ;0471   15 2E
                   MOV   A,2MOV                       ;0473   E5 2E
                   CPL   A                            ;0475   F4
                   JZ    Q04JZ                        ;0476   60 03
                   LJMP  Q0500                        ;0478   02 05 00
;==========================================================================
Q047B:             MOV   2EHMOV9H                     ;047B   75 2E 09
                   DEC   43HDEC                       ;047E   15 43
                   RET      RET                       ;0480   22
;==========================================================================
Q0481:             MOV   A,4MOV                       ;0481   E5 45
                   XRL   A,3BH                        ;0483   65 3B
                   JNZ   Q05JNZ                       ;0485   70 79
                   MOV   A,3MOV                       ;0487   E5 3B
                   CJNE  A,#1CH,Q0494                 ;0489   B4 1C 08
                   MOV   45HMOV1H                     ;048C   75 45 01
                   MOV   2EHMOV8H                     ;048F   75 2E 08
                   SJMP  Q04A0                        ;0492   80 0C
Q0494:             MOV   A,3MOV                       ;0494   E5 3B
                   XRL   A,#1DH                       ;0496   64 1D
                   JNZ   Q05JNZ                       ;0498   70 66
                   MOV   45HMOV1H                     ;049A   75 45 01
                   MOV   2EHMOV9H                     ;049D   75 2E 09
Q04A0:             MOV   43HMOV2H                     ;04A0   75 43 02
                   RET      RET                       ;04A3   22
;==========================================================================
Q04A4:             MOV   A,5MOV                       ;04A4   E5 54
                   XRL   A,#02H                       ;04A6   64 02
                   JZ    Q05JZ                        ;04A8   60 56
                   MOV   A,3MOV                       ;04AA   E5 36
                   XRL   A,#1EH                       ;04AC   64 1E
                   JZ    Q04JZ                        ;04AE   60 13
                   INC   36HINC                       ;04B0   05 36
                   MOV   45HMOVH                      ;04B2   85 36 45
                   DEC   2EHDEC                       ;04B5   15 2E
                   MOV   A,2MOV                       ;04B7   E5 2E
                   CPL   A                            ;04B9   F4
                   JNZ   Q05JNZ                       ;04BA   70 44
                   MOV   2EHMOV9H                     ;04BC   75 2E 09
                   DEC   43HDEC                       ;04BF   15 43
                   SJMP  Q04D1                        ;04C1   80 0E
Q04C3:             MOV   A,3MOV                       ;04C3   E5 36
                   XRL   A,#1EH                       ;04C5   64 1E
                   JNZ   Q05JNZ                       ;04C7   70 37
                   MOV   36HMOV1H                     ;04C9   75 36 01
                   MOV   2EHMOV                       ;04CC   F5 2E
                   MOV   43HMOV3H                     ;04CE   75 43 03
Q04D1:             MOV   45HMOVH                      ;04D1   85 36 45
                   RET      RET                       ;04D4   22
;==========================================================================
Q04D5:             JNB   20HJNBQ0500                  ;04D5   30 06 28
                   DEC   2CHDEC                       ;04D8   15 2C
                   MOV   A,2MOV                       ;04DA   E5 2C
                   CJNE  A,#0FFH,Q0500                ;04DC   B4 FF 21
                   MOV   2CHMOV9H                     ;04DF   75 2C 09
                   DEC   21HDEC                       ;04E2   15 21
                   MOV   A,2MOV                       ;04E4   E5 21
                   CJNE  A,#0FFH,Q0500                ;04E6   B4 FF 17
                   MOV   21HMOV9H                     ;04E9   75 21 09
                   DEC   24HDEC                       ;04EC   15 24
                   MOV   A,2MOV                       ;04EE   E5 24
                   CJNE  A,#0FFH,Q0500                ;04F0   B4 FF 0D
                   MOV   24HMOV9H                     ;04F3   75 24 09
                   DEC   2BHDEC                       ;04F6   15 2B
                   MOV   A,2MOV                       ;04F8   E5 2B
                   CJNE  A,#0FFH,Q0500                ;04FA   B4 FF 03
                   MOV   2BHMOV9H                     ;04FD   75 2B 09
Q0500:             RET      RET                       ;0500   22
;==========================================================================
Q0501:             JB    20HJB,Q0507                  ;0501   20 06 03
                   LJMP  Q05A6                        ;0504   02 05 A6
;==========================================================================
Q0507:             MOV   2CHMOVH                      ;0507   85 32 2C
                   MOV   21HMOVH                      ;050A   85 37 21
                   MOV   24HMOVH                      ;050D   85 40 24
                   MOV   2BHMOVH                      ;0510   85 3E 2B
Q0513:             JNB   20HJNBQ056F                  ;0513   30 06 59
                   CLR   A                            ;0516   E4
                   MOV   08HMOV                       ;0517   F5 08
Q0519:             MOV   32HMOVAH                     ;0519   75 32 0A
                   MOV   37HMOVAH                     ;051C   75 37 0A
                   MOV   40HMOVAH                     ;051F   75 40 0A
                   MOV   3EHMOVAH                     ;0522   75 3E 0A
                   MOV   46HMOVH                      ;0525   85 2E 46
                   MOV   53HMOVH                      ;0528   85 43 53
                   LCALL Q01CE                        ;052B   12 01 CE
                   LCALL Q0989                        ;052E   12 09 89
                   JB    20HJB,Q0537                  ;0531   20 06 03
                   MOV   08HMOV3H                     ;0534   75 08 33
Q0537:             INC   08HINC                       ;0537   05 08
                   MOV   A,0MOV                       ;0539   E5 08
                   CLR   C                            ;053B   C3
                   SUBB  A,#12H                       ;053C   94 12
                   JC    Q05JC                        ;053E   40 D9
                   JNB   20HJNBQ0513                  ;0540   30 06 D0
                   CLR   A                            ;0543   E4
                   MOV   08HMOV                       ;0544   F5 08
Q0546:             MOV   A,0MOV                       ;0546   E5 08
                   CLR   C                            ;0548   C3
                   SUBB  A,#12H                       ;0549   94 12
                   JNC   Q05JNC                       ;054B   50 C6
                   MOV   32HMOVH                      ;054D   85 2C 32
                   MOV   37HMOVH                      ;0550   85 21 37
                   MOV   40HMOVH                      ;0553   85 24 40
                   MOV   3EHMOVH                      ;0556   85 2B 3E
                   MOV   46HMOVH                      ;0559   85 2E 46
                   MOV   53HMOVH                      ;055C   85 43 53
                   LCALL Q01CE                        ;055F   12 01 CE
                   LCALL Q0989                        ;0562   12 09 89
                   JB    20HJB,Q056B                  ;0565   20 06 03
                   MOV   08HMOV3H                     ;0568   75 08 33
Q056B:             INC   08HINC                       ;056B   05 08
                   SJMP  Q0546                        ;056D   80 D7
Q056F:             JNB   20HJNBQ05A6                  ;056F   30 01 34
                   CLR   20H.1                        ;0572   C2 01
                   MOV   49HMOVH                      ;0574   85 2D 49
                   MOV   44HMOVH                      ;0577   85 2A 44
                   MOV   50HMOVH                      ;057A   85 30 50
                   MOV   4AHMOVH                      ;057D   85 2F 4A
Q057F:             ORL   A,R2                         ;057F   4A
                   MOV   3FHMOVH                      ;0580   85 28 3F
                   MOV   4BHMOVH                      ;0583   85 3C 4B
                   MOV   23HMOVH                      ;0586   85 51 23
                   MOV   22HMOVH                      ;0589   85 29 22
                   MOV   39HMOVH                      ;058C   85 54 39
                   MOV   47HMOVH                      ;058F   85 38 47
                   MOV   46HMOVH                      ;0592   85 2E 46
                   MOV   53HMOVH                      ;0595   85 43 53
                   MOV   32HMOVH                      ;0598   85 2C 32
                   MOV   37HMOVH                      ;059B   85 21 37
                   MOV   40HMOVH                      ;059E   85 24 40
                   MOV   3EHMOVH                      ;05A1   85 2B 3E
                   SETB  TR0                          ;05A4   D2 8C
Q05A6:             RET      RET                       ;05A6   22
;==========================================================================
Q05A7:             MOV   R0,MOVH                      ;05A7   78 7F
                   CLR   A                            ;05A9   E4
Q05AA:             MOV   @R0MOV                       ;05AA   F6
                   DJNZ  R0,Q05AA                     ;05AB   D8 FD
                   MOV   SP,MOVH  SP                  ;05AD   75 81 54
                   LJMP  Q05EE                        ;05B0   02 05 EE
;==========================================================================
Q05B3:             LJMP  Q0A26                        ;05B3   02 0A 26
;==========================================================================
Q05B6:             CLR   A                            ;05B6   E4
                   MOVC  A,@A+DPTR                    ;05B7   93
                   INC   DPTINC                       ;05B8   A3
                   MOV   R0,MOV                       ;05B9   F8
Q05BA:             CLR   A                            ;05BA   E4
                   MOVC  A,@A+DPTR                    ;05BB   93
                   INC   DPTINC                       ;05BC   A3
                   JC    Q05JC                        ;05BD   40 03
                   MOV   @R0MOV                       ;05BF   F6
                   SJMP  Q05C3                        ;05C0   80 01
Q05C2:             MOVX  @R0,A                        ;05C2   F2
Q05C3:             INC   R0 INC                       ;05C3   08
                   DJNZ  R7,Q05BA                     ;05C4   DF F4
                   SJMP  Q05F1                        ;05C6   80 29
Q05C8:             CLR   A                            ;05C8   E4
                   MOVC  A,@A+DPTR                    ;05C9   93
                   INC   DPTINC                       ;05CA   A3
                   MOV   R0,MOV                       ;05CB   F8
                   ANL   A,#07H                       ;05CC   54 07
                   ADD   A,#ADD                       ;05CE   24 0C
                   XCH   A,R0                         ;05D0   C8
                   CLR   C                            ;05D1   C3
                   RLC   A                            ;05D2   33
                   SWAP  A                            ;05D3   C4
                   ANL   A,#0FH                       ;05D4   54 0F
                   ORL   A,#20H                       ;05D6   44 20
                   XCH   A,R0                         ;05D8   C8
                   MOVC  A,@A+PC                      ;05D9   83
                   JC    Q05JC                        ;05DA   40 04
                   CPL   A                            ;05DC   F4
                   ANL   A,@R0                        ;05DD   56
                   SJMP  Q05E1                        ;05DE   80 01
Q05E0:             ORL   A,@R0                        ;05E0   46
Q05E1:             MOV   @R0MOV                       ;05E1   F6
                   DJNZ  R7,Q05C8                     ;05E2   DF E4
                   SJMP  Q05F1                        ;05E4   80 0B

                   INC   A  INC                       ;05E8   04
                   INC   R0 INC                       ;05E9   08
                   JBC   24H.0,Q062D                  ;05EA   10 20 40
                   SJMP  Q057F                        ;05ED   80 90
Q05EE:             MOV   DPTMOV0798H                  ;05EE   90 07 98
Q05F1:             CLR   A                            ;05F1   E4
                   MOV   R6,MOVH                      ;05F2   7E 01
                   MOVC  A,@A+DPTR                    ;05F4   93
                   JZ    Q05JZ                        ;05F5   60 BC
                   INC   DPTINC                       ;05F7   A3
                   MOV   R7,MOV                       ;05F8   FF
                   ANL   A,#3FH                       ;05F9   54 3F
                   JNB   ACCJNBQ0607                  ;05FB   30 E5 09
                   ANL   A,#1FH                       ;05FE   54 1F
                   MOV   R6,MOV                       ;0600   FE
                   CLR   A                            ;0601   E4
                   MOVC  A,@A+DPTR                    ;0602   93
                   INC   DPTINC                       ;0603   A3
                   JZ    Q06JZ                        ;0604   60 01
                   INC   R6 INC                       ;0606   0E
Q0607:             XCH   A,R7                         ;0607   CF
                   ANL   A,#0C0H                      ;0608   54 C0
                   ADD   A,AADD                       ;060A   25 E0
                   JZ    Q05JZ                        ;060C   60 A8
                   JC    Q05JC                        ;060E   40 B8
                   CLR   A                            ;0610   E4
                   MOVC  A,@A+DPTR                    ;0611   93
                   INC   DPTINC                       ;0612   A3
                   MOV   R2,MOV                       ;0613   FA
                   CLR   A                            ;0614   E4
                   MOVC  A,@A+DPTR                    ;0615   93
                   INC   DPTINC                       ;0616   A3
                   MOV   R0,MOV                       ;0617   F8
Q0618:             CLR   A                            ;0618   E4
                   MOVC  A,@A+DPTR                    ;0619   93
                   INC   DPTINC                       ;061A   A3
                   XCH   A,R0                         ;061B   C8
                   XCH   A,DPL                        ;061C   C5 82
                   XCH   A,R0                         ;061E   C8
                   XCH   A,R2                         ;061F   CA
                   XCH   A,DPH                        ;0620   C5 83
                   XCH   A,R2                         ;0622   CA
                   MOVX  @DPTR,A                      ;0623   F0
                   INC   DPTINC                       ;0624   A3
                   XCH   A,R0                         ;0625   C8
                   XCH   A,DPL                        ;0626   C5 82
                   XCH   A,R0                         ;0628   C8
                   XCH   A,R2                         ;0629   CA
                   XCH   A,DPH                        ;062A   C5 83
                   XCH   A,R2                         ;062C   CA
Q062D:             DJNZ  R7,Q0618                     ;062D   DF E9
                   DJNZ  R6,Q0618                     ;062F   DE E7
                   SJMP  Q05F1                        ;0631   80 BE
Q0633:             MOV   35HMOVH                      ;0633   85 28 35
                   MOV   27HMOVH                      ;0636   85 3C 27
                   MOV   31HMOVH                      ;0639   85 51 31
                   MOV   34HMOVH                      ;063C   85 29 34
                   MOV   25HMOV0H                     ;063F   75 25 00
                   MOV   26HMOVH                      ;0642   85 28 26
                   MOV   A,3MOV                       ;0645   E5 3C
                   SWAP  A                            ;0647   C4
                   ANL   A,#0F0H                      ;0648   54 F0
                   MOV   3CHMOV                       ;064A   F5 3C
                   ANL   3CH,#0F0H                    ;064C   53 3C F0
                   MOV   A,3MOV                       ;064F   E5 3C
                   ADD   A,2ADD                       ;0651   25 26
                   MOV   26HMOV                       ;0653   F5 26
                   CLR   A                            ;0655   E4
                   ADDC  A,25H                        ;0656   35 25
                   MOV   25HMOV                       ;0658   F5 25
                   MOV   A,2MOV                       ;065A   E5 26
                   MOV   26HMOV0H                     ;065C   75 26 00
                   MOV   25HMOV                       ;065F   F5 25
                   MOV   A,5MOV                       ;0661   E5 51
                   ADD   A,2ADD                       ;0663   25 26
                   MOV   26HMOV                       ;0665   F5 26
                   CLR   A                            ;0667   E4
                   ADDC  A,25H                        ;0668   35 25
                   MOV   25HMOV                       ;066A   F5 25
                   MOV   A,2MOV                       ;066C   E5 29
                   SWAP  A                            ;066E   C4
                   ANL   A,#0F0H                      ;066F   54 F0
                   MOV   29HMOV                       ;0671   F5 29
                   ANL   29H,#0F0H                    ;0673   53 29 F0
                   MOV   A,2MOV                       ;0676   E5 29
                   ADD   A,2ADD                       ;0678   25 26
                   MOV   26HMOV                       ;067A   F5 26
                   CLR   A                            ;067C   E4
                   ADDC  A,25H                        ;067D   35 25
                   MOV   25HMOV                       ;067F   F5 25
                   MOV   4CHMOV                       ;0681   F5 4C
                   MOV   4DHMOV0H                     ;0683   75 4D 00
                   MOV   A,4MOV                       ;0686   E5 4C
                   MOV   4DHMOV                       ;0688   F5 4D
                   MOV   4CHMOV0H                     ;068A   75 4C 00
                   MOV   4EHMOV0H                     ;068D   75 4E 00
                   MOV   4FHMOVH                      ;0690   85 26 4F
                   MOV   A,4MOV                       ;0693   E5 4F
                   MOV   4FHMOV0H                     ;0695   75 4F 00
                   MOV   4EHMOV                       ;0698   F5 4E
                   MOV   A,4MOV                       ;069A   E5 4D
                   ADD   A,4ADD                       ;069C   25 4F
                   MOV   26HMOV                       ;069E   F5 26
                   MOV   A,4MOV                       ;06A0   E5 4C
                   ADDC  A,4EH                        ;06A2   35 4E
                   MOV   25HMOV                       ;06A4   F5 25
                   MOV   28HMOVH                      ;06A6   85 35 28
                   MOV   3CHMOVH                      ;06A9   85 27 3C
                   MOV   51HMOVH                      ;06AC   85 31 51
                   MOV   29HMOVH                      ;06AF   85 34 29
                   RET      RET                       ;06B2   22
;==========================================================================
Q06B3:             INC   33HINC                       ;06B3   05 33
                   MOV   A,3MOV                       ;06B5   E5 33
                   CJNE  A,#01H,Q06C0                 ;06B7   B4 01 06
                   SETB  20H.5                        ;06BA   D2 05
                   CLR   20H.0                        ;06BC   C2 00
                   SJMP  Q06C9                        ;06BE   80 09
Q06C0:             MOV   A,3MOV                       ;06C0   E5 33
                   CJNE  A,#02H,Q06CD                 ;06C2   B4 02 08
                   CLR   20H.5                        ;06C5   C2 05
                   SETB  20H.0                        ;06C7   D2 00
Q06C9:             CLR   20H.4                        ;06C9   C2 04
                   SJMP  Q06D8                        ;06CB   80 0B
Q06CD:             MOV   A,3MOV                       ;06CD   E5 33
                   CJNE  A,#03H,Q06DC                 ;06CF   B4 03 0A
                   CLR   20H.5                        ;06D2   C2 05
                   CLR   20H.0                        ;06D4   C2 00
                   SETB  20H.4                        ;06D6   D2 04
Q06D8:             CLR   20H.3                        ;06D8   C2 03
                   SJMP  Q06E9                        ;06DA   80 0D
Q06DC:             MOV   A,3MOV                       ;06DC   E5 33
                   CJNE  A,#04H,Q06ED                 ;06DE   B4 04 0C
                   CLR   20H.5                        ;06E1   C2 05
                   CLR   20H.0                        ;06E3   C2 00
                   CLR   20H.4                        ;06E5   C2 04
                   SETB  20H.3                        ;06E7   D2 03
Q06E9:             CLR   20H.2                        ;06E9   C2 02
                   SJMP  Q06FC                        ;06EB   80 0F
Q06ED:             MOV   A,3MOV                       ;06ED   E5 33
                   CJNE  A,#05H,Q0701                 ;06EF   B4 05 0F
                   CLR   20H.5                        ;06F2   C2 05
                   CLR   20H.0                        ;06F4   C2 00
                   CLR   20H.4                        ;06F6   C2 04
                   CLR   20H.3                        ;06F8   C2 03
                   SETB  20H.2                        ;06FA   D2 02
Q06FC:             CLR   20H.6                        ;06FC   C2 06
                   CLR   20H.1                        ;06FE   C2 01
                   RET      RET                       ;0700   22
;==========================================================================
Q0701:             MOV   A,3MOV                       ;0701   E5 33
                   CJNE  A,#06H,Q0715                 ;0703   B4 06 0F
                   CLR   20H.5                        ;0706   C2 05
                   CLR   20H.0                        ;0708   C2 00
                   CLR   20H.4                        ;070A   C2 04
                   CLR   20H.3                        ;070C   C2 03
                   CLR   20H.2                        ;070E   C2 02
                   SETB  20H.6                        ;0710   D2 06
                   CLR   20H.1                        ;0712   C2 01
                   RET      RET                       ;0714   22
;==========================================================================
Q0715:             MOV   A,3MOV                       ;0715   E5 33
                   CJNE  A,#07H,Q072B                 ;0717   B4 07 11
                   CLR   A                            ;071A   E4
                   MOV   33HMOV                       ;071B   F5 33
                   CLR   20H.5                        ;071D   C2 05
                   CLR   20H.0                        ;071F   C2 00
                   CLR   20H.4                        ;0721   C2 04
                   CLR   20H.3                        ;0723   C2 03
                   CLR   20H.2                        ;0725   C2 02
                   CLR   20H.6                        ;0727   C2 06
                   SETB  20H.1                        ;0729   D2 01
Q072B:             RET      RET                       ;072B   22
;==========================================================================
Q072C:             JNB   20HJNBQ0797                  ;072C   30 04 68
                   MOV   29HMOVH                      ;072F   85 22 29
                   MOV   51HMOVH                      ;0732   85 23 51
                   MOV   3CHMOVH                      ;0735   85 4B 3C
                   MOV   28HMOVH                      ;0738   85 3F 28
Q073B:             JNB   20HJNBQ0797                  ;073B   30 04 59
                   CLR   A                            ;073E   E4
                   MOV   08HMOV                       ;073F   F5 08
Q0741:             MOV   22HMOVAH                     ;0741   75 22 0A
                   MOV   23HMOVAH                     ;0744   75 23 0A
                   MOV   4BHMOVAH                     ;0747   75 4B 0A
                   MOV   3FHMOVAH                     ;074A   75 3F 0A
                   MOV   49HMOVH                      ;074D   85 2D 49
                   MOV   44HMOVH                      ;0750   85 2A 44
                   LCALL Q01CE                        ;0753   12 01 CE
                   LCALL Q0989                        ;0756   12 09 89
                   JB    20HJB,Q075F                  ;0759   20 04 03
                   MOV   08HMOV3H                     ;075C   75 08 33
Q075F:             INC   08HINC                       ;075F   05 08
                   MOV   A,0MOV                       ;0761   E5 08
                   CLR   C                            ;0763   C3
                   SUBB  A,#12H                       ;0764   94 12
                   JC    Q07JC                        ;0766   40 D9
                   JNB   20HJNBQ073B                  ;0768   30 04 D0
                   CLR   A                            ;076B   E4
                   MOV   08HMOV                       ;076C   F5 08
Q076E:             MOV   A,0MOV                       ;076E   E5 08
                   CLR   C                            ;0770   C3
                   SUBB  A,#12H                       ;0771   94 12
                   JNC   Q07JNC                       ;0773   50 C6
                   MOV   22HMOVH                      ;0775   85 29 22
                   MOV   23HMOVH                      ;0778   85 51 23
                   MOV   4BHMOVH                      ;077B   85 3C 4B
                   MOV   3FHMOVH                      ;077E   85 28 3F
                   MOV   49HMOVH                      ;0781   85 2D 49
                   MOV   44HMOVH                      ;0784   85 2A 44
                   LCALL Q01CE                        ;0787   12 01 CE
                   LCALL Q0989                        ;078A   12 09 89
                   JB    20HJB,Q0793                  ;078D   20 04 03
                   MOV   08HMOV3H                     ;0790   75 08 33
Q0793:             INC   08HINC                       ;0793   05 08
                   SJMP  Q076E                        ;0795   80 D7
Q0797:             RET      RET                       ;0797   22
;==========================================================================
Q0798:		 DB  01H, DBH, 00H, 01H, 52H, 18H, 01H, 3DH	;.H..R..=
Q07A0:		 DB  00H, DBH, 3AH, 00H, 01H, 49H, 00H, 01H	;..:..I..
Q07A8:		 DB  44H, DBH, 01H, 50H, 00H, 01H, 4AH, 00H	;D..P..J.
Q07B0:		 DB  01H, DBH, 02H, 01H, 23H, 00H, 01H, 4BH	;."..#..K
Q07B8:		 DB  00H, DBH, 3FH, 07H, 01H, 47H, 00H, 01H	;..?..G..
Q07C0:		 DB  39H, DBH, 01H, 53H, 02H, 01H, 46H, 06H	;9..S..F.
Q07C8:		 DB  01H, DBH, 00H, 01H, 37H, 01H, 01H, 40H	;.2..7..@
Q07D0:		 DB  04H, DBH, 3EH, 00H, 01H, 42H, 1FH, 01H	;..>..B..
Q07D8:		 DB  45H, DBH, 01H, 36H, 1EH, 01H, 41H, 0CH	;E..6..A.
Q07E0:		 DB  01H, DBH, 00H,0C1H, 05H,0C1H, 00H,0C1H	;.3......
Q07E8:		 DB  04H,0DBH, 03H,0C1H, 02H,0C1H, 06H,0C1H	;........
Q07F0:		 DB  01H, DBH	;..
;==========================================================================
Q07F2:             CJNE  R4,#00H,Q0800                ;07F2   BC 00 0B
                   CJNE  R6,#00H,Q0821                ;07F5   BE 00 29
                   MOV   A,RMOV                       ;07F8   EF
                   MOV   B,RMOV                       ;07F9   8D F0
                   DIV   AB DIV                       ;07FB   84
                   MOV   R7,MOV                       ;07FC   FF
                   MOV   R5,MOV                       ;07FD   AD F0
                   RET      RET                       ;07FF   22
;==========================================================================
Q0800:             CLR   A                            ;0800   E4
                   XCH   A,R4                         ;0801   CC
                   MOV   R0,MOV                       ;0802   F8
                   MOV   B,#MOV                       ;0803   75 F0 08
Q0806:             MOV   A,RMOV                       ;0806   EF
                   ADD   A,RADD                       ;0807   2F
                   MOV   R7,MOV                       ;0808   FF
                   MOV   A,RMOV                       ;0809   EE
                   RLC   A                            ;080A   33
                   MOV   R6,MOV                       ;080B   FE
                   MOV   A,RMOV                       ;080C   EC
                   RLC   A                            ;080D   33
                   MOV   R4,MOV                       ;080E   FC
                   MOV   A,RMOV                       ;080F   EE
                   SUBB  A,R5                         ;0810   9D
                   MOV   A,RMOV                       ;0811   EC
                   SUBB  A,R0                         ;0812   98
                   JC    Q08JC                        ;0813   40 05
                   MOV   R4,MOV                       ;0815   FC
                   MOV   A,RMOV                       ;0816   EE
                   SUBB  A,R5                         ;0817   9D
                   MOV   R6,MOV                       ;0818   FE
                   INC   R7 INC                       ;0819   0F
Q081A:             DJNZ  B,Q0806                      ;081A   D5 F0 E9
                   CLR   A                            ;081D   E4
                   XCH   A,R6                         ;081E   CE
                   MOV   R5,MOV                       ;081F   FD
                   RET      RET                       ;0820   22
;==========================================================================
Q0821:             MOV   A,RMOV                       ;0821   ED
                   MOV   R0,MOV                       ;0822   F8
                   MOV   B,AMOV                       ;0823   F5 F0
                   MOV   A,RMOV                       ;0825   EE
                   DIV   AB DIV                       ;0826   84
                   JB    OV,JB846                     ;0827   20 D2 1C
                   MOV   R6,MOV                       ;082A   FE
                   MOV   R5,MOV                       ;082B   AD F0
                   MOV   B,#MOV                       ;082D   75 F0 08
Q0830:             MOV   A,RMOV                       ;0830   EF
                   ADD   A,RADD                       ;0831   2F
                   MOV   R7,MOV                       ;0832   FF
                   MOV   A,RMOV                       ;0833   ED
                   RLC   A                            ;0834   33
                   MOV   R5,MOV                       ;0835   FD
                   JC    Q08JC                        ;0836   40 07
                   SUBB  A,R0                         ;0838   98
                   JNC   Q08JNC                       ;0839   50 06
                   DJNZ  B,Q0830                      ;083B   D5 F0 F2
                   RET      RET                       ;083E   22
;==========================================================================
Q083F:             CLR   C                            ;083F   C3
                   SUBB  A,R0                         ;0840   98
Q0841:             MOV   R5,MOV                       ;0841   FD
                   INC   R7 INC                       ;0842   0F
                   DJNZ  B,Q0830                      ;0843   D5 F0 EA
Q0846:             RET      RET                       ;0846   22
;==========================================================================
Q0847:             JNB   20HJNBQ0894                  ;0847   30 00 4A
                   MOV   2DHMOVH                      ;084A   85 49 2D
                   MOV   2AHMOVH                      ;084D   85 44 2A
Q0850:             JNB   20HJNBQ0894                  ;0850   30 00 41
                   CLR   A                            ;0853   E4
                   MOV   08HMOV                       ;0854   F5 08
Q0856:             MOV   49HMOVAH                     ;0856   75 49 0A
                   MOV   44HMOVAH                     ;0859   75 44 0A
                   LCALL Q01C8                        ;085C   12 01 C8
                   LCALL Q0989                        ;085F   12 09 89
                   JB    20HJB,Q0868                  ;0862   20 00 03
                   MOV   08HMOV3H                     ;0865   75 08 33
Q0868:             INC   08HINC                       ;0868   05 08
                   MOV   A,0MOV                       ;086A   E5 08
                   CLR   C                            ;086C   C3
                   SUBB  A,#12H                       ;086D   94 12
                   JC    Q08JC                        ;086F   40 E5
                   JNB   20HJNBQ0850                  ;0871   30 00 DC
                   CLR   A                            ;0874   E4
                   MOV   08HMOV                       ;0875   F5 08
Q0877:             MOV   A,0MOV                       ;0877   E5 08
                   CLR   C                            ;0879   C3
                   SUBB  A,#12H                       ;087A   94 12
                   JNC   Q08JNC                       ;087C   50 D2
                   MOV   49HMOVH                      ;087E   85 2D 49
                   MOV   44HMOVH                      ;0881   85 2A 44
                   LCALL Q01C8                        ;0884   12 01 C8
                   LCALL Q0989                        ;0887   12 09 89
                   JB    20HJB,Q0890                  ;088A   20 00 03
                   MOV   08HMOV3H                     ;088D   75 08 33
Q0890:             INC   08HINC                       ;0890   05 08
                   SJMP  Q0877                        ;0892   80 E3
Q0894:             RET      RET                       ;0894   22
;==========================================================================
Q0895:             JB    TR0JB08A0                    ;0895   20 8C 08
                   LCALL Q09B7                        ;0898   12 09 B7
                   MOV   45HMOV                       ;089B   8F 45
                   MOV   3BHMOVH                      ;089D   85 45 3B
Q08A0:             JNB   20HJNBQ08E1                  ;08A0   30 03 3E
                   MOV   54HMOVH                      ;08A3   85 39 54
                   MOV   38HMOVH                      ;08A6   85 47 38
Q08A9:             JNB   20HJNBQ08E1                  ;08A9   30 03 35
                   CLR   A                            ;08AC   E4
                   MOV   08HMOV                       ;08AD   F5 08
Q08AF:             MOV   39HMOVAH                     ;08AF   75 39 0A
                   MOV   47HMOVAH                     ;08B2   75 47 0A
                   LCALL Q097A                        ;08B5   12 09 7A
                   JB    20HJB,Q08BE                  ;08B8   20 03 03
                   MOV   08HMOV3H                     ;08BB   75 08 33
Q08BE:             INC   08HINC                       ;08BE   05 08
                   MOV   A,0MOV                       ;08C0   E5 08
                   CLR   C                            ;08C2   C3
                   SUBB  A,#12H                       ;08C3   94 12
                   JC    Q08JC                        ;08C5   40 E8
                   JNB   20HJNBQ08A9                  ;08C7   30 03 DF
                   CLR   A                            ;08CA   E4
                   MOV   08HMOV                       ;08CB   F5 08
Q08CD:             MOV   A,0MOV                       ;08CD   E5 08
                   CLR   C                            ;08CF   C3
                   SUBB  A,#12H                       ;08D0   94 12
                   JNC   Q08JNC                       ;08D2   50 D5
                   LCALL Q0974                        ;08D4   12 09 74
                   JB    20HJB,Q08DD                  ;08D7   20 03 03
                   MOV   08HMOV3H                     ;08DA   75 08 33
Q08DD:             INC   08HINC                       ;08DD   05 08
                   SJMP  Q08CD                        ;08DF   80 EC
Q08E1:             RET      RET                       ;08E1   22
;==========================================================================
Q08E2:             JNB   20HJNBQ092B                  ;08E2   30 05 46
                   CLR   TR0                          ;08E5   C2 8C
                   MOV   30HMOVH                      ;08E7   85 50 30
                   MOV   2FHMOVH                      ;08EA   85 4A 2F
Q08ED:             JNB   20HJNBQ092B                  ;08ED   30 05 3B
                   CLR   A                            ;08F0   E4
                   MOV   08HMOV                       ;08F1   F5 08
Q08F3:             MOV   50HMOVAH                     ;08F3   75 50 0A
                   MOV   4AHMOVAH                     ;08F6   75 4A 0A
                   LCALL Q01CE                        ;08F9   12 01 CE
                   LCALL Q0989                        ;08FC   12 09 89
                   JB    20HJB,Q0905                  ;08FF   20 05 03
                   MOV   08HMOV3H                     ;0902   75 08 33
Q0905:             INC   08HINC                       ;0905   05 08
                   MOV   A,0MOV                       ;0907   E5 08
                   CLR   C                            ;0909   C3
                   SUBB  A,#12H                       ;090A   94 12
                   JC    Q08JC                        ;090C   40 E5
                   JNB   20HJNBQ08ED                  ;090E   30 05 DC
                   CLR   A                            ;0911   E4
                   MOV   08HMOV                       ;0912   F5 08
Q0914:             MOV   A,0MOV                       ;0914   E5 08
                   CLR   C                            ;0916   C3
                   SUBB  A,#12H                       ;0917   94 12
                   JNC   Q08JNC                       ;0919   50 D2
                   LCALL Q01C8                        ;091B   12 01 C8
                   LCALL Q0989                        ;091E   12 09 89
                   JB    20HJB,Q0927                  ;0921   20 05 03
                   MOV   08HMOV3H                     ;0924   75 08 33
Q0927:             INC   08HINC                       ;0927   05 08
                   SJMP  Q0914                        ;0929   80 E9
Q092B:             RET      RET                       ;092B   22
;==========================================================================
Q092C:             JNB   20HJNBQ0973                  ;092C   30 02 44
                   MOV   2EHMOVH                      ;092F   85 46 2E
                   MOV   43HMOVH                      ;0932   85 53 43
Q0935:             JNB   20HJNBQ0973                  ;0935   30 02 3B
                   CLR   A                            ;0938   E4
                   MOV   08HMOV                       ;0939   F5 08
Q093B:             MOV   46HMOVAH                     ;093B   75 46 0A
                   MOV   53HMOVAH                     ;093E   75 53 0A
                   LCALL Q0974                        ;0941   12 09 74
                   JB    20HJB,Q094A                  ;0944   20 02 03
                   MOV   08HMOV3H                     ;0947   75 08 33
Q094A:             INC   08HINC                       ;094A   05 08
                   MOV   A,0MOV                       ;094C   E5 08
                   CLR   C                            ;094E   C3
                   SUBB  A,#12H                       ;094F   94 12
                   JC    Q09JC                        ;0951   40 E8
                   JNB   20HJNBQ0935                  ;0953   30 02 DF
                   CLR   A                            ;0956   E4
                   MOV   08HMOV                       ;0957   F5 08
Q0959:             MOV   A,0MOV                       ;0959   E5 08
                   CLR   C                            ;095B   C3
                   SUBB  A,#12H                       ;095C   94 12
                   JNC   Q09JNC                       ;095E   50 D5
                   MOV   46HMOVH                      ;0960   85 2E 46
                   MOV   53HMOVH                      ;0963   85 43 53
                   LCALL Q0974                        ;0966   12 09 74
                   JB    20HJB,Q096F                  ;0969   20 02 03
                   MOV   08HMOV3H                     ;096C   75 08 33
Q096F:             INC   08HINC                       ;096F   05 08
                   SJMP  Q0959                        ;0971   80 E6
Q0973:             RET      RET                       ;0973   22
;==========================================================================
Q0974:             MOV   39HMOVH                      ;0974   85 54 39
                   MOV   47HMOVH                      ;0977   85 38 47
Q097A:             MOV   22HMOVH                      ;097A   85 29 22
                   MOV   23HMOVH                      ;097D   85 51 23
                   MOV   4BHMOVH                      ;0980   85 3C 4B
                   MOV   3FHMOVH                      ;0983   85 28 3F
                   LCALL Q01CE                        ;0986   12 01 CE
Q0989:             MOV   P1,MOVFH                     ;0989   75 90 FF
                   MOV   A,PMOV                       ;098C   E5 90
                   CPL   A                            ;098E   F4
                   JZ    Q09JZ                        ;098F   60 25
                   LCALL Q01CE                        ;0991   12 01 CE
                   LCALL Q01CE                        ;0994   12 01 CE
                   LCALL Q01CE                        ;0997   12 01 CE
                   MOV   A,PMOV                       ;099A   E5 90
                   CPL   A                            ;099C   F4
                   JZ    Q09JZ                        ;099D   60 17
                   MOV   R7,MOV                       ;099F   AF 90
                   MOV   A,RMOV                       ;09A1   EF
                   ADD   A,#ADD                       ;09A2   24 05
                   JZ    Q09JZ                        ;09A4   60 0D
                   ADD   A,#ADDH                      ;09A6   24 FE
                   JZ    Q09JZ                        ;09A8   60 06
                   DEC   A  DEC                       ;09AA   14
                   JNZ   Q09JNZ                       ;09AB   70 09
                   LJMP  Q06B3                        ;09AD   02 06 B3
;==========================================================================
Q09B0:             LJMP  Q0000                        ;09B0   02 00 00
;==========================================================================
Q09B3:             LCALL Q0367                        ;09B3   12 03 67
Q09B6:             RET      RET                       ;09B6   22
;==========================================================================
Q09B7:             LCALL Q0633                        ;09B7   12 06 33
                   MOV   A,2MOV                       ;09BA   E5 26
                   ANL   A,#03H                       ;09BC   54 03
                   JNZ   Q09JNZ                       ;09BE   70 0E
                   MOV   R6,MOV                       ;09C0   AE 25
                   MOV   R7,MOV                       ;09C2   AF 26
                   MOV   R4,MOV                       ;09C4   FC
                   MOV   R5,MOVH                      ;09C5   7D 64
                   LCALL Q07F2                        ;09C7   12 07 F2
                   MOV   A,RMOV                       ;09CA   ED
                   ORL   A,R4                         ;09CB   4C
                   JNZ   Q09JNZ                       ;09CC   70 1E
Q09CE:             MOV   R6,MOV                       ;09CE   AE 25
                   MOV   R7,MOV                       ;09D0   AF 26
                   MOV   R4,MOVH                      ;09D2   7C 00
                   MOV   R5,MOVH                      ;09D4   7D 64
                   LCALL Q07F2                        ;09D6   12 07 F2
                   MOV   A,RMOV                       ;09D9   ED
                   ORL   A,R4                         ;09DA   4C
                   JNZ   Q09JNZ                       ;09DB   70 12
                   MOV   R6,MOV                       ;09DD   AE 25
                   MOV   R7,MOV                       ;09DF   AF 26
                   MOV   R4,MOVH                      ;09E1   7C 01
                   MOV   R5,MOVH                      ;09E3   7D 90
                   LCALL Q07F2                        ;09E5   12 07 F2
                   MOV   A,RMOV                       ;09E8   ED
                   ORL   A,R4                         ;09E9   4C
                   JNZ   Q09JNZ                       ;09EA   70 03
Q09EC:             MOV   R7,MOVH                      ;09EC   7F 1D
                   RET      RET                       ;09EE   22
;==========================================================================
Q09EF:             MOV   R7,MOVH                      ;09EF   7F 1C
                   RET      RET                       ;09F1   22
;==========================================================================
Q09F2:             ADD   A,AADD                       ;09F2   25 E0
                   ADD   A,#ADD                       ;09F4   24 6D
                   MOV   DPLMOV                       ;09F6   F5 82
                   CLR   A                            ;09F8   E4
                   ADDC  A,#0AH                       ;09F9   34 0A
                   MOV   DPHMOV                       ;09FB   F5 83
                   MOV   A,#MOV                       ;09FD   74 01
                   MOVC  A,@A+DPTR                    ;09FF   93
Q0A00:             MOV   DPTMOV0EFFFH                 ;0A00   90 EF FF
Q0A03:             MOVX  @DPTR,A                      ;0A03   F0
                   MOV   R7,MOVH                      ;0A04   7F 03
                   MOV   R6,MOVH                      ;0A06   7E 00
Q0A08:             SETB  C                            ;0A08   D3
                   MOV   A,RMOV                       ;0A09   EF
                   SUBB  A,#00H                       ;0A0A   94 00
                   MOV   A,RMOV                       ;0A0C   EE
                   SUBB  A,#00H                       ;0A0D   94 00
                   JC    Q0AJC                        ;0A0F   40 14
                   MOV   R5,MOVH                      ;0A11   7D 32
                   MOV   R4,MOVH                      ;0A13   7C 00
Q0A15:             MOV   A,RMOV                       ;0A15   ED
                   DEC   R5 DEC                       ;0A16   1D
                   JNZ   Q0AJNZ                       ;0A17   70 01
                   DEC   R4 DEC                       ;0A19   1C
Q0A1A:             MOV   A,RMOV                       ;0A1A   ED
                   ORL   A,R4                         ;0A1B   4C
                   JNZ   Q0AJNZ                       ;0A1C   70 F7
                   MOV   A,RMOV                       ;0A1E   EF
                   DEC   R7 DEC                       ;0A1F   1F
                   JNZ   Q0AJNZ                       ;0A20   70 E6
                   DEC   R6 DEC                       ;0A22   1E
                   SJMP  Q0A08                        ;0A23   80 E3
Q0A25:             RET      RET                       ;0A25   22
;==========================================================================
Q0A26:             MOV   TMOMOV01H                    ;0A26   75 89 01
                   MOV   TH0MOVCH                     ;0A29   75 8C 3C
                   MOV   TL0MOVB0H                    ;0A2C   75 8A B0
                   SETB  EA                           ;0A2F   D2 AF
                   SETB  ET0                          ;0A31   D2 A9
                   SETB  TR0                          ;0A33   D2 8C
Q0A35:             LCALL Q0989                        ;0A35   12 09 89
                   LCALL Q01CE                        ;0A38   12 01 CE
                   LCALL Q08E2                        ;0A3B   12 08 E2
                   LCALL Q0847                        ;0A3E   12 08 47
                   LCALL Q072C                        ;0A41   12 07 2C
                   LCALL Q0895                        ;0A44   12 08 95
                   LCALL Q092C                        ;0A47   12 09 2C
                   LCALL Q0501                        ;0A4A   12 05 01
                   LCALL Q000E                        ;0A4D   12 00 0E
                   SJMP  Q0A35                        ;0A50   80 E3
                   PUSH  ACCPUSH                      ;0A52   C0 E0
                   PUSH  PSWPUSH  PSW                 ;0A54   C0 D0
                   MOV   TH0MOVCH                     ;0A56   75 8C 3C
                   MOV   TL0MOVB0H                    ;0A59   75 8A B0
                   INC   48HINC                       ;0A5C   05 48
                   MOV   A,4MOV                       ;0A5E   E5 48
                   CJNE  A,#14H,Q0A68                 ;0A60   B4 14 05
                   MOV   48HMOV0H                     ;0A63   75 48 00
                   INC   3DHINC                       ;0A66   05 3D
Q0A68:             POP   PSWPOP   PSW                 ;0A68   D0 D0
                   POP   ACCPOP                       ;0A6A   D0 E0
                   RETI                               ;0A6C   32
;==========================================================================
Q0A6D:		 DB  00H, DBH, 00H, 06H, 00H, 5BH, 00H, 4FH	;
Q0A75:		 DB  00H, DBH, 00H, 6DH, 00H, 7DH, 00H, 07H	;
Q0A7D:		 DB  00H, DBH, 00H, 6FH, 00H, 00H	;
