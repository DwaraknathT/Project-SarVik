syms x y z t x1 y1 z1 x2 y2 z2 p
p=1;
m=csvread('dosedata.csv');
%dose=csvread('r.csv');
xi=m(:,1);
yi=m(:,2);
zi=m(:,3);
dose=m(:,4);
plot3(xi,yi,zi,'*r','MarkerSize',1);
axis([0 1 0 1 0 1]);
xlabel('x-axis');
ylabel('y-axis');
zlabel('z-axis');
grid on
hold on
% to plot the source
%x=0*t;
%y=0*t;
%z=t;
%fplot3x,y,z,[0 10],'g','LineWidth',5)
% to obtain distance (radius of every cylinder)
tic 
r1=sqrt((xi).^2 + yi.^2);  % each point will have a cylinder around it
% 4 sets will form a plane , 
% these 4 sets will form the sides of a cuboid 
r2=sqrt((xi-0.05).^2 + (yi-0.05).^2);
r3=sqrt((xi-0.05).^2 + yi.^2);
r4=sqrt((xi).^2 + (yi-0.05).^2);
x=t;
y=t;
z=t;
%{
x1=0*t;y1=0*t;z1=t;
x2=0*t+0.1;y2=0*t;z2=t;
x3=0*t+0.15;y3=0*t;z3=t;
x5=0*t;y5=0*t+0.025;z5=t;
x6=0*t+0.05;y6=0*t+0.025;z6=t;
x4=0*t+0.05;y4=0*t;z4=t;
%}
%z=1;
%zz=0;
%x=0;
% to check wether the cuboid obtained is right or not 
%line([0,0.05],[0,0],[z,z],'Linewidth',3)
%line([0,0],[0,0.05],[x,x],'Linewidth',2)
%line([0,0],[0,0.05],[z,z],'Linewidth',3)
%line([0,0],[0,0.05],[zz,zz],'Linewidth',3)
%line([0.05,0.05],[0,0.05],[z,z],'Linewidth',3)
%line([0,0.05],[0.05,0.05],[z,z],'Linewidth',3)
%line([0.05,0.05],[0,0.05],[zz,zz],'Linewidth',3)
%line([0,0.05],[0.05,0.05],[zz,zz],'Linewidth',3)
%fplot3(x1,y1,z1,[0,1],'b','Linewidth',13);
%fplot3(x2,y2,z2,[0,1],'b','Linewidth',2);
%fplot3(x3,y3,z3,[0,1],'y','Linewidth',2)
%fplot3(x3,y3,z3,[0,1],'b','Linewidth',13);
%fplot3(x4,y4,z4,[0,1],'b','Linewidth',13);
%fplot3(x5,y5,z5,[0,1],'b','Linewidth',13);
%k=sqrt(dose./111)
%r=sqrt((x))
%tan(dose/111));


%parpool(4)
%spmd

for i=1:1331  
    [X1,Y1,Z1]=cylinder2P(r1(i),9,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    [X2,Y2,Z2]=cylinder2P(r2(i),9,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    [X3,Y3,Z3]=cylinder2P(r3(i),9,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    [X4,Y4,Z4]=cylinder2P(r4(i),9,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    surf(X1,Y1,Z1)
    surf(X2,Y2,Z2)
    surf(X3,Y3,Z3)
    surf(X4,Y4,Z4)
     % using the data given in the question
    %points(1,:),points(2,:),points(3,:),'g')
     fplot3(x1,y1,z1,[0,1],'g','Linewidth',20);
     fplot3(x2,y2,z2,[0,1],'y','Linewidth',20);
     fplot3(x3,y3,z3,[0,1],'g','Linewidth',20);
     fplot3(x4,y4,z4,[0,1],'y','Linewidth',20);
alpha 0.09
end
hold off
axis auto
toc
%delete(gcp)
