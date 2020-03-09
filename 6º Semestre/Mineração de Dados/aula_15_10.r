library(UsingR)
dt <- data.frame(Galton)
dt <- lapply(dt, function(x), x/39.37)
dt <- data.frame(dt)

x <- as.vector(dt$parent - mean(dt$parent))
y <- as.vector(dt$child - mean(dt$child))

dadosFr <- as.data.frame(table(x, y))

names(dadosFr)[1] <- "parent"
names(dadosFr)[2] <- "child"

plot(as.vector(dadosFr$parent), as.vector(dadosFr$child), cex = dadosFr$Freq*0.1)

