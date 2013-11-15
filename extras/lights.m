function [ minHeight ] = lights( lightData, L, R )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

N = size( lightData, 1);

lineVec = double(zeros(2*N, 4));

lineCount = 1;

for i=1:N
    angle = (lightData( i, 3) * pi) / 180.0;
    lineVec( lineCount, 3) = lightData(i, 1);
    lineVec( lineCount, 4) = lightData(i, 2);
    lineVec( lineCount, 1) = tan( pi/2.0 - angle);
    lineVec( lineCount, 2) = -1.0*(lineVec( lineCount, 1)*lineVec( lineCount, 3)) + lineVec( lineCount, 4);
    
    lineCount  = lineCount + 1;
    
    lineVec( lineCount, 3) = lightData(i, 1);
    lineVec( lineCount, 4) = lightData(i, 2);
    lineVec( lineCount, 1) = tan( pi/2.0 + angle);
    lineVec( lineCount, 2) = -1.0*(lineVec( lineCount, 1)*lineVec( lineCount, 3)) + lineVec( lineCount, 4);
    
    lineCount = lineCount + 1;   
end

lineCount = lineCount - 1;

minHeight = 1000;
minX = 0;

figure(1), hold on;

for i=1:lineCount
    for j=i+1:lineCount
        drawLine( 1, lineVec(i, :));
        drawLine( 1, lineVec(j, :));
        
        if( abs( lineVec(i, 1) - lineVec(j, 1)) > 0.001)
            X = (lineVec( j, 2) - lineVec( i, 2)) / (lineVec( i, 1) - lineVec( j, 1));
            Y = (lineVec(j, 1)*lineVec(i,2) - lineVec(i, 1)*lineVec(j, 2)) / (lineVec( j, 1) - lineVec( i, 1));
            
            
            if( X >=L && X <=R && Y > 0 && Y < minHeight)
                minHeight = Y;
                minX = X;                
            end
        end        
    end
end
figure(1), plot( minX, minHeight, 'bo');
figure(1), line( [L R], [minHeight minHeight], 'Color','r','LineWidth',4);
return
end

function [] = drawLine( figureNo, lineVec)

xVec = zeros(1, 2);
yVec = zeros(1, 2);

xVec(1) = lineVec(3);
xVec(2) = -1.0*lineVec(2)/lineVec(1);

yVec(1) = lineVec(4);
yVec(2) = 0;

figure( figureNo), line(xVec, yVec);
end