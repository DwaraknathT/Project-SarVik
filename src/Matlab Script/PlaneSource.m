syms t x y z 
m=csvread('dosedata.csv');
%dose=csvread('r.csv');
xi=m(:,1);
yi=m(:,2);
zi=m(:,3);
pointA = [0.1,0,1];
pointB=[.125,0,1];
pointC = [0.15,0,1];
%pointC = [10,20,10];
%points=[pointA' pointB' pointC'];
%dose=m(:,4);
%p=dose*(k.^4)-(k.^2)+(1-zi).^2+(1-zi)-1
%fsurf(p);
%zi=double(zi);
%
x2=0*t+0.10;y2=0*t;z2=t;
x3=0*t+0.15;y3=0*t;z3=t;
fplot3(x2,y2,z2,[0,1],'y','Linewidth',2);
%p1=[0.1 0 1];p2=[.125 0 1];p3=[.15 0 1];
plot3(xi,yi,zi,'*r','MarkerSize',2);
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
r1=sqrt((xi).^2 + yi.^2);
r2=sqrt((xi-0.05).^2 + (yi).^2); % this selection of radius is due to the distrubution of values in the csv file 
r3=sqrt((xi-0.10).^2 + yi.^2);
r4=sqrt((xi-0.15).^2 + (yi).^2);
%plot_line(p1,p2,p3);
%p=(1/r).*atand(1/r)
%{
x1=0*t;y1=0*t;z1=t;
x2=0*t+0.05;y2=0*t+0.05;z2=t;
x3=0*t;y3=0*t+0.05;z3=t;
x4=0*t+0.05;y4=0*t;z4=t;
%}
%now that we know our plane is between x=0.1 and x=0.15
% for loop to build the plane
for k =0:15
    xii=0*t+k/100;
    yii=0*t;
    zii=t;
  fplot3(xii,yii,zii,[0,1],'g','Linewidth',12)
end
%fplot3(x,y,z,[0 1],'g','Linewidth',15)
%fplot3(x2,y2,z2,[0 1],'y','Linewidth',10)
%fplot3(x1,y1,z1,[0 1],'y','Linewidth',10)
%fplot3(x3,y3,z3,[0 1],'g','Linewidth',10)

% the above is to confirm the plane obtained( the end line of the plane
% which bounds it)

%k=sqrt(dose./111)
%r=sqrt((x))
%tan(dose/111));
%fill3(points(1,:),points(2,:),points(3,:),'r');

%parpool(4)
%spmd

for i=1:600  
    [X1,Y1,Z1]=cylinder2P(r1(i),10,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    [X2,Y2,Z2]=cylinder2P(r2(i),10,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    [X3,Y3,Z3]=cylinder2P(r3(i),10,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    [X4,Y4,Z4]=cylinder2P(r4(i),10,[xi(i),yi(i),0],[xi(i),yi(i),1]);
    surf(X1,Y1,Z1)
    surf(X2,Y2,Z2)
    surf(X3,Y3,Z3)
    surf(X4,Y4,Z4)
    
     % using the data given in the question
    %points(1,:),points(2,:),points(3,:),'g')
    fplot3(x4,y4,z4,[0,1],'y','Linewidth',5);
    fplot3(x3,y3,z3,[0,1],'y','Linewidth',5);
alpha 0.2
end
%end
%}
hold off
axis auto
toc
