% configurações iniciais

clear
clc
format short

% entrada dos dados

A = input('Entre com a matriz A --> ');
b = input('Entre com o vetor b --> ');
nmax = input('Entre com o máximo de iterações --> ');
tol = input('Entre com a tolerância --> ');
x0 = input('Entre com o vetor inicial x0 --> ');

% Construção de C e g

n = size(A);

for i=1:n
    for j=1:n
        if i==j
            C(i,j) = 0;
        else
            C(i,j) = -A(i,j)/A(i,i);
        end
    end
    g(i) = b(i)/A(i,i);
end

% Teste de convergência

beta(1) = sum(abs(C(1,2:n)));
for i=1:n
    soma=0;
    if i==1
        for j=1:n
            beta(i) = soma + abs(C(i,j));
        end
    else
        soma1=0;
        for j=1:i-1
            soma1 = soma1 + beta(j) + abs(C(i,j));
        end
        for j=i+i:n
            soma = soma + abs(C(i,j));
        end
        beta(i) = soma1+soma;
    end
end

if norm(beta, inf) >= 1
    fprintf('Não há garantias de convergência\n');
    return;
end
                
% método iterativo

natual = 1;
erro = tol;
while (natual<=nmax && erro>=tol)
    for i=1:n
        soma=0;
        for j=1:n
            if i<=j
                soma = soma + C(i,j)*x0(j);
            else
                soma = soma + C(i,j)*x1(j);
            end
        end
        x1(i) = soma + g(i);
    end
    erro = norm(x1-x0, Inf)/norm(x1, Inf);
    x0 = x1;
    natual = natual + 1;
end

% saída

if (natual>nmax)
    fprintf('Estourou o limite de iterações');
    return;
end
fprintf('\nO vetor solução, com %d iterações, é:\n', natual);
for i = 1:n
    fprintf(' x(%d) = %f\n',i,x0(i));
end