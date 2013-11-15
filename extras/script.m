H = [1 2 3 4 5]
D = [5 2 3 1 4];
I = randi(size(D,2));
D(I) = D(I) + 15
S = sum(D-H)

count = 0;
while( ~isequal(H,D))
  [Max MI] = min(D-H);
  H = H +1;
  H(MI) = H(MI) - 2;
  H
  count = count+1;
  S = sum(D-H)
  pause;
end

count
