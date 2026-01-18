%date - 19/01/2026 
%created by - Kaushik Kumar Umar

clc;
clear all;
close all;

%create a 8*8 random matrix
mat=randi([0 255],8,8);

%load the image
I = imread('input.jpg');
I = imrotate(I, 90);
imshow(I);
title('Original Image');

figure;

%convert coloured image to grayscale
Ig=rgb2gray(I);
imshow(Ig);
title('Grayscale Image');

figure;

%extraction of red image out of the coloured RGB image
Ired = I;
Ired(:,:,2)=0;
Ired(:,:,3)=0;
imshow(Ired);
title('Red extracted Image');

figure;

%creation of a logical matrix
aa=randi([0,10],4,4);
aa=aa>4;

%converting grayscale to black & white
Ibw = Ig;
Ibw_1=Ibw>100;
imshow(Ibw_1);
title('Black & White Image with threshold = 100');

%converting the logical data type to uint8 - typecasting
Ibw_1=uint8(Ibw);

figure;

Ibw_2=Ibw>80;
imshow(Ibw_2);
title('Black & White Image with threshold = 80');