format long
clc; clear; close all;

%ejercicio 5
disp("ejercicio 5")
A = gallery('lehmer', 25);
[l1, V1, itT1] = MQR_simple(A, 1000, 1e-10);
[l2, V2, itT2] = MQR_dynamic(A, 20, 1e-10);
[V3, l3] = eigs(A, 25);

%este for lo usamos para asegurarnos de que los eigenvectores tengan las
%mismas entradas positivas
for i = 1:25
    if( max( abs(V1(:, i))) ~= max( V1(:, i) ))
        V1(:,i) = -V1(:,i);
    end
    if( max( abs(V2(:, i))) ~= max( V2(:, i) ) )
        V2(:,i) = -V2(:,i);
    end
    if( max( abs(V3(:, i))) ~= max( V3(:, i) ))
        V3(:,i) = -V3(:,i);
    end
end
l3 = diag(l3);
l1
l2
l3

%esvalores es el vector de los errores relativos de QR simple
%esvect es el vector de los error relativo maximo de cada eigenvector
esvalores = (l1-l3)./l3*100;
esvaloresAbs = (l1-l3);
esvect = zeros(25,1);
for i = 1:25
   esvect(i) = norm( (V1(:, i) - V3(:, i))./V3(:, i)*100, "inf"); 
end
esvect

%edvalores y edvect funcionan igual que antes, pero para QR dinamico
edvalores = (l1-l2)./l2*100;
edvaloresAbs = (l2-l3);
edvect = zeros(25, 1);
for i = 1:25
   edvect(i) = norm((V2(:, i) - V3(:, i))./V3(:, i)*100, "inf"); 
end
edvect

itT1
itT2

%esta es para comparar el eigenvector donde peor coincidencia hubo
v1 = V1(:, 25); v2 = V2(:, 25); v3 = V3(:,25);
e1 = (v1-v3)./v3.*100
e2 = (v1-v2)./v2.*100