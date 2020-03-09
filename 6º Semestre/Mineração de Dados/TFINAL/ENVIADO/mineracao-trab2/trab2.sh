#!/bin/sh

cd dataset

# Atera a caixa para minusculas
tr '[:upper:]' '[:lower:]' < topics.csv            >            topics_aux.csv
tr '[:upper:]' '[:lower:]' < papers_data_noise.csv > papers_data_noise_aux.csv
tr '[:upper:]' '[:lower:]' < papers_subt_noise.csv > papers_subt_noise_aux.csv

# Remove espaços antes e depois de delimitadores
sed -i "s/ \?; \?/;/g"            topics_aux.csv
sed -i "s/ \?, \?/,/g" papers_data_noise_aux.csv
sed -i "s/ \?, \?/,/g" papers_subt_noise_aux.csv
sed -i "s/ \?- \?/-/g" papers_subt_noise_aux.csv

# Converte status para 2 (rejected) ou 1 (accepted)
sed -i "s/accepted/1/g" papers_data_noise_aux.csv
sed -i "s/rejected/2/g" papers_data_noise_aux.csv

# Remove as colunas descritivas, mantem as de identificação
cut -d";" -f1,3 topics_aux.csv         > topics_final.csv

# Remove as primeiras colunas
cut -d, -f2- papers_data_noise_aux.csv > papers_data_noise_aux2.csv
cut -d, -f2- papers_subt_noise_aux.csv > papers_subt_noise_aux2.csv

# Remove linhas com problemas
sed -i '/^[0-9]\,/d' papers_data_noise_aux2.csv
sed -i '/^[0-9]\,/d' papers_subt_noise_aux2.csv
sed -i '/^na/d' papers_data_noise_aux2.csv
sed -i '/^na/d' papers_subt_noise_aux2.csv

# Split dos subtopicos
awk -F '[,-]' '{for(i=2;i<=NF;i++){print $1,$i;}}' OFS="," papers_subt_noise_aux2.csv > papers_subt_noise_final.csv

mv papers_data_noise_aux2.csv papers_data_noise_final.csv

# Remove arquivos auxiliares
rm *_aux*.csv

cd ..

# Executa o script R
# Rscript trab2.r
R -f trab2.r
