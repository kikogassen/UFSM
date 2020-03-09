qual_nome <- function(str, nomes){
  dist_str <- numeric(length(nomes))
  for (i in 1:length(nomes)){
    dist_str[i] <- adist(str, nomes[i])[1]
  }
  print(nomes[which.min(dist_str)])
}

nomes <- as.vector(csv$Jogadore.a.s.1)
nomes <- nomes[nomes != ""]
matrix <- matrix("", nrow = nrow(csv), ncol = 3)
for (i in 1:nrow(csv)){
  nomes_tmp <- unlist(strsplit(as.character(csv$Jogadore.a.s[i]), ","), use.names=FALSE)
  for (j in 1:length(nomes_tmp)){
    matrix[i, j] <- qual_nome(nomes_tmp[j], nomes = nomes)
  }
}

#individual
individual <- setNames(data.frame(matrix(ncol = 3, nrow = length(nomes))), c("nome", "vitorias", "derrotas"))
for (i in 1:length(nomes)){
  individual$nome[i] <- nomes[i]
  individual$vitorias <- 0
  individual$derrotas <- 0
}

for (i in 1:nrow(csv)){
  if (csv$Resultado[i] == "GANHOU"){
    for (j in 1:ncol(matrix)){
      if (matrix[i, j] != ""){
        individual$vitorias[which(individual$nome == matrix[i, j])] <- individual$vitorias[which(individual$nome == matrix[i, j])] + 1 
      }
    }
  } else {
    for (j in 1:ncol(matrix)){
      if (matrix[i, j] != ""){
        individual$derrotas[which(individual$nome == matrix[i, j])] <- individual$derrotas[which(individual$nome == matrix[i, j])] + 1 
      }
    }
  }
}

melhor_individual <- individual$nome[which.max(individual$vitorias)]

#em time
