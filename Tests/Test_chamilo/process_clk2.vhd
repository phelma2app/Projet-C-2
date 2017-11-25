
library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity variables is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    start :      In  bit;
    done :      In  bit;
    DIN :       In    bit_vector(15 downto 0);
    DOUT :       Out   bit_vector(15 downto 0)
    );
  end variables;

architecture struct of variables is

signal data_round_in       : bit_vector(12 downto 0);
signal data_round_out       : bit_vector(17 downto 0);
signal First_round_KEY       : bit_vector(6 downto 0);            
  signal round_KEY         : bit_vector(127 downto 0);            
  signal last_round_signal    : bit;
  signal first_round_signal    : bit;


begin

un: process(clk, reset)
 
begin
  if clk'event and clk='0' then
    if reset='1' then
     data_round_out<="000000000000000";
    else
      data_round_out<=data_round_in
    end if;
  end if;
 
end process;



toto: process (data_round_out)
begin
  if start='1' then
    data_round_in<=DIN;
  else
    data_round_in<=data_round_out;
  end if;
  end process;
end struct;

