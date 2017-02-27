clear all;
rng(12); %set seed for reproducable rand

%addition

a_A = round(sprandn(8,4,.25),4);
a_B = round(sprandn(8,4,.25),4);
a_C = a_A + a_B;
save_mp9mat(a_A,'input_mats/a_A.txt');
save_mp9mat(a_B,'input_mats/a_B.txt');
save_mp9mat(a_C,'output_mats/gold/a_C.txt');

%large sparse addition matrices

sa_A = round(sprandn(400,410,.0001),4);
sa_B = round(sprandn(400,410,.00005),4);
sa_C = sa_A + sa_B;
save_mp9mat(sa_A,'input_mats/sa_A.txt');
save_mp9mat(sa_B,'input_mats/sa_B.txt');
save_mp9mat(sa_C,'output_mats/gold/sa_C.txt');
 
% multiplication 

m_A = round(sprand(5,3,.5),4);
m_B = round(sprandn(3,6,.5),4);
m_C = m_A*m_B;

save_mp9mat(m_A,'input_mats/m_A.txt');
save_mp9mat(m_B,'input_mats/m_B.txt');
save_mp9mat(m_C,'output_mats/gold/m_C.txt');

% large sparse multiplication matrices

sm_A = round(sprand(900,320,.0001),4);
sm_B = round(sprandn(320,110,.001),4);
sm_C = sm_A*sm_B;

save_mp9mat(sm_A,'input_mats/sm_A.txt');
save_mp9mat(sm_B,'input_mats/sm_B.txt');
save_mp9mat(sm_C,'output_mats/gold/sm_C.txt');

%%
clear all;
rng(12);
filename = 'input_mats/scrambled_rows.txt';
A = round(sprandn(12,8,.25),4);
dlmwrite(filename,size(A),'delimiter',' ');
[i j a] = find(A);
b = [i j a];
b(randperm(size(i,1)),:);
dlmwrite(filename,[b(:,1)-1 b(:,2)-1 b(:,3)], '-append','delimiter',' ');


filename = 'input_mats/scrambled_rows2.txt';
A = round(sprandn(15,15,.099),4);
dlmwrite(filename,size(A),'delimiter',' ');
[i j a] = find(A);
b = [i j a];
b(randperm(size(i,1)),:);
dlmwrite(filename,[b(:,1)-1 b(:,2)-1 b(:,3)], '-append','delimiter',' ');




