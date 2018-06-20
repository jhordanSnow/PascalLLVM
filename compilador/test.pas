program foo;
// variables globales
var i, j, b, c, d: integer; msg: char; caca: array [1..100] of char;

// compound statements: "main"
begin
  i := 0;
  d := 1;
  c := 0;
  msg := 'Repeticiones ';
  write(msg);
  msg := '______________';
  read(b);
  while i < b do
    begin
      j := 0;
      write(msg);
      while j < b do
        begin
          if j = i then write(d) else write(c);
          j := j + 1
        end;
      i := i+1
    end
end.
