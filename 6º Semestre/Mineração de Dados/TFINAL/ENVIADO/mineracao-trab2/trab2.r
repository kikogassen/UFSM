#!/usr/bin/env Rscript

library(arules)

# Lê os arquivos
topics            <- read.csv("dataset/topics_final.csv"           , header = TRUE, sep = ";")
papers_subt_noise <- read.csv("dataset/papers_subt_noise_final.csv", header = TRUE, sep = ",")
papers_data_noise <- read.csv("dataset/papers_data_noise_final.csv", header = TRUE, sep = ",")

# Merge entre os dados
papers_data_subt_noise  <- merge(papers_data_noise,papers_subt_noise, by = 'paper')
dados <- merge(papers_data_subt_noise,topics, by.x ='subtopics', by.y ='subtopic')

# Escreve dados em csv
write.table(dados,"resultados/dados_agrupados.csv", sep = ",", row.names = FALSE)

# 
for(i in 1:ncol(dados))
{
    dados[, i] <- as.factor(dados[, i])
}


# Associação: apriori
# Transforma em transações
dados2 <- as(dados,"transactions")

# Gera regras utilizando o algoritmo apriori
rules <- sort(apriori(data = dados2, parameter = list(support = 0.01, confidence = 0.6)), by = "support")

# Subareas que historicamente tem maior possibilidade de aceite
# 4	 Functional Areas       25	 Performance management
# 4	 Functional Areas       26	 Security management
# 5	 Management Approaches	31	 Autonomic and self management
# 6	 Technologies           42	 Cloud computing
subarea <- sort(subset(rules, (size(lhs)==1) & (lhs %pin% "subtopics=") & (rhs %in% "status=1")), by = "support")
capture.output(inspect(subarea),file = "resultados/regras_subtopics.txt")


# Clasterização: kmeans
# Número de conferencias por ano não é constante.
# 2010, 2011, 2012 e 2016:   2 conferencias por ano.
# 2013, 2014 e 2017:         1 conferencia.
# 2015:                      3 conferencias.
# year X status
kmeans_year <- kmeans(dados[,4,5],8)
capture.output(kmeans_year$size,kmeans_year$centers,kmeans_year$withinss,table(kmeans_year$cluster,dados$conf),file = "resultados/conf.txt")

# Subtopicos 63,64,66,67,68 aparecem apenas em 2017 subtopico 65 não tem paper
# 
# 2	 Service Management	    63	 IoT Services
# 2	 Service Management	    64	 Security Services
# 3	 Business Management	66	 Economic Aspects
# 6	 Technologies           67	 Software-Defined Networking
# 6	 Technologies           68	 Network Function Virtualization
# 3	 Business Management	65	 Regulatory Perspective
capture.output(kmeans_year$size,kmeans_year$centers,kmeans_year$withinss,table(kmeans_year$cluster,dados$subtopics),file="resultados/sub.txt")

# Subtopicos 6, 20, 38 tem mais rejeições
# 1	 Network Management	    6	 Sensor Networks
# 3	 Business Management	20	 Legal & ethical issues
# 6	 Technologies           38	 Mobile agents
# status X topic
kmeans_status <- kmeans(dados[,5,6],2)
capture.output(kmeans_status$size,kmeans_status$centers,kmeans_status$withinss,table(kmeans_status$cluster, dados$subtopics),file="resultados/mais_rejected.txt")
