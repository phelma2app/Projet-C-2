
-- Empty entity

library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.std_logic_1164.all;
  use IEEE.std_logic_misc.all;
  use IEEE.std_logic_arith.all;
library portes;
use portes.all;

entity instances is
  Port(    
    CLK :       In    bit;
    RST :       In   bit;
    input :      In  bit_vector(5 downto 0);
    result: out bit
    );
  end instances;

architecture struct of instances is

signal int_level_1 : bit_vector(1 downto 0);
signal int_level_2 : bit_vector(1 downto 0);
begin

first: and2 port map(a => input(0),
	b => input(1),
	c => int_level_1(0));

second: or2 port map(a => input(2),
	b => input(3),
	c => int_level_1(1));

reg: registre
	generic  map (S => 2) 
	port map(
	D => int_level_1,
	clk    => CLK,
	reset => RST,
	Q  => int_level_2) ;

last: sub 
	generic  map (S => 2) 
	port map (
	A    => int_level_1,
	B     => int_level_2 ,
	R  => int_level_2 ,
	cout   => result) ;


end struct;

