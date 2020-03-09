#!/usr/bin/env Rscript

library(arules)

# Lê os arquivos
topics            <- data.frame(read.csv("dataset/topics_final.csv"           , header = TRUE, sep = ";"))
papers_subt_noise <- data.frame(read.csv("dataset/papers_subt_noise_final.csv", header = TRUE, sep = ","))
papers_data_noise <- data.frame(read.csv("dataset/papers_data_noise_final.csv", header = TRUE, sep = ","))

# Faz o merge entre eles
papers_data_subt_noise  <- merge(papers_data_noise,papers_subt_noise, by = 'paper')
dados <- merge(papers_data_subt_noise,topics, by.x ='subtopics', by.y ='subtopic')

dados$status = as.numeric(dados$status)
for (i in 1:6){
	dados[,i] = as.factor(dados[,i])
}


# Transforma em transações
dados2 <- as(dados, "transactions")

# Gera regras utilizando o algoritmo apriori
rules <- sort(apriori(data = dados2, parameter = list(support = 0.01, confidence = 0.6)), by = "support")
capture.output(inspect(rules),file = "resultados/rules_todas.txt")

# Escreve arquivos
write.table(dados,"resultados/dados_agrupados.csv", sep = ",", row.names = FALSE)

# Subareas que historicamente tem maior possibilidade de aceite
subarea <- sort(subset(rules, (size(lhs) == 1) & (lhs  %pin% "subtopics=") & (rhs %in% "status=1")), by = "support")

# Escreve arquivo com as regras
capture.output(inspect(subarea),file = "resultados/regras_subareas.txt")

# Converte coluna status para número
dados$status = as.numeric(dados$status)

# Aplica o kmeans
# Número de conferencias por ano não é constante. Entre 2010 e 2012 e em 2016, foram duas conferencias por ano. Já em 2013, 2014 e 2017 apenas uma. E no ano de 2015 foram 3 conferencias.
# year X status
teste <- kmeans(dados[,4,5],8)
capture.output(teste$size,teste$centers,teste$withinss,table(teste$cluster, dados$conf),file = "resultados/conf.txt")

# subtopicos 63,64,66,67,68 são novos e subtopico 65 não tem paper
# 
# 2	 Service Management	63	 IoT Services
# 2	 Service Management	64	 Security Services
# 3	 Business Management	66	 Economic Aspects
# 6	 Technologies	67	 Software-Defined Networking
# 6	 Technologies	68	 Network Function Virtualization
# 3	 Business Management	65	 Regulatory Perspective
capture.output(teste$size,teste$centers,teste$withinss,table(teste$cluster, dados$subtopics),file="resultados/sub.txt")

# subtopicos 6, 20, 38 tem mais rejeições que aceites
# status X topic
teste <- kmeans(dados[,5,6],2)
capture.output(teste$size,teste$centers,teste$withinss,table(teste$cluster, dados$subtopics),file="resultados/mais.txt")
