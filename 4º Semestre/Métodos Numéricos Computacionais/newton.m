%método de newton

clear
clc

%entradas

f = input ('Digite a funcao -->', 's');
f = str2sym(f);
x0 = input ('Digite o valor inicial -->');
tol = input ('Digite a tolerancia maxima desejada -->');
nmax = input ('Digite o número máximo de iterações -->');

%método

erro=1;
n=0;
while (erro>tol)
    fx0 = subs(f, x0);
    df = diff(f);
    dfx0 = subs(df, x0);
    x1 = x0 - fx0/dfx0;
    fx1 = subs(f, x1);
    if (abs(fx1)<tol)
        fprintf ('O método convergiu pela imagem e a solução é %f\n', x1);
        return;
    end
    erro = abs(x1-x0)/abs(x1);
    x0 = x1;
    n = n+1;
    if (n>nmax)
        fprintf ('Esgotou-se o número de iterações');
        return;
    end
end

fprintf ('O método convergiu pelo domínio e a solução é %f\n', x1);