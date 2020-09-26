format long
clc; clear; close all;

%ejercicio 1

A = [1, -2, 0; 
    1, 17, -2; 
    5, 7,   7]

%a)
q0 = [1,1,1]';
disp("el metodo arroja:")
[s, q] =metodo_potencia(A, q0, 10, 1e-14)

%b)
disp("los eigenpares de matlab:")
[V, D] = eig(A)
[d, indx] = max( diag(D) );
v = V(:, indx);
disp("comparacion entre los eigenvalores")
errorRelativo = abs(s-d)/d*100
errorAbsoluto = abs(s-d)


%c)
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
[~, qj] = metodo_potencia(A, q0, 10, 1e-14);
for j = 1:n
    [~,qj1] = metodo_potencia(A, q0, j+1, 1e-14);
    razones(j) = norm( qj1 - v, "inf")/norm(qj - v, "inf");
    qj = qj1;
end
razones
%d
razon = abs(D(2,2)/D(3,3))