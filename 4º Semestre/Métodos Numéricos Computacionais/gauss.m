% configurações iniciais

clear
clc
format short

% entrada dos dados

A = input('Entre com a matriz A-->');
b = input('Entre com o vetor b -->');

[n k] = size(A);

aum = [A b];

% Método de Eliminação de Gauss

for j = 1:n-1
    for i = j+1:n
        t = j;
        while (t <= n && aum(t,t)==0)
            t = t + 1;
        end
        if (t>n)
            fprintf('Não achou um pivô diferente de 0')
            return;
        else
            aum([j t],:) = aum([t j],:);
        end
        m(i,j) = aum(i,j)/aum(j,j);
        aum(i,:) = aum(i,:) - m(i,j)*aum(j,:);
    end
end

% resolução da matriz triangular superior

x(n) = aum(n, n+1)/aum(n,n);
for i = n-1:-1:1
    soma = 0;
    for j = i+1:n
        soma = soma + aum(i,j)*x(j);
    end
    x(i) = (aum(i,n+1)-soma)/aum(i,i);
end

fprintf('\n\nO vetor solução é:\n')
for i = 1:n
    fprintf(' x(%d) = %f\n',i,x(i));
end