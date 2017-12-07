
library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity signaux is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    start :      In  bit;
    done :      In  bit;
    DIN :       In    bit_vector(15 downto 0);
    DOUT :       Out   bit_vector(15 downto 0)
    );
  end signaux;

architecture struct of signaux is

signal data_round_in       : bit_vector(12 downto 0);
signal data_round_out       : bit_vector(17 downto 0);
signal First_round_KEY       : bit_vector(6 downto 0);            
signal round_KEY         : bit_vector(0 to 127); -- erreur de sens
signal round_KEY2         : bit_vector(0 to 127); 
signal last_round_signal    : bit;
signal first_round_signal    : bit;

begin

end struct;

