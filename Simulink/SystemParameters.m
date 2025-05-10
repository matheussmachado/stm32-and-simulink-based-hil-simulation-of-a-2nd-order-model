% SECOND ORDER BUTTERWORTH ANALOG FILTER SALLEN-KEY

%{
                      1/( R1*R2*C1*C2 )          
Gs =   -----------------------------------------------
        s^2 + [(1/R1) + (1/R2)]*s + 1/( R1*R2*C1*C2 )  
              -----------------
                      C1
%} 

% Analog Circuit Parameters
C1 = 200e-9;
C2 = 100e-9;
R1 = 2e6;
R2 = 1e6;

% 2nd Order Butterworth Transfer Function
num = 1/( R1*R2*C1*C2 );
den = [1, ( (1/R1) + (1/R2) ) / C1, 1/( R1*R2*C1*C2 )];                    
