% configurações iniciais

clear
clc
format long
syms x y

% entrada dos dados

x = input('Entre com o vetor x --> ');
y = input('Entre com o vetor y --> ');
xd = x;
yd = y;

hold on;
grid on;
plot(x,y,'*');

n = length(x);

A = zeros(n, n);
b = zeros(n, 1);

% construção de A e b

for i=1:n
    for j=1:n
       A(i,j) = x(i).^(n-j);
    end
    b(i) = y(i);
end

% Método de Eliminação de Gauss

[n k] = size(A);

aum = [A b];

for j = 1:n-1
    for i = j+1:n
        t = j;
        while (t <= n && aum(t,t)==0)
            t = t + 1;
        end
        if (t>n)
            fprintf('Não achou um pivô diferente de 0');
            fprintf('\n');
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

% mostrar resultados

fprintf('\n\nO vetor solução é:\n');
p = '';
for i = 1:n
    if x(i) ~= 0
        if x(i)>=0
            p = [p '+'];
        end
        p = [p '' num2str(x(i)) ''];
        if i~=n
            p = [p '*x^' num2str(n-i) ' '];
        end
    end
end
fprintf(p);
fprintf('\n');
fun = str2func(['@(x)' p]);
fplot(fun, [min(xd), max(xd)]);