% ------------------------------ %
%      LOGICA DE PREDICADO       %
% BASE DE CONHECIMENTO - Futebol %
% ------------------------------ %
% Frederico Gassen,              %
% Mauricio Schmaedeck,           %
% Pedro Henrique Rossato,        %
% Talles Siqueira Ceolin         %
% ------------------------------ %

time(gremio).
time(inter).

jogador(paulo).      % goleiro gremio      
jogador(kannemann).  % zagueiro gremio 
jogador(everton).    % atacante gremio 
jogador(marcelo).    % goleiro inter   
jogador(moledo).     % zagueiro inter 
jogador(guerrero).   % atacante inter 

tecnico(renato).
tecnico(odair).

joga_no(paulo, gremio).     
joga_no(kannemann, gremio).   
joga_no(everton, gremio).     
joga_no(renato, gremio).     % tecnico    
joga_no(marcelo, inter).      
joga_no(moledo, inter).     
joga_no(guerrero, inter).    
joga_no(odair, inter).       % tecnico 

posicao(renato, tecnico).
posicao(odair, tecnico).
posicao(paulo, goleiro).
posicao(marcelo, goleiro).
posicao(everton, atacante).
posicao(guerrero, atacante).
posicao(kannemann, zagueiro).
posicao(moledo, zagueiro).

escalacao(Time) :-
    joga_no(_, Time).
    