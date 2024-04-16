# 文档生成

## 编译

使用容器:

```bash
docker build . -t doc:latest
docker run --rm -it --network host -v $PWD:/home/user/ws doc:latest bash
# 在容器中
sphinx-build source build/html
```

然后在http://127.0.0.1:8000看生成效果

## 维护

只需要在source文件夹下添加相应的文件夹，更新index.rst以及contents.rst（或者contents.md）文件，形成文件树即可。


