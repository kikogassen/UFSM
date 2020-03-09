%método das secantes

clear
clc

%entradas

f = input ('Digite a funcao -->', 's');
f = str2sym(f);
x0 = input ('Digite o valor inicial x0 -->');
x1 = input ('Digite o valor inicial x1 -->');
tol = input ('Digite a tolerancia maxima desejada -->');
nmax = input ('Digite o número máximo de iterações -->');

%método

erro=1;
n=0;
while (erro>tol)
    fx0 = subs(f, x0);
    fx1 = subs(f, x1);
    x2 = ((x0*fx1)-(x1*fx0))/(fx1-fx0);
    erro = abs(x2-x1)/abs(x2);
    x0 = x1;
    x1 = x2;
    n = n+1;
    if (n>nmax)
        fprintf ('Esgotou-se o número de iterações');
        return;
    end
end

fprintf ('O método convergiu pelo domínio com %d iterações e a solução é %f\n', n, x2);