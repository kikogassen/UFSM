
#minmax
DF_minMax <- DF_vendasLucro
for (i in 1:nrow(DF_vendasLucro)){
  DF_minMax$Vendas[i] <- (DF_vendasLucro$Vendas[i]-min(DF_vendasLucro$Vendas))/(max(DF_vendasLucro$Vendas) - min(DF_vendasLucro$Vendas));
  DF_minMax$Lucro[i] <- (DF_vendasLucro$Lucro[i]-min(DF_vendasLucro$Lucro))/(max(DF_vendasLucro$Lucro) - min(DF_vendasLucro$Lucro));
}



#Z Score
DF_zScore <- DF_vendasLucro
for (i in 1:nrow(DF_vendasLucro)){
  DF_zScore$Vendas[i] <- (DF_vendasLucro$Vendas[i] - mean(DF_vendasLucro$Vendas))/sd(DF_vendasLucro$Vendas);
  DF_zScore$Lucro[i] <- (DF_vendasLucro$Lucro[i] - mean(DF_vendasLucro$Lucro))/sd(DF_vendasLucro$Lucro);
}


#escalonamento
DF_escalonamento <- DF_vendasLucro
while (max(DF_escalonamento$Vendas) >= 1){
  for (i in 1:nrow(DF_vendasLucro)){
    DF_escalonamento$Vendas[i] <- DF_escalonamento$Vendas[i]/10;
  }
}

while (max(DF_escalonamento$Lucro) >= 1){
  for (i in 1:nrow(DF_vendasLucro)){
    DF_escalonamento$Lucro[i] <- DF_escalonamento$Lucro[i]/10;
  }
}

DF_final <- data.frame(c(DF_vendasLucro$Vendas), c(DF_vendasLucro$Lucro), c(DF_minMax$Vendas), c(DF_minMax$Lucro), c(DF_zScore$Vendas), c(DF_zScore$Lucro), c(DF_escalonamento$Vendas), c(DF_escalonamento$Lucro));
