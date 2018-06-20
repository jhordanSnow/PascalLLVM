program foo;
// variables globales
var a, b, c, d: integer; e: char; caca: array [1..100] of integer;

// compound statements: "main"
begin
    read(a,b,c);
    // if b > a then write(b) else write(a);
    while a<=b do
        begin
            write(a);
            a:=a+c
        end
end.
