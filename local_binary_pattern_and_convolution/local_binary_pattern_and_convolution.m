clc;
clear;
close all;

% Read Image
img = imread('cameraman.tif');   % Built-in image
if size(img,3)==3
    img = rgb2gray(img);
end

img = double(img);
[m,n] = size(img);

lbp_img = zeros(m,n);

% LBP Calculation
for i = 2:m-1
    for j = 2:n-1
        center = img(i,j);
        binary = [ ...
            img(i-1,j-1)>=center, ...
            img(i-1,j)>=center, ...
            img(i-1,j+1)>=center, ...
            img(i,j+1)>=center, ...
            img(i+1,j+1)>=center, ...
            img(i+1,j)>=center, ...
            img(i+1,j-1)>=center, ...
            img(i,j-1)>=center ];

        weights = [1 2 4 8 16 32 64 128];
        lbp_img(i,j) = sum(binary .* weights);
    end
end

lbp_img = uint8(lbp_img);

% Display
figure
subplot(1,2,1), imshow(uint8(img)), title('Original Image')
subplot(1,2,2), imshow(lbp_img), title('LBP Image')

img = double(img);


% Example Kernel (Edge Detection)
kernel = [-1 -1 -1;
          -1  8 -1;
          -1 -1 -1];

conv_img = conv2(img, kernel, 'same');

figure
subplot(1,2,1), imshow(uint8(img)), title('Original Image')
subplot(1,2,2), imshow(uint8(conv_img)), title('Convolved Image')