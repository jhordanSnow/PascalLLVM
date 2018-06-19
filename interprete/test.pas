program foo;
// variables globales
var a, b, c, d: integer; e: char; caca: array [1..100] of integer;

// compound statements: "main"
begin
   read(a, b, c, d);
   read(caca[a]);
   a := (b+c)*d div a;
   write(a);
   write(caca[a])
end.
