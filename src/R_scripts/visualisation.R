setwd("E:\\Courses\\Udemy data science\\Test files")


#loading the libraries required
library(readxl)
library(ggplot2)
library(plotly)


#Importing data from excel sheet
radiator <- read_excel("radiation_data.xlsx")

#Using apply function 
apply(radiator,2,mean)
apply(radiator,2,min)
apply(radiator,2,max)

#Visualization of radiation sources

#Point source
plot_ly(data=radiator,title = 'Point Source',x=~x, y=~y, z=~z, type="scatter3d", 
        mode="markers", color=~Point) %>% layout(title="Point Source")

#1D source
plot_ly(data=radiator,x=~x, y=~y, z=~z, type="scatter3d", 
        mode="markers", color=radiator$`1d`)%>% layout(title="1D Source")

#2D Source
plot_ly(data=radiator,x=~x, y=~y, z=~z, type="scatter3d", 
        mode="markers", color=radiator$`2d`)%>% layout(title="2D Source")

#3D Source
plot_ly(data=radiator,x=~x, y=~y, z=~z, type="scatter3d", 
        mode="markers", color=radiator$`3d`)%>% layout(title="3D Source")

