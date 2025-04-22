x11(); #ouvre un affichage pour les résultats
pdf(); # mets la sortie dur pdf
dev.list(); # la liste des devices avec leurs id
dev.cur(); #donne le device actuel
dev.set(3); #set le device sur celui de l'indice
dev.off(2); #ferme le device donnée en id
dev.off(); #ferme un au hasard ( sans doute le device actuel en dernier )
rnorm(1000); #crée un graphique loi normale de nbparams points

plot(dnorm, xlim = c(-5,10), col = "blue", main = "graphique"); #graphique avec quelques modifications de paramètres
madensite = function ( x ) { dnorm (x , mean =3 , sd =2) };
plot (madensite, xlim = c(-5,10), col = "red", add=T)
legend("topright", legend = c ("dnorm" ,"madensite"), col= c( "blue" ,"red" ) , lty=1)

mais = read.table("mais.txt", sep="\t",header=TRUE)
plot(mais$Hauteur~mais$Masse)

plot(mais$Hauteur~mais$Masse,col=ifelse(mais$Couleur=="Jaune","yellow",ifelse(mais$Couleur=="Rouge","red","orange")),pch=69,
     main = "Hauteur des pieds de maïs en fonction de la masse",
     xlab = "Hauteur", ylab = "Masse")
grid(10,10, "lightgrey")
legend("bottomright", legend = c("jaune", "orange", "rouge"), col = c("yellow", "orange", "red"), lty=1)
reg = lm(mais$Hauteur ~ mais$Masse)
abline(reg, col ="blue")

hist(mais$Nb.grains, breaks= 20, probability = T)

hist( mais$Hauteur, col = grey(0.9), border = grey(0.2),
      main = paste("Taille de", nrow(mais), " pieds de ma¨ıs"),
      xlab = "Taille [cm]",
      ylab = "Effectifs relatifs",
      labels = TRUE, las = 1, ylim = c(0, 0.01), probability = T)


x <- seq(from = min(mais$Hauteur, na.rm=T), to = max(mais$Hauteur, na.rm=T),length = 7)
lines(x, dnorm(x, mean(mais$Hauteur, na.rm = TRUE), sd(mais$Hauteur,na.rm = TRUE)))

barplot(sort(table(mais$Parcelle)), horiz = T, col = c("blue", "green", "pink", "orange"))

pie(sort(table(mais$Parcelle)),labels = c(14,17,33,36), col = c("orange", "green", "blue", "pink"))
legend("bottomright", legend = c("Sud", "Nord", "Est", "Ouest"), col = c("orange","green", "blue", "pink"), lty=1)      

boxplot( mais$Masse.grains, col = grey(0.8),
         main = paste("Masse des grains pour ", nrow(mais), " pieds de maïs"),
         ylab = "g", las = 1)
rug(mais$Masse.grains, side = 2)

boxplot(mais$Hauteur.J7 ~ mais$Attaque)

#exercice 17
P1 = pnorm(1.5)

#exercice 18
P2 = pnorm(2.5, lower.tail = F) # > donc lower.tail = F
P3 = pnorm(-1.5)
P4 = pnorm(2.5)
P5 = P4 - P3 

#exercice 19
P6 = pnorm(10, 2, 5, lower.tail = T)
P7 = pnorm(0, 2, 5)
P8 = P6-P7
P8

#exercice 20
marepartition = function(x){
  return (pnorm(x,3,2))
  }

marepartition(2)

#exercice 21
plot(pnorm, xlim = c(-4, 10), ylim= c(0,1), col = "blue");
plot(marepartition, xlim = c(-4,10),ylim= c(0,1), col = "red", add = T)
legend("topleft", legend = c("pnorm","marepartition"), col= c( "blue" ,"red" ) , lty=1)

#exercice 22
P9 = qnorm(0.95)
P10 = qnorm(0.1)
P11 = qnorm(0.99, lower.tail = F)
P12 = qnorm(0.975)
P12

#exercice 23
P13 = qnorm(0.95,2,5)
P14 = qnorm(0.05, 2, 5)
P15 = qnorm(0.975, 2, 5)

#exercice 24
echa = rnorm(100)
echb = rnorm(100,3,2)

mean(echa)
mean(echb)
sd(echa)
sd(echb)

#exercice 25
echa = rnorm(10000)
echb = rnorm(10000,3,2)

mean(echa)
mean(echb)
sd(echa)
sd(echb)


#exercice 26
hist( echa, col = "blue", xlim = c(-4,10), main= "Histogramme des deux simulations",xlab = "histogrammes",
      ylab = "Density", probability = T)
hist(echb, col = "red",add = T, probability = T)
legend("topright", legend = c("N(0,1)","N(3,4)"), col= c( "blue" ,"red" ) , lty=1)

#exercice 27
hist(echa, col = "blue", probability = T, ylim = c(0,0.5))
plot(dnorm,xlim = c(-4,4), add=T)

hist(echb, col = "red", xlim = c(-4,10), probability = T, ylim = c(0,0.5))
plot(madensite,xlim = c(-4,10), add=T)

#exercice 28
boxplot ( echa , col = " blue " , main = " Boxplot N (0 ,1) " )
boxplot(echb, col="red", add=T)

