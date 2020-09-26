function [s, q1] = metodo_potencia_inv(A, x0, rho, k, tol)
    %{
        Función que utiliza el método de la potencia para regresar el
        eigenpar con eigenvalor mas cercano al valor rho de la matriz A
    
        IN: 
            A - matriz de la que queremos el eigenpar
            x0 - el vector en el que iniciamos el proceso
                 distinto del vector cero
            rho - el shift que aplicamos
            k   - el maximo de iteraciones
            tol -   tolerancia absoluta 
        OUT:
            lambda - el eigenvalr de A
            v     - un eigenvector asociado al eigenvalor lambda
        
      Limitaciones del método:
            Las mismas que el método de la potencia. No hay problema con
            que la matriz sea singular porque en tal caso ya encontramos el
            eigenpar. Aunque puede ser problemático si tenemos el
            eigenvalor, pero no el eigenvector. Para esto podemos recurrir
            a un shift muy cercano al eigenvalor.
            
           Naturalmente, sería un problema si nuestro shift justo nos deja
           entre dos eigenvalores, en cuyo caso no hay eigenvalor dominante
   
   
    %}
    
    n = length(A);
    
    %iniciamos con el vector inicial normalizado en norma infinito
    q1 = x0./norm(x0, "inf");
    
    for i = 1:k
        q0 = q1;
        %si su condicion es infinito, entonces ya convergió al eigenvalor
        %no tiene inversa y no podríamos aplicar el paso
        %en este caso rho es el eigenvalor y ya no modificamos q1
        if( rcond(A - rho.*eye(n)) == 0)
            s = rho;
            q1 = q0;
        else
            %si no, aplicamos la iteracion del metodo de la potencia
            %y guardamos la aproximacion del eigenvalor
            q1 = ( A-rho.*eye(n) ) \q0;
            s = norm(q1, "inf");
            
            %al igual que en el método de la potencia, esta parte se usa 
            % para detectar eigenvalores negativos, pues manejamos 
            % eigenvectores con la mayor cantidad de entradas máximas positivas 
            if( sum( q1 == -s) > sum(q1 == s))
                s = -s;
            end
            
            %normalizamos el vector
            q1 = q1./s;
        end 
        
        %misma condición de parada que en el método de la potencia
        if( norm( ((q0-q1)./q1).*100 , "inf") <= tol )
            break
        end 
            
    end
    % s es ahora el eigenvalor de inv(A-rho*I)
    % asi que lo traducimos al eigenvalor de A
     s = 1/s + rho;
end
