program foo(boo);
// variables globales
var a, b, c, d: integer;

function addition(a, b: integer) : integer;
   var c: Integer;
   Begin
      return a + b
   end;

// compound statements: "main"
Begin
   a := addition(1, 2);
   putchar(a)
end.
