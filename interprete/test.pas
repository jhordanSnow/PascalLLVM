program foo;
// variables globales
var a : array [0..6] of char;

// compound statements: "main"
begin
    a := 2;
    while a=a do
        begin 
            write(a)
        end
end.
