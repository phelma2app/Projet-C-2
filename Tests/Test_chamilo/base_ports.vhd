library portes;
use portes.all ;

package cell is

component and2
	port (
	a   :   in   bit;
	b   :   in   bit;
	c   :   out bit) ;
end component ;

component or2 
	port (
	a   :   in   bit;
	b   :   in   bit;
	c   :   out bit) ;
end component;

component not1
	port (
	a   :   in   bit;
	c   :   out bit) ;
end component;

component xor2 
	port (
	a   :   in   bit;
	b   :   in   bit;
	c   :   out bit) ;
end component ;

component latch 
	port (
	D :   in   bit;
	clk       :   in   bit;
	reset   :   in   bit;
	Q :   out bit) ;
end component ;

component  flip_flop 
	port (
	D :   in   bit;
	clk       :   in   bit;
	reset   :   in   bit;
	Q :   out bit) ;
end component;

component  flip_flop_e 
	port (
	D :   in   bit;
	e :   in   bit;
	clk       :   in   bit;
	reset   :   in   bit;
	Q :   out bit) ;
end component ;

component registre 
	generic (
	S   :  integer) ;
	port (
	D :   in   bit_vector (S-1  downto 0) ;
	clk ,   reset   :   in   bit;
	Q :   out bit_vector (S-1  downto 0) ) ;
end component;

component registre_e 
	generic (
	S   :  integer) ;
	port (
	D :   in   bit_vector (S-1  downto 0) ;
	e :   in   bit;
	clk ,   reset   :   in   bit;
	Q :   out bit_vector (S-1  downto 0) ) ;
end component ;

component add 
	generic (S   :  integer) ;
	port (
	A,  B     :   in   bit_vector (S-1  downto 0) ;
	R :   out bit_vector (S-1  downto 0) ;
	cout   :   out bit) ;
end component;

component sub 
generic (
	S   :  integer) ;
	port (
	A,  B     :   in   bit_vector (S-1  downto 0) ;
	R :   out bit_vector (S-1  downto 0) ;
	cout   :   out bit) ;
end component ;

component mult 
	generic (
	S   :  integer) ;
	port (
	A,  B     :   in   bit_vector (S-1  downto 0) ;
	R :   out bit_vector (S-1  downto 0) ;
	cout   :   out bit) ;
end component ;

end cell ;
