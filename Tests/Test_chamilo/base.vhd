
-- Empty entity

library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.std_logic_1164.all;
  use IEEE.std_logic_misc.all;
  use IEEE.std_logic_arith.all;

entity AES_core is
  Port(    
    CLK :       In    std_logic;
    RST :       In   std_logic;
    KEYIN :       In    STD_LOGIC_VECTOR(127 downto 0);
    start :      In  std_logic;
    DIN :       In    STD_LOGIC_VECTOR(127 downto 0);
    DOUT :       Out   STD_LOGIC_VECTOR(127 downto 0);
    IVIN :       In    STD_LOGIC_VECTOR(127 downto 0);
    ECB_CBC :      In  std_logic;
    DOUT_VAL :      Out   std_logic
    );
  end AES_core;

architecture struct of AES_core is
--components
  component key_schedule
    Port (      
      CLK :       In    std_logic;
      RST :       In   std_logic;
      KEYIN :       In    STD_LOGIC_VECTOR(127 downto 0);
      First_round_KEY :   out    STD_LOGIC_VECTOR(127 downto 0);
      round_KEY :     out    STD_LOGIC_VECTOR(127 downto 0);
      first_round_signal:  In   std_logic
      );
    end component;
  component round
    Port (    
      CLK :       In    std_logic;
      RST :       In   std_logic;
      DIN :       In    STD_LOGIC_VECTOR(0 TO 127);
      First_round_KEY :   In    STD_LOGIC_VECTOR(0 TO 127);
      round_KEY :     In    STD_LOGIC_VECTOR(0 TO 127);
      last_round_signal:  In   std_logic;
      first_round_signal:  In   std_logic;
      DOUT :       Out   STD_LOGIC_VECTOR(0 TO 127)
      );
    end component;
  component  aes_ctrl
    Port (
      CLK :        In  std_logic;
      RST :       In  std_logic;
      start :       In std_logic;
      last_round_signal:  Out   std_logic;
      first_round_signal:  Out   std_logic    
      );
    end component;
  component FFD_start 
    port(   
      A : in STD_LOGIC;
      Q : out STD_LOGIC;
      store : in STD_LOGIC;
      CLK:in STD_LOGIC;
      RST : in STD_LOGIC);
    end component;
-- signals
  signal data_round_in       : STD_LOGIC_VECTOR(127 downto 0);
  signal data_round_out       : STD_LOGIC_VECTOR(127 downto 0);
  signal First_round_KEY       : STD_LOGIC_VECTOR(127 downto 0);            
  signal round_KEY         : STD_LOGIC_VECTOR(127 downto 0);            
  signal last_round_signal    : std_logic;
  signal first_round_signal    : std_logic;
begin
-- mapping components
  round_inst: round port map( CLK, RST,data_round_in,first_round_key,round_key,last_round_signal,first_round_signal,data_round_out);
  key_sched_inst: key_schedule port map(CLK, RST,KEYIN,first_round_key,round_key,first_round_signal);
-- controller
  control_inst: aes_ctrl port map(CLK,RST,start,last_round_signal,first_round_signal);
-- logic part to manage modes as CBC or ECB
  data_round_in <= DIN when(ECB_CBC='0') else
      (DIN xor IVIN);

  DOUT<= data_round_out ;
  DOUT_VAL<=last_round_signal;

  end struct;

