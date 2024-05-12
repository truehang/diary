# 安装软件包失败总结

## 安装包找不到

- 问题：
  
  apt install 时提示：E: 软件包 libwebkit2gtk-4.0-37 没有可安装候选。

- 解决办法：
  
  需要把包含有相应软件包的apt服务器更新到本地的搜索范围。到[packages.ubuntu.com](https://packages.ubuntu.com/) 或 [debian.org/distrib/packages](https://www.debian.org/distrib/packages)查找该软件包
  
  比如在packages.ubuntu.com 找到libwebkit2gtk-4.0-37的包服务器，则更新到/etc/apt/sources.list中：

```bash
echo "deb http://kr.archive.ubuntu.com/ubuntu mantic-updates main" |sudo tee -a /etc/apt/sources.list
sudo apt update
```

之后安装就找得到了。

同理对于

E: 软件包 libicu72 没有可安装候选

也找到apt服务器为ftp.cn.debian.org/debian。

```bash
echo "deb http://ftp.cn.debian.org/debian bookworm main"|sudo tee -a /etc/apt/sources.list
```

## 安装包因为依赖库没有安装而失败

- 问题：
  
  下列软件包有未满足的依赖关系：
   libwebkit2gtk-4.0-37 : 依赖: libjavascriptcoregtk-4.0-18 (= 2.44.0-0ubuntu0.23.10.1) 但是它将不会被安装
  
                          依赖: libicu72 (>= 72.1~rc-1~) 但无法安装它
  
  E: 无法修正错误，因为您要求某些软件包保持现状，就是它们破坏了软件包间的依赖关系。

  根据报错的提示我们知道 需先安装依赖库：libicu72和libjavascriptcoregtk-4.0-18

  在安装libjavascriptcoregtk-4.0-18时继续报错：

  下列软件包有未满足的依赖关系：
   libjavascriptcoregtk-4.0-18 : 依赖: libicu72 (>= 72.1~rc-1~) 但无法安装它
  E: 无法修正错误，因为您要求某些软件包保持现状，就是它们破坏了软件包间的依赖关系。

- 解决办法：
  
  按照顺序安装就可以。从上面我们可以知道安装顺序是libicu72 -> libjavascriptcoregtk-4.0-18 -> libwebkit2gtk-4.0-37

## 提示没有apt服务器公匙

- 问题：
  
  在apt update时
  
  错误:5 http://mirrors.ustc.edu.cn/debian bookworm InRelease  
  由于没有公钥，无法验证下列签名： NO_PUBKEY 0E98404D386FA1D9 NO_PUBKEY 6ED0E7B82643E131 NO_PUBKEY F8D2585B8783D481

- 解决办法：
  
  从服务器下载并添加缺少的公匙

```bash
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 0E98404D386FA1D9 6ED0E7B82643E131 F8D2585B8783D481
sudo apt update
```
