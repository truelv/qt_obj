# qt_obj

# ProConfig
这个工程测试pro文件控制编译文件

# 添加指定目录操作
## 创建空本地仓库
git init 
## 以下在仓库里面操作
### 1、设置允许使用克隆子目录
git config core.sparsecheckout true
### 2、设置需要克隆的子目录，childfile是要克隆的目录
echo 'childfile*' >> .git/info/sparse-checkout
### 3、配置远程仓库
git remote add origin < giturl>
### 4、同步
git pull origin master
