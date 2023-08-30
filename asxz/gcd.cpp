int gcd(int a,int b)
{
    int az=__builtin_ctz(a),bz=__builtin_ctz(b);
    int z=std::min(az,bz);
    int dif;
    b>>=bz;
    while(a)
    {
        a>>=az;
        dif=b-a;
        az=__builtin_ctz(dif);
        if(a<b) b=a;
        if(dif<0) a=-dif;
        else a=dif;
    }
    return b<<z;
}
