% function terrainPlane()
    N = 30;
    x = linspace(-1.6,1.6,N);
    y = linspace(-1.6,1.6,N);
    z = ones(N,N)*(-0.5);
%     colormap gray

    c=zeros(size(z));%���o���С��x��ͬ

    for i=1:1:length(c(1,:))
        for j=1:1:length(c(:,1))
            c(i,j,1)=0.5412;
            c(i,j,2)=0.5412;
            c(i,j,3)=0.5412;%��ɫ
        end
    end

    surf(x,y,z,c)
% end