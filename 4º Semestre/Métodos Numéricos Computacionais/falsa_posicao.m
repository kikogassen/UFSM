% metodo da falsa posicao

clear
clc

% entradas
f = input ('Digite a funcao -->', 's');
f = str2sym(f);
a = input ('Digite o valor inferior a -->');
b = input ('Digite o valor superior b -->');
tol = input ('Digite a tolerancia maxima desejada -->');

% metodo da bissecao

fa = subs(f, a);
fb = subs(f, b);

% garante que satisfaça o teorema

while (fa*fb>=0)
    fprintf('Não satisfez o Teorema de Bolzano\n');
    a = input ('Digite o valor inferior a -->');
    b = input ('Digite o valor superior b -->');
    fa = subs(f, a);
    fb = subs(f, b);
end


intervalo = abs(b-a);
fprintf('a       |f(a)     |b       |f(b)    |pm      |f(pm)    |intervalo\n');

while (intervalo>tol)
    pm = (a*fb - b*fa)/(fb-fa);
    fpm = subs(f, pm);
    fprintf('%f|%f|%f|%f|%f|%f|%f', a, fa, b, fb, pm, fpm, intervalo);
    fprintf('\n');
    if (abs(fpm)<tol)
        fprintf('A solucao foi obtida pela imagem: %f\n', pm);
        clf reset
        vx = [a;b];
        vy = [fa;fb];
        hold on
        grid on
        fplot(f, [a b])
        plot(vx, vy, 'r-')
        plot(pm,0,'g*')
        hold off
        return;
    end
    if (fa*fpm<0)
        b = pm;
        fb = fpm;
    elseif (fb*fpm<0)
        a = pm;
        fa = fpm;
    end
    intervalo = abs(b-a);
end
if (abs(b-a)<tol)
    fprintf('A solucao foi obtida pelo domínio: %f\n', pm);
    clf reset
    vx = [a;b];
    vy = [fa;fb];
    hold on
    grid on
    fplot(f, [a b])
    plot(vx, vy, 'r-')
    plot(pm,0,'g*')
    hold off
else
    fprintf('Nao achou a solucao\n');
end
    