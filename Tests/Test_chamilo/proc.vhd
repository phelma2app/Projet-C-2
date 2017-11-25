
library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity proc is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    start :      In  bit;
    done :      In  bit;
    DIN :       In    bit_vector(15 downto 0);
    DOUT :       Out   bit_vector(15 downto 0)
    );
  end proc;

architecture struct of proc is

signal data_round_in       : bit_vector(12 downto 0);
signal data_round_out       : bit_vector(17 downto 0);
signal First_round_KEY       : bit_vector(6 downto 0);            
  signal round_KEY         : bit_vector(127 downto 0);            
  signal last_round_signal    : bit;
  signal first_round_signal    : bit;


begin

un: process(start)
begin
 if (start = '1') then
   first_round_signal <= '1';
 else
   First_round_KEY <= "0000000";
 end if;  
   
end process;


end struct;

