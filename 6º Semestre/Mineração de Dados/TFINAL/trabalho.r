#read data
topics <- read.csv("topics.csv", sep = ";")
papers_subt_noise <- read.csv("papers_subt_noise.csv", sep = ",")
papers_data_noise <- read.csv("papers_data_noise.csv", sep = ",")

#clean data
papers_subt_noise <- papers_subt_noise[!(papers_subt_noise$paper < 100),]

#separate data
papers <- papers_subt_noise[0,]
for (i in 1:nrow(papers_subt_noise)){
  topicsList = as.list(strsplit(toString(papers_subt_noise$subtopics[i]), '[[:punct:]]')[[1]])
  for (j in 1:length(topicsList)){
    papers[nrow(papers) + 1,] = list(papers_subt_noise$X[i], papers_subt_noise$paper[i], topicsList[[j]])
  }
}
