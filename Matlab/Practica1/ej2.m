format long
clc; clear; close all;

A = [1, -2, 0; 
    1, 17, -2; 
    5, 7,   7]

%a)
q0 = [1,1,1]';
rho = 0
[s, q] =metodo_potencia_inv(A, q0, rho, 10, 1e-14);

%b)
[V, D] = eig(A)
[d, indx] = min( diag(D) );
v = V(:, indx);
disp("comparacion entre los eigenvalores")
s
d
errorRelativo = abs(s-d)/d*100
errorAbsoluto = abs(s-d)


%c)
disp("comparacion de eigenvectores")
q
v = v./norm(v, "inf");
%tambien lo ponemos como nuestro vector, con la mayor cantidad de entradas
%maximas positivas
if( sum(v == 1) < sum(v == -1) )
    v = -v;
end
v
erroresRelativos =abs(v - q)./abs(v)
erroresAbsolutos = abs(v-q)

%calculo de razones para j = 1:n
n = 10;
razones = zeros(n, 1); 
[~, qj] = metodo_potencia_inv(A, q0, rho, 1, 1e-14);
for j = 1:n
    [~,qj1] = metodo_potencia_inv(A, q0, rho, j+1, 1e-14);
    razones(j) = norm( qj1 - v, "inf")/norm(qj - v, "inf");
    qj = qj1;
end
razones
%d
razon = abs(D(1,1)/D(2,2))

%ahora usando rho = 8.5
rho = 8.5
[s, q] =metodo_potencia_inv(A, q0, rho, 10, 1e-14);

%b)
d = D(2,2)
indx = 2
v = V(:, indx);
disp("comparacion entre los eigenvalores")
s
d
errorRelativo = abs(s-d)/d*100
errorAbsoluto = abs(s-d)


%c)
disp("comparacion de eigenvectores")
q
v = v./norm(v, "inf");
%tambien lo ponemos como nuestro vector, con la mayor cantidad de entradas
%maximas positivas
if( sum(v == 1) < sum(v == -1) )
    v = -v;
end
v
erroresRelativos =abs(v - q)./abs(v)
erroresAbsolutos = abs(v-q)

%calculo de razones para j = 1:n
n = 10;
razones = zeros(n, 1); 
errores = zeros(n+1,1);


[~, qj] = metodo_potencia_inv(A, q0, rho, 1, 1e-14);
errores(1) = norm(qj - v, "inf");
for j = 1:n
    [~,qj1] = metodo_potencia_inv(A, q0, rho, j+1, 1e-14);
    errores(j+1) = norm(qj1 - v, "inf");
    razones(j) = errores(j+1)/errores(j);
    qj = qj1;
end
errores
razones


%d
d = mink(abs(diag(D) - 8.5), 2);
razon = d(1)/d(2)