M = readmatrix('rotmats_matlab.dat');
n = floor(size(M,1)/3);
res = [];
for j = 1:n
  A = zeros(3, 3);
  A = [
    M((j-1)*3+1,:);
    M((j-1)*3+2,:);
    M((j-1)*3+3,:)
  ];
res = [res; inv(A)];
end

res