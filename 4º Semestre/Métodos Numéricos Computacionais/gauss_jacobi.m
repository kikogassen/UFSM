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


%A = rand(10,10);
%b = rand(10,1);
%n = size(A);
%for i=1:n
%    for j=1:n
%        if i==j
%            A(i,j) = 1000*A(i,j);
%        end
%    end
%end
%nmax = 1000;
%x0 = rand(10,1);
%tol = 0.001;


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

if norm(C, inf)>=1
    if norm(C, 1)>=1
        fprintf('Não há garantias de convergência\n');
        return;
    end
end

% método iterativo

natual = 1;
erro = tol;
while (natual<=nmax && erro>=tol)
    x1 = C*x0' + g';
    erro = norm(x1-x0, Inf)/norm(x1, Inf);
    x0 = x1;
    natual = natual + 1;
end

% saída

if (natual>nmax)
    fprintf('Estourou o limite de iterações');
end
fprintf('\nO vetor solução, com %d iterações, é:\n', natual);
for i = 1:n
    fprintf(' x(%d) = %f\n',i,x0(i));
end