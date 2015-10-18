program prj4;
var
sum,n:integer;
begin
sum:=0;
n:=20;
while n<=100 do
begin
if (n mod 3=0) then
	sum:= sum+n;
n:=n+1;
end;
writeln(sum);
end.
