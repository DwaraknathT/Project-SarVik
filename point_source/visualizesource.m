%sphere3d  A simple 3D-bubbleplot.
%     sphere3d() is a three-dimensional bubbleplot.
%   
%     sphere3d(x,y,z,r), where x, y, z and r are four vectors of the 
%     same length, plots bubbles of radii r in 3-space with centers at
%     the points whose coordinates are the elements of x, y and z. If r 
%     is a matrix of size numel(x)x3, sphere3d produces ellipsoids with
%     centers x(i),y(i),z(i) and radii r(i,1), r(i,2) and r(i,3).
% 
%     sphere3d(x,y,z,r,c), where c is a rgb-triplet array (in [0,1])
%     with numel(x) rows, plots bubbles with colours specified by c.
% 
%     sphere3d(x,y,z,r,c,Alpha), where Alpha is a scalar with value from 
%     0.0 to 1.0, plots bubbles with FaceAlpha Alpha.
% 
%     sphere3d(x,y,z,r,c,Alpha,n,m), where m and n are scalar values that
%     decides the size of the arrays used to render the bubbles. 
%     The largest radius in the set is rendered with (n+1)x(n+1) points.
%     To increase efficiency, the number of rendering points used is 
%     decreasing linearly with the radius but is never rendered with 
%     fewer points than (m+1)x(m+1). 
%     
%     sphere3d(x,y,z,r,c,Alpha,n,m,'PropertyName',PropertyValue,...)
%     Any property-value pair setting valid for a SURFACE object can be
%     passed as optional parameters.
%   
%     sphere3d returns a column vector of handles to surface objects.
%

%randomly generated dataset of 50 points in space
m=csvread('dose.csv');
x=csvread('coord.csv');
x1=x(:,1);
y1=x(:,2);
z1=x(:,3);

%y=csvread('coord.csv',0,1);y=y.';
%z=csvread('coord.csv',0,2);z=z.';
sphere3d(x1,y1,z1,m,[],0.01)
%plot(plot::Spherical([1, u, v], u = 0..2*PI, v = 0..PI))

% the last parameter is to make the sphere transparent.


%   shading interp; camlight right; lighting phong; view(60,30);
%   
%   See also scatter3 surface surf plot3 scatter 
function handles = sphere3d(x,y,z,r,varargin)
msgstruct = nargchk(0,1,nargout,'struct');
error(msgstruct);
if nargin > 8 
    [xargs{1:nargin-8}]=varargin{5:end};
else
    xargs={};
end
if nargin <8 || isempty(varargin{4}) || varargin{4}<7
    M=10;
else
    M=ceil(varargin{4});
end
if nargin <7 || isempty(varargin{3})
    N=20;
else
    N=floor(varargin{3}); 
end
% Use 3 (N+1)x(N+1) arrays to generate the sphere with the largest radii.
% There´s no need to render the smaller spheres/ellipsoids as detailed as
% the largest one, scale them linearly against R-max. Let the smallest N  be M 



N=ceil(r/norm(r,2)*N/(max(r/norm(r,2))+eps));
N(N<M)=M;
h=zeros(1,numel(x));

% Make sure that x is a column vector, makes it easier to check if the user
% supplied bubble or ellipsoid radiis for x,y,z
% hence the input in column vector fashion above. 
% You can also extract data from a csv file . 
%x=x';
%x=x(:);

% Set up equal axis, set DoubleBuffer on and add a grid
axis equal;set(gcf,'DoubleBuffer','on');grid on;
for k=1:numel(x)
    if size(r)==[numel(x)]
    [X{k},Y{k},Z{k}]=ellipsoid(x(k),y(k),z(k),r(k,1),r(k,2),r(k,3),N(k));
    else 
    [X{k},Y{k},Z{k}]=ellipsoid(x(k),y(k),z(k),r(k),r(k),r(k),N(k));
    end
    h(k)=surface(X{k},Y{k},Z{k},xargs{:});
end
% Set LineStyle to 'none'
[lstyle{1:numel(x),1}]=deal('none'); 
set(h,{'LineStyle'},lstyle); 
% If a color specification is available ...
if numel(varargin)>0 && ~isempty(varargin{1})
    try
        set(h,{'FaceColor'},mat2cell(varargin{1},ones(size(varargin{1},1),1),3));
    catch
        [errmsg,errid]=lasterr;
        error(errmsg);
    end
end
% If Alpha is specified ... 
if numel(varargin)>1 && ~isempty(varargin{2})
    [Alpha_{1:numel(x),1}]=deal(varargin{2});
    try
        set(h,{'FaceAlpha'},Alpha_);
    catch
        [errmsg,errid]=lasterr;
        error(errmsg);
    end
end 
view(3);
% outputs?
if nargout>0
    handles=h';
end
end
