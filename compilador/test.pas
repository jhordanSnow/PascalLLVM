program foo;
// variables globales
var a, b, c, d: integer; e: char; caca: array [1..100] of integer;

// compound statements: "main"
begin
    a := 2;
    b := 1;
    while a<10 do
        begin
            write(a);
            a:=a+b
        end.
end.
