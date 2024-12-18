```
# 使用 Ubuntu 作为基础镜像
FROM ubuntu:20.04

# 安装必要的工具
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    curl git vim build-essential \
    python3 python3-pip iputils-ping net-tools traceroute \
    && rm -rf /var/lib/apt/lists/*

# 安装 Go
RUN curl -LO https://go.dev/dl/go1.23.4.linux-amd64.tar.gz && \
    tar -C /usr/local -xzf go1.23.4.linux-amd64.tar.gz && \
    rm go1.23.4.linux-amd64.tar.gz

# 设置 Go 环境变量
ENV PATH="/usr/local/go/bin:${PATH}" \
    GO111MODULE=on \
    CGO_ENABLED=0 \
    GOOS=linux \
    GOARCH=amd64 \
    GOPROXY="https://goproxy.cn,direct"

# 创建工作目录
WORKDIR /go/src/app

# 将当前目录的内容复制到容器中
COPY . .

# 安装常用的 Go 第三方库
RUN go mod init myapp && \
    go get -u github.com/gin-gonic/gin && \
    go get -u github.com/jinzhu/gorm && \
    go get -u github.com/go-redis/redis/v8 && \
    go get -u github.com/stretchr/testify && \
    go get -u github.com/sirupsen/logrus && \
    go get -u go.uber.org/zap

# 暴露开发端口（例如，8080）
EXPOSE 8080

# 启动一个 shell，方便 IDE 连接
CMD ["bash"]

# 构建命令
# docker build --no-cache -t go-dev-version1 . 
# 启动命令
# docker run -it --rm -v D:\DockerTest:/go/src/app -p 8080:8080 [名字]
# docker run -it --rm -v D:\DockerTest\GO_Dev:/go/src/app -p 8080:8080 go-dev-version1
```
