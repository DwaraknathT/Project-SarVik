syms x y z t x1 y1 z1
m=csvread('dosedata.csv');
%dose=csvread('r.csv');
xi=m(:,1);
yi=m(:,2);
zi=m(:,3);
dose1=m(:,4);
dose2=m(:,5);
plot3(xi,yi,zi,'*r','MarkerSize',3);
axis([0 1 0 1 0 1]);
xlabel('x-axis');
ylabel('y-axis');
zlabel('z-axis');
grid on
hold on
% to plot the source once it has been computed 
%x1=0*t+0.1;
%y1=0*t;
%z1=t;
fplot3(x1,y1,z1,[0,1],'g','Linewidth',5);
% to obtain distance (radius of every cylinder)
tic 
r1=sqrt((xi-0.1).^2 + yi.^2);

%replace the above radius of the cylinders with 
%r2=(xi-0.15).^2+yi.^2
% to find the line source for the second set of dosage values
x=t;
y=t;
z=t;
%parpool(4)
%spmd
for i=1:1331
    [X1,Y1,Z1]=cylinder2P(r1(i),9,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    surf(X1,Y1,Z1)
   %  fplot3(x1,y1,z1,[0,1],'g','Linewidth',5); % run this to plot the line
alpha 0.09
end
%end
hold off
axis auto
toc
%delete(gcp)
