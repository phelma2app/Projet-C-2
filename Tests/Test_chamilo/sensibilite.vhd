
library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity case_ex is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    DIN :       In    bit_vector(2 downto 0);
    titi:       In    bit_vector(2 downto 0);
    DOUT :       Out   bit_vector(2 downto 0)
    );
  end case_ex;

architecture struct of case_ex is


begin

un: process(DIN)
begin
 case (DIN) is 
   when "000" => DOUT <= "001";
   when "010" => DOUT <= "101" or titi ;
   when others => DOUT <= "111";
   
 end case;  
   
end process;


end struct;

