function [s, qi] = metodo_potencia(A,q0, k, tol)
    %{
        Función que utiliza el método de la potencia para regresar el
        eigenvalor dominante de la matriz
  
        IN: 
            A - matriz de la que un eigenvalor
            q0 - el vector en el que iniciamos el proceso
                 elemento del eigenspacio
            k   - maximo de iteraciones por si el metodo no converge
            tol - porcentaje maximo de error relativo permitido en cada
                  entrada del eigenvector dominante
        OUT:
            sigmai - el eigenvalor dominante de A
            qi     - un eigenvector normalizado en norma infinito asociado
                     al eigenvalor dominante
        
        %Limitaciones del metodo:
            %no converge si el eigenspacio al que pertenece el vector inicial 
            no tiene eigenvalor dominante. También puede
            no converger si no es elemento de un eigenspacio, aunque hay
            veces en que esta condicion no detiene al método, y la más
            problemática es la de que la matriz no tenga eigenvalor
            dominante.
    %}
    %inicializamos variables

    qi = q0./norm(q0, "inf");
    for i = 1:k
        %guardamos qi en q0 para la condicion de parada
        q0 = qi;
        
        qi = A*q0;
        s = norm(qi, "inf");
        
        %esto es para detectar eigenvalores negativos
        %manejamos nuestros eigenvectores con la mayor cantidad 
        %de entradas máximas positivas, y si esto si invierte, el
        %eigenvalor es negativo
        if( sum( qi == -s) > sum(qi == s))
           s = -s;
        end
        
        %normalizamos el vector
        qi = qi./s;
        
        
        %condicion de parada relativa
        %{
        
        Para la condicion de parada, lo que hicimos fue guardar los vectores
        de las últimas dos iteraciones. El método converge cuando estos son
        iguales, o muy próximos con cierta tolerancia, pues si el penúltimo
        fuera eigenvector, tendríamos que s_(k+1) q_(k+1)= Aq_k, ambos 
        normalizados en norma infinito.  Para verificar la cercanía, 
        tomamos la norma infinito del vector de errore relativos y si es menor a la 
        tolerancia, entonces el método ha convergido. 

        %}
        if( norm( ((q0-qi)./qi).*100 , "inf") <= tol )
            break
        end 
       
    end

end