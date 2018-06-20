program foo;
// variables globales
var i, j, b, c, d, k: integer; msg: char;

procedure proc(c : char);
begin
  //c := x + y;
  write(c)
end;

// compound statements: "main"
begin
  i := 0;
  d := 1;
  c := 8;
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
          if j = i then write(d) else proc(c);
          j := j + 1
        end;
      i := i+1
    end
end.
