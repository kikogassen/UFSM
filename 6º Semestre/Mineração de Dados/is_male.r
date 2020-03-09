is_male <- function(weight, hair_length) {
  if (weight <= 160){
    if (hair_length > 2){
      return (FALSE)
    }
  }
  return (TRUE)
}

entropia <- function(a,b){
  total <- a + b
  return (-(a/total) * log2(a/total) - (b/total) * log2(b/total))
}