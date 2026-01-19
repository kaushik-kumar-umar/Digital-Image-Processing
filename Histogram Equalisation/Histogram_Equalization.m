%date - 19/01/2026 
%created by - Kaushik Kumar Umar

clc;
clear all;
close all;

%load the image
image_matrix = imread('input.jpg');
%display(image_matrix);
imshow(image_matrix);
title('Original Image also Grayscale Image');

figure;

%matlab command to get histogram Equalized image
Ieq=histeq(image_matrix);
imshow(Ieq);
title('Equalized image using matlab histeq command');

figure;


%{
%testing the equalisation code with pre loaded image data
image_matrix = [52	55	61	59	79	61	76	61
62	59	55	104	94	85	59	71
63	65	66	113	144	104	63	72
64	70	70	126	154	109	71	69
67	73	68	106	122	88	68	68
68	79	60	70	77	66	58	75
69	85	64	58	55	61	65	83
70	87	69	68	65	73	78	90];

count_matrix = [
52 1;
55 3;
58 2;
59 3;
60 1;
61 4;
62 1;
63 2;
64 2;
65 3;
66 2;
67 1;
68 5;
69 3;
70 4;
71 2;
72 1;
73 2;
75 1;
76 1;
77 1;
78 1;
79 2;
83 1;
85 2;
87 1;
88 1;
90 1;
94 1;
104 2;
106 1;
109 1;
113 1;
122 1;
126 1;
144 1;
154 1
];

%}

%calculating the Equalized Image

%forming unique elements matrix
[m,n] = size(image_matrix);

count_matrix_initial = []; 

for ii = 1:m
    for jj = 1:n
        
        val = image_matrix(ii,jj);
        found = 0;   % reset for each value
        
        [x,~] = size(count_matrix_initial);
        
        for kk = 1:x
            if val == count_matrix_initial(kk,1)
                found = 1;
                break;
            end
        end
        
        if found == 0
            count_matrix_initial(x+1,1) = val;
        end
        
    end
end

%arrange the count_matrix in ascending order
[x,~]=size(count_matrix_initial);
count_matrix = count_matrix_initial;
for ii=1:x-1
    for jj=1:x-ii
        if(count_matrix(jj+1,1)<=count_matrix(jj,1))
            temp = count_matrix(jj,1);
            count_matrix(jj,1) = count_matrix(jj+1,1);
            count_matrix(jj+1,1) = temp;
        end
    end
end


%disp(count_matrix);

%add the count of unique variables
[m,n]=size(image_matrix);
[x,~]=size(count_matrix);
count_matrix(:,2) = 0;
for kk=1:x
    val=count_matrix(kk,1);
for ii=1:m
    for jj=1:n
        if(val == image_matrix(ii,jj))
            count_matrix(kk,2) = count_matrix(kk,2)+1;
        end
    end
end
end

%making the cdf matrix
matrix_cdf = zeros(x,1);
value=0;
for ii=1:x
    value=value+count_matrix(ii,2);
    matrix_cdf(ii,1)=value;
end

%making the histogram equivalent value matrix
hist_val = zeros(x,1);
cdf_min = min(matrix_cdf);
n=size(image_matrix);
for ii = 1:x
    hist_val(ii) = round(((matrix_cdf(ii,1) - cdf_min) / ((n(1)*n(2)) - cdf_min)) * (256 - 1));
end
[m,n] = size(image_matrix);
histeq_mat = zeros(m,n);

for ii = 1:m
    for jj = 1:n
        
        old_val = image_matrix(ii,jj);
        
        % find matching value in count_matrix and replace with hist_val
        for kk = 1:x
            if old_val == count_matrix(kk,1)
                histeq_mat(ii,jj) = hist_val(kk);
                break;
            end
        end
        
    end
end

%disp(histeq_mat);

histeq_mat = uint8(histeq_mat);
imshow(histeq_mat);
title('Equalized image using made functions');