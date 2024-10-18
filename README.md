# 文档生成

## 编译

使用容器:

```bash
docker build . -t doc:latest
docker run -u root --rm -it --network host -v $PWD:/home/user/ws doc:latest bash
# 在容器中
sphinx-autobuild source build/html
```

然后在 http://127.0.0.1:8000 看生成效果

## 维护

只需要在source文件夹下添加相应的文件夹，更新index.rst以及contents.rst（或者contents.md）文件，形成文件树即可。

## 托管

main分支的内容生成托管在([Welcome to First Doc’s documentation! &mdash; First Doc v1 文档](https://diary-from-hang.readthedocs.io/zh-cn/latest/))上。


