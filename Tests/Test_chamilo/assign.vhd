library STD;
use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity assign is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    start :      In  bit;
    done :      out  bit;
    DIN :       In    bit_vector(15 downto 0);
    DOUT :       Out   bit_vector(15 downto 0)
    );
  end assign;-- faute de nom

architecture struct of assign is

signal data_round_in       : bit_vector(15 downto 0);
signal data_round_out       : bit_vector(15 downto 0);
  signal last_round_signal    : bit;
  signal first_round_signal    : bit;


begin

 --write output
done <= last_round_signal;

 --read input
first_round_signal <= start;

 --between signals

data_round_out <= data_round_in;

end struct;
