install.packages("caret")
library(caret)
csv <- read.csv("GeyserUFSM.csv")
inTrain <- createDataPartition(y=csv$espera, p=0.5, list=FALSE)
trainFaith <- faithful[inTrain,];
testFaith <- faithful[-inTrain,];
meuModeloLinear <- lm(eruptions ~ waiting, data=trainFaith)
b <- c(200, 230, 245, 270)
b <- data.frame(b)
names(b)[1] <- "waiting"
predict(meuModeloLinear, b)