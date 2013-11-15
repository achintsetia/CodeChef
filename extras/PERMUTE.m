MAX = 10;
ANS = zeros(MAX, 2*MAX-1);
ANS1 = zeros(MAX, 2*MAX-1);
for N=3:MAX
  for M=N+1:2*N-1
    
    A = perms(1:N);
    
    count = factorial(N);
    for i=1:size(A,1)
      for j=1:N-1
        if( A(i,j)+A(i,j+1) > M)
          count = count-1;
          break;
        end
      end
    end
    ANS(N,M) = count;
    if( ANS(N-1,M-1) > 0), ANS1(N,M) = ANS(N,M) / ANS(N-1,M-1);
    else
      ANS1(N,M) = ANS(N,M);
    end
  end
end
