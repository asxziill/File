//01���� 
//�ܿռ�V
//����Ʒ������v,��ֵw��
void DP(std::pair<int, int> obj){
    auto [v, w]=obj;
    for (int x=V; x>=v; x--){
        //��dp[x]��dp[x-v]ת����
        dp[x]=f(dp[x], dp[x-v], w);
    }
}

//��ȫ����
//�ܿռ�V
//����Ʒ������v,��ֵw��
void DP(std::pair<int, int> obj){
    auto [v, w]=obj;
    for (int x=v; x<=V; x--){
        //��dp[x]��dp[x-v]ת������dp[x-v]���Ѵ��������Ʒ
        dp[x]=f(dp[x], dp[x-v], w);
    }
} 

//���ر��� 
//�ܿռ�V
//����Ʒ������v,��ֵw, ����cnt��
void DP(std::tuple<int, int, int> obj){
    auto [v, w, cnt]=obj;
    int k=1;
    while (k<cnt){
        int x=v*k;
        //��ÿ����01����
        for (int vi=V; vi>=x; vi--){
            dp[vi]=f(dp[vi], dp[vi-x], w);
        }
        cnt-=k;
        k*=2;
    }
    int x=v*cnt;
    for (int vi=V; vi>=x; vi--){
        dp[vi]=f(dp[vi], dp[vi-x], w);
    }
}

//���鱳��
//�ܿռ�V
//������ÿ����Ʒ������v,��ֵw
void DP(std::vector<std::pair<int, int>> obj){
    //�Ӹ���Ϊһ������
    for (int vi=V; vi>=0; vi--){
        //һ���ռ�viֻ��ѡ����һ����Ʒת����
        for (auto [v, w]:obj){
            if (vi>=v){
                dp[vi]=f(dp[vi], dp[vi-v], w);
            }
        }
    }
} 
