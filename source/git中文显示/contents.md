# git显示中文乱码

我在使用git的时候，假如我使用中文路径，那么git status时就会显示乱码，完全没法猜测，我看了本地环境，`LANG`是zh_CN.UTF-8，所以是可以显示中文的。原来是git默认会对路径名字进行quote处理，以确保特殊字符不会解析错误。所以显示的乱码应该是git进行quota处理后的结果。那么解决问题也很容易：

```bash
# 不要对路径进行quota
git config --global core.quotepath false
# 你可以在这里检验下是否修复了问题
# 进一步设置提交文字采用utf-8格式，支持多语言
git config --global i18n.commitencoding utf-8
# 日志输出文字采用utf-8格式
git config --global i18n.logoutputencoding utf-8
```