#exercice 29
data = cbind ( echa , echb )
boxplot(data, col=c("blue", "red"))
legend("topleft", legend = c("N(0,1)","N(3,4)"), col= c( "blue" ,"red" ) , lty=1)

#exercice 30



#TP6

mais = read.table("mais.txt", header=T)

#exercice 1
summary(mais)

#exercice 2
newcol = data.frame(Censure.droite = as.factor(mais$Censure.droite))
newmais = mais[,-c(15)]
mais = cbind(newmais,newcol)
summary(mais)

#exercice 3
quanti = c(2,3,4,5,12,14)
quali = c(6,7,8,9,10,11,13,15)

#exercice 4
pairs(maisquanti)

#exercice 5
pairs(maisquanti, col=ifelse(mais$Attaque=="Oui", "pink", "darkgreen"))

#exercice 6
boxplot ( mais$Hauteur ~ mais$Parcelle , col = c("yellow","lightblue","darkgreen", "orange"))

#exercice 7
maishauteur = subset(mais,!is.na(Hauteur) & !is.na(Parcelle), select = c(11,12))
maishauteur
var(maishauteur$Hauteur.J7)

length(mais$Hauteur ~ mais$Parcelle)

#exercice 8
SCT = function(valeur){
  moyenne = mean(valeur)
  return (sum((valeur-moyenne)**2))
}

SCE <- function(valeur, groupe) {
  moyennes_groupes <- tapply(valeur, groupe, mean)  # Moyenne par groupe
  tailles_groupes <- table(groupe)  # Effectifs par groupe
  moyenne_globale <- mean(valeur)
  return(sum(tailles_groupes * (moyennes_groupes - moyenne_globale)^2))
}

SCR = function(valeur, groupe){
  return (SCT(valeur)-SCE(valeur, groupe))
}

rapport = function(valeur, groupe){
  valid_idx = !is.na(valeur) & !is.na(groupe)

  if (sum(valid_idx) == 0) {
    return(NA)
  }
  
  valeur_filtre = valeur[valid_idx]
  groupe_filtre = groupe[valid_idx]
  
  return (SCE(valeur_filtre, groupe_filtre) / SCT(valeur_filtre))
}

SCT(maishauteur$Hauteur.J7)
SCE(maishauteur$Hauteur.J7, maishauteur$Parcelle)
SCR(maishauteur$Hauteur.J7, maishauteur$Parcelle)
rapport(maishauteur$Hauteur.J7, maishauteur$Parcelle)

#Exercice 9 
resultat = function(quanti, quali, datagram){
  for (elem in quanti) {
    for (elem2 in quali) {
      r = rapport(datagram[[elem]], datagram[[elem2]])
      cat( names(datagram)[elem], "   ", names(datagram)[elem2], "         Rapport:", r, "\n")
    }
  }
}


resultat(quanti, quali, mais)


#Exercice 10
contPGe = table ( mais$Germination.epi , mais$Parcelle )

#Exercice 11
mosaicplot(contPGe, color = c( "darkgreen", "goldenrod","lightblue", "darkred"))
barplot(contPGe)

#Exercice 12
summary(contPGe)

#Exercice 13
X2max = function(countPGE){
  a = dim(countPGE)
  return (sum(countPGE) * min(a[1]-1, a[2]-1))
}

X2obs = function(countPGE){
  summary(countPGE)$statistic
  
}

Vcram = function(countPGE){
  x2max = X2max(countPGE)
  x2obs = X2obs(countPGE)
  return (sqrt((x2obs/x2max)))
}

Vcram(contPGe)

#Exercice 14
systema = function(quali, datagram){
  for (elem in quali) {
    for (elem2 in quali) {
      valid_idx = !is.na(datagram[[elem]]) & !is.nan(datagram[[elem]]) & 
        !is.na(datagram[[elem2]]) & !is.nan(datagram[[elem2]])
      
      valid_data = datagram[valid_idx, c(elem, elem2)]
      
      try_table <- table(valid_data[[1]], valid_data[[2]])
      
      r =  Vcram(try_table)
      if (r != 1){
      cat( names(datagram)[elem], "   ", names(datagram)[elem2], "         Vcram:", r, "\n")}
    }
  }
}

systema(quali, mais)

#Exercice 15
plot(mais$Masse.grains, mais$Nb.grains, col="purple", pch = 19)

#Exercice 16
cor(mais$Masse.grains,  mais$Nb.grains, use = "na.or.complete", method = "pearson")
cor(mais$Masse.grains,  mais$Nb.grains, use = "na.or.complete", method = "spearman")

#Exercice 17
pearspear = function (quanti, datagram){
  for (elem in quanti) {
    for (elem2 in quanti) {
      if (elem!=elem2){
      pear = cor(datagram[elem], datagram[elem2], use = "na.or.complete", method = "pearson")
      spear = cor(datagram[elem], datagram[elem2], use = "na.or.complete", method = "spearman")
      cat( names(datagram)[elem], "   ", names(datagram)[elem2], "         pearson:", pear, "           spearman : ", spear, "\n")}
      
    }
    }
}
pearspear(quanti, mais)

#Exercice 18
gigafonction = function(datagram, quanti, quali){
  resultat(quanti, quali, datagram)
  systema(quali, datagram)
  pearspear(quanti, datagram)
}

gigafonction(mais, quanti, quali)

#Exercice 19
