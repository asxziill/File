inline T RE(void){
	char c=getchar();
	T x=0;
	T f=1;
	for (; c<'0'||c>'9'; c=getchar()){
		if (c=='-') f=-1;
	}
	for (; c>='0'&&c<='9'; c=getchar()){
		x = (x<<3)+(x<<1)+(c^48);
	}
	return x*f;
}

inline void OUT(T x){
	if (x<0){
		putchar('-');
		x=-x;
	}
	if (x>9) OUT(x/10);
	putchar(x%10+'0');
}
