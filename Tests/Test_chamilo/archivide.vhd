library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity archivide is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    start :      In  bit;
    done :      In  bit;
    DIN :       In    bit_vector(15 downto 0);
    DOUT :       Out   bit_vector(15 downto 0)
    );
  end archivide;

architecture vide of archivide is
begin

 end vide;
