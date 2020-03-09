% configurações iniciais

clear
clc
format short

% entrada dos dados

x = input('Entre com o vetor x --> ');
y = input('Entre com o vetor y --> ');

n = length(x);

% escolha do ajuste

ajuste = input('Escolha o ajuste:\n0 - Polinomial\n1 - Hiperbólico\n2 - Exponencial de base e\n3 - Exponencial de base qualquer\n4 - Geométrico\n');

switch ajuste
    case 0
        grau = input('Entre com o grau do polinômio --> ');
    case 1
        for i=1:n
            y(i) = 1/y(i);
        end
        grau = 1;
    case 2
        for i=1:n
            y(i) = log(y(i));
        end
        grau = 1;
    case 3
        for i=1:n
            y(i) = log(y(i));
        end
        grau = 1;
    case 4
        for i=1:n
            y(i) = log(y(i));
            x(i) = log(x(i));
        end
        grau = 1;
    otherwise
        
end

A = zeros(grau+1, grau+1);
b = zeros(grau+1, 1);

% construção de A e b

for i=1:grau+1
    for j=1:grau+1
       A(i,j) = sum(x.^(2*grau+2-i-j));
    end
    b(i) = sum(y.*(x.^(grau-i+1)));
end
A(grau+1, grau+1) = n;

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

% mostrar resultados

switch ajuste
    case 0
        n = grau+1;
        fprintf('\n\nO vetor solução é:\n');
        p = [num2str(x(1)) '*x^' num2str(n-1)];
        for i = 2:n
            p = [p ' + (' num2str(x(i)) ')* x^' num2str(n-i)];
        end
        fprintf(p);
        fprintf('\n');
    case 1
        n = grau+1;
        fprintf('\n\nO vetor solução é:\n');
        p = ['1/(' num2str(x(1)) '*x + ' num2str(x(2)) ')'];
        fprintf(p);
        fprintf('\n');
    case 2
        n = grau+1;
        fprintf('\n\nO vetor solução é:\n');
        p = [num2str(exp(x(2))) '*e^(' num2str(x(1)) '*x)'];
        fprintf(p);
        fprintf('\n');
    case 3
        n = grau+1;
        fprintf('\n\nO vetor solução é:\n');
        p = [num2str(exp(x(2))) '*' num2str(exp(x(1))) '^x'];
        fprintf(p);
        fprintf('\n');
    case 4
        n = grau+1;
        fprintf('\n\nO vetor solução é:\n');
        p = [num2str(exp(x(2))) '*x^' num2str(x(1))];
        fprintf(p);
        fprintf('\n');
    otherwise
        
end

