% configurações iniciais

clear
clc
format long
syms x y

% entrada dos dados

x = input('Entre com o vetor x --> ');
y = input('Entre com o vetor y --> ');

n = length(x);
A = zeros(n, n+1);
A(:, 1) = x;
A(:, 2) = y;

for j=3:(n+1)
   for i=1:(n-j+2)
      A(i,j) = (A(i+1, j-1) - A(i, j-1)) / (A(i+j-2, 1) - A(i, 1)); 
   end
end

% gerar polinomio

p = '';

for i=2:(n+1)
    if (i~=2)
        p = [p '+'];
    end
    for j=1:(i-2)
        p = [p '(x-' num2str(A(j,1)) ')'];
    end
    p = [p '(' num2str(A(1,i)) ')'];
end

fprintf(p);
fprintf('\n');