
-- Empty entity

library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.std_logic_1164.all;
  use IEEE.std_logic_misc.all;
  use IEEE.std_logic_arith.all;

entity AES_core is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    KEYIN :       In    bit_vector(127 downto 0);
    start :      In  bit;
    DIN :       In    bit_vector(127 downto 0);
    DOUT :       Out   bit_vector(127 downto 0);
    IVIN :       In    bit_vector(127 downto 0);
    ECB_CBC :      In  bit;
    DOUT_VAL :      Out   bit
    );
  end AES_core;

architecture struct of AES_core is
--components
  component key_schedule
    Port (      
      CLK :       In    bit;
      RST :       In   bit;
      KEYIN :       In    bit_vector(127 downto 0);
      First_round_KEY :   out    bit_vector(127 downto 0);
      round_KEY :     out    bit_vector(127 downto 0);
      first_round_signal:  In   bit
      );
    end component;
  component round
    Port (    
      CLK :       In    bit;
      RST :       In   bit;
      DIN :       In    bit_vector(0 TO 127);
      First_round_KEY :   In    bit_vector(0 TO 127);
      round_KEY :     In    bit_vector(0 TO 127);
      last_round_signal:  In   bit;
      first_round_signal:  In   bit;
      DOUT :       Out   bit_vector(0 TO 127)
      );
    end component;
  component  aes_ctrl
    Port (
      CLK :        In  bit;
      RST :       In  bit;
      start :       In bit;
      last_round_signal:  Out   bit;
      first_round_signal:  Out   bit    
      );
    end component;
  component FFD_start 
    port(   
      A : in bit;
      Q : out bit;
      store : in bit;
      CLK:in bit;
      RST : in bit);
    end component;
-- signals
  signal data_round_in       : bit_vector(124 downto 0); -- pb de taille 
  signal data_round_out       : bit_vector(127 downto 0);
  signal First_round_KEY       : bit_vector(127 downto 0);            
  signal round_KEY         : bit_vector(127 downto 0);            
  signal last_round_signal    : bit;
  signal first_round_signal,a,b,c,d    : bit;
begin
-- mapping components
  round_inst: round port map( CLK, RST,data_round_in,first_round_key,round_key,last_round_signal,first_round_signal,data_round_out);
  key_sched_inst: key_schedule port map(CLK, RST,KEYIN,first_round_key,round_key,first_round_signal);
-- controller
  control_inst: aes_ctrl port map(CLK,RST,start,last_round_signal,first_round_signal);
-- logic part to manage modes as CBC or ECB
  data_round_in <= DIN when(ECB_CBC='0') else -- detecte l'erreur de taille
                                              -- entre DIN et data_round_in
      (DIN xor IVIN);

  DOUT<= data_round_out ;
  DOUT_VAL<=last_round_signal;
  a<= b or  (c='0' and d) or first_round_signal;
  b<= last_round_signal and c or d;
  c<= not first_round_signal xor d;
  d<= not last_round_signal;
  end struct;
