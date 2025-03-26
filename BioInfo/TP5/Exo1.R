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
