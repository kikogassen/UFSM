% configurações iniciais

clear
clc

% entrada dos dados

f = input ('Entre com a f(x) -->', 's');
f = str2sym(f);
a = input('Entre com o limite inferior a --> ');
b = input('Entre com o limite superior b --> ');
n = input('Entre com o número de subintervalos -->');

h = (b-a)/n;

% gerar o vetor x

k=1;
for i=a:h:b
    x(k)=i;
    k=k+1;
end

% gerar o vetor y

k=1;
for i=a:h:b
    y(k) = subs(f, x(k));
    k = k+1;
end

% calcula integral

soma = 0;
for i=1:(n+1)
    if i==1 || i==(n+1)
        soma = soma + y(i);
    elseif (mod (i,2)) == 0
        soma = soma + 4*y(i);
    elseif (mod (i,2)) ~= 0
        soma = soma + 2*y(i);
    end
end

I = (h/3)*soma;

fprintf('%f', I);
fprintf('\n');

% plot

plot(x, y, 'r*');
grid on;
hold on;