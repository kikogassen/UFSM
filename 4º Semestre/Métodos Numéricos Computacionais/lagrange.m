% configurações iniciais

clear
clc
format long
syms x y

% entrada dos dados

x = input('Entre com o vetor x --> ');
y = input('Entre com o vetor y --> ');

hold on;
grid on;
plot(x,y,'*');

n = length(x);
grau = n-1;

p = '';

for i=1:n
    numerador = '';
    denominador = 1;
    for j=1:n
        if i~=j
            if j==1 || (j==2 && i==1)
                numerador = [numerador '(x-'];
            else
                numerador = [numerador '*(x-'];
            end
            numerador = [numerador '(' num2str(x(j)) '))'];
            denominador = denominador * (x(i)-x(j));
        end
    end
    L = [numerador ')/(' num2str(denominador)];
    if i==1
        p = [p '((' num2str(y(i)) ')*' L ')']; 
    else
        p = [p ' + ((' num2str(y(i)) ')*' L ')'];
    end
end

hold on;
grid on;
fun = str2func(['@(x)' p]);
fplot(fun, [x(1), x(n)]);

fprintf(p);
fprintf('\n');
