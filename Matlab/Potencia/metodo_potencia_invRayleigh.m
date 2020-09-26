function [coefR, q1, it] = metodo_potencia_invRayleigh(A, x0, k)

    %{
        Función que utiliza el método de la potencia y la idea del shift 
        dinámico con el cociente de Rayleigh para regresar el
        eigenpar con eigenvector más próximo al vector inicial
    
        IN: 
            A - matriz de la que queremos el eigenpar
            x0 - el vector en el que iniciamos el proceso
                 distinto del vector cero
            k   - el maximo de iteraciones
        OUT:
            lambda - el eigenvalr de A
            v     - un eigenvector asociado al eigenvalor lambda
    %}
    
    %guardamos la dimension de A para no calcularla cada que hacemos un
    %shift
    n = length(A);
    tol = 1e-7;
    
    %iniciamos con el vector inicial normalizado
    q1 = x0./norm(x0);
    
    for i = 1:k  
        
        %calculamos el coeficiente de Rayleigh para usarlo como shift
        coefR = q1'*A*q1;
        
        %como en la potencia inversa, checamos que la matriz sea invertible
        if( rcond(A - coefR.*eye(n)) == 0)
            break
        else
            %si es invertible, aplicamos la iteracion del metodo de la
            %potencia y normalizamos el vector
            q1 = ( A-coefR.*eye(n) ) \q1;
            q1 = q1./norm(q1);
        end
        
       %aqui vemos si el metodo ya convergio
       %solo usamos <= tol en lugar del <=tol*norm(q1) porque q1 es unitario
        if( norm(A*q1 - coefR*q1) <= tol )
            break
        end 
            
    end
    
    %lo devolvemos con la mayor cantidad de entradas positivas
    if( sum(q1 > 0) < sum(q1<0) )
        q1 = -q1;
    end
    it = i;

end