program pr1;
var
sum,i:integer;
begin
	sum:=0;
	for i:=1 to (50 div 4) do
		sum:=sum + i*4;
	writeln(sum);
end.
