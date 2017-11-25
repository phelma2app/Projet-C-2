
library STD;
  use STD.textio.all;
library IEEE;
  use IEEE.bit_1164.all;
  use IEEE.bit_misc.all;
  use IEEE.bit_arith.all;

entity typage is
  end typage;

architecture essai of typage is

TYPE  couleur  IS  (bleu,  blanc,  rouge);
TYPE  std_logic  is  ('U',  'X',  '0',  '1',  'Z',  'W',  'L',  'H',  '-');

TYPE  mot  IS  array (0  TO  31)  OF  bit;
TYPE  drapeau  IS  array (0  TO  2)  OF  couleur;


signal one : couleur;
signal two : std_logic;

signal three : mot;
signal four: drapeau;

begin
 end vide;

