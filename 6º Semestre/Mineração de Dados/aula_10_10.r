data(mtcars)
mtcars$kpl <- mtcars$mpg * 0.425
mtcars$peso <- mtcars$wt * 0.453
cambio <- factor(mtcars$am, levels = c(0, 1), labels=c("Automático", "Manual"))
modelo <- lm(peso~kpl, data=mtcars)
install.packages("ggplot2")
library(ggplot2)
qplot(peso, kpl, data = modelo, color = cambio, shape = cambio, geom = c("point", "smooth"), xlab = "Peso (em toneladas)", ylab = "Km/l", main = "Modelo de regressão")

install.packages("UsingR")
library(UsingR)
