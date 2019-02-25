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

xcol=[22     
2
36
20
4
46
20
38
45
44
49
3
15
48
22
16
27
50
25
7
31
5
0
44
39
48
14
45
34
18
37
28
19
38
49
40
0
3
26
48
32
11
17
4
13
22
8
27
6
22];
ycol=[31
50
30
41
37
38
46
0
17
1
15
10
43
21
35
46
10
37
32
43
4
23
38
6
5
29
33
5
11
20
1
4
16
48
18
21
40
15
43
34
14
26
48
20
24
30
37
44
36
31];  
 zcol=[46
20
8
23
18
43
5
43
42
48
26
22
17
43
19
3
24
46
35
25
5
3
33
12
43
15
26
44
44
6
16
14
21
14
1
1
1
16
37
23
17
16
11
3
43
22
17
46
33
46];


 %radius calculated from forward boltzmann transport equation 

rdd=[59.76143047 
59.76143047 
54.23261445
 47.67312946 
51.2989176 
 41.16934848
 74.53559925 
50.63696835 
57.73502692
 63.2455532 
 64.54972244 
57.73502692
 24.32521277 
48.79500365 
67.41998625 
45.64354646 
48.79500365 
37.52933125
 76.69649888 
53.45224838 
50 
31.6227766  
23.70227316 
50.63696835
46.1265604  
58.72202195 
57.73502692 
44.28074428 
63.2455532  
56.79618342
27.52409413 
40.16096645 
31.6227766  
32.44428423 
63.2455532  
51.98752449
45.17539515 
40.16096645 
22.14037214
62.01736729 
63.2455532  
38.92494721
32.44428423 
51.98752449 
20.62842493 
50.63696835 
43.03314829 
41.52273993
 69.00655593
 49.38647983];



sphere3d(xcol,ycol,zcol,rdd,[],0.1)

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

x=x(:);

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